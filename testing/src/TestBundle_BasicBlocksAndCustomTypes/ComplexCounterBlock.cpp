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

#include "ComplexCounterBlock.h"
#include "common/_2RealData.h"

#include <Windows.h>

void ComplexCounter::getBlockMetainfo( _2Real::bundle::BlockMetainfo &info, _2Real::bundle::TypeMetainfoCollection const& types )
{
	_2Real::bundle::BlockMetainfo &counterinfo = dynamic_cast< _2Real::bundle::BlockMetainfo & >( info );

	auto simpleInfo = std::static_pointer_cast< const _2Real::bundle::CustomTypeMetainfo >( types.getTypeMetainfo( "simpleType" ) );
	auto complexInfo = std::static_pointer_cast< const _2Real::bundle::CustomTypeMetainfo >( types.getTypeMetainfo( "complexType" ) );

	counterinfo.setBlockClass< ComplexCounter >();
	counterinfo.setDescription( "counter" );

	_2Real::bundle::UpdatePolicyMetainfo policy = counterinfo.getUpdatePolicyMetainfo();
	policy.set( _2Real::DefaultUpdatePolicy::ANY );

	_2Real::bundle::InletMetainfo in = counterinfo.getInletMetainfo( "increment" );
	in.setDescription( "counter increment" );
	in.setDatatypeAndInitialValue( simpleInfo->makeData() );

	_2Real::bundle::InletMetainfo stringy = counterinfo.getInletMetainfo( "stringy" );
	stringy.setDescription( "test string inlet" );
	stringy.setDatatypeAndInitialValue( std::string( "yay" ) );

	_2Real::bundle::InletMetainfo multi = counterinfo.getInletMetainfo( "multi" );
	multi.setDescription( "test multi inlet" );
	multi.setDatatypeAndInitialValue( ( uint32_t )0 );

	_2Real::bundle::ParameterMetainfo param = counterinfo.getParameterMetainfo( "init" );
	param.setDescription( "counter initial value" );
	param.setDatatypeAndInitialValue( complexInfo->makeData() );

	_2Real::bundle::OutletMetainfo out = counterinfo.getOutletMetainfo( "value" );
	out.setDescription( "counter current value" );
	out.setDatatypeAndInitialValue( complexInfo->makeData() );

	_2Real::bundle::OutletMetainfo msg = counterinfo.getOutletMetainfo( "msg" );
	msg.setDescription( "a test message" );
	msg.setDatatypeAndInitialValue( std::string( "NARF" ) );

	_2Real::bundle::OutletMetainfo test = counterinfo.getOutletMetainfo( "test" );
	test.setDescription( "a test int" );
	test.setDatatypeAndInitialValue( (uint32_t)0 );
}

ComplexCounter::ComplexCounter( _2Real::bundle::BlockIo const& io, std::vector< std::shared_ptr< _2Real::bundle::Block > > const& dependencies ) :
	_2Real::bundle::Block( io, dependencies ), mUpdates( 0 )
{
}



ComplexCounter::~ComplexCounter()
{
}

void ComplexCounter::setup()
{	
	auto parameter = mIo.mParameters[ 0 ];
	auto outlet = mIo.mOutlets[ 0 ];
	boost::get< _2Real::CustomDataItem >( outlet->getValue() ) = boost::get< _2Real::CustomDataItem >( parameter->getValue() );
}

void ComplexCounter::update()
{
	auto inlet = std::dynamic_pointer_cast< _2Real::bundle::InletHandle >( mIo.mInlets[ 0 ] );
	auto outlet = mIo.mOutlets[ 0 ];

	auto message = mIo.mOutlets[ 1 ];
	auto test = mIo.mOutlets[ 2 ];

	// extract a reference to the simple field in the outlet data
	_2Real::CustomDataItem & counter = boost::get< _2Real::CustomDataItem >( outlet->getValue() );
	_2Real::CustomDataItem & val_out = counter.getValue< _2Real::CustomDataItem >( "simple_field" );

	// get const& ref to inlet data
	_2Real::CustomDataItem const& val_in = boost::get< _2Real::CustomDataItem >( inlet->getValue() );

	/*
	*	here, boost::apply_visitor might come in handy...
	*/
	val_out.getValue< uint8_t >( "uchar_field" ) += val_in.getValue< uint8_t >( "uchar_field" );
	val_out.getValue< uint32_t >( "uint_field" ) += val_in.getValue< uint32_t >( "uint_field" );
	val_out.getValue< uint64_t >( "ulong_field" ) += val_in.getValue< uint64_t >( "ulong_field" );
	val_out.getValue< float >( "float_field" ) += val_in.getValue< float >( "float_field" );
	val_out.getValue< double >( "double_field" ) += val_in.getValue< double >( "double_field" );

	std::cout << "UPDATE" << std::endl;
	//std::cout << counter << std::endl;

	++mUpdates;

	std::string &s = boost::get< std::string >( message->getValue() );
	uint32_t &i = boost::get< uint32_t >( test->getValue() );

	s = std::to_string( mUpdates );
	i = mUpdates;
}

void ComplexCounter::shutdown()
{
}