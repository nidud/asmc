ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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

ifndef __windows2Estorage_h__
define __windows2Estorage_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.FileProperties.inc
include Windows.Storage.Provider.inc
include Windows.Storage.Search.inc
include windows.foundation.collections.inc

ifndef ____FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer, "5adbc543-2170-5ad9-b35e-968cdb78fb30")

.comdef __FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer, "af3c131d-67aa-5c8d-ae0e-272ba24ae74f")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer, "a785be1d-159e-53ad-9553-598b03dca048")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CIStorageFile_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CIStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CIStorageFile, "314d2318-74ee-535c-b361-2144dbc573a0")

.comdef __FIIterator_1_Windows__CStorage__CIStorageFile : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CIStorageFile_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CIStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CIStorageFile, "76d43c7e-fd09-5908-a2b9-a49b4848294b")

.comdef __FIIterable_1_Windows__CStorage__CIStorageFile : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CIStorageItem, "05b487c2-3830-5d3c-98da-25fa11542dbd")

.comdef __FIIterator_1_Windows__CStorage__CIStorageItem : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CIStorageItem, "bb8b8418-65d1-544b-b083-6d172f568c73")

.comdef __FIIterable_1_Windows__CStorage__CIStorageItem : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CStorageFile, "43e29f53-0298-55aa-a6c8-4edd323d9598")

.comdef __FIIterator_1_Windows__CStorage__CStorageFile : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CStorageFile, "9ac00304-83ea-5688-87b6-ae38aab65d0b")

.comdef __FIIterable_1_Windows__CStorage__CStorageFile : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CStorageFolder, "5aac96fb-b3b9-5a7f-a920-4b5a8df81168")

.comdef __FIIterator_1_Windows__CStorage__CStorageFolder : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CStorageFolder, "4669befc-ae5c-52b1-8a97-5466ce61e94e")

.comdef __FIIterable_1_Windows__CStorage__CStorageFolder : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING_Windows__CStorage__CApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapView_2_HSTRING_Windows__CStorage__CApplicationDataContainer, "13624f8d-85cc-5780-a78d-64dba58f2c3c")

.comdef __FIMapView_2_HSTRING_Windows__CStorage__CApplicationDataContainer : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CStorageFolder, "e20debc6-dc4e-542e-a2e7-a24d19c8dd62")

.comdef __FIVectorView_1_Windows__CStorage__CStorageFolder : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVector_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CStorage__CStorageFolder, "6c26b7be-5f01-5a60-9dd7-fd17be3a9dd6")

.comdef __FIVector_1_Windows__CStorage__CStorageFolder : public IInspectable

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

ifndef ____FVectorChangedEventHandler_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FVectorChangedEventHandler_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FVectorChangedEventHandler_1_Windows__CStorage__CStorageFolder, "2057b641-4b9b-5338-a19a-e9a951916775")

.comdef __FVectorChangedEventHandler_1_Windows__CStorage__CStorageFolder : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FIObservableVector_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIObservableVector_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIObservableVector_1_Windows__CStorage__CStorageFolder, "358f44df-2a45-5cb8-9385-1ff66808cde0")

.comdef __FIObservableVector_1_Windows__CStorage__CStorageFolder : public IInspectable

    add_VectorChanged	proc :ptr, :ptr
    remove_VectorChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CIStorageItem, "85575a41-06cb-58d0-b98a-7c8f06e6e9d7")

.comdef __FIVectorView_1_Windows__CStorage__CIStorageItem : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CStorageFile, "80646519-5e2a-595d-a8cd-2a24b4067f1b")

.comdef __FIVectorView_1_Windows__CStorage__CStorageFile : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVector_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CStorage__CStorageFile, "fcbc8b8b-6103-5b4e-ba00-4bc2cedb6a35")

.comdef __FIVector_1_Windows__CStorage__CStorageFile : public IInspectable

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

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CIStorageItem, "51436e75-ace1-5a68-b260-f843b846f0db")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CIStorageItem : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CIStorageItem, "4b1c0fd7-7a01-5e7a-a6fe-be4500283f23")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CIStorageItem : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFile, "cb4206c5-0988-5104-afa9-253c298f86fd")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFile, "03362e33-e413-5f29-97d0-48a4780935f9")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFolder, "ed2d1d9b-26ec-5be7-a8a3-56458933d25f")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CStorageFolder : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFolder, "ca40b21b-aeb1-5a61-9e08-3bd5d9594023")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFolder : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CIStorageItem, "92c3102f-a327-5318-a6c1-76f6b2a0abfb")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CIStorageItem : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CIStorageItem, "5fc9c137-ebb7-5e6c-9cba-686f2ec2b0bb")

.comdef __FIAsyncOperation_1_Windows__CStorage__CIStorageItem : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile, "e521c894-2c26-5946-9e61-2b5e188d01ed")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStorageFile, "5e52f8ce-aced-5a42-95b4-f674dd84885e")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStorageFile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFolder, "c211026e-9e63-5452-ba54-3a07d6a96874")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageFolder : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStorageFolder, "6be9e7d7-e83a-5cbc-802c-1768960b52c3")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStorageFolder : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageLibrary_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageLibrary_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageLibrary, "36d560c3-731f-5c70-b907-30bc99bc300f")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageLibrary : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStorageLibrary_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CStorageLibrary_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStorageLibrary, "2f160a19-99c1-52b9-8dca-14e4ab79f287")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStorageLibrary : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageStreamTransaction_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageStreamTransaction_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageStreamTransaction, "d11739e6-2995-5d33-bfff-51b6041f68c1")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CStorageStreamTransaction : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CStorageStreamTransaction_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CStorageStreamTransaction_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CStorageStreamTransaction, "0d81405a-9bd3-5e87-82f4-9b4128a887eb")

.comdef __FIAsyncOperation_1_Windows__CStorage__CStorageStreamTransaction : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CApplicationData_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CApplicationData_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CApplicationData_IInspectable, "b5348b3b-5081-5ae9-8fa3-4d22d68fb0ea")

.comdef __FITypedEventHandler_2_Windows__CStorage__CApplicationData_IInspectable : public IUnknown

    _Invoke		proc :ptr IApplicationData, :ptr IInspectable
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CStorageLibrary_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CStorageLibrary_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CStorageLibrary_IInspectable, "edc09538-bbae-5b2b-9e81-b449ea7e48fe")

.comdef __FITypedEventHandler_2_Windows__CStorage__CStorageLibrary_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace Windows
.namespace Storage

.enum KnownLibraryId {
    KnownLibraryId_Music,
    KnownLibraryId_Pictures,
    KnownLibraryId_Videos,
    KnownLibraryId_Documents
    }

.enum CreationCollisionOption {
    CreationCollisionOption_GenerateUniqueName,
    CreationCollisionOption_ReplaceExisting,
    CreationCollisionOption_FailIfExists,
    CreationCollisionOption_OpenIfExists
    }

.enum NameCollisionOption {
    NameCollisionOption_GenerateUniqueName,
    NameCollisionOption_ReplaceExisting,
    NameCollisionOption_FailIfExists
    }

.enum StorageDeleteOption {
    StorageDeleteOption_Default,
    StorageDeleteOption_PermanentDelete
    }

.enum StorageItemTypes {
    StorageItemTypes_None	= 0,
    StorageItemTypes_File	= 0x1,
    StorageItemTypes_Folder	= 0x2
    }

.enum FileAttributes {
    FileAttributes_Normal	= 0,
    FileAttributes_ReadOnly	= 0x1,
    FileAttributes_Directory	= 0x10,
    FileAttributes_Archive	= 0x20,
    FileAttributes_Temporary	= 0x100,
    FileAttributes_LocallyIncomplete	= 0x200
    }

.enum FileAccessMode {
    FileAccessMode_Read,
    FileAccessMode_ReadWrite
    }

.enum StreamedFileFailureMode {
    StreamedFileFailureMode_Failed,
    StreamedFileFailureMode_CurrentlyUnavailable,
    StreamedFileFailureMode_Incomplete
    }

.enum ApplicationDataLocality {
    ApplicationDataLocality_Local,
    ApplicationDataLocality_Roaming,
    ApplicationDataLocality_Temporary,
    ApplicationDataLocality_LocalCache
    }

.enum ApplicationDataCreateDisposition {
    ApplicationDataCreateDisposition_Always,
    ApplicationDataCreateDisposition_Existing
    }


ifndef ____x_ABI_CWindows_CStorage_CIStreamedFileDataRequestedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStreamedFileDataRequestedHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IStreamedFileDataRequestedHandler, "FEF6A824-2FE1-4D07-A35B-B77C50B5F4CC")

.comdef IStreamedFileDataRequestedHandler : public IUnknown

    _Invoke		proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIApplicationDataSetVersionHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIApplicationDataSetVersionHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationDataSetVersionHandler, "A05791E6-CC9F-4687-ACAB-A364FD785463")

.comdef IApplicationDataSetVersionHandler : public IUnknown

    _Invoke		proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageLibraryStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageLibraryStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageLibraryStatics, "4208A6DB-684A-49C6-9E59-90121EE050D6")

.comdef IStorageLibraryStatics : public IInspectable

    GetLibraryAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageLibrary_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageLibrary_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageLibrary, "1EDD7103-0E5E-4D6C-B5E8-9318983D6A03")

.comdef IStorageLibrary : public IInspectable

    RequestAddFolderAsync proc :ptr
    RequestRemoveFolderAsync proc :ptr, :ptr
    get_Folders		proc :ptr
    get_SaveFolder	proc :ptr
    add_DefinitionChanged proc :ptr, :ptr
    remove_DefinitionChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIKnownFoldersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIKnownFoldersStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IKnownFoldersStatics, "5A2A7520-4802-452D-9AD9-4351ADA7EC35")

.comdef IKnownFoldersStatics : public IInspectable

    get_MusicLibrary	proc :ptr
    get_PicturesLibrary proc :ptr
    get_VideosLibrary	proc :ptr
    get_DocumentsLibrary proc :ptr
    get_HomeGroup	proc :ptr
    get_RemovableDevices proc :ptr
    get_MediaServerDevices proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIKnownFoldersPlaylistsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIKnownFoldersPlaylistsStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IKnownFoldersPlaylistsStatics, "DAD5ECD6-306F-4D6A-B496-46BA8EB106CE")

.comdef IKnownFoldersPlaylistsStatics : public IInspectable

    get_Playlists	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIKnownFoldersCameraRollStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIKnownFoldersCameraRollStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IKnownFoldersCameraRollStatics, "5D115E66-27E8-492F-B8E5-2F90896CD4CD")

.comdef IKnownFoldersCameraRollStatics : public IInspectable

    get_CameraRoll	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIKnownFoldersSavedPicturesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIKnownFoldersSavedPicturesStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IKnownFoldersSavedPicturesStatics, "055C93EA-253D-467C-B6CA-A97DA1E9A18D")

.comdef IKnownFoldersSavedPicturesStatics : public IInspectable

    get_SavedPictures	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIDownloadsFolderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIDownloadsFolderStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IDownloadsFolderStatics, "27862ED0-404E-47DF-A1E2-E37308BE7B37")

.comdef IDownloadsFolderStatics : public IInspectable

    CreateFileAsync	proc :HSTRING, :ptr
    CreateFolderAsync	proc :HSTRING, :ptr
    CreateFileWithCollisionOptionAsync proc :HSTRING, :ptr, :ptr
    CreateFolderWithCollisionOptionAsync proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStreamedFileDataRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStreamedFileDataRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IStreamedFileDataRequest, "1673FCCE-DABD-4D50-BEEE-180B8A8191B6")

.comdef IStreamedFileDataRequest : public IInspectable

    FailAndClose	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageFileStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageFileStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFileStatics, "5984C710-DAF2-43C8-8BB4-A4D3EACFD03F")

.comdef IStorageFileStatics : public IInspectable

    GetFileFromPathAsync proc :HSTRING, :ptr
    GetFileFromApplicationUriAsync proc :ptr, :ptr
    CreateStreamedFileAsync proc :HSTRING, :ptr, :ptr, :ptr
    ReplaceWithStreamedFileAsync proc :ptr, :ptr, :ptr, :ptr
    CreateStreamedFileFromUriAsync proc :HSTRING, :ptr, :ptr, :ptr
    ReplaceWithStreamedFileFromUriAsync proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItem, "4207A996-CA2F-42F7-BDE8-8B10457A7F30")

.comdef IStorageItem : public IInspectable

    RenameAsyncOverloadDefaultOptions proc :HSTRING, :ptr
    RenameAsync		proc :HSTRING, :ptr, :ptr
    DeleteAsyncOverloadDefaultOptions proc :ptr
    DeleteAsync		proc :ptr, :ptr
    GetBasicPropertiesAsync proc :ptr
    get_Name		proc :ptr HSTRING
    get_Path		proc :ptr HSTRING
    get_Attributes	proc :ptr
    get_DateCreated	proc :ptr
    IsOfType		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageFolder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFolder, "72D1CB78-B3EF-4F75-A80B-6FD9DAE2944B")

.comdef IStorageFolder : public IInspectable

    CreateFileAsyncOverloadDefaultOptions proc :HSTRING, :ptr ptr __FIAsyncOperation_1_Windows__CStorage__CStorageFile
    CreateFileAsync	proc :HSTRING, :Windows::Storage::CreationCollisionOption, :ptr ptr __FIAsyncOperation_1_Windows__CStorage__CStorageFile
    CreateFolderAsyncOverloadDefaultOptions proc :HSTRING, :ptr ptr __FIAsyncOperation_1_Windows__CStorage__CStorageFolder
    CreateFolderAsync	proc :HSTRING, :Windows::Storage::CreationCollisionOption, :ptr ptr __FIAsyncOperation_1_Windows__CStorage__CStorageFolder
    GetFileAsync	proc :HSTRING, :ptr ptr __FIAsyncOperation_1_Windows__CStorage__CStorageFile
    GetFolderAsync	proc :HSTRING, :ptr ptr __FIAsyncOperation_1_Windows__CStorage__CStorageFolder
    GetItemAsync	proc :HSTRING, :ptr ptr __FIAsyncOperation_1_Windows__CStorage__CIStorageItem
    GetFilesAsyncOverloadDefaultOptionsStartAndCount proc :ptr ptr __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFile
    GetFoldersAsyncOverloadDefaultOptionsStartAndCount proc :ptr ptr __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CStorageFolder
    GetItemsAsyncOverloadDefaultStartAndCount proc :ptr ptr __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CIStorageItem
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageFile_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFile, "FA3F6186-4214-428C-A64C-14C9AC7315EA")

.comdef IStorageFile : public IInspectable

    get_FileType	proc :ptr
    get_ContentType	proc :ptr
    OpenAsync		proc :ptr, :ptr
    OpenTransactedWriteAsync proc :ptr
    CopyOverloadDefaultNameAndOptions proc :ptr, :ptr
    CopyOverloadDefaultOptions proc :ptr, :HSTRING, :ptr
    CopyOverload	proc :ptr, :HSTRING, :ptr, :ptr
    CopyAndReplaceAsync proc :ptr, :ptr
    MoveOverloadDefaultNameAndOptions proc :ptr, :ptr
    MoveOverloadDefaultOptions proc :ptr, :HSTRING, :ptr
    MoveOverload	proc :ptr, :HSTRING, :ptr, :ptr
    MoveAndReplaceAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageFolderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageFolderStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFolderStatics, "08F327FF-85D5-48B9-AEE9-28511E339F9F")

.comdef IStorageFolderStatics : public IInspectable

    GetFolderFromPathAsync proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageItem2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageItem2_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItem2, "53F926D2-083C-4283-B45B-81C007237E44")

.comdef IStorageItem2 : public IInspectable

    GetParentAsync	proc :ptr
    IsEqual		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageItemProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageItemProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItemProperties, "86664478-8029-46FE-A789-1C2F3E2FFB5C")

.comdef IStorageItemProperties : public IInspectable

    GetThumbnailAsyncOverloadDefaultSizeDefaultOptions proc :ptr, :ptr
    GetThumbnailAsyncOverloadDefaultOptions proc :ptr, :UINT32, :ptr
    GetThumbnailAsync	proc :ptr, :UINT32, :ptr, :ptr
    get_DisplayName	proc :ptr
    get_DisplayType	proc :ptr
    get_FolderRelativeId proc :ptr
    get_Properties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageItemProperties2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageItemProperties2_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItemProperties2, "8E86A951-04B9-4BD2-929D-FEF3F71621D0")

.comdef IStorageItemProperties2 : public IInspectable

    GetScaledImageAsThumbnailAsyncOverloadDefaultSizeDefaultOptions proc :ptr, :ptr
    GetScaledImageAsThumbnailAsyncOverloadDefaultOptions proc :ptr, :UINT32, :ptr
    GetScaledImageAsThumbnailAsync proc :ptr, :UINT32, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageItemPropertiesWithProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageItemPropertiesWithProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItemPropertiesWithProvider, "861BF39B-6368-4DEE-B40E-74684A5CE714")

.comdef IStorageItemPropertiesWithProvider : public IInspectable

    get_Provider	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageFilePropertiesWithAvailability_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageFilePropertiesWithAvailability_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFilePropertiesWithAvailability, "AFCBBE9B-582B-4133-9648-E44CA46EE491")

.comdef IStorageFilePropertiesWithAvailability : public IInspectable

    get_IsAvailable	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageProvider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageProvider, "E705EED4-D478-47D6-BA46-1A8EBE114A20")

.comdef IStorageProvider : public IInspectable

    get_Id		proc :ptr
    get_DisplayName	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageFolder2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageFolder2_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFolder2, "E827E8B9-08D9-4A8E-A0AC-FE5ED3CBBBD3")

.comdef IStorageFolder2 : public IInspectable

    TryGetItemAsync	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIFileIOStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIFileIOStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IFileIOStatics, "887411EB-7F54-4732-A5F0-5E43E3B8C2F5")

.comdef IFileIOStatics : public IInspectable

    ReadTextAsync	proc :ptr, :ptr
    ReadTextWithEncodingAsync proc :ptr, :ptr, :ptr
    WriteTextAsync	proc :ptr, :HSTRING, :ptr
    WriteTextWithEncodingAsync proc :ptr, :HSTRING, :ptr, :ptr
    AppendTextAsync	proc :ptr, :HSTRING, :ptr
    AppendTextWithEncodingAsync proc :ptr, :HSTRING, :ptr, :ptr
    ReadLinesAsync	proc :ptr, :ptr
    ReadLinesWithEncodingAsync proc :ptr, :ptr, :ptr
    WriteLinesAsync	proc :ptr, :ptr, :ptr
    WriteLinesWithEncodingAsync proc :ptr, :ptr, :ptr, :ptr
    AppendLinesAsync	proc :ptr, :ptr, :ptr
    AppendLinesWithEncodingAsync proc :ptr, :ptr, :ptr, :ptr
    ReadBufferAsync	proc :ptr, :ptr
    WriteBufferAsync	proc :ptr, :ptr, :ptr
    WriteBytesAsync	proc :ptr, :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIPathIOStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIPathIOStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IPathIOStatics, "0F2F3758-8EC7-4381-922B-8F6C07D288F3")

.comdef IPathIOStatics : public IInspectable

    ReadTextAsync	proc :HSTRING, :ptr
    ReadTextWithEncodingAsync proc :HSTRING, :ptr, :ptr
    WriteTextAsync	proc :HSTRING, :HSTRING, :ptr
    WriteTextWithEncodingAsync proc :HSTRING, :HSTRING, :ptr, :ptr
    AppendTextAsync	proc :HSTRING, :HSTRING, :ptr
    AppendTextWithEncodingAsync proc :HSTRING, :HSTRING, :ptr, :ptr
    ReadLinesAsync	proc :HSTRING, :ptr
    ReadLinesWithEncodingAsync proc :HSTRING, :ptr, :ptr
    WriteLinesAsync	proc :HSTRING, :ptr, :ptr
    WriteLinesWithEncodingAsync proc :HSTRING, :ptr, :ptr, :ptr
    AppendLinesAsync	proc :HSTRING, :ptr, :ptr
    AppendLinesWithEncodingAsync proc :HSTRING, :ptr, :ptr, :ptr
    ReadBufferAsync	proc :HSTRING, :ptr
    WriteBufferAsync	proc :HSTRING, :ptr, :ptr
    WriteBytesAsync	proc :HSTRING, :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CICachedFileManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CICachedFileManagerStatics_INTERFACE_DEFINED__

DEFINE_IIDX(ICachedFileManagerStatics, "8FFC224A-E782-495D-B614-654C4F0B2370")

.comdef ICachedFileManagerStatics : public IInspectable

    DeferUpdates	proc :ptr
    CompleteUpdatesAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemAudioProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemAudioProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemAudioProperties, "3F8F38B7-308C-47E1-924D-8645348E5DB7")

.comdef ISystemAudioProperties : public IInspectable

    get_EncodingBitrate proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemGPSProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemGPSProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemGPSProperties, "C0F46EB4-C174-481A-BC25-921986F6A6F3")

.comdef ISystemGPSProperties : public IInspectable

    get_LatitudeDecimal proc :ptr
    get_LongitudeDecimal proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemImageProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemImageProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemImageProperties, "011B2E30-8B39-4308-BEA1-E8AA61E47826")

.comdef ISystemImageProperties : public IInspectable

    get_HorizontalSize	proc :ptr
    get_VerticalSize	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemMediaProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemMediaProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemMediaProperties, "A42B3316-8415-40DC-8C44-98361D235430")

.comdef ISystemMediaProperties : public IInspectable

    get_Duration	proc :ptr
    get_Producer	proc :ptr
    get_Publisher	proc :ptr
    get_SubTitle	proc :ptr
    get_Writer		proc :ptr
    get_Year		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemMusicProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemMusicProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemMusicProperties, "B47988D5-67AF-4BC3-8D39-5B89022026A1")

.comdef ISystemMusicProperties : public IInspectable

    get_AlbumArtist	proc :ptr
    get_AlbumTitle	proc :ptr
    get_Artist		proc :ptr
    get_Composer	proc :ptr
    get_Conductor	proc :ptr
    get_DisplayArtist	proc :ptr
    get_Genre		proc :ptr
    get_TrackNumber	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemPhotoProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemPhotoProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemPhotoProperties, "4734FC3D-AB21-4424-B735-F4353A56C8FC")

.comdef ISystemPhotoProperties : public IInspectable

    get_CameraManufacturer proc :ptr
    get_CameraModel	proc :ptr
    get_DateTaken	proc :ptr
    get_Orientation	proc :ptr
    get_PeopleNames	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemVideoProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemVideoProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemVideoProperties, "2040F715-67F8-4322-9B80-4FA9FEFB83E8")

.comdef ISystemVideoProperties : public IInspectable

    get_Director	proc :ptr
    get_FrameHeight	proc :ptr
    get_FrameWidth	proc :ptr
    get_Orientation	proc :ptr
    get_TotalBitrate	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISystemProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISystemProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemProperties, "917A71C1-85F3-4DD1-B001-A50BFD21C8D2")

.comdef ISystemProperties : public IInspectable

    get_Author		proc :ptr
    get_Comment		proc :ptr
    get_ItemNameDisplay proc :ptr
    get_Keywords	proc :ptr
    get_Rating		proc :ptr
    get_Title		proc :ptr
    get_Audio		proc :ptr
    get_GPS		proc :ptr
    get_Media		proc :ptr
    get_Music		proc :ptr
    get_Photo		proc :ptr
    get_Video		proc :ptr
    get_Image		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIStorageStreamTransaction_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIStorageStreamTransaction_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageStreamTransaction, "F67CF363-A53D-4D94-AE2C-67232D93ACDD")

.comdef IStorageStreamTransaction : public IInspectable

    get_Stream		proc :ptr
    CommitAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIApplicationDataStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationDataStatics, "5612147B-E843-45E3-94D8-06169E3C8E17")

.comdef IApplicationDataStatics : public IInspectable

    get_Current		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIApplicationData_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationData, "C3DA6FB7-B744-4B45-B0B8-223A0938D0DC")

.comdef IApplicationData : public IInspectable

    get_Version		proc :ptr
    SetVersionAsync	proc :UINT32, :ptr, :ptr
    ClearAllAsync	proc :ptr
    ClearAsync		proc :ptr, :ptr
    get_LocalSettings	proc :ptr
    get_RoamingSettings proc :ptr
    get_LocalFolder	proc :ptr
    get_RoamingFolder	proc :ptr
    get_TemporaryFolder proc :ptr
    add_DataChanged	proc :ptr, :ptr
    remove_DataChanged	proc :EventRegistrationToken
    SignalDataChanged	proc
    get_RoamingStorageQuota proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISetVersionRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISetVersionRequest_INTERFACE_DEFINED__

DEFINE_IIDX(ISetVersionRequest, "B9C76B9B-1056-4E69-8330-162619956F9B")

.comdef ISetVersionRequest : public IInspectable

    get_CurrentVersion	proc :ptr
    get_DesiredVersion	proc :ptr
    GetDeferral		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CISetVersionDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CISetVersionDeferral_INTERFACE_DEFINED__

DEFINE_IIDX(ISetVersionDeferral, "033508A2-781A-437A-B078-3F32BADCFE47")

.comdef ISetVersionDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CIApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationDataContainer, "C5AEFD1E-F467-40BA-8566-AB640A441E1D")

.comdef IApplicationDataContainer : public IInspectable

    get_Name		proc :ptr
    get_Locality	proc :ptr
    get_Values		proc :ptr
    get_Containers	proc :ptr
    CreateContainer	proc :HSTRING, :ptr, :ptr
    DeleteContainer	proc :HSTRING
   .ends

endif

.endn
.endn

HSTRING_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr DWORD, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr DWORD, :ptr HSTRING

endif

