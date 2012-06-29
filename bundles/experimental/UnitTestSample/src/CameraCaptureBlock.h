#pragma once

#include "_2RealBlock.h"
#include "_2RealInletHandle.h"
#include "_2RealOutletHandle.h"

class CameraCaptureBlock : public _2Real::Block
{

public:

	CameraCaptureBlock( _2Real::ContextBlock & context ) : Block() {}
	~CameraCaptureBlock() {}
	void shutdown() {}
	void update();
	void setup( _2Real::FrameworkContext &context );

private:

	_2Real::InletHandle				m_DoubleInletHandle;
	_2Real::OutletHandle			m_DoubleOutletHandle;
};