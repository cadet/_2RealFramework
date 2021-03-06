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

#include "common/_2RealBoostDefines.h"
#include "common/_2RealException.h"
#include "common/_2RealConstants.h"

#include "engine/_2RealSharedLibrary.h"
#include "engine/_2RealBundleMetainfoImpl.h"
#include "engine/_2RealBundleImpl.h"
#include "engine/_2RealBundleCollection.h"

namespace _2Real
{
	class BundleByAddress
	{
	public:
		explicit BundleByAddress( std::shared_ptr< const BundleImpl > bundle ) : mBaseline( bundle ) { assert( bundle.get() ); }
		bool operator()( std::pair< boost::signals2::connection, std::shared_ptr< const BundleImpl > > const& val ) const
		{
			assert( val.second.get() );
			return mBaseline.get() == val.second.get();
		}
	private:
		std::shared_ptr< const BundleImpl > mBaseline;
	};

	class BundleByPath
	{
	public:
		explicit BundleByPath( const Path path ) : mBaseline( path ) {}
		bool operator()( std::pair< boost::signals2::connection, std::shared_ptr< const BundleImpl > > const& val ) const
		{
			assert( val.second.get() );
			return mBaseline == val.second->getFilePath();
		}
	private:
		Path mBaseline;
	};

	/////////////////////////////////////////////////////////////////////////////////////

	BundleCollection::BundleCollection()
	{
		updateBundleDirectory();
	}

	void BundleCollection::clear( const unsigned long timeout )
	{
		// disconnect from all 'bundle was destroyed' signals
		for ( auto it : mBundles )
		{
			it.first.disconnect();
			it.second->unload( timeout );
		}

		mBundles.clear();
	}

	Path BundleCollection::getBundleDirectory() const
	{
		return mBundleDirectory;
	}

	void BundleCollection::updateBundleDirectory()
	{
		char * dir = std::getenv( Constants::BundleEnvName.c_str() );
		if ( nullptr != dir )
			mBundleDirectory = Path( dir );
		// TODO: exception? currently, the execution dir is being used
	}

	std::pair< std::shared_ptr< BundleImpl >, std::shared_ptr< const BundleMetainfoImpl > > BundleCollection::loadBundle( Path const& path, std::shared_ptr< TypeCollection > types )
	{
		Path absPath = path.is_absolute() ? path : mBundleDirectory / path;

		// check if bundle already exists
		auto it = std::find_if( mBundles.begin(), mBundles.end(), BundleByPath( absPath ) );
		if ( it != mBundles.end() )
		{
			auto result = std::make_pair( it->second, it->second->getMetainfo() );
			return result;
		}

		// actual dll loading, may throw bundle import exception
		std::shared_ptr< SharedLibrary > lib( new SharedLibrary( absPath ) );

		// get bundle metainfo
		std::shared_ptr< BundleMetainfoImpl > bundleMetainfo = BundleMetainfoImpl::make( lib, absPath, types );
		if ( !bundleMetainfo.get() )
		{
			std::ostringstream msg;
			msg << "shared library was found, but is not providing all necessary functions" << std::endl;
			throw BundleImportFailure( msg.str() );
		}

		// create bundle obj, register a unload listener & store
		std::shared_ptr< BundleImpl > bundle = BundleImpl::createFromMetainfo( bundleMetainfo, lib, absPath );
		boost::signals2::connection connection = bundle->registerToDestroyed( std::bind( &BundleCollection::bundleUnloaded, this, std::placeholders::_1 ) );
		mBundles.push_back( std::make_pair( connection, bundle ) );

		// return bundle + metainfo
		auto result = std::make_pair( bundle, bundleMetainfo );
		return result;
	}

	void BundleCollection::bundleUnloaded( std::shared_ptr< const BundleImpl > bundle )
	{
		auto it = std::find_if( mBundles.begin(), mBundles.end(), BundleByAddress( bundle ) );
		if ( it != mBundles.end() )
			mBundles.erase( it );
	}
}
