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

#include "_2RealAbstractBlock.h"
#include "_2RealAbstractBlockManager.h"
#include "_2RealAbstractIOManager.h"
#include "_2RealAbstractStateManager.h"

namespace _2Real
{

	template< typename IOMgr, typename UberBlockMgr, typename SubBlockMgr, typename StateMgr >
	class Block : public AbstractBlock
	{

	public:

		Block(std::string const& name, AbstractBlock *super) :
			AbstractBlock(name, super),
			m_IOManager(new IOMgr(*this)),
			m_SubBlockManager(new SubBlockMgr(*this)),
			m_UberBlockManager(new UberBlockMgr(*this)),
			m_StateManager(new StateMgr(*this))
		{
		}

		virtual ~Block()
		{
			delete m_StateManager;
			delete m_IOManager;
			delete m_SubBlockManager;
			delete m_UberBlockManager;
		}

		void addUberBlock(AbstractBlock &uberBlock)
		{
			m_UberBlockManager->addBlock(uberBlock);
		}
		
		void removeUberBlock(AbstractBlock &uberBlock)
		{
			m_UberBlockManager->removeBlock(uberBlock);
		}

		void addSubBlock(AbstractBlock &subBlock)
		{
			m_SubBlockManager->addBlock(subBlock);
		}

		void removeSubBlock(AbstractBlock &subBlock)
		{
			m_SubBlockManager->removeBlock(subBlock);
		}

		void registerToNewData(std::string const& outlet, DataCallback callback)
		{
			m_IOManager->registerToNewData(outlet, callback);
		}

		void unregisterFromNewData(std::string const& outlet, DataCallback callback)
		{
			m_IOManager->unregisterFromNewData(outlet, callback);
		}

		const EngineData getValue(std::string const& paramName) const
		{
			return m_IOManager->getValue(paramName);
		}

		std::string const& getKey(std::string const& paramName) const
		{
			return m_IOManager->getKey(paramName);
		}

		void setValue(std::string const& paramName, Data const& value)
		{
			m_IOManager->setValue(paramName, value);
		}

		void insertValue(std::string const& paramName, Data const& value)
		{
			m_IOManager->insertValue(paramName, value);
		}

		void linkWith(std::string const& nameIn, AbstractBlock &out, std::string const& nameOut)
		{
			m_IOManager->linkWith(nameIn, out, nameOut);
		}

		void setUp()
		{
			m_StateManager->setUp();
		}

		void prepareForShutDown()
		{
			m_StateManager->prepareForShutDown();
		}

		const bool shutDown()
		{
			return m_StateManager->shutDown();
		}

		AbstractStateManager& getStateManager()
		{
			return *m_StateManager;
		}

		//AbstractUpdateManager& getTriggerManager()
		//{
		//	return *m_TriggerManager;
		//}

		AbstractBlockManager& getSubBlockManager()
		{
			return *m_SubBlockManager;
		}

		AbstractBlockManager& getUberBlockManager()
		{
			return *m_UberBlockManager;
		}

		AbstractIOManager& getIOManager()
		{
			return *m_IOManager;
		}

		AbstractStateManager const& getStateManager() const
		{
			return *m_StateManager;
		}

		//AbstractUpdateManager const& getTriggerManager() const
		//{
		//	return *m_TriggerManager;
		//}

		AbstractBlockManager const& getSubBlockManager() const
		{
			return *m_SubBlockManager;
		}

		AbstractBlockManager const& getUberBlockManager() const
		{
			return *m_UberBlockManager;
		}

		AbstractIOManager const& getIOManager() const
		{
			return *m_IOManager;
		}

	protected:

		AbstractIOManager				*m_IOManager;
		AbstractBlockManager			*m_SubBlockManager;
		AbstractBlockManager			*m_UberBlockManager;
		AbstractStateManager			*m_StateManager;
		//AbstractUpdateManager			*m_TriggerManager;

	};

}