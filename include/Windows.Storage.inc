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

ifndef DEF_IKeyValuePair_ApplicationDataContainer_USE
define DEF_IKeyValuePair_ApplicationDataContainer_USE

DEFINE_IIDX(__FIKeyValuePair_2_HSTRING_Windows__CStorage__CApplicationDataContainer, "5adbc543-2170-5ad9-b35e-968cdb78fb30")

.comdef IKeyValuePair_ApplicationDataContainer : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
    .ends

endif

ifndef __IIterator_ApplicationDataContainer_INTERFACE_DEFINED__
define __IIterator_ApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(IIterator_ApplicationDataContainer, "af3c131d-67aa-5c8d-ae0e-272ba24ae74f")

.comdef IIterator_ApplicationDataContainer : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef __IIterable_ApplicationDataContainer_INTERFACE_DEFINED__
define __IIterable_ApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(IIterable_ApplicationDataContainer, "a785be1d-159e-53ad-9553-598b03dca048")

.comdef IIterable_ApplicationDataContainer : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef __IIterator_IStorageFile_INTERFACE_DEFINED__
define __IIterator_IStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IIterator_IStorageFile, "314d2318-74ee-535c-b361-2144dbc573a0")

.comdef IIterator_IStorageFile : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef __IIterable_IStorageFile_INTERFACE_DEFINED__
define __IIterable_IStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IIterable_IStorageFile, "76d43c7e-fd09-5908-a2b9-a49b4848294b")

.comdef IIterable_IStorageFile : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef __IIterator_IStorageItem_INTERFACE_DEFINED__
define __IIterator_IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IIterator_IStorageItem, "05b487c2-3830-5d3c-98da-25fa11542dbd")

.comdef IIterator_IStorageItem : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef __IIterable_IStorageItem_INTERFACE_DEFINED__
define __IIterable_IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IIterable_IStorageItem, "bb8b8418-65d1-544b-b083-6d172f568c73")

.comdef IIterable_IStorageItem : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef __IIterator_StorageFile_INTERFACE_DEFINED__
define __IIterator_StorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IIterator_StorageFile, "43e29f53-0298-55aa-a6c8-4edd323d9598")

.comdef IIterator_StorageFile : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef __IIterable_StorageFile_INTERFACE_DEFINED__
define __IIterable_StorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IIterable_StorageFile, "9ac00304-83ea-5688-87b6-ae38aab65d0b")

.comdef IIterable_StorageFile : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef __IIterator_StorageFolder_INTERFACE_DEFINED__
define __IIterator_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IIterator_StorageFolder, "5aac96fb-b3b9-5a7f-a920-4b5a8df81168")

.comdef IIterator_StorageFolder : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef __IIterable_StorageFolder_INTERFACE_DEFINED__
define __IIterable_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IIterable_StorageFolder, "4669befc-ae5c-52b1-8a97-5466ce61e94e")

.comdef IIterable_StorageFolder : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef __ApplicationDataContainer_INTERFACE_DEFINED__
define __ApplicationDataContainer_INTERFACE_DEFINED__

DEFINE_IIDX(ApplicationDataContainer, "13624f8d-85cc-5780-a78d-64dba58f2c3c")

.comdef ApplicationDataContainer : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
    .ends

endif

ifndef __IVectorView_StorageFolder_INTERFACE_DEFINED__
define __IVectorView_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IVectorView_StorageFolder, "e20debc6-dc4e-542e-a2e7-a24d19c8dd62")

.comdef IVectorView_StorageFolder : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
    .ends

endif

ifndef __IVector_StorageFolder_INTERFACE_DEFINED__
define __IVector_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IVector_StorageFolder, "6c26b7be-5f01-5a60-9dd7-fd17be3a9dd6")

.comdef IVector_StorageFolder : public IInspectable

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

ifndef __VectorChangedEventHandler_StorageFolder_INTERFACE_DEFINED__
define __VectorChangedEventHandler_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(VectorChangedEventHandler_StorageFolder, "2057b641-4b9b-5338-a19a-e9a951916775")

.comdef VectorChangedEventHandler_StorageFolder : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef __IObservableVector_StorageFolder_INTERFACE_DEFINED__
define __IObservableVector_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IObservableVector_StorageFolder, "358f44df-2a45-5cb8-9385-1ff66808cde0")

.comdef IObservableVector_StorageFolder : public IInspectable

    add_VectorChanged	proc :ptr, :ptr
    remove_VectorChanged proc :EventRegistrationToken
    .ends

endif

ifndef __IVectorView_IStorageItem_INTERFACE_DEFINED__
define __IVectorView_IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IVectorView_IStorageItem, "85575a41-06cb-58d0-b98a-7c8f06e6e9d7")

.comdef IVectorView_IStorageItem : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
    .ends

endif

ifndef __IVectorView_StorageFile_INTERFACE_DEFINED__
define __IVectorView_CStorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IVectorView_StorageFile, "80646519-5e2a-595d-a8cd-2a24b4067f1b")

.comdef IVectorView_StorageFile : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
    .ends

endif

ifndef __IVector_StorageFile_INTERFACE_DEFINED__
define __IVector_StorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IVector_StorageFile, "fcbc8b8b-6103-5b4e-ba00-4bc2cedb6a35")

.comdef IVector_StorageFile : public IInspectable

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

ifndef __IAsyncOperationCompletedHandler_IStorageItem_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_IStorageItem, "51436e75-ace1-5a68-b260-f843b846f0db")

.comdef IAsyncOperationCompletedHandler_IStorageItem : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef __IAsyncOperation_IStorageItem_INTERFACE_DEFINED__
define __IAsyncOperation_IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperation_IStorageItem, "4b1c0fd7-7a01-5e7a-a6fe-be4500283f23")

.comdef IAsyncOperation_IStorageItem : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef __IAsyncOperationCompletedHandler_StorageFile_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_StorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_StorageFile, "cb4206c5-0988-5104-afa9-253c298f86fd")

.comdef IAsyncOperationCompletedHandler_StorageFile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif


DEFINE_IIDX(IAsyncOperation_StorageFile, "03362e33-e413-5f29-97d0-48a4780935f9")

.comdef IAsyncOperation_StorageFile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

ifndef __IAsyncOperationCompletedHandler_StorageFolder_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_StorageFolder, "ed2d1d9b-26ec-5be7-a8a3-56458933d25f")

.comdef IAsyncOperationCompletedHandler_StorageFolder : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef __IAsyncOperation_StorageFolder_INTERFACE_DEFINED__
define __IAsyncOperation_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperation_StorageFolder, "ca40b21b-aeb1-5a61-9e08-3bd5d9594023")

.comdef IAsyncOperation_StorageFolder : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef __IAsyncOperationCompletedHandler_IStorageItem_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_IStorageItem, "92c3102f-a327-5318-a6c1-76f6b2a0abfb")

.comdef IAsyncOperationCompletedHandler_IStorageItem : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef __IAsyncOperation_IStorageItem_INTERFACE_DEFINED__
define __IAsyncOperation_IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperation_IStorageItem, "5fc9c137-ebb7-5e6c-9cba-686f2ec2b0bb")

.comdef IAsyncOperation_IStorageItem : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef __IAsyncOperationCompletedHandler_StorageFile_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_StorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_StorageFile, "e521c894-2c26-5946-9e61-2b5e188d01ed")

.comdef IAsyncOperationCompletedHandler_StorageFile : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef __IAsyncOperation_StorageFile_INTERFACE_DEFINED__
define __IAsyncOperation_StorageFile_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperation_StorageFile, "5e52f8ce-aced-5a42-95b4-f674dd84885e")

.comdef IAsyncOperation_StorageFile : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef __IAsyncOperationCompletedHandler_StorageFolder_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_StorageFolder, "c211026e-9e63-5452-ba54-3a07d6a96874")

.comdef IAsyncOperationCompletedHandler_StorageFolder : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef __IAsyncOperation_StorageFolder_INTERFACE_DEFINED__
define __IAsyncOperation_StorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperation_StorageFolder, "6be9e7d7-e83a-5cbc-802c-1768960b52c3")

.comdef IAsyncOperation_StorageFolder : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef __IAsyncOperationCompletedHandler_StorageLibrary_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_StorageLibrary_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_StorageLibrary, "36d560c3-731f-5c70-b907-30bc99bc300f")

.comdef IAsyncOperationCompletedHandler_StorageLibrary : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef __IAsyncOperation_StorageLibrary_INTERFACE_DEFINED__
define __IAsyncOperation_StorageLibrary_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperation_StorageLibrary, "2f160a19-99c1-52b9-8dca-14e4ab79f287")

.comdef IAsyncOperation_StorageLibrary : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef __IAsyncOperationCompletedHandler_StorageStreamTransaction_INTERFACE_DEFINED__
define __IAsyncOperationCompletedHandler_StorageStreamTransaction_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperationCompletedHandler_StorageStreamTransaction, "d11739e6-2995-5d33-bfff-51b6041f68c1")

.comdef IAsyncOperationCompletedHandler_StorageStreamTransaction : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef __IAsyncOperation_StorageStreamTransaction_INTERFACE_DEFINED__
define __IAsyncOperation_StorageStreamTransaction_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncOperation_StorageStreamTransaction, "0d81405a-9bd3-5e87-82f4-9b4128a887eb")

.comdef IAsyncOperation_StorageStreamTransaction : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

ifndef __ITypedEventHandler_INTERFACE_DEFINED__
define __ITypedEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(ITypedEventHandler, "b5348b3b-5081-5ae9-8fa3-4d22d68fb0ea")

.comdef ITypedEventHandler : public IUnknown

    _Invoke		proc :ptr IApplicationData, :ptr IInspectable
    .ends

endif

ifndef __ITypedEventHandler_StorageLibrary_IInspectable_INTERFACE_DEFINED__
define __ITypedEventHandler_StorageLibrary_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(ITypedEventHandler_StorageLibrary, "edc09538-bbae-5b2b-9e81-b449ea7e48fe")

.comdef ITypedEventHandler_StorageLibrary : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.enum KnownLibraryId {
    KnownLibraryId_Music	= 0,
    KnownLibraryId_Pictures	= 1,
    KnownLibraryId_Videos	= 2,
    KnownLibraryId_Documents	= 3
    }

.enum CreationCollisionOption {
    CreationCollisionOption_GenerateUniqueName	= 0,
    CreationCollisionOption_ReplaceExisting	= 1,
    CreationCollisionOption_FailIfExists	= 2,
    CreationCollisionOption_OpenIfExists	= 3
    }

.enum NameCollisionOption {
    NameCollisionOption_GenerateUniqueName	= 0,
    NameCollisionOption_ReplaceExisting = 1,
    NameCollisionOption_FailIfExists	= 2
    }

.enum StorageDeleteOption {
    StorageDeleteOption_Default = 0,
    StorageDeleteOption_PermanentDelete = 1
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
    FileAccessMode_Read = 0,
    FileAccessMode_ReadWrite	= 1
    }

.enum StreamedFileFailureMode {
    StreamedFileFailureMode_Failed	= 0,
    StreamedFileFailureMode_CurrentlyUnavailable	= 1,
    StreamedFileFailureMode_Incomplete	= 2
    }

.enum ApplicationDataLocality {
    ApplicationDataLocality_Local	= 0,
    ApplicationDataLocality_Roaming	= 1,
    ApplicationDataLocality_Temporary	= 2,
    ApplicationDataLocality_LocalCache	= 3
    }

.enum ApplicationDataCreateDisposition {
    ApplicationDataCreateDisposition_Always	= 0,
    ApplicationDataCreateDisposition_Existing	= 1
    }


ifndef __IStreamedFileDataRequestedHandler_INTERFACE_DEFINED__
define __IStreamedFileDataRequestedHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IStreamedFileDataRequestedHandler, "FEF6A824-2FE1-4D07-A35B-B77C50B5F4CC")

.comdef IStreamedFileDataRequestedHandler : public IUnknown

    _Invoke		proc :ptr
    .ends

endif

ifndef __IApplicationDataSetVersionHandler_INTERFACE_DEFINED__
define __IApplicationDataSetVersionHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationDataSetVersionHandler, "A05791E6-CC9F-4687-ACAB-A364FD785463")

.comdef IApplicationDataSetVersionHandler : public IUnknown

    _Invoke		proc :ptr
    .ends

endif

ifndef __IStorageLibraryStatics_INTERFACE_DEFINED__
define __IStorageLibraryStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageLibraryStatics, "4208A6DB-684A-49C6-9E59-90121EE050D6")

.comdef IStorageLibraryStatics : public IInspectable

    GetLibraryAsync	proc :ptr, :ptr
    .ends

endif

ifndef __IStorageLibrary_INTERFACE_DEFINED__
define __IStorageLibrary_INTERFACE_DEFINED__

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

ifndef __IKnownFoldersStatics_INTERFACE_DEFINED__
define __IKnownFoldersStatics_INTERFACE_DEFINED__

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

ifndef __IKnownFoldersPlaylistsStatics_INTERFACE_DEFINED__
define __IKnownFoldersPlaylistsStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IKnownFoldersPlaylistsStatics, "DAD5ECD6-306F-4D6A-B496-46BA8EB106CE")

.comdef IKnownFoldersPlaylistsStatics : public IInspectable

    get_Playlists	proc :ptr
    .ends

endif

ifndef __IKnownFoldersCameraRollStatics_INTERFACE_DEFINED__
define __IKnownFoldersCameraRollStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IKnownFoldersCameraRollStatics, "5D115E66-27E8-492F-B8E5-2F90896CD4CD")

.comdef IKnownFoldersCameraRollStatics : public IInspectable

    get_CameraRoll	proc :ptr
    .ends

endif

ifndef __IKnownFoldersSavedPicturesStatics_INTERFACE_DEFINED__
define __IKnownFoldersSavedPicturesStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IKnownFoldersSavedPicturesStatics, "055C93EA-253D-467C-B6CA-A97DA1E9A18D")

.comdef IKnownFoldersSavedPicturesStatics : public IInspectable

    get_SavedPictures	proc :ptr
    .ends

endif

ifndef __IDownloadsFolderStatics_INTERFACE_DEFINED__
define __IDownloadsFolderStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IDownloadsFolderStatics, "27862ED0-404E-47DF-A1E2-E37308BE7B37")

.comdef IDownloadsFolderStatics : public IInspectable

    CreateFileAsync	proc :HSTRING, :ptr
    CreateFolderAsync	proc :HSTRING, :ptr
    CreateFileWithCollisionOptionAsync proc :HSTRING, :ptr, :ptr
    CreateFolderWithCollisionOptionAsync proc :HSTRING, :ptr, :ptr
    .ends

endif

ifndef __IStreamedFileDataRequest_INTERFACE_DEFINED__
define __IStreamedFileDataRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IStreamedFileDataRequest, "1673FCCE-DABD-4D50-BEEE-180B8A8191B6")

.comdef IStreamedFileDataRequest : public IInspectable

    FailAndClose	proc :ptr
    .ends

endif

ifndef __IStorageFileStatics_INTERFACE_DEFINED__
define __IStorageFileStatics_INTERFACE_DEFINED__

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

ifndef __IStorageItem_INTERFACE_DEFINED__
define __IStorageItem_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItem, "4207A996-CA2F-42F7-BDE8-8B10457A7F30")

.comdef IStorageItem : public IInspectable

    RenameAsyncOverloadDefaultOptions proc :HSTRING, :ptr
    RenameAsync		proc :HSTRING, :ptr, :ptr
    DeleteAsyncOverloadDefaultOptions proc :ptr
    DeleteAsync		proc :ptr, :ptr
    GetBasicPropertiesAsync proc :ptr
    get_Name		proc :ptr
    get_Path		proc :ptr
    get_Attributes	proc :ptr
    get_DateCreated	proc :ptr
    IsOfType		proc :ptr, :ptr
    .ends

endif

ifndef __IStorageFolder_INTERFACE_DEFINED__
define __IStorageFolder_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFolder, "72D1CB78-B3EF-4F75-A80B-6FD9DAE2944B")

.comdef IStorageFolder : public IInspectable

    CreateFileAsyncOverloadDefaultOptions proc :HSTRING, :ptr
    CreateFileAsync	proc :HSTRING, :ptr, :ptr
    CreateFolderAsyncOverloadDefaultOptions proc :HSTRING, :ptr
    CreateFolderAsync	proc :HSTRING, :ptr, :ptr
    GetFileAsync	proc :HSTRING, :ptr
    GetFolderAsync	proc :HSTRING, :ptr
    GetItemAsync	proc :HSTRING, :ptr
    GetFilesAsyncOverloadDefaultOptionsStartAndCount proc :ptr
    GetFoldersAsyncOverloadDefaultOptionsStartAndCount proc :ptr
    GetItemsAsyncOverloadDefaultStartAndCount proc :ptr
    .ends

endif

ifndef __IStorageFile_INTERFACE_DEFINED__
define __IStorageFile_INTERFACE_DEFINED__

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

ifndef __IStorageFolderStatics_INTERFACE_DEFINED__
define __IStorageFolderStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFolderStatics, "08F327FF-85D5-48B9-AEE9-28511E339F9F")

.comdef IStorageFolderStatics : public IInspectable

    GetFolderFromPathAsync proc :HSTRING, :ptr
    .ends

endif

ifndef __IStorageItem2_INTERFACE_DEFINED__
define __IStorageItem2_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItem2, "53F926D2-083C-4283-B45B-81C007237E44")

.comdef IStorageItem2 : public IInspectable

    GetParentAsync	proc :ptr
    IsEqual		proc :ptr, :ptr
    .ends

endif

ifndef __IStorageItemProperties_INTERFACE_DEFINED__
define __IStorageItemProperties_INTERFACE_DEFINED__

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

ifndef __IStorageItemProperties2_INTERFACE_DEFINED__
define __IStorageItemProperties2_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItemProperties2, "8E86A951-04B9-4BD2-929D-FEF3F71621D0")

.comdef IStorageItemProperties2 : public IInspectable

    GetScaledImageAsThumbnailAsyncOverloadDefaultSizeDefaultOptions proc :ptr, :ptr
    GetScaledImageAsThumbnailAsyncOverloadDefaultOptions proc :ptr, :UINT32, :ptr
    GetScaledImageAsThumbnailAsync proc :ptr, :UINT32, :ptr, :ptr
    .ends

endif

ifndef __IStorageItemPropertiesWithProvider_INTERFACE_DEFINED__
define __IStorageItemPropertiesWithProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageItemPropertiesWithProvider, "861BF39B-6368-4DEE-B40E-74684A5CE714")

.comdef IStorageItemPropertiesWithProvider : public IInspectable

    get_Provider	proc :ptr
    .ends

endif

ifndef __IStorageFilePropertiesWithAvailability_INTERFACE_DEFINED__
define __IStorageFilePropertiesWithAvailability_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFilePropertiesWithAvailability, "AFCBBE9B-582B-4133-9648-E44CA46EE491")

.comdef IStorageFilePropertiesWithAvailability : public IInspectable

    get_IsAvailable	proc :ptr
    .ends

endif

ifndef __IStorageProvider_INTERFACE_DEFINED__
define __IStorageProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageProvider, "E705EED4-D478-47D6-BA46-1A8EBE114A20")

.comdef IStorageProvider : public IInspectable

    get_Id		proc :ptr
    get_DisplayName	proc :ptr
    .ends

endif

ifndef __IStorageFolder2_INTERFACE_DEFINED__
define __IStorageFolder2_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageFolder2, "E827E8B9-08D9-4A8E-A0AC-FE5ED3CBBBD3")

.comdef IStorageFolder2 : public IInspectable

    TryGetItemAsync	proc :HSTRING, :ptr
    .ends

endif

ifndef __IFileIOStatics_INTERFACE_DEFINED__
define __IFileIOStatics_INTERFACE_DEFINED__

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

ifndef __IPathIOStatics_INTERFACE_DEFINED__
define __IPathIOStatics_INTERFACE_DEFINED__

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

ifndef __ICachedFileManagerStatics_INTERFACE_DEFINED__
define __ICachedFileManagerStatics_INTERFACE_DEFINED__

DEFINE_IIDX(ICachedFileManagerStatics, "8FFC224A-E782-495D-B614-654C4F0B2370")

.comdef ICachedFileManagerStatics : public IInspectable

    DeferUpdates	proc :ptr
    CompleteUpdatesAsync proc :ptr, :ptr
    .ends

endif

ifndef __ISystemAudioProperties_INTERFACE_DEFINED__
define __ISystemAudioProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemAudioProperties, "3F8F38B7-308C-47E1-924D-8645348E5DB7")

.comdef ISystemAudioProperties : public IInspectable

    get_EncodingBitrate proc :ptr
    .ends

endif

ifndef __ISystemGPSProperties_INTERFACE_DEFINED__
define __ISystemGPSProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemGPSProperties, "C0F46EB4-C174-481A-BC25-921986F6A6F3")

.comdef ISystemGPSProperties : public IInspectable

    get_LatitudeDecimal proc :ptr
    get_LongitudeDecimal proc :ptr
    .ends

endif

ifndef __ISystemImageProperties_INTERFACE_DEFINED__
define __ISystemImageProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemImageProperties, "011B2E30-8B39-4308-BEA1-E8AA61E47826")

.comdef ISystemImageProperties : public IInspectable

    get_HorizontalSize	proc :ptr
    get_VerticalSize	proc :ptr
    .ends

endif

ifndef __ISystemMediaProperties_INTERFACE_DEFINED__
define __ISystemMediaProperties_INTERFACE_DEFINED__

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

ifndef __ISystemMusicProperties_INTERFACE_DEFINED__
define __ISystemMusicProperties_INTERFACE_DEFINED__

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

ifndef __ISystemPhotoProperties_INTERFACE_DEFINED__
define __ISystemPhotoProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemPhotoProperties, "4734FC3D-AB21-4424-B735-F4353A56C8FC")

.comdef ISystemPhotoProperties : public IInspectable

    get_CameraManufacturer proc :ptr
    get_CameraModel	proc :ptr
    get_DateTaken	proc :ptr
    get_Orientation	proc :ptr
    get_PeopleNames	proc :ptr
    .ends

endif

ifndef __ISystemVideoProperties_INTERFACE_DEFINED__
define __ISystemVideoProperties_INTERFACE_DEFINED__

DEFINE_IIDX(ISystemVideoProperties, "2040F715-67F8-4322-9B80-4FA9FEFB83E8")

.comdef ISystemVideoProperties : public IInspectable

    get_Director	proc :ptr
    get_FrameHeight	proc :ptr
    get_FrameWidth	proc :ptr
    get_Orientation	proc :ptr
    get_TotalBitrate	proc :ptr
    .ends

endif

ifndef __ISystemProperties_INTERFACE_DEFINED__
define __ISystemProperties_INTERFACE_DEFINED__

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

ifndef __IStorageStreamTransaction_INTERFACE_DEFINED__
define __IStorageStreamTransaction_INTERFACE_DEFINED__

DEFINE_IIDX(IStorageStreamTransaction, "F67CF363-A53D-4D94-AE2C-67232D93ACDD")

.comdef IStorageStreamTransaction : public IInspectable

    get_Stream		proc :ptr
    CommitAsync		proc :ptr
    .ends

endif

ifndef __IApplicationDataStatics_INTERFACE_DEFINED__
define __IApplicationDataStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IApplicationDataStatics, "5612147B-E843-45E3-94D8-06169E3C8E17")

.comdef IApplicationDataStatics : public IInspectable

    get_Current		proc :ptr
    .ends

endif

ifndef __IApplicationData_INTERFACE_DEFINED__
define __IApplicationData_INTERFACE_DEFINED__

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

ifndef __ISetVersionRequest_INTERFACE_DEFINED__
define __ISetVersionRequest_INTERFACE_DEFINED__

DEFINE_IIDX(ISetVersionRequest, "B9C76B9B-1056-4E69-8330-162619956F9B")

.comdef ISetVersionRequest : public IInspectable

    get_CurrentVersion	proc :ptr
    get_DesiredVersion	proc :ptr
    GetDeferral		proc :ptr
    .ends

endif

ifndef __ISetVersionDeferral_INTERFACE_DEFINED__
define __ISetVersionDeferral_INTERFACE_DEFINED__

DEFINE_IIDX(ISetVersionDeferral, "033508A2-781A-437A-B078-3F32BADCFE47")

.comdef ISetVersionDeferral : public IInspectable

    Complete		proc
    .ends

endif

ifndef __IApplicationDataContainer_INTERFACE_DEFINED__
define __IApplicationDataContainer_INTERFACE_DEFINED__

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

HSTRING_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr DWORD, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr DWORD, :ptr HSTRING

endif

