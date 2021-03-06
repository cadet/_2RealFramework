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
#include "app/_2RealTypeMetainfo_I.h"

namespace _2Real
{
	class CustomTypeMetainfoImpl;

	namespace app
	{
		class TypeMetainfo;

		class CustomTypeMetainfo : public TypeMetainfo_I
		{

		public:

			explicit CustomTypeMetainfo( std::shared_ptr< const CustomTypeMetainfoImpl > );

			/*
			*	@return: true is underlying object is valid
			*/
			bool			isValid() const;

			/*
			*	inherited, always returns true
			*/
			bool			isBasicType() const;

			/*
			*	@return: name
			*/
			std::string		getName() const;

			/*
			*	@return: description
			*/
			std::string		getDescription() const;

			/*
			*	creates & initializes a data item ( a boost::variant, see common/_2RealDataItem.h )
			*/
			DataItem		makeData() const;

			/*
			*	creates a custom data item - since this is a custom type metainfo, so you don't have to call boost::get
			*	a custom data item is basically a collection od DataItems ( see common/:2RealCustomdataItem )
			*/
			CustomDataItem	makeCustomData() const;

			/*
			*	@return: all data fields + their type metainfos
			*/
			std::vector< std::pair< std::string, std::shared_ptr< const TypeMetainfo_I > > > getDataFields() const;

		private:

			std::weak_ptr< const CustomTypeMetainfoImpl >		mImpl;

		};
	}
}