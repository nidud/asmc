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

ifndef __SHDocVw_LIBRARY_DEFINED__
__SHDocVw_LIBRARY_DEFINED__ equ 1

.enum CommandStateChangeConstants {
	CSC_UPDATECOMMANDS	= 0xffffffff,
	CSC_NAVIGATEFORWARD	= 0x1,
	CSC_NAVIGATEBACK	= 0x2
    }

.enum SecureLockIconConstants {
	secureLockIconUnsecure	= 0,
	secureLockIconMixed	= 0x1,
	secureLockIconSecureUnknownBits = 0x2,
	secureLockIconSecure40Bit	= 0x3,
	secureLockIconSecure56Bit	= 0x4,
	secureLockIconSecureFortezza	= 0x5,
	secureLockIconSecure128Bit	= 0x6
    }

.enum NewProcessCauseConstants {
	ProtectedModeRedirect	= 0x1
    }

.enum ShellWindowTypeConstants {
	SWC_EXPLORER	= 0,
	SWC_BROWSER	= 0x1,
	SWC_3RDPARTY	= 0x2,
	SWC_CALLBACK	= 0x4,
	SWC_DESKTOP	= 0x8
    }

.enum ShellWindowFindWindowOptions {
	SWFO_NEEDDISPATCH	= 0x1,
	SWFO_INCLUDEPENDING	= 0x2,
	SWFO_COOKIEPASSED	= 0x4
    }

externdef LIBID_SHDocVw:IID

ifndef __IWebBrowser_INTERFACE_DEFINED__
__IWebBrowser_INTERFACE_DEFINED__ equ 1

.enum BrowserNavConstants {
	navOpenInNewWindow	= 0x1,
	navNoHistory		= 0x2,
	navNoReadFromCache	= 0x4,
	navNoWriteToCache	= 0x8,
	navAllowAutosearch	= 0x10,
	navBrowserBar		= 0x20,
	navHyperlink		= 0x40,
	navEnforceRestricted	= 0x80,
	navNewWindowsManaged	= 0x100,
	navUntrustedForDownload = 0x200,
	navTrustedForActiveX	= 0x400,
	navOpenInNewTab		= 0x800,
	navOpenInBackgroundTab	= 0x1000,
	navKeepWordWheelText	= 0x2000,
	navVirtualTab		= 0x4000,
	navBlockRedirectsXDomain = 0x8000,
	navOpenNewForegroundTab = 0x10000
    }

.enum RefreshConstants {
	REFRESH_NORMAL		= 0,
	REFRESH_IFEXPIRED	= 1,
	REFRESH_COMPLETELY	= 3
    }

DEFINE_IIDX(IWebBrowser, "EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B")

.comdef IWebBrowser : public IDispatch

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


DEFINE_IIDX(DWebBrowserEvents,"EAB22AC2-30C1-11CF-A7EB-0000C05BAE0B")

.comdef DWebBrowserEvents : public IDispatch

    .ends

endif

ifndef __IWebBrowserApp_INTERFACE_DEFINED__
__IWebBrowserApp_INTERFACE_DEFINED__ equ 1

DEFINE_GUID(IID_IWebBrowserApp, 0x0002df05, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)

.comdef IWebBrowserApp : public IWebBrowser

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

DEFINE_IIDX(IWebBrowser2, "D30C1661-CDAF-11d0-8A3E-00C04FC9E26E")

.comdef IWebBrowser2 : public IWebBrowserApp

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

DEFINE_GUIDS(DIID_DWebBrowserEvents2, "34A715A0-6587-11D0-924A-0020AFC7AC4D")

.comdef DWebBrowserEvents2 : public IDispatch

    .ends
endif

DEFINE_GUIDS(CLSID_WebBrowser_V1,    "EAB22AC3-30C1-11CF-A7EB-0000C05BAE0B")
DEFINE_GUIDS(CLSID_WebBrowser,	     "8856F961-340A-11D0-A96B-00C04FD705A2")
DEFINE_GUIDS(CLSID_InternetExplorer, "0002DF01-0000-0000-C000-000000000046")

ifndef __DShellWindowsEvents_DISPINTERFACE_DEFINED__
__DShellWindowsEvents_DISPINTERFACE_DEFINED__ equ 1

DEFINE_GUIDS(DIID_DShellWindowsEvents, "fe4106e0-399a-11d0-a48c-00a0c90a8f39")

.comdef DShellWindowsEvents : public IDispatch

    .ends
endif


ifndef __IShellWindows_INTERFACE_DEFINED__
__IShellWindows_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellWindows, "85CB6900-4D95-11CF-960C-0080C7F4EE85")

.comdef IShellWindows : public IDispatch

    get_Count		proc :ptr
    Item		proc :VARIANT, :ptr
    NewEnum		proc :ptr
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

DEFINE_GUIDS(CLSID_ShellWindows, "9BA05972-F6A8-11CF-A442-00A0C90A8F39")

ifndef __IShellUIHelper_INTERFACE_DEFINED__
__IShellUIHelper_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellUIHelper, "729FE2F8-1EA8-11d1-8F85-00C04FC2FBE1")

.comdef IShellUIHelper : public IDispatch

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

DEFINE_IIDX(IShellUIHelper2, "a7fe6eda-1932-4281-b881-87b31b8bc52c")

.comdef IShellUIHelper2 : public IShellUIHelper

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

    .ends

endif

ifndef __IShellUIHelper3_INTERFACE_DEFINED__
__IShellUIHelper3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellUIHelper3, "528DF2EC-D419-40bc-9B6D-DCDBF9C1B25D")

.comdef IShellUIHelper3 : public IShellUIHelper2

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

ifndef __IShellUIHelper4_INTERFACE_DEFINED__
__IShellUIHelper4_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellUIHelper4, "B36E6A53-8073-499E-824C-D776330A333E")

.comdef IShellUIHelper4 : public IShellUIHelper3

    msIsSiteMode	proc :ptr
    msSiteModeShowThumbBar proc
    msSiteModeAddThumbBarButton proc :BSTR, :BSTR, :ptr
    msSiteModeUpdateThumbBarButton proc :VARIANT, :VARIANT_BOOL, :VARIANT_BOOL
    msSiteModeSetIconOverlay proc :BSTR, :ptr VARIANT
    msSiteModeClearIconOverlay proc
    msAddSiteMode	proc
    msSiteModeCreateJumpList proc :BSTR
    msSiteModeAddJumpListItem proc :BSTR, :BSTR, :BSTR, :ptr VARIANT
    msSiteModeClearJumpList proc
    msSiteModeShowJumpList proc
    msSiteModeAddButtonStyle proc :VARIANT, :BSTR, :BSTR, :ptr VARIANT
    msSiteModeShowButtonStyle proc :VARIANT, :VARIANT
    msSiteModeActivate	proc
    msIsSiteModeFirstRun proc :VARIANT_BOOL, :ptr VARIANT
    msAddTrackingProtectionList proc :BSTR, :BSTR
    msTrackingProtectionEnabled proc :ptr VARIANT_BOOL
    msActiveXFilteringEnabled proc :ptr VARIANT_BOOL

    .ends

endif

ifndef __IShellUIHelper5_INTERFACE_DEFINED__
__IShellUIHelper5_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellUIHelper5, "A2A08B09-103D-4D3F-B91C-EA455CA82EFA")

.comdef IShellUIHelper5 : public IShellUIHelper4

    msProvisionNetworks proc :BSTR, :ptr VARIANT
    msReportSafeUrl  proc
    msSiteModeRefreshBadge  proc
    msSiteModeClearBadge  proc
    msDiagnoseConnectionUILess	proc
    msLaunchNetworkClientHelp  proc
    msChangeDefaultBrowser proc :VARIANT_BOOL

    .ends

endif

DEFINE_GUIDS(CLSID_ShellUIHelper, "64AB4BB7-111E-11d1-8F79-00C04FC2FBE1")

ifndef __DShellNameSpaceEvents_DISPINTERFACE_DEFINED__
__DShellNameSpaceEvents_DISPINTERFACE_DEFINED__ equ 1

DEFINE_GUIDS(DIID_DShellNameSpaceEvents, "55136806-B2DE-11D1-B9F2-00A0C98BC547")

.comdef DShellNameSpaceEvents : public IDispatch

    .ends

endif


ifndef __IShellFavoritesNameSpace_INTERFACE_DEFINED__
__IShellFavoritesNameSpace_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellFavoritesNameSpace, "55136804-B2DE-11D1-B9F2-00A0C98BC547")

.comdef IShellFavoritesNameSpace : public IDispatch

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

DEFINE_IIDX(IShellNameSpace, "e572d3c9-37be-4ae2-825d-d521763e3108")

.comdef IShellNameSpace : public IShellFavoritesNameSpace

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

DEFINE_GUIDS(CLSID_ShellNameSpace, "55136805-B2DE-11D1-B9F2-00A0C98BC547")

ifndef __IScriptErrorList_INTERFACE_DEFINED__
__IScriptErrorList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IScriptErrorList, "F3470F24-15FD-11d2-BB2E-00805FF7EFCA")

.comdef IScriptErrorList : public IDispatch

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

DEFINE_GUIDS(CLSID_CScriptErrorList, "EFD01300-160F-11d2-BB2E-00805FF7EFCA")

endif ; __SHDocVw_LIBRARY_DEFINED__

endif
.pragma list(pop)
