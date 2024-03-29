ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Edevices2Esensors_h__
define __windows2Edevices2Esensors_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerReadingChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerReadingChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerReadingChangedEventArgs, "a5e83e40-b597-5b83-92f5-5bed3926ca80")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerReadingChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerShakenEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerShakenEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerShakenEventArgs, "3e5d6eaf-f169-5d60-92b0-98cd6bd8f808")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__CAccelerometer_Windows__CDevices__CSensors__CAccelerometerShakenEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__CCompass_Windows__CDevices__CSensors__CCompassReadingChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__CCompass_Windows__CDevices__CSensors__CCompassReadingChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__CCompass_Windows__CDevices__CSensors__CCompassReadingChangedEventArgs, "e787d73d-a121-5ae6-b497-ab934837e57f")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__CCompass_Windows__CDevices__CSensors__CCompassReadingChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__CGyrometer_Windows__CDevices__CSensors__CGyrometerReadingChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__CGyrometer_Windows__CDevices__CSensors__CGyrometerReadingChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__CGyrometer_Windows__CDevices__CSensors__CGyrometerReadingChangedEventArgs, "15171524-5786-59a5-af5b-a01245726c44")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__CGyrometer_Windows__CDevices__CSensors__CGyrometerReadingChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__CInclinometer_Windows__CDevices__CSensors__CInclinometerReadingChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__CInclinometer_Windows__CDevices__CSensors__CInclinometerReadingChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__CInclinometer_Windows__CDevices__CSensors__CInclinometerReadingChangedEventArgs, "6f3b411f-d147-59f1-bbe4-7bec396c7b6e")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__CInclinometer_Windows__CDevices__CSensors__CInclinometerReadingChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__CLightSensor_Windows__CDevices__CSensors__CLightSensorReadingChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__CLightSensor_Windows__CDevices__CSensors__CLightSensorReadingChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__CLightSensor_Windows__CDevices__CSensors__CLightSensorReadingChangedEventArgs, "1ecf183a-9f0a-5f73-9225-5a33eab5594f")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__CLightSensor_Windows__CDevices__CSensors__CLightSensorReadingChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__COrientationSensor_Windows__CDevices__CSensors__COrientationSensorReadingChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__COrientationSensor_Windows__CDevices__CSensors__COrientationSensorReadingChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__COrientationSensor_Windows__CDevices__CSensors__COrientationSensorReadingChangedEventArgs, "91ae0c43-e1f7-577d-a161-8aaf275eb927")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__COrientationSensor_Windows__CDevices__CSensors__COrientationSensorReadingChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CSensors__CSimpleOrientationSensor_Windows__CDevices__CSensors__CSimpleOrientationSensorOrientationChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CSensors__CSimpleOrientationSensor_Windows__CDevices__CSensors__CSimpleOrientationSensorOrientationChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CSensors__CSimpleOrientationSensor_Windows__CDevices__CSensors__CSimpleOrientationSensorOrientationChangedEventArgs, "92437fa7-ea7b-5fc5-8ecf-1b911bea2bfc")

.comdef __FITypedEventHandler_2_Windows__CDevices__CSensors__CSimpleOrientationSensor_Windows__CDevices__CSensors__CSimpleOrientationSensorOrientationChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Sensors

.enum MagnetometerAccuracy {
    MagnetometerAccuracy_Unknown	= 0,
    MagnetometerAccuracy_Unreliable	= 1,
    MagnetometerAccuracy_Approximate	= 2,
    MagnetometerAccuracy_High	= 3
    }

.enum SimpleOrientation {
    SimpleOrientation_NotRotated	= 0,
    SimpleOrientation_Rotated90DegreesCounterclockwise	= 1,
    SimpleOrientation_Rotated180DegreesCounterclockwise = 2,
    SimpleOrientation_Rotated270DegreesCounterclockwise = 3,
    SimpleOrientation_Faceup	= 4,
    SimpleOrientation_Facedown	= 5
    }

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IAccelerometerStatics <L"Windows.Devices.Sensors.IAccelerometerStatics">
DEFINE_IIDX(IAccelerometerStatics, "A5E28B74-5A87-4A2D-BECC-0F906EA061DD")

.comdef IAccelerometerStatics : public IInspectable

    GetDefault		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometer_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IAccelerometer <L"Windows.Devices.Sensors.IAccelerometer">
DEFINE_IIDX(IAccelerometer, "DF184548-2711-4DA7-8098-4B82205D3C7D")

.comdef IAccelerometer : public IInspectable

    GetCurrentReading	proc :ptr
    get_MinimumReportInterval proc :ptr
    put_ReportInterval	proc :UINT32
    get_ReportInterval	proc :ptr
    add_ReadingChanged	proc :ptr, :ptr
    remove_ReadingChanged proc :EventRegistrationToken
    add_Shaken		proc :ptr, :ptr
    remove_Shaken	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerReading_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerReading_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IAccelerometerReading <L"Windows.Devices.Sensors.IAccelerometerReading">
DEFINE_IIDX(IAccelerometerReading, "B9FE7ACB-D351-40AF-8BB6-7AA9AE641FB7")

.comdef IAccelerometerReading : public IInspectable

    get_Timestamp	proc :ptr
    get_AccelerationX	proc :ptr
    get_AccelerationY	proc :ptr
    get_AccelerationZ	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerReadingChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerReadingChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IAccelerometerReadingChangedEventArgs <L"Windows.Devices.Sensors.IAccelerometerReadingChangedEventArgs">
DEFINE_IIDX(IAccelerometerReadingChangedEventArgs, "0095C65B-B6AC-475A-9F44-8B32D35A3F25")

.comdef IAccelerometerReadingChangedEventArgs : public IInspectable

    get_Reading		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerShakenEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIAccelerometerShakenEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IAccelerometerShakenEventArgs <L"Windows.Devices.Sensors.IAccelerometerShakenEventArgs">
DEFINE_IIDX(IAccelerometerShakenEventArgs, "95FF01D1-4A28-4F35-98E8-8178AAE4084A")

.comdef IAccelerometerShakenEventArgs : public IInspectable

    get_Timestamp	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IInclinometerStatics <L"Windows.Devices.Sensors.IInclinometerStatics">
DEFINE_IIDX(IInclinometerStatics, "F22EC551-9C30-453A-8B49-3C3EEB33CB61")

.comdef IInclinometerStatics : public IInspectable

    GetDefault		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIInclinometer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIInclinometer_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IInclinometer <L"Windows.Devices.Sensors.IInclinometer">
DEFINE_IIDX(IInclinometer, "2648CA6F-2286-406F-9161-F0C4BD806EBF")

.comdef IInclinometer : public IInspectable

    GetCurrentReading	proc :ptr
    get_MinimumReportInterval proc :ptr
    put_ReportInterval	proc :UINT32
    get_ReportInterval	proc :ptr
    add_ReadingChanged	proc :ptr, :ptr
    remove_ReadingChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerReading_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerReading_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IInclinometerReading <L"Windows.Devices.Sensors.IInclinometerReading">
DEFINE_IIDX(IInclinometerReading, "9F44F055-B6F6-497F-B127-1A775E501458")

.comdef IInclinometerReading : public IInspectable

    get_Timestamp	proc :ptr
    get_PitchDegrees	proc :ptr
    get_RollDegrees	proc :ptr
    get_YawDegrees	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerReadingYawAccuracy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerReadingYawAccuracy_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IInclinometerReadingYawAccuracy <L"Windows.Devices.Sensors.IInclinometerReadingYawAccuracy">
DEFINE_IIDX(IInclinometerReadingYawAccuracy, "B453E880-1FE3-4986-A257-E6ECE2723949")

.comdef IInclinometerReadingYawAccuracy : public IInspectable

    get_YawAccuracy	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerReadingChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIInclinometerReadingChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IInclinometerReadingChangedEventArgs <L"Windows.Devices.Sensors.IInclinometerReadingChangedEventArgs">
DEFINE_IIDX(IInclinometerReadingChangedEventArgs, "4AE91DC1-E7EB-4938-8511-AE0D6B440438")

.comdef IInclinometerReadingChangedEventArgs : public IInspectable

    get_Reading		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIGyrometerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIGyrometerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IGyrometerStatics <L"Windows.Devices.Sensors.IGyrometerStatics">
DEFINE_IIDX(IGyrometerStatics, "83B6E7C9-E49D-4B39-86E6-CD554BE4C5C1")

.comdef IGyrometerStatics : public IInspectable

    GetDefault		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIGyrometer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIGyrometer_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IGyrometer <L"Windows.Devices.Sensors.IGyrometer">
DEFINE_IIDX(IGyrometer, "FDB9A9C4-84B1-4CA2-9763-9B589506C70C")

.comdef IGyrometer : public IInspectable

    GetCurrentReading	proc :ptr
    get_MinimumReportInterval proc :ptr
    put_ReportInterval	proc :UINT32
    get_ReportInterval	proc :ptr
    add_ReadingChanged	proc :ptr, :ptr
    remove_ReadingChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIGyrometerReading_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIGyrometerReading_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IGyrometerReading <L"Windows.Devices.Sensors.IGyrometerReading">
DEFINE_IIDX(IGyrometerReading, "B3D6DE5C-1EE4-456F-9DE7-E2493B5C8E03")

.comdef IGyrometerReading : public IInspectable

    get_Timestamp	proc :ptr
    get_AngularVelocityX proc :ptr
    get_AngularVelocityY proc :ptr
    get_AngularVelocityZ proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIGyrometerReadingChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIGyrometerReadingChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IGyrometerReadingChangedEventArgs <L"Windows.Devices.Sensors.IGyrometerReadingChangedEventArgs">
DEFINE_IIDX(IGyrometerReadingChangedEventArgs, "0FDF1895-6F9E-42CE-8D58-388C0AB8356D")

.comdef IGyrometerReadingChangedEventArgs : public IInspectable

    get_Reading		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CICompassStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CICompassStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ICompassStatics <L"Windows.Devices.Sensors.ICompassStatics">
DEFINE_IIDX(ICompassStatics, "9ABC97DF-56EC-4C25-B54D-40A68BB5B269")

.comdef ICompassStatics : public IInspectable

    GetDefault		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CICompass_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CICompass_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ICompass <L"Windows.Devices.Sensors.ICompass">
DEFINE_IIDX(ICompass, "292FFA94-1B45-403C-BA06-B106DBA69A64")

.comdef ICompass : public IInspectable

    GetCurrentReading	proc :ptr
    get_MinimumReportInterval proc :ptr
    put_ReportInterval	proc :UINT32
    get_ReportInterval	proc :ptr
    add_ReadingChanged	proc :ptr, :ptr
    remove_ReadingChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CICompassReading_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CICompassReading_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ICompassReading <L"Windows.Devices.Sensors.ICompassReading">
DEFINE_IIDX(ICompassReading, "82911128-513D-4DC9-B781-5EEDFBF02D0C")

.comdef ICompassReading : public IInspectable

    get_Timestamp	proc :ptr
    get_HeadingMagneticNorth proc :ptr
    get_HeadingTrueNorth proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CICompassReadingHeadingAccuracy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CICompassReadingHeadingAccuracy_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ICompassReadingHeadingAccuracy <L"Windows.Devices.Sensors.ICompassReadingHeadingAccuracy">
DEFINE_IIDX(ICompassReadingHeadingAccuracy, "E761354E-8911-40F7-9E16-6ECC7DAEC5DE")

.comdef ICompassReadingHeadingAccuracy : public IInspectable

    get_HeadingAccuracy proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CICompassReadingChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CICompassReadingChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ICompassReadingChangedEventArgs <L"Windows.Devices.Sensors.ICompassReadingChangedEventArgs">
DEFINE_IIDX(ICompassReadingChangedEventArgs, "8F1549B0-E8BC-4C7E-B009-4E41DF137072")

.comdef ICompassReadingChangedEventArgs : public IInspectable

    get_Reading		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CILightSensorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CILightSensorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ILightSensorStatics <L"Windows.Devices.Sensors.ILightSensorStatics">
DEFINE_IIDX(ILightSensorStatics, "45DB8C84-C3A8-471E-9A53-6457FAD87C0E")

.comdef ILightSensorStatics : public IInspectable

    GetDefault		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CILightSensor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CILightSensor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ILightSensor <L"Windows.Devices.Sensors.ILightSensor">
DEFINE_IIDX(ILightSensor, "F84C0718-0C54-47AE-922E-789F57FB03A0")

.comdef ILightSensor : public IInspectable

    GetCurrentReading	proc :ptr
    get_MinimumReportInterval proc :ptr
    put_ReportInterval	proc :UINT32
    get_ReportInterval	proc :ptr
    add_ReadingChanged	proc :ptr, :ptr
    remove_ReadingChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CILightSensorReading_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CILightSensorReading_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ILightSensorReading <L"Windows.Devices.Sensors.ILightSensorReading">
DEFINE_IIDX(ILightSensorReading, "FFDF6300-227C-4D2B-B302-FC0142485C68")

.comdef ILightSensorReading : public IInspectable

    get_Timestamp	proc :ptr
    get_IlluminanceInLux proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CILightSensorReadingChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CILightSensorReadingChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ILightSensorReadingChangedEventArgs <L"Windows.Devices.Sensors.ILightSensorReadingChangedEventArgs">
DEFINE_IIDX(ILightSensorReadingChangedEventArgs, "A3A2F4CF-258B-420C-B8AB-8EDD601ECF50")

.comdef ILightSensorReadingChangedEventArgs : public IInspectable

    get_Reading		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CISensorRotationMatrix_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CISensorRotationMatrix_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ISensorRotationMatrix <L"Windows.Devices.Sensors.ISensorRotationMatrix">
DEFINE_IIDX(ISensorRotationMatrix, "0A3D5A67-22F4-4392-9538-65D0BD064AA6")

.comdef ISensorRotationMatrix : public IInspectable

    get_M11		proc :ptr
    get_M12		proc :ptr
    get_M13		proc :ptr
    get_M21		proc :ptr
    get_M22		proc :ptr
    get_M23		proc :ptr
    get_M31		proc :ptr
    get_M32		proc :ptr
    get_M33		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CISensorQuaternion_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CISensorQuaternion_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ISensorQuaternion <L"Windows.Devices.Sensors.ISensorQuaternion">
DEFINE_IIDX(ISensorQuaternion, "C9C5C827-C71C-46E7-9DA3-36A193B232BC")

.comdef ISensorQuaternion : public IInspectable

    get_W		proc :ptr
    get_X		proc :ptr
    get_Y		proc :ptr
    get_Z		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IOrientationSensorStatics <L"Windows.Devices.Sensors.IOrientationSensorStatics">
DEFINE_IIDX(IOrientationSensorStatics, "10EF8712-FB4C-428A-898B-2765E409E669")

.comdef IOrientationSensorStatics : public IInspectable

    GetDefault		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IOrientationSensor <L"Windows.Devices.Sensors.IOrientationSensor">
DEFINE_IIDX(IOrientationSensor, "5E354635-CF6B-4C63-ABD8-10252B0BF6EC")

.comdef IOrientationSensor : public IInspectable

    GetCurrentReading	proc :ptr
    get_MinimumReportInterval proc :ptr
    put_ReportInterval	proc :UINT32
    get_ReportInterval	proc :ptr
    add_ReadingChanged	proc :ptr, :ptr
    remove_ReadingChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorReading_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorReading_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IOrientationSensorReading <L"Windows.Devices.Sensors.IOrientationSensorReading">
DEFINE_IIDX(IOrientationSensorReading, "4756C993-6595-4897-BCC6-D537EE757564")

.comdef IOrientationSensorReading : public IInspectable

    get_Timestamp	proc :ptr
    get_RotationMatrix	proc :ptr
    get_Quaternion	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorReadingYawAccuracy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorReadingYawAccuracy_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IOrientationSensorReadingYawAccuracy <L"Windows.Devices.Sensors.IOrientationSensorReadingYawAccuracy">
DEFINE_IIDX(IOrientationSensorReadingYawAccuracy, "D1AC9824-3F5A-49A2-BC7B-1180BC38CD2B")

.comdef IOrientationSensorReadingYawAccuracy : public IInspectable

    get_YawAccuracy	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorReadingChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CIOrientationSensorReadingChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_IOrientationSensorReadingChangedEventArgs <L"Windows.Devices.Sensors.IOrientationSensorReadingChangedEventArgs">
DEFINE_IIDX(IOrientationSensorReadingChangedEventArgs, "012C1186-C3BA-46BC-AE65-7A98996CBFB8")

.comdef IOrientationSensorReadingChangedEventArgs : public IInspectable

    get_Reading		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CISimpleOrientationSensorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CISimpleOrientationSensorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ISimpleOrientationSensorStatics <L"Windows.Devices.Sensors.ISimpleOrientationSensorStatics">
DEFINE_IIDX(ISimpleOrientationSensorStatics, "72ED066F-70AA-40C6-9B1B-3433F7459B4E")

.comdef ISimpleOrientationSensorStatics : public IInspectable

    GetDefault		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CISimpleOrientationSensor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CISimpleOrientationSensor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ISimpleOrientationSensor <L"Windows.Devices.Sensors.ISimpleOrientationSensor">
DEFINE_IIDX(ISimpleOrientationSensor, "5FF53856-214A-4DEE-A3F9-616F1AB06FFD")

.comdef ISimpleOrientationSensor : public IInspectable

    GetCurrentOrientation proc :ptr
    add_OrientationChanged proc :ptr, :ptr
    remove_OrientationChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CSensors_CISimpleOrientationSensorOrientationChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CSensors_CISimpleOrientationSensorOrientationChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Sensors_ISimpleOrientationSensorOrientationChangedEventArgs <L"Windows.Devices.Sensors.ISimpleOrientationSensorOrientationChangedEventArgs">
DEFINE_IIDX(ISimpleOrientationSensorOrientationChangedEventArgs, "BCD5C660-23D4-4B4C-A22E-BA81ADE0C601")

.comdef ISimpleOrientationSensorOrientationChangedEventArgs : public IInspectable

    get_Timestamp	proc :ptr
    get_Orientation	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Sensors_Accelerometer_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_Accelerometer_DEFINED
define RuntimeClass_Windows_Devices_Sensors_Accelerometer <L"Windows.Devices.Sensors.Accelerometer">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_AccelerometerReading_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_AccelerometerReading_DEFINED
define RuntimeClass_Windows_Devices_Sensors_AccelerometerReading <L"Windows.Devices.Sensors.AccelerometerReading">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_AccelerometerReadingChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_AccelerometerReadingChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_AccelerometerReadingChangedEventArgs <L"Windows.Devices.Sensors.AccelerometerReadingChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_AccelerometerShakenEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_AccelerometerShakenEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_AccelerometerShakenEventArgs <L"Windows.Devices.Sensors.AccelerometerShakenEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_Inclinometer_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_Inclinometer_DEFINED
define RuntimeClass_Windows_Devices_Sensors_Inclinometer <L"Windows.Devices.Sensors.Inclinometer">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_InclinometerReading_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_InclinometerReading_DEFINED
define RuntimeClass_Windows_Devices_Sensors_InclinometerReading <L"Windows.Devices.Sensors.InclinometerReading">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_InclinometerReadingChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_InclinometerReadingChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_InclinometerReadingChangedEventArgs <L"Windows.Devices.Sensors.InclinometerReadingChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_Gyrometer_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_Gyrometer_DEFINED
define RuntimeClass_Windows_Devices_Sensors_Gyrometer <L"Windows.Devices.Sensors.Gyrometer">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_GyrometerReading_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_GyrometerReading_DEFINED
define RuntimeClass_Windows_Devices_Sensors_GyrometerReading <L"Windows.Devices.Sensors.GyrometerReading">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_GyrometerReadingChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_GyrometerReadingChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_GyrometerReadingChangedEventArgs <L"Windows.Devices.Sensors.GyrometerReadingChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_Compass_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_Compass_DEFINED
define RuntimeClass_Windows_Devices_Sensors_Compass <L"Windows.Devices.Sensors.Compass">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_CompassReading_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_CompassReading_DEFINED
define RuntimeClass_Windows_Devices_Sensors_CompassReading <L"Windows.Devices.Sensors.CompassReading">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_CompassReadingChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_CompassReadingChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_CompassReadingChangedEventArgs <L"Windows.Devices.Sensors.CompassReadingChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_LightSensor_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_LightSensor_DEFINED
define RuntimeClass_Windows_Devices_Sensors_LightSensor <L"Windows.Devices.Sensors.LightSensor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_LightSensorReading_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_LightSensorReading_DEFINED
define RuntimeClass_Windows_Devices_Sensors_LightSensorReading <L"Windows.Devices.Sensors.LightSensorReading">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_LightSensorReadingChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_LightSensorReadingChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_LightSensorReadingChangedEventArgs <L"Windows.Devices.Sensors.LightSensorReadingChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_SensorRotationMatrix_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_SensorRotationMatrix_DEFINED
define RuntimeClass_Windows_Devices_Sensors_SensorRotationMatrix <L"Windows.Devices.Sensors.SensorRotationMatrix">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_SensorQuaternion_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_SensorQuaternion_DEFINED
define RuntimeClass_Windows_Devices_Sensors_SensorQuaternion <L"Windows.Devices.Sensors.SensorQuaternion">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_OrientationSensor_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_OrientationSensor_DEFINED
define RuntimeClass_Windows_Devices_Sensors_OrientationSensor <L"Windows.Devices.Sensors.OrientationSensor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_OrientationSensorReading_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_OrientationSensorReading_DEFINED
define RuntimeClass_Windows_Devices_Sensors_OrientationSensorReading <L"Windows.Devices.Sensors.OrientationSensorReading">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_OrientationSensorReadingChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_OrientationSensorReadingChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_OrientationSensorReadingChangedEventArgs <L"Windows.Devices.Sensors.OrientationSensorReadingChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_SimpleOrientationSensor_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_SimpleOrientationSensor_DEFINED
define RuntimeClass_Windows_Devices_Sensors_SimpleOrientationSensor <L"Windows.Devices.Sensors.SimpleOrientationSensor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Sensors_SimpleOrientationSensorOrientationChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Sensors_SimpleOrientationSensorOrientationChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Sensors_SimpleOrientationSensorOrientationChangedEventArgs <L"Windows.Devices.Sensors.SimpleOrientationSensorOrientationChangedEventArgs">
endif

endif
