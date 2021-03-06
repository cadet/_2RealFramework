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

#include "app/_2RealLinkHandle.h"
#include "engine/_2RealLink.h"

#include "common/_2RealWeakPtrCheck.h"

namespace _2Real
{
	namespace app
	{
		LinkHandle::LinkHandle( std::shared_ptr< Link > link ) :
			mImpl( link )
		{
		}

		bool LinkHandle::isValid() const
		{
			std::shared_ptr< Link > link = mImpl.lock();
			return ( nullptr != link.get() );
		}

		void LinkHandle::destroy()
		{
			std::shared_ptr< Link > link = checkValidity< Link >( link, "link" );
			link->destroy();
		}
	}
}
	