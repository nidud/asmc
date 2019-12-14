.pragma list(push, 0)
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

ifndef __SHLDISP_INC
__SHLDISP_INC equ <>

ifndef __IFolderViewOC_FWD_DEFINED__
__IFolderViewOC_FWD_DEFINED__ equ 1
endif
ifndef __DShellFolderViewEvents_FWD_DEFINED__
__DShellFolderViewEvents_FWD_DEFINED__ equ 1
endif
ifndef __ShellFolderViewOC_FWD_DEFINED__
__ShellFolderViewOC_FWD_DEFINED__ equ 1
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
endif
ifndef __ShellDispatchInproc_FWD_DEFINED__
__ShellDispatchInproc_FWD_DEFINED__ equ 1
endif
ifndef __IFileSearchBand_FWD_DEFINED__
__IFileSearchBand_FWD_DEFINED__ equ 1
endif
ifndef __FileSearchBand_FWD_DEFINED__
__FileSearchBand_FWD_DEFINED__ equ 1
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

DECLSPEC_UUID("35f1a0d0-3e9a-11d2-8499-005345000000")

.enum OfflineFolderStatus {
    OFS_INACTIVE	= -1,
    OFS_ONLINE		= ( OFS_INACTIVE + 1 ) ,
    OFS_OFFLINE		= ( OFS_ONLINE + 1 ) ,
    OFS_SERVERBACK	= ( OFS_OFFLINE + 1 ) ,
    OFS_DIRTYCACHE	= ( OFS_SERVERBACK + 1 )
}

.enum ShellFolderViewOptions {
    SFVVO_SHOWALLOBJECTS = 0x1,
    SFVVO_SHOWEXTENSIONS = 0x2,
    SFVVO_SHOWCOMPCOLOR = 0x8,
    SFVVO_SHOWSYSFILES	= 0x20,
    SFVVO_WIN95CLASSIC	= 0x40,
    SFVVO_DOUBLECLICKINWEBVIEW = 0x80,
    SFVVO_DESKTOPHTML	= 0x200
}

.enum ShellSpecialFolderConstants {
    ssfDESKTOP		= 0,
    ssfPROGRAMS		= 0x2,
    ssfCONTROLS		= 0x3,
    ssfPRINTERS		= 0x4,
    ssfPERSONAL		= 0x5,
    ssfFAVORITES	= 0x6,
    ssfSTARTUP		= 0x7,
    ssfRECENT		= 0x8,
    ssfSENDTO		= 0x9,
    ssfBITBUCKET	= 0xa,
    ssfSTARTMENU	= 0xb,
    ssfDESKTOPDIRECTORY = 0x10,
    ssfDRIVES		= 0x11,
    ssfNETWORK		= 0x12,
    ssfNETHOOD		= 0x13,
    ssfFONTS		= 0x14,
    ssfTEMPLATES	= 0x15,
    ssfCOMMONSTARTMENU	= 0x16,
    ssfCOMMONPROGRAMS	= 0x17,
    ssfCOMMONSTARTUP	= 0x18,
    ssfCOMMONDESKTOPDIR = 0x19,
    ssfAPPDATA		= 0x1a,
    ssfPRINTHOOD	= 0x1b,
    ssfLOCALAPPDATA	= 0x1c,
    ssfALTSTARTUP	= 0x1d,
    ssfCOMMONALTSTARTUP = 0x1e,
    ssfCOMMONFAVORITES	= 0x1f,
    ssfINTERNETCACHE	= 0x20,
    ssfCOOKIES		= 0x21,
    ssfHISTORY		= 0x22,
    ssfCOMMONAPPDATA	= 0x23,
    ssfWINDOWS		= 0x24,
    ssfSYSTEM		= 0x25,
    ssfPROGRAMFILES	= 0x26,
    ssfMYPICTURES	= 0x27,
    ssfPROFILE		= 0x28,
    ssfSYSTEMx86	= 0x29,
    ssfPROGRAMFILESx86	= 0x30
}

DECLSPEC_UUID("742A99A0-C77E-11D0-A32C-00A0C91EEDBA")
DECLSPEC_UUID("CA31EA20-48D0-11CF-8350-444553540000")
externdef LIBID_Shell32:IID

ifndef __Shell32_LIBRARY_DEFINED__
__Shell32_LIBRARY_DEFINED__ equ 1

ifndef __IFolderViewOC_INTERFACE_DEFINED__
__IFolderViewOC_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFolderViewOC, "9BA05970-F6A8-11CF-A442-00A0C90A8F39")

.comdef IFolderViewOC : public IDispatch

    SetFolderView	proc :ptr
    .ends
endif

ifndef __DShellFolderViewEvents_DISPINTERFACE_DEFINED__
__DShellFolderViewEvents_DISPINTERFACE_DEFINED__ equ 1

DEFINE_GUIDS(DIID_DShellFolderViewEvents, "62112AA2-EBE4-11cf-A5FB-0020AFE7292D")

.comdef DShellFolderViewEvents : public IDispatch
    .ends
endif

externdef CLSID_ShellFolderViewOC:CLSID

ifndef __DFConstraint_INTERFACE_DEFINED__
__DFConstraint_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(DFConstraint, "4a3df050-23bd-11d2-939f-00a0c91eedba")

.comdef DFConstraint : public IDispatch

    get_Name		proc :ptr
    get_Value		proc :ptr
    .ends
endif

ifndef __FolderItem_INTERFACE_DEFINED__
__FolderItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(FolderItem, "FAC32C80-CBE4-11CE-8350-444553540000")

.comdef FolderItem : public IDispatch

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
    LPFOLDERITEM	typedef ptr FolderItem
endif


ifndef __FolderItems_INTERFACE_DEFINED__
__FolderItems_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(FolderItems, "744129E0-CBE5-11CE-8350-444553540000")

.comdef FolderItems : public IDispatch

    get_Count		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    Item		proc :VARIANT, :ptr
    NewEnum		proc :ptr
    .ends
endif

ifndef __FolderItemVerb_INTERFACE_DEFINED__
__FolderItemVerb_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(FolderItemVerb, "08EC3E00-50B0-11CF-960C-0080C7F4EE85")

.comdef FolderItemVerb : public IDispatch

    get_Application	proc :ptr
    get_Parent		proc :ptr
    get_Name		proc :ptr
    DoIt		proc
    .ends
endif

ifndef __FolderItemVerbs_INTERFACE_DEFINED__
__FolderItemVerbs_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(FolderItemVerbs, "1F8352C0-50B0-11CF-960C-0080C7F4EE85")

.comdef FolderItemVerbs : public IDispatch

    get_Count		proc :ptr
    get_Application	proc :ptr
    get_Parent		proc :ptr
    Item		proc :VARIANT, :ptr
    NewEnum		proc :ptr
    .ends
endif

ifndef __Folder_INTERFACE_DEFINED__
__Folder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Folder, "BBCBDE60-C3FF-11CE-8350-444553540000")

.comdef Folder : public IDispatch

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

DEFINE_IIDX(Folder2, "f0d2d8ef-3890-11d2-bf8b-00c04fb93661")

.comdef Folder2: public Folder

    get_Self		proc :ptr
    get_OfflineStatus	proc :ptr
    Synchronize		proc
    get_HaveToShowWebViewBarricade proc :ptr
    DismissedWebViewBarricade proc
    .ends
endif


ifndef __Folder3_INTERFACE_DEFINED__
__Folder3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(Folder3,"A7AE5F64-C4D7-4d7f-9307-4D24EE54B841")

.comdef Folder3: public Folder2

    get_ShowWebViewBarricade proc :ptr
    put_ShowWebViewBarricade proc :VARIANT_BOOL
    .ends
endif


ifndef __FolderItem2_INTERFACE_DEFINED__
__FolderItem2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(FolderItem2, "edc817aa-92b8-11d1-b075-00c04fc33aa5")

.comdef FolderItem2: public FolderItem

    InvokeVerbEx	proc :VARIANT, :VARIANT
    ExtendedProperty	proc :BSTR, :ptr
    .ends
endif

DEFINE_GUIDS(CLSID_ShellFolderItem, "2fe352ea-fd1f-11d2-b1f4-00c04f8eeb3e")

ifndef __FolderItems2_INTERFACE_DEFINED__
__FolderItems2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(FolderItems2, "C94F0AD0-F363-11d2-A327-00C04F8EEC7F")

.comdef FolderItems2 : public FolderItems

    InvokeVerbEx	proc :VARIANT, :VARIANT
    .ends
endif

ifndef __FolderItems3_INTERFACE_DEFINED__
__FolderItems3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(FolderItems3, "eaa7c309-bbec-49d5-821d-64d966cb667f")

.comdef FolderItems3: public FolderItems2

    Filter		proc :LONG, :BSTR
    get_Verbs		proc :ptr
    .ends
endif

ifndef __IShellLinkDual_INTERFACE_DEFINED__
__IShellLinkDual_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellLinkDual, "88A05C00-F000-11CE-8350-444553540000")

.comdef IShellLinkDual: public IDispatch

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

DEFINE_IIDX(IShellLinkDual2, "317EE249-F12E-11d2-B1E4-00C04F8EEB3E")

.comdef IShellLinkDual2: public IShellLinkDual

    get_Target		proc :ptr
    .ends
endif

externdef CLSID_ShellLinkObject:CLSID

ifndef __IShellFolderViewDual_INTERFACE_DEFINED__
__IShellFolderViewDual_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellFolderViewDual, "E7A1AF80-4D96-11CF-960C-0080C7F4EE85")

.comdef IShellFolderViewDual : public IDispatch

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

DEFINE_IIDX(IShellFolderViewDual2, "31C147b6-0ADE-4A3C-B514-DDF932EF6D17")

.comdef IShellFolderViewDual2 : public IShellFolderViewDual

    get_CurrentViewMode proc :ptr
    put_CurrentViewMode proc :UINT
    SelectItemRelative	proc :SINT
    .ends
endif

ifndef __IShellFolderViewDual3_INTERFACE_DEFINED__
__IShellFolderViewDual3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellFolderViewDual3, "29EC8E6C-46D3-411f-BAAA-611A6C9CAC66")

.comdef IShellFolderViewDual3 : public IShellFolderViewDual2

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

DEFINE_GUIDS(CLSID_ShellFolderView, "62112AA1-EBE4-11cf-A5FB-0020AFE7292D")

ifndef __IShellDispatch_INTERFACE_DEFINED__
__IShellDispatch_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellDispatch, "D8F015C0-C278-11CE-A49E-444553540000")

.comdef IShellDispatch : public IDispatch

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

DEFINE_IIDX(IShellDispatch2, "A4C6892C-3BA9-11d2-9DEA-00C04FB16162")

.comdef IShellDispatch2 : public IShellDispatch

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

DEFINE_IIDX(IShellDispatch3, "177160ca-bb5a-411c-841d-bd38facdeaa0")

.comdef IShellDispatch3 : public IShellDispatch2

    AddToRecent		proc :VARIANT, :BSTR
    .ends
endif


ifndef __IShellDispatch4_INTERFACE_DEFINED__
__IShellDispatch4_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellDispatch4, "efd84b2d-4bcf-4298-be25-eb542a59fbda")

.comdef IShellDispatch4 : public IShellDispatch3

    WindowsSecurity	proc
    ToggleDesktop	proc
    ExplorerPolicy	proc :BSTR, :ptr
    GetSetting		proc :LONG, :ptr
    .ends
endif

ifndef __IShellDispatch5_INTERFACE_DEFINED__
__IShellDispatch5_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IShellDispatch5, "866738b9-6cf2-4de8-8767-f794ebe74f4e")

.comdef IShellDispatch5 : public IShellDispatch4

    WindowSwitcher	proc
    .ends
endif

DEFINE_GUIDS(CLSID_Shell,		"13709620-C279-11CE-A49E-444553540000")
DEFINE_GUIDS(CLSID_ShellDispatchInproc, "0A89A860-D7B1-11CE-8350-444553540000")

ifndef __IFileSearchBand_INTERFACE_DEFINED__
__IFileSearchBand_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IFileSearchBand, "2D91EEA1-9932-11d2-BE86-00A0C9A83DA1")

.comdef IFileSearchBand : public IDispatch

    SetFocus		proc
    SetSearchParameters proc :ptr, :VARIANT_BOOL, :ptr, :ptr
    get_SearchID	proc :ptr
    get_Scope		proc :ptr
    get_QueryFile	proc :ptr
    .ends
endif

DEFINE_GUIDS(CLSID_FileSearchBand, "C4EE31F3-4768-11D2-BE5C-00A0C9A83DA1")

ifndef __IWebWizardHost_INTERFACE_DEFINED__
__IWebWizardHost_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWebWizardHost, "18bcc359-4990-4bfb-b951-3c83702be5f9")

.comdef IWebWizardHost : public IDispatch

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

DEFINE_IIDX(INewWDEvents, "0751c551-7568-41c9-8e5b-e22e38919236")

.comdef INewWDEvents : public IWebWizardHost

    PassportAuthenticate proc :BSTR, :ptr
    .ends
endif
endif


ifndef __IAutoComplete_INTERFACE_DEFINED__
__IAutoComplete_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAutoComplete, "00bb2762-6a77-11d0-a535-00c04fd7d062")

.comdef IAutoComplete : public IUnknown

    Init		proc :HWND, :ptr, :LPCWSTR, :LPCWSTR
    Enable		proc :BOOL
    .ends
    LPAUTOCOMPLETE	typedef ptr IAutoComplete
endif

ifndef __IAutoComplete2_INTERFACE_DEFINED__
__IAutoComplete2_INTERFACE_DEFINED__ equ 1

.enum AUTOCOMPLETEOPTIONS {
    ACO_NONE		= 0,
    ACO_AUTOSUGGEST	= 0x1,
    ACO_AUTOAPPEND	= 0x2,
    ACO_SEARCH		= 0x4,
    ACO_FILTERPREFIXES	= 0x8,
    ACO_USETAB		= 0x10,
    ACO_UPDOWNKEYDROPSLIST = 0x20,
    ACO_RTLREADING	= 0x40,
    ACO_WORD_FILTER	= 0x80,
    ACO_NOPREFIXFILTERING = 0x100
}

DEFINE_IIDX(IAutoComplete2, "EAC04BC0-3791-11d2-BB95-0060977B464C")

.comdef IAutoComplete2 : public IAutoComplete

    SetOptions		proc :DWORD
    GetOptions		proc :ptr
    .ends
    LPAUTOCOMPLETE2	typedef ptr IAutoComplete2
endif


ifndef __IEnumACString_INTERFACE_DEFINED__
__IEnumACString_INTERFACE_DEFINED__ equ 1

.enum ACENUMOPTION {
    ACEO_NONE		= 0,
    ACEO_MOSTRECENTFIRST = 0x1,
    ACEO_FIRSTUNUSED	= 0x10000
}

DEFINE_IIDX(IEnumACString, "8E74C210-CF9D-4eaf-A403-7356428F0A5A")

.comdef IEnumACString : public IEnumString

    NextItem		proc :LPWSTR, :ULONG, :ptr
    SetEnumOptions	proc :DWORD
    GetEnumOptions	proc :ptr
    .ends
    PENUMACSTRING	typedef ptr IEnumACString
    LPENUMACSTRING	typedef ptr IEnumACString
endif

ifndef __IAsyncOperation_INTERFACE_DEFINED__
__IAsyncOperation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAsyncOperation, "3D8B0590-F691-11d2-8EA9-006097DF5BD4")

.comdef IAsyncOperation : public IUnknown

    SetAsyncMode	proc :BOOL
    GetAsyncMode	proc :ptr
    StartOperation	proc :ptr
    InOperation		proc :ptr
    EndOperation	proc :HRESULT, :ptr, :DWORD
    .ends
    LPASYNCOPERATION	typedef ptr IAsyncOperation
endif
endif
.pragma list(pop)
