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

.comdef IFolderViewOC
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    SetFolderView	proc :ptr
    .ends

endif

ifndef __DShellFolderViewEvents_DISPINTERFACE_DEFINED__
__DShellFolderViewEvents_DISPINTERFACE_DEFINED__ equ 1


externdef		DIID_DShellFolderViewEvents:IID

.comdef DShellFolderViewEvents
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    .ends

endif

externdef		CLSID_ShellFolderViewOC:CLSID

ifndef __DFConstraint_INTERFACE_DEFINED__
__DFConstraint_INTERFACE_DEFINED__ equ 1


externdef		IID_DFConstraint:IID
.comdef DFConstraint
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Name		proc :ptr
    get_Value		proc :ptr
    .ends

endif

ifndef __FolderItem_INTERFACE_DEFINED__
__FolderItem_INTERFACE_DEFINED__ equ 1


.comdef FolderItem
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Path		proc :ptr
    get_GetLink		proc :ptr
    get_GetFolder	proc :ptr
    get_IsLink		proc :ptr
    get_IsFolder	proc :ptr
    get_IsFileSystem	proc :ptr
    get_IsBrowsable	proc :ptr
    get_ModifyDate	proc :ptr
    put_ModifyDate	proc :DATE
    get_Size		proc :ptr
    get_Type		proc :ptr
    Verbs		proc :ptr
    InvokeVerb		proc :VARIANT
    .ends
LPFOLDERITEM		typedef ptr FolderItem
externdef		IID_FolderItem:IID

endif


ifndef __FolderItems_INTERFACE_DEFINED__
__FolderItems_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItems:IID
.comdef FolderItems
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    Item		proc :VARIANT, :ptr
    _NewEnum		proc :ptr
    .ends

endif

ifndef __FolderItemVerb_INTERFACE_DEFINED__
__FolderItemVerb_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItemVerb:IID
.comdef FolderItemVerb
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Name		proc :ptr
    DoIt		proc
    .ends

endif

ifndef __FolderItemVerbs_INTERFACE_DEFINED__
__FolderItemVerbs_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItemVerbs:IID
.comdef FolderItemVerbs
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    Item		proc :VARIANT, :ptr
    _NewEnum		proc :ptr
    .ends

endif

ifndef __Folder_INTERFACE_DEFINED__
__Folder_INTERFACE_DEFINED__ equ 1


externdef		IID_Folder:IID
.comdef Folder
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Title		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_ParentFolder	proc :ptr
    Items		proc :ptr
    ParseName		proc :BSTR, :ptr
    NewFolder		proc :BSTR, :VARIANT
    MoveHere		proc :VARIANT, :VARIANT
    CopyHere		proc :VARIANT, :VARIANT
    GetDetailsOf	proc :VARIANT, :SINT, :ptr
    .ends

endif

ifndef __Folder2_INTERFACE_DEFINED__
__Folder2_INTERFACE_DEFINED__ equ 1


externdef		IID_Folder2:IID
.comdef Folder2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Title		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_ParentFolder	proc :ptr
    Items		proc :ptr
    ParseName		proc :BSTR, :ptr
    NewFolder		proc :BSTR, :VARIANT
    MoveHere		proc :VARIANT, :VARIANT
    CopyHere		proc :VARIANT, :VARIANT
    GetDetailsOf	proc :VARIANT, :SINT, :ptr
    get_Self		proc :ptr
    get_OfflineStatus	proc :ptr
    Synchronize		proc
    get_HaveToShowWebViewBarricade proc :ptr
    DismissedWebViewBarricade proc
    .ends

endif


ifndef __Folder3_INTERFACE_DEFINED__
__Folder3_INTERFACE_DEFINED__ equ 1


externdef		IID_Folder3:IID
.comdef Folder3
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Title		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_ParentFolder	proc :ptr
    Items		proc :ptr
    ParseName		proc :BSTR, :ptr
    NewFolder		proc :BSTR, :VARIANT
    MoveHere		proc :VARIANT, :VARIANT
    CopyHere		proc :VARIANT, :VARIANT
    GetDetailsOf	proc :VARIANT, :SINT, :ptr
    get_Self		proc :ptr
    get_OfflineStatus	proc :ptr
    Synchronize		proc
    get_HaveToShowWebViewBarricade proc :ptr
    DismissedWebViewBarricade proc
    get_ShowWebViewBarricade proc :ptr
    put_ShowWebViewBarricade proc :VARIANT_BOOL
    .ends

endif


ifndef __FolderItem2_INTERFACE_DEFINED__
__FolderItem2_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItem2:IID
.comdef FolderItem2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Path		proc :ptr
    get_GetLink		proc :ptr
    get_GetFolder	proc :ptr
    get_IsLink		proc :ptr
    get_IsFolder	proc :ptr
    get_IsFileSystem	proc :ptr
    get_IsBrowsable	proc :ptr
    get_ModifyDate	proc :ptr
    put_ModifyDate	proc :DATE
    get_Size		proc :ptr
    get_Type		proc :ptr
    Verbs		proc :ptr
    InvokeVerb		proc :VARIANT
    InvokeVerbEx	proc :VARIANT, :VARIANT
    ExtendedProperty	proc :BSTR, :ptr
    .ends

endif

externdef		CLSID_ShellFolderItem:CLSID

ifndef __FolderItems2_INTERFACE_DEFINED__
__FolderItems2_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItems2:IID
.comdef FolderItems2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    Item		proc :VARIANT, :ptr
    _NewEnum		proc :ptr
    InvokeVerbEx	proc :VARIANT, :VARIANT
    .ends

endif

ifndef __FolderItems3_INTERFACE_DEFINED__
__FolderItems3_INTERFACE_DEFINED__ equ 1


externdef		IID_FolderItems3:IID
.comdef FolderItems3
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Count		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    Item		proc :VARIANT, :ptr
    _NewEnum		proc :ptr
    InvokeVerbEx	proc :VARIANT, :VARIANT
    Filter		proc :LONG, :BSTR
    get_Verbs		proc :ptr
    .ends

endif

ifndef __IShellLinkDual_INTERFACE_DEFINED__
__IShellLinkDual_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellLinkDual:IID
.comdef IShellLinkDual
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Path		proc :ptr
    put_Path		proc :BSTR
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_WorkingDirectory proc :ptr
    put_WorkingDirectory proc :BSTR
    get_Arguments	proc :ptr
    put_Arguments	proc :BSTR
    get_Hotkey		proc :ptr
    put_Hotkey		proc :SINT
    get_ShowCommand	proc :ptr
    put_ShowCommand	proc :SINT
    Resolve		proc :SINT
    GetIconLocation	proc :ptr, :ptr
    SetIconLocation	proc :BSTR, :SINT
    Save		proc :VARIANT
    .ends

endif


ifndef __IShellLinkDual2_INTERFACE_DEFINED__
__IShellLinkDual2_INTERFACE_DEFINED__ equ 1



externdef		IID_IShellLinkDual2:IID
.comdef IShellLinkDual2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Path		proc :ptr
    put_Path		proc :BSTR
    get_Description	proc :ptr
    put_Description	proc :BSTR
    get_WorkingDirectory proc :ptr
    put_WorkingDirectory proc :BSTR
    get_Arguments	proc :ptr
    put_Arguments	proc :BSTR
    get_Hotkey		proc :ptr
    put_Hotkey		proc :SINT
    get_ShowCommand	proc :ptr
    put_ShowCommand	proc :SINT
    Resolve		proc :SINT
    GetIconLocation	proc :ptr, :ptr
    SetIconLocation	proc :BSTR, :SINT
    Save		proc :VARIANT
    get_Target		proc :ptr
    .ends

endif

externdef		CLSID_ShellLinkObject:CLSID

ifndef __IShellFolderViewDual_INTERFACE_DEFINED__
__IShellFolderViewDual_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFolderViewDual:IID
.comdef IShellFolderViewDual
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Folder		proc :ptr
    SelectedItems	proc :ptr
    get_FocusedItem	proc :ptr
    SelectItem		proc :ptr, :SINT
    PopupItemMenu	proc :ptr, :VARIANT, :VARIANT, :ptr
    get_Script		proc :ptr
    get_ViewOptions	proc :ptr
    .ends

endif

ifndef __IShellFolderViewDual2_INTERFACE_DEFINED__
__IShellFolderViewDual2_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFolderViewDual2:IID
.comdef IShellFolderViewDual2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Folder		proc :ptr
    SelectedItems	proc :ptr
    get_FocusedItem	proc :ptr
    SelectItem		proc :ptr, :SINT
    PopupItemMenu	proc :ptr, :VARIANT, :VARIANT, :ptr
    get_Script		proc :ptr
    get_ViewOptions	proc :ptr
    get_CurrentViewMode proc :ptr
    put_CurrentViewMode proc :UINT
    SelectItemRelative	proc :SINT
    .ends

endif

ifndef __IShellFolderViewDual3_INTERFACE_DEFINED__
__IShellFolderViewDual3_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellFolderViewDual3:IID

.comdef IShellFolderViewDual3
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Folder		proc :ptr
    SelectedItems	proc :ptr
    get_FocusedItem	proc :ptr
    SelectItem		proc :ptr, :SINT
    PopupItemMenu	proc :ptr, :VARIANT, :VARIANT, :ptr
    get_Script		proc :ptr
    get_ViewOptions	proc :ptr
    get_CurrentViewMode proc :ptr
    put_CurrentViewMode proc :UINT
    SelectItemRelative	proc :SINT
    get_GroupBy		proc :ptr
    put_GroupBy		proc :BSTR
    get_FolderFlags	proc :ptr
    put_FolderFlags	proc :DWORD
    get_SortColumns	proc :ptr
    put_SortColumns	proc :BSTR
    put_IconSize	proc :SINT
    get_IconSize	proc :ptr
    FilterView		proc :BSTR
    .ends

endif

externdef		CLSID_ShellFolderView:CLSID

ifndef __IShellDispatch_INTERFACE_DEFINED__
__IShellDispatch_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch:IID
.comdef IShellDispatch
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    NameSpace		proc :VARIANT, :ptr
    BrowseForFolder	proc :LONG, :BSTR, :LONG, :VARIANT, :ptr
    Windows		proc :ptr
    Open		proc :VARIANT
    Explore		proc :VARIANT
    MinimizeAll		proc
    UndoMinimizeALL	proc
    FileRun		proc
    CascadeWindows	proc
    TileVertically	proc
    TileHorizontally	proc
    ShutdownWindows	proc
    Suspend		proc
    EjectPC		proc
    SetTime		proc
    TrayProperties	proc
    Help		proc
    FindFiles		proc
    FindComputer	proc
    RefreshMenu		proc
    ControlPanelItem	proc :BSTR
    .ends

endif

ifndef __IShellDispatch2_INTERFACE_DEFINED__
__IShellDispatch2_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch2:IID
.comdef IShellDispatch2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    NameSpace		proc :VARIANT, :ptr
    BrowseForFolder	proc :LONG, :BSTR, :LONG, :VARIANT, :ptr
    Windows		proc :ptr
    Open		proc :VARIANT
    Explore		proc :VARIANT
    MinimizeAll		proc
    UndoMinimizeALL	proc
    FileRun		proc
    CascadeWindows	proc
    TileVertically	proc
    TileHorizontally	proc
    ShutdownWindows	proc
    Suspend		proc
    EjectPC		proc
    SetTime		proc
    TrayProperties	proc
    Help		proc
    FindFiles		proc
    FindComputer	proc
    RefreshMenu		proc
    ControlPanelItem	proc :BSTR
    IsRestricted	proc :BSTR, :BSTR, :ptr
    ShellExecute	proc :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
    FindPrinter		proc :BSTR, :BSTR, :BSTR
    GetSystemInformation proc :BSTR, :ptr
    ServiceStart	proc :BSTR, :VARIANT, :ptr
    ServiceStop		proc :BSTR, :VARIANT, :ptr
    IsServiceRunning	proc :BSTR, :ptr
    CanStartStopService proc :BSTR, :ptr
    ShowBrowserBar	proc :BSTR, :VARIANT, :ptr
    .ends

endif

ifndef __IShellDispatch3_INTERFACE_DEFINED__
__IShellDispatch3_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch3:IID
.comdef IShellDispatch3
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    NameSpace		proc :VARIANT, :ptr
    BrowseForFolder	proc :LONG, :BSTR, :LONG, :VARIANT, :ptr
    Windows		proc :ptr
    Open		proc :VARIANT
    Explore		proc :VARIANT
    MinimizeAll		proc
    UndoMinimizeALL	proc
    FileRun		proc
    CascadeWindows	proc
    TileVertically	proc
    TileHorizontally	proc
    ShutdownWindows	proc
    Suspend		proc
    EjectPC		proc
    SetTime		proc
    TrayProperties	proc
    Help		proc
    FindFiles		proc
    FindComputer	proc
    RefreshMenu		proc
    ControlPanelItem	proc :BSTR
    IsRestricted	proc :BSTR, :BSTR, :ptr
    ShellExecute	proc :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
    FindPrinter		proc :BSTR, :BSTR, :BSTR
    GetSystemInformation proc :BSTR, :ptr
    ServiceStart	proc :BSTR, :VARIANT, :ptr
    ServiceStop		proc :BSTR, :VARIANT, :ptr
    IsServiceRunning	proc :BSTR, :ptr
    CanStartStopService proc :BSTR, :ptr
    ShowBrowserBar	proc :BSTR, :VARIANT, :ptr
    AddToRecent		proc :VARIANT, :BSTR
    .ends

endif


ifndef __IShellDispatch4_INTERFACE_DEFINED__
__IShellDispatch4_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch4:IID
.comdef IShellDispatch4
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    NameSpace		proc :VARIANT, :ptr
    BrowseForFolder	proc :LONG, :BSTR, :LONG, :VARIANT, :ptr
    Windows		proc :ptr
    Open		proc :VARIANT
    Explore		proc :VARIANT
    MinimizeAll		proc
    UndoMinimizeALL	proc
    FileRun		proc
    CascadeWindows	proc
    TileVertically	proc
    TileHorizontally	proc
    ShutdownWindows	proc
    Suspend		proc
    EjectPC		proc
    SetTime		proc
    TrayProperties	proc
    Help		proc
    FindFiles		proc
    FindComputer	proc
    RefreshMenu		proc
    ControlPanelItem	proc :BSTR
    IsRestricted	proc :BSTR, :BSTR, :ptr
    ShellExecute	proc :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
    FindPrinter		proc :BSTR, :BSTR, :BSTR
    GetSystemInformation proc :BSTR, :ptr
    ServiceStart	proc :BSTR, :VARIANT, :ptr
    ServiceStop		proc :BSTR, :VARIANT, :ptr
    IsServiceRunning	proc :BSTR, :ptr
    CanStartStopService proc :BSTR, :ptr
    ShowBrowserBar	proc :BSTR, :VARIANT, :ptr
    AddToRecent		proc :VARIANT, :BSTR
    WindowsSecurity	proc
    ToggleDesktop	proc
    ExplorerPolicy	proc :BSTR, :ptr
    GetSetting		proc :LONG, :ptr
    .ends

endif

ifndef __IShellDispatch5_INTERFACE_DEFINED__
__IShellDispatch5_INTERFACE_DEFINED__ equ 1


externdef		IID_IShellDispatch5:IID
.comdef IShellDispatch5
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    NameSpace		proc :VARIANT, :ptr
    BrowseForFolder	proc :LONG, :BSTR, :LONG, :VARIANT, :ptr
    Windows		proc :ptr
    Open		proc :VARIANT
    Explore		proc :VARIANT
    MinimizeAll		proc
    UndoMinimizeALL	proc
    FileRun		proc
    CascadeWindows	proc
    TileVertically	proc
    TileHorizontally	proc
    ShutdownWindows	proc
    Suspend		proc
    EjectPC		proc
    SetTime		proc
    TrayProperties	proc
    Help		proc
    FindFiles		proc
    FindComputer	proc
    RefreshMenu		proc
    ControlPanelItem	proc :BSTR
    IsRestricted	proc :BSTR, :BSTR, :ptr
    ShellExecute	proc :BSTR, :VARIANT, :VARIANT, :VARIANT, :VARIANT
    FindPrinter		proc :BSTR, :BSTR, :BSTR
    GetSystemInformation proc :BSTR, :ptr
    ServiceStart	proc :BSTR, :VARIANT, :ptr
    ServiceStop		proc :BSTR, :VARIANT, :ptr
    IsServiceRunning	proc :BSTR, :ptr
    CanStartStopService proc :BSTR, :ptr
    ShowBrowserBar	proc :BSTR, :VARIANT, :ptr
    AddToRecent		proc :VARIANT, :BSTR
    WindowsSecurity	proc
    ToggleDesktop	proc
    ExplorerPolicy	proc :BSTR, :ptr
    GetSetting		proc :LONG, :ptr
    WindowSwitcher	proc
    .ends

endif

externdef		CLSID_Shell:CLSID
externdef		CLSID_ShellDispatchInproc:CLSID

ifndef __IFileSearchBand_INTERFACE_DEFINED__
__IFileSearchBand_INTERFACE_DEFINED__ equ 1


externdef		IID_IFileSearchBand:IID
.comdef IFileSearchBand
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    SetFocus		proc
    SetSearchParameters proc :ptr, :VARIANT_BOOL, :ptr, :ptr
    get_SearchID	proc :ptr
    get_Scope		proc :ptr
    get_QueryFile	proc :ptr
    .ends

endif

externdef		CLSID_FileSearchBand:CLSID

ifndef __IWebWizardHost_INTERFACE_DEFINED__
__IWebWizardHost_INTERFACE_DEFINED__ equ 1


externdef		IID_IWebWizardHost:IID
.comdef IWebWizardHost
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    FinalBack		proc
    FinalNext		proc
    Cancel		proc
    put_Caption		proc :BSTR
    get_Caption		proc :ptr
    put_Property	proc :BSTR, :ptr
    get_Property	proc :BSTR, :ptr
    SetWizardButtons	proc :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL
    SetHeaderText	proc :BSTR, :BSTR
    .ends

endif

ifndef __INewWDEvents_INTERFACE_DEFINED__
__INewWDEvents_INTERFACE_DEFINED__ equ 1


externdef		IID_INewWDEvents:IID
.comdef INewWDEvents
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    FinalBack		proc
    FinalNext		proc
    Cancel		proc
    put_Caption		proc :BSTR
    get_Caption		proc :ptr
    put_Property	proc :BSTR, :ptr
    get_Property	proc :BSTR, :ptr
    SetWizardButtons	proc :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL
    SetHeaderText	proc :BSTR, :BSTR
    PassportAuthenticate proc :BSTR, :ptr
    .ends

endif
endif


externdef		__MIDL_itf_shldisp_0001_0067_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shldisp_0001_0067_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAutoComplete_INTERFACE_DEFINED__
__IAutoComplete_INTERFACE_DEFINED__ equ 1


.comdef IAutoComplete
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Init		proc :HWND, :ptr, :LPCWSTR, :LPCWSTR
    Enable		proc :BOOL
    .ends
LPAUTOCOMPLETE		typedef ptr IAutoComplete
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

.comdef IAutoComplete2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Init		proc :HWND, :ptr, :LPCWSTR, :LPCWSTR
    Enable		proc :BOOL
    SetOptions		proc :DWORD
    GetOptions		proc :ptr
    .ends
LPAUTOCOMPLETE2		typedef ptr IAutoComplete2
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
.comdef IEnumACString
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    NextItem		proc :LPWSTR, :ULONG, :ptr
    SetEnumOptions	proc :DWORD
    GetEnumOptions	proc :ptr
    .ends
PENUMACSTRING		typedef ptr IEnumACString
LPENUMACSTRING		typedef ptr IEnumACString

endif

externdef		__MIDL_itf_shldisp_0000_0003_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_shldisp_0000_0003_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAsyncOperation_INTERFACE_DEFINED__
__IAsyncOperation_INTERFACE_DEFINED__ equ 1

.comdef IAsyncOperation
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetAsyncMode	proc :BOOL
    GetAsyncMode	proc :ptr
    StartOperation	proc :ptr
    InOperation		proc :ptr
    EndOperation	proc :HRESULT, :ptr, :DWORD
    .ends
LPASYNCOPERATION	typedef ptr IAsyncOperation
externdef		IID_IAsyncOperation:IID

endif

.list
endif ; __shldisp_h__
