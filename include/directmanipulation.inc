ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err<this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __directmanipulation_h__
__directmanipulation_h__ equ <>

ifndef __IDirectManipulationManager_FWD_DEFINED__
__IDirectManipulationManager_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationManager2_FWD_DEFINED__
__IDirectManipulationManager2_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationViewport_FWD_DEFINED__
__IDirectManipulationViewport_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationViewport2_FWD_DEFINED__
__IDirectManipulationViewport2_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationViewportEventHandler_FWD_DEFINED__
__IDirectManipulationViewportEventHandler_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationContent_FWD_DEFINED__
__IDirectManipulationContent_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationPrimaryContent_FWD_DEFINED__
__IDirectManipulationPrimaryContent_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationDragDropEventHandler_FWD_DEFINED__
__IDirectManipulationDragDropEventHandler_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationDragDropBehavior_FWD_DEFINED__
__IDirectManipulationDragDropBehavior_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationInteractionEventHandler_FWD_DEFINED__
__IDirectManipulationInteractionEventHandler_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationFrameInfoProvider_FWD_DEFINED__
__IDirectManipulationFrameInfoProvider_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationCompositor_FWD_DEFINED__
__IDirectManipulationCompositor_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationUpdateHandler_FWD_DEFINED__
__IDirectManipulationUpdateHandler_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationUpdateManager_FWD_DEFINED__
__IDirectManipulationUpdateManager_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationAutoScrollBehavior_FWD_DEFINED__
__IDirectManipulationAutoScrollBehavior_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationParametricMotionBehavior_FWD_DEFINED__
__IDirectManipulationParametricMotionBehavior_FWD_DEFINED__ equ 1
endif
ifndef __IDirectManipulationParametricMotionCurve_FWD_DEFINED__
__IDirectManipulationParametricMotionCurve_FWD_DEFINED__ equ 1
endif
ifndef __DirectManipulationViewport_FWD_DEFINED__
__DirectManipulationViewport_FWD_DEFINED__ equ 1
endif
ifndef __DirectManipulationUpdateManager_FWD_DEFINED__
__DirectManipulationUpdateManager_FWD_DEFINED__ equ 1
endif
ifndef __DirectManipulationPrimaryContent_FWD_DEFINED__
__DirectManipulationPrimaryContent_FWD_DEFINED__ equ 1
endif
ifndef __DirectManipulationManager_FWD_DEFINED__
__DirectManipulationManager_FWD_DEFINED__ equ 1
endif
ifndef __DCompManipulationCompositor_FWD_DEFINED__
__DCompManipulationCompositor_FWD_DEFINED__ equ 1
endif

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (NTDDI_VERSION GE NTDDI_WIN8)

DIRECTMANIPULATION_STATUS typedef SDWORD
DIRECTMANIPULATION_BUILDING equ 0
DIRECTMANIPULATION_ENABLED equ 1
DIRECTMANIPULATION_DISABLED equ 2
DIRECTMANIPULATION_RUNNING equ 3
DIRECTMANIPULATION_INERTIA equ 4
DIRECTMANIPULATION_READY equ 5
DIRECTMANIPULATION_SUSPENDED equ 6

DIRECTMANIPULATION_HITTEST_TYPE typedef SDWORD
DIRECTMANIPULATION_HITTEST_TYPE_ASYNCHRONOUS equ 0
DIRECTMANIPULATION_HITTEST_TYPE_SYNCHRONOUS equ 0x1
DIRECTMANIPULATION_HITTEST_TYPE_AUTO_SYNCHRONOUS equ 0x2

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_HITTEST_TYPE)
DIRECTMANIPULATION_CONFIGURATION typedef SDWORD
DIRECTMANIPULATION_CONFIGURATION_NONE equ 0
DIRECTMANIPULATION_CONFIGURATION_INTERACTION equ 0x1
DIRECTMANIPULATION_CONFIGURATION_TRANSLATION_X equ 0x2
DIRECTMANIPULATION_CONFIGURATION_TRANSLATION_Y equ 0x4
DIRECTMANIPULATION_CONFIGURATION_SCALING equ 0x10
DIRECTMANIPULATION_CONFIGURATION_TRANSLATION_INERTIA equ 0x20
DIRECTMANIPULATION_CONFIGURATION_SCALING_INERTIA equ 0x80
DIRECTMANIPULATION_CONFIGURATION_RAILS_X equ 0x100
DIRECTMANIPULATION_CONFIGURATION_RAILS_Y equ 0x200

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_CONFIGURATION)
DIRECTMANIPULATION_GESTURE_CONFIGURATION typedef SDWORD
DIRECTMANIPULATION_GESTURE_NONE equ 0
DIRECTMANIPULATION_GESTURE_DEFAULT equ 0
DIRECTMANIPULATION_GESTURE_CROSS_SLIDE_VERTICAL equ 0x8
DIRECTMANIPULATION_GESTURE_CROSS_SLIDE_HORIZONTAL equ 0x10
DIRECTMANIPULATION_GESTURE_PINCH_ZOOM equ 0x20

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_GESTURE_CONFIGURATION)
DIRECTMANIPULATION_MOTION_TYPES typedef SDWORD
DIRECTMANIPULATION_MOTION_NONE equ 0
DIRECTMANIPULATION_MOTION_TRANSLATEX equ 0x1
DIRECTMANIPULATION_MOTION_TRANSLATEY equ 0x2
DIRECTMANIPULATION_MOTION_ZOOM equ 0x4
DIRECTMANIPULATION_MOTION_CENTERX equ 0x10
DIRECTMANIPULATION_MOTION_CENTERY equ 0x20
DIRECTMANIPULATION_MOTION_ALL equ ( ( ( ( DIRECTMANIPULATION_MOTION_TRANSLATEX or \
	DIRECTMANIPULATION_MOTION_TRANSLATEY ) or DIRECTMANIPULATION_MOTION_ZOOM ) or \
	DIRECTMANIPULATION_MOTION_CENTERX ) or DIRECTMANIPULATION_MOTION_CENTERY )

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_MOTION_TYPES)
DIRECTMANIPULATION_VIEWPORT_OPTIONS typedef SDWORD
DIRECTMANIPULATION_VIEWPORT_OPTIONS_DEFAULT equ 0
DIRECTMANIPULATION_VIEWPORT_OPTIONS_AUTODISABLE equ 0x1
DIRECTMANIPULATION_VIEWPORT_OPTIONS_MANUALUPDATE equ 0x2
DIRECTMANIPULATION_VIEWPORT_OPTIONS_INPUT equ 0x4
DIRECTMANIPULATION_VIEWPORT_OPTIONS_EXPLICITHITTEST equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_VIEWPORT_OPTIONS)
DIRECTMANIPULATION_SNAPPOINT_TYPE typedef SDWORD
DIRECTMANIPULATION_SNAPPOINT_MANDATORY equ 0
DIRECTMANIPULATION_SNAPPOINT_OPTIONAL equ 1
DIRECTMANIPULATION_SNAPPOINT_MANDATORY_SINGLE equ 2
DIRECTMANIPULATION_SNAPPOINT_OPTIONAL_SINGLE equ 3

DIRECTMANIPULATION_SNAPPOINT_COORDINATE typedef SDWORD
DIRECTMANIPULATION_COORDINATE_BOUNDARY equ 0
DIRECTMANIPULATION_COORDINATE_ORIGIN equ 0x1
DIRECTMANIPULATION_COORDINATE_MIRRORED equ 0x10

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_SNAPPOINT_COORDINATE)
DIRECTMANIPULATION_HORIZONTALALIGNMENT typedef SDWORD
DIRECTMANIPULATION_HORIZONTALALIGNMENT_NONE equ 0
DIRECTMANIPULATION_HORIZONTALALIGNMENT_LEFT equ 0x1
DIRECTMANIPULATION_HORIZONTALALIGNMENT_CENTER equ 0x2
DIRECTMANIPULATION_HORIZONTALALIGNMENT_RIGHT equ 0x4
DIRECTMANIPULATION_HORIZONTALALIGNMENT_UNLOCKCENTER equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_HORIZONTALALIGNMENT)
DIRECTMANIPULATION_VERTICALALIGNMENT typedef SDWORD
DIRECTMANIPULATION_VERTICALALIGNMENT_NONE equ 0
DIRECTMANIPULATION_VERTICALALIGNMENT_TOP equ 0x1
DIRECTMANIPULATION_VERTICALALIGNMENT_CENTER equ 0x2
DIRECTMANIPULATION_VERTICALALIGNMENT_BOTTOM equ 0x4
DIRECTMANIPULATION_VERTICALALIGNMENT_UNLOCKCENTER equ 0x8

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_VERTICALALIGNMENT)
DIRECTMANIPULATION_INPUT_MODE typedef SDWORD
DIRECTMANIPULATION_INPUT_MODE_AUTOMATIC equ 0
DIRECTMANIPULATION_INPUT_MODE_MANUAL equ 1

DIRECTMANIPULATION_KEYBOARDFOCUS equ ( 0xfffffffe )
DIRECTMANIPULATION_MOUSEFOCUS equ ( 0xfffffffd )
DIRECTMANIPULATION_MINIMUM_ZOOM equ ( 0.1 )

DEFINE_GUID(CLSID_VerticalIndicatorContent, 0xa10b5f17, 0xafe0, 0x4aa2, 0x91, 0xe9, 0x3e, 0x70, 0x1, 0xd2, 0xe6, 0xb4);
DEFINE_GUID(CLSID_HorizontalIndicatorContent, 0xe7d18cf5, 0x3ec7, 0x44d5, 0xa7, 0x6b, 0x37, 0x70, 0xf3, 0xcf, 0x90, 0x3d);
DEFINE_GUID(CLSID_VirtualViewportContent, 0x3206a19a, 0x86f0, 0x4cb4, 0xa7, 0xf3, 0x16, 0xe3, 0xb7, 0xe2, 0xd8, 0x52);
DEFINE_GUID(CLSID_DragDropConfigurationBehavior, 0x09b01b3e, 0xba6c, 0x454d, 0x82, 0xe8, 0x95, 0xe3, 0x52, 0x32, 0x9f, 0x23);
DEFINE_GUID(CLSID_AutoScrollBehavior, 0x26126a51, 0x3c70, 0x4c9a, 0xae, 0xc2, 0x94, 0x88, 0x49, 0xee, 0xb0, 0x93);


ifndef __IDirectManipulationManager_INTERFACE_DEFINED__
__IDirectManipulationManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationManager, "FBF5D3B4-70C7-4163-9322-5A6F660D6FBC")

.comdef IDirectManipulationManager

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Activate		proc :HWND
    Deactivate		proc :HWND
    RegisterHitTestTarget proc :HWND, :HWND, :DIRECTMANIPULATION_HITTEST_TYPE
    ProcessInput	proc :ptr MSG, :ptr BOOL
    GetUpdateManager	proc :REFIID, :ptr
    CreateViewport	proc :ptr, :HWND, :REFIID, :ptr
    CreateContent	proc :ptr, :REFCLSID, :REFIID, :ptr
    .ends

endif

ifndef __IDirectManipulationManager2_INTERFACE_DEFINED__
__IDirectManipulationManager2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationManager2, "923CCAAC-61E1-4385-B726-017AF189882A")

.comdef IDirectManipulationManager2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Activate		proc :HWND
    Deactivate		proc :HWND
    RegisterHitTestTarget proc :HWND, :HWND, :DIRECTMANIPULATION_HITTEST_TYPE
    ProcessInput	proc :ptr MSG, :ptr
    GetUpdateManager	proc :REFIID, :ptr
    CreateViewport	proc :ptr, :HWND, :REFIID, :ptr
    CreateContent	proc :ptr, :REFCLSID, :REFIID, :ptr
    CreateBehavior	proc :REFCLSID, :REFIID, :ptr
    .ends

endif

ifndef __IDirectManipulationViewport_INTERFACE_DEFINED__
__IDirectManipulationViewport_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationViewport, "952121DA-D69F-45F9-B0F9-F23944321A6D")

.comdef IDirectManipulationViewport

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Enable		proc
    Disable		proc
    SetContact		proc :UINT32
    ReleaseContact	proc :UINT32
    ReleaseAllContacts	proc
    GetStatus		proc :ptr
    GetTag		proc :REFIID, :ptr, :ptr
    SetTag		proc :ptr, :UINT32
    GetViewportRect	proc :ptr
    SetViewportRect	proc :ptr RECT
    ZoomToRect		proc :real4, :real4, :real4, :real4, :BOOL
    SetViewportTransform proc :ptr real4, :DWORD
    SyncDisplayTransform proc :ptr real4, :DWORD
    GetPrimaryContent	proc :REFIID, :ptr
    AddContent		proc :ptr
    RemoveContent	proc :ptr
    SetViewportOptions	proc :DIRECTMANIPULATION_VIEWPORT_OPTIONS
    AddConfiguration	proc :DIRECTMANIPULATION_CONFIGURATION
    RemoveConfiguration proc :DIRECTMANIPULATION_CONFIGURATION
    ActivateConfiguration proc :DIRECTMANIPULATION_CONFIGURATION
    SetManualGesture	proc :DIRECTMANIPULATION_GESTURE_CONFIGURATION
    SetChaining		proc :DIRECTMANIPULATION_MOTION_TYPES
    AddEventHandler	proc :HWND, :ptr, :ptr
    RemoveEventHandler	proc :DWORD
    SetInputMode	proc :DIRECTMANIPULATION_INPUT_MODE
    SetUpdateMode	proc :DIRECTMANIPULATION_INPUT_MODE
    Stop		proc
    Abandon		proc
    .ends

endif

ifndef __IDirectManipulationViewport2_INTERFACE_DEFINED__
__IDirectManipulationViewport2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationViewport2, "923CCAAC-61E1-4385-B726-017AF189882A")

.comdef IDirectManipulationViewport2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Enable		proc
    Disable		proc
    SetContact		proc :UINT32
    ReleaseContact	proc :UINT32
    ReleaseAllContacts	proc
    GetStatus		proc :ptr
    GetTag		proc :REFIID, :ptr, :ptr
    SetTag		proc :ptr, :UINT32
    GetViewportRect	proc :ptr
    SetViewportRect	proc :ptr real4
    ZoomToRect		proc :real4, :real4, :real4, :real4, :BOOL
    SetViewportTransform proc
    SyncDisplayTransform proc
    GetPrimaryContent	proc :REFIID, :ptr
    AddContent		proc :ptr
    RemoveContent	proc :ptr
    SetViewportOptions	proc :DIRECTMANIPULATION_VIEWPORT_OPTIONS
    AddConfiguration	proc :DIRECTMANIPULATION_CONFIGURATION
    RemoveConfiguration proc :DIRECTMANIPULATION_CONFIGURATION
    ActivateConfiguration proc :DIRECTMANIPULATION_CONFIGURATION
    SetManualGesture	proc :DIRECTMANIPULATION_GESTURE_CONFIGURATION
    SetChaining		proc :DIRECTMANIPULATION_MOTION_TYPES
    AddEventHandler	proc :HWND, :ptr, :ptr
    RemoveEventHandler	proc :DWORD
    SetInputMode	proc :DIRECTMANIPULATION_INPUT_MODE
    SetUpdateMode	proc :DIRECTMANIPULATION_INPUT_MODE
    Stop		proc
    Abandon		proc
    AddBehavior		proc :ptr, :ptr
    RemoveBehavior	proc :DWORD
    RemoveAllBehaviors	proc
    .ends

endif

ifndef __IDirectManipulationViewportEventHandler_INTERFACE_DEFINED__
__IDirectManipulationViewportEventHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationViewportEventHandler, "952121DA-D69F-45F9-B0F9-F23944321A6D")

.comdef IDirectManipulationViewportEventHandler

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnViewportStatusChanged proc :ptr, :DIRECTMANIPULATION_STATUS, :DIRECTMANIPULATION_STATUS
    OnViewportUpdated	proc :ptr
    OnContentUpdated	proc :ptr, :ptr
    .ends

endif

ifndef __IDirectManipulationContent_INTERFACE_DEFINED__
__IDirectManipulationContent_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationContent, "B89962CB-3D89-442B-BB58-5098FA0F9F16")

.comdef IDirectManipulationContent

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetContentRect	proc :ptr
    SetContentRect	proc :ptr
    GetViewport		proc :REFIID, :ptr
    GetTag		proc :REFIID, :ptr, :ptr
    SetTag		proc :ptr, :UINT32
    GetOutputTransform	proc
    GetContentTransform proc
    SyncContentTransform proc
    .ends

endif

ifndef __IDirectManipulationPrimaryContent_INTERFACE_DEFINED__
__IDirectManipulationPrimaryContent_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationPrimaryContent, "C12851E4-1698-4625-B9B1-7CA3EC18630B")

.comdef IDirectManipulationPrimaryContent

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetSnapInterval	proc :DIRECTMANIPULATION_MOTION_TYPES, :float, :float
    SetSnapPoints	proc :DIRECTMANIPULATION_MOTION_TYPES
    SetSnapType		proc :DIRECTMANIPULATION_MOTION_TYPES, :DIRECTMANIPULATION_SNAPPOINT_TYPE
    SetSnapCoordinate	proc :DIRECTMANIPULATION_MOTION_TYPES, :DIRECTMANIPULATION_SNAPPOINT_COORDINATE, :float
    SetZoomBoundaries	proc :float, :float
    SetHorizontalAlignment proc :DIRECTMANIPULATION_HORIZONTALALIGNMENT
    SetVerticalAlignment proc :DIRECTMANIPULATION_VERTICALALIGNMENT
    GetInertiaEndTransform proc
    GetCenterPoint	proc :ptr, :ptr
    .ends

endif

DIRECTMANIPULATION_DRAG_DROP_STATUS typedef SDWORD
DIRECTMANIPULATION_DRAG_DROP_READY equ 0
DIRECTMANIPULATION_DRAG_DROP_PRESELECT equ 1
DIRECTMANIPULATION_DRAG_DROP_SELECTING equ 2
DIRECTMANIPULATION_DRAG_DROP_DRAGGING equ 3
DIRECTMANIPULATION_DRAG_DROP_CANCELLED equ 4
DIRECTMANIPULATION_DRAG_DROP_COMMITTED equ 5

ifndef __IDirectManipulationDragDropEventHandler_INTERFACE_DEFINED__
__IDirectManipulationDragDropEventHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationDragDropEventHandler, "1FA11B10-701B-41AE-B5F2-49E36BD595AA")

.comdef IDirectManipulationDragDropEventHandler

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnDragDropStatusChange proc :ptr, :DIRECTMANIPULATION_DRAG_DROP_STATUS, :DIRECTMANIPULATION_DRAG_DROP_STATUS
    .ends

endif

DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION typedef SDWORD
DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION_VERTICAL equ 0x1
DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION_HORIZONTAL equ 0x2
DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION_SELECT_ONLY equ 0x10
DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION_SELECT_DRAG equ 0x20
DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION_HOLD_DRAG equ 0x40

DEFINE_ENUM_FLAG_OPERATORS(DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION)

ifndef __IDirectManipulationDragDropBehavior_INTERFACE_DEFINED__
__IDirectManipulationDragDropBehavior_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationDragDropBehavior, "814B5AF5-C2C8-4270-A9B7-A198CE8D02FA")

.comdef IDirectManipulationDragDropBehavior

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetConfiguration	proc :DIRECTMANIPULATION_DRAG_DROP_CONFIGURATION
    GetStatus		proc :ptr
    .ends

endif

DIRECTMANIPULATION_INTERACTION_TYPE typedef SDWORD
DIRECTMANIPULATION_INTERACTION_BEGIN equ 0
DIRECTMANIPULATION_INTERACTION_TYPE_MANIPULATION equ 1
DIRECTMANIPULATION_INTERACTION_TYPE_GESTURE_TAP equ 2
DIRECTMANIPULATION_INTERACTION_TYPE_GESTURE_HOLD equ 3
DIRECTMANIPULATION_INTERACTION_TYPE_GESTURE_CROSS_SLIDE equ 4
DIRECTMANIPULATION_INTERACTION_TYPE_GESTURE_PINCH_ZOOM equ 5
DIRECTMANIPULATION_INTERACTION_END equ 100

ifndef __IDirectManipulationInteractionEventHandler_INTERFACE_DEFINED__
__IDirectManipulationInteractionEventHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationInteractionEventHandler, "E43F45B8-42B4-403E-B1F2-273B8F510830")

.comdef IDirectManipulationInteractionEventHandler

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnInteraction	proc :ptr, :DIRECTMANIPULATION_INTERACTION_TYPE
    .ends

endif

ifndef __IDirectManipulationFrameInfoProvider_INTERFACE_DEFINED__
__IDirectManipulationFrameInfoProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationFrameInfoProvider, "fb759dba-6f4c-4c01-874e-19c8a05907f9")

.comdef IDirectManipulationFrameInfoProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetNextFrameInfo	proc :ptr, :ptr, :ptr
    .ends

endif

ifndef __IDirectManipulationCompositor_INTERFACE_DEFINED__
__IDirectManipulationCompositor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationCompositor, "537A0825-0387-4EFA-B62F-71EB1F085A7E")

.comdef IDirectManipulationCompositor

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddContent		proc :ptr, :ptr, :ptr, :ptr
    RemoveContent	proc :ptr
    SetUpdateManager	proc :ptr
    Flush		proc
    .ends

endif

ifndef __IDirectManipulationUpdateHandler_INTERFACE_DEFINED__
__IDirectManipulationUpdateHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationUpdateHandler, "790B6337-64F8-4FF5-A269-B32BC2AF27A7")

.comdef IDirectManipulationUpdateHandler

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Update		proc
    .ends

endif

ifndef __IDirectManipulationUpdateManager_INTERFACE_DEFINED__
__IDirectManipulationUpdateManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationUpdateManager, "B0AE62FD-BE34-46E7-9CAA-D361FACBB9CC")

.comdef IDirectManipulationUpdateManager

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    RegisterWaitHandleCallback proc :HANDLE, :ptr, :ptr
    UnregisterWaitHandleCallback proc :DWORD
    Update		proc :ptr
    .ends

endif

DIRECTMANIPULATION_AUTOSCROLL_CONFIGURATION typedef SDWORD
DIRECTMANIPULATION_AUTOSCROLL_CONFIGURATION_STOP equ 0
DIRECTMANIPULATION_AUTOSCROLL_CONFIGURATION_FORWARD equ 1
DIRECTMANIPULATION_AUTOSCROLL_CONFIGURATION_REVERSE equ 2

ifndef __IDirectManipulationAutoScrollBehavior_INTERFACE_DEFINED__
__IDirectManipulationAutoScrollBehavior_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDirectManipulationAutoScrollBehavior, "6D5954D4-2003-4356-9B31-D051C9FF0AF7")

.comdef IDirectManipulationAutoScrollBehavior

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetConfiguration	proc :DIRECTMANIPULATION_MOTION_TYPES, :DIRECTMANIPULATION_AUTOSCROLL_CONFIGURATION
    .ends

endif

endif ;; #if (NTDDI_VERSION GT NTDDI_WIN8)

ifndef __DirectManipulation_LIBRARY_DEFINED__
__DirectManipulation_LIBRARY_DEFINED__ equ 1

externdef		LIBID_DirectManipulation:IID
DEFINE_GUIDS(CLSID_DirectManipulationViewport,		"34E211B6-3650-4F75-8334-FA359598E1C5")
DEFINE_GUIDS(CLSID_DirectManipulationUpdateManager,	"9FC1BFD5-1835-441A-B3B1-B6CC74B727D0")
DEFINE_GUIDS(CLSID_DirectManipulationPrimaryContent,	"CAA02661-D59E-41C7-8393-3BA3BACB6B57")
DEFINE_GUIDS(CLSID_DirectManipulationManager,		"54E211B6-3650-4F75-8334-FA359598E1C5")
DEFINE_GUIDS(CLSID_DCompManipulationCompositor,		"79DEA627-A08A-43AC-8EF5-6900B9299126")

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

endif
