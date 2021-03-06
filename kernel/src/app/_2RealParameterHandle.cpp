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

#include "app/_2RealParameterHandle.h"
#include "app/_2RealBlockHandle.h"

#include "engine/_2RealParameterImpl.h"

#include "common/_2RealWeakPtrCheck.h"

namespace _2Real
{
	namespace app
	{
		ParameterHandle::ParameterHandle( std::shared_ptr< ParameterImpl > inlet ) :
			mImpl( inlet )
		{
		}

		bool ParameterHandle::isValid() const
		{
			std::shared_ptr< ParameterImpl > parameter = mImpl.lock();
			return ( nullptr != parameter.get() );
		}

		BlockHandle ParameterHandle::getBlock()
		{
			std::shared_ptr< ParameterImpl > parameter = checkValidity< ParameterImpl >( mImpl, "parameter" );
			return BlockHandle( parameter->getParent() );
		}

		void ParameterHandle::setValue( std::shared_ptr< const DataItem > value )
		{
			std::shared_ptr< ParameterImpl > parameter = checkValidity< ParameterImpl >( mImpl, "parameter" );
			parameter->setData( value );
		}
	}
}