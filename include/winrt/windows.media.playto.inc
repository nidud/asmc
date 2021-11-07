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

ifndef __windows2Emedia2Eplayto_h__
define __windows2Emedia2Eplayto_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionErrorEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionErrorEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionErrorEventArgs, "8f599f3d-3655-5993-a119-741ec4ee6e42")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionErrorEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionStateChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionStateChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionStateChangedEventArgs, "def77c1c-9363-5b47-b9f8-a236c50d372e")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionStateChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionTransferredEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionTransferredEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionTransferredEventArgs, "7278e7f2-0360-5571-8c3e-ea032767c473")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToConnection_Windows__CMedia__CPlayTo__CPlayToConnectionTransferredEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceRequestedEventArgs, "6ac9f3a4-39b6-51d8-8e08-f137908e922f")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceSelectedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceSelectedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceSelectedEventArgs, "bf87431a-7451-52a5-a5e2-bfaf408e0c88")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToManager_Windows__CMedia__CPlayTo__CPlayToSourceSelectedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_IInspectable, "7a89b9c2-78d4-5866-88f1-4cdc0a0e75b8")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CCurrentTimeChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CCurrentTimeChangeRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CCurrentTimeChangeRequestedEventArgs, "42abdf9f-14a6-5c1f-839b-86029505b1d0")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CCurrentTimeChangeRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CMuteChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CMuteChangeRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CMuteChangeRequestedEventArgs, "0674cf85-b6fd-5926-9b72-35fe517a3f44")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CMuteChangeRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CPlaybackRateChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CPlaybackRateChangeRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CPlaybackRateChangeRequestedEventArgs, "e7594396-58c3-5316-bc4f-1d13eadbeffd")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CPlaybackRateChangeRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CSourceChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CSourceChangeRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CSourceChangeRequestedEventArgs, "1466d074-b7b4-5814-b2d7-847c5ae7d87d")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CSourceChangeRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CVolumeChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CVolumeChangeRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CVolumeChangeRequestedEventArgs, "9c3f7c84-9b4d-5cdc-8144-1c2f617b6ede")

.comdef __FITypedEventHandler_2_Windows__CMedia__CPlayTo__CPlayToReceiver_Windows__CMedia__CPlayTo__CVolumeChangeRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace PlayTo

.enum PlayToConnectionState {
    PlayToConnectionState_Disconnected	= 0,
    PlayToConnectionState_Connected	= 1,
    PlayToConnectionState_Rendering	= 2
    }

.enum PlayToConnectionError {
    PlayToConnectionError_None	= 0,
    PlayToConnectionError_DeviceNotResponding	= 1,
    PlayToConnectionError_DeviceError	= 2,
    PlayToConnectionError_DeviceLocked	= 3,
    PlayToConnectionError_ProtectedPlaybackFailed	= 4
    }

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CISourceChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CISourceChangeRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_ISourceChangeRequestedEventArgs <L"Windows.Media.PlayTo.ISourceChangeRequestedEventArgs">
DEFINE_IIDX(ISourceChangeRequestedEventArgs, "FB3F3A96-7AA6-4A8B-86E7-54F6C6D34F64")

.comdef ISourceChangeRequestedEventArgs : public IInspectable

    get_Stream		proc :ptr
    get_Title		proc :ptr
    get_Author		proc :ptr
    get_Album		proc :ptr
    get_Genre		proc :ptr
    get_Description	proc :ptr
    get_Date		proc :ptr
    get_Thumbnail	proc :ptr
    get_Rating		proc :ptr
    get_Properties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlaybackRateChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlaybackRateChangeRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlaybackRateChangeRequestedEventArgs <L"Windows.Media.PlayTo.IPlaybackRateChangeRequestedEventArgs">
DEFINE_IIDX(IPlaybackRateChangeRequestedEventArgs, "0F5661AE-2C88-4CCA-8540-D586095D13A5")

.comdef IPlaybackRateChangeRequestedEventArgs : public IInspectable

    get_Rate		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CICurrentTimeChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CICurrentTimeChangeRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_ICurrentTimeChangeRequestedEventArgs <L"Windows.Media.PlayTo.ICurrentTimeChangeRequestedEventArgs">
DEFINE_IIDX(ICurrentTimeChangeRequestedEventArgs, "99711324-EDC7-4BF5-91F6-3C8627DB59E5")

.comdef ICurrentTimeChangeRequestedEventArgs : public IInspectable

    get_Time		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIMuteChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIMuteChangeRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IMuteChangeRequestedEventArgs <L"Windows.Media.PlayTo.IMuteChangeRequestedEventArgs">
DEFINE_IIDX(IMuteChangeRequestedEventArgs, "E4B4F5F6-AF1F-4F1E-B437-7DA32400E1D4")

.comdef IMuteChangeRequestedEventArgs : public IInspectable

    get_Mute		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIVolumeChangeRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIVolumeChangeRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IVolumeChangeRequestedEventArgs <L"Windows.Media.PlayTo.IVolumeChangeRequestedEventArgs">
DEFINE_IIDX(IVolumeChangeRequestedEventArgs, "6F026D5C-CF75-4C2B-913E-6D7C6C329179")

.comdef IVolumeChangeRequestedEventArgs : public IInspectable

    get_Volume		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToReceiver_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToReceiver_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToReceiver <L"Windows.Media.PlayTo.IPlayToReceiver">
DEFINE_IIDX(IPlayToReceiver, "AC15CF47-A162-4AA6-AF1B-3AA35F3B9069")

.comdef IPlayToReceiver : public IInspectable

    add_PlayRequested	proc :ptr, :ptr
    remove_PlayRequested proc :EventRegistrationToken
    add_PauseRequested	proc :ptr, :ptr
    remove_PauseRequested proc :EventRegistrationToken
    add_SourceChangeRequested proc :ptr, :ptr
    remove_SourceChangeRequested proc :EventRegistrationToken
    add_PlaybackRateChangeRequested proc :ptr, :ptr
    remove_PlaybackRateChangeRequested proc :EventRegistrationToken
    add_CurrentTimeChangeRequested proc :ptr, :ptr
    remove_CurrentTimeChangeRequested proc :EventRegistrationToken
    add_MuteChangeRequested proc :ptr, :ptr
    remove_MuteChangeRequested proc :EventRegistrationToken
    add_VolumeChangeRequested proc :ptr, :ptr
    remove_VolumeChangeRequested proc :EventRegistrationToken
    add_TimeUpdateRequested proc :ptr, :ptr
    remove_TimeUpdateRequested proc :EventRegistrationToken
    add_StopRequested	proc :ptr, :ptr
    remove_StopRequested proc :EventRegistrationToken
    NotifyVolumeChange	proc :DOUBLE, :boolean
    NotifyRateChange	proc :DOUBLE
    NotifyLoadedMetadata proc
    NotifyTimeUpdate	proc :Windows::Foundation::TimeSpan
    NotifyDurationChange proc :Windows::Foundation::TimeSpan
    NotifySeeking	proc
    NotifySeeked	proc
    NotifyPaused	proc
    NotifyPlaying	proc
    NotifyEnded		proc
    NotifyError		proc
    NotifyStopped	proc
    get_FriendlyName	proc :ptr
    put_FriendlyName	proc :HSTRING
    put_SupportsImage	proc :boolean
    get_SupportsImage	proc :ptr
    put_SupportsAudio	proc :boolean
    get_SupportsAudio	proc :ptr
    put_SupportsVideo	proc :boolean
    get_SupportsVideo	proc :ptr
    get_Properties	proc :ptr
    StartAsync		proc :ptr
    StopAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSource_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToSource <L"Windows.Media.PlayTo.IPlayToSource">
DEFINE_IIDX(IPlayToSource, "7F138A08-FBB7-4B09-8356-AA5F4E335C31")

.comdef IPlayToSource : public IInspectable

    get_Connection	proc :ptr
    get_Next		proc :ptr
    put_Next		proc :ptr
    PlayNext		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceWithPreferredSourceUri_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceWithPreferredSourceUri_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToSourceWithPreferredSourceUri <L"Windows.Media.PlayTo.IPlayToSourceWithPreferredSourceUri">
DEFINE_IIDX(IPlayToSourceWithPreferredSourceUri, "AAB253EB-3301-4DC4-AFBA-B2F2ED9635A0")

.comdef IPlayToSourceWithPreferredSourceUri : public IInspectable

    get_PreferredSourceUri proc :ptr
    put_PreferredSourceUri proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnectionStateChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnectionStateChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToConnectionStateChangedEventArgs <L"Windows.Media.PlayTo.IPlayToConnectionStateChangedEventArgs">
DEFINE_IIDX(IPlayToConnectionStateChangedEventArgs, "68C4B50F-0C20-4980-8602-58C62238D423")

.comdef IPlayToConnectionStateChangedEventArgs : public IInspectable

    get_PreviousState	proc :ptr
    get_CurrentState	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnectionTransferredEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnectionTransferredEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToConnectionTransferredEventArgs <L"Windows.Media.PlayTo.IPlayToConnectionTransferredEventArgs">
DEFINE_IIDX(IPlayToConnectionTransferredEventArgs, "FAE3193A-0683-47D9-8DF0-18CBB48984D8")

.comdef IPlayToConnectionTransferredEventArgs : public IInspectable

    get_PreviousSource	proc :ptr
    get_CurrentSource	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnectionErrorEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnectionErrorEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToConnectionErrorEventArgs <L"Windows.Media.PlayTo.IPlayToConnectionErrorEventArgs">
DEFINE_IIDX(IPlayToConnectionErrorEventArgs, "BF5EADA6-88E6-445F-9D40-D9B9F8939896")

.comdef IPlayToConnectionErrorEventArgs : public IInspectable

    get_Code		proc :ptr
    get_Message		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToConnection_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToConnection <L"Windows.Media.PlayTo.IPlayToConnection">
DEFINE_IIDX(IPlayToConnection, "112FBFC8-F235-4FDE-8D41-9BF27C9E9A40")

.comdef IPlayToConnection : public IInspectable

    get_State		proc :ptr
    add_StateChanged	proc :ptr, :ptr
    remove_StateChanged proc :EventRegistrationToken
    add_Transferred	proc :ptr, :ptr
    remove_Transferred	proc :EventRegistrationToken
    add_Error		proc :ptr, :ptr
    remove_Error	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceSelectedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceSelectedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToSourceSelectedEventArgs <L"Windows.Media.PlayTo.IPlayToSourceSelectedEventArgs">
DEFINE_IIDX(IPlayToSourceSelectedEventArgs, "0C9D8511-5202-4DCB-8C67-ABDA12BB3C12")

.comdef IPlayToSourceSelectedEventArgs : public IInspectable

    get_FriendlyName	proc :ptr
    get_Icon		proc :ptr
    get_SupportsImage	proc :ptr
    get_SupportsAudio	proc :ptr
    get_SupportsVideo	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToSourceDeferral <L"Windows.Media.PlayTo.IPlayToSourceDeferral">
DEFINE_IIDX(IPlayToSourceDeferral, "4100891D-278E-4F29-859B-A9E501053E7D")

.comdef IPlayToSourceDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToSourceRequest <L"Windows.Media.PlayTo.IPlayToSourceRequest">
DEFINE_IIDX(IPlayToSourceRequest, "F8584665-64F4-44A0-AC0D-468D2B8FDA83")

.comdef IPlayToSourceRequest : public IInspectable

    get_Deadline	proc :ptr
    DisplayErrorString	proc :HSTRING
    GetDeferral		proc :ptr
    SetSource		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToSourceRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToSourceRequestedEventArgs <L"Windows.Media.PlayTo.IPlayToSourceRequestedEventArgs">
DEFINE_IIDX(IPlayToSourceRequestedEventArgs, "C5CDC330-29DF-4EC6-9DA9-9FBDFCFC1B3E")

.comdef IPlayToSourceRequestedEventArgs : public IInspectable

    get_SourceRequest	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToManager <L"Windows.Media.PlayTo.IPlayToManager">
DEFINE_IIDX(IPlayToManager, "F56A206E-1B77-42EF-8F0D-B949F8D9B260")

.comdef IPlayToManager : public IInspectable

    add_SourceRequested proc :ptr, :ptr
    remove_SourceRequested proc :EventRegistrationToken
    add_SourceSelected	proc :ptr, :ptr
    remove_SourceSelected proc :EventRegistrationToken
    put_DefaultSourceSelection proc :boolean
    get_DefaultSourceSelection proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CPlayTo_CIPlayToManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_PlayTo_IPlayToManagerStatics <L"Windows.Media.PlayTo.IPlayToManagerStatics">
DEFINE_IIDX(IPlayToManagerStatics, "64E6A887-3982-4F3B-BA20-6155E435325B")

.comdef IPlayToManagerStatics : public IInspectable

    GetForCurrentView	proc :ptr
    ShowPlayToUI	proc
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_PlayTo_SourceChangeRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_SourceChangeRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_SourceChangeRequestedEventArgs <L"Windows.Media.PlayTo.SourceChangeRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlaybackRateChangeRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlaybackRateChangeRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlaybackRateChangeRequestedEventArgs <L"Windows.Media.PlayTo.PlaybackRateChangeRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_CurrentTimeChangeRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_CurrentTimeChangeRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_CurrentTimeChangeRequestedEventArgs <L"Windows.Media.PlayTo.CurrentTimeChangeRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_MuteChangeRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_MuteChangeRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_MuteChangeRequestedEventArgs <L"Windows.Media.PlayTo.MuteChangeRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_VolumeChangeRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_VolumeChangeRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_VolumeChangeRequestedEventArgs <L"Windows.Media.PlayTo.VolumeChangeRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToReceiver_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToReceiver_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToReceiver <L"Windows.Media.PlayTo.PlayToReceiver">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnection_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnection_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToConnection <L"Windows.Media.PlayTo.PlayToConnection">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToSource_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToSource_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToSource <L"Windows.Media.PlayTo.PlayToSource">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnectionStateChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnectionStateChangedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToConnectionStateChangedEventArgs <L"Windows.Media.PlayTo.PlayToConnectionStateChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnectionTransferredEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnectionTransferredEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToConnectionTransferredEventArgs <L"Windows.Media.PlayTo.PlayToConnectionTransferredEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnectionErrorEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToConnectionErrorEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToConnectionErrorEventArgs <L"Windows.Media.PlayTo.PlayToConnectionErrorEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceSelectedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceSelectedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToSourceSelectedEventArgs <L"Windows.Media.PlayTo.PlayToSourceSelectedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceDeferral_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceDeferral_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToSourceDeferral <L"Windows.Media.PlayTo.PlayToSourceDeferral">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceRequest_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceRequest_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToSourceRequest <L"Windows.Media.PlayTo.PlayToSourceRequest">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToSourceRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToSourceRequestedEventArgs <L"Windows.Media.PlayTo.PlayToSourceRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_PlayTo_PlayToManager_DEFINED
define RUNTIMECLASS_Windows_Media_PlayTo_PlayToManager_DEFINED
define RuntimeClass_Windows_Media_PlayTo_PlayToManager <L"Windows.Media.PlayTo.PlayToManager">
endif

endif
