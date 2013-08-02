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

#include "helpers/_2RealStdIncludes.h"

namespace _2Real
{
	class DataField;
	typedef std::shared_ptr< const DataField >	DataFieldRef;
	typedef std::vector< const DataFieldRef >	DataFields;

	typedef std::pair< std::string, std::string >	TypeName;

	class DataField
	{
	public:
		DataField( std::string const& name, TypeName const& type, DataFields const& subfields ) :
			mFieldName( name ), mTypeName( type ), mSubFields( subfields )
		{
		}
		~DataField() {}
		std::string					getName() const { return mFieldName; }
		TypeName					getTypename() const { return mTypeName; }
		DataFields					getSubFields() const { return mSubFields; }
		static DataFieldRef			createSimpleField( std::string const& name, std::string const& type )
		{
			return DataFieldRef( new DataField( name, TypeName( sBasicTypeName, type ), DataFields() ) );
		}
		static DataFieldRef			createComplexField( std::string const& name, TypeName const& type, DataFields const& subfields )
		{
			return DataFieldRef( new DataField( name, type, subfields ) );
		}
		static const std::string sBasicTypeName;
	private:
		std::string					mFieldName;
		TypeName					mTypeName;
		DataFields					mSubFields;
	};
}