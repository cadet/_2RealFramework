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

#include "_2RealIContainer.h"
#include "_2RealIdentifierImpl.h"

#include <list>

#include "Poco/BasicEvent.h"

namespace _2Real
{

	/**
	*
	*/

	class AbstractContainer : public IContainer
	{

		friend class ServiceFactory;

	public:

		/**
		*	returns identifier
		*/
		IdentifierImpl const& id() const;

		/**
		*
		*/
		void start(bool const& _runOnce) throw(...);

		/**
		*
		*/
		void stop();

		/**
		*
		*/
		bool const& canReconfigure() const;

		/**
		*
		*/
		void setup(ServiceContext *const _contextPtr) throw(...);

		/**
		*	
		*/
		void addListener(IDataQueue *const _queue) throw(...);
		
		/**
		*
		*/
		void removeListener(IDataQueue *const _queue) throw(...);
		
		/**
		*
		*/
		void receiveData(NamedData &_data);

		/**
		*
		*/
		void sendData(bool const& _blocking);

	protected:

		/**
		*
		*/
		AbstractContainer(IdentifierImpl const& _id);

		/**
		*
		*/
		AbstractContainer(AbstractContainer const& _src);

		/**
		*
		*/
		AbstractContainer& operator=(AbstractContainer const& _src);

		/**
		*
		*/
		~AbstractContainer();

		/**
		*
		*/
		bool								m_bRunOnce;

		/**
		*
		*/
		bool								m_bRun;

		/**
		*
		*/
		bool								m_bIsConfigured;

		/**
		*
		*/
		bool								m_bCanReconfigure;

		/**
		*
		*/
		ConfigurationData					*m_Configuration;

		/**
		*
		*/
		std::list< NamedData >				m_DataList;

		/**
		*
		*/
		Poco::BasicEvent< NamedData >		m_NewData;

		/**
		*
		*/
		IdentifierImpl						m_ID;

	};

}