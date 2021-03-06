 /*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2012 Fachhochschule Salzburg GmbH

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

#include "_2RealBundle.h"
#include "ComplexCounterBlock.h"

void getBundleMetainfo( _2Real::bundle::BundleMetainfo &info )
{
	info.setAuthor( "fhs33223" );
	info.setDescription( "a test bundle that exports simple blocks and custom types - no context blocks" );
	info.setCategory( "testing" );
	info.setContact( "fhs33223@fh-salzburg.ac.at" );
	info.setVersion( 0, 0, 0 );

	info.exportsType( "simpleType", { _2Real::declareField( "uchar_field", "uchar" ), _2Real::declareField( "uint_field", "uint" ), _2Real::declareField( "ulong_field", "ulong" ), _2Real::declareField( "double_field", "double" ), _2Real::declareField( "float_field", "float" ) } );
	info.exportsType( "complexType", { _2Real::declareField( "string_field", "string" ), _2Real::declareField( "simple_field", "simpleType" ) } );
	info.exportsBlock( "counter", { _2Real::declareInlet( "increment" ), _2Real::declareInlet( "stringy" ), _2Real::declareMultiInlet( "multi" ), }, { _2Real::declareOutlet( "value" ), _2Real::declareOutlet( "msg" ), _2Real::declareOutlet( "test" ) }, { _2Real::declareParameter( "init" ) } );
}

void getTypeMetainfo( _2Real::bundle::CustomTypeMetainfo &info, _2Real::bundle::TypeMetainfoCollection const& existingTypes )
{
	if ( info.getName() == "simpleType" )
	{
		info.setDescription( "testing simple types, that is, types where all fields are not custom types" );
		info.setInitialFieldValue( "uchar_field", ( uint8_t )5 );
		info.setInitialFieldValue( "uint_field", ( uint32_t )0 );
		info.setInitialFieldValue( "ulong_field", ( uint64_t )23 );
		info.setInitialFieldValue( "double_field", -1.50 );
		info.setInitialFieldValue( "float_field", 0.1f );
	}
	else if ( info.getName() == "complexType" )
	{
		auto simpleInfo = std::static_pointer_cast< const _2Real::bundle::CustomTypeMetainfo >( existingTypes.getTypeMetainfo( "simpleType" ) );

		info.setDescription( "testing complex types, that is, types where at least one field is a custom type" );
		info.setInitialFieldValue( "string_field", std::string( "denn nudeln sind wir, und piraten wollen wir werden" ) );
		info.setInitialFieldValue( "simple_field", simpleInfo->makeData() );
	}
}

void getBlockMetainfo( _2Real::bundle::BlockMetainfo &info, _2Real::bundle::TypeMetainfoCollection const& types )
{
	if ( info.getName() == "counter" )
		ComplexCounter::getBlockMetainfo( info, types );
}