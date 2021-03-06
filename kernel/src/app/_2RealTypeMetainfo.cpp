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

#include "app/_2RealTypeMetainfo.h"
#include "engine/_2RealBasicTypeMetainfoImpl.h"

#include "common/_2RealWeakPtrCheck.h"

namespace _2Real
{
	namespace app
	{
		TypeMetainfo::TypeMetainfo( std::shared_ptr< const BasicTypeMetainfoImpl > meta ) :
			mImpl( meta )
		{
		}

		bool TypeMetainfo::isValid() const
		{
			std::shared_ptr< const BasicTypeMetainfoImpl > meta = mImpl.lock();
			return ( meta.get() != nullptr );
		}

		bool TypeMetainfo::isBasicType() const
		{
			std::shared_ptr< const BasicTypeMetainfoImpl > meta = checkValidity< const BasicTypeMetainfoImpl >( mImpl, "type metainfo" );
			return true;
		}

		DataItem TypeMetainfo::makeData() const
		{
			std::shared_ptr< const BasicTypeMetainfoImpl > meta = checkValidity< const BasicTypeMetainfoImpl >( mImpl, "type metainfo" );
			return meta->makeData();
		}

		std::string TypeMetainfo::getName() const
		{
			std::shared_ptr< const BasicTypeMetainfoImpl > meta = checkValidity< const BasicTypeMetainfoImpl >( mImpl, "type metainfo" );
			return meta->getName();
		}
	}
}