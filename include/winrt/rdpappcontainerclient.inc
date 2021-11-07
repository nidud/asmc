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

ifndef __rdpappcontainerclient_h__
define __rdpappcontainerclient_h__

include oaidl.inc
include ocidl.inc

if (NTDDI_VERSION GE NTDDI_WIN8)

define	DISPID_METHOD_REMOTEDESKTOPCLIENT_CONNECT	( 701 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_DISCONNECT	( 702 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_RECONNECT	( 703 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_DELETE_SAVED_CREDENTIALS	( 704 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_UPDATE_SESSION_DISPLAYSETTINGS	( 705 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_ATTACH_EVENT	( 706 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_DETACH_EVENT	( 707 )
define	DISPID_PROP_REMOTEDESKTOPCLIENT_SETTINGS	( 710 )
define	DISPID_PROP_REMOTEDESKTOPCLIENT_ACTIONS ( 711 )
define	DISPID_PROP_REMOTEDESKTOPCLIENT_TOUCH_POINTER	( 712 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_SET_RDPPROPERTY	( 720 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_GET_RDPPROPERTY	( 721 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_APPLY_SETTINGS	( 722 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_RETRIEVE_SETTINGS	( 723 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_SUSPEND_SCREEN_UPDATES	( 730 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_RESUME_SCREEN_UPDATES ( 731 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_EXECUTE_REMOTE_ACTION ( 732 )
define	DISPID_METHOD_REMOTEDESKTOPCLIENT_GET_SNAPSHOT	( 733 )
define	DISPID_PROP_REMOTEDESKTOPCLIENT_TOUCHPOINTER_ENABLED	( 740 )
define	DISPID_PROP_REMOTEDESKTOPCLIENT_TOUCHPOINTER_EVENTSENABLED	( 741 )
define	DISPID_PROP_REMOTEDESKTOPCLIENT_TOUCHPOINTER_POINTERSPEED	( 742 )
define	DISPID_AX_CONNECTING	( 750 )
define	DISPID_AX_CONNECTED	( 751 )
define	DISPID_AX_LOGINCOMPLETED	( 752 )
define	DISPID_AX_DISCONNECTED	( 753 )
define	DISPID_AX_STATUSCHANGED ( 754 )
define	DISPID_AX_AUTORECONNECTING	( 755 )
define	DISPID_AX_AUTORECONNECTED	( 756 )
define	DISPID_AX_DIALOGDISPLAYING	( 757 )
define	DISPID_AX_DIALOGDISMISSED	( 758 )
define	DISPID_AX_NETWORKSTATUSCHANGED	( 759 )
define	DISPID_AX_ADMINMESSAGERECEIVED	( 760 )
define	DISPID_AX_KEYCOMBINATIONPRESSED ( 761 )
define	DISPID_AX_REMOTEDESKTOPSIZECHANGED	( 762 )
define	DISPID_AX_TOUCHPOINTERCURSORMOVED	( 800 )

ifndef __IRemoteDesktopClientSettings_INTERFACE_DEFINED__
define __IRemoteDesktopClientSettings_INTERFACE_DEFINED__

.enum PasswordEncodingType {
    PasswordEncodingUTF8,
    PasswordEncodingUTF16LE,
    PasswordEncodingUTF16BE
    }

DEFINE_IIDX(IRemoteDesktopClientSettings, "48A0F2A7-2713-431f-BBAC-6F4558E7D64D")

.comdef IRemoteDesktopClientSettings : public IDispatch

    ApplySettings	proc :BSTR
    RetrieveSettings	proc :ptr
    GetRdpProperty	proc :BSTR, :ptr
    SetRdpProperty	proc :BSTR, :VARIANT
   .ends

endif

ifndef __IRemoteDesktopClientActions_INTERFACE_DEFINED__
define __IRemoteDesktopClientActions_INTERFACE_DEFINED__

.enum RemoteActionType {
    RemoteActionCharms,
    RemoteActionAppbar,
    RemoteActionSnap,
    RemoteActionStartScreen,
    RemoteActionAppSwitch
    }

.enum SnapshotEncodingType {
    SnapshotEncodingDataUri
    }

.enum SnapshotFormatType {
    SnapshotFormatPng,
    SnapshotFormatJpeg,
    SnapshotFormatBmp
    }

DEFINE_IIDX(IRemoteDesktopClientActions, "7D54BC4E-1028-45d4-8B0A-B9B6BFFBA176")

.comdef IRemoteDesktopClientActions : public IDispatch

    SuspendScreenUpdates proc
    ResumeScreenUpdates proc
    ExecuteRemoteAction proc :RemoteActionType
    GetSnapshot		proc :SnapshotEncodingType, :SnapshotFormatType, :ULONG, :ULONG, :ptr
   .ends

endif

ifndef __IRemoteDesktopClientTouchPointer_INTERFACE_DEFINED__
define __IRemoteDesktopClientTouchPointer_INTERFACE_DEFINED__
DEFINE_IIDX(IRemoteDesktopClientTouchPointer, "260ec22d-8cbc-44b5-9e88-2a37f6c93ae9")

.comdef IRemoteDesktopClientTouchPointer : public IDispatch

    put_Enabled		proc :VARIANT_BOOL
    get_Enabled		proc :ptr
    put_EventsEnabled	proc :VARIANT_BOOL
    get_EventsEnabled	proc :ptr
    put_PointerSpeed	proc :ULONG
    get_PointerSpeed	proc :ptr
   .ends

endif

ifndef __IRemoteDesktopClient_INTERFACE_DEFINED__
define __IRemoteDesktopClient_INTERFACE_DEFINED__

.enum KeyCombinationType {
    KeyCombinationHome,
    KeyCombinationLeft,
    KeyCombinationUp,
    KeyCombinationRight,
    KeyCombinationDown,
    KeyCombinationScroll
    }

DEFINE_IIDX(IRemoteDesktopClient, "57D25668-625A-4905-BE4E-304CAA13F89C")

.comdef IRemoteDesktopClient : public IDispatch

    Connect		proc
    Disconnect		proc
    Reconnect		proc :ULONG, :ULONG
    get_Settings	proc :ptr
    get_Actions		proc :ptr
    get_TouchPointer	proc :ptr
    DeleteSavedCredentials proc :BSTR
    UpdateSessionDisplaySettings proc :ULONG, :ULONG
    attachEvent		proc :BSTR, :ptr
    detachEvent		proc :BSTR, :ptr
   .ends

endif
endif

endif
