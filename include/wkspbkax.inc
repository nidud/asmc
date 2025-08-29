ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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

ifndef __wkspbkax_h__
define __wkspbkax_h__

include oaidl.inc
include ocidl.inc

if (NTDDI_VERSION ge NTDDI_WIN8)

define	DISPID_WKSPAX_WORKSPACE_SETUP_COMPLETED 1

ifndef __IWorkspaceBrokerAx_INTERFACE_DEFINED__
define __IWorkspaceBrokerAx_INTERFACE_DEFINED__

DEFINE_IIDX(IWorkspaceBrokerAx, "2F93474C-2ED7-4A68-AFD1-D3C9781F341E")

.comdef IWorkspaceBrokerAx : public IDispatch
    SetupWorkspace	proc
    InitializeWorkspaceConfiguration proc
    get_WorkspacesCount proc :ptr
    get_WorkspaceName	proc :LONG, :ptr
    get_WorkspaceId	proc :LONG, :ptr
    get_WorkspaceFoldersCount proc :BSTR, :ptr
    get_WorkspaceFolderName proc :BSTR, :LONG, :ptr
    get_WorkspaceFolderContentsCount proc :BSTR, :BSTR, :ptr
    get_WorkspaceFolderImageData proc :BSTR, :BSTR, :LONG, :ptr
    get_WorkspaceFolderItemName proc :BSTR, :BSTR, :LONG, :ptr
    get_WorkspaceFolderItemFileExtension proc :BSTR, :BSTR, :LONG, :ptr
    get_IsWorkspaceFolderItemRemoteDesktop proc :BSTR, :BSTR, :LONG, :ptr
    LaunchWorkspaceItem proc :BSTR, :BSTR, :BSTR, :BSTR
    attachEvent		proc :BSTR, :ptr
    detachEvent		proc :BSTR, :ptr
   .ends

endif

ifndef __IWorkspaceBrokerAx2_INTERFACE_DEFINED__
define __IWorkspaceBrokerAx2_INTERFACE_DEFINED__

DEFINE_IIDX(IWorkspaceBrokerAx2, "57D42F01-D762-4680-9893-326B08F22652")

.comdef IWorkspaceBrokerAx2 : public IWorkspaceBrokerAx
    RefreshWorkspace	proc :BSTR
    RemoveWorkspace	proc :BSTR
    get_WorkspaceDescription proc :BSTR, :ptr
    get_WorkspaceURL	proc :BSTR, :ptr
    get_WorkspaceLastUpdateDescription proc :BSTR, :ptr
    get_IsDefaultWorkspace proc :BSTR, :ptr
   .ends

endif

ifndef __wkspbkaxLib_LIBRARY_DEFINED__
define __wkspbkaxLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_wkspbkaxLib, 0xA47EDEDD,0x2921,0x4E5A,0x9B,0x91,0x13,0xC9,0x53,0xEC,0x7F,0xE3)

ifndef ___IWorkspaceBrokerAxEvents_DISPINTERFACE_DEFINED__
define ___IWorkspaceBrokerAxEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IWorkspaceBrokerAxEvents, "7A3D0ADC-0CC4-473D-B327-D37886308F28")

.comdef _IWorkspaceBrokerAxEvents : public IDispatch
   .ends

endif

DEFINE_GUID(CLSID_WorkspaceBrokerAx, 0xCD70A734,0xB6DB,0x4588,0x98,0x13,0xFF,0x2E,0x37,0xA4,0x66,0x1F)

endif

endif

endif
