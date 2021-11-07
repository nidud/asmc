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

ifndef __windows2Estorage2Eaccesscache_h__
define __windows2Estorage2Eaccesscache_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace Storage
.namespace AccessCache

.enum AccessCacheOptions {
    AccessCacheOptions_None	= 0,
    AccessCacheOptions_DisallowUserInput	= 0x1,
    AccessCacheOptions_FastLocationsOnly	= 0x2,
    AccessCacheOptions_UseReadOnlyCachedCopy	= 0x4,
    AccessCacheOptions_SuppressAccessTimeUpdate = 0x8
    }

.template AccessListEntry
    Token		HSTRING ?
    Metadata		HSTRING ?
   .ends

.endn
.endn
.endn

ifndef ____FIIterator_1_Windows__CStorage__CAccessCache__CAccessListEntry_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CAccessCache__CAccessListEntry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CAccessCache__CAccessListEntry, "d1a0a6c4-889d-519b-8508-26241b329b7e")

.comdef __FIIterator_1_Windows__CStorage__CAccessCache__CAccessListEntry : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CAccessCache__CAccessListEntry_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CAccessCache__CAccessListEntry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CAccessCache__CAccessListEntry, "4995c2b0-736b-588d-ae42-6f69b025b388")

.comdef __FIIterable_1_Windows__CStorage__CAccessCache__CAccessListEntry : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CAccessCache__CAccessListEntry_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CAccessCache__CAccessListEntry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CAccessCache__CAccessListEntry, "42b49b8a-3014-5d27-8f2c-1ef5ee89ec00")

.comdef __FIVectorView_1_Windows__CStorage__CAccessCache__CAccessListEntry : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :Windows::Storage::AccessCache::AccessListEntry, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CAccessCache__CStorageItemMostRecentlyUsedList_Windows__CStorage__CAccessCache__CItemRemovedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CAccessCache__CStorageItemMostRecentlyUsedList_Windows__CStorage__CAccessCache__CItemRemovedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CAccessCache__CStorageItemMostRecentlyUsedList_Windows__CStorage__CAccessCache__CItemRemovedEventArgs, "029dace8-98d1-5bf7-b780-9717e95027ff")

.comdef __FITypedEventHandler_2_Windows__CStorage__CAccessCache__CStorageItemMostRecentlyUsedList_Windows__CStorage__CAccessCache__CItemRemovedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Storage
.namespace AccessCache

ifndef ____x_ABI_CWindows_CStorage_CAccessCache_CIItemRemovedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CAccessCache_CIItemRemovedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_AccessCache_IItemRemovedEventArgs <L"Windows.Storage.AccessCache.IItemRemovedEventArgs">
DEFINE_IIDX(IItemRemovedEventArgs, "59677E5C-55BE-4C66-BA66-5EAEA79D2631")

.comdef IItemRemovedEventArgs : public IInspectable

    get_RemovedEntry	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CAccessCache_CIStorageItemAccessList_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CAccessCache_CIStorageItemAccessList_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_AccessCache_IStorageItemAccessList <L"Windows.Storage.AccessCache.IStorageItemAccessList">
DEFINE_IIDX(IStorageItemAccessList, "2CAFF6AD-DE90-47F5-B2C3-DD36C9FDD453")

.comdef IStorageItemAccessList : public IInspectable

    AddOverloadDefaultMetadata proc :ptr, :ptr
    _Add		proc :ptr, :HSTRING, :ptr
    AddOrReplaceOverloadDefaultMetadata proc :HSTRING, :ptr
    AddOrReplace	proc :HSTRING, :ptr, :HSTRING
    GetItemAsync	proc :HSTRING, :ptr
    GetFileAsync	proc :HSTRING, :ptr
    GetFolderAsync	proc :HSTRING, :ptr
    GetItemWithOptionsAsync proc :HSTRING, :Windows::Storage::AccessCache::AccessCacheOptions, :ptr
    GetFileWithOptionsAsync proc :HSTRING, :Windows::Storage::AccessCache::AccessCacheOptions, :ptr
    GetFolderWithOptionsAsync proc :HSTRING, :Windows::Storage::AccessCache::AccessCacheOptions, :ptr
    Remove		proc :HSTRING
    ContainsItem	proc :HSTRING, :ptr
    Clear		proc
    CheckAccess		proc :ptr, :ptr
    get_Entries		proc :ptr
    get_MaximumItemsAllowed proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CAccessCache_CIStorageItemMostRecentlyUsedList_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CAccessCache_CIStorageItemMostRecentlyUsedList_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_AccessCache_IStorageItemMostRecentlyUsedList <L"Windows.Storage.AccessCache.IStorageItemMostRecentlyUsedList">
DEFINE_IIDX(IStorageItemMostRecentlyUsedList, "016239D5-510D-411E-8CF1-C3D1EFFA4C33")

.comdef IStorageItemMostRecentlyUsedList : public IInspectable

    add_ItemRemoved	proc :ptr, :ptr
    remove_ItemRemoved	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CAccessCache_CIStorageApplicationPermissionsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CAccessCache_CIStorageApplicationPermissionsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Storage_AccessCache_IStorageApplicationPermissionsStatics <L"Windows.Storage.AccessCache.IStorageApplicationPermissionsStatics">
DEFINE_IIDX(IStorageApplicationPermissionsStatics, "4391DFAA-D033-48F9-8060-3EC847D2E3F1")

.comdef IStorageApplicationPermissionsStatics : public IInspectable

    get_FutureAccessList proc :ptr
    get_MostRecentlyUsedList proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Storage_AccessCache_AccessListEntryView_DEFINED
define RUNTIMECLASS_Windows_Storage_AccessCache_AccessListEntryView_DEFINED
define RuntimeClass_Windows_Storage_AccessCache_AccessListEntryView <L"Windows.Storage.AccessCache.AccessListEntryView">
endif
ifndef RUNTIMECLASS_Windows_Storage_AccessCache_StorageItemMostRecentlyUsedList_DEFINED
define RUNTIMECLASS_Windows_Storage_AccessCache_StorageItemMostRecentlyUsedList_DEFINED
define RuntimeClass_Windows_Storage_AccessCache_StorageItemMostRecentlyUsedList <L"Windows.Storage.AccessCache.StorageItemMostRecentlyUsedList">
endif
ifndef RUNTIMECLASS_Windows_Storage_AccessCache_ItemRemovedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Storage_AccessCache_ItemRemovedEventArgs_DEFINED
define RuntimeClass_Windows_Storage_AccessCache_ItemRemovedEventArgs <L"Windows.Storage.AccessCache.ItemRemovedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Storage_AccessCache_StorageItemAccessList_DEFINED
define RUNTIMECLASS_Windows_Storage_AccessCache_StorageItemAccessList_DEFINED
define RuntimeClass_Windows_Storage_AccessCache_StorageItemAccessList <L"Windows.Storage.AccessCache.StorageItemAccessList">
endif
ifndef RUNTIMECLASS_Windows_Storage_AccessCache_StorageApplicationPermissions_DEFINED
define RUNTIMECLASS_Windows_Storage_AccessCache_StorageApplicationPermissions_DEFINED
define RuntimeClass_Windows_Storage_AccessCache_StorageApplicationPermissions <L"Windows.Storage.AccessCache.StorageApplicationPermissions">
endif

endif
