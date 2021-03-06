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

#include "common/_2RealStdIncludes.h"
#include "common/_2RealSignals.h"
#include "common/_2RealBlockResult.h"

#include "bundle/_2RealBlock.h"
#include "engine/_2RealBlockAccess.h"

namespace _2Real
{

	class BlockMetainfoImpl;
	class UpdateTrigger_I;
	class ThreadpoolImpl_I;
	class UpdatePolicyImpl;
	class BlockStateHandler;
	class InstanceId;
	class BundleImpl;
	class InletImpl_I;
	class InletImpl;
	class MultiInletImpl;

	class BlockIo
	{

	public:

		BlockIo( BlockAccess const& access );

		std::vector< std::shared_ptr< InletImpl_I > >			mInlets;
		std::vector< std::shared_ptr< ParameterImpl > >			mParameters;
		std::vector< std::shared_ptr< OutletImpl > >			mOutlets;
		std::shared_ptr< bundle::Block >	mBlockObj;	

		std::shared_ptr< InletImpl >		getInlet( std::string const& );
		std::shared_ptr< MultiInletImpl >	getMultiInlet( std::string const& );
		std::shared_ptr< OutletImpl >		getOutlet( std::string const& );
		std::shared_ptr< ParameterImpl >	getParameter( std::string const& );

		boost::signals2::connection			registerToException( boost::signals2::signal< void( Exception ) >::slot_type ) const;

		void doSetup();
		void doUpdate();
		void doShutdown();
		void doNothing();

	private:

		mutable boost::signals2::signal< void( Exception ) >	mException;
		BlockAccess							mKey;

	};

	class BlockImpl : public std::enable_shared_from_this< BlockImpl >
	{

	public:

		static std::shared_ptr< BlockImpl > createFromMetainfo( std::shared_ptr< BundleImpl >, std::shared_ptr< const BlockMetainfoImpl >, std::shared_ptr< ThreadpoolImpl_I >, std::vector< std::shared_ptr< BlockImpl > > const&, const uint64_t );

		BlockImpl() = delete;
		BlockImpl( BlockImpl const& other ) = delete;
		BlockImpl operator=( BlockImpl const& other ) = delete;
		BlockImpl( BlockImpl && other ) = delete;
		BlockImpl& operator=( BlockImpl && other ) = delete;

		~BlockImpl() = default;

		std::shared_ptr< const InstanceId >			getId() const;
		std::shared_ptr< BundleImpl >					getParent();

		std::future< BlockResult > setup();
		std::future< BlockResult > singlestep();
		std::future< BlockResult > shutdown();

		std::future< BlockResult > startUpdating();
		std::future< BlockResult > startUpdating( std::shared_ptr< UpdateTrigger_I > );
		std::future< BlockResult > stopUpdating();

		void						destroy( const uint64_t );
		std::future< BlockResult >	parentUnloaded();

		std::shared_ptr< BlockIo >			getBlockIo();
		std::shared_ptr< UpdatePolicyImpl >	getUpdatePolicy();

		std::shared_ptr< InletImpl >		getInlet( std::string const& );
		std::shared_ptr< MultiInletImpl >	getMultiInlet( std::string const& );
		std::shared_ptr< OutletImpl >		getOutlet( std::string const& );
		std::shared_ptr< ParameterImpl >	getParameter( std::string const& );

		boost::signals2::connection			registerToException( boost::signals2::signal< void( Exception ) >::slot_type );
		boost::signals2::connection			registerToDestroyed( boost::signals2::signal< void( std::shared_ptr< const BlockImpl > ) >::slot_type );

	private:

		BlockImpl( std::shared_ptr< BundleImpl >, std::shared_ptr< const BlockMetainfoImpl >, std::shared_ptr< const InstanceId >, std::shared_ptr< ThreadpoolImpl_I > );

		std::weak_ptr< BundleImpl >								mParent;
		std::weak_ptr< const BlockMetainfoImpl >		mMetainfo;
		std::shared_ptr< const InstanceId >					mId;
		std::shared_ptr< UpdatePolicyImpl >						mUpdatePolicy;
		std::shared_ptr< BlockStateHandler >						mStateHandler;
		std::shared_ptr< BlockIo >							mIo;

		boost::signals2::signal< void( std::shared_ptr< const BlockImpl > ) > mDestroyed;

	};

}