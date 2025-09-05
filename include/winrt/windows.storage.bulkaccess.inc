ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Estorage2Ebulkaccess_h__
define __windows2Estorage2Ebulkaccess_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc

ifndef ____FIIterator_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__

.comdef __FIIterator_1_Windows__CStorage__CBulkAccess__CFileInformation : public IInspectable
DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CBulkAccess__CFileInformation, "bf2f6543-230e-50bf-9c57-9e4ba8635903")

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CBulkAccess__CFileInformation, "dd96d7e9-892b-5932-b677-5bc32588008f")

.comdef __FIIterable_1_Windows__CStorage__CBulkAccess__CFileInformation : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CBulkAccess__CFolderInformation, "ff68b5b6-caad-553a-9808-95eea700c9de")

.comdef __FIIterator_1_Windows__CStorage__CBulkAccess__CFolderInformation : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CBulkAccess__CFolderInformation, "5c720bf5-7636-51fd-9ef7-d5f57f071a9b")

.comdef __FIIterable_1_Windows__CStorage__CBulkAccess__CFolderInformation : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation, "3da6401d-1279-55a1-962c-25cd23b99b27")

.comdef __FIIterator_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation : public IInspectable

    get_Current         proc :ptr
    get_HasCurrent      proc :ptr
    MoveNext            proc :ptr
    GetMany             proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation, "43bc252e-a3d6-5f00-a12c-b088d3b912d4")

.comdef __FIIterable_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation : public IInspectable

    First               proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation, "50bcd975-67ba-53b7-a5a7-1fb59f04bbb3")

.comdef __FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation, "506f1329-dbdc-5a37-91d5-b047cb24276d")

.comdef __FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation, "da3a4ef8-d315-529b-a73b-524490573f7e")

.comdef __FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation : public IInspectable

    GetAt               proc :SINT, :ptr
    get_Size            proc :ptr
    IndexOf             proc :ptr, :ptr, :ptr
    GetMany             proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation, "ebdb2c85-d27a-5c93-a1b3-6ca3651ada5d")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation : public IUnknown

    _Invoke             proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation, "222f6bb6-e71e-55cb-885d-e051e35995dc")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFileInformation : public IInspectable

    put_Completed       proc :ptr
    get_Completed       proc :ptr
    GetResults          proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation, "020713ec-604a-5e45-b03f-1b9e65253804")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation : public IUnknown

    _Invoke             proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation, "7f10e569-2bf7-5752-8f75-602809a7d304")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CFolderInformation : public IInspectable

    put_Completed       proc :ptr
    get_Completed       proc :ptr
    GetResults          proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation, "ff163034-ece9-55be-a6f8-08c72aae56b4")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation : public IUnknown

    _Invoke             proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation, "413d160c-3e1a-5603-acba-1e176d6a6082")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CBulkAccess__CIStorageItemInformation : public IInspectable

    put_Completed       proc :ptr
    get_Completed       proc :ptr
    GetResults          proc :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CBulkAccess__CIStorageItemInformation_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CBulkAccess__CIStorageItemInformation_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CBulkAccess__CIStorageItemInformation_IInspectable, "5b98b352-e0cf-58de-b2ec-4fd786bbb5a7")

.comdef __FITypedEventHandler_2_Windows__CStorage__CBulkAccess__CIStorageItemInformation_IInspectable : public IUnknown

    _Invoke             proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Storage
.namespace BulkAccess

ifndef ____x_ABI_CWindows_CStorage_CBulkAccess_CIStorageItemInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CBulkAccess_CIStorageItemInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_BulkAccess_IStorageItemInformation <L"Windows.Storage.BulkAccess.IStorageItemInformation">
DEFINE_IIDX(IStorageItemInformation, "87A5CB8B-8972-4F40-8DE0-D86FB179D8FA")

.comdef IStorageItemInformation : public IInspectable

    get_MusicProperties proc :ptr
    get_VideoProperties proc :ptr
    get_ImageProperties proc :ptr
    get_DocumentProperties proc :ptr
    get_BasicProperties proc :ptr
    get_Thumbnail       proc :ptr
    add_ThumbnailUpdated proc :ptr, :ptr
    remove_ThumbnailUpdated proc :EventRegistrationToken
    add_PropertiesUpdated proc :ptr, :ptr
    remove_PropertiesUpdated proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CBulkAccess_CIFileInformationFactoryFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CBulkAccess_CIFileInformationFactoryFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_BulkAccess_IFileInformationFactoryFactory <L"Windows.Storage.BulkAccess.IFileInformationFactoryFactory">
DEFINE_IIDX(IFileInformationFactoryFactory, "84EA0E7D-E4A2-4F00-8AFA-AF5E0F826BD5")

.comdef IFileInformationFactoryFactory : public IInspectable

    CreateWithMode      proc :ptr, :Windows::Storage::FileProperties::ThumbnailMode, :ptr
    CreateWithModeAndSize proc :ptr, :Windows::Storage::FileProperties::ThumbnailMode, :UINT32, :ptr
    CreateWithModeAndSizeAndOptions proc :ptr, :Windows::Storage::FileProperties::ThumbnailMode, :UINT32, :Windows::Storage::FileProperties::ThumbnailOptions, :ptr
    CreateWithModeAndSizeAndOptionsAndFlags proc :ptr, :Windows::Storage::FileProperties::ThumbnailMode, :UINT32, :Windows::Storage::FileProperties::ThumbnailOptions, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CBulkAccess_CIFileInformationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CBulkAccess_CIFileInformationFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_BulkAccess_IFileInformationFactory <L"Windows.Storage.BulkAccess.IFileInformationFactory">
DEFINE_IIDX(IFileInformationFactory, "401D88BE-960F-4D6D-A7D0-1A3861E76C83")

.comdef IFileInformationFactory : public IInspectable

    GetItemsAsync       proc :UINT32, :UINT32, :ptr
    GetItemsAsyncDefaultStartAndCount proc :ptr
    GetFilesAsync       proc :UINT32, :UINT32, :ptr
    GetFilesAsyncDefaultStartAndCount proc :ptr
    GetFoldersAsync     proc :UINT32, :UINT32, :ptr
    GetFoldersAsyncDefaultStartAndCount proc :ptr
    GetVirtualizedItemsVector proc :ptr
    GetVirtualizedFilesVector proc :ptr
    GetVirtualizedFoldersVector proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Storage_BulkAccess_FileInformationFactory_DEFINED
define RUNTIMECLASS_Windows_Storage_BulkAccess_FileInformationFactory_DEFINED
define RuntimeClass_Windows_Storage_BulkAccess_FileInformationFactory <L"Windows.Storage.BulkAccess.FileInformationFactory">
endif
ifndef RUNTIMECLASS_Windows_Storage_BulkAccess_FileInformation_DEFINED
define RUNTIMECLASS_Windows_Storage_BulkAccess_FileInformation_DEFINED
define RuntimeClass_Windows_Storage_BulkAccess_FileInformation <L"Windows.Storage.BulkAccess.FileInformation">
endif
ifndef RUNTIMECLASS_Windows_Storage_BulkAccess_FolderInformation_DEFINED
define RUNTIMECLASS_Windows_Storage_BulkAccess_FolderInformation_DEFINED
define RuntimeClass_Windows_Storage_BulkAccess_FolderInformation <L"Windows.Storage.BulkAccess.FolderInformation">
endif

endif
