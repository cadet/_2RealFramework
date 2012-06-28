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

#include "_2RealOwnedBlockManager.h"
#include "_2RealException.h"
#include "_2RealAbstractUberBlock.h"

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;
using std::list;

namespace _2Real
{

	SystemBlockManager::SystemBlockManager( AbstractUberBlock &owner ) :
		AbstractBlockManager( owner )
	{
	}

	SystemBlockManager::~SystemBlockManager()
	{
	}

	void SystemBlockManager::clear()
	{
		BlockList ready;

		for ( BlockList::iterator it = m_Blocks.begin(); it != m_Blocks.end(); ++it )
		{
			(*it)->prepareForShutDown();
		}

		for ( BlockList::iterator it = m_Blocks.begin(); it != m_Blocks.end(); /**/ )
		{
			if ( (*it)->shutDown( 1000 ) )
			{
				ready.push_back( *it );
			}
			else
			{
#ifdef _DEBUG
				cout << "failed to shut down " << ( *it )->getName() << endl;
#endif
			}

			it = m_Blocks.erase( it );
		}

		for ( BlockList::iterator it = ready.begin(); it != ready.end(); /**/ )
		{
			std::cout << "deleting!" << std::endl;
			delete *it;
			std::cout << "deleted!" << std::endl;
			it = ready.erase( it );
		}
	}

	AbstractUberBlock & SystemBlockManager::getBlock( BlockIdentifier const& id )
	{
		for ( BlockList::iterator it = m_Blocks.begin(); it != m_Blocks.end(); ++it )
		{
			if ( ( *it )->getIdentifier() == id )
			{
				return **it;
			}
		}

		ostringstream msg;
		msg << "sub block " << id.getName() << " not found in " << m_Owner.getName();
		throw NotFoundException( msg.str() );
	}

	AbstractUberBlock const& SystemBlockManager::getBlock( BlockIdentifier const& id ) const
	{
		for ( BlockList::const_iterator it = m_Blocks.begin(); it != m_Blocks.end(); ++it )
		{
			if ( ( *it )->getIdentifier() == id )
			{
				return **it;
			}
		}

		ostringstream msg;
		msg << "sub block " << id.getName() << " not found in " << m_Owner.getName();
		throw NotFoundException( msg.str() );
	}

	void SystemBlockManager::addBlock( AbstractUberBlock &block )
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
		for ( BlockList::iterator it = m_Blocks.begin(); it != m_Blocks.end(); ++it )
		{
			if ( ( *it ) == &block )
			{
				//in case the block already is a sub block, fail silently
				return;
			}
		}
		
		m_Blocks.push_back( &block );
	}
	void SystemBlockManager::removeBlock( AbstractUberBlock &block )
	{
		// in case of a system, removing means shutdown
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
		for ( BlockList::iterator it = m_Blocks.begin(); it != m_Blocks.end(); ++it )
		{
			if ( *it == &block )
			{
				( *it )->prepareForShutDown();
				if ( (*it)->shutDown( 5000 ) )
				{
					delete *it;
				}

				m_Blocks.erase( it );
				break;
			}
		}
	}

}