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

#include "_2RealFramework.h"
#include "_2RealAbstractServiceVariable.h"
#include "_2RealData.h"

namespace _2Real
{
	template< typename T >
	class ServiceParameter : public AbstractServiceVariable
	{

	public:

		ServiceParameter(std::string _name, T &_var) : AbstractServiceVariable(_name), m_Variable(_var) { }
		bool getFrom(const Data &_data);
		void insertInto(Data &_data) const;

	private:

		T		&m_Variable;
	};

	template< typename T >
	bool ServiceParameter< T >::getFrom(const Data &_data)
	{
		return _data.get< T >(AbstractServiceVariable::originalName(), m_Variable);
	}

	template< typename T >
	void ServiceParameter< T >::insertInto(Data &_data) const
	{
		_data.insert< T >(AbstractServiceVariable::originalName(), m_Variable);
	}
}