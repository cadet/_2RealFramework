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
#include "bundle/_2RealInletHandle_I.h"

namespace _2Real
{
	class MultiInletImpl;

	namespace bundle
	{
		class InletHandle;

		class MultiInletHandle : public InletHandle_I
		{

		public:

			explicit MultiInletHandle( std::shared_ptr< MultiInletImpl > );

			bool isMultiInlet() const;

			/*
			*	@return: number of subinlets
			*/
			uint32_t getSize() const;

			/*
			*	@return: true if empty
			*/
			bool isEmpty() const;

			/*
			*	@return: subinlet at index idx
			*/
			InletHandle operator[]( const uint32_t indx );
		
		private:

			std::shared_ptr< MultiInletImpl >	mImpl;

		};
	}
}