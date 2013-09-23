#pragma once

#include "ofConstants.h"
#include "ofColor.h"

#if (_MSC_VER) || _LIBCPP_VERSION
// no tr1 in c++11
#	include <memory>
#	if _LIBCPP_VERSION
namespace std {
	// this is a temporary fix while ofPtr is not deprecated.
	struct __dynamic_cast_tag { };
}
#	endif
#else
// import tr1
// import smart pointers utils into std
#	include <tr1/memory>
namespace std {
#	if __cplusplus<201103L
	using std::tr1::shared_ptr;
	using std::tr1::weak_ptr;
	using std::tr1::enable_shared_from_this;
#	endif
	using std::tr1::static_pointer_cast;
	using std::tr1::dynamic_pointer_cast;
	using std::tr1::const_pointer_cast;
	using std::tr1::__dynamic_cast_tag;
}
#endif





//----------------------------------------------------------
// ofDeviceInfo
//----------------------------------------------------------
class ofSerial;
class ofSerialDeviceInfo{
	friend class ofSerial;

	public:

		ofSerialDeviceInfo(string devicePathIn, string deviceNameIn, int deviceIDIn){
			devicePath			= devicePathIn;
			deviceName			= deviceNameIn;
			deviceID			= deviceIDIn;
		}

		ofSerialDeviceInfo(){
			deviceName = "device undefined";
			deviceID   = -1;
		}

		string getDevicePath(){
			return devicePath;
		}

		string getDeviceName(){
			return deviceName;
		}

		int getDeviceID(){
			return deviceID;
		}

	protected:
		string devicePath;			//eg: /dev/tty.cu/usbdevice-a440
		string deviceName;			//eg: usbdevice-a440 / COM4
		int deviceID;				//eg: 0,1,2,3 etc

		//TODO: other stuff for serial ?
};


//----------------------------------------------------------
// ofMutex
//----------------------------------------------------------

#include "Poco/Mutex.h"
typedef Poco::FastMutex ofMutex;
typedef Poco::FastMutex::ScopedLock ofScopedLock;

//----------------------------------------------------------
// ofStyle
//----------------------------------------------------------

class ofStyle{
	public:
		ofStyle(){
			bFill				= true;
			blendingMode		= OF_BLENDMODE_DISABLED;
			smoothing			= false;
			circleResolution	= 20;
			sphereResolution	= 20;
			curveResolution		= 20;
			lineWidth			= 1.0;
			polyMode			= OF_POLY_WINDING_ODD;
			rectMode			= OF_RECTMODE_CORNER;
			#ifdef TARGET_OPENGLES
				drawBitmapMode		= OF_BITMAPMODE_SIMPLE;
			#else
				drawBitmapMode		= OF_BITMAPMODE_MODEL_BILLBOARD;
			#endif
			bgColor.set(200,200,200);
			//depthTest = false;
		}

		virtual ~ofStyle(){}

		ofColor color;
		ofColor bgColor;
		ofPolyWindingMode polyMode;
		ofRectMode rectMode;
		bool bFill;
		ofDrawBitmapMode drawBitmapMode;

		ofBlendMode blendingMode;

		bool smoothing;
		int circleResolution;
		int sphereResolution;
		int curveResolution;
		float lineWidth;
		//bool depthTest; removed since it'll break old projects setting depth test through glEnable
};

class ofVideoFormat{
public:
	  ofPixelFormat pixelFormat;
	  int    width;
	  int    height;
	  vector<float> framerates;
};

class ofVideoDevice{
public:
	  int id;
	  string deviceName;
	  string hardwareName;
	  vector<ofVideoFormat> formats;
      bool bAvailable;
};

//----------------------------------------------------------
// ofPtr
//----------------------------------------------------------
template <typename T>
class ofPtr: public std::shared_ptr<T>
{

public:

	ofPtr()
	  : std::shared_ptr<T>() { }

	  template<typename Tp1>
		explicit
		ofPtr(Tp1* __p)
	: std::shared_ptr<T>(__p) { }

	  template<typename Tp1, typename _Deleter>
		ofPtr(Tp1* __p, _Deleter __d)
	: std::shared_ptr<T>(__p, __d) { }

	  template<typename Tp1, typename _Deleter, typename _Alloc>
		ofPtr(Tp1* __p, _Deleter __d, const _Alloc& __a)
	: std::shared_ptr<T>(__p, __d, __a) { }

	  // Aliasing constructor
	  template<typename Tp1>
		ofPtr(const ofPtr<Tp1>& __r, T* __p)
	: std::shared_ptr<T>(__r, __p) { }

	  template<typename Tp1>
		ofPtr(const ofPtr<Tp1>& __r)
	: std::shared_ptr<T>(__r) { }

	  template<typename Tp1>
		ofPtr(const std::shared_ptr<Tp1>& __r)
	: std::shared_ptr<T>(__r) { }

	  template<typename Tp1>
		explicit
		ofPtr(const std::weak_ptr<Tp1>& __r)
	: std::shared_ptr<T>(__r) { }

#if (_MSC_VER)
	template<typename Tp1>
	ofPtr(const ofPtr<Tp1>& __r, std::_Dynamic_tag)
	: std::shared_ptr<T>(__r, std:::_Dynamic_tag()) { }
#else
	template<typename Tp1>
	ofPtr(const ofPtr<Tp1>& __r, std::__dynamic_cast_tag)
	: std::shared_ptr<T>(__r, std::__dynamic_cast_tag()) { }
#endif
};

#if (_MSC_VER)
template<typename _Tp, typename _Tp1>
ofPtr<_Tp>
	dynamic_pointer_cast(const ofPtr<_Tp1>& __r)
{ return ofPtr<_Tp>(__r, std::_Dynamic_tag()); }
#else
template<typename _Tp, typename _Tp1>
ofPtr<_Tp>
	dynamic_pointer_cast(const ofPtr<_Tp1>& __r)
{ return ofPtr<_Tp>(__r, std::__dynamic_cast_tag()); }
#endif
