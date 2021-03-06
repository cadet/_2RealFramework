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

/*
*	helper object, contains handles to all inlets, outlets and parameters
*	in the order they were declared in
*	inlet handles must be downcasted properly ( see InletHandle_I::isMultiinlet )
*/

#include "common/_2RealStdIncludes.h"
#include "app/_2RealInletHandle_I.h"
#include "app/_2RealOutletHandle.h"
#include "app/_2RealParameterHandle.h"

namespace _2Real
{
	namespace app
	{
		class BlockIo
		{

		public:

			std::vector< std::shared_ptr< ParameterHandle > >		mParameters;
			std::vector< std::shared_ptr< InletHandle_I > >			mInlets;
			std::vector< std::shared_ptr< OutletHandle > >			mOutlets;

		};
	}
}