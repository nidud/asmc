ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
 .err <this stub requires an updated version of rpcndr>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __shldisp_h__
__shldisp_h__ equ 1
.xlist

ifndef __IFolderViewOC_FWD_DEFINED__
__IFolderViewOC_FWD_DEFINED__ equ 1
endif

ifndef __DShellFolderViewEvents_FWD_DEFINED__
__DShellFolderViewEvents_FWD_DEFINED__ equ 1
endif

ifndef __ShellFolderViewOC_FWD_DEFINED__
__ShellFolderViewOC_FWD_DEFINED__ equ 1
ShellFolderViewOC	typedef ShellFolderViewOC
endif

ifndef __DFConstraint_FWD_DEFINED__
__DFConstraint_FWD_DEFINED__ equ 1
endif

ifndef __FolderItem_FWD_DEFINED__
__FolderItem_FWD_DEFINED__ equ 1
endif

ifndef __FolderItems_FWD_DEFINED__
__FolderItems_FWD_DEFINED__ equ 1
endif

ifndef __FolderItemVerb_FWD_DEFINED__
__FolderItemVerb_FWD_DEFINED__ equ 1
endif

ifndef __FolderItemVerbs_FWD_DEFINED__
__FolderItemVerbs_FWD_DEFINED__ equ 1
endif

ifndef __Folder_FWD_DEFINED__
__Folder_FWD_DEFINED__ equ 1
endif

ifndef __Folder2_FWD_DEFINED__
__Folder2_FWD_DEFINED__ equ 1
endif

ifndef __Folder3_FWD_DEFINED__
__Folder3_FWD_DEFINED__ equ 1
endif

ifndef __FolderItem2_FWD_DEFINED__
__FolderItem2_FWD_DEFINED__ equ 1
endif

ifndef __ShellFolderItem_FWD_DEFINED__
__ShellFolderItem_FWD_DEFINED__ equ 1
ShellFolderItem		typedef ShellFolderItem
endif

ifndef __FolderItems2_FWD_DEFINED__
__FolderItems2_FWD_DEFINED__ equ 1
endif

ifndef __FolderItems3_FWD_DEFINED__
__FolderItems3_FWD_DEFINED__ equ 1
endif

ifndef __IShellLinkDual_FWD_DEFINED__
__IShellLinkDual_FWD_DEFINED__ equ 1
endif

ifndef __IShellLinkDual2_FWD_DEFINED__
__IShellLinkDual2_FWD_DEFINED__ equ 1
endif

ifndef __ShellLinkObject_FWD_DEFINED__
__ShellLinkObject_FWD_DEFINED__ equ 1
ShellLinkObject		typedef ShellLinkObject
endif

ifndef __IShellFolderViewDual_FWD_DEFINED__
__IShellFolderViewDual_FWD_DEFINED__ equ 1
endif

ifndef __IShellFolderViewDual2_FWD_DEFINED__
__IShellFolderViewDual2_FWD_DEFINED__ equ 1
endif

ifndef __IShellFolderViewDual3_FWD_DEFINED__
__IShellFolderViewDual3_FWD_DEFINED__ equ 1
endif

ifndef __ShellFolderView_FWD_DEFINED__
__ShellFolderView_FWD_DEFINED__ equ 1
ShellFolderView		typedef ShellFolderView
endif

ifndef __IShellDispatch_FWD_DEFINED__
__IShellDispatch_FWD_DEFINED__ equ 1
endif

ifndef __IShellDispatch2_FWD_DEFINED__
__IShellDispatch2_FWD_DEFINED__ equ 1
endif

ifndef __IShellDispatch3_FWD_DEFINED__
__IShellDispatch3_FWD_DEFINED__ equ 1
endif

ifndef __IShellDispatch4_FWD_DEFINED__
__IShellDispatch4_FWD_DEFINED__ equ 1
endif

ifndef __IShellDispatch5_FWD_DEFINED__
__IShellDispatch5_FWD_DEFINED__ equ 1
endif

ifndef __Shell_FWD_DEFINED__
__Shell_FWD_DEFINED__ equ 1
Shell			typedef Shell
endif

ifndef __ShellDispatchInproc_FWD_DEFINED__
__ShellDispatchInproc_FWD_DEFINED__ equ 1
ShellDispatchInproc	typedef ShellDispatchInproc
endif

ifndef __IFileSearchBand_FWD_DEFINED__
__IFileSearchBand_FWD_DEFINED__ equ 1
endif

ifndef __FileSearchBand_FWD_DEFINED__
__FileSearchBand_FWD_DEFINED__ equ 1
FileSearchBand		typedef FileSearchBand
endif

ifndef __IWebWizardHost_FWD_DEFINED__
__IWebWizardHost_FWD_DEFINED__ equ 1
endif

ifndef __INewWDEvents_FWD_DEFINED__
__INewWDEvents_FWD_DEFINED__ equ 1
endif

ifndef __IAutoComplete_FWD_DEFINED__
__IAutoComplete_FWD_DEFINED__ equ 1
endif

ifndef __IAutoComplete2_FWD_DEFINED__
__IAutoComplete2_FWD_DEFINED__ equ 1
endif

ifndef __IEnumACString_FWD_DEFINED__
__IEnumACString_FWD_DEFINED__ equ 1
endif

ifndef __IAsyncOperation_FWD_DEFINED__
__IAsyncOperation_FWD_DEFINED__ equ 1
endif

include ocidl.inc
.xlist

DECLSPEC_UUID("35f1a0d0-3e9a-11d2-8499-005345000000")

OfflineFolderStatus	typedef SDWORD
OFS_INACTIVE		equ -1
OFS_ONLINE		equ ( OFS_INACTIVE + 1 )
OFS_OFFLINE		equ ( OFS_ONLINE + 1 )
OFS_SERVERBACK		equ ( OFS_OFFLINE + 1 )
OFS_DIRTYCACHE		equ ( OFS_SERVERBACK + 1 )

DECLSPEC_UUID("742A99A0-C77E-11D0-A32C-00A0C91EEDBA")

ShellFolderViewOptions	typedef SDWORD
SFVVO_SHOWALLOBJECTS	equ 0x1
SFVVO_SHOWEXTENSIONS	equ 0x2
SFVVO_SHOWCOMPCOLOR	equ 0x8
SFVVO_SHOWSYSFILES	equ 0x20
SFVVO_WIN95CLASSIC	equ 0x40
SFVVO_DOUBLECLICKINWEBVIEW  equ 0x80
SFVVO_DESKTOPHTML	equ 0x200

DECLSPEC_UUID("CA31EA20-48D0-11CF-8350-444553540000")

ShellSpecialFolderConstants typedef SDWORD
ssfDESKTOP		equ 0
ssfPROGRAMS		equ 0x2
ssfCONTROLS		equ 0x3
ssfPRINTERS		equ 0x4
ssfPERSONAL		equ 0x5
ssfFAVORITES		equ 0x6
ssfSTARTUP		equ 0x7
ssfRECENT		equ 0x8
ssfSENDTO		equ 0x9
ssfBITBUCKET		equ 0xa
ssfSTARTMENU		equ 0xb
ssfDESKTOPDIRECTORY	equ 0x10
ssfDRIVES		equ 0x11
ssfNETWORK		equ 0x12
ssfNETHOOD		equ 0x13
ssfFONTS		equ 0x14
ssfTEMPLATES		equ 0x15
ssfCOMMONSTARTMENU	equ 0x16
ssfCOMMONPROGRAMS	equ 0x17
ssfCOMMONSTARTUP	equ 0x18
ssfCOMMONDESKTOPDIR	equ 0x19
ssfAPPDATA		equ 0x1a
ssfPRINTHOOD		equ 0x1b
ssfLOCALAPPDATA		equ 0x1c
ssfALTSTARTUP		equ 0x1d
ssfCOMMONALTSTARTUP	equ 0x1e
ssfCOMMONFAVORITES	equ 0x1f
ssfINTERNETCACHE	equ 0x20
ssfCOOKIES		equ 0x21
ssfHISTORY		equ 0x22
ssfCOMMONAPPDATA	equ 0x23
ssfWINDOWS		equ 0x24
ssfSYSTEM		equ 0x25
ssfPROGRAMFILES		equ 0x26
ssfMYPICTURES		equ 0x27
ssfPROFILE		equ 0x28
ssfSYSTEMx86		equ 0x29
ssfPROGRAMFILESx86	equ 0x30

externdef		LIBID_Shell32:IID
externdef		__MIDL_itf_shldisp_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shldisp_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __Shell32_LIBRARY_DEFINED__
__Shell32_LIBRARY_DEFINED__ equ 1


ifndef __IFolderViewOC_INTERFACE_DEFINED__
__IFolderViewOC_INTERFACE_DEFINED__ equ 1


externdef		IID_IFolderViewOC:IID

IFolderViewOC		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	SetFolderView, :ptr
IFolderViewOC		ENDS
LPIFolderViewOC		typedef ptr IFolderViewOC

endif

ifndef __DShellFolderViewEvents_DISPINTERFACE_DEFINED__
__DShellFolderViewEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DShellFolderViewEvents:IID

DShellFolderViewEvents	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
DShellFolderViewEvents	ENDS
LPDShellFolderViewEvents typedef ptr DShellFolderViewEvents

endif

externdef		CLSID_ShellFolderViewOC:CLSID

ifndef __DFConstraint_INTERFACE_DEFINED__
__DFConstraint_INTERFACE_DEFINED__ equ 1


externdef		IID_DFConstraint:IID
DFConstraint		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	get_Value, :ptr
DFConstraint		ENDS
LPDFConstraint		typedef ptr DFConstraint

endif

ifndef __FolderItem_INTERFACE_DEFINED__
__FolderItem_INTERFACE_DEFINED__ equ 1


FolderItem		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	put_Name, :BSTR
	STDMETHOD	get_Path, :ptr
	STDMETHOD	get_GetLink, :ptr
	STDMETHOD	get_GetFolder, :ptr
	STDMETHOD	get_IsLink, :ptr
	STDMETHOD	get_IsFolder, :ptr
	STDMETHOD	get_IsFileSystem, :ptr
	STDMETHOD	get_IsBrowsable, :ptr
	STDMETHOD	get_ModifyDate, :ptr
	STDMETHOD	put_ModifyDate, :DATE
	STDMETHOD	get_Size, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	Verbs, :ptr
	STDMETHOD	InvokeVerb, :VARIANT
FolderItem		ENDS
LPFOLDERITEM		typedef ptr FolderItem
LPFolderItem		typedef ptr FolderItem
externdef		IID_FolderItem:IID

endif


ifndef __FolderItems_INTERFACE_DEFINED__
__FolderItems_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItems:IID
FolderItems		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	Item, :VARIANT, :ptr
	STDMETHOD	_NewEnum, :ptr
FolderItems		ENDS
LPFolderItems		typedef ptr FolderItems

endif

ifndef __FolderItemVerb_INTERFACE_DEFINED__
__FolderItemVerb_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItemVerb:IID
FolderItemVerb		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	DoIt
FolderItemVerb		ENDS
LPFolderItemVerb	typedef ptr FolderItemVerb

endif

ifndef __FolderItemVerbs_INTERFACE_DEFINED__
__FolderItemVerbs_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItemVerbs:IID
FolderItemVerbs		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	Item, :VARIANT, :ptr
	STDMETHOD	_NewEnum, :ptr
FolderItemVerbs		ENDS
LPFolderItemVerbs	typedef ptr FolderItemVerbs

endif

ifndef __Folder_INTERFACE_DEFINED__
__Folder_INTERFACE_DEFINED__ equ 1


externdef		IID_Folder:IID
Folder			STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Title, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_ParentFolder, :ptr
	STDMETHOD	Items, :ptr
	STDMETHOD	ParseName, :BSTR, :ptr
	STDMETHOD	NewFolder, :BSTR, :VARIANT
	STDMETHOD	MoveHere, :VARIANT, :VARIANT
	STDMETHOD	CopyHere, :VARIANT, :VARIANT
	STDMETHOD	GetDetailsOf, :VARIANT, :SINT, :ptr
Folder			ENDS
LPFolder		typedef ptr Folder

endif

ifndef __Folder2_INTERFACE_DEFINED__
__Folder2_INTERFACE_DEFINED__ equ 1


externdef		IID_Folder2:IID
Folder2			STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Title, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_ParentFolder, :ptr
	STDMETHOD	Items, :ptr
	STDMETHOD	ParseName, :BSTR, :ptr
	STDMETHOD	NewFolder, :BSTR, :VARIANT
	STDMETHOD	MoveHere, :VARIANT, :VARIANT
	STDMETHOD	CopyHere, :VARIANT, :VARIANT
	STDMETHOD	GetDetailsOf, :VARIANT, :SINT, :ptr
	STDMETHOD	get_Self, :ptr
	STDMETHOD	get_OfflineStatus, :ptr
	STDMETHOD	Synchronize
	STDMETHOD	get_HaveToShowWebViewBarricade, :ptr
	STDMETHOD	DismissedWebViewBarricade
Folder2			ENDS
LPFolder2		typedef ptr Folder2

endif


ifndef __Folder3_INTERFACE_DEFINED__
__Folder3_INTERFACE_DEFINED__ equ 1


externdef		IID_Folder3:IID
Folder3			STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Title, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_ParentFolder, :ptr
	STDMETHOD	Items, :ptr
	STDMETHOD	ParseName, :BSTR, :ptr
	STDMETHOD	NewFolder, :BSTR, :VARIANT
	STDMETHOD	MoveHere, :VARIANT, :VARIANT
	STDMETHOD	CopyHere, :VARIANT, :VARIANT
	STDMETHOD	GetDetailsOf, :VARIANT, :SINT, :ptr
	STDMETHOD	get_Self, :ptr
	STDMETHOD	get_OfflineStatus, :ptr
	STDMETHOD	Synchronize
	STDMETHOD	get_HaveToShowWebViewBarricade, :ptr
	STDMETHOD	DismissedWebViewBarricade
	STDMETHOD	get_ShowWebViewBarricade, :ptr
	STDMETHOD	put_ShowWebViewBarricade, :VARIANT_BOOL
Folder3			ENDS
LPFolder3		typedef ptr Folder3

endif


ifndef __FolderItem2_INTERFACE_DEFINED__
__FolderItem2_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItem2:IID
FolderItem2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Name, :ptr
	STDMETHOD	put_Name, :BSTR
	STDMETHOD	get_Path, :ptr
	STDMETHOD	get_GetLink, :ptr
	STDMETHOD	get_GetFolder, :ptr
	STDMETHOD	get_IsLink, :ptr
	STDMETHOD	get_IsFolder, :ptr
	STDMETHOD	get_IsFileSystem, :ptr
	STDMETHOD	get_IsBrowsable, :ptr
	STDMETHOD	get_ModifyDate, :ptr
	STDMETHOD	put_ModifyDate, :DATE
	STDMETHOD	get_Size, :ptr
	STDMETHOD	get_Type, :ptr
	STDMETHOD	Verbs, :ptr
	STDMETHOD	InvokeVerb, :VARIANT
	STDMETHOD	InvokeVerbEx, :VARIANT, :VARIANT
	STDMETHOD	ExtendedProperty, :BSTR, :ptr
FolderItem2		ENDS
LPFolderItem2		typedef ptr FolderItem2

endif

externdef		CLSID_ShellFolderItem:CLSID

ifndef __FolderItems2_INTERFACE_DEFINED__
__FolderItems2_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItems2:IID
FolderItems2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	Item, :VARIANT, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	InvokeVerbEx, :VARIANT, :VARIANT
FolderItems2		ENDS
LPFolderItems2		typedef ptr FolderItems2

endif

ifndef __FolderItems3_INTERFACE_DEFINED__
__FolderItems3_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItems3:IID
FolderItems3		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Count, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	Item, :VARIANT, :ptr
	STDMETHOD	_NewEnum, :ptr
	STDMETHOD	InvokeVerbEx, :VARIANT, :VARIANT
	STDMETHOD	Filter, :LONG, :BSTR
	STDMETHOD	get_Verbs, :ptr
FolderItems3		ENDS
LPFolderItems3		typedef ptr FolderItems3

endif

ifndef __IShellLinkDual_INTERFACE_DEFINED__
__IShellLinkDual_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellLinkDual:IID
IShellLinkDual		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Path, :ptr
	STDMETHOD	put_Path, :BSTR
	STDMETHOD	get_Description, :ptr
	STDMETHOD	put_Description, :BSTR
	STDMETHOD	get_WorkingDirectory, :ptr
	STDMETHOD	put_WorkingDirectory, :BSTR
	STDMETHOD	get_Arguments, :ptr
	STDMETHOD	put_Arguments, :BSTR
	STDMETHOD	get_Hotkey, :ptr
	STDMETHOD	put_Hotkey, :SINT
	STDMETHOD	get_ShowCommand, :ptr
	STDMETHOD	put_ShowCommand, :SINT
	STDMETHOD	Resolve, :SINT
	STDMETHOD	GetIconLocation, :ptr, :ptr
	STDMETHOD	SetIconLocation, :BSTR, :SINT
	STDMETHOD	Save, :VARIANT
IShellLinkDual		ENDS
LPIShellLinkDual	typedef ptr IShellLinkDual

endif


ifndef __IShellLinkDual2_INTERFACE_DEFINED__
__IShellLinkDual2_INTERFACE_DEFINED__ equ 1



externdef		IID_IShellLinkDual2:IID
IShellLinkDual2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Path, :ptr
	STDMETHOD	put_Path, :BSTR
	STDMETHOD	get_Description, :ptr
	STDMETHOD	put_Description, :BSTR
	STDMETHOD	get_WorkingDirectory, :ptr
	STDMETHOD	put_WorkingDirectory, :BSTR
	STDMETHOD	get_Arguments, :ptr
	STDMETHOD	put_Arguments, :BSTR
	STDMETHOD	get_Hotkey, :ptr
	STDMETHOD	put_Hotkey, :SINT
	STDMETHOD	get_ShowCommand, :ptr
	STDMETHOD	put_ShowCommand, :SINT
	STDMETHOD	Resolve, :SINT
	STDMETHOD	GetIconLocation, :ptr, :ptr
	STDMETHOD	SetIconLocation, :BSTR, :SINT
	STDMETHOD	Save, :VARIANT
	STDMETHOD	get_Target, :ptr
IShellLinkDual2		ENDS
LPIShellLinkDual2	typedef ptr IShellLinkDual2

endif

externdef		CLSID_ShellLinkObject:CLSID

ifndef __IShellFolderViewDual_INTERFACE_DEFINED__
__IShellFolderViewDual_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFolderViewDual:IID
IShellFolderViewDual	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Folder, :ptr
	STDMETHOD	SelectedItems, :ptr
	STDMETHOD	get_FocusedItem, :ptr
	STDMETHOD	SelectItem, :ptr, :SINT
	STDMETHOD	PopupItemMenu, :ptr, :VARIANT, :VARIANT, :ptr
	STDMETHOD	get_Script, :ptr
	STDMETHOD	get_ViewOptions, :ptr
IShellFolderViewDual	ENDS
LPIShellFolderViewDual	typedef ptr IShellFolderViewDual

endif

ifndef __IShellFolderViewDual2_INTERFACE_DEFINED__
__IShellFolderViewDual2_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFolderViewDual2:IID
IShellFolderViewDual2	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Folder, :ptr
	STDMETHOD	SelectedItems, :ptr
	STDMETHOD	get_FocusedItem, :ptr
	STDMETHOD	SelectItem, :ptr, :SINT
	STDMETHOD	PopupItemMenu, :ptr, :VARIANT, :VARIANT, :ptr
	STDMETHOD	get_Script, :ptr
	STDMETHOD	get_ViewOptions, :ptr
	STDMETHOD	get_CurrentViewMode, :ptr
	STDMETHOD	put_CurrentViewMode, :UINT
	STDMETHOD	SelectItemRelative, :SINT
IShellFolderViewDual2	ENDS
LPIShellFolderViewDual2 typedef ptr IShellFolderViewDual2

endif

ifndef __IShellFolderViewDual3_INTERFACE_DEFINED__
__IShellFolderViewDual3_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFolderViewDual3:IID

IShellFolderViewDual3 STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	get_Folder, :ptr
	STDMETHOD	SelectedItems, :ptr
	STDMETHOD	get_FocusedItem, :ptr
	STDMETHOD	SelectItem, :ptr, :SINT
	STDMETHOD	PopupItemMenu, :ptr, :VARIANT, :VARIANT, :ptr
	STDMETHOD	get_Script, :ptr
	STDMETHOD	get_ViewOptions, :ptr
	STDMETHOD	get_CurrentViewMode, :ptr
	STDMETHOD	put_CurrentViewMode, :UINT
	STDMETHOD	SelectItemRelative, :SINT
	STDMETHOD	get_GroupBy, :ptr
	STDMETHOD	put_GroupBy, :BSTR
	STDMETHOD	get_FolderFlags, :ptr
	STDMETHOD	put_FolderFlags, :DWORD
	STDMETHOD	get_SortColumns, :ptr
	STDMETHOD	put_SortColumns, :BSTR
	STDMETHOD	put_IconSize, :SINT
	STDMETHOD	get_IconSize, :ptr
	STDMETHOD	FilterView, :BSTR
IShellFolderViewDual3	ENDS
LPIShellFolderViewDual3 typedef ptr IShellFolderViewDual3

endif

externdef		CLSID_ShellFolderView:CLSID

ifndef __IShellDispatch_INTERFACE_DEFINED__
__IShellDispatch_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch:IID
IShellDispatch		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	NameSpace, :VARIANT, :ptr
	STDMETHOD	BrowseForFolder, :LONG, :BSTR, :LONG, :VARIANT, :ptr
	STDMETHOD	Windows, :ptr
	STDMETHOD	Open, :VARIANT
	STDMETHOD	Explore, :VARIANT
	STDMETHOD	MinimizeAll
	STDMETHOD	UndoMinimizeALL
	STDMETHOD	FileRun
	STDMETHOD	CascadeWindows
	STDMETHOD	TileVertically
	STDMETHOD	TileHorizontally
	STDMETHOD	ShutdownWindows
	STDMETHOD	Suspend
	STDMETHOD	EjectPC
	STDMETHOD	SetTime
	STDMETHOD	TrayProperties
	STDMETHOD	Help
	STDMETHOD	FindFiles
	STDMETHOD	FindComputer
	STDMETHOD	RefreshMenu
	STDMETHOD	ControlPanelItem, :BSTR
IShellDispatch		ENDS
LPIShellDispatch	typedef ptr IShellDispatch

endif


ifndef __IShellDispatch2_INTERFACE_DEFINED__
__IShellDispatch2_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch2:IID
IShellDispatch2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	NameSpace, :VARIANT, :ptr
	STDMETHOD	BrowseForFolder, :LONG, :BSTR, :LONG, :VARIANT, :ptr
	STDMETHOD	Windows, :ptr
	STDMETHOD	Open, :VARIANT
	STDMETHOD	Explore, :VARIANT
	STDMETHOD	MinimizeAll
	STDMETHOD	UndoMinimizeALL
	STDMETHOD	FileRun
	STDMETHOD	CascadeWindows
	STDMETHOD	TileVertically
	STDMETHOD	TileHorizontally
	STDMETHOD	ShutdownWindows
	STDMETHOD	Suspend
	STDMETHOD	EjectPC
	STDMETHOD	SetTime
	STDMETHOD	TrayProperties
	STDMETHOD	Help
	STDMETHOD	FindFiles
	STDMETHOD	FindComputer
	STDMETHOD	RefreshMenu
	STDMETHOD	ControlPanelItem, :BSTR
	STDMETHOD	IsRestricted, :BSTR, :BSTR, :ptr
	STDMETHOD	ShellExecute, :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
	STDMETHOD	FindPrinter, :BSTR, :BSTR, :BSTR
	STDMETHOD	GetSystemInformation, :BSTR, :ptr
	STDMETHOD	ServiceStart, :BSTR, :VARIANT, :ptr
	STDMETHOD	ServiceStop, :BSTR, :VARIANT, :ptr
	STDMETHOD	IsServiceRunning, :BSTR, :ptr
	STDMETHOD	CanStartStopService, :BSTR, :ptr
	STDMETHOD	ShowBrowserBar, :BSTR, :VARIANT, :ptr
IShellDispatch2		ENDS
LPIShellDispatch2	typedef ptr IShellDispatch2

endif

ifndef __IShellDispatch3_INTERFACE_DEFINED__
__IShellDispatch3_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch3:IID
IShellDispatch3		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	NameSpace, :VARIANT, :ptr
	STDMETHOD	BrowseForFolder, :LONG, :BSTR, :LONG, :VARIANT, :ptr
	STDMETHOD	Windows, :ptr
	STDMETHOD	Open, :VARIANT
	STDMETHOD	Explore, :VARIANT
	STDMETHOD	MinimizeAll
	STDMETHOD	UndoMinimizeALL
	STDMETHOD	FileRun
	STDMETHOD	CascadeWindows
	STDMETHOD	TileVertically
	STDMETHOD	TileHorizontally
	STDMETHOD	ShutdownWindows
	STDMETHOD	Suspend
	STDMETHOD	EjectPC
	STDMETHOD	SetTime
	STDMETHOD	TrayProperties
	STDMETHOD	Help
	STDMETHOD	FindFiles
	STDMETHOD	FindComputer
	STDMETHOD	RefreshMenu
	STDMETHOD	ControlPanelItem, :BSTR
	STDMETHOD	IsRestricted, :BSTR, :BSTR, :ptr
	STDMETHOD	ShellExecute, :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
	STDMETHOD	FindPrinter, :BSTR, :BSTR, :BSTR
	STDMETHOD	GetSystemInformation, :BSTR, :ptr
	STDMETHOD	ServiceStart, :BSTR, :VARIANT, :ptr
	STDMETHOD	ServiceStop, :BSTR, :VARIANT, :ptr
	STDMETHOD	IsServiceRunning, :BSTR, :ptr
	STDMETHOD	CanStartStopService, :BSTR, :ptr
	STDMETHOD	ShowBrowserBar, :BSTR, :VARIANT, :ptr
	STDMETHOD	AddToRecent, :VARIANT, :BSTR
IShellDispatch3		ENDS
LPIShellDispatch3	typedef ptr IShellDispatch3

endif


ifndef __IShellDispatch4_INTERFACE_DEFINED__
__IShellDispatch4_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch4:IID
IShellDispatch4		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	NameSpace, :VARIANT, :ptr
	STDMETHOD	BrowseForFolder, :LONG, :BSTR, :LONG, :VARIANT, :ptr
	STDMETHOD	Windows, :ptr
	STDMETHOD	Open, :VARIANT
	STDMETHOD	Explore, :VARIANT
	STDMETHOD	MinimizeAll
	STDMETHOD	UndoMinimizeALL
	STDMETHOD	FileRun
	STDMETHOD	CascadeWindows
	STDMETHOD	TileVertically
	STDMETHOD	TileHorizontally
	STDMETHOD	ShutdownWindows
	STDMETHOD	Suspend
	STDMETHOD	EjectPC
	STDMETHOD	SetTime
	STDMETHOD	TrayProperties
	STDMETHOD	Help
	STDMETHOD	FindFiles
	STDMETHOD	FindComputer
	STDMETHOD	RefreshMenu
	STDMETHOD	ControlPanelItem, :BSTR
	STDMETHOD	IsRestricted, :BSTR, :BSTR, :ptr
	STDMETHOD	ShellExecute, :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
	STDMETHOD	FindPrinter, :BSTR, :BSTR, :BSTR
	STDMETHOD	GetSystemInformation, :BSTR, :ptr
	STDMETHOD	ServiceStart, :BSTR, :VARIANT, :ptr
	STDMETHOD	ServiceStop, :BSTR, :VARIANT, :ptr
	STDMETHOD	IsServiceRunning, :BSTR, :ptr
	STDMETHOD	CanStartStopService, :BSTR, :ptr
	STDMETHOD	ShowBrowserBar, :BSTR, :VARIANT, :ptr
	STDMETHOD	AddToRecent, :VARIANT, :BSTR
	STDMETHOD	WindowsSecurity
	STDMETHOD	ToggleDesktop
	STDMETHOD	ExplorerPolicy, :BSTR, :ptr
	STDMETHOD	GetSetting, :LONG, :ptr
IShellDispatch4		ENDS
LPIShellDispatch4	typedef ptr IShellDispatch4

endif

ifndef __IShellDispatch5_INTERFACE_DEFINED__
__IShellDispatch5_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch5:IID
IShellDispatch5		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_Application, :ptr
	STDMETHOD	get_Parent, :ptr
	STDMETHOD	NameSpace, :VARIANT, :ptr
	STDMETHOD	BrowseForFolder, :LONG, :BSTR, :LONG, :VARIANT, :ptr
	STDMETHOD	Windows, :ptr
	STDMETHOD	Open, :VARIANT
	STDMETHOD	Explore, :VARIANT
	STDMETHOD	MinimizeAll
	STDMETHOD	UndoMinimizeALL
	STDMETHOD	FileRun
	STDMETHOD	CascadeWindows
	STDMETHOD	TileVertically
	STDMETHOD	TileHorizontally
	STDMETHOD	ShutdownWindows
	STDMETHOD	Suspend
	STDMETHOD	EjectPC
	STDMETHOD	SetTime
	STDMETHOD	TrayProperties
	STDMETHOD	Help
	STDMETHOD	FindFiles
	STDMETHOD	FindComputer
	STDMETHOD	RefreshMenu
	STDMETHOD	ControlPanelItem, :BSTR
	STDMETHOD	IsRestricted, :BSTR, :BSTR, :ptr
	STDMETHOD	ShellExecute, :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
	STDMETHOD	FindPrinter, :BSTR, :BSTR, :BSTR
	STDMETHOD	GetSystemInformation, :BSTR, :ptr
	STDMETHOD	ServiceStart, :BSTR, :VARIANT, :ptr
	STDMETHOD	ServiceStop, :BSTR, :VARIANT, :ptr
	STDMETHOD	IsServiceRunning, :BSTR, :ptr
	STDMETHOD	CanStartStopService, :BSTR, :ptr
	STDMETHOD	ShowBrowserBar, :BSTR, :VARIANT, :ptr
	STDMETHOD	AddToRecent, :VARIANT, :BSTR
	STDMETHOD	WindowsSecurity
	STDMETHOD	ToggleDesktop
	STDMETHOD	ExplorerPolicy, :BSTR, :ptr
	STDMETHOD	GetSetting, :LONG, :ptr
	STDMETHOD	WindowSwitcher
IShellDispatch5		ENDS
LPIShellDispatch5	typedef ptr IShellDispatch5

endif

externdef		CLSID_Shell:CLSID
externdef		CLSID_ShellDispatchInproc:CLSID

ifndef __IFileSearchBand_INTERFACE_DEFINED__
__IFileSearchBand_INTERFACE_DEFINED__ equ 1


externdef		IID_IFileSearchBand:IID
IFileSearchBand		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	SetFocus
	STDMETHOD	SetSearchParameters, :ptr, :VARIANT_BOOL, :ptr, :ptr
	STDMETHOD	get_SearchID, :ptr
	STDMETHOD	get_Scope, :ptr
	STDMETHOD	get_QueryFile, :ptr
IFileSearchBand		ENDS
LPIFileSearchBand	typedef ptr IFileSearchBand

endif

externdef		CLSID_FileSearchBand:CLSID

ifndef __IWebWizardHost_INTERFACE_DEFINED__
__IWebWizardHost_INTERFACE_DEFINED__ equ 1


externdef		IID_IWebWizardHost:IID
IWebWizardHost		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	FinalBack
	STDMETHOD	FinalNext
	STDMETHOD	Cancel
	STDMETHOD	put_Caption, :BSTR
	STDMETHOD	get_Caption, :ptr
	STDMETHOD	put_Property, :BSTR, :ptr
	STDMETHOD	get_Property, :BSTR, :ptr
	STDMETHOD	SetWizardButtons, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL
	STDMETHOD	SetHeaderText, :BSTR, :BSTR
IWebWizardHost		ENDS
LPIWebWizardHost	typedef ptr IWebWizardHost

endif

ifndef __INewWDEvents_INTERFACE_DEFINED__
__INewWDEvents_INTERFACE_DEFINED__ equ 1


externdef		IID_INewWDEvents:IID
INewWDEvents		STRUC
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	FinalBack
	STDMETHOD	FinalNext
	STDMETHOD	Cancel
	STDMETHOD	put_Caption, :BSTR
	STDMETHOD	get_Caption, :ptr
	STDMETHOD	put_Property, :BSTR, :ptr
	STDMETHOD	get_Property, :BSTR, :ptr
	STDMETHOD	SetWizardButtons, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL
	STDMETHOD	SetHeaderText, :BSTR, :BSTR
	STDMETHOD	PassportAuthenticate, :BSTR, :ptr
INewWDEvents		ENDS
LPINewWDEvents		typedef ptr INewWDEvents

endif
endif


externdef		__MIDL_itf_shldisp_0001_0067_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shldisp_0001_0067_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAutoComplete_INTERFACE_DEFINED__
__IAutoComplete_INTERFACE_DEFINED__ equ 1


IAutoComplete		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Init, :HWND, :ptr, :LPCWSTR, :LPCWSTR
	STDMETHOD	Enable, :BOOL
IAutoComplete		ENDS
LPAUTOCOMPLETE		typedef ptr IAutoComplete
LPIAutoComplete		typedef ptr IAutoComplete
externdef		IID_IAutoComplete:IID

endif

ifndef __IAutoComplete2_INTERFACE_DEFINED__
__IAutoComplete2_INTERFACE_DEFINED__ equ 1


tagAUTOCOMPLETEOPTIONS	typedef SDWORD
ACO_NONE		equ 0
ACO_AUTOSUGGEST		equ 0x1
ACO_AUTOAPPEND		equ 0x2
ACO_SEARCH		equ 0x4
ACO_FILTERPREFIXES	equ 0x8
ACO_USETAB		equ 0x10
ACO_UPDOWNKEYDROPSLIST	equ 0x20
ACO_RTLREADING		equ 0x40
ACO_WORD_FILTER		equ 0x80
ACO_NOPREFIXFILTERING	equ 0x100

IAutoComplete2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Init, :HWND, :ptr, :LPCWSTR, :LPCWSTR
	STDMETHOD	Enable, :BOOL
	STDMETHOD	SetOptions, :DWORD
	STDMETHOD	GetOptions, :ptr
IAutoComplete2		ENDS
LPAUTOCOMPLETE2		typedef ptr IAutoComplete2
LPIAutoComplete2	typedef ptr IAutoComplete2
externdef		IID_IAutoComplete2:IID

endif


externdef		__MIDL_itf_shldisp_0000_0002_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shldisp_0000_0002_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumACString_INTERFACE_DEFINED__
__IEnumACString_INTERFACE_DEFINED__ equ 1


tagACENUMOPTION		typedef SDWORD
ACEO_NONE		equ 0
ACEO_MOSTRECENTFIRST	equ 0x1
ACEO_FIRSTUNUSED	equ 0x10000


externdef		IID_IEnumACString:IID
IEnumACString		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :ULONG, :ptr, :ptr
	STDMETHOD	Skip, :ULONG
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
	STDMETHOD	NextItem, :LPWSTR, :ULONG, :ptr
	STDMETHOD	SetEnumOptions, :DWORD
	STDMETHOD	GetEnumOptions, :ptr
IEnumACString		ENDS
PENUMACSTRING		typedef ptr IEnumACString
LPENUMACSTRING		typedef ptr IEnumACString
LPIEnumACString		typedef ptr IEnumACString

endif

externdef		__MIDL_itf_shldisp_0000_0003_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shldisp_0000_0003_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAsyncOperation_INTERFACE_DEFINED__
__IAsyncOperation_INTERFACE_DEFINED__ equ 1

IAsyncOperation		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetAsyncMode, :BOOL
	STDMETHOD	GetAsyncMode, :ptr
	STDMETHOD	StartOperation, :ptr
	STDMETHOD	InOperation, :ptr
	STDMETHOD	EndOperation, :HRESULT, :ptr, :DWORD
IAsyncOperation		ENDS
LPIAsyncOperation	typedef ptr IAsyncOperation
LPASYNCOPERATION	typedef ptr IAsyncOperation
externdef		IID_IAsyncOperation:IID

endif

.list
endif ; __shldisp_h__
