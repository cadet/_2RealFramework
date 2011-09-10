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

#include "_2RealEngine.h"
#include "_2RealEngineTypedefs.h"

#include "_2RealPluginMetadata.h"
#include "_2RealServiceMetadata.h"
#include "_2RealPluginPool.h"
#include "_2RealServiceFactory.h"
#include "_2RealEntities.h"
#include "_2RealProductionGraphs.h"
#include "_2RealContainer.h"
#include "_2RealIEntity.h"
#include "_2RealIdentifier.h"
#include "_2RealException.h"
#include "_2RealServiceImpl.h"
#include "_2RealServiceValue.h"
#include "_2RealServiceSlot.h"

#include <sstream>
#include <iostream>

namespace _2Real
{

	Engine *Engine::s_Instance = NULL;
	unsigned int Engine::s_iRefCount = 0;
	Poco::Mutex Engine::s_Mutex;
	
	Engine *const Engine::instance()
	{
		if (s_Mutex.tryLock(10000))
		{
			if(s_Instance == NULL)
			{
				s_Instance = new Engine();
			}
			s_iRefCount++;
			s_Mutex.unlock();
			return s_Instance;
		}

		throw Exception("engine instance(): could not lock mutex.");
	}

	void Engine::retain()
	{
		if (s_Mutex.tryLock(1000))
		{
			s_iRefCount++;
			
			s_Mutex.unlock();
			return;
		}
		
		throw Exception("engine retain(): could not lock mutex");
	}

	void Engine::release()
	{
		if (s_Mutex.tryLock(1000))
		{
			s_iRefCount--;
			
			if (s_iRefCount == 0 && s_Instance != NULL)
			{
				delete s_Instance;
				s_Instance = NULL;
			}

			s_Mutex.unlock();
			return;
		}

		throw Exception("engine release(): could not lock mutex");
	}

	Engine::Engine() :
		m_Plugins(new PluginPool()),
		m_Factory(new ServiceFactory()),
		m_Entities(new EntityTable()),
		m_Graphs(new ProductionGraphs())
	{
		//this is really ugly oO
		m_Entities->m_Plugins = m_Factory->m_Plugins = m_Plugins;
		m_Entities->m_Factory = m_Plugins->m_Factory = m_Factory;
		m_Entities->m_Graphs = m_Plugins->m_Graphs = m_Factory->m_Graphs = m_Graphs;
		m_Plugins->m_Entities = m_Factory->m_Entities = m_Graphs->m_Entities = m_Entities;
	}

	Engine::Engine(Engine const& _src)
	{
		throw Exception("engine: attempted copy");
	}

	Engine& Engine::operator=(Engine const& _src)
	{
		throw Exception("engine: attempted assignment");
	}

	Engine::~Engine()
	{
		delete m_Graphs;
		delete m_Plugins;
		delete m_Factory;
		delete m_Entities;
	}

	const Identifier Engine::createSystem(std::string const& _name)
	{
		try
		{
			//at some point, nirvana should be renamed system
			unsigned int id = m_Graphs->createSystem(_name);
			return m_Entities->getIdentifier(id);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::destroySystem(Identifier const& _id)
	{
		try
		{
			//destroys nirvana, and everything within it
			m_Graphs->destroySystem(_id.id());
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	const Identifier Engine::installPlugin(std::string const& _name, std::string const& _dir, std::string const& _file, std::string const& _class, Identifier const& _top)
	{
		try
		{
			//loads plugin & carries out init
			unsigned int id = m_Plugins->install(_name, _dir, _file, _class);
			return m_Entities->getIdentifier(id);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::dumpPluginInfo(Identifier const& _id, Identifier const& _top) const
	{
		try
		{
			PluginMetadata data = m_Plugins->pluginInfo(_id.id());
			std::string info = data.info();
			std::cout << info << std::endl;
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::dumpServiceInfo(Identifier const& _id, std::string const& _name, Identifier const& _top) const
	{
		try
		{
			ServiceMetadata data = m_Factory->serviceInfo(_id.id(), _name);
			std::string info = data.info();
			std::cout << info << std::endl;
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	const Identifier Engine::createService(std::string const& _name, Identifier const& _id, std::string const& _service, Identifier const& _top)
	{
		try
		{
			unsigned int id = m_Factory->createService(_name, _id.id(), _service, _top.id());
			return m_Entities->getIdentifier(id);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	Identifiers Engine::getSetupParameters(Identifier const& _id, Identifier const& _top) const
	{
		try
		{
			IDs ids;
			Identifiers setup;

			Entity *e = m_Entities->get(_id.id());
			if (!e)
			{
				throw Exception("non-existant entity");
			}

			Entity::eType type = e->type();
			if (type != Entity::SERVICE)
			{
				throw Exception("the entity is not a service");
			}

			ServiceContainer *service = static_cast< ServiceContainer * >(e);
			AbstractContainer *root = service->root();

			Entity *top = m_Entities->get(_top.id());
			if (!top)
			{
				//what the fuck?
				throw Exception("non-existant system");
			}

			AbstractContainer *system = static_cast< AbstractContainer * >(top);
			if (root != system)
			{
				//this could happen if there is more than one system and the user mixes them up
				throw Exception("the entity does not belong to the system");
			}

			ids = service->setupParamIDs();
			for (IDIterator it = ids.begin(); it != ids.end(); it++)
			{
				setup.push_back(m_Entities->getIdentifier(*it));
			}
			return setup;
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	Identifiers Engine::getInputSlots(Identifier const& _id, Identifier const& _top) const
	{
		try
		{
			IDs ids;
			Identifiers input;

			Entity *e = m_Entities->get(_id.id());
			if (!e)
			{
				throw Exception("non-existant entity");
			}

			Entity::eType type = e->type();
			if (!(type == Entity::SERVICE || type == Entity::SEQUENCE || type == Entity::SYNCHRONIZATION))
			{
				throw Exception("the entity is neither service nor sequence nor synchronization");
			}

			AbstractContainer *container = static_cast< AbstractContainer * >(e);
			AbstractContainer *root = container->root();

			Entity *top = m_Entities->get(_top.id());
			if (!top)
			{
				//what the fuck?
				throw Exception("non-existant system");
			}
			
			AbstractContainer *system = static_cast< AbstractContainer * >(top);
			if (root != system)
			{
				//this could happen if there is more than one system and the user mixes them up
				throw Exception("the entity does not belong to this system");
			}

			ids = container->inputSlotIDs();
			for (IDIterator it = ids.begin(); it != ids.end(); it++)
			{
				input.push_back(m_Entities->getIdentifier(*it));
			}
			return input;
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	Identifiers Engine::getOutputSlots(Identifier const& _id, Identifier const& _top) const
	{
		try
		{
			IDs ids;
			Identifiers output;

			Entity *e = m_Entities->get(_id.id());
			if (!e)
			{
				throw Exception("non-existant entity");
			}

			Entity::eType type = e->type();
			if (!(type == Entity::SERVICE || type == Entity::SEQUENCE || type == Entity::SYNCHRONIZATION))
			{
				throw Exception("the entity is neither service nor sequence nor synchronization");
			}

			AbstractContainer *container = static_cast< AbstractContainer * >(e);
			AbstractContainer *root = container->root();

			Entity *top = m_Entities->get(_top.id());
			if (!top)
			{
				//what the fuck?
				throw Exception("non-existant system");
			}

			AbstractContainer *system = static_cast< AbstractContainer * >(top);
			if (root != system)
			{
				//this could happen if there is more than one system and the user mixes them up
				throw Exception("the entity does not belong to this system");
			}

			ids = container->outputSlotIDs();
			for (IDIterator it = ids.begin(); it != ids.end(); it++)
			{
				output.push_back(m_Entities->getIdentifier(*it));
			}
			return output;
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	const Identifier Engine::createSequence(std::string const& _name, Identifier const& _idA, Identifier const& _idB, Identifier const& _top)
	{
		try
		{
			unsigned int id = m_Graphs->createSequence(_name, _idA.id(), _idB.id(), _top.id());
			return m_Entities->getIdentifier(id);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	const Identifier Engine::createSynchronization(std::string const& _name, Identifier const& _idA, Identifier const& _idB, Identifier const& _top)
	{
		try
		{
			unsigned int id = m_Graphs->createSynchronization(_name, _idA.id(), _idB.id(), _top.id());
			return m_Entities->getIdentifier(id);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::setParameterValue(Identifier const& _id, Poco::Any _any)
	{
		try
		{
			//Entity *e = m_Entities->get(_id.id());
			//ServiceValue *val = static_cast< ServiceValue * >(e);
			//val->setValue(_any);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::link(Identifier const& _in,  Identifier const& _out, Identifier const& _top)
	{
		try
		{
			//Entity *in = m_Entities->get(_in.id());
			//Entity *out = m_Entities->get(_out.id());
			//Entity *top = m_Entities->get(_top.id());
			//Container *nirvana = static_cast< Container * >(top);
			//ServiceSlot *inSlot = static_cast< ServiceSlot * >(in);
			//ServiceSlot *outSlot = static_cast< ServiceSlot * >(out);
			//ServiceContainer *inService = inSlot->service();
			//ServiceContainer *outService = outSlot->service();
			//Container *inFather = static_cast< Container * >(inService->father());
			//Container *outFather = static_cast< Container * >(outService->father());

			//if (inService == outService)
			//{
			//	throw Exception("could not link IO slots - slots belong to same service");
			//}

			//nirvana->stopChild(_in.id());
			//nirvana->stopChild(_out.id());
			//outSlot->linkWith(inSlot);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::registerToException(Identifier const& _id, ExceptionCallback _callback)
	{
		try
		{
			//Entity *e = m_Entities->get(_id.id());
			//AbstractContainer *container = static_cast< AbstractContainer * >(e);
			//AbstractContainer *father = container->father();
			//if (m_Graphs->isSystem(father->id()))
			//{
			//}
			//else
			//{
			//	throw Exception("");
			//}
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::registerToNewData(Identifier const& _id, NewDataCallback _callback)
	{
		try
		{
			//Entity *e = m_Entities->get(_id.id());
			//AbstractContainer *container = static_cast< AbstractContainer * >(e);
			//AbstractContainer *father = container->father();
			//if (m_Graphs->isSystem(father->id()))
			//{
			//	//container->registerDataCallback(_callback);
			//}
			//else
			//{
			//	//throw Exception::failure();
			//}
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	Identifiers Engine::getChildren(Identifier const& _id)
	{
		try
		{
			IDs ids;
			Identifiers identifiers;

			////
			//Entity *e = m_Entities->get(_id.id());
			//if (!(e->type() == Entity::SEQUENCE || e->type() == Entity::SYNCHRONIZATION || e->type() == Entity::NIRVANA))
			//{

			//}

			////children is a container function
			//AbstractContainer *container = static_cast< AbstractContainer * >(e);
			//Container *father = static_cast< Container * >(container);
			//ids = father->children();
			//for (IDIterator it = ids.begin(); it != ids.end(); it++)
			//{
			//	identifiers.push_back(m_Entities->getIdentifier(*it));
			//}
			return identifiers;
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::start(Identifier const& _id, Identifier const& _top)
	{
		try
		{
			//Entity *e = m_Entities->get(_id.id());

			//if (!e)
			//{
			//	throw Exception::failure();
			//}
			//else if (e->type() != Entity::SEQUENCE && e->type() != Entity::SYNCHRONIZATION &&  e->type() != Entity::SERVICE)
			//{
			//	throw Exception::failure();
			//}

			//Entity *n = m_Entities->get(_top.id());

			//if (!n)
			//{
			//	throw Exception::failure();
			//}

			//AbstractContainer *container = static_cast< AbstractContainer * >(e);
			//Container *nirvana = static_cast< Container * >(n);
			//Container *father = static_cast< Container * >(container->father());
			//
			//if (nirvana != father)
			//{
			//	throw Exception::failure();
			//}
			//else if (m_Graphs->isSystem(father->id()))
			//{
			//	father->startChild(_id.id());
			//}
			//else
			//{
			//	throw Exception::failure();
			//}
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::startAll(Identifier const& _top)
	{
		try
		{
			//if (m_Graphs->isSystem(_top.id()))
			//{
			//	Entity *e = m_Entities->get(_top.id());

			//	if (!e)
			//	{
			//		throw Exception::failure();
			//	}
			//	else if (e->type() != Entity::NIRVANA)
			//	{
			//		throw Exception::failure();
			//	}

			//	Container *nirvana = static_cast< Container * >(e);
			//	std::list< unsigned int > children = nirvana->children();
			//	for (std::list< unsigned int >::iterator it = children.begin(); it != children.end(); it++)
			//	{
			//		nirvana->startChild(*it);
			//	}
			//}
			//else
			//{
			//	throw Exception::failure();
			//}
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::stop(Identifier const& _id, Identifier const& _top)
	{
		try
		{
			//Entity *e = m_Entities->get(_id.id());

			//if (!e)
			//{
			//	//id does not exist
			//	throw Exception::failure();
			//}
			//else if (e->type() != Entity::SEQUENCE && e->type() != Entity::SYNCHRONIZATION &&  e->type() != Entity::SERVICE)
			//{
			//	//id != container
			//	throw Exception::failure();
			//}

			//Entity *n = m_Entities->get(_top.id());

			//if (!n)
			//{
			//	//top does not exist
			//	throw Exception::failure();
			//}
			//else if (n->type() != Entity::NIRVANA)
			//{
			//	//top != nirvana
			//	throw Exception::failure();
			//}

			//AbstractContainer *container = static_cast< AbstractContainer * >(e);
			//Container *root = static_cast< Container * >(container->root());
			//Container *nirvana = static_cast< Container * >(n);
			//Container *father = static_cast< Container * >(root->father());
			//if (nirvana != father)
			//{
			//	//id is not a child of top
			//	throw Exception::failure();
			//}
			//else if (m_Graphs->isSystem(father->id()))
			//{
			//	//stops root (will complete last update cycle)
			//	father->stopChild(root->id());
			//}
			//else
			//{
			//	throw Exception::failure();
			//}
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::stopAll(Identifier const& _top)
	{
		try
		{
			//if (m_Graphs->isSystem(_top.id()))
			//{
			//	Entity *e = m_Entities->get(_top.id());

			//	if (!e)
			//	{
			//		throw Exception::failure();
			//	}

			//	Container *nirvana = static_cast< Container * >(e);
			//	std::list< unsigned int > children = nirvana->children();
			//	for (std::list< unsigned int >::iterator it = children.begin(); it != children.end(); it++)
			//	{
			//		nirvana->stopChild(*it);
			//	}
			//}
			//else
			//{
			//	throw Exception::failure();
			//}
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::destroy(Identifier const& _id, Identifier const& _top)
	{
		try
		{
			//unsigned int id = _id.id();
			//Entity *e = m_Entities->get(id);
			//if (!e)
			//{
			//	throw Exception::failure();
			//}

			//Entity::eType type = e->type();
			//if (type != Entity::SEQUENCE && type != Entity::SYNCHRONIZATION && type != Entity::SERVICE)
			//{
			//	throw Exception::failure();
			//}

			//AbstractContainer *container = static_cast< AbstractContainer * >(e);
			//Container *father = static_cast< Container * >(container->father());
			//if (!father)
			//{
			//	throw Exception::failure();
			//}

			//AbstractContainer *root = container->root();
			//if (!root)
			//{
			//	throw Exception::failure();
			//}
			//Entity *n = m_Entities->get(_top.id());
			//if (!n)
			//{
			//	throw Exception::failure();
			//}

			//Container *nirvana = static_cast< Container * >(n);
			//Container *rootFather = static_cast< Container * >(root->father());
			//if (nirvana != rootFather)
			//{
			//	throw Exception::failure();
			//}

			////remove container from its father
			////this stops the container
			////& resets IO
			//father->remove(id);
			//container->shutdown();
			//m_Entities->destroy(id);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}

	void Engine::insert(Identifier const& _dst, unsigned int const& _index, Identifier const& _src, Identifier const& _top)
	{
		try
		{
			//Entity *src = m_Entities->get(_src.id());
			//if (!src)
			//{
			//	throw Exception::failure();
			//}
			//else if (src->type() != Entity::SEQUENCE && src->type() != Entity::SYNCHRONIZATION &&  src->type() != Entity::SERVICE)
			//{
			//	throw Exception::failure();
			//}
			//AbstractContainer *srcContainer = static_cast< AbstractContainer * >(src);
			//Container *srcFather = static_cast< Container * >(srcContainer->father());
			//Container *srcRoot = static_cast< Container * >(srcContainer->root());

			//Entity *dst = m_Entities->get(_dst.id());
			//if (!dst)
			//{
			//	throw Exception::failure();
			//}
			//else if (dst->type() != Entity::SEQUENCE && dst->type() != Entity::SYNCHRONIZATION)
			//{
			//	throw Exception::failure();
			//}
			//Container *dstContainer = static_cast< Container * >(dst);
			//Container *dstRoot = static_cast< Container * >(dstContainer->root());

			//Entity *top = m_Entities->get(_top.id());
			//if (!top)
			//{
			//	throw Exception::failure();
			//}
			//else if (top->type() != Entity::NIRVANA)
			//{
			//	throw Exception::failure();
			//}
			//Container *nirvana = static_cast< Container * >(top);

			//if (_index > dstContainer->childCount())
			//{
			//	throw Exception::failure();
			//}

			//nirvana->stopChild(srcRoot->id());
			//nirvana->stopChild(dstRoot->id());
			//srcFather->remove(srcContainer->id());
			//dstContainer->add(srcContainer, _index);
		}
		catch (Exception &e)
		{
			throw e;
		}
	}
}