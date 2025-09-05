ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eweb2Eatompub_h__
define __windows2Eweb2Eatompub_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Security.Credentials.inc
include Windows.Storage.Streams.inc
include Windows.Web.Syndication.inc

ifndef ____FIIterator_1_Windows__CWeb__CAtomPub__CResourceCollection_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CAtomPub__CResourceCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CAtomPub__CResourceCollection, "2b175876-0920-52f0-80bf-dfe79744128d")

.comdef __FIIterator_1_Windows__CWeb__CAtomPub__CResourceCollection : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CAtomPub__CResourceCollection_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CAtomPub__CResourceCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CAtomPub__CResourceCollection, "d4372a2d-7ab0-5d8e-bd5c-6e9c0a67a8d8")

.comdef __FIIterable_1_Windows__CWeb__CAtomPub__CResourceCollection : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CAtomPub__CWorkspace_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CAtomPub__CWorkspace_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CAtomPub__CWorkspace, "0cc8c426-d68a-5136-9741-de326764ca32")

.comdef __FIIterator_1_Windows__CWeb__CAtomPub__CWorkspace : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CAtomPub__CWorkspace_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CAtomPub__CWorkspace_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CAtomPub__CWorkspace, "f02d0ebe-eac2-502f-9836-1c5482333bfe")

.comdef __FIIterable_1_Windows__CWeb__CAtomPub__CWorkspace : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CAtomPub__CResourceCollection_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CAtomPub__CResourceCollection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CAtomPub__CResourceCollection, "32f021c7-368b-5cfa-829c-4acf8a36c810")

.comdef __FIVectorView_1_Windows__CWeb__CAtomPub__CResourceCollection : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CAtomPub__CWorkspace_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CAtomPub__CWorkspace_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CAtomPub__CWorkspace, "d0d7b58d-d97e-5761-be66-42b85b3d19c8")

.comdef __FIVectorView_1_Windows__CWeb__CAtomPub__CWorkspace : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Web
.namespace AtomPub

ifndef ____x_ABI_CWindows_CWeb_CAtomPub_CIResourceCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CAtomPub_CIResourceCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_AtomPub_IResourceCollection <L"Windows.Web.AtomPub.IResourceCollection">
DEFINE_IIDX(IResourceCollection, "7F5FD609-BC88-41D4-88FA-3DE6704D428E")

.comdef IResourceCollection : public IInspectable

    get_Title           proc :ptr
    get_Uri             proc :ptr
    get_Categories      proc :ptr
    get_Accepts         proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CAtomPub_CIWorkspace_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CAtomPub_CIWorkspace_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_AtomPub_IWorkspace <L"Windows.Web.AtomPub.IWorkspace">
DEFINE_IIDX(IWorkspace, "B41DA63B-A4B8-4036-89C5-83C31266BA49")

.comdef IWorkspace : public IInspectable

    get_Title           proc :ptr
    get_Collections     proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CAtomPub_CIServiceDocument_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CAtomPub_CIServiceDocument_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_AtomPub_IServiceDocument <L"Windows.Web.AtomPub.IServiceDocument">
DEFINE_IIDX(IServiceDocument, "8B7EC771-2AB3-4DBE-8BCC-778F92B75E51")

.comdef IServiceDocument : public IInspectable

    get_Workspaces      proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CAtomPub_CIAtomPubClient_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CAtomPub_CIAtomPubClient_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_AtomPub_IAtomPubClient <L"Windows.Web.AtomPub.IAtomPubClient">
DEFINE_IIDX(IAtomPubClient, "35392C38-CDED-4D4C-9637-05F15C1C9406")

.comdef IAtomPubClient : public IInspectable

    RetrieveServiceDocumentAsync proc :ptr, :ptr
    RetrieveMediaResourceAsync proc :ptr, :ptr
    RetrieveResourceAsync proc :ptr, :ptr
    CreateResourceAsync proc :ptr, :HSTRING, :ptr, :ptr
    CreateMediaResourceAsync proc :ptr, :HSTRING, :HSTRING, :ptr, :ptr
    UpdateMediaResourceAsync proc :ptr, :HSTRING, :ptr, :ptr
    UpdateResourceAsync proc :ptr, :ptr, :ptr
    UpdateResourceItemAsync proc :ptr, :ptr
    DeleteResourceAsync proc :ptr, :ptr
    DeleteResourceItemAsync proc :ptr, :ptr
    CancelAsyncOperations proc
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CAtomPub_CIAtomPubClientFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CAtomPub_CIAtomPubClientFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_AtomPub_IAtomPubClientFactory <L"Windows.Web.AtomPub.IAtomPubClientFactory">
DEFINE_IIDX(IAtomPubClientFactory, "49D55012-57CB-4BDE-AB9F-2610B172777B")

.comdef IAtomPubClientFactory : public IInspectable

    CreateAtomPubClientWithCredentials proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Web_AtomPub_ResourceCollection_DEFINED
define RUNTIMECLASS_Windows_Web_AtomPub_ResourceCollection_DEFINED
define RuntimeClass_Windows_Web_AtomPub_ResourceCollection <L"Windows.Web.AtomPub.ResourceCollection">
endif
ifndef RUNTIMECLASS_Windows_Web_AtomPub_Workspace_DEFINED
define RUNTIMECLASS_Windows_Web_AtomPub_Workspace_DEFINED
define RuntimeClass_Windows_Web_AtomPub_Workspace <L"Windows.Web.AtomPub.Workspace">
endif
ifndef RUNTIMECLASS_Windows_Web_AtomPub_ServiceDocument_DEFINED
define RUNTIMECLASS_Windows_Web_AtomPub_ServiceDocument_DEFINED
define RuntimeClass_Windows_Web_AtomPub_ServiceDocument <L"Windows.Web.AtomPub.ServiceDocument">
endif
ifndef RUNTIMECLASS_Windows_Web_AtomPub_AtomPubClient_DEFINED
define RUNTIMECLASS_Windows_Web_AtomPub_AtomPubClient_DEFINED
define RuntimeClass_Windows_Web_AtomPub_AtomPubClient <L"Windows.Web.AtomPub.AtomPubClient">
endif

endif
