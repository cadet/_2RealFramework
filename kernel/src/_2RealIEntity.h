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

#include <string>

namespace _2Real
{

	/**
	*	entity - plugin/ service / service creator / container / service param / service slot
	*/

	class IdentifierImpl;

	class Entity
	{

		friend class EntityTable;

	public:

		enum eType
		{
			INVALID,
			PLUGIN,
			FACTORY,
			SERVICE,
			SEQUENCE,
			SYNCHRONIZATION,
			NIRVANA,
			SETUP,
			INPUT,
			OUTPUT
		};

		Entity(IdentifierImpl *const _id);
		Entity(Entity const& _src) throw(...);
		Entity& operator=(Entity const& _src) throw(...);
		virtual ~Entity();
		
		eType const& type() const;
		unsigned int const& id() const;
		std::string const& name() const;
		void setInfo(std::string const& _info);

	private:
	
		IdentifierImpl		*m_ID;

	};

}