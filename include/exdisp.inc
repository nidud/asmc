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
.xlist

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
.xlist

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

IWebBrowser		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	GoBack
	STDMETHOD	GoForward
	STDMETHOD	GoHome
	STDMETHOD	GoSearch
	STDMETHOD	Navigate, :BSTR, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	Refresh
	STDMETHOD	Refresh2, :ptr
	STDMETHOD	Stop
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Container, :ptr
	STDMETHOD	get_Document, :ptr
	STDMETHOD	get_TopLevelContainer, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	get_Left, :ptr
	STDMETHOD	put_Left, :SDWORD
	STDMETHOD	get_Top, :ptr
	STDMETHOD	put_Top, :SDWORD
	STDMETHOD	get_Width, :ptr
	STDMETHOD	put_Width, :SDWORD
	STDMETHOD	get_Height, :ptr
	STDMETHOD	put_Height, :SDWORD
	STDMETHOD	get_LocationName, :ptr
	STDMETHOD	get_LocationURL, :ptr
	STDMETHOD	get_Busy, :ptr
IWebBrowser		ENDS

endif


ifndef __DWebBrowserEvents_DISPINTERFACE_DEFINED__
__DWebBrowserEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DWebBrowserEvents:IID
DWebBrowserEvents	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
DWebBrowserEvents	ENDS

endif

ifndef __IWebBrowserApp_INTERFACE_DEFINED__
__IWebBrowserApp_INTERFACE_DEFINED__ equ 1


DEFINE_GUID(IID_IWebBrowserApp, 0x0002df05, 0x0000, 0x0000, 0xc0,0x00, 0x00,0x00,0x00,0x00,0x00,0x46)

externdef		IID_IWebBrowserApp:IID
IWebBrowserApp		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	GoBack
	STDMETHOD	GoForward
	STDMETHOD	GoHome
	STDMETHOD	GoSearch
	STDMETHOD	Navigate, :BSTR, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	Refresh
	STDMETHOD	Refresh2, :ptr
	STDMETHOD	Stop
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Container, :ptr
	STDMETHOD	get_Document, :ptr
	STDMETHOD	get_TopLevelContainer, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	get_Left, :ptr
	STDMETHOD	put_Left, :SDWORD
	STDMETHOD	get_Top, :ptr
	STDMETHOD	put_Top, :SDWORD
	STDMETHOD	get_Width, :ptr
	STDMETHOD	put_Width, :SDWORD
	STDMETHOD	get_Height, :ptr
	STDMETHOD	put_Height, :SDWORD
	STDMETHOD	get_LocationName, :ptr
	STDMETHOD	get_LocationURL, :ptr
	STDMETHOD	get_Busy, :ptr
	STDMETHOD	Quit
	STDMETHOD	ClientToWindow, :ptr, :ptr
	STDMETHOD	PutProperty, :BSTR, :VARIANT
	STDMETHOD	GetProperty, :BSTR, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_HWND, :ptr
	STDMETHOD	get_FullName, :ptr
	STDMETHOD	get_Path, :ptr
	STDMETHOD	get_Visible, :ptr
	STDMETHOD	put_Visible, :VARIANT_BOOL
	STDMETHOD	get_StatusBar, :ptr
	STDMETHOD	put_StatusBar, :VARIANT_BOOL
	STDMETHOD	get_StatusText, :ptr
	STDMETHOD	put_StatusText, :BSTR
	STDMETHOD	get_ToolBar, :ptr
	STDMETHOD	put_ToolBar, :DWORD
	STDMETHOD	get_MenuBar, :ptr
	STDMETHOD	put_MenuBar, :VARIANT_BOOL
	STDMETHOD	get_FullScreen, :ptr
	STDMETHOD	put_FullScreen, :VARIANT_BOOL
IWebBrowserApp		ENDS

endif

ifndef __IWebBrowser2_INTERFACE_DEFINED__
__IWebBrowser2_INTERFACE_DEFINED__ equ 1


externdef		IID_IWebBrowser2:IID
IWebBrowser2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	GoBack
	STDMETHOD	GoForward
	STDMETHOD	GoHome
	STDMETHOD	GoSearch
	STDMETHOD	Navigate, :BSTR, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	Refresh
	STDMETHOD	Refresh2, :ptr
	STDMETHOD	Stop
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Container, :ptr
	STDMETHOD	get_Document, :ptr
	STDMETHOD	get_TopLevelContainer, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	get_Left, :ptr
	STDMETHOD	put_Left, :SDWORD
	STDMETHOD	get_Top, :ptr
	STDMETHOD	put_Top, :SDWORD
	STDMETHOD	get_Width, :ptr
	STDMETHOD	put_Width, :SDWORD
	STDMETHOD	get_Height, :ptr
	STDMETHOD	put_Height, :SDWORD
	STDMETHOD	get_LocationName, :ptr
	STDMETHOD	get_LocationURL, :ptr
	STDMETHOD	get_Busy, :ptr
	STDMETHOD	Quit
	STDMETHOD	ClientToWindow, :ptr, :ptr
	STDMETHOD	PutProperty, :BSTR, :VARIANT
	STDMETHOD	GetProperty, :BSTR, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_HWND, :ptr
	STDMETHOD	get_FullName, :ptr
	STDMETHOD	get_Path, :ptr BSTR
	STDMETHOD	get_Visible, :ptr
	STDMETHOD	put_Visible, :VARIANT_BOOL
	STDMETHOD	get_StatusBar, :ptr
	STDMETHOD	put_StatusBar, :VARIANT_BOOL
	STDMETHOD	get_StatusText, :ptr
	STDMETHOD	put_StatusText, :BSTR
	STDMETHOD	get_ToolBar, :ptr
	STDMETHOD	put_ToolBar, :DWORD
	STDMETHOD	get_MenuBar, :ptr
	STDMETHOD	put_MenuBar, :VARIANT_BOOL
	STDMETHOD	get_FullScreen, :ptr
	STDMETHOD	put_FullScreen, :VARIANT_BOOL
	STDMETHOD	Navigate2, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	QueryStatusWB, :OLECMDID, :ptr
	STDMETHOD	ExecWB, :OLECMDID, :OLECMDEXECOPT, :ptr, :ptr
	STDMETHOD	ShowBrowserBar, :ptr, :ptr, :ptr
	STDMETHOD	get_ReadyState, :ptr
	STDMETHOD	get_Offline, :ptr
	STDMETHOD	put_Offline, :VARIANT_BOOL
	STDMETHOD	get_Silent, :ptr
	STDMETHOD	put_Silent, :VARIANT_BOOL
	STDMETHOD	get_RegisterAsBrowser, :ptr
	STDMETHOD	put_RegisterAsBrowser, :VARIANT_BOOL
	STDMETHOD	get_RegisterAsDropTarget, :ptr
	STDMETHOD	put_RegisterAsDropTarget, :VARIANT_BOOL
	STDMETHOD	get_TheaterMode, :ptr
	STDMETHOD	put_TheaterMode, :VARIANT_BOOL
	STDMETHOD	get_AddressBar, :ptr
	STDMETHOD	put_AddressBar, :VARIANT_BOOL
	STDMETHOD	get_Resizable, :ptr
	STDMETHOD	put_Resizable, :VARIANT_BOOL
IWebBrowser2		ENDS

endif

ifndef __DWebBrowserEvents2_DISPINTERFACE_DEFINED__
__DWebBrowserEvents2_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DWebBrowserEvents2:IID
DWebBrowserEvents2	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames,:REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
DWebBrowserEvents2	ENDS
endif

externdef		CLSID_WebBrowser_V1:CLSID
externdef		CLSID_WebBrowser:CLSID
externdef		CLSID_InternetExplorer:CLSID

ifndef __DShellWindowsEvents_DISPINTERFACE_DEFINED__
__DShellWindowsEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DShellWindowsEvents:IID
DShellWindowsEvents	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
DShellWindowsEvents	ENDS

endif


ifndef __IShellWindows_INTERFACE_DEFINED__
__IShellWindows_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellWindows:IID
IShellWindows		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	Item, :VARIANT, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	Register, :ptr, :SDWORD, :DWORD, :ptr
	STDMETHOD	RegisterPending, :SDWORD, :ptr, :ptr, :DWORD, :ptr
	STDMETHOD	Revoke, :SDWORD
	STDMETHOD	OnNavigate, :SDWORD, :ptr
	STDMETHOD	OnActivated, :SDWORD, :VARIANT_BOOL
	STDMETHOD	FindWindowSW, :ptr, :ptr, :DWORD, :ptr, :DWORD, :ptr
	STDMETHOD	OnCreated, :SDWORD, :ptr
	STDMETHOD	ProcessAttachDetach, :VARIANT_BOOL
IShellWindows		ENDS

endif

externdef		CLSID_ShellWindows:CLSID

ifndef __IShellUIHelper_INTERFACE_DEFINED__
__IShellUIHelper_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellUIHelper:IID
IShellUIHelper		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	ResetFirstBootMode
	STDMETHOD	ResetSafeMode
	STDMETHOD	RefreshOfflineDesktop
	STDMETHOD	AddFavorite, :BSTR, :ptr
	STDMETHOD	AddChannel, :BSTR
	STDMETHOD	AddDesktopComponent, :BSTR, :BSTR, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	IsSubscribed, :BSTR, :ptr
	STDMETHOD	NavigateAndFind, :BSTR, :BSTR, :ptr
	STDMETHOD	ImportExportFavorites, :VARIANT_BOOL, :BSTR
	STDMETHOD	AutoCompleteSaveForm, :ptr
	STDMETHOD	AutoScan, :BSTR, :BSTR, :ptr
	STDMETHOD	AutoCompleteAttach, :ptr
	STDMETHOD	ShowBrowserUI, :BSTR, :ptr, :ptr
IShellUIHelperVtbl	ENDS

endif


ifndef __IShellUIHelper2_INTERFACE_DEFINED__
__IShellUIHelper2_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellUIHelper2:IID
IShellUIHelper2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
IShellUIHelper2		ENDS

endif

ifndef __IShellUIHelper3_INTERFACE_DEFINED__
__IShellUIHelper3_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellUIHelper3:IID
IShellUIHelper3		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	ResetFirstBootMode
	STDMETHOD	ResetSafeMode
	STDMETHOD	RefreshOfflineDesktop
	STDMETHOD	AddFavorite, :BSTR, :ptr
	STDMETHOD	AddChannel, :BSTR
	STDMETHOD	AddDesktopComponent, :BSTR, :BSTR, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	IsSubscribed, :BSTR, :ptr
	STDMETHOD	NavigateAndFind, :BSTR, :BSTR, :ptr
	STDMETHOD	ImportExportFavorites, :VARIANT_BOOL, :BSTR
	STDMETHOD	AutoCompleteSaveForm, :ptr
	STDMETHOD	AutoScan, :BSTR, :BSTR, :ptr
	STDMETHOD	AutoCompleteAttach, :ptr
	STDMETHOD	ShowBrowserUI, :BSTR, :ptr, :ptr
	STDMETHOD	AddSearchProvider, :BSTR
	STDMETHOD	RunOnceShown
	STDMETHOD	SkipRunOnce
	STDMETHOD	CustomizeSettings, :VARIANT_BOOL, :VARIANT_BOOL
	STDMETHOD	SqmEnabled, :ptr
	STDMETHOD	PhishingEnabled, :ptr
	STDMETHOD	BrandImageUri, :ptr
	STDMETHOD	SkipTabsWelcome
	STDMETHOD	DiagnoseConnection
	STDMETHOD	CustomizeClearType, :VARIANT_BOOL
	STDMETHOD	IsSearchProviderInstalled, :BSTR, :ptr
	STDMETHOD	IsSearchMigrated, :ptr
	STDMETHOD	DefaultSearchProvider, :ptr
	STDMETHOD	RunOnceRequiredSettingsComplete, :VARIANT_BOOL
	STDMETHOD	RunOnceHasShown, :ptr
	STDMETHOD	SearchGuideUrl, :ptr
	STDMETHOD	AddService, :BSTR
	STDMETHOD	IsServiceInstalled, :BSTR, :BSTR, :ptr
	STDMETHOD	InPrivateFilteringEnabled, :ptr
	STDMETHOD	AddToFavoritesBar, :BSTR, :BSTR, :ptr
	STDMETHOD	BuildNewTabPage
	STDMETHOD	SetRecentlyClosedVisible, :VARIANT_BOOL
	STDMETHOD	SetActivitiesVisible, :VARIANT_BOOL
	STDMETHOD	ContentDiscoveryResetSTDMETHOD
	STDMETHOD	IsSuggestedSitesEnabled, :ptr
	STDMETHOD	EnableSuggestedSites, :VARIANT_BOOL
	STDMETHOD	NavigateToSuggestedSites, :BSTR
	STDMETHOD	ShowTabsHelp
	STDMETHOD	ShowInPrivateHelp
IShellUIHelper3		ENDS

endif

externdef		CLSID_ShellUIHelper:CLSID

ifndef __DShellNameSpaceEvents_DISPINTERFACE_DEFINED__
__DShellNameSpaceEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DShellNameSpaceEvents:IID
DShellNameSpaceEvents	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
DShellNameSpaceEvents	ENDS

endif


ifndef __IShellFavoritesNameSpace_INTERFACE_DEFINED__
__IShellFavoritesNameSpace_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFavoritesNameSpace:IID
IShellFavoritesNameSpace STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	MoveSelectionUp
	STDMETHOD	MoveSelectionDown
	STDMETHOD	ResetSort
	STDMETHOD	NewFolder
	STDMETHOD	Synchronize
	STDMETHOD	Import
	STDMETHOD	Export
	STDMETHOD	InvokeContextMenuCommand, :BSTR
	STDMETHOD	MoveSelectionTo
	STDMETHOD	get_SubscriptionsEnabled, :ptr
	STDMETHOD	CreateSubscriptionForSelection, :ptr
	STDMETHOD	DeleteSubscriptionForSelection, :ptr
	STDMETHOD	SetRoot, :BSTR
IShellFavoritesNameSpace ENDS

endif


ifndef __IShellNameSpace_INTERFACE_DEFINED__
__IShellNameSpace_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellNameSpace:IID
IShellNameSpace		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	MoveSelectionUp
	STDMETHOD	MoveSelectionDown
	STDMETHOD	ResetSort
	STDMETHOD	NewFolder
	STDMETHOD	Synchronize
	STDMETHOD	Import
	STDMETHOD	Export
	STDMETHOD	InvokeContextMenuCommand, :BSTR
	STDMETHOD	MoveSelectionTo
	STDMETHOD	get_SubscriptionsEnabled, :ptr
	STDMETHOD	CreateSubscriptionForSelection, :ptr
	STDMETHOD	DeleteSubscriptionForSelection, :ptr
	STDMETHOD	SetRoot, :BSTR
	STDMETHOD	get_EnumOptions, :ptr
	STDMETHOD	put_EnumOptions, :SDWORD
	STDMETHOD	get_SelectedItem, :ptr
	STDMETHOD	put_SelectedItem, :ptr
	STDMETHOD	get_Root, :ptr
	STDMETHOD	put_Root, :VARIANT
	STDMETHOD	get_Depth, :ptr
	STDMETHOD	put_Depth, :DWORD
	STDMETHOD	get_Mode, :ptr
	STDMETHOD	put_Mode, :DWORD
	STDMETHOD	get_Flags, :ptr
	STDMETHOD	put_Flags, :DWORD
	STDMETHOD	put_TVFlags, :DWORD
	STDMETHOD	get_TVFlags, :ptr
	STDMETHOD	get_Columns, :ptr
	STDMETHOD	put_Columns, :BSTR
	STDMETHOD	get_CountViewTypes, :ptr
	STDMETHOD	SetViewType, :DWORD
	STDMETHOD	SelectedItems, :ptr
	STDMETHOD	Expand, :VARIANT, :DWORD
	STDMETHOD	UnselectAll
IShellNameSpace		ENDS

endif

externdef		CLSID_ShellNameSpace:CLSID

ifndef __IScriptErrorList_INTERFACE_DEFINED__
__IScriptErrorList_INTERFACE_DEFINED__ equ 1


externdef		IID_IScriptErrorList:IID
IScriptErrorList	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :DWORD, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	advanceError
	STDMETHOD	retreatError
	STDMETHOD	canAdvanceError, :ptr
	STDMETHOD	canRetreatError, :ptr
	STDMETHOD	getErrorLine, :ptr
	STDMETHOD	getErrorChar, :ptr
	STDMETHOD	getErrorCode, :ptr
	STDMETHOD	getErrorMsg, :ptr
	STDMETHOD	getErrorUrl, :ptr
	STDMETHOD	getAlwaysShowLockState, :ptr
	STDMETHOD	getDetailsPaneOpen, :ptr
	STDMETHOD	setDetailsPaneOpen, :BOOL
	STDMETHOD	getPerErrorDisplay, :ptr
	STDMETHOD	setPerErrorDisplay, :BOOL
IScriptErrorList	ENDS

endif

externdef		CLSID_CScriptErrorList:CLSID

endif ; __SHDocVw_LIBRARY_DEFINED__

.list
endif ; __exdisp_h__
