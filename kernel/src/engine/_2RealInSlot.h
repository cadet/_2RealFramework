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
#include "engine/_2RealIoSlot.h"
#include "helpers/_2RealEvent_T.h"

namespace _2Real
{
	class InSlot : public IoSlot
	{

	public:

		InSlot( std::shared_ptr< const SharedServiceIoSlotMetainfo > );

		virtual ~InSlot() {}

		using IoSlot::getName;
		using IoSlot::getMetainfo;

		template< typename TCallable >
		void registerToValueUpdated( TCallable *callable, void ( TCallable::*callback )( const unsigned int ) )
		{
			std::shared_ptr< AbstractCallback_T< const unsigned int > > listener( new MemberCallback_T< TCallable, const unsigned int >( callable, callback ) );
			mValueUpdatedEvent.addListener( listener );
		}

		template< typename TCallable >
		void unregisterFromValueUpdated( TCallable *callable, void ( TCallable::*callback )( const unsigned int ) )
		{
			std::shared_ptr< AbstractCallback_T< const unsigned int > > listener( new MemberCallback_T< TCallable, const unsigned int >( callable, callback ) );
			mValueUpdatedEvent.removeListener( listener );
		}

	private:

		InSlot( InSlot const& other );
		InSlot operator=( InSlot const& other );

		Event_T< const unsigned int >		mValueUpdatedEvent;

	};
}