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

#include "helpers/_2RealStdIncludes.h"
#include "enums/_2RealThreadpoolPolicy.h"

namespace _2Real
{
	class Threadpool;

	class ThreadpoolCollection : public std::enable_shared_from_this< ThreadpoolCollection >
	{
	
	public:

		ThreadpoolCollection();
		~ThreadpoolCollection();

		std::shared_ptr< Threadpool >	createThreadpool( const ThreadpoolPolicy );

	private:

		ThreadpoolCollection( ThreadpoolCollection const& other ) = delete;
		ThreadpoolCollection& operator=( ThreadpoolCollection const& other ) = delete;

		typedef std::set< std::shared_ptr< Threadpool > >		Threadpools;

		Threadpools				mThreadpools;

	};
}