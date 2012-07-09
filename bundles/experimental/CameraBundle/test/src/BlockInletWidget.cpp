#include "BlockInletWidget.h"

using namespace std;
using namespace _2Real;

BlockInletWidget::BlockInletWidget(_2Real::app::InletHandle& inletHandle, QWidget *parent) 
	: QGroupBox(parent),
	  m_InletHandle ( inletHandle )
{
	try
	{
		QHBoxLayout*	layout = new QHBoxLayout();
		layout->addWidget( new QLabel(QString::fromStdString( inletHandle.getName())) );
	
		m_ValueWidget = new QDoubleSpinBox ();
		m_ValueWidget->setSingleStep(1);
	
		connect(m_ValueWidget, SIGNAL(valueChanged(double)), this, SLOT(setValue(double)));
		layout->addWidget( m_ValueWidget );

		setLayout( layout );
	}
	catch(Exception& e)
	{
		cout << e.message() << e.what() << std::endl;
	}
}

void BlockInletWidget::setValue(double value)
{
	try
	{
		m_InletHandle.setValue<int>((int)value);
	//	setValue<double>(value);
	}
	catch(_2Real::Exception& e)
	{
		cout << e.message() << e.what() << std::endl; 
	}
}