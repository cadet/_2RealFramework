/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#include "_2RealPlugin.h"
#include "_2RealPluginContext.h"
#include "_2RealErrorState.h"
#include "_2RealServiceFactory.h"

namespace _2Real
{

	Plugin::Plugin(std::string const& _path, std::string const& _class, ServiceFactory *const _factory) throw(...) :
		m_LibraryPath(_path), m_ClassName(_class), m_Factory(_factory), m_Activator(NULL), m_Metadata(NULL), m_State(Plugin::UNINSTALLED)
	{
	}

	Plugin::Plugin(Plugin const& _src) throw(...)
	{
		throw ErrorState::failure();
	}

	Plugin& Plugin::operator=(Plugin const& _src)
	{
		throw ErrorState::failure();
	}

	Plugin::~Plugin()
	{
		if (m_State != Plugin::UNINSTALLED)
		{
			try
			{
				stop();
				unload();
				uninstall();
			}
			catch (...)
			{
				std::cout << "plugin destruction error" << std::endl;
			}
		}
	}

	Plugin::ePluginState const& Plugin::state() const
	{
		return m_State;
	}
		
	std::string const& Plugin::name() const
	{
		return m_ClassName;
	}

	std::string const& Plugin::path() const
	{
		return m_LibraryPath;
	}

	Metadata const *const Plugin::metadata() const
	{
		return m_Metadata;
	}

	std::vector< IdentifierImpl > const& Plugin::serviceIDs() const
	{
		return m_Services;
	}

	void Plugin::registerService(std::string const& _name, ServiceCreator _creator) throw (...)
	{
		try
		{
			//metadata is TODO
			const IdentifierImpl *id = m_Factory->registerService(_name, this, NULL, _creator);
			m_Services.push_back(*id);
		}
		catch (...)
		{
			throw ErrorState::failure();
		}
	}

	void Plugin::install(IdentifierImpl const& _id) throw(...)
	{
		if (m_State == Plugin::UNINSTALLED)
		{
			m_ID = _id;

			if (m_LibraryPath.empty())
			{
				throw ErrorState::failure();
			}

			if (m_ClassName.empty())
			{
				throw ErrorState::failure();
			}

			if (m_Factory == NULL)
			{
				throw ErrorState::failure();
			}

			m_State = Plugin::INSTALLED;
		}

		m_State = Plugin::INVALID;
		throw ErrorState::failure();
	}

	void Plugin::uninstall() throw(...)
	{
		try
		{
			if (m_State == Plugin::ACTIVE)
			{
				stop();
			}

			if (m_State == Plugin::LOADED)
			{
				unload();
			}

			m_State = Plugin::UNINSTALLED;

		}
		catch (...)
		{
			m_State = Plugin::INVALID;
			throw ErrorState::failure();
		}
	}

	void Plugin::load() throw(...)
	{
		if (m_State == Plugin::INSTALLED)
		{
			try
			{
				m_PluginLoader.loadLibrary(m_LibraryPath);
			}
			catch (...)
			{
				m_State = Plugin::INVALID;
				throw ErrorState::failure();
			}

			m_State = Plugin::LOADED;
		}

		throw ErrorState::failure();
	}

	void Plugin::start() throw(...)
	{
		if (m_State == Plugin::LOADED)
		{
			try
			{
				if (m_PluginLoader.canCreate(m_ClassName))
				{
					m_Activator = m_PluginLoader.create(m_ClassName);
					if (!m_Activator)
					{
						m_State = Plugin::INVALID;
						throw ErrorState::failure();
					}

					m_Activator->start(new PluginContext(this));
				}
				else
				{
					m_State = Plugin::INVALID;
					throw ErrorState::failure();
				}
			}
			catch (...)
			{
				if (m_Activator)
				{
					delete m_Activator;
					m_Activator = NULL;
				}

				if (!m_Services.empty())
				{
					//clean up services
				}

				m_State = Plugin::INVALID;
				throw ErrorState::failure();
			}

			m_State = Plugin::ACTIVE;
		}

		throw ErrorState::failure();
	}

	void Plugin::stop() throw(...)
	{
		if (m_State == Plugin::ACTIVE)
		{
			try
			{
				m_PluginLoader.destroy(m_ClassName, m_Activator);
				if (!m_Services.empty())
				{
					//clean up services
				}
				delete m_Activator;
				m_Activator = NULL;
			}
			catch (...)
			{
				m_State = Plugin::INVALID;
				throw ErrorState::failure();
			}

			m_State = Plugin::LOADED;
		}

		throw ErrorState::failure();
	}

	void Plugin::unload() throw(...)
	{
		if (m_State == Plugin::LOADED)
		{
			try
			{
				if (m_PluginLoader.isLibraryLoaded(m_LibraryPath))
				{
					m_PluginLoader.unloadLibrary(m_LibraryPath);
				}
			}
			catch(...)
			{
				m_State = Plugin::INVALID;
				throw ErrorState::failure();
			}

			m_State = Plugin::INSTALLED;
		}

		throw ErrorState::failure();
	}

}