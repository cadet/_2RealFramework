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

#include "engine/_2RealStateData.h"

namespace _2Real
{
	void ActionRequest::start( std::shared_ptr< Threadpool > threads, CbPtr cb )
	{
		mCallback = cb;
		threads->requestThread( makeCallback( this, &ActionRequest::onThreadReady ) );
	}

	void ActionRequest::onThreadReady( std::shared_ptr< Thread > thread )
	{
		// this thread will be kept alive
		mThread = thread;

		// TODO
		// mThread->run( Block, appropriate function, mCallback );
	}
}
