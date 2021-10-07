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

ifndef __windows2Estorage2Esearch_h__
define __windows2Estorage2Esearch_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Data.Text.inc
include Windows.Storage.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CSearch__CIIndexableContent, "6cdb32ba-2361-57a8-a39d-be1df041bdb8")

.comdef __FIIterator_1_Windows__CStorage__CSearch__CIIndexableContent : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CSearch__CIIndexableContent, "4a6edbfe-0c41-5042-ac58-a885a8fc7928")

.comdef __FIIterable_1_Windows__CStorage__CSearch__CIIndexableContent : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CStorage__CSearch__CSortEntry, "520434a2-acf7-58c9-b47a-2741f2fac2c2")

.comdef __FIIterator_1_Windows__CStorage__CSearch__CSortEntry : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CStorage__CSearch__CSortEntry, "35aff6f9-ef75-5280-bb84-a2bf8317cf35")

.comdef __FIIterable_1_Windows__CStorage__CSearch__CSortEntry : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent, "f4512416-6bb8-5c6f-b83a-bf8a2788ce9f")

.comdef __FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CStorage__CSearch__CSortEntry, "823c7604-b37b-5465-a169-29497893cdb9")

.comdef __FIVectorView_1_Windows__CStorage__CSearch__CSortEntry : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVector_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CStorage__CSearch__CSortEntry_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CStorage__CSearch__CSortEntry, "d8ea401b-47b3-5254-84f4-eea10c4cf068")

.comdef __FIVector_1_Windows__CStorage__CSearch__CSortEntry : public IInspectable

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

ifndef ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent, "6a29f493-efb7-5fdb-a13e-f2c28b4dab58")

.comdef __FIAsyncOperationCompletedHandler_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__
define ____FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent, "919850e1-084b-5f9b-a0a0-50db0cd5da91")

.comdef __FIAsyncOperation_1___FIVectorView_1_Windows__CStorage__CSearch__CIIndexableContent : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CSearch__CIndexedState_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CStorage__CSearch__CIndexedState_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CStorage__CSearch__CIndexedState, "b67a3cba-f5f7-5e51-968a-385126d1f918")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CStorage__CSearch__CIndexedState : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CStorage__CSearch__CIndexedState_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CStorage__CSearch__CIndexedState_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CStorage__CSearch__CIndexedState, "88694b1f-f380-574d-8a05-4f67bd52cd11")

.comdef __FIAsyncOperation_1_Windows__CStorage__CSearch__CIndexedState : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :LONG
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CStorage__CSearch__CIStorageQueryResultBase_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CStorage__CSearch__CIStorageQueryResultBase_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CStorage__CSearch__CIStorageQueryResultBase_IInspectable, "4ba22861-00c4-597f-b6bf-3af516f3b870")

.comdef __FITypedEventHandler_2_Windows__CStorage__CSearch__CIStorageQueryResultBase_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace ABI
.namespace Windows
.namespace Storage
.namespace Search

.enum DateStackOption {
    DateStackOption_None,
    DateStackOption_Year,
    DateStackOption_Month
    }

.enum IndexerOption {
    IndexerOption_UseIndexerWhenAvailable,
    IndexerOption_OnlyUseIndexer,
    IndexerOption_DoNotUseIndexer
    }

.enum FolderDepth {
    FolderDepth_Shallow,
    FolderDepth_Deep
    }

.enum CommonFileQuery {
    CommonFileQuery_DefaultQuery,
    CommonFileQuery_OrderByName,
    CommonFileQuery_OrderByTitle,
    CommonFileQuery_OrderByMusicProperties,
    CommonFileQuery_OrderBySearchRank,
    CommonFileQuery_OrderByDate
    }

.enum CommonFolderQuery {
    CommonFolderQuery_DefaultQuery	= 0,
    CommonFolderQuery_GroupByYear	= 100,
    CommonFolderQuery_GroupByMonth	= 101,
    CommonFolderQuery_GroupByArtist	= 102,
    CommonFolderQuery_GroupByAlbum	= 103,
    CommonFolderQuery_GroupByAlbumArtist	= 104,
    CommonFolderQuery_GroupByComposer	= 105,
    CommonFolderQuery_GroupByGenre	= 106,
    CommonFolderQuery_GroupByPublishedYear	= 107,
    CommonFolderQuery_GroupByRating	= 108,
    CommonFolderQuery_GroupByTag	= 109,
    CommonFolderQuery_GroupByAuthor	= 110,
    CommonFolderQuery_GroupByType	= 111
    }

.enum IndexedState {
    IndexedState_Unknown,
    IndexedState_NotIndexed,
    IndexedState_PartiallyIndexed,
    IndexedState_FullyIndexed
    }

.template SortEntry
    PropertyName	HSTRING ?
    AscendingOrder	boolean ?
   .ends


ifndef ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexerStatics_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IContentIndexerStatics, "8C488375-B37E-4C60-9BA8-B760FDA3E59D")

.comdef IContentIndexerStatics : public IInspectable

    GetIndexerWithName	proc :HSTRING, :ptr
    GetIndexer		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIIndexableContent_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIIndexableContent_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IIndexableContent, "CCF1A05F-D4B5-483A-B06E-E0DB1EC420E4")

.comdef IIndexableContent : public IInspectable

    get_Id		proc :ptr
    put_Id		proc :HSTRING
    get_Properties	proc :ptr
    get_Stream		proc :ptr
    put_Stream		proc :ptr
    get_StreamContentType proc :ptr
    put_StreamContentType proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexer_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IContentIndexer, "B1767F8D-F698-4982-B05F-3A6E8CAB01A2")

.comdef IContentIndexer : public IInspectable

    AddAsync		proc :ptr, :ptr
    UpdateAsync		proc :ptr, :ptr
    DeleteAsync		proc :HSTRING, :ptr
    DeleteMultipleAsync proc :ptr, :ptr
    DeleteAllAsync	proc :ptr
    RetrievePropertiesAsync proc :HSTRING, :ptr, :ptr
    get_Revision	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIValueAndLanguage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIValueAndLanguage_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IValueAndLanguage, "B9914881-A1EE-4BC4-92A5-466968E30436")

.comdef IValueAndLanguage : public IInspectable

    get_Language	proc :ptr
    put_Language	proc :HSTRING
    get_Value		proc :ptr
    put_Value		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexerQueryOperations_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexerQueryOperations_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IContentIndexerQueryOperations, "28823E10-4786-42F1-9730-792B3566B150")

.comdef IContentIndexerQueryOperations : public IInspectable

    CreateQueryWithSortOrderAndLanguage proc :HSTRING, :ptr, :ptr, :HSTRING, :ptr
    CreateQueryWithSortOrder proc :HSTRING, :ptr, :ptr, :ptr
    CreateQuery		proc :HSTRING, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexerQuery_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIContentIndexerQuery_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IContentIndexerQuery, "70E3B0F8-4BFC-428A-8889-CC51DA9A7B9D")

.comdef IContentIndexerQuery : public IInspectable

    GetCountAsync	proc :ptr
    GetPropertiesAsync	proc :ptr
    GetPropertiesRangeAsync proc :UINT32, :UINT32, :ptr
    GetAsync		proc :ptr
    GetRangeAsync	proc :UINT32, :UINT32, :ptr
    get_QueryFolder	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIQueryOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIQueryOptions_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IQueryOptions, "1E5E46EE-0F45-4838-A8E9-D0479D446C30")

.comdef IQueryOptions : public IInspectable

    get_FileTypeFilter	proc :ptr
    get_FolderDepth	proc :ptr
    put_FolderDepth	proc :ABI_Windows_Storage_Search_FolderDepth
    get_ApplicationSearchFilter proc :ptr
    put_ApplicationSearchFilter proc :HSTRING
    get_UserSearchFilter proc :ptr
    put_UserSearchFilter proc :HSTRING
    get_Language	proc :ptr
    put_Language	proc :HSTRING
    get_IndexerOption	proc :ptr
    put_IndexerOption	proc :ABI_Windows_Storage_Search_IndexerOption
    get_SortOrder	proc :ptr
    get_GroupPropertyName proc :ptr
    get_DateStackOption proc :ptr
    SaveToString	proc :ptr
    LoadFromString	proc :HSTRING
    SetThumbnailPrefetch proc :ptr, :UINT32, :ptr
    SetPropertyPrefetch proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIQueryOptionsWithProviderFilter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIQueryOptionsWithProviderFilter_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IQueryOptionsWithProviderFilter, "5B9D1026-15C4-44DD-B89A-47A59B7D7C4F")

.comdef IQueryOptionsWithProviderFilter : public IInspectable

    get_StorageProviderIdFilter proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIQueryOptionsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIQueryOptionsFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IQueryOptionsFactory, "032E1F8C-A9C1-4E71-8011-0DEE9D4811A3")

.comdef IQueryOptionsFactory : public IInspectable

    CreateCommonFileQuery proc :ABI_Windows_Storage_Search_CommonFileQuery, :ptr, :ptr
    CreateCommonFolderQuery proc :ABI_Windows_Storage_Search_CommonFolderQuery, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIStorageQueryResultBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIStorageQueryResultBase_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IStorageQueryResultBase, "C297D70D-7353-47AB-BA58-8C61425DC54B")

.comdef IStorageQueryResultBase : public IInspectable

    GetItemCountAsync	proc :ptr
    get_Folder		proc :ptr
    add_ContentsChanged proc :ptr, :ptr
    remove_ContentsChanged proc :EventRegistrationToken
    add_OptionsChanged	proc :ptr, :ptr
    remove_OptionsChanged proc :EventRegistrationToken
    FindStartIndexAsync proc :ptr, :ptr
    GetCurrentQueryOptions proc :ptr
    ApplyNewQueryOptions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIStorageFileQueryResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIStorageFileQueryResult_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IStorageFileQueryResult, "52FDA447-2BAA-412C-B29F-D4B1778EFA1E")

.comdef IStorageFileQueryResult : public IInspectable

    GetFilesAsync	proc :UINT32, :UINT32, :ptr
    GetFilesAsyncDefaultStartAndCount proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIStorageFileQueryResult2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIStorageFileQueryResult2_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IStorageFileQueryResult2, "4E5DB9DD-7141-46C4-8BE3-E9DC9E27275C")

.comdef IStorageFileQueryResult2 : public IInspectable

    GetMatchingPropertiesWithRanges proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIStorageFolderQueryResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIStorageFolderQueryResult_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IStorageFolderQueryResult, "6654C911-7D66-46FA-AECF-E4A4BAA93AB8")

.comdef IStorageFolderQueryResult : public IInspectable

    GetFoldersAsync	proc :UINT32, :UINT32, :ptr
    GetFoldersAsyncDefaultStartAndCount proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIStorageItemQueryResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIStorageItemQueryResult_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IStorageItemQueryResult, "E8948079-9D58-47B8-B2B2-41B07F4795F9")

.comdef IStorageItemQueryResult : public IInspectable

    GetItemsAsync	proc :UINT32, :UINT32, :ptr
    GetItemsAsyncDefaultStartAndCount proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CStorage_CSearch_CIStorageFolderQueryOperations_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CStorage_CSearch_CIStorageFolderQueryOperations_INTERFACE_DEFINED__

DEFINE_IIDX(ABI_Windows_Storage_Search_IStorageFolderQueryOperations, "CB43CCC9-446B-4A4F-BE97-757771BE5203")

.comdef IStorageFolderQueryOperations : public IInspectable

    GetIndexedStateAsync proc :ptr
    CreateFileQueryOverloadDefault proc :ptr
    CreateFileQuery	proc :ABI_Windows_Storage_Search_CommonFileQuery, :ptr
    CreateFileQueryWithOptions proc :ptr, :ptr
    CreateFolderQueryOverloadDefault proc :ptr
    CreateFolderQuery	proc :ABI_Windows_Storage_Search_CommonFolderQuery, :ptr
    CreateFolderQueryWithOptions proc :ptr, :ptr
    CreateItemQuery	proc :ptr
    CreateItemQueryWithOptions proc :ptr, :ptr
    GetFilesAsync	proc :ABI_Windows_Storage_Search_CommonFileQuery, :UINT32, :UINT32, :ptr
    GetFilesAsyncOverloadDefaultStartAndCount proc :ABI_Windows_Storage_Search_CommonFileQuery, :ptr
    GetFoldersAsync	proc :ABI_Windows_Storage_Search_CommonFolderQuery, :UINT32, :UINT32, :ptr
    GetFoldersAsyncOverloadDefaultStartAndCount proc :ABI_Windows_Storage_Search_CommonFolderQuery, :ptr
    GetItemsAsync	proc :UINT32, :UINT32, :ptr
    AreQueryOptionsSupported proc :ptr, :ptr
    IsCommonFolderQuerySupported proc :ABI_Windows_Storage_Search_CommonFolderQuery, :ptr
    IsCommonFileQuerySupported proc :ABI_Windows_Storage_Search_CommonFileQuery, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

HSTRING_UserSize	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr ULONG, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr ULONG, :ptr HSTRING

endif
