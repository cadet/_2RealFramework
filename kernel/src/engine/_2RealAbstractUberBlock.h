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

#include "engine/_2RealIdentifier.h"

namespace _2Real
{

	class InletIO;
	class OutletIO;
	class Exception;

	class AbstractUberBlock
	{

	public:

		AbstractUberBlock( Identifier const& id );
		virtual ~AbstractUberBlock();

		Identifier	const&			getIdentifier() const;
		std::string const&			getName() const;
		unsigned int				getId() const;

		virtual void				setUp() = 0;
		virtual void				start() = 0;
		virtual void				stop( const bool blocking, const long timeout ) = 0;
		virtual void				prepareForShutDown() = 0;
		virtual bool				shutDown( const long timeout ) = 0;

		virtual void				updateWhenInletDataNew( InletIO &inletIO, const bool isSingleWeight ) = 0;
		virtual void				updateWhenInletDataValid( InletIO &inletIO ) = 0;
		virtual void				updateWithFixedRate( const double updatesPerSecond ) = 0;

		virtual void				handleException( Exception &e ) = 0;

	protected:

		Identifier					const m_Identifier;

	};

}