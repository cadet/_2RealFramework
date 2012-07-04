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

#include "app/_2RealCallbacks.h"
#include "helpers/_2RealHandleAble.h"

#include <string>

namespace _2Real
{
	class FunctionBlock;

	namespace app
	{
		class InletHandle;
		class OutletHandle;
		class BlockInfo;

		class BlockHandle : public Handle
		{

		public:

			typedef std::vector< InletHandle >					InletHandles;
			typedef std::vector< InletHandle >::iterator		InletHandleIterator;
			typedef std::vector< InletHandle >::const_iterator	InletHandleConstIterator;

			typedef std::vector< OutletHandle >					OutletHandles;
			typedef std::vector< OutletHandle >::iterator		OutletHandleIterator;
			typedef std::vector< OutletHandle >::const_iterator	OutletHandleConstIterator;

			BlockHandle();
			BlockHandle( FunctionBlock &block );
			~BlockHandle();
			BlockHandle( BlockHandle const& other );
			BlockHandle& operator=( BlockHandle const& other );

			BlockInfo getBlockInfo() const;

			// negative or zero: no time based update at all
			void setUpdateRate( const double updatesPerSecond );

			void setup();
			void start();
			void stop();

			InletHandle &			getInletHandle( std::string const& name ) const;
			OutletHandle &			getOutletHandle( std::string const& name ) const;
			InletHandles const&		getAllInletHandles() const;
			OutletHandles const&	getAllOutletHandles() const;

			// callback registration for free functions
			void registerToNewData( BlockDataCallback callback, void *userData = nullptr );
			void unregisterFromNewData( BlockDataCallback callback, void *userData = nullptr );

			// callback registration for member functions
			template< typename TCallable >
			void registerToNewData( TCallable &callable, void ( TCallable::*callback )( std::list< AppData > const& ) )
			{
				BlockCallback *cb = new MemberCallback< TCallable, std::list< AppData > const& >( callable, callback );
				registerToNewDataInternal( *cb );
			}

			template< typename TCallable >
			void unregisterFromNewData( TCallable &callable, void ( TCallable::*callback )( std::list< AppData > const& ) )
			{
				BlockCallback *cb = new MemberCallback< TCallable, std::list< AppData > const& >( callable, callback );
				unregisterFromNewDataInternal( *cb );
			}

		private:

			void registerToNewDataInternal( BlockCallback &cb );
			void unregisterFromNewDataInternal( BlockCallback &cb );

			FunctionBlock		*m_Block;

		};
	}
}