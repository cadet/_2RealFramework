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

namespace _2Real
{

	/**
	*	placeholder class thingie, since it's not really decided if we're going to use
	*	exceptions or return codes. 
	*	right now, i throw these objects in some functions, while using them as return
	*	values in others Oo
	*/

	class ErrorState
	{

	public:

		ErrorState();

		ErrorState(unsigned int const& _nr);

		unsigned int m_Code;

		static ErrorState			s_Success;
		static ErrorState			s_Failure;
		static ErrorState const&	success();
		static ErrorState const&	failure();

		bool operator==(ErrorState const& _rhs);
		bool operator!=(ErrorState const& _rhs);
		ErrorState& operator=(ErrorState const& _src);

	};

}