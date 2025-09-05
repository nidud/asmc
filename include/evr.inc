ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __evr_h__
define __evr_h__

ifndef __unknwn_h__
include unknwn.inc
endif
include propidl.inc
include mfidl.inc
include strmif.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

DEFINE_GUID(MR_VIDEO_RENDER_SERVICE, 0x1092a86c, 0xab1a, 0x459a, 0xa3, 0x36, 0x83, 0x1f, 0xbc, 0x4d, 0x11, 0xff)
DEFINE_GUID(MR_VIDEO_MIXER_SERVICE, 0x73cd2fc, 0x6cf4, 0x40b7, 0x88, 0x59, 0xe8, 0x95, 0x52, 0xc8, 0x41, 0xf8);
DEFINE_GUID(MR_VIDEO_ACCELERATION_SERVICE, 0xefef5175, 0x5c7d, 0x4ce2, 0xbb, 0xbd, 0x34, 0xff, 0x8b, 0xca, 0x65, 0x54);
DEFINE_GUID(MR_BUFFER_SERVICE, 0xa562248c, 0x9ac6, 0x4ffc, 0x9f, 0xba, 0x3a, 0xf8, 0xf8, 0xad, 0x1a, 0x4d)
DEFINE_GUID(VIDEO_ZOOM_RECT, 0x7aaa1638, 0x1b7f, 0x4c93, 0xbd, 0x89, 0x5b, 0x9c, 0x9f, 0xb6, 0xfc, 0xf0)

ifndef __IMFVideoPositionMapper_INTERFACE_DEFINED__
define __IMFVideoPositionMapper_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoPositionMapper, "1F6A9F17-E70B-4e24-8AE4-0B2C3BA7A4AE")

.comdef IMFVideoPositionMapper : public IUnknown

    MapOutputCoordinateToInputStream proc :real4, :real4, :DWORD, :DWORD, :ptr, :ptr
   .ends

endif

ifndef __IMFVideoDeviceID_INTERFACE_DEFINED__
define __IMFVideoDeviceID_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoDeviceID, "A38D9567-5A9C-4f3c-B293-8EB415B279BA")

.comdef IMFVideoDeviceID : public IUnknown

    GetDeviceID		proc :ptr
   .ends

endif

.enum MFVideoAspectRatioMode {
    MFVideoARMode_None	= 0,
    MFVideoARMode_PreservePicture	= 0x1,
    MFVideoARMode_PreservePixel = 0x2,
    MFVideoARMode_NonLinearStretch	= 0x4,
    MFVideoARMode_Mask	= 0x7
    }

.enum MFVideoRenderPrefs {
    MFVideoRenderPrefs_DoNotRenderBorder	= 0x1,
    MFVideoRenderPrefs_DoNotClipToDevice	= 0x2,
    MFVideoRenderPrefs_AllowOutputThrottling	= 0x4,
    MFVideoRenderPrefs_ForceOutputThrottling	= 0x8,
    MFVideoRenderPrefs_ForceBatching	= 0x10,
    MFVideoRenderPrefs_AllowBatching	= 0x20,
    MFVideoRenderPrefs_ForceScaling	= 0x40,
    MFVideoRenderPrefs_AllowScaling	= 0x80,
    MFVideoRenderPrefs_DoNotRepaintOnStop	= 0x100,
    MFVideoRenderPrefs_Mask	= 0x1ff
    }

ifndef _MFVideoNormalizedRect_
define _MFVideoNormalizedRect_
MFVideoNormalizedRect	STRUC
left			real4 ?
top			real4 ?
right			real4 ?
bottom			real4 ?
MFVideoNormalizedRect	ENDS
endif

ifndef __IMFVideoDisplayControl_INTERFACE_DEFINED__
define __IMFVideoDisplayControl_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoDisplayControl, "a490b1e4-ab84-4d31-a1b2-181e03b1077a")

.comdef IMFVideoDisplayControl : public IUnknown

    GetNativeVideoSize	proc :ptr, :ptr
    GetIdealVideoSize	proc :ptr, :ptr
    SetVideoPosition	proc :ptr, :ptr
    GetVideoPosition	proc :ptr, :LPRECT
    SetAspectRatioMode	proc :DWORD
    GetAspectRatioMode	proc :ptr
    SetVideoWindow	proc :HWND
    GetVideoWindow	proc :ptr
    RepaintVideo	proc
    GetCurrentImage	proc :ptr
    SetBorderColor	proc :COLORREF
    GetBorderColor	proc :ptr
    SetRenderingPrefs	proc :DWORD
    GetRenderingPrefs	proc :ptr
    SetFullscreen	proc :BOOL
    GetFullscreen	proc :ptr
   .ends

endif

.enum MFVP_MESSAGE_TYPE {
    MFVP_MESSAGE_FLUSH,
    MFVP_MESSAGE_INVALIDATEMEDIATYPE,
    MFVP_MESSAGE_PROCESSINPUTNOTIFY,
    MFVP_MESSAGE_BEGINSTREAMING,
    MFVP_MESSAGE_ENDSTREAMING,
    MFVP_MESSAGE_ENDOFSTREAM,
    MFVP_MESSAGE_STEP,
    MFVP_MESSAGE_CANCELSTEP
    }

ifndef __IMFVideoPresenter_INTERFACE_DEFINED__
define __IMFVideoPresenter_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoPresenter, "29AFF080-182A-4a5d-AF3B-448F3A6346CB")

.comdef IMFVideoPresenter : public IMFClockStateSink

    ProcessMessage	proc :MFVP_MESSAGE_TYPE, :ULONG_PTR
    GetCurrentMediaType proc :ptr
   .ends

endif

ifndef __IMFDesiredSample_INTERFACE_DEFINED__
define __IMFDesiredSample_INTERFACE_DEFINED__

DEFINE_IIDX(IMFDesiredSample, "56C294D0-753E-4260-8D61-A3D8820B1D54")

.comdef IMFDesiredSample : public IUnknown

    GetDesiredSampleTimeAndDuration proc :ptr, :ptr
    SetDesiredSampleTimeAndDuration proc :LONGLONG, :LONGLONG
    Clear		proc
   .ends

endif

ifndef __IMFVideoMixerControl_INTERFACE_DEFINED__
define __IMFVideoMixerControl_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoMixerControl, "A5C6C53F-C202-4aa5-9695-175BA8C508A5")

.comdef IMFVideoMixerControl : public IUnknown

    SetStreamZOrder	proc :DWORD, :DWORD
    GetStreamZOrder	proc :DWORD, :ptr
    SetStreamOutputRect proc :DWORD, :ptr
    GetStreamOutputRect proc :DWORD, :ptr
   .ends

endif

.enum MFVideoMixPrefs {
    MFVideoMixPrefs_ForceHalfInterlace	= 0x1,
    MFVideoMixPrefs_AllowDropToHalfInterlace	= 0x2,
    MFVideoMixPrefs_AllowDropToBob	= 0x4,
    MFVideoMixPrefs_ForceBob	= 0x8,
    MFVideoMixPrefs_EnableRotation	= 0x10,
    MFVideoMixPrefs_Mask	= 0x1f
    }

ifndef __IMFVideoMixerControl2_INTERFACE_DEFINED__
define __IMFVideoMixerControl2_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoMixerControl2, "8459616d-966e-4930-b658-54fa7e5a16d3")

.comdef IMFVideoMixerControl2 : public IMFVideoMixerControl

    SetMixingPrefs	proc :DWORD
    GetMixingPrefs	proc :ptr
   .ends

endif

ifndef __IMFVideoRenderer_INTERFACE_DEFINED__
define __IMFVideoRenderer_INTERFACE_DEFINED__

DEFINE_IIDX(IMFVideoRenderer, "DFDFD197-A9CA-43d8-B341-6AF3503792CD")

.comdef IMFVideoRenderer : public IUnknown

    InitializeRenderer	proc :ptr, :ptr
   .ends

endif

ifndef __IEVRFilterConfig_INTERFACE_DEFINED__
define __IEVRFilterConfig_INTERFACE_DEFINED__

DEFINE_IIDX(IEVRFilterConfig, "83E91E85-82C1-4ea7-801D-85DC50B75086")

.comdef IEVRFilterConfig : public IUnknown

    SetNumberOfStreams	proc :DWORD
    GetNumberOfStreams	proc :ptr
   .ends

endif

.enum EVRFilterConfig_Prefs {
    EVRFilterConfigPrefs_EnableQoS	= 0x1,
    EVRFilterConfigPrefs_Mask	= 0x1
    }

ifndef __IEVRFilterConfigEx_INTERFACE_DEFINED__
define __IEVRFilterConfigEx_INTERFACE_DEFINED__

DEFINE_IIDX(IEVRFilterConfigEx, "aea36028-796d-454f-beee-b48071e24304")

.comdef IEVRFilterConfigEx : public IEVRFilterConfig

    SetConfigPrefs	proc :DWORD
    GetConfigPrefs	proc :ptr
   .ends

endif

.enum MF_SERVICE_LOOKUP_TYPE {
    MF_SERVICE_LOOKUP_UPSTREAM,
    MF_SERVICE_LOOKUP_UPSTREAM_DIRECT,
    MF_SERVICE_LOOKUP_DOWNSTREAM,
    MF_SERVICE_LOOKUP_DOWNSTREAM_DIRECT,
    MF_SERVICE_LOOKUP_ALL,
    MF_SERVICE_LOOKUP_GLOBAL
    }

ifndef __IMFTopologyServiceLookup_INTERFACE_DEFINED__
define __IMFTopologyServiceLookup_INTERFACE_DEFINED__

DEFINE_IIDX(IMFTopologyServiceLookup, "fa993889-4383-415a-a930-dd472a8cf6f7")

.comdef IMFTopologyServiceLookup : public IUnknown

    LookupService	proc :MF_SERVICE_LOOKUP_TYPE, :DWORD, :REFGUID, :REFIID
   .ends

endif

ifndef __IMFTopologyServiceLookupClient_INTERFACE_DEFINED__
define __IMFTopologyServiceLookupClient_INTERFACE_DEFINED__

DEFINE_IIDX(IMFTopologyServiceLookupClient, "fa99388a-4383-415a-a930-dd472a8cf6f7")

.comdef IMFTopologyServiceLookupClient : public IUnknown

    InitServicePointers proc :ptr
    ReleaseServicePointers proc
   .ends

endif

ifndef __IEVRTrustedVideoPlugin_INTERFACE_DEFINED__
define __IEVRTrustedVideoPlugin_INTERFACE_DEFINED__

DEFINE_IIDX(IEVRTrustedVideoPlugin, "83A4CE40-7710-494b-A893-A472049AF630")

.comdef IEVRTrustedVideoPlugin : public IUnknown

    IsInTrustedVideoMode proc :ptr
    CanConstrict	proc :ptr
    SetConstriction	proc :DWORD
    DisableImageExport	proc :BOOL
   .ends

endif
ifndef MFEVRDLL
MFEVRDLL		equ 0
endif
endif

endif
