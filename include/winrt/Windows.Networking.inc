ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Enetworking_h__
define __windows2Enetworking_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

.namespace Windows
.namespace Networking

.enum HostNameSortOptions {
    HostNameSortOptions_None	= 0,
    HostNameSortOptions_OptimizeForLongConnections = 0x2
    }

.enum HostNameType {
    HostNameType_DomainName	= 0,
    HostNameType_Ipv4		= 1,
    HostNameType_Ipv6		= 2,
    HostNameType_Bluetooth	= 3
    }

.enum DomainNameType {
    DomainNameType_Suffix	= 0,
    DomainNameType_FullyQualified = 1
    }

.endn
.endn

ifndef __windows2Enetworking2Econnectivity_h__
include Windows.Networking.Connectivity.inc
endif
include windows.foundation.collections.inc


ifndef ____FIIterator_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CNetworking__CEndpointPair, "c899ff9f-e6f5-5673-810c-04e2ff98704f")

.comdef __FIIterator_1_Windows__CNetworking__CEndpointPair : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CNetworking__CEndpointPair, "d7ec83c4-a17b-51bf-8997-aa33b9102dc9")

.comdef __FIIterable_1_Windows__CNetworking__CEndpointPair : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CNetworking__CHostName, "557bf83c-a428-5dbd-a0fe-05f6ee543d45")

.comdef __FIIterator_1_Windows__CNetworking__CHostName : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CNetworking__CHostName, "9e5f3ed0-cf1c-5d38-832c-acea6164bf5c")

.comdef __FIIterable_1_Windows__CNetworking__CHostName : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CNetworking__CEndpointPair, "8780a851-6d48-5006-9288-81f3d7045a96")

.comdef __FIVectorView_1_Windows__CNetworking__CEndpointPair : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CNetworking__CHostName, "f4706ab1-55a3-5270-afb2-732988fe8227")

.comdef __FIVectorView_1_Windows__CNetworking__CHostName : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CNetworking__CHostName_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CNetworking__CHostName, "90c71c29-a9b5-5267-a5ad-8b756736317c")

.comdef __FIVector_1_Windows__CNetworking__CHostName : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CEndpointPair, "20d6faab-3b8e-5a1f-8397-b01cb219a18d")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CNetworking__CEndpointPair : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CEndpointPair_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CEndpointPair, "afc2ff8e-e393-566a-89c4-d043e940050d")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CNetworking__CEndpointPair : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Networking

ifndef ____x_ABI_CWindows_CNetworking_CIHostNameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CIHostNameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_IHostNameStatics <L"Windows.Networking.IHostNameStatics">
DEFINE_IIDX(IHostNameStatics, "F68CD4BF-A388-4E8B-91EA-54DD6DD901C0")

.comdef IHostNameStatics : public IInspectable

    Compare		proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CIHostName_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CIHostName_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_IHostName <L"Windows.Networking.IHostName">
DEFINE_IIDX(IHostName, "BF8ECAAD-ED96-49A7-9084-D416CAE88DCB")

.comdef IHostName : public IInspectable

    get_IPInformation	proc :ptr
    get_RawName		proc :ptr
    get_DisplayName	proc :ptr
    get_CanonicalName	proc :ptr
    get_Type		proc :ptr
    IsEqual		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CIHostNameFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CIHostNameFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_IHostNameFactory <L"Windows.Networking.IHostNameFactory">
DEFINE_IIDX(IHostNameFactory, "458C23ED-712F-4576-ADF1-C20B2C643558")

.comdef IHostNameFactory : public IInspectable

    CreateHostName	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CIEndpointPair_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CIEndpointPair_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_IEndpointPair <L"Windows.Networking.IEndpointPair">
DEFINE_IIDX(IEndpointPair, "33A0AA36-F8FA-4B30-B856-76517C3BD06D")

.comdef IEndpointPair : public IInspectable

    get_LocalHostName	proc :ptr
    put_LocalHostName	proc :ptr
    get_LocalServiceName proc :ptr
    put_LocalServiceName proc :HSTRING
    get_RemoteHostName	proc :ptr
    put_RemoteHostName	proc :ptr
    get_RemoteServiceName proc :ptr
    put_RemoteServiceName proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CNetworking_CIEndpointPairFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CNetworking_CIEndpointPairFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Networking_IEndpointPairFactory <L"Windows.Networking.IEndpointPairFactory">
DEFINE_IIDX(IEndpointPairFactory, "B609D971-64E0-442B-AA6F-CC8C8F181F78")

.comdef IEndpointPairFactory : public IInspectable

    CreateEndpointPair	proc :ptr, :HSTRING, :ptr, :HSTRING, :ptr
   .ends

endif

.endn
.endn

ifndef RUNTIMECLASS_Windows_Networking_HostName_DEFINED
define RUNTIMECLASS_Windows_Networking_HostName_DEFINED
define RuntimeClass_Windows_Networking_HostName <L"Windows.Networking.HostName">
endif
ifndef RUNTIMECLASS_Windows_Networking_EndpointPair_DEFINED
define RUNTIMECLASS_Windows_Networking_EndpointPair_DEFINED
define RuntimeClass_Windows_Networking_EndpointPair <L"Windows.Networking.EndpointPair">
endif

endif
