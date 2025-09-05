ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esystem2Euserprofile_h__
define __windows2Esystem2Euserprofile_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Globalization.inc
include Windows.Storage.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult, "603f3e31-7a51-518c-9280-c188ea4213d8")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult, "6809e406-6d3b-5164-8f32-b845b0781405")

.comdef __FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetAccountPictureResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetImageFeedResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetImageFeedResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetImageFeedResult, "f214731a-1305-5b44-932c-af9a1e4d78c9")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSystem__CUserProfile__CSetImageFeedResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetImageFeedResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetImageFeedResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetImageFeedResult, "5361bfc9-0740-544a-9797-1ffe5e73c54e")

.comdef __FIAsyncOperation_1_Windows__CSystem__CUserProfile__CSetImageFeedResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace System
.namespace UserProfile

.enum AccountPictureKind {
    AccountPictureKind_SmallImage	= 0,
    AccountPictureKind_LargeImage	= 1,
    AccountPictureKind_Video	= 2
    }

.enum SetAccountPictureResult {
    SetAccountPictureResult_Success	= 0,
    SetAccountPictureResult_ChangeDisabled	= 1,
    SetAccountPictureResult_LargeOrDynamicError = 2,
    SetAccountPictureResult_VideoFrameSizeError = 3,
    SetAccountPictureResult_FileSizeError	= 4,
    SetAccountPictureResult_Failure	= 5
    }

.enum SetImageFeedResult {
    SetImageFeedResult_Success	= 0,
    SetImageFeedResult_ChangeDisabled	= 1,
    SetImageFeedResult_UserCanceled	= 2
    }

ifndef ____x_ABI_CWindows_CSystem_CUserProfile_CIAdvertisingManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CUserProfile_CIAdvertisingManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_UserProfile_IAdvertisingManagerStatics <L"Windows.System.UserProfile.IAdvertisingManagerStatics">
DEFINE_IIDX(IAdvertisingManagerStatics, "ADD3468C-A273-48CB-B346-3544522D5581")

.comdef IAdvertisingManagerStatics : public IInspectable

    get_AdvertisingId	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CUserProfile_CIUserInformationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CUserProfile_CIUserInformationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_UserProfile_IUserInformationStatics <L"Windows.System.UserProfile.IUserInformationStatics">
DEFINE_IIDX(IUserInformationStatics, "77F3A910-48FA-489C-934E-2AE85BA8F772")

.comdef IUserInformationStatics : public IInspectable

    get_AccountPictureChangeEnabled proc :ptr
    get_NameAccessAllowed proc :ptr
    GetAccountPicture	proc :Windows::System::UserProfile::AccountPictureKind, :ptr
    SetAccountPictureAsync proc :ptr, :ptr
    SetAccountPicturesAsync proc :ptr, :ptr, :ptr, :ptr
    SetAccountPictureFromStreamAsync proc :ptr, :ptr
    SetAccountPicturesFromStreamsAsync proc :ptr, :ptr, :ptr, :ptr
    add_AccountPictureChanged proc :ptr, :ptr
    remove_AccountPictureChanged proc :EventRegistrationToken
    GetDisplayNameAsync proc :ptr
    GetFirstNameAsync	proc :ptr
    GetLastNameAsync	proc :ptr
    GetPrincipalNameAsync proc :ptr
    GetSessionInitiationProtocolUriAsync proc :ptr
    GetDomainNameAsync	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CUserProfile_CILockScreenStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CUserProfile_CILockScreenStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_UserProfile_ILockScreenStatics <L"Windows.System.UserProfile.ILockScreenStatics">
DEFINE_IIDX(ILockScreenStatics, "3EE9D3AD-B607-40AE-B426-7631D9821269")

.comdef ILockScreenStatics : public IInspectable

    get_OriginalImageFile proc :ptr
    GetImageStream	proc :ptr
    SetImageFileAsync	proc :ptr, :ptr
    SetImageStreamAsync proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CUserProfile_CILockScreenImageFeedStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CUserProfile_CILockScreenImageFeedStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_UserProfile_ILockScreenImageFeedStatics <L"Windows.System.UserProfile.ILockScreenImageFeedStatics">
DEFINE_IIDX(ILockScreenImageFeedStatics, "2C0D73F6-03A9-41A6-9B01-495251FF51D5")

.comdef ILockScreenImageFeedStatics : public IInspectable

    RequestSetImageFeedAsync proc :ptr, :ptr
    TryRemoveImageFeed	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CUserProfile_CIGlobalizationPreferencesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CUserProfile_CIGlobalizationPreferencesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_UserProfile_IGlobalizationPreferencesStatics <L"Windows.System.UserProfile.IGlobalizationPreferencesStatics">
DEFINE_IIDX(IGlobalizationPreferencesStatics, "01BF4326-ED37-4E96-B0E9-C1340D1EA158")

.comdef IGlobalizationPreferencesStatics : public IInspectable

    get_Calendars	proc :ptr
    get_Clocks		proc :ptr
    get_Currencies	proc :ptr
    get_Languages	proc :ptr
    get_HomeGeographicRegion proc :ptr
    get_WeekStartsOn	proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_System_UserProfile_AdvertisingManager_DEFINED
define RUNTIMECLASS_Windows_System_UserProfile_AdvertisingManager_DEFINED
define RuntimeClass_Windows_System_UserProfile_AdvertisingManager <L"Windows.System.UserProfile.AdvertisingManager">
endif
ifndef RUNTIMECLASS_Windows_System_UserProfile_UserInformation_DEFINED
define RUNTIMECLASS_Windows_System_UserProfile_UserInformation_DEFINED
define RuntimeClass_Windows_System_UserProfile_UserInformation <L"Windows.System.UserProfile.UserInformation">
endif
ifndef RUNTIMECLASS_Windows_System_UserProfile_LockScreen_DEFINED
define RUNTIMECLASS_Windows_System_UserProfile_LockScreen_DEFINED
define RuntimeClass_Windows_System_UserProfile_LockScreen <L"Windows.System.UserProfile.LockScreen">
endif
ifndef RUNTIMECLASS_Windows_System_UserProfile_GlobalizationPreferences_DEFINED
define RUNTIMECLASS_Windows_System_UserProfile_GlobalizationPreferences_DEFINED
define RuntimeClass_Windows_System_UserProfile_GlobalizationPreferences <L"Windows.System.UserProfile.GlobalizationPreferences">
endif

endif
