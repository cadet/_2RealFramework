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

#include "engine/_2RealBundleImporter.h"
#include "helpers/_2RealStdIncludes.h"
#include "helpers/_2RealPath.h"

namespace _2Real
{
	class Bundle;
	class TypeRegistry;
	class Threadpool;

	class BundleCollection : public std::enable_shared_from_this< BundleCollection >
	{
	
	public:

		BundleCollection( std::shared_ptr< TypeRegistry > registry, std::shared_ptr< Threadpool >, std::shared_ptr< Threadpool > );
		~BundleCollection();

		std::shared_ptr< Bundle > 					loadBundle( Path const& pathToBundle );
		Path const&									getBundleDirectory() const;

		void										clear( const unsigned long timeout );
		void										bundleUnloaded( std::shared_ptr< const Bundle > );

		std::weak_ptr< Threadpool >					getThreadsForSingletonBlock();
		std::weak_ptr< Threadpool >					getThreadsForRegularBlock();

	private:

		BundleCollection( BundleCollection const& other );
		BundleCollection& operator=( BundleCollection const& other );

		void updateBundleDirectory();

		typedef std::map< Path, std::shared_ptr< Bundle > >		Bundles;

		// responsible for loading bundles
		BundleImporter								mBundleImporter;
		// initialized on contruction by querying an env variable; can't change during runtime
		Path										mBundleDirectory;
		// the bundles
		Bundles										mBundles;

		// ? not sure where these should be handled
		// ultimately, should each bundle collection. have its own threads??
		// maybe we'll reintroduce the concepts of systems some time?
		// currently, the threadpools are managed by the engine...
		std::weak_ptr< Threadpool >					mThreadsDedicated;
		std::weak_ptr< Threadpool >					mThreads;

	};
}