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

#pragma once

#include "_2RealServiceTypedefs.h"
#include "_2RealEngineTypedefs.h"

#include <map>
#include <list>
#include <vector>

namespace _2Real
{

	/**
	*	currently, this class keeps track of all service factories
	*	as well as the actual service objects
	*	and because all containers are services, too, it keeps track of container creation as well
	*/

	class Plugin;
	class FactoryReference;
	class AbstractContainer;
	class ServiceImpl;
	class IdentifierImpl;
	class Identities;
	class Metadata;

	class ServiceFactory
	{

		friend class EngineImpl;

	public:

		/**
		*	registers factory function of a service, returns identifier of factory function
		*/
		IdentifierImpl const *const registerService(std::string const& _name, Plugin *const _plugin, Metadata const *const _metadata, ServiceCreator _creator) throw(...);

		/**
		*	returns true if service in question can be created
		*/
		const bool canCreate(IdentifierImpl const& _serviceID) const;

		/**
		*	returns true if the service in question is a singleton
		*/
		const bool isSingleton(IdentifierImpl const& _serviceID) const;

		/**
		*	returns true if the service in question can be reconfigured
		*/
		const bool canReconfigure(IdentifierImpl const& _serviceID) const;

		/**
		*	creates service container holding an instance of user service identified by _serviceID
		*/
		IdentifierImpl const *const createServiceContainer(IdentifierImpl const& _serviceID) throw(...);

		/**
		*	creates a production graph
		*/
		IdentifierImpl const *const createProductionGraph(std::string const& _name, eContainerType const _type) throw(...);

	private:

		/**
		*	
		*/
		ServiceFactory();

		/**
		*	
		*/
		ServiceFactory(Identities *const _ids);

		/**
		*	does nothing; should not be called
		*/
		ServiceFactory(ServiceFactory const& _src) throw(...);

		/**
		*	does nothing; should not be called
		*/
		ServiceFactory& operator=(ServiceFactory const& _src) throw(...);

		/**
		*	
		*/
		~ServiceFactory();

		/**
		*	yay, typedefs
		*/
		typedef std::list< ServiceImpl * >							ServiceList;

		/**
		*	yay, typedefs
		*/
		typedef std::pair< FactoryReference *, ServiceList >		ServiceReference;

		/**
		*	yay, typedefs
		*/
		typedef std::pair< IdentifierImpl, ServiceReference >		NamedServiceReference;
		
		/**
		*	yay, typedefs
		*/
		typedef std::map< IdentifierImpl, ServiceReference >		ReferenceTable;

		/**
		*	yay, pirates!
		*/
		typedef std::pair< IdentifierImpl, AbstractContainer * >	NamedContainer;
		
		/**
		*	yay, typedefs
		*/
		typedef std::map< IdentifierImpl, AbstractContainer * >		ContainerMap;

		/**
		*	
		*/
		ReferenceTable												m_References;

		/**
		*	
		*/
		ContainerMap												m_Containers;

		/**
		*
		*/
		Identities													*m_IDs;

	};

}