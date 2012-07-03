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

#include "engine/_2RealAbstractIOManager.h"

namespace _2Real
{
	namespace app
	{
		class InletHandle;
		class OutletHandle;
		class ParameterHandle;
	}

	namespace bundle
	{
		class InletHandle;
		class OutletHandle;
		class ParameterHandle;
	}
	
	class ParamData;
	class FunctionBlock;
	class FunctionBlockStateManager;
	class FunctionBlockUpdatePolicy;

	class FunctionBlockIOManager : public AbstractIOManager
	{

	public:

		FunctionBlockIOManager( FunctionBlock &owner );
		~FunctionBlockIOManager();

		void						clear();

		void						registerToNewData( Outlet const& outlet, app::OutletCallback &cb );
		void						unregisterFromNewData( Outlet const& outlet, app::OutletCallback &cb );
		void						registerToNewData( app::BlockCallback &cb );
		void						unregisterFromNewData( app::BlockCallback &cb );

		void						addInlet( ParamData const& data );
		void						addOutlet( ParamData const& data );
		void						addParameter( ParamData const& data );

		app::InletHandle &			getAppInletHandle( std::string const& name );
		app::OutletHandle &			getAppOutletHandle( std::string const& name );
		app::ParameterHandle &		getAppParameterHandle( std::string const& name );

		bundle::InletHandle &		getBundleInletHandle( std::string const& name );
		bundle::OutletHandle &		getBundleOutletHandle( std::string const& name );
		bundle::ParameterHandle &	getBundleParameterHandle( std::string const& name );

		void						updateInletValues();
		void						updateOutletValues();
		void						updateInletBuffers();
		void						updateParameterValues();

	private:

		friend class FunctionBlock;

		FunctionBlockStateManager		*m_StateManager;
		FunctionBlockUpdatePolicy		*m_UpdatePolicy;

		mutable Poco::FastMutex			m_InletAccess;
		mutable Poco::FastMutex			m_OutletAccess;
		mutable Poco::FastMutex			m_ParamAccess;
		InletVector						m_Inlets;
		OutletVector					m_Outlets;
		ParameterVector					m_Parameters;

		Inlet &							getInlet( std::string const& name );
		Outlet &						getOutlet( std::string const& name );
		Parameter &						getParameter( std::string const& name );

	};

}