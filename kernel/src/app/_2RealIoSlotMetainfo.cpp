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

#include "app/_2RealIoSlotMetainfo.h"
#include "app/_2RealTypeMetainfo.h"
#include "app/_2RealCustomTypeMetainfo.h"
#include "engine/_2RealTypeMetainfoImpl_I.h"
#include "engine/_2RealBasicTypeMetainfoImpl.h"
#include "engine/_2RealCustomTypeMetainfoImpl.h"
#include "engine/_2RealIoSlotMetainfoImpl.h"
#include "common/_2RealWeakPtrCheck.h"

namespace _2Real
{
	namespace app
	{
		IoSlotMetainfo::IoSlotMetainfo( std::shared_ptr< const IoSlotMetainfoImpl > meta ) :
			mImpl( meta )
		{
		}

		bool IoSlotMetainfo::isValid() const
		{
			std::shared_ptr< const IoSlotMetainfoImpl > meta = mImpl.lock();
			return ( meta.get() != nullptr );
		}

		std::string IoSlotMetainfo::getName() const
		{
			std::shared_ptr< const IoSlotMetainfoImpl > meta = checkValidity< const IoSlotMetainfoImpl >( mImpl, "io slot metainfo" );
			return meta->getName();
		}

		std::string IoSlotMetainfo::getDescription() const
		{
			std::shared_ptr< const IoSlotMetainfoImpl > meta = checkValidity< const IoSlotMetainfoImpl >( mImpl, "io slot metainfo" );
			return meta->getDescription();
		}

		std::shared_ptr< TypeMetainfo_I > IoSlotMetainfo::getTypeMetainfo() const
		{
			std::shared_ptr< const IoSlotMetainfoImpl > meta = checkValidity< const IoSlotMetainfoImpl >( mImpl, "io slot metainfo" );
			std::shared_ptr< const TypeMetainfoImpl_I > tmp = meta->getTypeMetainfo();
			if ( tmp->isBasicType() )
				return std::shared_ptr< TypeMetainfo_I >( new TypeMetainfo( std::static_pointer_cast< const BasicTypeMetainfoImpl >( tmp ) ) );
			else
				return std::shared_ptr< TypeMetainfo_I >( new CustomTypeMetainfo( std::static_pointer_cast< const CustomTypeMetainfoImpl >( tmp ) ) );
		}

		DataItem IoSlotMetainfo::getInitialValue() const
		{
			std::shared_ptr< const IoSlotMetainfoImpl > meta = checkValidity< const IoSlotMetainfoImpl >( mImpl, "io slot metainfo" );
			return meta->getInitialValue();
		}

		bool IoSlotMetainfo::isMulti() const
		{
			std::shared_ptr< const IoSlotMetainfoImpl > meta = checkValidity< const IoSlotMetainfoImpl >( mImpl, "io slot metainfo" );
			return meta->isMulti();
		}
	}
}