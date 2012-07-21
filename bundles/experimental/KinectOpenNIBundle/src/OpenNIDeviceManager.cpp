#include "OpenNIDeviceManager.h"

#include <iostream>
#include <string>

using _2Real::bundle::Block;
using _2Real::bundle::BlockHandle;
using _2Real::Exception;
using std::cout;
using std::endl;
using std::string;
using namespace _2RealKinectWrapper;


OpenNIDeviceManager::OpenNIDeviceManager() : ContextBlock()
{
}

OpenNIDeviceManager::~OpenNIDeviceManager()
{
}

void OpenNIDeviceManager::setup( BlockHandle &context )
{
	try
	{
		m_2RealKinect = _2RealKinect::getInstance();
		std::cout << "_2RealKinectWrapper Version: " << m_2RealKinect->getVersion() << std::endl;
		m_iNumDevices = m_2RealKinect->getNumberOfDevices();
		initDeviceList();
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		m_2RealKinect = nullptr;
		cout << e.what() << endl;
	}
}

void OpenNIDeviceManager::update()
{
	try
	{
		rescanDeviceList();
	}
	catch ( Exception &e )
	{
		cout << e.message() << endl;
		e.rethrow();
	}
}

void OpenNIDeviceManager::shutdown()
{
	Poco::Mutex::ScopedLock lock(m_Mutex);
	
	try
	{
		if(m_2RealKinect != nullptr)
		m_2RealKinect->shutdown();
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		cout << e.what() << endl;
	}
}

void OpenNIDeviceManager::initDeviceList()
{
	Poco::Mutex::ScopedLock lock(m_Mutex);
	
	m_DevicesInUse.clear();
	for(unsigned int i=0; i<m_iNumDevices; i++)
	{
		m_DevicesInUse.push_back(DeviceItem());
	}
}

void OpenNIDeviceManager::rescanDeviceList()
{
	Poco::Mutex::ScopedLock lock(m_Mutex);

	try
	{
		printf("rescanning\n");
		if(m_2RealKinect==nullptr)
			return;						// no driver found
		int numDevices = m_2RealKinect->getNumberOfDevices();
		if(numDevices != m_iNumDevices)
		{
			// reinit devices
			m_iNumDevices = numDevices;
		}
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		cout << e.what() << endl;
	}
}

bool OpenNIDeviceManager::isDeviceRunning(const unsigned int deviceIdx)
{
	Poco::Mutex::ScopedLock lock(m_Mutex);

	return true;
}

bool OpenNIDeviceManager::isDeviceAvailable(const unsigned int deviceIdx)
{
	return  (deviceIdx < m_DevicesInUse.size());
}

bool OpenNIDeviceManager::isGeneratorFree(const unsigned int deviceIdx, _2RealGenerator generatorType)
{
	if(isDeviceAvailable(deviceIdx))
		return  !m_DevicesInUse[deviceIdx].m_bGeneratorIsUsed[generatorType];
	else
	{
		return false;
	}
}

bool OpenNIDeviceManager::bindGenerator(const unsigned int deviceIdx, _2RealGenerator generatorType, int w, int h, int fps)
{
	Poco::Mutex::ScopedLock lock(m_Mutex);
	try
	{
		if(isGeneratorFree(deviceIdx, generatorType))
		{
			// setup device
			bool bResult = false;

			uint32_t resolution;
			if(generatorType == _2RealKinectWrapper::COLORIMAGE)
			{
				resolution = IMAGE_COLOR_640X480;
				if(w == 640 && h == 480)
				{
					 resolution = IMAGE_COLOR_640X480;
				}
			}
			else if(generatorType == _2RealKinectWrapper::USERIMAGE)
			{
				resolution = IMAGE_USER_DEPTH_640X480;
				if(w == 640 && h == 480)
				{
					resolution = IMAGE_USER_DEPTH_640X480;
				}
			}

			bResult = m_2RealKinect->configure( deviceIdx,  generatorType, resolution  );

			if( bResult )
			{
				std::cout << "_2RealKinectWrapper Device " << deviceIdx << " started successfully!..." << std::endl;
			}
			m_2RealKinect->startGenerator( deviceIdx, generatorType );

			return m_DevicesInUse[deviceIdx].m_bGeneratorIsUsed[generatorType] = true;
		}
		else
		{
			return false;
		}
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		cout << e.what() << endl;
	}
	catch(...)
	{
		printf("ramala");
	}
}

void OpenNIDeviceManager::unbindGenerator(const unsigned int deviceIdx, _2RealGenerator generatorType)
{
	Poco::Mutex::ScopedLock lock(m_Mutex);

	try
	{
		if(!isGeneratorFree(deviceIdx, generatorType))
		{
			// stop device
			m_2RealKinect->stopGenerator( deviceIdx, generatorType );
			m_DevicesInUse[deviceIdx].m_bGeneratorIsUsed[generatorType] = false;
		}
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		cout << e.what() << endl;
	}
}


bool OpenNIDeviceManager::setGeneratorParams(const unsigned int deviceIdx, _2RealGenerator generatorType, int w, int h, int fps)
{
	Poco::Mutex::ScopedLock lock(m_Mutex);

	if(!isGeneratorFree(deviceIdx, generatorType))
	{
		return true;
	}
	return false;
}

unsigned int OpenNIDeviceManager::getNumberOfConnectedDevices() 
{
	Poco::Mutex::ScopedLock lock(m_Mutex);
	return m_iNumDevices;
}


_2Real::ImageT<unsigned char> OpenNIDeviceManager::getImage( const unsigned int deviceIdx, _2RealKinectWrapper::_2RealGenerator generatorType )
{
	Poco::Mutex::ScopedLock lock(m_Mutex);
	try
	{
		if(!m_2RealKinect->isNewData(deviceIdx, generatorType))
			return  m_DevicesInUse[deviceIdx].m_Image;
		int imageWidth = m_2RealKinect->getImageWidth( deviceIdx, generatorType );		
		int imageHeight = m_2RealKinect->getImageHeight( deviceIdx, generatorType );
		unsigned char* pixels = m_2RealKinect->getImageData( deviceIdx, generatorType ).get();

		m_DevicesInUse[deviceIdx].m_Image = _2Real::ImageT<unsigned char>( pixels, false, imageWidth, imageHeight, _2Real::ImageChannelOrder::RGB );
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		cout << e.what() << endl;
	}

	return m_DevicesInUse[deviceIdx].m_Image;
}

int OpenNIDeviceManager::getWidth( const unsigned int deviceIdx, _2RealGenerator generatorType )
{
	try
	{
		return m_2RealKinect->getImageWidth( deviceIdx, generatorType );		
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		cout << e.what() << endl;
	}
}

int OpenNIDeviceManager::getHeight( const unsigned int deviceIdx, _2RealGenerator generatorType )
{
	try
	{
		return m_2RealKinect->getImageHeight( deviceIdx, generatorType );
	}
	catch ( _2RealKinectWrapper::_2RealException &e )
	{
		cout << e.what() << endl;
	}
}