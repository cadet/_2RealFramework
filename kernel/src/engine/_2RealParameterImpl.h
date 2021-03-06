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
#include "engine/_2RealInSlot.h"

namespace _2Real
{
	class IoSlotMetainfoImpl;
	class InstanceId;
	class BlockImpl;

	class ParameterImpl : private InSlot, public std::enable_shared_from_this< ParameterImpl >
	{

	public:

		static std::shared_ptr< ParameterImpl > createFromMetainfo( std::shared_ptr< BlockImpl >, std::shared_ptr< const IoSlotMetainfoImpl > );

		ParameterImpl() = delete;
		ParameterImpl( ParameterImpl const& other ) = delete;
		ParameterImpl( ParameterImpl && other ) = delete;
		ParameterImpl& operator=( ParameterImpl const& other ) = delete;
		ParameterImpl& operator=( ParameterImpl && other ) = delete;

		~ParameterImpl() = default;

		std::shared_ptr< const InstanceId > getId() const;
		std::shared_ptr< BlockImpl >		getParent();

		void setData( std::shared_ptr< const DataItem > );

		using InSlot::update;
		using InSlot::getValue;

	private:

		ParameterImpl( std::shared_ptr< BlockImpl >, std::shared_ptr< const IoSlotMetainfoImpl >, std::shared_ptr< const InstanceId > );

		std::weak_ptr< BlockImpl >						mParent;
		std::weak_ptr< const IoSlotMetainfoImpl >		mMetainfo;
		std::shared_ptr< const InstanceId >			mId;

	};
}