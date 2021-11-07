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

ifndef __windows2Edevices2Egeolocation2Egeofencing_h__
define __windows2Edevices2Egeolocation2Egeofencing_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Devices.Geolocation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence, "e7a9e144-202d-5708-a9bd-e3dc0e14df46")

.comdef __FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence, "ce697733-595c-51c0-ad5f-324af5cdf2dd")

.comdef __FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport, "eaff2de4-6650-544a-b7ac-6d5b819d4698")

.comdef __FIIterator_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport, "76f50b4e-7aa7-565b-aada-b0c1cc144ed0")

.comdef __FIIterable_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence, "d8039aca-1a45-5d13-8cfd-4900c22b8ef1")

.comdef __FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport, "ea91593d-ecf4-5041-86f2-837a282c4d94")

.comdef __FIVectorView_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceStateChangeReport : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence, "096dc936-5f66-5c6e-95ce-ef5541fbf4c4")

.comdef __FIVector_1_Windows__CDevices__CGeolocation__CGeofencing__CGeofence : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceMonitor_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceMonitor_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceMonitor_IInspectable, "ecc5af2c-e47a-59ce-86be-9c3066fe26f7")

.comdef __FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeofencing__CGeofenceMonitor_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Geolocation
.namespace Geofencing


.enum MonitoredGeofenceStates {
    MonitoredGeofenceStates_None	= 0,
    MonitoredGeofenceStates_Entered	= 0x1,
    MonitoredGeofenceStates_Exited	= 0x2,
    MonitoredGeofenceStates_Removed	= 0x4
    }

.enum GeofenceState {
    GeofenceState_None	= 0,
    GeofenceState_Entered	= 0x1,
    GeofenceState_Exited	= 0x2,
    GeofenceState_Removed	= 0x4
    }

.enum GeofenceMonitorStatus {
    GeofenceMonitorStatus_Ready = 0,
    GeofenceMonitorStatus_Initializing	= 1,
    GeofenceMonitorStatus_NoData	= 2,
    GeofenceMonitorStatus_Disabled	= 3,
    GeofenceMonitorStatus_NotInitialized	= 4,
    GeofenceMonitorStatus_NotAvailable	= 5
    }

.enum GeofenceRemovalReason {
    GeofenceRemovalReason_Used	= 0,
    GeofenceRemovalReason_Expired	= 1
    }


ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_Geofencing_IGeofenceFactory <L"Windows.Devices.Geolocation.Geofencing.IGeofenceFactory">
DEFINE_IIDX(IGeofenceFactory, "841F624B-325F-4B90-BCA7-2B8022A93796")

.comdef IGeofenceFactory : public IInspectable

    Create		proc :HSTRING, :ptr, :ptr
    CreateWithMonitorStates proc :HSTRING, :ptr, :Windows::Devices::Geolocation::Geofencing::MonitoredGeofenceStates, :boolean, :ptr
    CreateWithMonitorStatesAndDwellTime proc :HSTRING, :ptr, :Windows::Devices::Geolocation::Geofencing::MonitoredGeofenceStates, :boolean, :Windows::Foundation::TimeSpan, :ptr
    CreateWithMonitorStatesDwellTimeStartTimeAndDuration proc :HSTRING, :ptr, :Windows::Devices::Geolocation::Geofencing::MonitoredGeofenceStates, :boolean, :Windows::Foundation::TimeSpan, :Windows::Foundation::DateTime, :Windows::Foundation::TimeSpan, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofence_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofence_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_Geofencing_IGeofence <L"Windows.Devices.Geolocation.Geofencing.IGeofence">
DEFINE_IIDX(IGeofence, "9C090823-EDB8-47E0-8245-5BF61D321F2D")

.comdef IGeofence : public IInspectable

    get_StartTime	proc :ptr
    get_Duration	proc :ptr
    get_DwellTime	proc :ptr
    get_Id		proc :ptr
    get_MonitoredStates proc :ptr
    get_Geoshape	proc :ptr
    get_SingleUse	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceStateChangeReport_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceStateChangeReport_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_Geofencing_IGeofenceStateChangeReport <L"Windows.Devices.Geolocation.Geofencing.IGeofenceStateChangeReport">
DEFINE_IIDX(IGeofenceStateChangeReport, "9A243C18-2464-4C89-BE05-B3FFFF5BABC5")

.comdef IGeofenceStateChangeReport : public IInspectable

    get_NewState	proc :ptr
    get_Geofence	proc :ptr
    get_Geoposition	proc :ptr
    get_RemovalReason	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceMonitorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceMonitorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_Geofencing_IGeofenceMonitorStatics <L"Windows.Devices.Geolocation.Geofencing.IGeofenceMonitorStatics">
DEFINE_IIDX(IGeofenceMonitorStatics, "2DD32FCF-7E75-4899-ACE3-2BD0A65CCE06")

.comdef IGeofenceMonitorStatics : public IInspectable

    get_Current		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceMonitor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CGeofencing_CIGeofenceMonitor_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_Geofencing_IGeofenceMonitor <L"Windows.Devices.Geolocation.Geofencing.IGeofenceMonitor">
DEFINE_IIDX(IGeofenceMonitor, "4C0F5F78-1C1F-4621-BBBD-833B92247226")

.comdef IGeofenceMonitor : public IInspectable

    get_Status		proc :ptr
    get_Geofences	proc :ptr
    get_LastKnownGeoposition proc :ptr
    add_GeofenceStateChanged proc :ptr, :ptr
    remove_GeofenceStateChanged proc :EventRegistrationToken
    ReadReports		proc :ptr
    add_StatusChanged	proc :ptr, :ptr
    remove_StatusChanged proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geofencing_Geofence_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geofencing_Geofence_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geofencing_Geofence <L"Windows.Devices.Geolocation.Geofencing.Geofence">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geofencing_GeofenceMonitor_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geofencing_GeofenceMonitor_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geofencing_GeofenceMonitor <L"Windows.Devices.Geolocation.Geofencing.GeofenceMonitor">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geofencing_GeofenceStateChangeReport_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geofencing_GeofenceStateChangeReport_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geofencing_GeofenceStateChangeReport <L"Windows.Devices.Geolocation.Geofencing.GeofenceStateChangeReport">
endif

endif
