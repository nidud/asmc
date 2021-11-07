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

ifndef __windows2Emedia2Econtentrestrictions_h__
define __windows2Emedia2Econtentrestrictions_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel, "cf61be5d-40c3-5484-846a-3f82b8ba5738")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel, "860c0179-be01-546d-a9ce-5956464c98ab")

.comdef __FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentAccessRestrictionLevel : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy, "72ae1a16-c705-54e7-b1c4-fc05a0e07a77")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy, "ae3399b2-c7d5-5f1b-9fb9-f8bd81e9f9be")

.comdef __FIAsyncOperation_1_Windows__CMedia__CContentRestrictions__CContentRestrictionsBrowsePolicy : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace ContentRestrictions

.enum RatedContentCategory {
    RatedContentCategory_General	= 0,
    RatedContentCategory_Application	= 1,
    RatedContentCategory_Game	= 2,
    RatedContentCategory_Movie	= 3,
    RatedContentCategory_Television	= 4,
    RatedContentCategory_Music	= 5
    }

.enum ContentAccessRestrictionLevel {
    ContentAccessRestrictionLevel_Allow = 0,
    ContentAccessRestrictionLevel_Warn	= 1,
    ContentAccessRestrictionLevel_Block = 2,
    ContentAccessRestrictionLevel_Hide	= 3
    }

ifndef ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentDescription_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentDescription_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ContentRestrictions_IRatedContentDescription <L"Windows.Media.ContentRestrictions.IRatedContentDescription">
DEFINE_IIDX(IRatedContentDescription, "694866DF-66B2-4DC3-96B1-F090EEDEE255")

.comdef IRatedContentDescription : public IInspectable

    get_Id		proc :ptr
    put_Id		proc :HSTRING
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_Image		proc :ptr
    put_Image		proc :ptr
    get_Category	proc :ptr
    put_Category	proc :Windows::Media::ContentRestrictions::RatedContentCategory
    get_Ratings		proc :ptr
    put_Ratings		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentDescriptionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentDescriptionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ContentRestrictions_IRatedContentDescriptionFactory <L"Windows.Media.ContentRestrictions.IRatedContentDescriptionFactory">
DEFINE_IIDX(IRatedContentDescriptionFactory, "2E38DF62-9B90-4FA6-89C1-4B8D2FFB3573")

.comdef IRatedContentDescriptionFactory : public IInspectable

    Create		proc :HSTRING, :HSTRING, :Windows::Media::ContentRestrictions::RatedContentCategory, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CContentRestrictions_CIContentRestrictionsBrowsePolicy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CContentRestrictions_CIContentRestrictionsBrowsePolicy_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ContentRestrictions_IContentRestrictionsBrowsePolicy <L"Windows.Media.ContentRestrictions.IContentRestrictionsBrowsePolicy">
DEFINE_IIDX(IContentRestrictionsBrowsePolicy, "8C0133A4-442E-461A-8757-FAD2F5BD37E4")

.comdef IContentRestrictionsBrowsePolicy : public IInspectable

    get_GeographicRegion proc :ptr
    get_MaxBrowsableAgeRating proc :ptr
    get_PreferredAgeRating proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentRestrictions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentRestrictions_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ContentRestrictions_IRatedContentRestrictions <L"Windows.Media.ContentRestrictions.IRatedContentRestrictions">
DEFINE_IIDX(IRatedContentRestrictions, "3F7F23CB-BA07-4401-A49D-8B9222205723")

.comdef IRatedContentRestrictions : public IInspectable

    GetBrowsePolicyAsync proc :ptr
    GetRestrictionLevelAsync proc :ptr, :ptr
    RequestContentAccessAsync proc :ptr, :ptr
    add_RestrictionsChanged proc :ptr, :ptr
    remove_RestrictionsChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentRestrictionsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CContentRestrictions_CIRatedContentRestrictionsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_ContentRestrictions_IRatedContentRestrictionsFactory <L"Windows.Media.ContentRestrictions.IRatedContentRestrictionsFactory">
DEFINE_IIDX(IRatedContentRestrictionsFactory, "FB4B2996-C3BD-4910-9619-97CFD0694D56")

.comdef IRatedContentRestrictionsFactory : public IInspectable

    CreateWithMaxAgeRating proc :UINT32, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_ContentRestrictions_RatedContentDescription_DEFINED
define RUNTIMECLASS_Windows_Media_ContentRestrictions_RatedContentDescription_DEFINED
define RuntimeClass_Windows_Media_ContentRestrictions_RatedContentDescription <L"Windows.Media.ContentRestrictions.RatedContentDescription">
endif
ifndef RUNTIMECLASS_Windows_Media_ContentRestrictions_ContentRestrictionsBrowsePolicy_DEFINED
define RUNTIMECLASS_Windows_Media_ContentRestrictions_ContentRestrictionsBrowsePolicy_DEFINED
define RuntimeClass_Windows_Media_ContentRestrictions_ContentRestrictionsBrowsePolicy <L"Windows.Media.ContentRestrictions.ContentRestrictionsBrowsePolicy">
endif
ifndef RUNTIMECLASS_Windows_Media_ContentRestrictions_RatedContentRestrictions_DEFINED
define RUNTIMECLASS_Windows_Media_ContentRestrictions_RatedContentRestrictions_DEFINED
define RuntimeClass_Windows_Media_ContentRestrictions_RatedContentRestrictions <L"Windows.Media.ContentRestrictions.RatedContentRestrictions">
endif

endif
