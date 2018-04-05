ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __mmc_h__
__mmc_h__ equ 1
.xlist

ifndef __IComponentData_FWD_DEFINED__
__IComponentData_FWD_DEFINED__ equ 1
endif
ifndef __IComponent_FWD_DEFINED__
__IComponent_FWD_DEFINED__ equ 1
endif
ifndef __IResultDataCompare_FWD_DEFINED__
__IResultDataCompare_FWD_DEFINED__ equ 1
endif
ifndef __IResultOwnerData_FWD_DEFINED__
__IResultOwnerData_FWD_DEFINED__ equ 1
endif
ifndef __IConsole_FWD_DEFINED__
__IConsole_FWD_DEFINED__ equ 1
endif
ifndef __IHeaderCtrl_FWD_DEFINED__
__IHeaderCtrl_FWD_DEFINED__ equ 1
endif
ifndef __IContextMenuCallback_FWD_DEFINED__
__IContextMenuCallback_FWD_DEFINED__ equ 1
endif
ifndef __IContextMenuProvider_FWD_DEFINED__
__IContextMenuProvider_FWD_DEFINED__ equ 1
endif
ifndef __IExtendContextMenu_FWD_DEFINED__
__IExtendContextMenu_FWD_DEFINED__ equ 1
endif
ifndef __IImageList_FWD_DEFINED__
__IImageList_FWD_DEFINED__ equ 1
endif
ifndef __IResultData_FWD_DEFINED__
__IResultData_FWD_DEFINED__ equ 1
endif
ifndef __IConsoleNameSpace_FWD_DEFINED__
__IConsoleNameSpace_FWD_DEFINED__ equ 1
endif
ifndef __IConsoleNameSpace2_FWD_DEFINED__
__IConsoleNameSpace2_FWD_DEFINED__ equ 1
endif
ifndef __IPropertySheetCallback_FWD_DEFINED__
__IPropertySheetCallback_FWD_DEFINED__ equ 1
endif
ifndef __IPropertySheetProvider_FWD_DEFINED__
__IPropertySheetProvider_FWD_DEFINED__ equ 1
endif
ifndef __IExtendPropertySheet_FWD_DEFINED__
__IExtendPropertySheet_FWD_DEFINED__ equ 1
endif
ifndef __IControlbar_FWD_DEFINED__
__IControlbar_FWD_DEFINED__ equ 1
endif
ifndef __IExtendControlbar_FWD_DEFINED__
__IExtendControlbar_FWD_DEFINED__ equ 1
endif
ifndef __IToolbar_FWD_DEFINED__
__IToolbar_FWD_DEFINED__ equ 1
endif
ifndef __IConsoleVerb_FWD_DEFINED__
__IConsoleVerb_FWD_DEFINED__ equ 1
endif
ifndef __ISnapinAbout_FWD_DEFINED__
__ISnapinAbout_FWD_DEFINED__ equ 1
endif
ifndef __IMenuButton_FWD_DEFINED__
__IMenuButton_FWD_DEFINED__ equ 1
endif
ifndef __ISnapinHelp_FWD_DEFINED__
__ISnapinHelp_FWD_DEFINED__ equ 1
endif
ifndef __IExtendPropertySheet2_FWD_DEFINED__
__IExtendPropertySheet2_FWD_DEFINED__ equ 1
endif
ifndef __IHeaderCtrl2_FWD_DEFINED__
__IHeaderCtrl2_FWD_DEFINED__ equ 1
endif
ifndef __ISnapinHelp2_FWD_DEFINED__
__ISnapinHelp2_FWD_DEFINED__ equ 1
endif
ifndef __IEnumTASK_FWD_DEFINED__
__IEnumTASK_FWD_DEFINED__ equ 1
endif
ifndef __IExtendTaskPad_FWD_DEFINED__
__IExtendTaskPad_FWD_DEFINED__ equ 1
endif
ifndef __IConsole2_FWD_DEFINED__
__IConsole2_FWD_DEFINED__ equ 1
endif
ifndef __IDisplayHelp_FWD_DEFINED__
__IDisplayHelp_FWD_DEFINED__ equ 1
endif
ifndef __IRequiredExtensions_FWD_DEFINED__
__IRequiredExtensions_FWD_DEFINED__ equ 1
endif
ifndef __IStringTable_FWD_DEFINED__
__IStringTable_FWD_DEFINED__ equ 1
endif
ifndef __IColumnData_FWD_DEFINED__
__IColumnData_FWD_DEFINED__ equ 1
endif
ifndef __IMessageView_FWD_DEFINED__
__IMessageView_FWD_DEFINED__ equ 1
endif
ifndef __IResultDataCompareEx_FWD_DEFINED__
__IResultDataCompareEx_FWD_DEFINED__ equ 1
endif
ifndef __IComponentData2_FWD_DEFINED__
__IComponentData2_FWD_DEFINED__ equ 1
endif
ifndef __IComponent2_FWD_DEFINED__
__IComponent2_FWD_DEFINED__ equ 1
endif
ifndef __IContextMenuCallback2_FWD_DEFINED__
__IContextMenuCallback2_FWD_DEFINED__ equ 1
endif
ifndef __IMMCVersionInfo_FWD_DEFINED__
__IMMCVersionInfo_FWD_DEFINED__ equ 1
endif
ifndef __MMCVersionInfo_FWD_DEFINED__
__MMCVersionInfo_FWD_DEFINED__ equ 1
MMCVersionInfo typedef MMCVersionInfo
endif
ifndef __ConsolePower_FWD_DEFINED__
__ConsolePower_FWD_DEFINED__ equ 1
;ConsolePower typedef ConsolePower
endif
ifndef __IExtendView_FWD_DEFINED__
__IExtendView_FWD_DEFINED__ equ 1
endif
ifndef __IViewExtensionCallback_FWD_DEFINED__
__IViewExtensionCallback_FWD_DEFINED__ equ 1
endif
ifndef __IConsolePower_FWD_DEFINED__
__IConsolePower_FWD_DEFINED__ equ 1
endif
ifndef __IConsolePowerSink_FWD_DEFINED__
__IConsolePowerSink_FWD_DEFINED__ equ 1
endif
ifndef __INodeProperties_FWD_DEFINED__
__INodeProperties_FWD_DEFINED__ equ 1
endif
ifndef __IConsole3_FWD_DEFINED__
__IConsole3_FWD_DEFINED__ equ 1
endif
ifndef __IResultData2_FWD_DEFINED__
__IResultData2_FWD_DEFINED__ equ 1
endif

include basetsd.inc
.xlist
include oaidl.inc
.xlist

ifdef __PE__
option	dllimport:<Comctl32>
else
includelib Comctl32.lib
endif

ifndef MMC_VER
MMC_VER			equ 0x0210
endif

if (MMC_VER GE 0x0110)
endif
if (MMC_VER GE 0x0120)
endif
if (MMC_VER GE 0x0200)
endif
if (MMC_VER GE 0x0110)
endif
if (MMC_VER GE 0x0120)
endif
if (MMC_VER GE 0x0200)
endif

LPCONSOLE		typedef ptr IConsole
LPHEADERCTRL		typedef ptr IHeaderCtrl
LPTOOLBAR		typedef ptr IToolbar
LPIMAGELIST		typedef ptr IImageList
LPRESULTDATA		typedef ptr IResultData
LPCONSOLENAMESPACE	typedef ptr IConsoleNameSpace
LPPROPERTYSHEETPROVIDER typedef ptr IPropertySheetProvider
LPPROPERTYSHEETCALLBACK typedef ptr IPropertySheetCallback
LPCONTEXTMENUPROVIDER	typedef ptr IContextMenuProvider
LPCONTEXTMENUCALLBACK	typedef ptr IContextMenuCallback
LPCONTROLBAR		typedef ptr IControlbar
LPCONSOLEVERB		typedef ptr IConsoleVerb
LPMENUBUTTON		typedef ptr IMenuButton

if (MMC_VER GE 0x0110)
LPCONSOLE2		typedef ptr IConsole2
LPHEADERCTRL2		typedef ptr IHeaderCtrl2
LPCONSOLENAMESPACE2	typedef ptr IConsoleNameSpace2
LPDISPLAYHELP		typedef ptr IDisplayHelp
LPSTRINGTABLE		typedef ptr IStringTable
endif

if (MMC_VER GE 0x0120)
LPCOLUMNDATA		typedef ptr IColumnData
LPRESULTDATACOMPAREEX	typedef ptr IResultDataCompareEx
endif

LPCOMPONENT		typedef ptr IComponent
LPCOMPONENTDATA		typedef ptr IComponentData
LPEXTENDPROPERTYSHEET	typedef ptr IExtendPropertySheet
LPEXTENDCONTEXTMENU	typedef ptr IExtendContextMenu
LPEXTENDCONTROLBAR	typedef ptr IExtendControlbar
LPRESULTDATACOMPARE	typedef ptr IResultDataCompare
LPRESULTOWNERDATA	typedef ptr IResultOwnerData
LPSNAPABOUT		typedef ptr ISnapinAbout
LPSNAPINABOUT		typedef ptr ISnapinAbout
LPSNAPHELP		typedef ptr ISnapinHelp
LPSNAPINHELP		typedef ptr ISnapinHelp

if (MMC_VER GE 0x0110)
LPENUMTASK		typedef ptr IEnumTASK
LPEXTENDPROPERTYSHEET2	typedef ptr IExtendPropertySheet2
LPSNAPINHELP2		typedef ptr ISnapinHelp2
LPEXTENDTASKPAD		typedef ptr IExtendTaskPad
LPREQUIREDEXTENSIONS	typedef ptr IRequiredExtensions
endif

if (MMC_VER GE 0x0200)
LPCOMPONENT2		typedef ptr IComponent2
LPCOMPONENTDATA2	typedef ptr IComponentData2
LPEXTENDVIEW		typedef ptr IExtendView
LPVIEWEXTENSIONCALLBACK typedef ptr IViewExtensionCallback
LPCONSOLEPOWER		typedef ptr IConsolePower
LPCONSOLEPOWERSINK	typedef ptr IConsolePowerSink
LPCONSOLE3		typedef ptr IConsole3
LPNODEPROPERTIES	typedef ptr INodeProperties
LPRESULTDATA2		typedef ptr IResultData2
endif

PBSTR			typedef ptr BSTR
MMCLV_AUTO		equ ( -1 )
MMCLV_NOPARAM		equ ( -2 )
MMCLV_NOICON		equ ( -1 )
MMCLV_VIEWSTYLE_ICON	equ ( 0 )
MMCLV_VIEWSTYLE_SMALLICON equ ( 0x2 )
MMCLV_VIEWSTYLE_LIST	equ ( 0x3 )
MMCLV_VIEWSTYLE_REPORT	equ ( 0x1 )
MMCLV_VIEWSTYLE_FILTERED equ ( 0x4 )
MMCLV_NOPTR		equ ( 0 )
MMCLV_UPDATE_NOINVALIDATEALL equ ( 0x1 )
MMCLV_UPDATE_NOSCROLL	equ ( 0x2 )
;static LPOLESTR MMC_CALLBACK	=	( LPOLESTR  )-1;

if (MMC_VER GE 0x0120)
MMC_IMAGECALLBACK	equ (-1)
MMC_TEXTCALLBACK	equ MMC_CALLBACK
endif

HSCOPEITEM		typedef LONG_PTR
COMPONENTID		typedef SDWORD
HRESULTITEM		typedef LONG_PTR

RDI_STR			equ ( 0x2 )
RDI_IMAGE		equ ( 0x4 )
RDI_STATE		equ ( 0x8 )
RDI_PARAM		equ ( 0x10 )
RDI_INDEX		equ ( 0x20 )
RDI_INDENT		equ ( 0x40 )

MMC_RESULT_VIEW_STYLE	typedef SDWORD
MMC_SINGLESEL		equ 0x0001
MMC_SHOWSELALWAYS	equ 0x0002
MMC_NOSORTHEADER	equ 0x0004
if (MMC_VER GE 0x0120)
MMC_ENSUREFOCUSVISIBLE	equ 0x0008
endif
if 0
MMC_RESULT_VIEW_STYLE	typedef SDWORD
_MMC_VIEW_STYLE__dummy_ equ 0
endif
MMC_VIEW_OPTIONS_NONE	equ ( 0 )
MMC_VIEW_OPTIONS_NOLISTVIEWS equ ( 0x1 )
MMC_VIEW_OPTIONS_MULTISELECT equ ( 0x2 )
MMC_VIEW_OPTIONS_OWNERDATALIST equ ( 0x4 )
MMC_VIEW_OPTIONS_FILTERED equ ( 0x8 )
MMC_VIEW_OPTIONS_CREATENEW equ ( 0x10 )
if (MMC_VER GE 0x0110)
MMC_VIEW_OPTIONS_USEFONTLINKING equ ( 0x20 )
endif
if (MMC_VER GE 0x0120)
MMC_VIEW_OPTIONS_EXCLUDE_SCOPE_ITEMS_FROM_LIST equ ( 0x40 )
MMC_VIEW_OPTIONS_LEXICAL_SORT equ ( 0x80 )
endif
MMC_PSO_NOAPPLYNOW	equ ( 0x1 )
MMC_PSO_HASHELP		equ ( 0x2 )
MMC_PSO_NEWWIZARDTYPE	equ ( 0x4 )
MMC_PSO_NO_PROPTITLE	equ ( 0x8 )
MMC_CONTROL_TYPE	typedef SDWORD
TOOLBAR			equ 0
MENUBUTTON		equ ( TOOLBAR + 1 )
COMBOBOXBAR		equ ( MENUBUTTON + 1 )

MMC_CONSOLE_VERB	typedef SDWORD
MMC_VERB_NONE		equ 0x0000
MMC_VERB_OPEN		equ 0x8000
MMC_VERB_COPY		equ 0x8001
MMC_VERB_PASTE		equ 0x8002
MMC_VERB_DELETE		equ 0x8003
MMC_VERB_PROPERTIES	equ 0x8004
MMC_VERB_RENAME		equ 0x8005
MMC_VERB_REFRESH	equ 0x8006
MMC_VERB_PRINT		equ 0x8007
if (MMC_VER GE 0x0110)
MMC_VERB_CUT		equ 0x8008
MMC_VERB_MAX		equ 10
MMC_VERB_FIRST		equ MMC_VERB_OPEN
MMC_VERB_LAST		equ MMC_VERB_MAX - 1
endif
if 0
MMC_CONSOLE_VERB	typedef SDWORD
MMC_VERB__dummy_	equ 0
endif

;include pshpack8.inc
MMCBUTTON		STRUC 8
nBitmap			SINT ?
idCommand		SINT ?
fsState			db ?
fsType			db ?
lpButtonText		LPOLESTR ?
lpTooltipText		LPOLESTR ?
MMCBUTTON		ENDS
;include poppack.inc
LPMMCBUTTON		typedef ptr MMCBUTTON

MMC_BUTTON_STATE	typedef SDWORD
ENABLED			equ 0x1
CHECKED			equ 0x2
HIDDEN			equ 0x4
INDETERMINATE		equ 0x8
BUTTONPRESSED		equ 0x10

RESULTDATAITEM		STRUC
_mask			dd ?
bScopeItem		BOOL ?
itemID			HRESULTITEM ?
nIndex			SINT ?
nCol			SINT ?
_str			LPOLESTR ?
nImage			SINT ?
nState			UINT ?
lParam			LPARAM ?
iIndent			SINT ?
RESULTDATAITEM		ENDS

LPRESULTDATAITEM	typedef ptr RESULTDATAITEM

RFI_PARTIAL		equ ( 0x1 )
RFI_WRAP		equ ( 0x2 )

RESULTFINDINFO		STRUC
psz			LPOLESTR ?
nStart			SINT ?
dwOptions		dd ?
RESULTFINDINFO		ENDS

LPRESULTFINDINFO	typedef ptr RESULTFINDINFO
RSI_DESCENDING		equ ( 0x1 )
RSI_NOSORTICON		equ ( 0x2 )

SDI_STR			equ ( 0x2 )
SDI_IMAGE		equ ( 0x4 )
SDI_OPENIMAGE		equ ( 0x8 )
SDI_STATE		equ ( 0x10 )
SDI_PARAM		equ ( 0x20 )
SDI_CHILDREN		equ ( 0x40 )
SDI_PARENT		equ ( 0 )
SDI_PREVIOUS		equ ( 0x10000000 )
SDI_NEXT		equ ( 0x20000000 )
SDI_FIRST		equ ( 0x8000000 )

SCOPEDATAITEM		STRUC
_mask			dd ?
displayname		LPOLESTR ?
nImage			SINT ?
nOpenImage		SINT ?
nState			UINT ?
cChildren		SINT ?
lParam			LPARAM ?
relativeID		HSCOPEITEM ?
ID			HSCOPEITEM ?
SCOPEDATAITEM		ENDS
LPSCOPEDATAITEM		typedef ptr SCOPEDATAITEM

MMC_SCOPE_ITEM_STATE	typedef SDWORD
MMC_SCOPE_ITEM_STATE_NORMAL equ 0x1
MMC_SCOPE_ITEM_STATE_BOLD equ 0x2
MMC_SCOPE_ITEM_STATE_EXPANDEDONCE equ 0x3

CONTEXTMENUITEM		STRUC
strName			LPWSTR ?
strStatusBarText	LPWSTR ?
lCommandID		LONG ?
lInsertionPointID	LONG ?
fFlags			LONG ?
fSpecialFlags		LONG ?
CONTEXTMENUITEM		ENDS
LPCONTEXTMENUITEM	typedef ptr CONTEXTMENUITEM

MMC_MENU_COMMAND_IDS	typedef SDWORD
MMCC_STANDARD_VIEW_SELECT equ -1

MENUBUTTONDATA		STRUC
idCommand		SINT ?
x			SINT ?
y			SINT ?
MENUBUTTONDATA		ENDS
LPMENUBUTTONDATA	typedef ptr MENUBUTTONDATA

MMC_COOKIE		typedef LONG_PTR
MMC_MULTI_SELECT_COOKIE equ ( -2 )
MMC_WINDOW_COOKIE	equ ( -3 )

if (MMC_VER GE 0x0110)
SPECIAL_COOKIE_MIN	equ ( -10 )
SPECIAL_COOKIE_MAX	equ ( -1 )

MMC_FILTER_TYPE		typedef SDWORD
MMC_STRING_FILTER	equ 0
MMC_INT_FILTER		equ 0x1
MMC_FILTER_NOVALUE	equ 0x8000

MMC_FILTERDATA		STRUC
pszText			LPOLESTR ?
cchTextMax		SINT ?
lValue			LONG ?
MMC_FILTERDATA		ENDS

MMC_FILTER_CHANGE_CODE	typedef SDWORD
MFCC_DISABLE		equ 0
MFCC_ENABLE		equ 1
MFCC_VALUE_CHANGE	equ 2

MMC_RESTORE_VIEW	STRUC
dwSize			dd ?
cookie			MMC_COOKIE ?
pViewType		LPOLESTR ?
lViewOptions		SDWORD ?
MMC_RESTORE_VIEW	ENDS

MMC_EXPANDSYNC_STRUCT	STRUC
bHandled		BOOL ?
bExpanding		BOOL ?
hItem			HSCOPEITEM ?
MMC_EXPANDSYNC_STRUCT	ENDS
endif

if (MMC_VER GE 0x0120)
MMC_VISIBLE_COLUMNS	STRUC
nVisibleColumns		SINT ?
rgVisibleCols		SINT 1 dup(?)
MMC_VISIBLE_COLUMNS	ENDS
endif

MMC_NOTIFY_TYPE		typedef SDWORD
MMCN_ACTIVATE		equ 0x8001
MMCN_ADD_IMAGES		equ 0x8002
MMCN_BTN_CLICK		equ 0x8003
MMCN_CLICK		equ 0x8004
MMCN_COLUMN_CLICK	equ 0x8005
MMCN_CONTEXTMENU	equ 0x8006
MMCN_CUTORMOVE		equ 0x8007
MMCN_DBLCLICK		equ 0x8008
MMCN_DELETE		equ 0x8009
MMCN_DESELECT_ALL	equ 0x800A
MMCN_EXPAND		equ 0x800B
MMCN_HELP		equ 0x800C
MMCN_MENU_BTNCLICK	equ 0x800D
MMCN_MINIMIZED		equ 0x800E
MMCN_PASTE		equ 0x800F
MMCN_PROPERTY_CHANGE	equ 0x8010
MMCN_QUERY_PASTE	equ 0x8011
MMCN_REFRESH		equ 0x8012
MMCN_REMOVE_CHILDREN	equ 0x8013
MMCN_RENAME		equ 0x8014
MMCN_SELECT		equ 0x8015
MMCN_SHOW		equ 0x8016
MMCN_VIEW_CHANGE	equ 0x8017
MMCN_SNAPINHELP		equ 0x8018
MMCN_CONTEXTHELP	equ 0x8019
MMCN_INITOCX		equ 0x801A
if (MMC_VER GE 0x0110)
MMCN_FILTER_CHANGE	equ 0x801B
MMCN_FILTERBTN_CLICK	equ 0x801C
MMCN_RESTORE_VIEW	equ 0x801D
MMCN_PRINT		equ 0x801E
MMCN_PRELOAD		equ 0x801F
MMCN_LISTPAD		equ 0x8020
MMCN_EXPANDSYNC		equ 0x8021
if (MMC_VER GE 0x0120)
MMCN_COLUMNS_CHANGED	equ 0x8022
if (MMC_VER GE 0x0200)
MMCN_CANPASTE_OUTOFPROC equ 0x8023
endif
endif
endif
if 0
MMC_NOTIFY_TYPE		typedef SDWORD
MMCN__dummy_		equ 0
endif
DATA_OBJECT_TYPES	typedef SDWORD
CCT_SCOPE		equ 0x8000
CCT_RESULT		equ 0x8001
CCT_SNAPIN_MANAGER	equ 0x8002
CCT_UNINITIALIZED	equ 0xffff

MMC_NW_OPTION_NONE	equ ( 0 )
MMC_NW_OPTION_NOSCOPEPANE equ ( 0x1 )
MMC_NW_OPTION_NOTOOLBARS equ ( 0x2 )
MMC_NW_OPTION_SHORTTITLE equ ( 0x4 )
MMC_NW_OPTION_CUSTOMTITLE equ ( 0x8 )
MMC_NW_OPTION_NOPERSIST equ ( 0x10 )
MMC_NW_OPTION_NOACTIONPANE equ ( 0x20 )

CCF_NODETYPE		equ ( L"CCF_NODETYPE" )
CCF_SZNODETYPE		equ ( L"CCF_SZNODETYPE" )
CCF_DISPLAY_NAME	equ ( L"CCF_DISPLAY_NAME" )
CCF_SNAPIN_CLASSID	equ ( L"CCF_SNAPIN_CLASSID" )

if (MMC_VER GE 0x0210)
CCF_SNAPIN_CLASS	equ ( L"CCF_SNAPIN_CLASS" )
endif
CCF_WINDOW_TITLE	equ ( L"CCF_WINDOW_TITLE" )
CCF_MMC_MULTISELECT_DATAOBJECT equ ( L"CCF_MMC_MULTISELECT_DATAOBJECT" )

SMMCDataObjects		STRUC
count			dd ?
lpDataObject		LPDATAOBJECT  1	 dup(?)
SMMCDataObjects		ENDS

CCF_MULTI_SELECT_SNAPINS equ ( L"CCF_MULTI_SELECT_SNAPINS" )

SMMCObjectTypes		STRUC
count			dd ?
guid			GUID 1 dup(<>)
SMMCObjectTypes		ENDS

CCF_OBJECT_TYPES_IN_MULTI_SELECT equ ( L"CCF_OBJECT_TYPES_IN_MULTI_SELECT" )

if (MMC_VER GE 0x0110)
SMMCDynamicExtensions	typedef SMMCObjectTypes
CCF_MMC_DYNAMIC_EXTENSIONS equ ( L"CCF_MMC_DYNAMIC_EXTENSIONS" )
CCF_SNAPIN_PRELOADS	equ ( L"CCF_SNAPIN_PRELOADS" )

SNodeID			STRUC
cBytes			dd ?
id			db  1  dup(?)
SNodeID			ENDS

if (MMC_VER GE 0x0120)
SNodeID2		STRUC
dwFlags			dd ?
cBytes			dd ?
id			db  1  dup(?)
SNodeID2		ENDS

MMC_NODEID_SLOW_RETRIEVAL equ ( 0x1 )
CCF_NODEID2		equ ( L"CCF_NODEID2" )
endif ;; MMC_VER GE 0x0120

CCF_NODEID		equ ( L"CCF_NODEID" )

if (MMC_VER GE 0x0120)
SColumnSetID		STRUC
dwFlags			dd ?
cBytes			dd ?
id			db  1  dup(?)
SColumnSetID		ENDS

CCF_COLUMN_SET_ID	equ ( L"CCF_COLUMN_SET_ID" )
endif
endif

;STDAPI
MMCPropertyChangeNotify proto WINAPI \
	 lNotifyHandle: LONG_PTR,
		 param: LPARAM

if (MMC_VER GE 0x0110)
include specstrings.inc
.xlist
;STDAPI
MMCPropertyHelp proto WINAPI \
	  pszHelpTopic: LPOLESTR
endif

;STDAPI
MMCFreeNotifyHandle proto WINAPI \
	 lNotifyHandle: LONG_PTR

;STDAPI
MMCPropPageCallback proto WINAPI
externdef		CLSID_NodeManager:CLSID
if (MMC_VER GE 0x0120)
externdef		CLSID_MessageView:CLSID
endif
if (MMC_VER GE 0x0210)
;PFNAfxManageStateCallback)() typedef ptr void (STDAPICALLTYPE
;STDAPI
MMCAfxPropPageCallback proto WINAPI \
		  vpsp: PVOID,
pfnManageStateCallback: PVOID;PFNAfxManageStateCallback
endif

DOBJ_NULL		equ (LPDATAOBJECT)   0
DOBJ_CUSTOMOCX		equ (LPDATAOBJECT)  -1
DOBJ_CUSTOMWEB		equ (LPDATAOBJECT)  -2

if (MMC_VER GE 0x0110)
if (MMC_VER GE 0x0120)
DOBJ_NOCONSOLE		equ (LPDATAOBJECT)  -3
endif
SPECIAL_DOBJ_MIN	equ -10
SPECIAL_DOBJ_MAX	equ 0
endif
IS_SPECIAL_DATAOBJECT macro d
	exitm<(((LONG_PTR)(d) GE SPECIAL_DOBJ_MIN) AND ((LONG_PTR)(d) LE SPECIAL_DOBJ_MAX))>
	endm
IS_SPECIAL_COOKIE macro c
	exitm<(((c) GE SPECIAL_COOKIE_MIN) AND ((c) LE SPECIAL_COOKIE_MAX))>
	endm


externdef		__MIDL_itf_mmc_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IComponentData_INTERFACE_DEFINED__
__IComponentData_INTERFACE_DEFINED__ equ 1
externdef		IID_IComponentData:IID

.comdef IComponentData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :LPUNKNOWN
    CreateComponent	proc :ptr
    Notify		proc :LPDATAOBJECT, :MMC_NOTIFY_TYPE, :LPARAM, :LPARAM
    Destroy		proc
    QueryDataObject	proc :MMC_COOKIE, :DATA_OBJECT_TYPES, :ptr
    GetDisplayInfo	proc :ptr
    CompareObjects	proc :LPDATAOBJECT, :LPDATAOBJECT
    .ends
endif

ifndef __IComponent_INTERFACE_DEFINED__
__IComponent_INTERFACE_DEFINED__ equ 1
externdef		IID_IComponent:IID

.comdef IComponent

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :LPCONSOLE
    Notify		proc :LPDATAOBJECT, :MMC_NOTIFY_TYPE, :LPARAM, :LPARAM
    Destroy		proc :MMC_COOKIE
    QueryDataObject	proc :MMC_COOKIE, :DATA_OBJECT_TYPES, :ptr
    GetResultViewType	proc :MMC_COOKIE, :ptr, :ptr
    GetDisplayInfo	proc :ptr
    CompareObjects	proc :LPDATAOBJECT, :LPDATAOBJECT
    .ends
endif

ifndef __IResultDataCompare_INTERFACE_DEFINED__
__IResultDataCompare_INTERFACE_DEFINED__ equ 1
externdef		IID_IResultDataCompare:IID

.comdef IResultDataCompare

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Compare		proc :LPARAM, :MMC_COOKIE, :MMC_COOKIE, :ptr
    .ends
endif

ifndef __IResultOwnerData_INTERFACE_DEFINED__
__IResultOwnerData_INTERFACE_DEFINED__ equ 1
externdef		IID_IResultOwnerData:IID

.comdef IResultOwnerData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    FindItem		proc :LPRESULTFINDINFO, :ptr
    CacheHint		proc :SINT, :SINT
    SortItems		proc :SINT, :DWORD, :LPARAM
    .ends
endif

ifndef __IConsole_INTERFACE_DEFINED__
__IConsole_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsole:IID

.comdef IConsole

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetHeader		proc :LPHEADERCTRL
    SetToolbar		proc :LPTOOLBAR
    QueryResultView	proc :ptr
    QueryScopeImageList proc :ptr
    QueryResultImageList proc :ptr
    UpdateAllViews	proc :LPDATAOBJECT, :LPARAM, :LONG_PTR
    MessageBox		proc :LPCWSTR, :LPCWSTR, :UINT, :ptr
    QueryConsoleVerb	proc :ptr
    SelectScopeItem	proc :HSCOPEITEM
    GetMainWindow	proc :ptr
    NewWindow		proc :HSCOPEITEM, :SDWORD
    .ends
endif

ifndef __IHeaderCtrl_INTERFACE_DEFINED__
__IHeaderCtrl_INTERFACE_DEFINED__ equ 1
AUTO_WIDTH		equ ( -1 )
if (MMC_VER GE 0x0120)
HIDE_COLUMN		equ ( -4 )
endif
externdef		IID_IHeaderCtrl:IID

.comdef IHeaderCtrl

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InsertColumn	proc :SINT, :LPCWSTR, :SINT, :SINT
    DeleteColumn	proc :SINT
    SetColumnText	proc :SINT, :LPCWSTR
    GetColumnText	proc :SINT, :ptr
    SetColumnWidth	proc :SINT, :SINT
    GetColumnWidth	proc :SINT, :ptr
    .ends
endif

_MIDL___MIDL_itf_mmc_0000_0006_0001 typedef SDWORD
CCM_INSERTIONPOINTID_MASK_SPECIAL equ 0xffff0000
CCM_INSERTIONPOINTID_MASK_SHARED equ 0x80000000
CCM_INSERTIONPOINTID_MASK_CREATE_PRIMARY equ 0x40000000
CCM_INSERTIONPOINTID_MASK_ADD_PRIMARY equ 0x20000000
CCM_INSERTIONPOINTID_MASK_ADD_3RDPARTY equ 0x10000000
CCM_INSERTIONPOINTID_MASK_RESERVED equ 0xfff0000
CCM_INSERTIONPOINTID_MASK_FLAGINDEX equ 0x1f
CCM_INSERTIONPOINTID_PRIMARY_TOP equ 0xa0000000
CCM_INSERTIONPOINTID_PRIMARY_NEW equ 0xa0000001
CCM_INSERTIONPOINTID_PRIMARY_TASK equ 0xa0000002
CCM_INSERTIONPOINTID_PRIMARY_VIEW equ 0xa0000003
CCM_INSERTIONPOINTID_PRIMARY_HELP equ 0xa0000004
CCM_INSERTIONPOINTID_3RDPARTY_NEW equ 0x90000001
CCM_INSERTIONPOINTID_3RDPARTY_TASK equ 0x90000002
CCM_INSERTIONPOINTID_ROOT_MENU equ 0x80000000

_MIDL___MIDL_itf_mmc_0000_0006_0002 typedef SDWORD
CCM_INSERTIONALLOWED_TOP  equ ( 1 SHL ( CCM_INSERTIONPOINTID_PRIMARY_TOP  AND CCM_INSERTIONPOINTID_MASK_FLAGINDEX ))
CCM_INSERTIONALLOWED_NEW  equ ( 1 SHL ( CCM_INSERTIONPOINTID_PRIMARY_NEW  AND CCM_INSERTIONPOINTID_MASK_FLAGINDEX ))
CCM_INSERTIONALLOWED_TASK equ ( 1 SHL ( CCM_INSERTIONPOINTID_PRIMARY_TASK AND CCM_INSERTIONPOINTID_MASK_FLAGINDEX ))
CCM_INSERTIONALLOWED_VIEW equ ( 1 SHL ( CCM_INSERTIONPOINTID_PRIMARY_VIEW AND CCM_INSERTIONPOINTID_MASK_FLAGINDEX ))

_MIDL___MIDL_itf_mmc_0000_0006_0003 typedef SDWORD
CCM_COMMANDID_MASK_RESERVED equ 0xffff0000

_MIDL___MIDL_itf_mmc_0000_0006_0004 typedef SDWORD
CCM_SPECIAL_SEPARATOR	equ 0x1
CCM_SPECIAL_SUBMENU	equ 0x2
CCM_SPECIAL_DEFAULT_ITEM equ 0x4
CCM_SPECIAL_INSERTION_POINT equ 0x8
CCM_SPECIAL_TESTONLY	equ 0x10

externdef		__MIDL_itf_mmc_0000_0006_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0006_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IContextMenuCallback_INTERFACE_DEFINED__
__IContextMenuCallback_INTERFACE_DEFINED__ equ 1
externdef		IID_IContextMenuCallback:IID

.comdef IContextMenuCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddItem		proc :ptr
    .ends
endif

ifndef __IContextMenuProvider_INTERFACE_DEFINED__
__IContextMenuProvider_INTERFACE_DEFINED__ equ 1
externdef		IID_IContextMenuProvider:IID

.comdef IContextMenuProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddItem		proc :ptr
    EmptyMenuList	proc
    AddPrimaryExtensionItems proc :LPUNKNOWN, :LPDATAOBJECT
    AddThirdPartyExtensionItems proc :LPDATAOBJECT
    ShowContextMenu	proc :HWND, :SDWORD, :SDWORD, :ptr
    .ends
endif

ifndef __IExtendContextMenu_INTERFACE_DEFINED__
__IExtendContextMenu_INTERFACE_DEFINED__ equ 1
externdef		IID_IExtendContextMenu:IID

.comdef IExtendContextMenu

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddMenuItems	proc :LPDATAOBJECT, :LPCONTEXTMENUCALLBACK, :ptr
    Command		proc :SDWORD, :LPDATAOBJECT
    .ends
endif

if (MMC_VER GE 0x0120)
ILSIF_LEAVE_LARGE_ICON	equ 0x40000000
ILSIF_LEAVE_SMALL_ICON	equ 0x20000000
ILSIF_LEAVE_MASK	equ (ILSIF_LEAVE_LARGE_ICON OR ILSIF_LEAVE_SMALL_ICON)
ILSI_LARGE_ICON macro nLoc
	exitm<(nLoc OR ILSIF_LEAVE_SMALL_ICON)>
	endm
ILSI_SMALL_ICON macro nLoc
	exitm<(nLoc OR ILSIF_LEAVE_LARGE_ICON)>
	endm
endif

externdef		__MIDL_itf_mmc_0000_0009_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0009_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IImageList_INTERFACE_DEFINED__
__IImageList_INTERFACE_DEFINED__ equ 1
externdef		IID_IImageList:IID

.comdef IImageList

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ImageListSetIcon	proc :ptr, :SDWORD
    ImageListSetStrip	proc :ptr, :ptr, :SDWORD, :COLORREF
    .ends
endif

ifndef __IResultData_INTERFACE_DEFINED__
__IResultData_INTERFACE_DEFINED__ equ 1
externdef		IID_IResultData:IID

.comdef IResultData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InsertItem		proc :LPRESULTDATAITEM
    DeleteItem		proc :HRESULTITEM, :SINT
    FindItemByLParam	proc :LPARAM, :ptr
    DeleteAllRsltItems	proc
    SetItem		proc :LPRESULTDATAITEM
    GetItem		proc :LPRESULTDATAITEM
    GetNextItem		proc :LPRESULTDATAITEM
    ModifyItemState	proc :SINT, :HRESULTITEM, :UINT, :UINT
    ModifyViewStyle	proc :MMC_RESULT_VIEW_STYLE, :MMC_RESULT_VIEW_STYLE
    SetViewMode		proc :SDWORD
    GetViewMode		proc :ptr
    UpdateItem		proc :HRESULTITEM
    Sort		proc :SINT, :DWORD, :LPARAM
    SetDescBarText	proc :LPOLESTR
    SetItemCount	proc :SINT, :DWORD
    .ends
endif

ifndef __IConsoleNameSpace_INTERFACE_DEFINED__
__IConsoleNameSpace_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsoleNameSpace:IID

.comdef IConsoleNameSpace

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InsertItem		proc :LPSCOPEDATAITEM
    DeleteItem		proc :HSCOPEITEM
    SetItem		proc :LPSCOPEDATAITEM
    GetItem		proc :LPSCOPEDATAITEM
    GetChildItem	proc :HSCOPEITEM, :ptr, :ptr
    GetNextItem		proc :HSCOPEITEM, :ptr, :ptr
    GetParentItem	proc :HSCOPEITEM, :ptr, :ptr
    .ends
endif

ifndef __IConsoleNameSpace2_INTERFACE_DEFINED__
__IConsoleNameSpace2_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsoleNameSpace2:IID

.comdef IConsoleNameSpace2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InsertItem		proc :LPSCOPEDATAITEM
    DeleteItem		proc :HSCOPEITEM
    SetItem		proc :LPSCOPEDATAITEM
    GetItem		proc :LPSCOPEDATAITEM
    GetChildItem	proc :HSCOPEITEM, :ptr, :ptr
    GetNextItem		proc :HSCOPEITEM, :ptr, :ptr
    GetParentItem	proc :HSCOPEITEM, :ptr, :ptr
    Expand		proc :HSCOPEITEM
    AddExtension	proc :HSCOPEITEM, :LPCLSID
    .ends
endif
HPROPSHEETPAGE		typedef ptr ;_PSP

externdef		__MIDL_itf_mmc_0000_0013_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0013_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPropertySheetCallback_INTERFACE_DEFINED__
__IPropertySheetCallback_INTERFACE_DEFINED__ equ 1
externdef		IID_IPropertySheetCallback:IID

.comdef IPropertySheetCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddPage		proc :HPROPSHEETPAGE
    RemovePage		proc :HPROPSHEETPAGE
    .ends
endif

ifndef __IPropertySheetProvider_INTERFACE_DEFINED__
__IPropertySheetProvider_INTERFACE_DEFINED__ equ 1
externdef		IID_IPropertySheetProvider:IID

.comdef IPropertySheetProvider

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreatePropertySheet proc :LPCWSTR, :boolean, :MMC_COOKIE, :LPDATAOBJECT, :DWORD
    FindPropertySheet	proc :HSCOPEITEM, :LPCOMPONENT, :LPDATAOBJECT
    AddPrimaryPages	proc :LPUNKNOWN, :BOOL, :HWND, :BOOL
    AddExtensionPages	proc
    Show		proc :LONG_PTR, :SINT
    .ends
endif

ifndef __IExtendPropertySheet_INTERFACE_DEFINED__
__IExtendPropertySheet_INTERFACE_DEFINED__ equ 1
externdef		IID_IExtendPropertySheet:IID

.comdef IExtendPropertySheet

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreatePropertyPages proc :LPPROPERTYSHEETCALLBACK, :LONG_PTR, :LPDATAOBJECT
    QueryPagesFor	proc :LPDATAOBJECT
    .ends
endif

ifndef __IControlbar_INTERFACE_DEFINED__
__IControlbar_INTERFACE_DEFINED__ equ 1
externdef		IID_IControlbar:IID

.comdef IControlbar

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Create		proc :MMC_CONTROL_TYPE, :LPEXTENDCONTROLBAR, :ptr
    Attach		proc :MMC_CONTROL_TYPE, :LPUNKNOWN
    Detach		proc :LPUNKNOWN
    .ends
endif

ifndef __IExtendControlbar_INTERFACE_DEFINED__
__IExtendControlbar_INTERFACE_DEFINED__ equ 1
externdef		IID_IExtendControlbar:IID

.comdef IExtendControlbar

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetControlbar	proc :LPCONTROLBAR
    ControlbarNotify	proc :MMC_NOTIFY_TYPE, :LPARAM, :LPARAM
    .ends
endif

ifndef __IToolbar_INTERFACE_DEFINED__
__IToolbar_INTERFACE_DEFINED__ equ 1
externdef		IID_IToolbar:IID

.comdef IToolbar

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddBitmap		proc :SINT, :HBITMAP, :SINT, :SINT, :COLORREF
    AddButtons		proc :SINT, :LPMMCBUTTON
    InsertButton	proc :SINT, :LPMMCBUTTON
    DeleteButton	proc :SINT
    GetButtonState	proc :SINT, :MMC_BUTTON_STATE, :ptr
    SetButtonState	proc :SINT, :MMC_BUTTON_STATE, :BOOL
    .ends
endif

ifndef __IConsoleVerb_INTERFACE_DEFINED__
__IConsoleVerb_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsoleVerb:IID

.comdef IConsoleVerb

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetVerbState	proc :MMC_CONSOLE_VERB, :MMC_BUTTON_STATE, :ptr
    SetVerbState	proc :MMC_CONSOLE_VERB, :MMC_BUTTON_STATE, :BOOL
    SetDefaultVerb	proc :MMC_CONSOLE_VERB
    GetDefaultVerb	proc :ptr
    .ends
endif

ifndef __ISnapinAbout_INTERFACE_DEFINED__
__ISnapinAbout_INTERFACE_DEFINED__ equ 1
externdef		IID_ISnapinAbout:IID

.comdef ISnapinAbout

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetSnapinDescription proc :ptr
    GetProvider		proc :ptr
    GetSnapinVersion	proc :ptr
    GetSnapinImage	proc :ptr
    GetStaticFolderImage proc :ptr, :ptr, :ptr, :ptr
    .ends
endif

ifndef __IMenuButton_INTERFACE_DEFINED__
__IMenuButton_INTERFACE_DEFINED__ equ 1
externdef		IID_IMenuButton:IID

.comdef IMenuButton

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddButton		proc :SINT, :LPOLESTR, :LPOLESTR
    SetButton		proc :SINT, :LPOLESTR, :LPOLESTR
    SetButtonState	proc :SINT, :MMC_BUTTON_STATE, :BOOL
    .ends
endif

ifndef __ISnapinHelp_INTERFACE_DEFINED__
__ISnapinHelp_INTERFACE_DEFINED__ equ 1
externdef		IID_ISnapinHelp:IID

.comdef ISnapinHelp

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetHelpTopic	proc :ptr
    .ends
endif	;; __ISnapinHelp_INTERFACE_DEFINED__

if (MMC_VER GE 0x0110)
externdef		__MIDL_itf_mmc_0000_0023_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0023_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IExtendPropertySheet2_INTERFACE_DEFINED__
__IExtendPropertySheet2_INTERFACE_DEFINED__ equ 1
externdef		IID_IExtendPropertySheet2:IID

.comdef IExtendPropertySheet2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    CreatePropertyPages proc :LPPROPERTYSHEETCALLBACK, :LONG_PTR, :LPDATAOBJECT
    QueryPagesFor	proc :LPDATAOBJECT
    GetWatermarks	proc :LPDATAOBJECT, :ptr, :ptr, :ptr, :ptr
    .ends
endif

ifndef __IHeaderCtrl2_INTERFACE_DEFINED__
__IHeaderCtrl2_INTERFACE_DEFINED__ equ 1

externdef		IID_IHeaderCtrl2:IID

.comdef IHeaderCtrl2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InsertColumn	proc :SINT, :LPCWSTR, :SINT, :SINT
    DeleteColumn	proc :SINT
    SetColumnText	proc :SINT, :LPCWSTR
    GetColumnText	proc :SINT, :ptr
    SetColumnWidth	proc :SINT, :SINT
    GetColumnWidth	proc :SINT, :ptr
    SetChangeTimeOut	proc :SDWORD
    SetColumnFilter	proc :UINT, :DWORD, :ptr
    GetColumnFilter	proc :UINT, :LPDWORD, :ptr
    .ends
endif

ifndef __ISnapinHelp2_INTERFACE_DEFINED__
__ISnapinHelp2_INTERFACE_DEFINED__ equ 1
externdef		IID_ISnapinHelp2:IID

.comdef ISnapinHelp2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetHelpTopic	proc :ptr
    GetLinkedTopics	proc :ptr
    .ends
endif

MMC_TASK_DISPLAY_TYPE	typedef SDWORD
MMC_TASK_DISPLAY_UNINITIALIZED equ 0
MMC_TASK_DISPLAY_TYPE_SYMBOL equ ( MMC_TASK_DISPLAY_UNINITIALIZED + 1 )
MMC_TASK_DISPLAY_TYPE_VANILLA_GIF equ ( MMC_TASK_DISPLAY_TYPE_SYMBOL + 1 )
MMC_TASK_DISPLAY_TYPE_CHOCOLATE_GIF equ ( MMC_TASK_DISPLAY_TYPE_VANILLA_GIF + 1 )
MMC_TASK_DISPLAY_TYPE_BITMAP equ ( MMC_TASK_DISPLAY_TYPE_CHOCOLATE_GIF + 1 )

MMC_TASK_DISPLAY_SYMBOL STRUC
szFontFamilyName	LPOLESTR ?
szURLtoEOT		LPOLESTR ?
szSymbolString		LPOLESTR ?
MMC_TASK_DISPLAY_SYMBOL ENDS

MMC_TASK_DISPLAY_BITMAP STRUC
szMouseOverBitmap	LPOLESTR ?
szMouseOffBitmap	LPOLESTR ?
MMC_TASK_DISPLAY_BITMAP ENDS

MMC_TASK_DISPLAY_OBJECT STRUC
eDisplayType		MMC_TASK_DISPLAY_TYPE ?
UNION
 uBitmap		MMC_TASK_DISPLAY_BITMAP <>
 uSymbol		MMC_TASK_DISPLAY_SYMBOL <>
ENDS
MMC_TASK_DISPLAY_OBJECT ENDS

MMC_ACTION_TYPE		typedef SDWORD
MMC_ACTION_UNINITIALIZED equ -1
MMC_ACTION_ID		equ ( MMC_ACTION_UNINITIALIZED + 1 )
MMC_ACTION_LINK		equ ( MMC_ACTION_ID + 1 )
MMC_ACTION_SCRIPT	equ ( MMC_ACTION_LINK + 1 )

MMC_TASK		STRUC
sDisplayObject		MMC_TASK_DISPLAY_OBJECT <>
szText			LPOLESTR ?
szHelpString		LPOLESTR ?
eActionType		MMC_ACTION_TYPE ?
UNION
nCommandID		LONG_PTR ?
szActionURL		LPOLESTR ?
szScript		LPOLESTR ?
ENDS
MMC_TASK		ENDS

MMC_LISTPAD_INFO	STRUC
szTitle			LPOLESTR ?
szButtonText		LPOLESTR ?
nCommandID		LONG_PTR ?
MMC_LISTPAD_INFO	ENDS

MMC_STRING_ID		typedef DWORD

externdef		__MIDL_itf_mmc_0000_0026_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0026_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumTASK_INTERFACE_DEFINED__
__IEnumTASK_INTERFACE_DEFINED__ equ 1
externdef		IID_IEnumTASK:IID

.comdef IEnumTASK

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends
endif

ifndef __IExtendTaskPad_INTERFACE_DEFINED__
__IExtendTaskPad_INTERFACE_DEFINED__ equ 1
externdef		IID_IExtendTaskPad:IID

.comdef IExtendTaskPad

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    TaskNotify		proc :ptr, :ptr, :ptr
    EnumTasks		proc :ptr, :LPOLESTR, :ptr
    GetTitle		proc :LPOLESTR, :ptr
    GetDescriptiveText	proc :LPOLESTR, :ptr
    GetBackground	proc :LPOLESTR, :ptr
    GetListPadInfo	proc :LPOLESTR, :ptr
    .ends
endif

ifndef __IConsole2_INTERFACE_DEFINED__
__IConsole2_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsole2:IID

.comdef IConsole2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetHeader		proc :LPHEADERCTRL
    SetToolbar		proc :LPTOOLBAR
    QueryResultView	proc :ptr
    QueryScopeImageList proc :ptr
    QueryResultImageList proc :ptr
    UpdateAllViews	proc :LPDATAOBJECT, :LPARAM, :LONG_PTR
    MessageBox		proc :LPCWSTR, :LPCWSTR, :UINT, :ptr
    QueryConsoleVerb	proc :ptr
    SelectScopeItem	proc :HSCOPEITEM
    GetMainWindow	proc :ptr
    NewWindow		proc :HSCOPEITEM, :SDWORD
    Expand		proc :HSCOPEITEM, :BOOL
    IsTaskpadViewPreferred proc
    SetStatusText	proc :LPOLESTR
    .ends
endif

ifndef __IDisplayHelp_INTERFACE_DEFINED__
__IDisplayHelp_INTERFACE_DEFINED__ equ 1
externdef		IID_IDisplayHelp:IID

.comdef IDisplayHelp

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ShowTopic		proc :LPOLESTR
    .ends
endif

ifndef __IRequiredExtensions_INTERFACE_DEFINED__
__IRequiredExtensions_INTERFACE_DEFINED__ equ 1
externdef		IID_IRequiredExtensions:IID

.comdef IRequiredExtensions

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    EnableAllExtensions proc
    GetFirstExtension	proc :LPCLSID
    GetNextExtension	proc :LPCLSID
    .ends
endif

ifndef __IStringTable_INTERFACE_DEFINED__
__IStringTable_INTERFACE_DEFINED__ equ 1
externdef		IID_IStringTable:IID

.comdef IStringTable

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddString		proc :LPCOLESTR, :ptr
    GetString		proc :MMC_STRING_ID, :ULONG
    GetStringLength	proc :MMC_STRING_ID, :ptr
    DeleteString	proc :MMC_STRING_ID
    DeleteAllStrings	proc
    FindString		proc :LPCOLESTR, :ptr
    Enumerate		proc :ptr
    .ends
endif
endif ;; MMC_VER GE 0x0110

if (MMC_VER GE 0x0120)
HDI_HIDDEN		equ ( 0x1 )

MMC_COLUMN_DATA		STRUC
nColIndex		SINT ?
dwFlags			dd ?
nWidth			SINT ?
ulReserved		ULONG_PTR ?
MMC_COLUMN_DATA		ENDS
LPMMC_COLUMN_DATA	typedef ptr MMC_COLUMN_DATA

MMC_COLUMN_SET_DATA	STRUC
cbSize			SINT ?
nNumCols		SINT ?
pColData		LPMMC_COLUMN_DATA ?
MMC_COLUMN_SET_DATA	ENDS

MMC_SORT_DATA		STRUC
nColIndex		SINT ?
dwSortOptions		dd ?
ulReserved		ULONG_PTR ?
MMC_SORT_DATA		ENDS
LPMMC_SORT_DATA		typedef ptr MMC_SORT_DATA

MMC_SORT_SET_DATA	STRUC
cbSize			SINT ?
nNumItems		SINT ?
pSortData		LPMMC_SORT_DATA ?
MMC_SORT_SET_DATA	ENDS

externdef		__MIDL_itf_mmc_0000_0032_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0032_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IColumnData_INTERFACE_DEFINED__
__IColumnData_INTERFACE_DEFINED__ equ 1
externdef		IID_IColumnData:IID

.comdef IColumnData

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetColumnConfigData proc :ptr, :ptr
    GetColumnConfigData proc :ptr, :ptr
    SetColumnSortData	proc :ptr, :ptr
    GetColumnSortData	proc :ptr, :ptr
    .ends
endif

ifndef __IMessageView_INTERFACE_DEFINED__
__IMessageView_INTERFACE_DEFINED__ equ 1

IconIdentifier		typedef SDWORD
Icon_None		equ 0
Icon_Error		equ 32513
Icon_Question		equ 32514
Icon_Warning		equ 32515
Icon_Information	equ 32516
Icon_First		equ Icon_Error
Icon_Last		equ Icon_Information

externdef		IID_IMessageView:IID

.comdef IMessageView

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetTitleText	proc :LPCOLESTR
    SetBodyText		proc :LPCOLESTR
    SetIcon		proc :IconIdentifier
    Clear		proc
    .ends
endif

RDITEMHDR		STRUC
dwFlags			dd ?
cookie			MMC_COOKIE ?
lpReserved		LPARAM ?
RDITEMHDR		ENDS
LPRDITEMHDR		typedef ptr RDITEMHDR

RDCI_ScopeItem		equ ( 0x80000000 )

RDCOMPARE		STRUC
cbSize			dd ?
dwFlags			dd ?
nColumn			SINT ?
lUserParam		LPARAM ?
prdch1			LPRDITEMHDR ?
prdch2			LPRDITEMHDR ?
RDCOMPARE		ENDS

externdef		__MIDL_itf_mmc_0000_0034_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0034_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IResultDataCompareEx_INTERFACE_DEFINED__
__IResultDataCompareEx_INTERFACE_DEFINED__ equ 1
externdef		IID_IResultDataCompareEx:IID

.comdef IResultDataCompareEx

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Compare		proc :ptr, :ptr
    .ends
endif
endif

if (MMC_VER GE 0x0200)
MMC_VIEW_TYPE		typedef SDWORD
MMC_VIEW_TYPE_LIST	equ 0
MMC_VIEW_TYPE_HTML	equ ( MMC_VIEW_TYPE_LIST + 1 )
MMC_VIEW_TYPE_OCX	equ ( MMC_VIEW_TYPE_HTML + 1 )

RVTI_MISC_OPTIONS_NOLISTVIEWS equ ( 0x1 )
RVTI_LIST_OPTIONS_NONE	equ ( 0 )
RVTI_LIST_OPTIONS_OWNERDATALIST equ ( 0x2 )
RVTI_LIST_OPTIONS_MULTISELECT equ ( 0x4 )
RVTI_LIST_OPTIONS_FILTERED equ ( 0x8 )
RVTI_LIST_OPTIONS_USEFONTLINKING equ ( 0x20 )
RVTI_LIST_OPTIONS_EXCLUDE_SCOPE_ITEMS_FROM_LIST equ ( 0x40 )
RVTI_LIST_OPTIONS_LEXICAL_SORT equ ( 0x80 )
RVTI_LIST_OPTIONS_ALLOWPASTE equ ( 0x100 )
RVTI_HTML_OPTIONS_NONE	equ ( 0 )
RVTI_HTML_OPTIONS_NOLISTVIEW equ ( 0x1 )
RVTI_OCX_OPTIONS_NONE	equ ( 0 )
RVTI_OCX_OPTIONS_NOLISTVIEW equ ( 0x1 )
RVTI_OCX_OPTIONS_CACHE_OCX equ ( 0x2 )

RESULT_VIEW_TYPE_INFO	STRUC
pstrPersistableViewDescription LPOLESTR ?
eViewType		MMC_VIEW_TYPE ?
dwMiscOptions		dd ?
UNION
 dwListOptions		dd ?
 STRUC
  dwHTMLOptions		dd ?
  pstrURL		LPOLESTR ?
 ENDS
 STRUC
  dwOCXOptions		dd ?
  pUnkControl		LPUNKNOWN ?
 ENDS
ENDS
RESULT_VIEW_TYPE_INFO	ENDS
PRESULT_VIEW_TYPE_INFO	typedef ptr RESULT_VIEW_TYPE_INFO

CCF_DESCRIPTION		equ ( L"CCF_DESCRIPTION" )
CCF_HTML_DETAILS	equ ( L"CCF_HTML_DETAILS" )

CONTEXTMENUITEM2	STRUC
strName			LPWSTR ?
strStatusBarText	LPWSTR ?
lCommandID		LONG ?
lInsertionPointID	LONG ?
fFlags			LONG ?
fSpecialFlags		LONG ?
strLanguageIndependentName LPWSTR ?
CONTEXTMENUITEM2	ENDS
LPCONTEXTMENUITEM2	typedef ptr CONTEXTMENUITEM2

MMC_EXT_VIEW_DATA	STRUC
viewID			GUID <>
pszURL			LPCOLESTR ?
pszViewTitle		LPCOLESTR ?
pszTooltipText		LPCOLESTR ?
bReplacesDefaultView	BOOL ?
MMC_EXT_VIEW_DATA	ENDS
PMMC_EXT_VIEW_DATA	typedef ptr MMC_EXT_VIEW_DATA

MMC_DEFAULT_OPERATION_COPY equ ( 0x1 )

externdef		__MIDL_itf_mmc_0000_0035_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0035_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IComponentData2_INTERFACE_DEFINED__
__IComponentData2_INTERFACE_DEFINED__ equ 1
externdef		IID_IComponentData2:IID

.comdef IComponentData2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :LPUNKNOWN
    CreateComponent	proc :ptr
    Notify		proc :LPDATAOBJECT, :MMC_NOTIFY_TYPE, :LPARAM, :LPARAM
    Destroy		proc
    QueryDataObject	proc :MMC_COOKIE, :DATA_OBJECT_TYPES, :ptr
    GetDisplayInfo	proc :ptr
    CompareObjects	proc :LPDATAOBJECT, :LPDATAOBJECT
    QueryDispatch	proc :MMC_COOKIE, :DATA_OBJECT_TYPES, :ptr
    .ends
endif

ifndef __IComponent2_INTERFACE_DEFINED__
__IComponent2_INTERFACE_DEFINED__ equ 1
externdef		IID_IComponent2:IID

.comdef IComponent2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Initialize		proc :LPCONSOLE
    Notify		proc :LPDATAOBJECT, :MMC_NOTIFY_TYPE, :LPARAM, :LPARAM
    Destroy		proc :MMC_COOKIE
    QueryDataObject	proc :MMC_COOKIE, :DATA_OBJECT_TYPES, :ptr
    GetResultViewType	proc :MMC_COOKIE, :ptr, :ptr
    GetDisplayInfo	proc :ptr
    CompareObjects	proc :LPDATAOBJECT, :LPDATAOBJECT
    QueryDispatch	proc :MMC_COOKIE, :DATA_OBJECT_TYPES, :ptr
    GetResultViewType2	proc :MMC_COOKIE, :PRESULT_VIEW_TYPE_INFO
    RestoreResultView	proc :MMC_COOKIE, :PRESULT_VIEW_TYPE_INFO
    .ends
endif

ifndef __IContextMenuCallback2_INTERFACE_DEFINED__
__IContextMenuCallback2_INTERFACE_DEFINED__ equ 1
externdef		IID_IContextMenuCallback2:IID

.comdef IContextMenuCallback2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddItem		proc :ptr
    .ends
endif

ifndef __IMMCVersionInfo_INTERFACE_DEFINED__
__IMMCVersionInfo_INTERFACE_DEFINED__ equ 1
externdef		IID_IMMCVersionInfo:IID

.comdef IMMCVersionInfo

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetMMCVersion	proc :ptr, :ptr
    .ends
endif

ifndef __MMCVersionLib_LIBRARY_DEFINED__
__MMCVersionLib_LIBRARY_DEFINED__ equ 1
externdef		LIBID_MMCVersionLib:IID
externdef		CLSID_MMCVersionInfo:CLSID
externdef		CLSID_ConsolePower:CLSID
endif

ifndef __IExtendView_INTERFACE_DEFINED__
__IExtendView_INTERFACE_DEFINED__ equ 1
externdef		IID_IExtendView:IID

.comdef IExtendView

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetViews		proc :LPDATAOBJECT, :LPVIEWEXTENSIONCALLBACK
    .ends
endif

ifndef __IViewExtensionCallback_INTERFACE_DEFINED__
__IViewExtensionCallback_INTERFACE_DEFINED__ equ 1
externdef		IID_IViewExtensionCallback:IID

.comdef IViewExtensionCallback

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    AddView		proc :PMMC_EXT_VIEW_DATA
    .ends
endif

ifndef __IConsolePower_INTERFACE_DEFINED__
__IConsolePower_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsolePower:IID

.comdef IConsolePower

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetExecutionState	proc :DWORD, :DWORD
    ResetIdleTimer	proc :DWORD
    .ends
endif

ifndef __IConsolePowerSink_INTERFACE_DEFINED__
__IConsolePowerSink_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsolePowerSink:IID

.comdef IConsolePowerSink

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnPowerBroadcast	proc :UINT, :LPARAM, :ptr
    .ends
endif

ifndef __INodeProperties_INTERFACE_DEFINED__
__INodeProperties_INTERFACE_DEFINED__ equ 1
externdef		IID_INodeProperties:IID

.comdef INodeProperties

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetProperty		proc :LPDATAOBJECT, :BSTR, :PBSTR
    .ends
endif

ifndef __IConsole3_INTERFACE_DEFINED__
__IConsole3_INTERFACE_DEFINED__ equ 1
externdef		IID_IConsole3:IID

.comdef IConsole3

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetHeader		proc :LPHEADERCTRL
    SetToolbar		proc :LPTOOLBAR
    QueryResultView	proc :ptr
    QueryScopeImageList proc :ptr
    QueryResultImageList proc :ptr
    UpdateAllViews	proc :LPDATAOBJECT, :LPARAM, :LONG_PTR
    MessageBox		proc :LPCWSTR, :LPCWSTR, :UINT, :ptr
    QueryConsoleVerb	proc :ptr
    SelectScopeItem	proc :HSCOPEITEM
    GetMainWindow	proc :ptr
    NewWindow		proc :HSCOPEITEM, :SDWORD
    Expand		proc :HSCOPEITEM, :BOOL
    IsTaskpadViewPreferred proc
    SetStatusText	proc :LPOLESTR
    RenameScopeItem	proc :HSCOPEITEM
    .ends
endif

ifndef __IResultData2_INTERFACE_DEFINED__
__IResultData2_INTERFACE_DEFINED__ equ 1
externdef		IID_IResultData2:IID

.comdef IResultData2

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    InsertItem		proc :LPRESULTDATAITEM
    DeleteItem		proc :HRESULTITEM, :SINT
    FindItemByLParam	proc :LPARAM, :ptr
    DeleteAllRsltItems	proc
    SetItem		proc :LPRESULTDATAITEM
    GetItem		proc :LPRESULTDATAITEM
    GetNextItem		proc :LPRESULTDATAITEM
    ModifyItemState	proc :SINT, :HRESULTITEM, :UINT, :UINT
    ModifyViewStyle	proc :MMC_RESULT_VIEW_STYLE, :MMC_RESULT_VIEW_STYLE
    SetViewMode		proc :SDWORD
    GetViewMode		proc :ptr
    UpdateItem		proc :HRESULTITEM
    Sort		proc :SINT, :DWORD, :LPARAM
    SetDescBarText	proc :LPOLESTR
    SetItemCount	proc :SINT, :DWORD
    RenameResultItem	proc :HRESULTITEM
    .ends
endif
endif

if (MMC_VER GE 0x0210)
MMC_ITEM_OVERLAY	typedef SDWORD
MMC_ITEM_OVERLAY_NONE	equ 0
MMC_ITEM_OVERLAY_ERROR	equ 1
MMC_ITEM_OVERLAY_WARNING equ 2
MMC_ITEM_OVERLAY_INFO	equ 3
MMC_ITEM_OVERLAY_BUSY	equ 4
MMC_ITEM_OVERLAY_UNAVAILABLE equ 5
MMC_ITEM_OVERLAY_SHORTCUT equ 6
MMC_ITEM_OVERLAY_RUNNING equ 7
MMC_ITEM_OVERLAY_PAUSED equ 8
MMC_ITEM_OVERLAY_STOPPED equ 9
MMC_ITEM_OVERLAY_COMPLETE equ 10
MMC_ITEM_OVERLAY_STATE_MASK equ ( 0xf00 )
MMC_ITEM_OVERLAY_STATE_SHIFT equ ( 8 )
MMC_OVERLAY_ITEM_INDEX_TO_ITEM_STATE macro i
	exitm<(((i) SHL MMC_ITEM_OVERLAY_STATE_SHIFT) AND MMC_ITEM_OVERLAY_STATE_MASK)>
	endm
MMC_OVERLAY_ITEM_INDEX_FROM_ITEM_STATE macro state
	exitm<(((state) AND MMC_ITEM_OVERLAY_STATE_MASK) SHR MMC_ITEM_OVERLAY_STATE_SHIFT)>
	endm
MMC_ITEM_STATE_MASK	equ ( 0xff )
endif

externdef		__MIDL_itf_mmc_0000_0046_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_mmc_0000_0046_v0_0_s_ifspec:RPC_IF_HANDLE

;DWORD
BSTR_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HBITMAP_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;void
HBITMAP_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HBITMAP


;DWORD
HICON_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HICON

;LPSTR
HICON_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;LPSTR
HICON_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;void
HICON_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HICON


;DWORD
HPALETTE_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HPALETTE

;LPSTR
HPALETTE_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HPALETTE

;LPSTR
HPALETTE_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HPALETTE

;void
HPALETTE_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HPALETTE


;DWORD
HWND_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND


;DWORD
BSTR_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr BSTR

;LPSTR
BSTR_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;LPSTR
BSTR_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr BSTR


;DWORD
HBITMAP_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;LPSTR
HBITMAP_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HBITMAP

;void
HBITMAP_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HBITMAP


;DWORD
HICON_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HICON

;LPSTR
HICON_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;LPSTR
HICON_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HICON

;void
HICON_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HICON


;DWORD
HPALETTE_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HPALETTE

;LPSTR
HPALETTE_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HPALETTE

;LPSTR
HPALETTE_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HPALETTE

;void
HPALETTE_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HPALETTE


;DWORD
HWND_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HWND

;LPSTR
HWND_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;LPSTR
HWND_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HWND

.list
endif
