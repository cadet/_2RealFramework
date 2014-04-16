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
	class MetainfoId;

	class TypeMetainfoImpl_I
	{

	public:

		TypeMetainfoImpl_I() = default;
		virtual ~TypeMetainfoImpl_I() = default;

		TypeMetainfoImpl_I( TypeMetainfoImpl_I const& ) = delete;
		TypeMetainfoImpl_I& operator=( TypeMetainfoImpl_I const& ) = delete;
		TypeMetainfoImpl_I( TypeMetainfoImpl_I && ) = delete;
		TypeMetainfoImpl_I& operator=( TypeMetainfoImpl_I && ) = delete;

		virtual DataItem								makeData() const = 0;
		virtual bool									isBasicType() const = 0;
		virtual std::shared_ptr< const MetainfoId >		getId() const = 0;
		virtual std::string								getName() const = 0;

	};
}