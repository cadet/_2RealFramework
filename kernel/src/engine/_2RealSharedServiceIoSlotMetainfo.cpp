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

#include "engine/_2RealSharedServiceIoSlotMetainfo.h"

namespace _2Real
{

	SharedServiceIoSlotMetainfo::SharedServiceIoSlotMetainfo( std::string const& name ) :
		std::enable_shared_from_this< SharedServiceIoSlotMetainfo >(),
		mName( name ),
		mDescription( "" ),
		mDatatype( "undefined" )
	{
	}

	SharedServiceIoSlotMetainfo::~SharedServiceIoSlotMetainfo()
	{
	}

	void SharedServiceIoSlotMetainfo::setName( std::string const& name )
	{
		mName = name;
	}

	void SharedServiceIoSlotMetainfo::setDescription( std::string const& description )
	{
		mDescription = description;
	}

	void SharedServiceIoSlotMetainfo::setDatatype( std::string const& datatype )
	{
		mDatatype = datatype;
	}

	std::string const& SharedServiceIoSlotMetainfo::getName() const
	{
		return mName;
	}

	std::string const& SharedServiceIoSlotMetainfo::getDescription() const
	{
		return mDescription;
	}

	std::string const& SharedServiceIoSlotMetainfo::getDatatype() const
	{
		return mDatatype;
	}

}