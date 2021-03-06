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
#include "common/_2RealVersion.h"

namespace _2Real
{
	class BundleMetainfoImpl;

	namespace app
	{
		class BlockMetainfo;
		class CustomTypeMetainfo;

		class BundleMetainfo
		{

		public:

			/*
			*	created by engine, via Engine::loadBundle
			*/
			explicit BundleMetainfo( std::shared_ptr< const BundleMetainfoImpl > );

			/*
			*	@return: true is underlying object is valid
			*/
			bool			isValid() const;

			/*
			*	@return: description
			*/
			std::string		getDescription() const;

			/*
			*	@return: author
			*/
			std::string		getAuthor() const;

			/*
			*	@return:contact address
			*/
			std::string		getContact() const;

			/*
			*	@return: category
			*/
			std::string		getCategory() const;
			
			/*
			*	@return: version
			*/
			Version			getVersion() const;

			/*
			*	@return: the metainjfos of all exported blocks
			*/
			std::vector< BlockMetainfo >		getExportedBlocks() const;

			/*
			*	@return: the metainfos of all exported types
			*/
			std::vector< CustomTypeMetainfo >	getExportedTypes() const;

			/*
			*	@ return: specific block metainfo, by name
			*/
			BlockMetainfo						getExportedBlock( std::string const& );

			/*
			*	@ return: specific type metainfo, by name
			*/
			CustomTypeMetainfo					getExportedType( std::string const& );

		private:

			std::weak_ptr< const BundleMetainfoImpl >		mImpl;

		};
	}
}