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
#include "common/_2RealData.h"

namespace _2Real
{
	class IoSlotMetainfoImpl;

	namespace bundle
	{
		class IoSlotMetainfo
		{

		public:

			explicit IoSlotMetainfo( std::shared_ptr< IoSlotMetainfoImpl > );

			/*
			*	set description
			*/
			void setDescription( std::string const& description );

			/*
			*	sets the initial value: careful, this causes the datatype to also be set
			*	- so setDataTypeAndInitialValue( -5 ) will set to int32_t, for example
			*/
			void setDatatypeAndInitialValue( DataItem const& initialValue );

		protected:

			std::shared_ptr< IoSlotMetainfoImpl >		mImpl;

		};

		typedef IoSlotMetainfo InletMetainfo;
		typedef IoSlotMetainfo OutletMetainfo;
		typedef IoSlotMetainfo ParameterMetainfo;

	}
}