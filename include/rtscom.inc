ifndef _RPC500_
include rpc500.inc
endif
ifndef __rtscom_h__
define __rtscom_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include tpcshrd.inc
include msinkaut.inc
include manipulations.inc

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum RealTimeStylusDataInterest {
	RTSDI_AllData			= 0xffffffff,
	RTSDI_None			= 0,
	RTSDI_Error			= 0x1,
	RTSDI_RealTimeStylusEnabled	= 0x2,
	RTSDI_RealTimeStylusDisabled	= 0x4,
	RTSDI_StylusNew			= 0x8,
	RTSDI_StylusInRange		= 0x10,
	RTSDI_InAirPackets		= 0x20,
	RTSDI_StylusOutOfRange		= 0x40,
	RTSDI_StylusDown		= 0x80,
	RTSDI_Packets			= 0x100,
	RTSDI_StylusUp			= 0x200,
	RTSDI_StylusButtonUp		= 0x400,
	RTSDI_StylusButtonDown		= 0x800,
	RTSDI_SystemEvents		= 0x1000,
	RTSDI_TabletAdded		= 0x2000,
	RTSDI_TabletRemoved		= 0x4000,
	RTSDI_CustomStylusDataAdded	= 0x8000,
	RTSDI_UpdateMapping		= 0x10000,
	RTSDI_DefaultEvents		= ( ( ( ( ( ( RTSDI_RealTimeStylusEnabled or RTSDI_RealTimeStylusDisabled ) or RTSDI_StylusDown ) or RTSDI_Packets ) or RTSDI_StylusUp ) or RTSDI_SystemEvents ) or RTSDI_CustomStylusDataAdded )
	}

STYLUS_ID		typedef CURSOR_ID

StylusInfo		struct
tcid			TABLET_CONTEXT_ID ?
cid			STYLUS_ID ?
bIsInvertedCursor	BOOL ?
StylusInfo		ends

.enum StylusQueue {
	SyncStylusQueue			= 0x1,
	AsyncStylusQueueImmediate	= 0x2,
	AsyncStylusQueue		= 0x3
	}

.enum RealTimeStylusLockType {
	RTSLT_ObjLock		= 0x1,
	RTSLT_SyncEventLock	= 0x2,
	RTSLT_AsyncEventLock	= 0x4,
	RTSLT_ExcludeCallback	= 0x8,
	RTSLT_SyncObjLock	= 0xb,
	RTSLT_AsyncObjLock	= 0xd
	}

GESTURE_DATA		struct
gestureId		sdword ?
recoConfidence		sdword ?
strokeCount		sdword ?
GESTURE_DATA		ends

DYNAMIC_RENDERER_CACHED_DATA struct
strokeId		LONG ?
dynamicRenderer		ptr IDynamicRenderer ?
DYNAMIC_RENDERER_CACHED_DATA ends

ifndef __TPCRTSLib_LIBRARY_DEFINED__
define __TPCRTSLib_LIBRARY_DEFINED__

externdef LIBID_TPCRTSLib:IID

ifndef __IRealTimeStylus_INTERFACE_DEFINED__
define __IRealTimeStylus_INTERFACE_DEFINED__

DEFINE_IIDX(IRealTimeStylus, "A8BB5D22-3144-4a7b-93CD-F34A16BE513A")

.comdef IRealTimeStylus : public IUnknown
    get_Enabled		proc :ptr
    put_Enabled		proc :BOOL
    get_HWND		proc :ptr
    put_HWND		proc :HANDLE_PTR
    get_WindowInputRectangle proc :ptr
    put_WindowInputRectangle proc :ptr
    AddStylusSyncPlugin proc :ULONG, :ptr
    RemoveStylusSyncPlugin proc :ULONG, :ptr ptr
    RemoveAllStylusSyncPlugins proc
    GetStylusSyncPlugin proc :ULONG, :ptr ptr
    GetStylusSyncPluginCount proc :ptr
    AddStylusAsyncPlugin proc :ULONG, :ptr
    RemoveStylusAsyncPlugin proc :ULONG, :ptr ptr
    RemoveAllStylusAsyncPlugins proc
    GetStylusAsyncPlugin proc :ULONG, :ptr ptr
    GetStylusAsyncPluginCount proc :ptr
    get_ChildRealTimeStylusPlugin proc :ptr ptr
    putref_ChildRealTimeStylusPlugin proc :ptr
    AddCustomStylusDataToQueue proc :StylusQueue, :ptr, :ULONG, :ptr
    ClearStylusQueues	proc
    SetAllTabletsMode	proc :BOOL
    SetSingleTabletMode proc :ptr
    GetTablet		proc :ptr ptr
    GetTabletContextIdFromTablet proc :ptr, :ptr
    GetTabletFromTabletContextId proc :TABLET_CONTEXT_ID, :ptr ptr
    GetAllTabletContextIds proc :ptr, :ptr ptr
    GetStyluses		proc :ptr ptr
    GetStylusForId	proc :STYLUS_ID, :ptr ptr
    SetDesiredPacketDescription proc :ULONG, :ptr
    GetDesiredPacketDescription proc :ptr, :ptr ptr
    GetPacketDescriptionData proc :TABLET_CONTEXT_ID, :ptr, :ptr, :ptr, :ptr ptr
   .ends

endif

ifndef __IRealTimeStylus2_INTERFACE_DEFINED__
define __IRealTimeStylus2_INTERFACE_DEFINED__

DEFINE_IIDX(IRealTimeStylus2, "B5F2A6CD-3179-4a3e-B9C4-BB5865962BE2")

.comdef IRealTimeStylus2 : public IUnknown
    get_FlicksEnabled	proc :ptr
    put_FlicksEnabled	proc :BOOL
   .ends

endif

ifndef __IRealTimeStylus3_INTERFACE_DEFINED__
define __IRealTimeStylus3_INTERFACE_DEFINED__

DEFINE_IIDX(IRealTimeStylus3, "D70230A3-6986-4051-B57A-1CF69F4D9DB5")

.comdef IRealTimeStylus3 : public IUnknown
    get_MultiTouchEnabled proc :ptr
    put_MultiTouchEnabled proc :BOOL
   .ends

endif

ifndef __IRealTimeStylusSynchronization_INTERFACE_DEFINED__
define __IRealTimeStylusSynchronization_INTERFACE_DEFINED__

DEFINE_IIDX(IRealTimeStylusSynchronization, "AA87EAB8-AB4A-4cea-B5CB-46D84C6A2509")

.comdef IRealTimeStylusSynchronization : public IUnknown
    AcquireLock		proc :RealTimeStylusLockType
    ReleaseLock		proc :RealTimeStylusLockType
   .ends

endif

ifndef __IStrokeBuilder_INTERFACE_DEFINED__
define __IStrokeBuilder_INTERFACE_DEFINED__

DEFINE_IIDX(IStrokeBuilder, "A5FD4E2D-C44B-4092-9177-260905EB672B")

.comdef IStrokeBuilder : public IUnknown
    CreateStroke	proc :ULONG, :ptr, :ULONG, :ptr, :FLOAT, :FLOAT, :ptr ptr
    BeginStroke		proc :TABLET_CONTEXT_ID, :STYLUS_ID, :ptr, :ULONG, :ptr, :FLOAT, :FLOAT, :ptr ptr
    AppendPackets	proc :TABLET_CONTEXT_ID, :STYLUS_ID, :ULONG, :ptr
    EndStroke		proc :TABLET_CONTEXT_ID, :STYLUS_ID, :ptr ptr, :ptr
    get_Ink		proc :ptr ptr
    putref_Ink		proc :ptr
   .ends

endif

ifndef __IStylusPlugin_INTERFACE_DEFINED__
define __IStylusPlugin_INTERFACE_DEFINED__

DEFINE_IIDX(IStylusPlugin, "A81436D8-4757-4fd1-A185-133F97C6C545")

.comdef IStylusPlugin : public IUnknown
    RealTimeStylusEnabled proc :ptr, :ULONG, :ptr
    RealTimeStylusDisabled proc :ptr, :ULONG, :ptr
    StylusInRange	proc :ptr, :TABLET_CONTEXT_ID, :STYLUS_ID
    StylusOutOfRange	proc :ptr, :TABLET_CONTEXT_ID, :STYLUS_ID
    StylusDown		proc :ptr, :ptr, :ULONG, :ptr, :ptr ptr
    StylusUp		proc :ptr, :ptr, :ULONG, :ptr, :ptr ptr
    StylusButtonDown	proc :ptr, :STYLUS_ID, :ptr, :ptr
    StylusButtonUp	proc :ptr, :STYLUS_ID, :ptr, :ptr
    InAirPackets	proc :ptr, :ptr, :ULONG, :ULONG, :ptr, :ptr, :ptr ptr
    Packets		proc :ptr, :ptr, :ULONG, :ULONG, :ptr, :ptr, :ptr ptr
    CustomStylusDataAdded proc :ptr, :ptr, :ULONG, :ptr
    SystemEvent		proc :ptr, :TABLET_CONTEXT_ID, :STYLUS_ID, :SYSTEM_EVENT, :SYSTEM_EVENT_DATA
    TabletAdded		proc :ptr, :ptr
    TabletRemoved	proc :ptr, :LONG
    Error		proc :ptr, :ptr, :RealTimeStylusDataInterest, :HRESULT, :ptr
    UpdateMapping	proc :ptr
    DataInterest	proc :ptr
   .ends

endif

ifndef __IStylusSyncPlugin_INTERFACE_DEFINED__
define __IStylusSyncPlugin_INTERFACE_DEFINED__

DEFINE_IIDX(IStylusSyncPlugin, "A157B174-482F-4d71-A3F6-3A41DDD11BE9")

.comdef IStylusSyncPlugin : public IStylusPlugin
   .ends

endif

ifndef __IStylusAsyncPlugin_INTERFACE_DEFINED__
define __IStylusAsyncPlugin_INTERFACE_DEFINED__

DEFINE_IIDX(IStylusAsyncPlugin, "A7CCA85A-31BC-4cd2-AADC-3289A3AF11C8")

.comdef IStylusAsyncPlugin : public IStylusPlugin
   .ends

endif

ifndef __IDynamicRenderer_INTERFACE_DEFINED__
define __IDynamicRenderer_INTERFACE_DEFINED__

DEFINE_IIDX(IDynamicRenderer, "A079468E-7165-46f9-B7AF-98AD01A93009")

.comdef IDynamicRenderer : public IUnknown
    get_Enabled		proc :ptr
    put_Enabled		proc :BOOL
    get_HWND		proc :ptr
    put_HWND		proc :HANDLE_PTR
    get_ClipRectangle	proc :ptr
    put_ClipRectangle	proc :ptr
    get_ClipRegion	proc :ptr
    put_ClipRegion	proc :HANDLE_PTR
    get_DrawingAttributes proc :ptr ptr
    putref_DrawingAttributes proc :ptr
    get_DataCacheEnabled proc :ptr
    put_DataCacheEnabled proc :BOOL
    ReleaseCachedData	proc :ULONG
    Refresh		proc
    Draw		proc :HANDLE_PTR
   .ends

endif

ifndef __IGestureRecognizer_INTERFACE_DEFINED__
define __IGestureRecognizer_INTERFACE_DEFINED__

DEFINE_IIDX(IGestureRecognizer, "AE9EF86B-7054-45e3-AE22-3174DC8811B7")

.comdef IGestureRecognizer : public IUnknown
    get_Enabled		proc :ptr
    put_Enabled		proc :BOOL
    get_MaxStrokeCount	proc :ptr
    put_MaxStrokeCount	proc :LONG
    EnableGestures	proc :ULONG, :ptr
    Reset		proc
   .ends

endif

DEFINE_GUIDS(CLSID_RealTimeStylus, "E26B366D-F998-43ce-836F-CB6D904432B0")
DEFINE_GUIDS(CLSID_DynamicRenderer, "ECD32AEA-746F-4dcb-BF68-082757FAFF18")
DEFINE_GUIDS(CLSID_GestureRecognizer, "EA30C654-C62C-441f-AC00-95F9A196782C")
DEFINE_GUIDS(CLSID_StrokeBuilder, "E810CEE7-6E51-4cb0-AA3A-0B985B70DAF7")

endif

endif

endif
