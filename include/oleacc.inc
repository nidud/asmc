ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 475
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

ifndef __oleacc_h__
define __oleacc_h__

include oaidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

CALLBACK(LPFNLRESULTFROMOBJECT, :REFIID, :WPARAM, :LPUNKNOWN)
CALLBACK(LPFNOBJECTFROMLRESULT, :LRESULT, :REFIID, :WPARAM, :ptr ptr)
CALLBACK(LPFNACCESSIBLEOBJECTFROMWINDOW, :HWND, :DWORD, :REFIID, :ptr ptr)
CALLBACK(LPFNACCESSIBLEOBJECTFROMPOINT, :POINT, :ptr ptr IAccessible, :ptr VARIANT)
CALLBACK(LPFNCREATESTDACCESSIBLEOBJECT, :HWND, :LONG, :REFIID, :ptr ptr)
CALLBACK(LPFNACCESSIBLECHILDREN, :ptr IAccessible, :LONG, :LONG, :ptr VARIANT, :ptr LONG)


DEFINE_GUID(LIBID_Accessibility,     0x1ea4dbf0, 0x3c3b, 0x11cf, 0x81, 0x0c, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71)
DEFINE_GUID(IID_IAccessible,	     0x618736e0, 0x3c3d, 0x11cf, 0x81, 0x0c, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71)
DEFINE_GUID(IID_IAccessibleHandler,  0x03022430, 0xABC4, 0x11d0, 0xBD, 0xE2, 0x00, 0xAA, 0x00, 0x1A, 0x19, 0x53)
DEFINE_GUID(IID_IAccIdentity,	     0x7852b78d, 0x1cfd, 0x41c1, 0xa6, 0x15, 0x9c, 0x0c, 0x85, 0x96, 0x0b, 0x5f)
DEFINE_GUID(IID_IAccPropServer,	     0x76c0dbbb, 0x15e0, 0x4e7b, 0xb6, 0x1b, 0x20, 0xee, 0xea, 0x20, 0x01, 0xe0)
DEFINE_GUID(IID_IAccPropServices,    0x6e26e776, 0x04f0, 0x495d, 0x80, 0xe4, 0x33, 0x30, 0x35, 0x2e, 0x31, 0x69)
DEFINE_GUID(IID_IAccPropMgrInternal, 0x2bd370a9, 0x3e7f, 0x4edd, 0x8a, 0x85, 0xf8, 0xfe, 0xd1, 0xf8, 0xe5, 0x1f)
DEFINE_GUID(CLSID_AccPropServices,   0xb5f8350b, 0x0548, 0x48b1, 0xa6, 0xee, 0x88, 0xbd, 0x00, 0xb4, 0xa5, 0xe7)
DEFINE_GUID(IIS_IsOleaccProxy,	     0x902697fa, 0x80e4, 0x4560, 0x80, 0x2a, 0xa1, 0x3f, 0x22, 0xa6, 0x47, 0x09)
DEFINE_GUID(IIS_ControlAccessible,   0x38c682a6, 0x9731, 0x43f2, 0x9f, 0xae, 0xe9, 0x01, 0xe6, 0x41, 0xb1, 0x01)


LresultFromObject proto WINAPI :REFIID, :WPARAM, :LPUNKNOWN
ObjectFromLresult proto WINAPI :LRESULT, :REFIID, :WPARAM, :ptr
WindowFromAccessibleObject proto WINAPI :ptr, :ptr
AccessibleObjectFromWindow proto WINAPI :HWND, :DWORD, :REFIID, :ptr
AccessibleObjectFromEvent proto WINAPI :HWND, :DWORD, :DWORD, :ptr, :ptr
AccessibleObjectFromPoint proto WINAPI :POINT, :ptr, :ptr
AccessibleChildren proto WINAPI :ptr, :LONG, :LONG, :ptr, :ptr
GetRoleTextA proto WINAPI :DWORD, :LPSTR, :UINT
GetRoleTextW proto WINAPI :DWORD, :LPWSTR, :UINT
ifdef _UNICODE
GetRoleText		equ <GetRoleTextW>
else
GetRoleText		equ <GetRoleTextA>
endif

GetStateTextA proto WINAPI :DWORD, :LPSTR, :UINT
GetStateTextW proto WINAPI :DWORD, :LPWSTR, :UINT
ifdef _UNICODE
GetStateText		equ <GetStateTextW>
else
GetStateText		equ <GetStateTextA>
endif

GetOleaccVersionInfo proto WINAPI :ptr, :ptr
CreateStdAccessibleObject proto WINAPI :HWND, :LONG, :REFIID, :ptr
CreateStdAccessibleProxyA proto WINAPI :HWND, :LPCSTR, :LONG, :REFIID, :ptr
CreateStdAccessibleProxyW proto WINAPI :HWND, :LPCWSTR, :LONG, :REFIID, :ptr
ifdef _UNICODE
CreateStdAccessibleProxy equ <CreateStdAccessibleProxyW>
else
CreateStdAccessibleProxy equ <CreateStdAccessibleProxyA>
endif

ANRUS_ON_SCREEN_KEYBOARD_ACTIVE equ 0x0000001
ANRUS_TOUCH_MODIFICATION_ACTIVE equ 0x0000002
ANRUS_PRIORITY_AUDIO_ACTIVE equ 0x0000004
ANRUS_PRIORITY_AUDIO_ACTIVE_NODUCK equ 0x0000008

AccSetRunningUtilityState proto WINAPI :HWND, :DWORD, :DWORD
AccNotifyTouchInteraction proto WINAPI :HWND, :HWND, :POINT

MSAA_MENU_SIG		equ 0xAA0DF00D

MSAAMENUINFO		STRUC
dwMSAASignature		dd ?
cchWText		dd ?
pszWText		LPWSTR ?
MSAAMENUINFO		ENDS
LPMSAAMENUINFO		typedef ptr MSAAMENUINFO

DEFINE_GUID( PROPID_ACC_NAME		 , 0x608d3df8, 0x8128, 0x4aa7, 0xa4, 0x28, 0xf5, 0x5e, 0x49, 0x26, 0x72, 0x91);
DEFINE_GUID( PROPID_ACC_VALUE		 , 0x123fe443, 0x211a, 0x4615, 0x95, 0x27, 0xc4, 0x5a, 0x7e, 0x93, 0x71, 0x7a);
DEFINE_GUID( PROPID_ACC_DESCRIPTION	 , 0x4d48dfe4, 0xbd3f, 0x491f, 0xa6, 0x48, 0x49, 0x2d, 0x6f, 0x20, 0xc5, 0x88);
DEFINE_GUID( PROPID_ACC_ROLE		 , 0xcb905ff2, 0x7bd1, 0x4c05, 0xb3, 0xc8, 0xe6, 0xc2, 0x41, 0x36, 0x4d, 0x70);
DEFINE_GUID( PROPID_ACC_STATE		 , 0xa8d4d5b0, 0x0a21, 0x42d0, 0xa5, 0xc0, 0x51, 0x4e, 0x98, 0x4f, 0x45, 0x7b);
DEFINE_GUID( PROPID_ACC_HELP		 , 0xc831e11f, 0x44db, 0x4a99, 0x97, 0x68, 0xcb, 0x8f, 0x97, 0x8b, 0x72, 0x31);
DEFINE_GUID( PROPID_ACC_KEYBOARDSHORTCUT , 0x7d9bceee, 0x7d1e, 0x4979, 0x93, 0x82, 0x51, 0x80, 0xf4, 0x17, 0x2c, 0x34);
DEFINE_GUID( PROPID_ACC_DEFAULTACTION	 , 0x180c072b, 0xc27f, 0x43c7, 0x99, 0x22, 0xf6, 0x35, 0x62, 0xa4, 0x63, 0x2b);

DEFINE_GUID( PROPID_ACC_HELPTOPIC	 , 0x787d1379, 0x8ede, 0x440b, 0x8a, 0xec, 0x11, 0xf7, 0xbf, 0x90, 0x30, 0xb3);
DEFINE_GUID( PROPID_ACC_FOCUS		 , 0x6eb335df, 0x1c29, 0x4127, 0xb1, 0x2c, 0xde, 0xe9, 0xfd, 0x15, 0x7f, 0x2b);
DEFINE_GUID( PROPID_ACC_SELECTION	 , 0xb99d073c, 0xd731, 0x405b, 0x90, 0x61, 0xd9, 0x5e, 0x8f, 0x84, 0x29, 0x84);
DEFINE_GUID( PROPID_ACC_PARENT		 , 0x474c22b6, 0xffc2, 0x467a, 0xb1, 0xb5, 0xe9, 0x58, 0xb4, 0x65, 0x73, 0x30);

DEFINE_GUID( PROPID_ACC_NAV_UP		 , 0x016e1a2b, 0x1a4e, 0x4767, 0x86, 0x12, 0x33, 0x86, 0xf6, 0x69, 0x35, 0xec);
DEFINE_GUID( PROPID_ACC_NAV_DOWN	 , 0x031670ed, 0x3cdf, 0x48d2, 0x96, 0x13, 0x13, 0x8f, 0x2d, 0xd8, 0xa6, 0x68);
DEFINE_GUID( PROPID_ACC_NAV_LEFT	 , 0x228086cb, 0x82f1, 0x4a39, 0x87, 0x05, 0xdc, 0xdc, 0x0f, 0xff, 0x92, 0xf5);
DEFINE_GUID( PROPID_ACC_NAV_RIGHT	 , 0xcd211d9f, 0xe1cb, 0x4fe5, 0xa7, 0x7c, 0x92, 0x0b, 0x88, 0x4d, 0x09, 0x5b);
DEFINE_GUID( PROPID_ACC_NAV_PREV	 , 0x776d3891, 0xc73b, 0x4480, 0xb3, 0xf6, 0x07, 0x6a, 0x16, 0xa1, 0x5a, 0xf6);
DEFINE_GUID( PROPID_ACC_NAV_NEXT	 , 0x1cdc5455, 0x8cd9, 0x4c92, 0xa3, 0x71, 0x39, 0x39, 0xa2, 0xfe, 0x3e, 0xee);
DEFINE_GUID( PROPID_ACC_NAV_FIRSTCHILD	 , 0xcfd02558, 0x557b, 0x4c67, 0x84, 0xf9, 0x2a, 0x09, 0xfc, 0xe4, 0x07, 0x49);
DEFINE_GUID( PROPID_ACC_NAV_LASTCHILD	 , 0x302ecaa5, 0x48d5, 0x4f8d, 0xb6, 0x71, 0x1a, 0x8d, 0x20, 0xa7, 0x78, 0x32);

DEFINE_GUID( PROPID_ACC_ROLEMAP		 , 0xf79acda2, 0x140d, 0x4fe6, 0x89, 0x14, 0x20, 0x84, 0x76, 0x32, 0x82, 0x69);
DEFINE_GUID( PROPID_ACC_VALUEMAP	 , 0xda1c3d79, 0xfc5c, 0x420e, 0xb3, 0x99, 0x9d, 0x15, 0x33, 0x54, 0x9e, 0x75);
DEFINE_GUID( PROPID_ACC_STATEMAP	 , 0x43946c5e, 0x0ac0, 0x4042, 0xb5, 0x25, 0x07, 0xbb, 0xdb, 0xe1, 0x7f, 0xa7);
DEFINE_GUID( PROPID_ACC_DESCRIPTIONMAP	 , 0x1ff1435f, 0x8a14, 0x477b, 0xb2, 0x26, 0xa0, 0xab, 0xe2, 0x79, 0x97, 0x5d);

DEFINE_GUID( PROPID_ACC_DODEFAULTACTION	 , 0x1ba09523, 0x2e3b, 0x49a6, 0xa0, 0x59, 0x59, 0x68, 0x2a, 0x3c, 0x48, 0xfd);


ifndef __IAccessible_INTERFACE_DEFINED__
define __IAccessible_INTERFACE_DEFINED__

DISPID_ACC_PARENT	equ ( -5000 )
DISPID_ACC_CHILDCOUNT	equ ( -5001 )
DISPID_ACC_CHILD	equ ( -5002 )
DISPID_ACC_NAME		equ ( -5003 )
DISPID_ACC_VALUE	equ ( -5004 )
DISPID_ACC_DESCRIPTION	equ ( -5005 )
DISPID_ACC_ROLE		equ ( -5006 )
DISPID_ACC_STATE	equ ( -5007 )
DISPID_ACC_HELP		equ ( -5008 )
DISPID_ACC_HELPTOPIC	equ ( -5009 )
DISPID_ACC_KEYBOARDSHORTCUT equ ( -5010 )
DISPID_ACC_FOCUS	equ ( -5011 )
DISPID_ACC_SELECTION	equ ( -5012 )
DISPID_ACC_DEFAULTACTION equ ( -5013 )
DISPID_ACC_SELECT	equ ( -5014 )
DISPID_ACC_LOCATION	equ ( -5015 )
DISPID_ACC_NAVIGATE	equ ( -5016 )
DISPID_ACC_HITTEST	equ ( -5017 )
DISPID_ACC_DODEFAULTACTION equ ( -5018 )

LPACCESSIBLE		typedef ptr IAccessible

NAVDIR_MIN		equ ( 0 )
NAVDIR_UP		equ ( 0x1 )
NAVDIR_DOWN		equ ( 0x2 )
NAVDIR_LEFT		equ ( 0x3 )
NAVDIR_RIGHT		equ ( 0x4 )
NAVDIR_NEXT		equ ( 0x5 )
NAVDIR_PREVIOUS		equ ( 0x6 )
NAVDIR_FIRSTCHILD	equ ( 0x7 )
NAVDIR_LASTCHILD	equ ( 0x8 )
NAVDIR_MAX		equ ( 0x9 )

SELFLAG_NONE		equ ( 0 )
SELFLAG_TAKEFOCUS	equ ( 0x1 )
SELFLAG_TAKESELECTION	equ ( 0x2 )
SELFLAG_EXTENDSELECTION equ ( 0x4 )
SELFLAG_ADDSELECTION	equ ( 0x8 )
SELFLAG_REMOVESELECTION equ ( 0x10 )
SELFLAG_VALID		equ ( 0x1f )

ifndef STATE_SYSTEM_UNAVAILABLE
STATE_SYSTEM_NORMAL	equ ( 0 )
STATE_SYSTEM_UNAVAILABLE equ ( 0x1 )
STATE_SYSTEM_SELECTED	equ ( 0x2 )
STATE_SYSTEM_FOCUSED	equ ( 0x4 )
STATE_SYSTEM_PRESSED	equ ( 0x8 )
STATE_SYSTEM_CHECKED	equ ( 0x10 )
STATE_SYSTEM_MIXED	equ ( 0x20 )
STATE_SYSTEM_INDETERMINATE equ ( STATE_SYSTEM_MIXED )
STATE_SYSTEM_READONLY	equ ( 0x40 )
STATE_SYSTEM_HOTTRACKED equ ( 0x80 )
STATE_SYSTEM_DEFAULT	equ ( 0x100 )
STATE_SYSTEM_EXPANDED	equ ( 0x200 )
STATE_SYSTEM_COLLAPSED	equ ( 0x400 )
STATE_SYSTEM_BUSY	equ ( 0x800 )
STATE_SYSTEM_FLOATING	equ ( 0x1000 )
STATE_SYSTEM_MARQUEED	equ ( 0x2000 )
STATE_SYSTEM_ANIMATED	equ ( 0x4000 )
STATE_SYSTEM_INVISIBLE	equ ( 0x8000 )
STATE_SYSTEM_OFFSCREEN	equ ( 0x10000 )
STATE_SYSTEM_SIZEABLE	equ ( 0x20000 )
STATE_SYSTEM_MOVEABLE	equ ( 0x40000 )
STATE_SYSTEM_SELFVOICING equ ( 0x80000 )
STATE_SYSTEM_FOCUSABLE	equ ( 0x100000 )
STATE_SYSTEM_SELECTABLE equ ( 0x200000 )
STATE_SYSTEM_LINKED	equ ( 0x400000 )
STATE_SYSTEM_TRAVERSED	equ ( 0x800000 )
STATE_SYSTEM_MULTISELECTABLE equ ( 0x1000000 )
STATE_SYSTEM_EXTSELECTABLE equ ( 0x2000000 )
STATE_SYSTEM_ALERT_LOW	equ ( 0x4000000 )
STATE_SYSTEM_ALERT_MEDIUM equ ( 0x8000000 )
STATE_SYSTEM_ALERT_HIGH equ ( 0x10000000 )
STATE_SYSTEM_PROTECTED	equ ( 0x20000000 )
STATE_SYSTEM_VALID	equ ( 0x7fffffff )
endif
ifndef STATE_SYSTEM_HASPOPUP
STATE_SYSTEM_HASPOPUP	equ ( 0x40000000 )
endif

ROLE_SYSTEM_TITLEBAR	equ ( 0x1 )
ROLE_SYSTEM_MENUBAR	equ ( 0x2 )
ROLE_SYSTEM_SCROLLBAR	equ ( 0x3 )
ROLE_SYSTEM_GRIP	equ ( 0x4 )
ROLE_SYSTEM_SOUND	equ ( 0x5 )
ROLE_SYSTEM_CURSOR	equ ( 0x6 )
ROLE_SYSTEM_CARET	equ ( 0x7 )
ROLE_SYSTEM_ALERT	equ ( 0x8 )
ROLE_SYSTEM_WINDOW	equ ( 0x9 )
ROLE_SYSTEM_CLIENT	equ ( 0xa )
ROLE_SYSTEM_MENUPOPUP	equ ( 0xb )
ROLE_SYSTEM_MENUITEM	equ ( 0xc )
ROLE_SYSTEM_TOOLTIP	equ ( 0xd )
ROLE_SYSTEM_APPLICATION equ ( 0xe )
ROLE_SYSTEM_DOCUMENT	equ ( 0xf )
ROLE_SYSTEM_PANE	equ ( 0x10 )
ROLE_SYSTEM_CHART	equ ( 0x11 )
ROLE_SYSTEM_DIALOG	equ ( 0x12 )
ROLE_SYSTEM_BORDER	equ ( 0x13 )
ROLE_SYSTEM_GROUPING	equ ( 0x14 )
ROLE_SYSTEM_SEPARATOR	equ ( 0x15 )
ROLE_SYSTEM_TOOLBAR	equ ( 0x16 )
ROLE_SYSTEM_STATUSBAR	equ ( 0x17 )
ROLE_SYSTEM_TABLE	equ ( 0x18 )
ROLE_SYSTEM_COLUMNHEADER equ ( 0x19 )
ROLE_SYSTEM_ROWHEADER	equ ( 0x1a )
ROLE_SYSTEM_COLUMN	equ ( 0x1b )
ROLE_SYSTEM_ROW		equ ( 0x1c )
ROLE_SYSTEM_CELL	equ ( 0x1d )
ROLE_SYSTEM_LINK	equ ( 0x1e )
ROLE_SYSTEM_HELPBALLOON equ ( 0x1f )
ROLE_SYSTEM_CHARACTER	equ ( 0x20 )
ROLE_SYSTEM_LIST	equ ( 0x21 )
ROLE_SYSTEM_LISTITEM	equ ( 0x22 )
ROLE_SYSTEM_OUTLINE	equ ( 0x23 )
ROLE_SYSTEM_OUTLINEITEM equ ( 0x24 )
ROLE_SYSTEM_PAGETAB	equ ( 0x25 )
ROLE_SYSTEM_PROPERTYPAGE equ ( 0x26 )
ROLE_SYSTEM_INDICATOR	equ ( 0x27 )
ROLE_SYSTEM_GRAPHIC	equ ( 0x28 )
ROLE_SYSTEM_STATICTEXT	equ ( 0x29 )
ROLE_SYSTEM_TEXT	equ ( 0x2a )
ROLE_SYSTEM_PUSHBUTTON	equ ( 0x2b )
ROLE_SYSTEM_CHECKBUTTON equ ( 0x2c )
ROLE_SYSTEM_RADIOBUTTON equ ( 0x2d )
ROLE_SYSTEM_COMBOBOX	equ ( 0x2e )
ROLE_SYSTEM_DROPLIST	equ ( 0x2f )
ROLE_SYSTEM_PROGRESSBAR equ ( 0x30 )
ROLE_SYSTEM_DIAL	equ ( 0x31 )
ROLE_SYSTEM_HOTKEYFIELD equ ( 0x32 )
ROLE_SYSTEM_SLIDER	equ ( 0x33 )
ROLE_SYSTEM_SPINBUTTON	equ ( 0x34 )
ROLE_SYSTEM_DIAGRAM	equ ( 0x35 )
ROLE_SYSTEM_ANIMATION	equ ( 0x36 )
ROLE_SYSTEM_EQUATION	equ ( 0x37 )
ROLE_SYSTEM_BUTTONDROPDOWN equ ( 0x38 )
ROLE_SYSTEM_BUTTONMENU	equ ( 0x39 )
ROLE_SYSTEM_BUTTONDROPDOWNGRID equ ( 0x3a )
ROLE_SYSTEM_WHITESPACE	equ ( 0x3b )
ROLE_SYSTEM_PAGETABLIST equ ( 0x3c )
ROLE_SYSTEM_CLOCK	equ ( 0x3d )
ROLE_SYSTEM_SPLITBUTTON equ ( 0x3e )
ROLE_SYSTEM_IPADDRESS	equ ( 0x3f )
ROLE_SYSTEM_OUTLINEBUTTON equ ( 0x40 )


DEFINE_IIDX(IAccessible, "618736e0-3c3d-11cf-810c-00aa00389b71")

.comdef IAccessible : public IDispatch

    get_accParent	proc :ptr
    get_accChildCount	proc :ptr
    get_accChild	proc :VARIANT, :ptr
    get_accName		proc :VARIANT, :ptr
    get_accValue	proc :VARIANT, :ptr
    get_accDescription	proc :VARIANT, :ptr
    get_accRole		proc :VARIANT, :ptr
    get_accState	proc :VARIANT, :ptr
    get_accHelp		proc :VARIANT, :ptr
    get_accHelpTopic	proc :ptr, :VARIANT, :ptr
    get_accKeyboardShortcut proc :VARIANT, :ptr
    get_accFocus	proc :ptr
    get_accSelection	proc :ptr
    get_accDefaultAction proc :VARIANT, :ptr
    accSelect		proc :LONG, :VARIANT
    accLocation		proc :ptr, :ptr, :ptr, :ptr, :VARIANT
    accNavigate		proc :LONG, :VARIANT, :ptr
    accHitTest		proc :LONG, :LONG, :ptr
    accDoDefaultAction	proc :VARIANT
    put_accName		proc :VARIANT, :BSTR
    put_accValue	proc :VARIANT, :BSTR
   .ends

endif

ifndef __IAccessibleHandler_INTERFACE_DEFINED__
define __IAccessibleHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibleHandler, "03022430-ABC4-11d0-BDE2-00AA001A1953")

.comdef IAccessibleHandler : public IUnknown

    AccessibleObjectFromID proc :LONG, :LONG, :ptr
   .ends
    LPACCESSIBLEHANDLER	 typedef ptr IAccessibleHandler

endif

ifndef __IAccessibleWindowlessSite_INTERFACE_DEFINED__
define __IAccessibleWindowlessSite_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibleWindowlessSite, "BF3ABD9C-76DA-4389-9EB6-1427D25ABAB7")

.comdef IAccessibleWindowlessSite : public IUnknown

    AcquireObjectIdRange proc :LONG, :ptr, :ptr
    ReleaseObjectIdRange proc :LONG, :ptr
    QueryObjectIdRanges proc :ptr, :ptr
    GetParentAccessible proc :ptr
   .ends
    LPACCESSIBLEWINDOWLESSSITE typedef ptr IAccessibleWindowlessSite

endif

.enum AnnoScope {
    ANNO_THIS	   = 0,
    ANNO_CONTAINER = 1
    }

MSAAPROPID typedef GUID

ifndef __IAccIdentity_INTERFACE_DEFINED__
define __IAccIdentity_INTERFACE_DEFINED__

DEFINE_IIDX(IAccIdentity, "7852b78d-1cfd-41c1-a615-9c0c85960b5f")

.comdef IAccIdentity : public IUnknown

    GetIdentityString	proc :DWORD
   .ends

endif


ifndef __IAccPropServer_INTERFACE_DEFINED__
define __IAccPropServer_INTERFACE_DEFINED__

DEFINE_IIDX(IAccPropServer, "76c0dbbb-15e0-4e7b-b61b-20eeea2001e0")

.comdef IAccPropServer : public IUnknown

    GetPropValue	proc
   .ends

endif


ifndef __IAccPropServices_INTERFACE_DEFINED__
define __IAccPropServices_INTERFACE_DEFINED__

DEFINE_IIDX(IAccPropServices, "6e26e776-04f0-495d-80e4-3330352e3169")

.comdef IAccPropServices : public IUnknown

    SetPropValue	proc
    SetPropServer	proc :ptr, :SINT, :ptr, :AnnoScope
    ClearProps		proc :ptr, :SINT
    SetHwndProp		proc :HWND, :DWORD, :DWORD, :MSAAPROPID, :VARIANT
    SetHwndPropStr	proc :HWND, :DWORD, :DWORD, :MSAAPROPID, :LPCWSTR
    SetHwndPropServer	proc :HWND, :DWORD, :DWORD
    ClearHwndProps	proc :HWND, :DWORD, :DWORD
    ComposeHwndIdentityString proc :HWND, :DWORD, :DWORD
    DecomposeHwndIdentityString proc
    SetHmenuProp	proc :HMENU, :DWORD, :MSAAPROPID, :VARIANT
    SetHmenuPropStr	proc :HMENU, :DWORD, :MSAAPROPID, :LPCWSTR
    SetHmenuPropServer	proc :HMENU, :DWORD
    ClearHmenuProps	proc :HMENU, :DWORD
    ComposeHmenuIdentityString proc :HMENU, :DWORD
    DecomposeHmenuIdentityString proc
   .ends

endif


ifndef __Accessibility_LIBRARY_DEFINED__
define __Accessibility_LIBRARY_DEFINED__

externdef LIBID_Accessibility:IID
DEFINE_GUIDS(CLSID_CAccPropServices, "b5f8350b-0548-48b1-a6ee-88bd00b4a5e7")

endif

endif

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

HMENU_UserSize proto WINAPI :ptr, :dword, :ptr
HMENU_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HMENU_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HMENU_UserFree proto WINAPI :ptr, :ptr

HWND_UserSize proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree proto WINAPI :ptr, :ptr

LPSAFEARRAY_UserSize proto WINAPI :ptr, :dword, :ptr
LPSAFEARRAY_UserMarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
LPSAFEARRAY_UserFree proto WINAPI :ptr, :ptr

VARIANT_UserSize proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree proto WINAPI :ptr, :ptr

endif
