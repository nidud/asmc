ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Edevices2Egeolocation_h__
define __windows2Edevices2Egeolocation_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CGeolocation__CGeoposition_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CDevices__CGeolocation__CGeoposition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CDevices__CGeolocation__CGeoposition, "7668a704-244e-5e12-8dcb-92a3299eba26")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CDevices__CGeolocation__CGeoposition : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CDevices__CGeolocation__CGeoposition_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CDevices__CGeolocation__CGeoposition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CDevices__CGeolocation__CGeoposition, "ee73ecf0-099d-57e5-8407-5b32e5af1cc4")

.comdef __FIAsyncOperation_1_Windows__CDevices__CGeolocation__CGeoposition : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CPositionChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CPositionChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CPositionChangedEventArgs, "df3c6164-4e7b-5e8e-9a7e-13da059dec1e")

.comdef __FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CPositionChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CStatusChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CStatusChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CStatusChangedEventArgs, "97fcf582-de6b-5cd3-9690-e2ecbb66da4d")

.comdef __FITypedEventHandler_2_Windows__CDevices__CGeolocation__CGeolocator_Windows__CDevices__CGeolocation__CStatusChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Devices
.namespace Geolocation

.enum PositionAccuracy {
    PositionAccuracy_Default	= 0,
    PositionAccuracy_High	= 1
    }

.enum PositionStatus {
    PositionStatus_Ready	= 0,
    PositionStatus_Initializing = 1,
    PositionStatus_NoData	= 2,
    PositionStatus_Disabled	= 3,
    PositionStatus_NotInitialized	= 4,
    PositionStatus_NotAvailable = 5
    }

.enum PositionSource {
    PositionSource_Cellular	= 0,
    PositionSource_Satellite	= 1,
    PositionSource_WiFi = 2,
    PositionSource_IPAddress	= 3,
    PositionSource_Unknown	= 4
    }

.enum GeoshapeType {
    GeoshapeType_Geopoint	= 0,
    GeoshapeType_Geocircle	= 1
    }

.enum AltitudeReferenceSystem {
    AltitudeReferenceSystem_Unspecified = 0,
    AltitudeReferenceSystem_Terrain	= 1,
    AltitudeReferenceSystem_Ellipsoid	= 2,
    AltitudeReferenceSystem_Geoid	= 3,
    AltitudeReferenceSystem_Surface	= 4
    }

.template BasicGeoposition
    Latitude	DOUBLE ?
    Longitude	DOUBLE ?
    Altitude	DOUBLE ?
   .ends


ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeoshape_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeoshape_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeoshape <L"Windows.Devices.Geolocation.IGeoshape">
DEFINE_IIDX(IGeoshape, "C99CA2AF-C729-43C1-8FAB-D6DEC914DF7E")

.comdef IGeoshape : public IInspectable

    get_GeoshapeType	proc :ptr
    get_SpatialReferenceId proc :ptr
    get_AltitudeReferenceSystem proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeopoint_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeopoint_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeopoint <L"Windows.Devices.Geolocation.IGeopoint">
DEFINE_IIDX(IGeopoint, "6BFA00EB-E56E-49BB-9CAF-CBAA78A8BCEF")

.comdef IGeopoint : public IInspectable

    get_Position	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeopointFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeopointFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeopointFactory <L"Windows.Devices.Geolocation.IGeopointFactory">
DEFINE_IIDX(IGeopointFactory, "DB6B8D33-76BD-4E30-8AF7-A844DC37B7A0")

.comdef IGeopointFactory : public IInspectable

    Create		proc :Windows::Devices::Geolocation::BasicGeoposition, :ptr
    CreateWithAltitudeReferenceSystem proc :Windows::Devices::Geolocation::BasicGeoposition, :Windows::Devices::Geolocation::AltitudeReferenceSystem, :ptr
    CreateWithAltitudeReferenceSystemAndSpatialReferenceId proc :Windows::Devices::Geolocation::BasicGeoposition, :Windows::Devices::Geolocation::AltitudeReferenceSystem, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinateSatelliteData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinateSatelliteData_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeocoordinateSatelliteData <L"Windows.Devices.Geolocation.IGeocoordinateSatelliteData">
DEFINE_IIDX(IGeocoordinateSatelliteData, "C32A74D9-2608-474C-912C-06DD490F4AF7")

.comdef IGeocoordinateSatelliteData : public IInspectable

    get_PositionDilutionOfPrecision proc :ptr
    get_HorizontalDilutionOfPrecision proc :ptr
    get_VerticalDilutionOfPrecision proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinate_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeocoordinate <L"Windows.Devices.Geolocation.IGeocoordinate">
DEFINE_IIDX(IGeocoordinate, "EE21A3AA-976A-4C70-803D-083EA55BCBC4")

.comdef IGeocoordinate : public IInspectable

    get_Latitude	proc :ptr
    get_Longitude	proc :ptr
    get_Altitude	proc :ptr
    get_Accuracy	proc :ptr
    get_AltitudeAccuracy proc :ptr
    get_Heading		proc :ptr
    get_Speed		proc :ptr
    get_Timestamp	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinateWithPositionData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinateWithPositionData_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeocoordinateWithPositionData <L"Windows.Devices.Geolocation.IGeocoordinateWithPositionData">
DEFINE_IIDX(IGeocoordinateWithPositionData, "95E634BE-DBD6-40AC-B8F2-A65C0340D9A6")

.comdef IGeocoordinateWithPositionData : public IInspectable

    get_PositionSource	proc :ptr
    get_SatelliteData	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinateWithPoint_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocoordinateWithPoint_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeocoordinateWithPoint <L"Windows.Devices.Geolocation.IGeocoordinateWithPoint">
DEFINE_IIDX(IGeocoordinateWithPoint, "FEEA0525-D22C-4D46-B527-0B96066FC7DB")

.comdef IGeocoordinateWithPoint : public IInspectable

    get_Point		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CICivicAddress_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CICivicAddress_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_ICivicAddress <L"Windows.Devices.Geolocation.ICivicAddress">
DEFINE_IIDX(ICivicAddress, "A8567A1A-64F4-4D48-BCEA-F6B008ECA34C")

.comdef ICivicAddress : public IInspectable

    get_Country		proc :ptr
    get_State		proc :ptr
    get_City		proc :ptr
    get_PostalCode	proc :ptr
    get_Timestamp	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeoposition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeoposition_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeoposition <L"Windows.Devices.Geolocation.IGeoposition">
DEFINE_IIDX(IGeoposition, "C18D0454-7D41-4FF7-A957-9DFFB4EF7F5B")

.comdef IGeoposition : public IInspectable

    get_Coordinate	proc :ptr
    get_CivicAddress	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIPositionChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIPositionChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IPositionChangedEventArgs <L"Windows.Devices.Geolocation.IPositionChangedEventArgs">
DEFINE_IIDX(IPositionChangedEventArgs, "37859CE5-9D1E-46C5-BF3B-6AD8CAC1A093")

.comdef IPositionChangedEventArgs : public IInspectable

    get_Position	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIStatusChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIStatusChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IStatusChangedEventArgs <L"Windows.Devices.Geolocation.IStatusChangedEventArgs">
DEFINE_IIDX(IStatusChangedEventArgs, "3453D2DA-8C93-4111-A205-9AECFC9BE5C0")

.comdef IStatusChangedEventArgs : public IInspectable

    get_Status		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeolocator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeolocator_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeolocator <L"Windows.Devices.Geolocation.IGeolocator">
DEFINE_IIDX(IGeolocator, "A9C3BF62-4524-4989-8AA9-DE019D2E551F")

.comdef IGeolocator : public IInspectable

    get_DesiredAccuracy proc :ptr
    put_DesiredAccuracy proc :Windows::Devices::Geolocation::PositionAccuracy
    get_MovementThreshold proc :ptr
    put_MovementThreshold proc :DOUBLE
    get_ReportInterval	proc :ptr
    put_ReportInterval	proc :UINT32
    get_LocationStatus	proc :ptr
    GetGeopositionAsync proc :ptr
    GetGeopositionAsyncWithAgeAndTimeout proc :Windows::Foundation::TimeSpan, :Windows::Foundation::TimeSpan, :ptr
    add_PositionChanged proc :ptr, :ptr
    remove_PositionChanged proc :EventRegistrationToken
    add_StatusChanged	proc :ptr, :ptr
    remove_StatusChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeolocatorWithScalarAccuracy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeolocatorWithScalarAccuracy_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeolocatorWithScalarAccuracy <L"Windows.Devices.Geolocation.IGeolocatorWithScalarAccuracy">
DEFINE_IIDX(IGeolocatorWithScalarAccuracy, "96F5D3C1-B80F-460A-994D-A96C47A51AA4")

.comdef IGeolocatorWithScalarAccuracy : public IInspectable

    get_DesiredAccuracyInMeters proc :ptr
    put_DesiredAccuracyInMeters proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocircle_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocircle_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeocircle <L"Windows.Devices.Geolocation.IGeocircle">
DEFINE_IIDX(IGeocircle, "39E45843-A7F9-4E63-92A7-BA0C28D124B1")

.comdef IGeocircle : public IInspectable

    get_Center		proc :ptr
    get_Radius		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocircleFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CDevices_CGeolocation_CIGeocircleFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Devices_Geolocation_IGeocircleFactory <L"Windows.Devices.Geolocation.IGeocircleFactory">
DEFINE_IIDX(IGeocircleFactory, "AFD6531F-72B1-4F7D-87CC-4ED4C9849C05")

.comdef IGeocircleFactory : public IInspectable

    Create		proc :Windows::Devices::Geolocation::BasicGeoposition, :DOUBLE, :ptr
    CreateWithAltitudeReferenceSystem proc :Windows::Devices::Geolocation::BasicGeoposition, :DOUBLE, :Windows::Devices::Geolocation::AltitudeReferenceSystem, :ptr
    CreateWithAltitudeReferenceSystemAndSpatialReferenceId proc :Windows::Devices::Geolocation::BasicGeoposition, :DOUBLE, :Windows::Devices::Geolocation::AltitudeReferenceSystem, :UINT32, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geopoint_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geopoint_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geopoint <L"Windows.Devices.Geolocation.Geopoint">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_GeocoordinateSatelliteData_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_GeocoordinateSatelliteData_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_GeocoordinateSatelliteData <L"Windows.Devices.Geolocation.GeocoordinateSatelliteData">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geocoordinate_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geocoordinate_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geocoordinate <L"Windows.Devices.Geolocation.Geocoordinate">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_CivicAddress_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_CivicAddress_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_CivicAddress <L"Windows.Devices.Geolocation.CivicAddress">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geoposition_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geoposition_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geoposition <L"Windows.Devices.Geolocation.Geoposition">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_PositionChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_PositionChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_PositionChangedEventArgs <L"Windows.Devices.Geolocation.PositionChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_StatusChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_StatusChangedEventArgs_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_StatusChangedEventArgs <L"Windows.Devices.Geolocation.StatusChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geolocator_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geolocator_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geolocator <L"Windows.Devices.Geolocation.Geolocator">
endif
ifndef RUNTIMECLASS_Windows_Devices_Geolocation_Geocircle_DEFINED
define RUNTIMECLASS_Windows_Devices_Geolocation_Geocircle_DEFINED
define RuntimeClass_Windows_Devices_Geolocation_Geocircle <L"Windows.Devices.Geolocation.Geocircle">
endif

endif
