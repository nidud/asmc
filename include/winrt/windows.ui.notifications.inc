ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Enotifications_h__
define __windows2Eui2Enotifications_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Data.Xml.Dom.inc

ifndef ____FIIterator_1_Windows__CUI__CNotifications__CScheduledTileNotification_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CNotifications__CScheduledTileNotification_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CUI__CNotifications__CScheduledTileNotification, "5665e491-6543-5036-935f-b5157950b359")

.comdef __FIIterator_1_Windows__CUI__CNotifications__CScheduledTileNotification : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CNotifications__CScheduledTileNotification_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CNotifications__CScheduledTileNotification_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CUI__CNotifications__CScheduledTileNotification, "4b60d1e5-52ae-5766-9720-be4ad086f952")

.comdef __FIIterable_1_Windows__CUI__CNotifications__CScheduledTileNotification : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CNotifications__CScheduledToastNotification_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CNotifications__CScheduledToastNotification_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CUI__CNotifications__CScheduledToastNotification, "304238b6-888a-5dd2-96cd-bfca8927483b")

.comdef __FIIterator_1_Windows__CUI__CNotifications__CScheduledToastNotification : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CNotifications__CScheduledToastNotification_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CNotifications__CScheduledToastNotification_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CUI__CNotifications__CScheduledToastNotification, "7a7b2a51-c182-5846-a861-4f9c036f24ad")

.comdef __FIIterable_1_Windows__CUI__CNotifications__CScheduledToastNotification : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CNotifications__CScheduledTileNotification_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CNotifications__CScheduledTileNotification_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CNotifications__CScheduledTileNotification, "4f729c64-a213-52e9-af8b-58adca3e597f")

.comdef __FIVectorView_1_Windows__CUI__CNotifications__CScheduledTileNotification : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CNotifications__CScheduledToastNotification_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CNotifications__CScheduledToastNotification_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CNotifications__CScheduledToastNotification, "ba0aff1f-6a8a-5a7e-a9f7-505b6266a436")

.comdef __FIVectorView_1_Windows__CUI__CNotifications__CScheduledToastNotification : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_IInspectable, "ab54de2d-97d9-5528-b6ad-105afe156530")

.comdef __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_IInspectable : public IUnknown

    IInvoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastDismissedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastDismissedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastDismissedEventArgs, "61c2402f-0ed0-5a18-ab69-59f4aa99a368")

.comdef __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastDismissedEventArgs : public IUnknown

    IInvoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastFailedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastFailedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastFailedEventArgs, "95e3e803-c969-5e3a-9753-ea2ad22a9a33")

.comdef __FITypedEventHandler_2_Windows__CUI__CNotifications__CToastNotification_Windows__CUI__CNotifications__CToastFailedEventArgs : public IUnknown

    IInvoke		proc :ptr, :ptr
    .ends

endif

.namespace Windows
.namespace UI
.namespace Notifications

.enum NotificationSetting {
    NotificationSetting_Enabled,
    NotificationSetting_DisabledForApplication,
    NotificationSetting_DisabledForUser,
    NotificationSetting_DisabledByGroupPolicy,
    NotificationSetting_DisabledByManifest
    }

.enum ToastDismissalReason {
    ToastDismissalReason_UserCanceled,
    ToastDismissalReason_ApplicationHidden,
    ToastDismissalReason_TimedOut
    }

.enum BadgeTemplateType {
    BadgeTemplateType_BadgeGlyph,
    BadgeTemplateType_BadgeNumber
    }


.enum TileTemplateType {
    TileTemplateType_TileSquareImage	= 0,
    TileTemplateType_TileSquareBlock	= 1,
    TileTemplateType_TileSquareText01	= 2,
    TileTemplateType_TileSquareText02	= 3,
    TileTemplateType_TileSquareText03	= 4,
    TileTemplateType_TileSquareText04	= 5,
    TileTemplateType_TileSquarePeekImageAndText01	= 6,
    TileTemplateType_TileSquarePeekImageAndText02	= 7,
    TileTemplateType_TileSquarePeekImageAndText03	= 8,
    TileTemplateType_TileSquarePeekImageAndText04	= 9,
    TileTemplateType_TileWideImage	= 10,
    TileTemplateType_TileWideImageCollection	= 11,
    TileTemplateType_TileWideImageAndText01	= 12,
    TileTemplateType_TileWideImageAndText02	= 13,
    TileTemplateType_TileWideBlockAndText01	= 14,
    TileTemplateType_TileWideBlockAndText02	= 15,
    TileTemplateType_TileWidePeekImageCollection01	= 16,
    TileTemplateType_TileWidePeekImageCollection02	= 17,
    TileTemplateType_TileWidePeekImageCollection03	= 18,
    TileTemplateType_TileWidePeekImageCollection04	= 19,
    TileTemplateType_TileWidePeekImageCollection05	= 20,
    TileTemplateType_TileWidePeekImageCollection06	= 21,
    TileTemplateType_TileWidePeekImageAndText01 = 22,
    TileTemplateType_TileWidePeekImageAndText02 = 23,
    TileTemplateType_TileWidePeekImage01	= 24,
    TileTemplateType_TileWidePeekImage02	= 25,
    TileTemplateType_TileWidePeekImage03	= 26,
    TileTemplateType_TileWidePeekImage04	= 27,
    TileTemplateType_TileWidePeekImage05	= 28,
    TileTemplateType_TileWidePeekImage06	= 29,
    TileTemplateType_TileWideSmallImageAndText01	= 30,
    TileTemplateType_TileWideSmallImageAndText02	= 31,
    TileTemplateType_TileWideSmallImageAndText03	= 32,
    TileTemplateType_TileWideSmallImageAndText04	= 33,
    TileTemplateType_TileWideSmallImageAndText05	= 34,
    TileTemplateType_TileWideText01	= 35,
    TileTemplateType_TileWideText02	= 36,
    TileTemplateType_TileWideText03	= 37,
    TileTemplateType_TileWideText04	= 38,
    TileTemplateType_TileWideText05	= 39,
    TileTemplateType_TileWideText06	= 40,
    TileTemplateType_TileWideText07	= 41,
    TileTemplateType_TileWideText08	= 42,
    TileTemplateType_TileWideText09	= 43,
    TileTemplateType_TileWideText10	= 44,
    TileTemplateType_TileWideText11	= 45,
    TileTemplateType_TileSquare150x150Image	= 0,
    TileTemplateType_TileSquare150x150Block	= 1,
    TileTemplateType_TileSquare150x150Text01	= 2,
    TileTemplateType_TileSquare150x150Text02	= 3,
    TileTemplateType_TileSquare150x150Text03	= 4,
    TileTemplateType_TileSquare150x150Text04	= 5,
    TileTemplateType_TileSquare150x150PeekImageAndText01	= 6,
    TileTemplateType_TileSquare150x150PeekImageAndText02	= 7,
    TileTemplateType_TileSquare150x150PeekImageAndText03	= 8,
    TileTemplateType_TileSquare150x150PeekImageAndText04	= 9,
    TileTemplateType_TileWide310x150Image	= 10,
    TileTemplateType_TileWide310x150ImageCollection	= 11,
    TileTemplateType_TileWide310x150ImageAndText01	= 12,
    TileTemplateType_TileWide310x150ImageAndText02	= 13,
    TileTemplateType_TileWide310x150BlockAndText01	= 14,
    TileTemplateType_TileWide310x150BlockAndText02	= 15,
    TileTemplateType_TileWide310x150PeekImageCollection01	= 16,
    TileTemplateType_TileWide310x150PeekImageCollection02	= 17,
    TileTemplateType_TileWide310x150PeekImageCollection03	= 18,
    TileTemplateType_TileWide310x150PeekImageCollection04	= 19,
    TileTemplateType_TileWide310x150PeekImageCollection05	= 20,
    TileTemplateType_TileWide310x150PeekImageCollection06	= 21,
    TileTemplateType_TileWide310x150PeekImageAndText01	= 22,
    TileTemplateType_TileWide310x150PeekImageAndText02	= 23,
    TileTemplateType_TileWide310x150PeekImage01 = 24,
    TileTemplateType_TileWide310x150PeekImage02 = 25,
    TileTemplateType_TileWide310x150PeekImage03 = 26,
    TileTemplateType_TileWide310x150PeekImage04 = 27,
    TileTemplateType_TileWide310x150PeekImage05 = 28,
    TileTemplateType_TileWide310x150PeekImage06 = 29,
    TileTemplateType_TileWide310x150SmallImageAndText01 = 30,
    TileTemplateType_TileWide310x150SmallImageAndText02 = 31,
    TileTemplateType_TileWide310x150SmallImageAndText03 = 32,
    TileTemplateType_TileWide310x150SmallImageAndText04 = 33,
    TileTemplateType_TileWide310x150SmallImageAndText05 = 34,
    TileTemplateType_TileWide310x150Text01	= 35,
    TileTemplateType_TileWide310x150Text02	= 36,
    TileTemplateType_TileWide310x150Text03	= 37,
    TileTemplateType_TileWide310x150Text04	= 38,
    TileTemplateType_TileWide310x150Text05	= 39,
    TileTemplateType_TileWide310x150Text06	= 40,
    TileTemplateType_TileWide310x150Text07	= 41,
    TileTemplateType_TileWide310x150Text08	= 42,
    TileTemplateType_TileWide310x150Text09	= 43,
    TileTemplateType_TileWide310x150Text10	= 44,
    TileTemplateType_TileWide310x150Text11	= 45,
    TileTemplateType_TileSquare310x310BlockAndText01	= 46,
    TileTemplateType_TileSquare310x310BlockAndText02	= 47,
    TileTemplateType_TileSquare310x310Image	= 48,
    TileTemplateType_TileSquare310x310ImageAndText01	= 49,
    TileTemplateType_TileSquare310x310ImageAndText02	= 50,
    TileTemplateType_TileSquare310x310ImageAndTextOverlay01	= 51,
    TileTemplateType_TileSquare310x310ImageAndTextOverlay02	= 52,
    TileTemplateType_TileSquare310x310ImageAndTextOverlay03	= 53,
    TileTemplateType_TileSquare310x310ImageCollectionAndText01	= 54,
    TileTemplateType_TileSquare310x310ImageCollectionAndText02	= 55,
    TileTemplateType_TileSquare310x310ImageCollection	= 56,
    TileTemplateType_TileSquare310x310SmallImagesAndTextList01	= 57,
    TileTemplateType_TileSquare310x310SmallImagesAndTextList02	= 58,
    TileTemplateType_TileSquare310x310SmallImagesAndTextList03	= 59,
    TileTemplateType_TileSquare310x310SmallImagesAndTextList04	= 60,
    TileTemplateType_TileSquare310x310Text01	= 61,
    TileTemplateType_TileSquare310x310Text02	= 62,
    TileTemplateType_TileSquare310x310Text03	= 63,
    TileTemplateType_TileSquare310x310Text04	= 64,
    TileTemplateType_TileSquare310x310Text05	= 65,
    TileTemplateType_TileSquare310x310Text06	= 66,
    TileTemplateType_TileSquare310x310Text07	= 67,
    TileTemplateType_TileSquare310x310Text08	= 68,
    TileTemplateType_TileSquare310x310TextList01	= 69,
    TileTemplateType_TileSquare310x310TextList02	= 70,
    TileTemplateType_TileSquare310x310TextList03	= 71,
    TileTemplateType_TileSquare310x310SmallImageAndText01	= 72,
    TileTemplateType_TileSquare310x310SmallImagesAndTextList05	= 73,
    TileTemplateType_TileSquare310x310Text09	= 74,
    TileTemplateType_TileSquare99x99IconWithBadge	= 1000,
    TileTemplateType_TileSquare210x210IconWithBadge	= 1001,
    TileTemplateType_TileWide432x210IconWithBadgeAndText	= 1002
    }

.enum ToastTemplateType {
    ToastTemplateType_ToastImageAndText01,
    ToastTemplateType_ToastImageAndText02,
    ToastTemplateType_ToastImageAndText03,
    ToastTemplateType_ToastImageAndText04,
    ToastTemplateType_ToastText01,
    ToastTemplateType_ToastText02,
    ToastTemplateType_ToastText03,
    ToastTemplateType_ToastText04
    }

.enum PeriodicUpdateRecurrence {
    PeriodicUpdateRecurrence_HalfHour,
    PeriodicUpdateRecurrence_Hour,
    PeriodicUpdateRecurrence_SixHours,
    PeriodicUpdateRecurrence_TwelveHours,
    PeriodicUpdateRecurrence_Daily
    }


ifndef ____x_ABI_CWindows_CUI_CNotifications_CIToastDismissedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIToastDismissedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(IToastDismissedEventArgs, "3F89D935-D9CB-4538-A0F0-FFE7659938F8")

.comdef IToastDismissedEventArgs : public IInspectable

    get_Reason		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIToastFailedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIToastFailedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(IToastFailedEventArgs, "35176862-CFD4-44F8-AD64-F500FD896C3B")

.comdef IToastFailedEventArgs : public IInspectable

    get_ErrorCode	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIToastActivatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIToastActivatedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(IToastActivatedEventArgs, "E3BF92F3-C197-436F-8265-0625824F8DAC")

.comdef IToastActivatedEventArgs : public IInspectable

    get_Arguments	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CITileUpdateManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CITileUpdateManagerStatics_INTERFACE_DEFINED__

DEFINE_IIDX(ITileUpdateManagerStatics, "DA159E5D-3EA9-4986-8D84-B09D5E12276D")

.comdef ITileUpdateManagerStatics : public IInspectable

    CreateTileUpdaterForApplication proc :ptr
    CreateTileUpdaterForApplicationWithId proc :HSTRING, :ptr
    CreateTileUpdaterForSecondaryTile proc :HSTRING, :ptr
    GetTemplateContent	proc :LONG, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CITileUpdater_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CITileUpdater_INTERFACE_DEFINED__

DEFINE_IIDX(ITileUpdater, "0942A48B-1D91-44EC-9243-C1E821C29A20")

.comdef ITileUpdater : public IInspectable

    Update		proc :ptr
    Clear		proc
    EnableNotificationQueue proc :boolean
    get_Setting		proc :ptr
    AddToSchedule	proc :ptr
    RemoveFromSchedule	proc :ptr
    GetScheduledTileNotifications proc :ptr
    StartPeriodicUpdate proc :ptr, :LONG
    StartPeriodicUpdateAtTime proc :ptr, :ptr, :LONG
    StopPeriodicUpdate	proc
    StartPeriodicUpdateBatch proc :ptr, :LONG
    StartPeriodicUpdateBatchAtTime proc :ptr, :ptr, :LONG
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CITileUpdater2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CITileUpdater2_INTERFACE_DEFINED__

DEFINE_IIDX(ITileUpdater2, "A2266E12-15EE-43ED-83F5-65B352BB1A84")

.comdef ITileUpdater2 : public IInspectable

    EnableNotificationQueueForSquare150x150 proc :boolean
    EnableNotificationQueueForWide310x150 proc :boolean
    EnableNotificationQueueForSquare310x310 proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIBadgeUpdateManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIBadgeUpdateManagerStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IBadgeUpdateManagerStatics, "33400FAA-6DD5-4105-AEBC-9B50FCA492DA")

.comdef IBadgeUpdateManagerStatics : public IInspectable

    CreateBadgeUpdaterForApplication proc :ptr
    CreateBadgeUpdaterForApplicationWithId proc :HSTRING, :ptr
    CreateBadgeUpdaterForSecondaryTile proc :HSTRING, :ptr
    GetTemplateContent	proc :LONG, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIBadgeUpdater_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIBadgeUpdater_INTERFACE_DEFINED__

DEFINE_IIDX(IBadgeUpdater, "B5FA1FD4-7562-4F6C-BFA3-1B6ED2E57F2F")

.comdef IBadgeUpdater : public IInspectable

    Update		proc :ptr
    Clear		proc
    StartPeriodicUpdate proc :ptr, :LONG
    StartPeriodicUpdateAtTime proc :ptr, :ptr, :LONG
    StopPeriodicUpdate	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIToastNotificationManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIToastNotificationManagerStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IToastNotificationManagerStatics, "50AC103F-D235-4598-BBEF-98FE4D1A3AD4")

.comdef IToastNotificationManagerStatics : public IInspectable

    CreateToastNotifier proc :ptr
    CreateToastNotifierWithId proc :HSTRING, :ptr
    GetTemplateContent	proc :LONG, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIToastNotifier_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIToastNotifier_INTERFACE_DEFINED__

DEFINE_IIDX(IToastNotifier, "75927B93-03F3-41EC-91D3-6E5BAC1B38E7")

.comdef IToastNotifier : public IInspectable

    Show		proc :ptr
    Hide		proc :ptr
    get_Setting		proc :ptr
    AddToSchedule	proc :ptr
    RemoveFromSchedule	proc :ptr
    GetScheduledToastNotifications proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CITileNotificationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CITileNotificationFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ITileNotificationFactory, "C6ABDD6E-4928-46C8-BDBF-81A047DEA0D4")

.comdef ITileNotificationFactory : public IInspectable

    CreateTileNotification proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CITileNotification_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CITileNotification_INTERFACE_DEFINED__

DEFINE_IIDX(ITileNotification, "EBAEC8FA-50EC-4C18-B4D0-3AF02E5540AB")

.comdef ITileNotification : public IInspectable

    get_Content		proc :ptr
    put_ExpirationTime	proc :ptr
    get_ExpirationTime	proc :ptr
    put_Tag		proc :HSTRING
    get_Tag		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIBadgeNotificationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIBadgeNotificationFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IBadgeNotificationFactory, "EDF255CE-0618-4D59-948A-5A61040C52F9")

.comdef IBadgeNotificationFactory : public IInspectable

    CreateBadgeNotification proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIBadgeNotification_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIBadgeNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IBadgeNotification, "075CB4CA-D08A-4E2F-9233-7E289C1F7722")

.comdef IBadgeNotification : public IInspectable

    get_Content		proc :ptr
    put_ExpirationTime	proc :ptr
    get_ExpirationTime	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIToastNotificationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIToastNotificationFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IToastNotificationFactory, "04124B20-82C6-4229-B109-FD9ED4662B53")

.comdef IToastNotificationFactory : public IInspectable

    CreateToastNotification proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIToastNotification_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIToastNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IToastNotification, "997E2675-059E-4E60-8B06-1760917C8B80")

.comdef IToastNotification : public IInspectable

    get_Content		proc :ptr
    put_ExpirationTime	proc :ptr
    get_ExpirationTime	proc :ptr
    add_Dismissed	proc :ptr, :ptr
    remove_Dismissed	proc :EventRegistrationToken
    add_Activated	proc :ptr, :ptr
    remove_Activated	proc :EventRegistrationToken
    add_Failed		proc :ptr, :ptr
    remove_Failed	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIScheduledToastNotificationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIScheduledToastNotificationFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IScheduledToastNotificationFactory, "E7BED191-0BB9-4189-8394-31761B476FD7")

.comdef IScheduledToastNotificationFactory : public IInspectable

    CreateScheduledToastNotification proc :ptr, :ptr, :ptr
    CreateScheduledToastNotificationRecurring proc :ptr, :ptr, :ptr, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIScheduledToastNotification_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIScheduledToastNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IScheduledToastNotification, "79F577F8-0DE7-48CD-9740-9B370490C838")

.comdef IScheduledToastNotification : public IInspectable

    get_Content		proc :ptr
    get_DeliveryTime	proc :ptr
    get_SnoozeInterval	proc :ptr
    get_MaximumSnoozeCount proc :ptr
    put_Id		proc :HSTRING
    get_Id		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIScheduledTileNotificationFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIScheduledTileNotificationFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IScheduledTileNotificationFactory, "3383138A-98C0-4C3B-BBD6-4A633C7CFC29")

.comdef IScheduledTileNotificationFactory : public IInspectable

    CreateScheduledTileNotification proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CNotifications_CIScheduledTileNotification_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CNotifications_CIScheduledTileNotification_INTERFACE_DEFINED__

DEFINE_IIDX(IScheduledTileNotification, "0ABCA6D5-99DC-4C78-A11C-C9E7F86D7EF7")

.comdef IScheduledTileNotification : public IInspectable

    get_Content		proc :ptr
    get_DeliveryTime	proc :ptr
    put_ExpirationTime	proc :ptr
    get_ExpirationTime	proc :ptr
    put_Tag		proc :HSTRING
    get_Tag		proc :ptr
    put_Id		proc :HSTRING
    get_Id		proc :ptr
   .ends

endif

.endn
.endn
.endn

define RuntimeClass_Windows_UI_Notifications_TileUpdater <L"Windows.UI.Notifications.TileUpdater">
define RuntimeClass_Windows_UI_Notifications_TileNotification <L"Windows.UI.Notifications.TileNotification">
define RuntimeClass_Windows_UI_Notifications_ScheduledTileNotification <L"Windows.UI.Notifications.ScheduledTileNotification">
define RuntimeClass_Windows_UI_Notifications_BadgeUpdater <L"Windows.UI.Notifications.BadgeUpdater">
define RuntimeClass_Windows_UI_Notifications_BadgeNotification <L"Windows.UI.Notifications.BadgeNotification">
define RuntimeClass_Windows_UI_Notifications_ToastNotifier <L"Windows.UI.Notifications.ToastNotifier">
define RuntimeClass_Windows_UI_Notifications_ToastNotification <L"Windows.UI.Notifications.ToastNotification">
define RuntimeClass_Windows_UI_Notifications_ScheduledToastNotification <L"Windows.UI.Notifications.ScheduledToastNotification">
define RuntimeClass_Windows_UI_Notifications_ToastDismissedEventArgs <L"Windows.UI.Notifications.ToastDismissedEventArgs">
define RuntimeClass_Windows_UI_Notifications_ToastFailedEventArgs <L"Windows.UI.Notifications.ToastFailedEventArgs">
define RuntimeClass_Windows_UI_Notifications_TileUpdateManager <L"Windows.UI.Notifications.TileUpdateManager">
define RuntimeClass_Windows_UI_Notifications_BadgeUpdateManager <L"Windows.UI.Notifications.BadgeUpdateManager">
define RuntimeClass_Windows_UI_Notifications_ToastNotificationManager <L"Windows.UI.Notifications.ToastNotificationManager">
define RuntimeClass_Windows_UI_Notifications_ToastActivatedEventArgs <L"Windows.UI.Notifications.ToastActivatedEventArgs">

endif
