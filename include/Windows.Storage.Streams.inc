ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Estorage2Estreams_h__
define __windows2Estorage2Estreams_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include windows.foundation.collections.inc

ifndef DEF___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_USE
DEF___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_USE equ 1

DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference, "e5195792-aeab-56e8-bd30-1372c4340bf6")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
    .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference, "9419af53-acb8-5328-8853-70ba87eb6ad5")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference, "c9729ba7-5e20-569d-a3d1-97a4e653e5bb")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef ____FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer, "82a3a3b7-e04a-5395-8487-7f94f1508ce7")

.comdef __FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
    .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIIterator_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer, "a295fa0c-c99f-5109-8ab9-91534bb48c9b")

.comdef __FIIterator_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIIterable_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer, "4fe7fe23-22b1-528c-881d-a4eceaef0f11")

.comdef __FIIterable_1___FIKeyValuePair_2_UINT32_Windows__CStorage__CStreams__CIBuffer : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
____FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream, "c875446a-587f-58da-897e-3bbe5ec7c30b")

.comdef __FIIterator_1_Windows__CStorage__CStreams__CIRandomAccessStream : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
____FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream, "ba666a00-1555-5df4-81a5-07d23f7ffceb")

.comdef __FIIterable_1_Windows__CStorage__CStreams__CIRandomAccessStream : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference, "0a4ce7a5-dfe0-5796-a438-effdfaa31f1b")

.comdef __FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
    .ends

endif

ifndef ____FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer, "57dc41e6-8b4d-5910-9703-d7c668436852")

.comdef __FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer : public IInspectable

    Lookup		proc :UINT32, :ptr
    get_Size		proc :dword
    HasKey		proc :UINT32, :ptr
    Split		proc :ptr, :ptr
    .ends

endif

ifndef ____FIMap_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIMap_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIMap_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference, "e5d2ccfc-825a-5a8e-82aa-095ed5dbd5d1")

.comdef __FIMap_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    GetView		proc :ptr
    Insert		proc :HSTRING, :ptr, :ptr
    Remove		proc :HSTRING
    Clear		proc
    .ends

endif

ifndef ____FIMap_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIMap_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIMap_2_UINT32_Windows__CStorage__CStreams__CIBuffer, "5d2591df-48c5-5734-9ef1-bd639b032007")

.comdef __FIMap_2_UINT32_Windows__CStorage__CStreams__CIBuffer : public IInspectable

    Lookup		proc :UINT32, :ptr
    get_Size		proc :dword
    HasKey		proc :UINT32, :ptr
    GetView		proc :ptr
    Insert		proc :UINT32, :ptr, :ptr
    Remove		proc :UINT32
    Clear		proc
    .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
____FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream, "92cd0a46-2266-5cd6-9293-e111299f2793")

.comdef __FIVectorView_1_Windows__CStorage__CStreams__CIRandomAccessStream : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
    .ends

endif

ifndef ____FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
____FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream, "2736b66b-daa3-5e0c-9842-6a0f44b5440b")

.comdef __FIVector_1_Windows__CStorage__CStreams__CIRandomAccessStream : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    GetView		proc :ptr
    IndexOf		proc :ptr, :dword, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :dword
    ReplaceAll		proc :SINT, :ptr
    .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32_INTERFACE_DEFINED__
____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32, "bf666554-7605-5d9a-b14e-18d8c8472afe")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32 : public IUnknown

    _Invoke		proc :ptr, :UINT32
    .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32_INTERFACE_DEFINED__
____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32, "06386a7a-e009-5b0b-ab68-a8e48b516647")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT32 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT32_INTERFACE_DEFINED__
____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT32_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT32, "d26b2819-897f-5c7d-84d6-56d796561431")

.comdef __FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT32 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64_INTERFACE_DEFINED__
____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64, "d17f5eb6-b422-5e26-a817-7e0fd08f75d5")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64 : public IUnknown

    _Invoke		proc :ptr, :UINT64
    .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64_INTERFACE_DEFINED__
____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64, "abc81235-39c7-59bf-9948-2d14a93d40fd")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_UINT64 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT64_INTERFACE_DEFINED__
____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT64_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT64, "ad960e7f-d73b-56e4-a58c-6ec7678cfd88")

.comdef __FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_UINT64 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64_INTERFACE_DEFINED__
____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64, "f9b2e7f6-762f-50db-95dd-7f6c6ec47090")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64 : public IUnknown

    _Invoke		proc :ptr, :UINT64
    .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64_INTERFACE_DEFINED__
____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64, "8db69706-3dd1-5a28-986a-93be0776d9c3")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_UINT64 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_UINT64_INTERFACE_DEFINED__
____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_UINT64_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_UINT64, "455aa601-f13e-5dee-b9cb-16b531996327")

.comdef __FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_UINT64 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference, "d4cb6b80-821a-5a7b-898d-d58917b31a36")

.comdef __FIAsyncOperationCompletedHandler_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIAsyncOperation_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference, "fc012d44-2dcf-5162-be9a-7668675aa590")

.comdef __FIAsyncOperation_1___FIMapView_2_HSTRING_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer, "92c2e4d0-7c25-596b-9135-10d1472e6968")

.comdef __FIAsyncOperationCompletedHandler_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIAsyncOperation_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer, "d4904ded-bc1d-5933-aecf-e42c5d465bff")

.comdef __FIAsyncOperation_1___FIMapView_2_UINT32_Windows__CStorage__CStreams__CIBuffer : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIBuffer, "51c3d2fd-b8a1-5620-b746-7ee6d533aca3")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIBuffer : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CStreams__CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIBuffer, "51c3d2fd-b8a1-5620-b746-7ee6d533aca3")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStreams__CIBuffer : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIInputStream_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIInputStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIInputStream, "d0bd0125-9049-57a3-bd66-e2525d98c814")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIInputStream : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIInputStream_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CStreams__CIInputStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIInputStream, "a8fe0732-556d-5841-b7ee-b3450fb52666")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStreams__CIInputStream : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIOutputStream_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIOutputStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIOutputStream, "bcb37f4f-3af4-561c-a9e3-eef1738494d7")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIOutputStream : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIOutputStream_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CStreams__CIOutputStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIOutputStream, "e8736833-d013-5361-977d-c5e99934680e")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStreams__CIOutputStream : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream, "398c4183-793d-5b00-819b-4aef92485e94")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStream : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream, "430ecece-1418-5d19-81b2-5ddb381603cc")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStream : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType, "3dddecf4-1d39-58e8-83b1-dbed541c7f35")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType, "c4a57c5e-32b0-55b3-ad13-ce1c23041ed6")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStreams__CIRandomAccessStreamWithContentType : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CRandomAccessStreamReference, "3d203732-ded7-5d32-87e6-c179781f791f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CStorage__CStreams__CRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStreams__CRandomAccessStreamReference, "d90442ca-543c-504b-9eb9-294bcad8a283")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStreams__CRandomAccessStreamReference : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif


.enum _x_ABI_CWindows_CStorage_CStreams_CByteOrder {
    ByteOrder_LittleEndian	= 0,
    ByteOrder_BigEndian = 1
    }

.enum _x_ABI_CWindows_CStorage_CStreams_CUnicodeEncoding {
    UnicodeEncoding_Utf8	= 0,
    UnicodeEncoding_Utf16LE	= 1,
    UnicodeEncoding_Utf16BE	= 2
    }

.enum _x_ABI_CWindows_CStorage_CStreams_CInputStreamOptions {
    InputStreamOptions_None	= 0,
    InputStreamOptions_Partial	= 0x1,
    InputStreamOptions_ReadAhead	= 0x2
    }


ifndef ____x_ABI_CWindows_CStorage_CStreams_CIDataReader_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIDataReader_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIDataReader, "E2B50029-B4C1-4314-A4B8-FB813A2F275E")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIDataReader : public IInspectable

    get_UnconsumedBufferLength proc :ptr
    get_UnicodeEncoding proc :ptr
    put_UnicodeEncoding proc :ptr
    get_ByteOrder	proc :ptr
    put_ByteOrder	proc :ptr
    get_InputStreamOptions proc :ptr
    put_InputStreamOptions proc :ptr
    ReadByte		proc :ptr
    ReadBytes		proc :UINT32, :ptr
    ReadBuffer		proc :UINT32, :ptr
    ReadBoolean		proc :ptr
    ReadGuid		proc :ptr
    ReadInt16		proc :ptr
    ReadInt32		proc :ptr
    ReadInt64		proc :ptr
    ReadUInt16		proc :ptr
    ReadUInt32		proc :ptr
    ReadUInt64		proc :ptr
    ReadSingle		proc :ptr
    ReadDouble		proc :ptr
    ReadString		proc :UINT32, :ptr
    ReadDateTime	proc :ptr
    ReadTimeSpan	proc :ptr
    LoadAsync		proc :UINT32, :ptr
    DetachBuffer	proc :ptr
    DetachStream	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIDataReaderFactory_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIDataReaderFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIDataReaderFactory, "D7527847-57DA-4E15-914C-06806699A098")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIDataReaderFactory : public IInspectable

    CreateDataReader	proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIDataReaderStatics_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIDataReaderStatics_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIDataReaderStatics, "11FCBFC8-F93A-471B-B121-F379E349313C")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIDataReaderStatics : public IInspectable

    FromBuffer		proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIDataWriter_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIDataWriter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIDataWriter, "64B89265-D341-4922-B38A-DD4AF8808C4E")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIDataWriter : public IInspectable

    get_UnstoredBufferLength proc :ptr
    get_UnicodeEncoding proc :ptr
    put_UnicodeEncoding proc :ptr
    get_ByteOrder	proc :ptr
    put_ByteOrder	proc :ptr
    WriteByte		proc :BYTE
    WriteBytes		proc :UINT32, :ptr
    WriteBuffer		proc :ptr
    WriteBufferRange	proc :ptr, :UINT32, :UINT32
    WriteBoolean	proc :boolean
    WriteGuid		proc :GUID
    WriteInt16		proc :INT16
    WriteInt32		proc :INT32
    WriteInt64		proc :INT64
    WriteUInt16		proc :UINT16
    WriteUInt32		proc :UINT32
    WriteUInt64		proc :UINT64
    WriteSingle		proc :FLOAT
    WriteDouble		proc :DOUBLE
    WriteDateTime	proc :ptr
    WriteTimeSpan	proc :ptr
    WriteString		proc :HSTRING, :ptr
    MeasureString	proc :HSTRING, :ptr
    StoreAsync		proc :ptr
    FlushAsync		proc :ptr
    DetachBuffer	proc :ptr
    DetachStream	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIDataWriterFactory_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIDataWriterFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIDataWriterFactory, "338C67C2-8B84-4C2B-9C50-7B8767847A1F")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIDataWriterFactory : public IInspectable

    CreateDataWriter	proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamStatics_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamStatics_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamStatics, "524CEDCF-6E29-4CE5-9573-6B753DB66C3A")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamStatics : public IInspectable

    CopyAsync		proc :ptr, :ptr, :ptr
    CopySizeAsync	proc :ptr, :ptr, :UINT64, :ptr
    CopyAndCloseAsync	proc :ptr, :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIBufferFactory_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIBufferFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIBufferFactory, "71AF914D-C10F-484B-BC50-14BC623B3A27")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIBufferFactory : public IInspectable

    Create		proc :UINT32, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIBuffer_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIBuffer, "905A0FE0-BC53-11DF-8C49-001E4FC686DA")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIBuffer : public IInspectable

    get_Capacity	proc :ptr
    get_Length		proc :ptr
    put_Length		proc :UINT32
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIContentTypeProvider_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIContentTypeProvider_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIContentTypeProvider, "97D098A5-3B99-4DE9-88A5-E11D2F50C795")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIContentTypeProvider : public IInspectable

    get_ContentType	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference, "33EE3134-1DD6-4E3A-8067-D1C162E8642B")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReference : public IInspectable

    OpenReadAsync	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIInputStreamReference_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIInputStreamReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIInputStreamReference, "43929D18-5EC9-4B5A-919C-4205B0C804B6")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIInputStreamReference : public IInspectable

    OpenSequentialReadAsync proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReferenceStatics_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReferenceStatics_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReferenceStatics, "857309DC-3FBF-4E7D-986F-EF3B1A07A964")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamReferenceStatics : public IInspectable

    CreateFromFile	proc :ptr, :ptr
    CreateFromUri	proc :ptr, :ptr
    CreateFromStream	proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIInputStream_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIInputStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIInputStream, "905A0FE2-BC53-11DF-8C49-001E4FC686DA")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIInputStream : public IInspectable

    ReadAsync		proc :ptr, :UINT32, :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIOutputStream_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIOutputStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIOutputStream, "905A0FE6-BC53-11DF-8C49-001E4FC686DA")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIOutputStream : public IInspectable

    WriteAsync		proc :ptr, :ptr
    FlushAsync		proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream, "905A0FE1-BC53-11DF-8C49-001E4FC686DA")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStream : public IInspectable

    get_Size		proc :ptr
    put_Size		proc :UINT64
    GetInputStreamAt	proc :UINT64, :ptr
    GetOutputStreamAt	proc :UINT64, :ptr
    get_Position	proc :ptr
    Seek		proc :UINT64
    CloneStream		proc :ptr
    get_CanRead		proc :ptr
    get_CanWrite	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamWithContentType_INTERFACE_DEFINED__
____x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamWithContentType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamWithContentType, "CC254827-4B3D-438F-9232-10C76BC7E038")

.comdef __x_ABI_CWindows_CStorage_CStreams_CIRandomAccessStreamWithContentType : public IInspectable

    .ends

endif


HSTRING_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HSTRING

HSTRING_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HSTRING


HSTRING_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HSTRING

HSTRING_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HSTRING


endif

