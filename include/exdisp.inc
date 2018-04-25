.pragma list(push, 0)
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 475
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif
ifndef __exdisp_h__
__exdisp_h__ equ <>

ifndef __IWebBrowser_FWD_DEFINED__
__IWebBrowser_FWD_DEFINED__ equ 1
endif
ifndef __DWebBrowserEvents_FWD_DEFINED__
__DWebBrowserEvents_FWD_DEFINED__ equ 1
endif
ifndef __IWebBrowserApp_FWD_DEFINED__
__IWebBrowserApp_FWD_DEFINED__ equ 1
endif
ifndef __IWebBrowser2_FWD_DEFINED__
__IWebBrowser2_FWD_DEFINED__ equ 1
endif
ifndef __DWebBrowserEvents2_FWD_DEFINED__
__DWebBrowserEvents2_FWD_DEFINED__ equ 1
endif
ifndef __WebBrowser_V1_FWD_DEFINED__
__WebBrowser_V1_FWD_DEFINED__ equ 1
WebBrowser_V1		typedef WebBrowser_V1
endif
ifndef __WebBrowser_FWD_DEFINED__
__WebBrowser_FWD_DEFINED__ equ 1
WebBrowser		typedef WebBrowser
endif
ifndef __InternetExplorer_FWD_DEFINED__
__InternetExplorer_FWD_DEFINED__ equ 1
InternetExplorer	typedef InternetExplorer
endif
ifndef __InternetExplorerMedium_FWD_DEFINED__
__InternetExplorerMedium_FWD_DEFINED__ equ 1
InternetExplorerMedium	typedef InternetExplorerMedium
endif
ifndef __ShellBrowserWindow_FWD_DEFINED__
__ShellBrowserWindow_FWD_DEFINED__ equ 1
ShellBrowserWindow	typedef ShellBrowserWindow
endif
ifndef __DShellWindowsEvents_FWD_DEFINED__
__DShellWindowsEvents_FWD_DEFINED__ equ 1
endif
ifndef __IShellWindows_FWD_DEFINED__
__IShellWindows_FWD_DEFINED__ equ 1
endif
ifndef __ShellWindows_FWD_DEFINED__
__ShellWindows_FWD_DEFINED__ equ 1
ShellWindows		typedef ShellWindows
endif
ifndef __IShellUIHelper_FWD_DEFINED__
__IShellUIHelper_FWD_DEFINED__ equ 1
endif
ifndef __IShellUIHelper2_FWD_DEFINED__
__IShellUIHelper2_FWD_DEFINED__ equ 1
endif
ifndef __IShellUIHelper3_FWD_DEFINED__
__IShellUIHelper3_FWD_DEFINED__ equ 1
endif
ifndef __ShellUIHelper_FWD_DEFINED__
__ShellUIHelper_FWD_DEFINED__ equ 1
ShellUIHelper		typedef ShellUIHelper
endif
ifndef __DShellNameSpaceEvents_FWD_DEFINED__
__DShellNameSpaceEvents_FWD_DEFINED__ equ 1
endif
ifndef __IShellFavoritesNameSpace_FWD_DEFINED__
__IShellFavoritesNameSpace_FWD_DEFINED__ equ 1
endif
ifndef __IShellNameSpace_FWD_DEFINED__
__IShellNameSpace_FWD_DEFINED__ equ 1
endif
ifndef __ShellNameSpace_FWD_DEFINED__
__ShellNameSpace_FWD_DEFINED__ equ 1
ShellNameSpace		typedef ShellNameSpace
endif
ifndef __IScriptErrorList_FWD_DEFINED__
__IScriptErrorList_FWD_DEFINED__ equ 1
endif
ifndef __CScriptErrorList_FWD_DEFINED__
__CScriptErrorList_FWD_DEFINED__ equ 1
CScriptErrorList	typedef CScriptErrorList
endif

include ocidl.inc
include docobj.inc

SID_SkipHung		equ <IID_IEnumVARIANT>

externdef		__MIDL_itf_exdisp_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_exdisp_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __SHDocVw_LIBRARY_DEFINED__
__SHDocVw_LIBRARY_DEFINED__ equ 1

CommandStateChangeConstants typedef SDWORD
CSC_UPDATECOMMANDS	equ 0xffffffff
CSC_NAVIGATEFORWARD	equ 0x1
CSC_NAVIGATEBACK	equ 0x2

SecureLockIconConstants typedef SDWORD
secureLockIconUnsecure		equ 0
secureLockIconMixed		equ 0x1
secureLockIconSecureUnknownBits equ 0x2
secureLockIconSecure40Bit	equ 0x3
secureLockIconSecure56Bit	equ 0x4
secureLockIconSecureFortezza	equ 0x5
secureLockIconSecure128Bit	equ 0x6

NewProcessCauseConstants typedef SDWORD
ProtectedModeRedirect	equ 0x1

ShellWindowTypeConstants typedef SDWORD
SWC_EXPLORER		equ 0
SWC_BROWSER		equ 0x1
SWC_3RDPARTY		equ 0x2
SWC_CALLBACK		equ 0x4
SWC_DESKTOP		equ 0x8

ShellWindowFindWindowOptions typedef SDWORD
SWFO_NEEDDISPATCH	equ 0x1
SWFO_INCLUDEPENDING	equ 0x2
SWFO_COOKIEPASSED	equ 0x4


externdef		LIBID_SHDocVw:IID

ifndef __IWebBrowser_INTERFACE_DEFINED__
__IWebBrowser_INTERFACE_DEFINED__ equ 1


BrowserNavConstants	typedef SDWORD
navOpenInNewWindow	equ 0x1
navNoHistory		equ 0x2
navNoReadFromCache	equ 0x4
navNoWriteToCache	equ 0x8
navAllowAutosearch	equ 0x10
navBrowserBar		equ 0x20
navHyperlink		equ 0x40
navEnforceRestricted	equ 0x80
navNewWindowsManaged	equ 0x100
navUntrustedForDownload equ 0x200
navTrustedForActiveX	equ 0x400
navOpenInNewTab		equ 0x800
navOpenInBackgroundTab	equ 0x1000
navKeepWordWheelText	equ 0x2000
navVirtualTab		equ 0x4000
navBlockRedirectsXDomain equ 0x8000
navOpenNewForegroundTab equ 0x10000

RefreshConstants	typedef SDWORD
REFRESH_NORMAL		equ 0
REFRESH_IFEXPIRED	equ 1
REFRESH_COMPLETELY	equ 3

externdef		IID_IWebBrowser:IID

.comdef IWebBrowser
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    GoBack		proc
    GoForward		proc
    GoHome		proc
    GoSearch		proc
    Navigate		proc :BSTR, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    Refresh2		proc :ptr
    Stop		proc
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Container	proc :ptr
    get_Document	proc :ptr
    get_TopLevelContainer proc :ptr
    get_Type		proc :ptr
    get_Left		proc :ptr
    put_Left		proc :SDWORD
    get_Top		proc :ptr
    put_Top		proc :SDWORD
    get_Width		proc :ptr
    put_Width		proc :SDWORD
    get_Height		proc :ptr
    put_Height		proc :SDWORD
    get_LocationName	proc :ptr
    get_LocationURL	proc :ptr
    get_Busy		proc :ptr
    .ends

endif


ifndef __DWebBrowserEvents_DISPINTERFACE_DEFINED__
__DWebBrowserEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DWebBrowserEvents:IID
.comdef DWebBrowserEvents
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends

endif

ifndef __IWebBrowserApp_INTERFACE_DEFINED__
__IWebBrowserApp_INTERFACE_DEFINED__ equ 1


DEFINE_GUID(IID_IWebBrowserApp, 0x0002df05, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)

externdef		IID_IWebBrowserApp:IID
.comdef IWebBrowserApp
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    GoBack		proc
    GoForward		proc
    GoHome		proc
    GoSearch		proc
    Navigate		proc :BSTR, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    Refresh2		proc :ptr
    Stop		proc
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Container	proc :ptr
    get_Document	proc :ptr
    get_TopLevelContainer proc :ptr
    get_Type		proc :ptr
    get_Left		proc :ptr
    put_Left		proc :SDWORD
    get_Top		proc :ptr
    put_Top		proc :SDWORD
    get_Width		proc :ptr
    put_Width		proc :SDWORD
    get_Height		proc :ptr
    put_Height		proc :SDWORD
    get_LocationName	proc :ptr
    get_LocationURL	proc :ptr
    get_Busy		proc :ptr
    Quit		proc
    ClientToWindow	proc :ptr, :ptr
    PutProperty		proc :BSTR, :VARIANT
    GetProperty		proc :BSTR, :ptr
    get_Name		proc :ptr
    get_HWND		proc :ptr
    get_FullName	proc :ptr
    get_Path		proc :ptr
    get_Visible		proc :ptr
    put_Visible		proc :VARIANT_BOOL
    get_StatusBar	proc :ptr
    put_StatusBar	proc :VARIANT_BOOL
    get_StatusText	proc :ptr
    put_StatusText	proc :BSTR
    get_ToolBar		proc :ptr
    put_ToolBar		proc :DWORD
    get_MenuBar		proc :ptr
    put_MenuBar		proc :VARIANT_BOOL
    get_FullScreen	proc :ptr
    put_FullScreen	proc :VARIANT_BOOL
    .ends

endif

ifndef __IWebBrowser2_INTERFACE_DEFINED__
__IWebBrowser2_INTERFACE_DEFINED__ equ 1


externdef		IID_IWebBrowser2:IID
.comdef IWebBrowser2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    GoBack		proc
    GoForward		proc
    GoHome		proc
    GoSearch		proc
    Navigate		proc :BSTR, :ptr, :ptr, :ptr, :ptr
    Refresh		proc
    Refresh2		proc :ptr
    Stop		proc
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Container	proc :ptr
    get_Document	proc :ptr
    get_TopLevelContainer proc :ptr
    get_Type		proc :ptr
    get_Left		proc :ptr
    put_Left		proc :SDWORD
    get_Top		proc :ptr
    put_Top		proc :SDWORD
    get_Width		proc :ptr
    put_Width		proc :SDWORD
    get_Height		proc :ptr
    put_Height		proc :SDWORD
    get_LocationName	proc :ptr
    get_LocationURL	proc :ptr
    get_Busy		proc :ptr
    Quit		proc
    ClientToWindow	proc :ptr, :ptr
    PutProperty		proc :BSTR, :VARIANT
    GetProperty		proc :BSTR, :ptr
    get_Name		proc :ptr
    get_HWND		proc :ptr
    get_FullName	proc :ptr
    get_Path		proc :ptr BSTR
    get_Visible		proc :ptr
    put_Visible		proc :VARIANT_BOOL
    get_StatusBar	proc :ptr
    put_StatusBar	proc :VARIANT_BOOL
    get_StatusText	proc :ptr
    put_StatusText	proc :BSTR
    get_ToolBar		proc :ptr
    put_ToolBar		proc :DWORD
    get_MenuBar		proc :ptr
    put_MenuBar		proc :VARIANT_BOOL
    get_FullScreen	proc :ptr
    put_FullScreen	proc :VARIANT_BOOL
    Navigate2		proc :ptr, :ptr, :ptr, :ptr, :ptr
    QueryStatusWB	proc :OLECMDID, :ptr
    ExecWB		proc :OLECMDID, :OLECMDEXECOPT, :ptr, :ptr
    ShowBrowserBar	proc :ptr, :ptr, :ptr
    get_ReadyState	proc :ptr
    get_Offline		proc :ptr
    put_Offline		proc :VARIANT_BOOL
    get_Silent		proc :ptr
    put_Silent		proc :VARIANT_BOOL
    get_RegisterAsBrowser proc :ptr
    put_RegisterAsBrowser proc :VARIANT_BOOL
    get_RegisterAsDropTarget proc :ptr
    put_RegisterAsDropTarget proc :VARIANT_BOOL
    get_TheaterMode	proc :ptr
    put_TheaterMode	proc :VARIANT_BOOL
    get_AddressBar	proc :ptr
    put_AddressBar	proc :VARIANT_BOOL
    get_Resizable	proc :ptr
    put_Resizable	proc :VARIANT_BOOL
    .ends

endif

ifndef __DWebBrowserEvents2_DISPINTERFACE_DEFINED__
__DWebBrowserEvents2_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DWebBrowserEvents2:IID
.comdef DWebBrowserEvents2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends
endif

externdef		CLSID_WebBrowser_V1:CLSID
externdef		CLSID_WebBrowser:CLSID
externdef		CLSID_InternetExplorer:CLSID

ifndef __DShellWindowsEvents_DISPINTERFACE_DEFINED__
__DShellWindowsEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DShellWindowsEvents:IID
.comdef DShellWindowsEvents
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends

endif


ifndef __IShellWindows_INTERFACE_DEFINED__
__IShellWindows_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellWindows:IID
.comdef IShellWindows
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    Item		proc :VARIANT, :ptr
    _NewEnum		proc :ptr
    Register		proc :ptr, :SDWORD, :DWORD, :ptr
    RegisterPending	proc :SDWORD, :ptr, :ptr, :DWORD, :ptr
    Revoke		proc :SDWORD
    OnNavigate		proc :SDWORD, :ptr
    OnActivated		proc :SDWORD, :VARIANT_BOOL
    FindWindowSW	proc :ptr, :ptr, :DWORD, :ptr, :DWORD, :ptr
    OnCreated		proc :SDWORD, :ptr
    ProcessAttachDetach proc :VARIANT_BOOL
    .ends

endif

externdef		CLSID_ShellWindows:CLSID

ifndef __IShellUIHelper_INTERFACE_DEFINED__
__IShellUIHelper_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellUIHelper:IID
.comdef IShellUIHelper
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    ResetFirstBootMode	proc
    ResetSafeMode	proc
    RefreshOfflineDesktop proc
    AddFavorite		proc :BSTR, :ptr
    AddChannel		proc :BSTR
    AddDesktopComponent proc :BSTR, :BSTR, :ptr, :ptr, :ptr, :ptr
    IsSubscribed	proc :BSTR, :ptr
    NavigateAndFind	proc :BSTR, :BSTR, :ptr
    ImportExportFavorites proc :VARIANT_BOOL, :BSTR
    AutoCompleteSaveForm proc :ptr
    AutoScan		proc :BSTR, :BSTR, :ptr
    AutoCompleteAttach	proc :ptr
    ShowBrowserUI	proc :BSTR, :ptr, :ptr
    .ends

endif


ifndef __IShellUIHelper2_INTERFACE_DEFINED__
__IShellUIHelper2_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellUIHelper2:IID
.comdef IShellUIHelper2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    .ends

endif

ifndef __IShellUIHelper3_INTERFACE_DEFINED__
__IShellUIHelper3_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellUIHelper3:IID
.comdef IShellUIHelper3
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    ResetFirstBootMode	proc
    ResetSafeMode	proc
    RefreshOfflineDesktop proc
    AddFavorite		proc :BSTR, :ptr
    AddChannel		proc :BSTR
    AddDesktopComponent proc :BSTR, :BSTR, :ptr, :ptr, :ptr, :ptr
    IsSubscribed	proc :BSTR, :ptr
    NavigateAndFind	proc :BSTR, :BSTR, :ptr
    ImportExportFavorites proc :VARIANT_BOOL, :BSTR
    AutoCompleteSaveForm proc :ptr
    AutoScan		proc :BSTR, :BSTR, :ptr
    AutoCompleteAttach	proc :ptr
    ShowBrowserUI	proc :BSTR, :ptr, :ptr
    AddSearchProvider	proc :BSTR
    RunOnceShown	proc
    SkipRunOnce		proc
    CustomizeSettings	proc :VARIANT_BOOL, :VARIANT_BOOL
    SqmEnabled		proc :ptr
    PhishingEnabled	proc :ptr
    BrandImageUri	proc :ptr
    SkipTabsWelcome	proc
    DiagnoseConnection	proc
    CustomizeClearType	proc :VARIANT_BOOL
    IsSearchProviderInstalled proc :BSTR, :ptr
    IsSearchMigrated	proc :ptr
    DefaultSearchProvider proc :ptr
    RunOnceRequiredSettingsComplete proc :VARIANT_BOOL
    RunOnceHasShown	proc :ptr
    SearchGuideUrl	proc :ptr
    AddService		proc :BSTR
    IsServiceInstalled	proc :BSTR, :BSTR, :ptr
    InPrivateFilteringEnabled proc :ptr
    AddToFavoritesBar	proc :BSTR, :BSTR, :ptr
    BuildNewTabPage	proc
    SetRecentlyClosedVisible proc :VARIANT_BOOL
    SetActivitiesVisible proc :VARIANT_BOOL
    ContentDiscoveryResetSTDMETHOD proc
    IsSuggestedSitesEnabled proc :ptr
    EnableSuggestedSites proc :VARIANT_BOOL
    NavigateToSuggestedSites proc :BSTR
    ShowTabsHelp	proc
    ShowInPrivateHelp	proc
    .ends

endif

externdef		CLSID_ShellUIHelper:CLSID

ifndef __DShellNameSpaceEvents_DISPINTERFACE_DEFINED__
__DShellNameSpaceEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DShellNameSpaceEvents:IID
.comdef DShellNameSpaceEvents
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends

endif


ifndef __IShellFavoritesNameSpace_INTERFACE_DEFINED__
__IShellFavoritesNameSpace_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFavoritesNameSpace:IID
.comdef IShellFavoritesNameSpace
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    MoveSelectionUp	proc
    MoveSelectionDown	proc
    ResetSort		proc
    NewFolder		proc
    Synchronize		proc
    Import		proc
    Export		proc
    InvokeContextMenuCommand proc :BSTR
    MoveSelectionTo	proc
    get_SubscriptionsEnabled proc :ptr
    CreateSubscriptionForSelection proc :ptr
    DeleteSubscriptionForSelection proc :ptr
    SetRoot		proc :BSTR
    .ends

endif


ifndef __IShellNameSpace_INTERFACE_DEFINED__
__IShellNameSpace_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellNameSpace:IID
.comdef IShellNameSpace
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    MoveSelectionUp	proc
    MoveSelectionDown	proc
    ResetSort		proc
    NewFolder		proc
    Synchronize		proc
    Import		proc
    Export		proc
    InvokeContextMenuCommand proc :BSTR
    MoveSelectionTo	proc
    get_SubscriptionsEnabled proc :ptr
    CreateSubscriptionForSelection proc :ptr
    DeleteSubscriptionForSelection proc :ptr
    SetRoot		proc :BSTR
    get_EnumOptions	proc :ptr
    put_EnumOptions	proc :SDWORD
    get_SelectedItem	proc :ptr
    put_SelectedItem	proc :ptr
    get_Root		proc :ptr
    put_Root		proc :VARIANT
    get_Depth		proc :ptr
    put_Depth		proc :DWORD
    get_Mode		proc :ptr
    put_Mode		proc :DWORD
    get_Flags		proc :ptr
    put_Flags		proc :DWORD
    put_TVFlags		proc :DWORD
    get_TVFlags		proc :ptr
    get_Columns		proc :ptr
    put_Columns		proc :BSTR
    get_CountViewTypes	proc :ptr
    SetViewType		proc :DWORD
    SelectedItems	proc :ptr
    Expand		proc :VARIANT, :DWORD
    UnselectAll		proc
    .ends

endif

externdef		CLSID_ShellNameSpace:CLSID

ifndef __IScriptErrorList_INTERFACE_DEFINED__
__IScriptErrorList_INTERFACE_DEFINED__ equ 1


externdef		IID_IScriptErrorList:IID
.comdef IScriptErrorList
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :DWORD, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :DWORD, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    advanceError	proc
    retreatError	proc
    canAdvanceError	proc :ptr
    canRetreatError	proc :ptr
    getErrorLine	proc :ptr
    getErrorChar	proc :ptr
    getErrorCode	proc :ptr
    getErrorMsg		proc :ptr
    getErrorUrl		proc :ptr
    getAlwaysShowLockState proc :ptr
    getDetailsPaneOpen	proc :ptr
    setDetailsPaneOpen	proc :BOOL
    getPerErrorDisplay	proc :ptr
    setPerErrorDisplay	proc :BOOL
    .ends

endif

externdef		CLSID_CScriptErrorList:CLSID

endif ; __SHDocVw_LIBRARY_DEFINED__

endif
.pragma list(pop)
