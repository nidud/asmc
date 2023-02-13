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

ifndef __segment_h__
define __segment_h__

include oaidl.inc
include ocidl.inc
include strmif.inc
include tuner.inc
include tvratings.inc
include evr.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include olectl.inc

.enum SegDispidList {
    dispidName	= 0,
    dispidStatus	= ( dispidName + 1 ) ,
    dispidDevImageSourceWidth	= ( dispidStatus + 1 ) ,
    dispidDevImageSourceHeight	= ( dispidDevImageSourceWidth + 1 ) ,
    dispidDevCountryCode	= ( dispidDevImageSourceHeight + 1 ) ,
    dispidDevOverScan	= ( dispidDevCountryCode + 1 ) ,
    dispidSegment	= ( dispidDevOverScan + 1 ) ,
    dispidDevVolume	= ( dispidSegment + 1 ) ,
    dispidDevBalance	= ( dispidDevVolume + 1 ) ,
    dispidDevPower	= ( dispidDevBalance + 1 ) ,
    dispidTuneChan	= ( dispidDevPower + 1 ) ,
    dispidDevVideoSubchannel	= ( dispidTuneChan + 1 ) ,
    dispidDevAudioSubchannel	= ( dispidDevVideoSubchannel + 1 ) ,
    dispidChannelAvailable	= ( dispidDevAudioSubchannel + 1 ) ,
    dispidDevVideoFrequency	= ( dispidChannelAvailable + 1 ) ,
    dispidDevAudioFrequency	= ( dispidDevVideoFrequency + 1 ) ,
    dispidCount = ( dispidDevAudioFrequency + 1 ) ,
    dispidDevFileName	= ( dispidCount + 1 ) ,
    dispidVisible	= ( dispidDevFileName + 1 ) ,
    dispidOwner = ( dispidVisible + 1 ) ,
    dispidMessageDrain	= ( dispidOwner + 1 ) ,
    dispidViewable	= ( dispidMessageDrain + 1 ) ,
    dispidDevView	= ( dispidViewable + 1 ) ,
    dispidKSCat = ( dispidDevView + 1 ) ,
    dispidCLSID = ( dispidKSCat + 1 ) ,
    dispid_KSCat	= ( dispidCLSID + 1 ) ,
    dispid_CLSID	= ( dispid_KSCat + 1 ) ,
    dispidTune	= ( dispid_CLSID + 1 ) ,
    dispidTS	= ( dispidTune + 1 ) ,
    dispidDevSAP	= ( dispidTS + 1 ) ,
    dispidClip	= ( dispidDevSAP + 1 ) ,
    dispidRequestedClipRect	= ( dispidClip + 1 ) ,
    dispidClippedSourceRect	= ( dispidRequestedClipRect + 1 ) ,
    dispidAvailableSourceRect	= ( dispidClippedSourceRect + 1 ) ,
    dispidMediaPosition = ( dispidAvailableSourceRect + 1 ) ,
    dispidDevRun	= ( dispidMediaPosition + 1 ) ,
    dispidDevPause	= ( dispidDevRun + 1 ) ,
    dispidDevStop	= ( dispidDevPause + 1 ) ,
    dispidCCEnable	= ( dispidDevStop + 1 ) ,
    dispidDevStep	= ( dispidCCEnable + 1 ) ,
    dispidDevCanStep	= ( dispidDevStep + 1 ) ,
    dispidSourceSize	= ( dispidDevCanStep + 1 ) ,
    dispid_playtitle	= ( dispidSourceSize + 1 ) ,
    dispid_playchapterintitle	= ( dispid_playtitle + 1 ) ,
    dispid_playchapter	= ( dispid_playchapterintitle + 1 ) ,
    dispid_playchaptersautostop = ( dispid_playchapter + 1 ) ,
    dispid_playattime	= ( dispid_playchaptersautostop + 1 ) ,
    dispid_playattimeintitle	= ( dispid_playattime + 1 ) ,
    dispid_playperiodintitleautostop	= ( dispid_playattimeintitle + 1 ) ,
    dispid_replaychapter	= ( dispid_playperiodintitleautostop + 1 ) ,
    dispid_playprevchapter	= ( dispid_replaychapter + 1 ) ,
    dispid_playnextchapter	= ( dispid_playprevchapter + 1 ) ,
    dispid_playforwards = ( dispid_playnextchapter + 1 ) ,
    dispid_playbackwards	= ( dispid_playforwards + 1 ) ,
    dispid_stilloff	= ( dispid_playbackwards + 1 ) ,
    dispid_audiolanguage	= ( dispid_stilloff + 1 ) ,
    dispid_showmenu	= ( dispid_audiolanguage + 1 ) ,
    dispid_resume	= ( dispid_showmenu + 1 ) ,
    dispid_returnfromsubmenu	= ( dispid_resume + 1 ) ,
    dispid_buttonsavailable	= ( dispid_returnfromsubmenu + 1 ) ,
    dispid_currentbutton	= ( dispid_buttonsavailable + 1 ) ,
    dispid_SelectAndActivateButton	= ( dispid_currentbutton + 1 ) ,
    dispid_ActivateButton	= ( dispid_SelectAndActivateButton + 1 ) ,
    dispid_SelectRightButton	= ( dispid_ActivateButton + 1 ) ,
    dispid_SelectLeftButton	= ( dispid_SelectRightButton + 1 ) ,
    dispid_SelectLowerButton	= ( dispid_SelectLeftButton + 1 ) ,
    dispid_SelectUpperButton	= ( dispid_SelectLowerButton + 1 ) ,
    dispid_ActivateAtPosition	= ( dispid_SelectUpperButton + 1 ) ,
    dispid_SelectAtPosition	= ( dispid_ActivateAtPosition + 1 ) ,
    dispid_ButtonAtPosition	= ( dispid_SelectAtPosition + 1 ) ,
    dispid_NumberOfChapters	= ( dispid_ButtonAtPosition + 1 ) ,
    dispid_TotalTitleTime	= ( dispid_NumberOfChapters + 1 ) ,
    dispid_TitlesAvailable	= ( dispid_TotalTitleTime + 1 ) ,
    dispid_VolumesAvailable	= ( dispid_TitlesAvailable + 1 ) ,
    dispid_CurrentVolume	= ( dispid_VolumesAvailable + 1 ) ,
    dispid_CurrentDiscSide	= ( dispid_CurrentVolume + 1 ) ,
    dispid_CurrentDomain	= ( dispid_CurrentDiscSide + 1 ) ,
    dispid_CurrentChapter	= ( dispid_CurrentDomain + 1 ) ,
    dispid_CurrentTitle = ( dispid_CurrentChapter + 1 ) ,
    dispid_CurrentTime	= ( dispid_CurrentTitle + 1 ) ,
    dispid_FramesPerSecond	= ( dispid_CurrentTime + 1 ) ,
    dispid_DVDTimeCode2bstr	= ( dispid_FramesPerSecond + 1 ) ,
    dispid_DVDDirectory = ( dispid_DVDTimeCode2bstr + 1 ) ,
    dispid_IsSubpictureStreamEnabled	= ( dispid_DVDDirectory + 1 ) ,
    dispid_IsAudioStreamEnabled = ( dispid_IsSubpictureStreamEnabled + 1 ) ,
    dispid_CurrentSubpictureStream	= ( dispid_IsAudioStreamEnabled + 1 ) ,
    dispid_SubpictureLanguage	= ( dispid_CurrentSubpictureStream + 1 ) ,
    dispid_CurrentAudioStream	= ( dispid_SubpictureLanguage + 1 ) ,
    dispid_AudioStreamsAvailable	= ( dispid_CurrentAudioStream + 1 ) ,
    dispid_AnglesAvailable	= ( dispid_AudioStreamsAvailable + 1 ) ,
    dispid_CurrentAngle = ( dispid_AnglesAvailable + 1 ) ,
    dispid_CCActive	= ( dispid_CurrentAngle + 1 ) ,
    dispid_CurrentCCService	= ( dispid_CCActive + 1 ) ,
    dispid_SubpictureStreamsAvailable	= ( dispid_CurrentCCService + 1 ) ,
    dispid_SubpictureOn = ( dispid_SubpictureStreamsAvailable + 1 ) ,
    dispid_DVDUniqueID	= ( dispid_SubpictureOn + 1 ) ,
    dispid_EnableResetOnStop	= ( dispid_DVDUniqueID + 1 ) ,
    dispid_AcceptParentalLevelChange	= ( dispid_EnableResetOnStop + 1 ) ,
    dispid_NotifyParentalLevelChange	= ( dispid_AcceptParentalLevelChange + 1 ) ,
    dispid_SelectParentalCountry	= ( dispid_NotifyParentalLevelChange + 1 ) ,
    dispid_SelectParentalLevel	= ( dispid_SelectParentalCountry + 1 ) ,
    dispid_TitleParentalLevels	= ( dispid_SelectParentalLevel + 1 ) ,
    dispid_PlayerParentalCountry	= ( dispid_TitleParentalLevels + 1 ) ,
    dispid_PlayerParentalLevel	= ( dispid_PlayerParentalCountry + 1 ) ,
    dispid_Eject	= ( dispid_PlayerParentalLevel + 1 ) ,
    dispid_UOPValid	= ( dispid_Eject + 1 ) ,
    dispid_SPRM = ( dispid_UOPValid + 1 ) ,
    dispid_GPRM = ( dispid_SPRM + 1 ) ,
    dispid_DVDTextStringType	= ( dispid_GPRM + 1 ) ,
    dispid_DVDTextString	= ( dispid_DVDTextStringType + 1 ) ,
    dispid_DVDTextNumberOfStrings	= ( dispid_DVDTextString + 1 ) ,
    dispid_DVDTextNumberOfLanguages	= ( dispid_DVDTextNumberOfStrings + 1 ) ,
    dispid_DVDTextLanguageLCID	= ( dispid_DVDTextNumberOfLanguages + 1 ) ,
    dispid_RegionChange = ( dispid_DVDTextLanguageLCID + 1 ) ,
    dispid_DVDAdm	= ( dispid_RegionChange + 1 ) ,
    dispid_DeleteBookmark	= ( dispid_DVDAdm + 1 ) ,
    dispid_RestoreBookmark	= ( dispid_DeleteBookmark + 1 ) ,
    dispid_SaveBookmark = ( dispid_RestoreBookmark + 1 ) ,
    dispid_SelectDefaultAudioLanguage	= ( dispid_SaveBookmark + 1 ) ,
    dispid_SelectDefaultSubpictureLanguage	= ( dispid_SelectDefaultAudioLanguage + 1 ) ,
    dispid_PreferredSubpictureStream	= ( dispid_SelectDefaultSubpictureLanguage + 1 ) ,
    dispid_DefaultMenuLanguage	= ( dispid_PreferredSubpictureStream + 1 ) ,
    dispid_DefaultSubpictureLanguage	= ( dispid_DefaultMenuLanguage + 1 ) ,
    dispid_DefaultAudioLanguage = ( dispid_DefaultSubpictureLanguage + 1 ) ,
    dispid_DefaultSubpictureLanguageExt = ( dispid_DefaultAudioLanguage + 1 ) ,
    dispid_DefaultAudioLanguageExt	= ( dispid_DefaultSubpictureLanguageExt + 1 ) ,
    dispid_LanguageFromLCID	= ( dispid_DefaultAudioLanguageExt + 1 ) ,
    dispid_KaraokeAudioPresentationMode = ( dispid_LanguageFromLCID + 1 ) ,
    dispid_KaraokeChannelContent	= ( dispid_KaraokeAudioPresentationMode + 1 ) ,
    dispid_KaraokeChannelAssignment	= ( dispid_KaraokeChannelContent + 1 ) ,
    dispid_RestorePreferredSettings	= ( dispid_KaraokeChannelAssignment + 1 ) ,
    dispid_ButtonRect	= ( dispid_RestorePreferredSettings + 1 ) ,
    dispid_DVDScreenInMouseCoordinates	= ( dispid_ButtonRect + 1 ) ,
    dispid_CustomCompositorClass	= ( dispid_DVDScreenInMouseCoordinates + 1 ) ,
    dispidCustomCompositorClass = ( dispid_CustomCompositorClass + 1 ) ,
    dispid_CustomCompositor	= ( dispidCustomCompositorClass + 1 ) ,
    dispidMixerBitmap	= ( dispid_CustomCompositor + 1 ) ,
    dispid_MixerBitmap	= ( dispidMixerBitmap + 1 ) ,
    dispidMixerBitmapOpacity	= ( dispid_MixerBitmap + 1 ) ,
    dispidMixerBitmapRect	= ( dispidMixerBitmapOpacity + 1 ) ,
    dispidSetupMixerBitmap	= ( dispidMixerBitmapRect + 1 ) ,
    dispidUsingOverlay	= ( dispidSetupMixerBitmap + 1 ) ,
    dispidDisplayChange = ( dispidUsingOverlay + 1 ) ,
    dispidRePaint	= ( dispidDisplayChange + 1 ) ,
    dispid_IsEqualDevice	= ( dispidRePaint + 1 ) ,
    dispidrate	= ( dispid_IsEqualDevice + 1 ) ,
    dispidposition	= ( dispidrate + 1 ) ,
    dispidpositionmode	= ( dispidposition + 1 ) ,
    dispidlength	= ( dispidpositionmode + 1 ) ,
    dispidChangePassword	= ( dispidlength + 1 ) ,
    dispidSaveParentalLevel	= ( dispidChangePassword + 1 ) ,
    dispidSaveParentalCountry	= ( dispidSaveParentalLevel + 1 ) ,
    dispidConfirmPassword	= ( dispidSaveParentalCountry + 1 ) ,
    dispidGetParentalLevel	= ( dispidConfirmPassword + 1 ) ,
    dispidGetParentalCountry	= ( dispidGetParentalLevel + 1 ) ,
    dispidDefaultAudioLCID	= ( dispidGetParentalCountry + 1 ) ,
    dispidDefaultSubpictureLCID = ( dispidDefaultAudioLCID + 1 ) ,
    dispidDefaultMenuLCID	= ( dispidDefaultSubpictureLCID + 1 ) ,
    dispidBookmarkOnStop	= ( dispidDefaultMenuLCID + 1 ) ,
    dispidMaxVidRect	= ( dispidBookmarkOnStop + 1 ) ,
    dispidMinVidRect	= ( dispidMaxVidRect + 1 ) ,
    dispidCapture	= ( dispidMinVidRect + 1 ) ,
    dispid_DecimateInput	= ( dispidCapture + 1 ) ,
    dispidAlloctor	= ( dispid_DecimateInput + 1 ) ,
    dispid_Allocator	= ( dispidAlloctor + 1 ) ,
    dispidAllocPresentID	= ( dispid_Allocator + 1 ) ,
    dispidSetAllocator	= ( dispidAllocPresentID + 1 ) ,
    dispid_SetAllocator = ( dispidSetAllocator + 1 ) ,
    dispidStreamBufferSinkName	= ( dispid_SetAllocator + 1 ) ,
    dispidStreamBufferSourceName	= ( dispidStreamBufferSinkName + 1 ) ,
    dispidStreamBufferContentRecording	= ( dispidStreamBufferSourceName + 1 ) ,
    dispidStreamBufferReferenceRecording	= ( dispidStreamBufferContentRecording + 1 ) ,
    dispidstarttime	= ( dispidStreamBufferReferenceRecording + 1 ) ,
    dispidstoptime	= ( dispidstarttime + 1 ) ,
    dispidrecordingstopped	= ( dispidstoptime + 1 ) ,
    dispidrecordingstarted	= ( dispidrecordingstopped + 1 ) ,
    dispidNameSetLock	= ( dispidrecordingstarted + 1 ) ,
    dispidrecordingtype = ( dispidNameSetLock + 1 ) ,
    dispidstart = ( dispidrecordingtype + 1 ) ,
    dispidRecordingAttribute	= ( dispidstart + 1 ) ,
    dispid_RecordingAttribute	= ( dispidRecordingAttribute + 1 ) ,
    dispidSBEConfigure	= ( dispid_RecordingAttribute + 1 ) ,
    dispid_CurrentRatings	= ( dispidSBEConfigure + 1 ) ,
    dispid_MaxRatingsLevel	= ( dispid_CurrentRatings + 1 ) ,
    dispid_audioencoderint	= ( dispid_MaxRatingsLevel + 1 ) ,
    dispid_videoencoderint	= ( dispid_audioencoderint + 1 ) ,
    dispidService	= ( dispid_videoencoderint + 1 ) ,
    dispid_BlockUnrated = ( dispidService + 1 ) ,
    dispid_UnratedDelay = ( dispid_BlockUnrated + 1 ) ,
    dispid_SuppressEffects	= ( dispid_UnratedDelay + 1 ) ,
    dispidsbesource	= ( dispid_SuppressEffects + 1 ) ,
    dispidSetSinkFilter = ( dispidsbesource + 1 ) ,
    dispid_SinkStreams	= ( dispidSetSinkFilter + 1 ) ,
    dispidTVFormats	= ( dispid_SinkStreams + 1 ) ,
    dispidModes = ( dispidTVFormats + 1 ) ,
    dispidAuxInputs	= ( dispidModes + 1 ) ,
    dispidTeleTextFilter	= ( dispidAuxInputs + 1 ) ,
    dispid_channelchangeint	= ( dispidTeleTextFilter + 1 ) ,
    dispidUnlockProfile = ( dispid_channelchangeint + 1 ) ,
    dispid_AddFilter	= ( dispidUnlockProfile + 1 ) ,
    dispidSetMinSeek	= ( dispid_AddFilter + 1 ) ,
    dispidRateEx	= ( dispidSetMinSeek + 1 ) ,
    dispidaudiocounter	= ( dispidRateEx + 1 ) ,
    dispidvideocounter	= ( dispidaudiocounter + 1 ) ,
    dispidcccounter	= ( dispidvideocounter + 1 ) ,
    dispidwstcounter	= ( dispidcccounter + 1 ) ,
    dispid_audiocounter = ( dispidwstcounter + 1 ) ,
    dispid_videocounter = ( dispid_audiocounter + 1 ) ,
    dispid_cccounter	= ( dispid_videocounter + 1 ) ,
    dispid_wstcounter	= ( dispid_cccounter + 1 ) ,
    dispidaudioanalysis = ( dispid_wstcounter + 1 ) ,
    dispidvideoanalysis = ( dispidaudioanalysis + 1 ) ,
    dispiddataanalysis	= ( dispidvideoanalysis + 1 ) ,
    dispidaudio_analysis	= ( dispiddataanalysis + 1 ) ,
    dispidvideo_analysis	= ( dispidaudio_analysis + 1 ) ,
    dispiddata_analysis = ( dispidvideo_analysis + 1 ) ,
    dispid_resetFilterList	= ( dispiddata_analysis + 1 ) ,
    dispidDevicePath	= ( dispid_resetFilterList + 1 ) ,
    dispid_SourceFilter = ( dispidDevicePath + 1 ) ,
    dispid__SourceFilter	= ( dispid_SourceFilter + 1 ) ,
    dispidUserEvent	= ( dispid__SourceFilter + 1 ) ,
    dispid_Bookmark	= ( dispidUserEvent + 1 ) ,
    LastReservedDeviceDispid	= 0x3fff
    }

.enum SegEventidList {
    eventidStateChange	= 0,
    eventidOnTuneChanged	= ( eventidStateChange + 1 ) ,
    eventidEndOfMedia	= ( eventidOnTuneChanged + 1 ) ,
    eventidDVDNotify	= ( eventidEndOfMedia + 1 ) ,
    eventidPlayForwards = ( eventidDVDNotify + 1 ) ,
    eventidPlayBackwards	= ( eventidPlayForwards + 1 ) ,
    eventidShowMenu	= ( eventidPlayBackwards + 1 ) ,
    eventidResume	= ( eventidShowMenu + 1 ) ,
    eventidSelectOrActivateButton	= ( eventidResume + 1 ) ,
    eventidStillOff	= ( eventidSelectOrActivateButton + 1 ) ,
    eventidPauseOn	= ( eventidStillOff + 1 ) ,
    eventidChangeCurrentAudioStream	= ( eventidPauseOn + 1 ) ,
    eventidChangeCurrentSubpictureStream	= ( eventidChangeCurrentAudioStream + 1 ) ,
    eventidChangeCurrentAngle	= ( eventidChangeCurrentSubpictureStream + 1 ) ,
    eventidPlayAtTimeInTitle	= ( eventidChangeCurrentAngle + 1 ) ,
    eventidPlayAtTime	= ( eventidPlayAtTimeInTitle + 1 ) ,
    eventidPlayChapterInTitle	= ( eventidPlayAtTime + 1 ) ,
    eventidPlayChapter	= ( eventidPlayChapterInTitle + 1 ) ,
    eventidReplayChapter	= ( eventidPlayChapter + 1 ) ,
    eventidPlayNextChapter	= ( eventidReplayChapter + 1 ) ,
    eventidStop = ( eventidPlayNextChapter + 1 ) ,
    eventidReturnFromSubmenu	= ( eventidStop + 1 ) ,
    eventidPlayTitle	= ( eventidReturnFromSubmenu + 1 ) ,
    eventidPlayPrevChapter	= ( eventidPlayTitle + 1 ) ,
    eventidChangeKaraokePresMode	= ( eventidPlayPrevChapter + 1 ) ,
    eventidChangeVideoPresMode	= ( eventidChangeKaraokePresMode + 1 ) ,
    eventidOverlayUnavailable	= ( eventidChangeVideoPresMode + 1 ) ,
    eventidSinkCertificateFailure	= ( eventidOverlayUnavailable + 1 ) ,
    eventidSinkCertificateSuccess	= ( eventidSinkCertificateFailure + 1 ) ,
    eventidSourceCertificateFailure	= ( eventidSinkCertificateSuccess + 1 ) ,
    eventidSourceCertificateSuccess	= ( eventidSourceCertificateFailure + 1 ) ,
    eventidRatingsBlocked	= ( eventidSourceCertificateSuccess + 1 ) ,
    eventidRatingsUnlocked	= ( eventidRatingsBlocked + 1 ) ,
    eventidRatingsChanged	= ( eventidRatingsUnlocked + 1 ) ,
    eventidWriteFailure = ( eventidRatingsChanged + 1 ) ,
    eventidTimeHole	= ( eventidWriteFailure + 1 ) ,
    eventidStaleDataRead	= ( eventidTimeHole + 1 ) ,
    eventidContentBecomingStale = ( eventidStaleDataRead + 1 ) ,
    eventidStaleFileDeleted	= ( eventidContentBecomingStale + 1 ) ,
    eventidEncryptionOn = ( eventidStaleFileDeleted + 1 ) ,
    eventidEncryptionOff	= ( eventidEncryptionOn + 1 ) ,
    eventidRateChange	= ( eventidEncryptionOff + 1 ) ,
    eventidLicenseChange	= ( eventidRateChange + 1 ) ,
    eventidCOPPBlocked	= ( eventidLicenseChange + 1 ) ,
    eventidCOPPUnblocked	= ( eventidCOPPBlocked + 1 ) ,
    dispidlicenseerrorcode	= ( eventidCOPPUnblocked + 1 ) ,
    eventidBroadcastEvent	= ( dispidlicenseerrorcode + 1 ) ,
    eventidBroadcastEventEx	= ( eventidBroadcastEvent + 1 ) ,
    eventidContentPrimarilyAudio	= ( eventidBroadcastEventEx + 1 ) ,
    dispidAVDecAudioDualMonoEvent	= ( eventidContentPrimarilyAudio + 1 ) ,
    dispidAVAudioSampleRateEvent	= ( dispidAVDecAudioDualMonoEvent + 1 ) ,
    dispidAVAudioChannelConfigEvent	= ( dispidAVAudioSampleRateEvent + 1 ) ,
    dispidAVAudioChannelCountEvent	= ( dispidAVAudioChannelConfigEvent + 1 ) ,
    dispidAVDecCommonMeanBitRateEvent	= ( dispidAVAudioChannelCountEvent + 1 ) ,
    dispidAVDDSurroundModeEvent = ( dispidAVDecCommonMeanBitRateEvent + 1 ) ,
    dispidAVDecCommonInputFormatEvent	= ( dispidAVDDSurroundModeEvent + 1 ) ,
    dispidAVDecCommonOutputFormatEvent	= ( dispidAVDecCommonInputFormatEvent + 1 ) ,
    eventidWriteFailureClear	= ( dispidAVDecCommonOutputFormatEvent + 1 ) ,
    LastReservedDeviceEvent	= 0x3fff
    }

.enum PositionModeList {
    FrameMode	= 0,
    TenthsSecondsMode	= ( FrameMode + 1 )
    }

.enum RecordingType {
    CONTENT	= 0,
    REFERENCE	= ( CONTENT + 1 )
    }

.enum MSVidCCService {
    None	= 0,
    Caption1	= ( None + 1 ) ,
    Caption2	= ( Caption1 + 1 ) ,
    Text1	= ( Caption2 + 1 ) ,
    Text2	= ( Text1 + 1 ) ,
    XDS = ( Text2 + 1 )
    }

.enum MSVidSinkStreams {
    MSVidSink_Video	= 1,
    MSVidSink_Audio	= 2,
    MSVidSink_Other	= 4
    }

ifndef __IMSVidRect_INTERFACE_DEFINED__
define __IMSVidRect_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidRect, "7F5000A6-A440-47ca-8ACC-C0E75531A2C2")

.comdef IMSVidRect : public IDispatch

    get_Top		proc :ptr LONG
    put_Top		proc :LONG
    get_Left		proc :ptr LONG
    put_Left		proc :LONG
    get_Width		proc :ptr LONG
    put_Width		proc :LONG
    get_Height		proc :ptr LONG
    put_Height		proc :LONG
    get_HWnd		proc :ptr HWND
    put_HWnd		proc :HWND
    put_Rect		proc :ptr IMSVidRect
   .ends

endif

ifndef __IMSVidGraphSegmentContainer_INTERFACE_DEFINED__
define __IMSVidGraphSegmentContainer_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidGraphSegmentContainer, "3DD2903D-E0AA-11d2-B63A-00C04F79498E")

.comdef IMSVidGraphSegmentContainer : public IUnknown

    get_Graph		proc :ptr ptr
    get_Input		proc :ptr ptr
    get_Outputs		proc :ptr ptr
    get_VideoRenderer	proc :ptr ptr
    get_AudioRenderer	proc :ptr ptr
    get_Features	proc :ptr ptr
    get_Composites	proc :ptr ptr
    get_ParentContainer proc :ptr ptr
    Decompose		proc :ptr
    IsWindowless	proc
    GetFocus		proc
   .ends

endif

.enum MSVidSegmentType {
    MSVidSEG_SOURCE	= 0,
    MSVidSEG_XFORM	= ( MSVidSEG_SOURCE + 1 ) ,
    MSVidSEG_DEST	= ( MSVidSEG_XFORM + 1 )
    }

ifndef __IMSVidGraphSegment_INTERFACE_DEFINED__
define __IMSVidGraphSegment_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidGraphSegment, "238DEC54-ADEB-4005-A349-F772B9AFEBC4")

.comdef IMSVidGraphSegment : public IPersist

    get_Init		proc :ptr ptr IUnknown
    put_Init		proc :ptr IUnknown
    EnumFilters		proc :ptr ptr IEnumFilters
    get_Container	proc :ptr ptr IMSVidGraphSegmentContainer
    put_Container	proc :ptr IMSVidGraphSegmentContainer
    get_Type		proc :ptr MSVidSegmentType
    get_Category	proc :ptr GUID
    Build		proc
    PostBuild		proc
    PreRun		proc
    PostRun		proc
    PreStop		proc
    PostStop		proc
    OnEventNotify	proc :LONG, :LONG_PTR, :LONG_PTR
    Decompose		proc
   .ends

endif

.enum MSVidCtlButtonstate {
    MSVIDCTL_LEFT_BUTTON	= 0x1,
    MSVIDCTL_RIGHT_BUTTON	= 0x2,
    MSVIDCTL_MIDDLE_BUTTON	= 0x4,
    MSVIDCTL_X_BUTTON1	= 0x8,
    MSVIDCTL_X_BUTTON2	= 0x10,
    MSVIDCTL_SHIFT	= 0x1,
    MSVIDCTL_CTRL	= 0x2,
    MSVIDCTL_ALT	= 0x4
    }


ifndef __IMSVidGraphSegmentUserInput_INTERFACE_DEFINED__
define __IMSVidGraphSegmentUserInput_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidGraphSegmentUserInput, "301C060E-20D9-4587-9B03-F82ED9A9943C")

.comdef IMSVidGraphSegmentUserInput : public IUnknown

    Click		proc
    DblClick		proc
    KeyDown		proc :ptr, :sword
    KeyPress		proc :ptr
    KeyUp		proc :ptr, :sword
    MouseDown		proc :sword, :sword, :OLE_XPOS_PIXELS, :OLE_YPOS_PIXELS
    MouseMove		proc :sword, :sword, :OLE_XPOS_PIXELS, :OLE_YPOS_PIXELS
    MouseUp		proc :sword, :sword, :OLE_XPOS_PIXELS, :OLE_YPOS_PIXELS
   .ends

endif

ifndef __IMSVidCompositionSegment_INTERFACE_DEFINED__
define __IMSVidCompositionSegment_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidCompositionSegment, "1C15D483-911D-11d2-B632-00C04F79498E")

.comdef IMSVidCompositionSegment : public IMSVidGraphSegment

    Compose		proc :ptr, :ptr
    get_Up		proc :ptr ptr IMSVidGraphSegment
    get_Down		proc :ptr ptr IMSVidGraphSegment
   .ends

endif

ifndef __IEnumMSVidGraphSegment_INTERFACE_DEFINED__
define __IEnumMSVidGraphSegment_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumMSVidGraphSegment, "3DD2903E-E0AA-11d2-B63A-00C04F79498E")

.comdef IEnumMSVidGraphSegment : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IMSVidVRGraphSegment_INTERFACE_DEFINED__
define __IMSVidVRGraphSegment_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVRGraphSegment, "DD47DE3F-9874-4f7b-8B22-7CB2688461E7")

.comdef IMSVidVRGraphSegment : public IMSVidGraphSegment

    put__VMRendererMode proc :LONG
    put_Owner		proc :HWND
    get_Owner		proc :ptr HWND
    get_UseOverlay	proc :ptr VARIANT_BOOL
    put_UseOverlay	proc :VARIANT_BOOL
    get_Visible		proc :ptr VARIANT_BOOL
    put_Visible		proc :VARIANT_BOOL
    get_ColorKey	proc :ptr OLE_COLOR
    put_ColorKey	proc :OLE_COLOR
    get_Source		proc :LPRECT
    put_Source		proc :RECT
    get_Destination	proc :LPRECT
    put_Destination	proc :RECT
    get_NativeSize	proc :LPSIZE, :LPSIZE
    get_BorderColor	proc :ptr OLE_COLOR
    put_BorderColor	proc :OLE_COLOR
    get_MaintainAspectRatio proc :ptr VARIANT_BOOL
    put_MaintainAspectRatio proc :VARIANT_BOOL
    Refresh		proc
    DisplayChange	proc
    RePaint		proc :HDC
   .ends

endif

ifndef __IMSVidDevice_INTERFACE_DEFINED__
define __IMSVidDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidDevice, "1C15D47C-911D-11d2-B632-00C04F79498E")

.comdef IMSVidDevice : public IDispatch

    get_Name		proc :ptr BSTR
    get_Status		proc :ptr
    put_Power		proc :VARIANT_BOOL
    get_Power		proc :ptr VARIANT_BOOL
    get_Category	proc :ptr BSTR
    get_ClassID		proc :ptr BSTR
    get__Category	proc :ptr GUID
    get__ClassID	proc :ptr GUID
    IsEqualDevice	proc :ptr IMSVidDevice, :ptr VARIANT_BOOL
   .ends

endif

ifndef __IMSVidDevice2_INTERFACE_DEFINED__
define __IMSVidDevice2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidDevice2, "87BD2783-EBC0-478C-B4A0-E8E7F43AB78E")

.comdef IMSVidDevice2 : public IUnknown

    get_DevicePath	proc :ptr BSTR
   .ends

endif

ifndef __IMSVidInputDevice_INTERFACE_DEFINED__
define __IMSVidInputDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidInputDevice, "37B0353D-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidInputDevice : public IMSVidDevice

    IsViewable		proc :ptr VARIANT, :ptr VARIANT_BOOL
    View		proc :ptr VARIANT
   .ends

endif

ifndef __IMSVidDeviceEvent_INTERFACE_DEFINED__
define __IMSVidDeviceEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidDeviceEvent, "1C15D480-911D-11d2-B632-00C04F79498E")

.comdef IMSVidDeviceEvent : public IDispatch

    StateChange		proc :ptr IMSVidDevice, :LONG, :LONG
   .ends

endif

ifndef __IMSVidInputDeviceEvent_INTERFACE_DEFINED__
define __IMSVidInputDeviceEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidInputDeviceEvent, "37B0353E-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidInputDeviceEvent : public IDispatch

    .ends

endif

ifndef __IMSVidVideoInputDevice_INTERFACE_DEFINED__
define __IMSVidVideoInputDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVideoInputDevice, "1C15D47F-911D-11d2-B632-00C04F79498E")

.comdef IMSVidVideoInputDevice : public IMSVidInputDevice

    .ends

endif

ifndef __IMSVidPlayback_INTERFACE_DEFINED__
define __IMSVidPlayback_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidPlayback, "37B03538-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidPlayback : public IMSVidInputDevice

    get_EnableResetOnStop proc :ptr VARIANT_BOOL
    put_EnableResetOnStop proc :VARIANT_BOOL
    Run			proc
    _Pause		proc
    Stop		proc
    get_CanStep		proc :VARIANT_BOOL, :ptr VARIANT_BOOL
    Step		proc :LONG
    put_Rate		proc :real8
    get_Rate		proc :ptr real8
    put_CurrentPosition proc :LONG
    get_CurrentPosition proc :ptr LONG
    put_PositionMode	proc :PositionModeList
    get_PositionMode	proc :ptr PositionModeList
    get_Length		proc :ptr LONG
   .ends

endif

ifndef __IMSVidPlaybackEvent_INTERFACE_DEFINED__
define __IMSVidPlaybackEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidPlaybackEvent, "37B0353B-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidPlaybackEvent : public IMSVidInputDeviceEvent

    EndOfMedia		proc :ptr IMSVidPlayback
   .ends

endif

ifndef __IMSVidTuner_INTERFACE_DEFINED__
define __IMSVidTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidTuner, "1C15D47D-911D-11d2-B632-00C04F79498E")

.comdef IMSVidTuner : public IMSVidVideoInputDevice

    get_Tune		proc :ptr ptr ITuneRequest
    put_Tune		proc :ptr ITuneRequest
    get_TuningSpace	proc :ptr ptr ITuningSpace
    put_TuningSpace	proc :ptr ITuningSpace
   .ends

endif

ifndef __IMSVidTunerEvent_INTERFACE_DEFINED__
define __IMSVidTunerEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidTunerEvent, "1C15D485-911D-11d2-B632-00C04F79498E")

.comdef IMSVidTunerEvent : public IMSVidInputDeviceEvent

    TuneChanged		proc :ptr IMSVidTuner
   .ends

endif

ifndef __IMSVidAnalogTuner_INTERFACE_DEFINED__
define __IMSVidAnalogTuner_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidAnalogTuner, "1C15D47E-911D-11d2-B632-00C04F79498E")

.comdef IMSVidAnalogTuner : public IMSVidTuner

    get_Channel		proc :ptr LONG
    put_Channel		proc :LONG
    get_VideoFrequency	proc :ptr LONG
    get_AudioFrequency	proc :ptr LONG
    get_CountryCode	proc :ptr LONG
    put_CountryCode	proc :LONG
    get_SAP		proc :ptr VARIANT_BOOL
    put_SAP		proc :VARIANT_BOOL
    ChannelAvailable	proc :LONG, :ptr LONG, :ptr VARIANT_BOOL
   .ends

endif

ifndef __IMSVidAnalogTuner2_INTERFACE_DEFINED__
define __IMSVidAnalogTuner2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidAnalogTuner2, "37647BF7-3DDE-4cc8-A4DC-0D534D3D0037")

.comdef IMSVidAnalogTuner2 : public IMSVidAnalogTuner

    get_TVFormats	proc :ptr LONG
    get_TunerModes	proc :ptr LONG
    get_NumAuxInputs	proc :ptr LONG
   .ends

endif

ifndef __IMSVidAnalogTunerEvent_INTERFACE_DEFINED__
define __IMSVidAnalogTunerEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidAnalogTunerEvent, "1C15D486-911D-11d2-B632-00C04F79498E")

.comdef IMSVidAnalogTunerEvent : public IMSVidTunerEvent

    .ends

endif

ifndef __IMSVidFilePlayback_INTERFACE_DEFINED__
define __IMSVidFilePlayback_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidFilePlayback, "37B03539-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidFilePlayback : public IMSVidPlayback

    get_FileName	proc :ptr BSTR
    put_FileName	proc :BSTR
   .ends

endif

ifndef __IMSVidFilePlayback2_INTERFACE_DEFINED__
define __IMSVidFilePlayback2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidFilePlayback2, "2F7E44AF-6E52-4660-BC08-D8D542587D72")

.comdef IMSVidFilePlayback2 : public IMSVidFilePlayback

    put__SourceFilter	proc :BSTR
    put___SourceFilter	proc :ptr GUID
   .ends

endif

ifndef __IMSVidFilePlaybackEvent_INTERFACE_DEFINED__
define __IMSVidFilePlaybackEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidFilePlaybackEvent, "37B0353A-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidFilePlaybackEvent : public IMSVidPlaybackEvent

    .ends

endif

.enum DVDMenuIDConstants {
    dvdMenu_Title	= 2,
    dvdMenu_Root	= ( dvdMenu_Title + 1 ) ,
    dvdMenu_Subpicture	= ( dvdMenu_Root + 1 ) ,
    dvdMenu_Audio	= ( dvdMenu_Subpicture + 1 ) ,
    dvdMenu_Angle	= ( dvdMenu_Audio + 1 ) ,
    dvdMenu_Chapter	= ( dvdMenu_Angle + 1 )
    }

.enum DVDFilterState {
    dvdState_Undefined	= -2,
    dvdState_Unitialized = -1,
    dvdState_Stopped	= 0,
    dvdState_Paused	= ( dvdState_Stopped + 1 ),
    dvdState_Running	= ( dvdState_Paused + 1 )
    }

.enum DVDTextStringType {
    dvdStruct_Volume	= 0x1,
    dvdStruct_Title	= 0x2,
    dvdStruct_ParentalID	= 0x3,
    dvdStruct_PartOfTitle	= 0x4,
    dvdStruct_Cell	= 0x5,
    dvdStream_Audio	= 0x10,
    dvdStream_Subpicture	= 0x11,
    dvdStream_Angle	= 0x12,
    dvdChannel_Audio	= 0x20,
    dvdGeneral_Name	= 0x30,
    dvdGeneral_Comments = 0x31,
    dvdTitle_Series	= 0x38,
    dvdTitle_Movie	= 0x39,
    dvdTitle_Video	= 0x3a,
    dvdTitle_Album	= 0x3b,
    dvdTitle_Song	= 0x3c,
    dvdTitle_Other	= 0x3f,
    dvdTitle_Sub_Series = 0x40,
    dvdTitle_Sub_Movie	= 0x41,
    dvdTitle_Sub_Video	= 0x42,
    dvdTitle_Sub_Album	= 0x43,
    dvdTitle_Sub_Song	= 0x44,
    dvdTitle_Sub_Other	= 0x47,
    dvdTitle_Orig_Series	= 0x48,
    dvdTitle_Orig_Movie = 0x49,
    dvdTitle_Orig_Video = 0x4a,
    dvdTitle_Orig_Album = 0x4b,
    dvdTitle_Orig_Song	= 0x4c,
    dvdTitle_Orig_Other = 0x4f,
    dvdOther_Scene	= 0x50,
    dvdOther_Cut	= 0x51,
    dvdOther_Take	= 0x52
    }

.enum DVDSPExt {
    dvdSPExt_NotSpecified	= 0,
    dvdSPExt_Caption_Normal	= 1,
    dvdSPExt_Caption_Big	= 2,
    dvdSPExt_Caption_Children	= 3,
    dvdSPExt_CC_Normal	= 5,
    dvdSPExt_CC_Big	= 6,
    dvdSPExt_CC_Children	= 7,
    dvdSPExt_Forced	= 9,
    dvdSPExt_DirectorComments_Normal	= 13,
    dvdSPExt_DirectorComments_Big	= 14,
    dvdSPExt_DirectorComments_Children	= 15
    }

ifndef __IMSVidWebDVD_INTERFACE_DEFINED__
define __IMSVidWebDVD_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidWebDVD, "CF45F88B-AC56-4EE2-A73A-ED04E2885D3C")

.comdef IMSVidWebDVD : public IMSVidPlayback

    OnDVDEvent		proc :LONG, :LONG_PTR, :LONG_PTR
    PlayTitle		proc :LONG
    PlayChapterInTitle	proc :LONG, :LONG
    PlayChapter		proc :LONG
    PlayChaptersAutoStop proc :LONG, :LONG, :LONG
    PlayAtTime		proc :BSTR
    PlayAtTimeInTitle	proc :LONG, :BSTR
    PlayPeriodInTitleAutoStop proc :LONG, :BSTR, :BSTR
    ReplayChapter	proc
    PlayPrevChapter	proc
    PlayNextChapter	proc
    StillOff		proc
    get_AudioLanguage	proc :LONG, :VARIANT_BOOL, :ptr BSTR
    ShowMenu		proc :DVDMenuIDConstants
    Resume		proc
    ReturnFromSubmenu	proc
    get_ButtonsAvailable proc :ptr LONG
    get_CurrentButton	proc :ptr LONG
    SelectAndActivateButton proc :LONG
    ActivateButton	proc
    SelectRightButton	proc
    SelectLeftButton	proc
    SelectLowerButton	proc
    SelectUpperButton	proc
    ActivateAtPosition	proc :LONG, :LONG
    SelectAtPosition	proc :LONG, :LONG
    get_ButtonAtPosition proc :LONG, :LONG, :ptr LONG
    get_NumberOfChapters proc :LONG, :ptr LONG
    get_TotalTitleTime	proc :ptr BSTR
    get_TitlesAvailable proc :ptr LONG
    get_VolumesAvailable proc :ptr LONG
    get_CurrentVolume	proc :ptr LONG
    get_CurrentDiscSide proc :ptr LONG
    get_CurrentDomain	proc :ptr LONG
    get_CurrentChapter	proc :ptr LONG
    get_CurrentTitle	proc :ptr LONG
    get_CurrentTime	proc :ptr BSTR
    DVDTimeCode2bstr	proc :LONG, :ptr BSTR
    get_DVDDirectory	proc :ptr BSTR
    put_DVDDirectory	proc :BSTR
    IsSubpictureStreamEnabled proc :LONG, :ptr VARIANT_BOOL
    IsAudioStreamEnabled proc :LONG, :ptr VARIANT_BOOL
    get_CurrentSubpictureStream proc :ptr LONG
    put_CurrentSubpictureStream proc :LONG
    get_SubpictureLanguage proc :LONG, :ptr BSTR
    get_CurrentAudioStream proc :ptr LONG
    put_CurrentAudioStream proc :LONG
    get_AudioStreamsAvailable proc :ptr LONG
    get_AnglesAvailable proc :ptr LONG
    get_CurrentAngle	proc :ptr LONG
    put_CurrentAngle	proc :LONG
    get_SubpictureStreamsAvailable proc :ptr LONG
    get_SubpictureOn	proc :ptr VARIANT_BOOL
    put_SubpictureOn	proc :VARIANT_BOOL
    get_DVDUniqueID	proc :ptr BSTR
    AcceptParentalLevelChange proc :VARIANT_BOOL, :BSTR, :BSTR
    NotifyParentalLevelChange proc :VARIANT_BOOL
    SelectParentalCountry proc :LONG, :BSTR, :BSTR
    SelectParentalLevel proc :LONG, :BSTR, :BSTR
    get_TitleParentalLevels proc :LONG, :ptr LONG
    get_PlayerParentalCountry proc :ptr LONG
    get_PlayerParentalLevel proc :ptr LONG
    Eject		proc
    UOPValid		proc :LONG, :ptr VARIANT_BOOL
    get_SPRM		proc :LONG, :ptr sword
    get_GPRM		proc :LONG, :ptr sword
    put_GPRM		proc :LONG, :sword
    get_DVDTextStringType proc :LONG, :LONG, :ptr DVDTextStringType
    get_DVDTextString	proc :LONG, :LONG, :ptr BSTR
    get_DVDTextNumberOfStrings proc :LONG, :ptr LONG
    get_DVDTextNumberOfLanguages proc :ptr LONG
    get_DVDTextLanguageLCID proc :ptr sword, :ptr LONG
    RegionChange	proc
    get_DVDAdm		proc :ptr ptr IDispatch
    DeleteBookmark	proc
    RestoreBookmark	proc
    SaveBookmark	proc
    SelectDefaultAudioLanguage	proc :LONG, :LONG
    SelectDefaultSubpictureLanguage proc :LONG, :DVDSPExt
    get_PreferredSubpictureStream proc :ptr LONG
    get_DefaultMenuLanguage	proc :ptr LONG
    put_DefaultMenuLanguage	proc :LONG
    get_DefaultSubpictureLanguage proc :ptr LONG
    get_DefaultAudioLanguage	proc :ptr LONG
    get_DefaultSubpictureLanguageExt proc :ptr DVDSPExt
    get_DefaultAudioLanguageExt proc :ptr LONG
    get_LanguageFromLCID	proc :LONG, :ptr BSTR
    get_KaraokeAudioPresentationMode proc :ptr LONG
    put_KaraokeAudioPresentationMode proc :LONG
    get_KaraokeChannelContent	proc :LONG, :LONG, :ptr LONG
    get_KaraokeChannelAssignment proc :LONG, :ptr LONG
    RestorePreferredSettings proc
    get_ButtonRect	proc :LONG, :ptr ptr IMSVidRect
    get_DVDScreenInMouseCoordinates proc :ptr ptr IMSVidRect
    put_DVDScreenInMouseCoordinates proc :ptr IMSVidRect
   .ends

endif

ifndef __IMSVidWebDVD2_INTERFACE_DEFINED__
define __IMSVidWebDVD2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidWebDVD2, "7027212F-EE9A-4a7c-8B67-F023714CDAFF")

.comdef IMSVidWebDVD2 : public IMSVidWebDVD

    get_Bookmark	proc :ptr ptr BYTE, :ptr DWORD
    put_Bookmark	proc :ptr BYTE, :DWORD
   .ends


IMSVidWebDVD2_put_Bookmark_Stub proto __cdecl \
		  This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IMSVidWebDVDEvent_INTERFACE_DEFINED__
define __IMSVidWebDVDEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidWebDVDEvent, "B4F7A674-9B83-49cb-A357-C63B871BE958")

.comdef IMSVidWebDVDEvent : public IMSVidPlaybackEvent

    DVDNotify		proc :LONG, :VARIANT, :VARIANT
    PlayForwards	proc :VARIANT_BOOL
    PlayBackwards	proc :VARIANT_BOOL
    ShowMenu		proc :DVDMenuIDConstants, :VARIANT_BOOL
    Resume		proc :VARIANT_BOOL
    SelectOrActivateButton proc :VARIANT_BOOL
    StillOff		proc :VARIANT_BOOL
    PauseOn		proc :VARIANT_BOOL
    ChangeCurrentAudioStream proc :VARIANT_BOOL
    ChangeCurrentSubpictureStream proc :VARIANT_BOOL
    ChangeCurrentAngle	proc :VARIANT_BOOL
    PlayAtTimeInTitle	proc :VARIANT_BOOL
    PlayAtTime		proc :VARIANT_BOOL
    PlayChapterInTitle	proc :VARIANT_BOOL
    PlayChapter		proc :VARIANT_BOOL
    ReplayChapter	proc :VARIANT_BOOL
    PlayNextChapter	proc :VARIANT_BOOL
    Stop		proc :VARIANT_BOOL
    ReturnFromSubmenu	proc :VARIANT_BOOL
    PlayTitle		proc :VARIANT_BOOL
    PlayPrevChapter	proc :VARIANT_BOOL
    ChangeKaraokePresMode proc :VARIANT_BOOL
    ChangeVideoPresMode proc :VARIANT_BOOL
   .ends

endif

ifndef __IMSVidWebDVDAdm_INTERFACE_DEFINED__
define __IMSVidWebDVDAdm_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidWebDVDAdm, "B8BE681A-EB2C-47f0-B415-94D5452F0E05")

.comdef IMSVidWebDVDAdm : public IDispatch

    ChangePassword	proc :BSTR, :BSTR, :BSTR
    SaveParentalLevel	proc :LONG, :BSTR, :BSTR
    SaveParentalCountry proc :LONG, :BSTR, :BSTR
    ConfirmPassword	proc :BSTR, :BSTR, :ptr VARIANT_BOOL
    GetParentalLevel	proc :ptr LONG
    GetParentalCountry	proc :ptr LONG
    get_DefaultAudioLCID proc :ptr LONG
    put_DefaultAudioLCID proc :LONG
    get_DefaultSubpictureLCID proc :ptr LONG
    put_DefaultSubpictureLCID proc :LONG
    get_DefaultMenuLCID proc :ptr LONG
    put_DefaultMenuLCID proc :LONG
    get_BookmarkOnStop	proc :ptr VARIANT_BOOL
    put_BookmarkOnStop	proc :VARIANT_BOOL
   .ends

endif

ifndef __IMSVidOutputDevice_INTERFACE_DEFINED__
define __IMSVidOutputDevice_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidOutputDevice, "37B03546-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidOutputDevice : public IMSVidDevice

    .ends

endif

ifndef __IMSVidOutputDeviceEvent_INTERFACE_DEFINED__
define __IMSVidOutputDeviceEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidOutputDeviceEvent, "2E6A14E2-571C-11d3-B652-00C04F79498E")

.comdef IMSVidOutputDeviceEvent : public IMSVidDeviceEvent

    .ends

endif

ifndef __IMSVidFeature_INTERFACE_DEFINED__
define __IMSVidFeature_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidFeature, "37B03547-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidFeature : public IMSVidDevice

    .ends

endif

ifndef __IMSVidFeatureEvent_INTERFACE_DEFINED__
define __IMSVidFeatureEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidFeatureEvent, "3DD2903C-E0AA-11d2-B63A-00C04F79498E")

.comdef IMSVidFeatureEvent : public IMSVidDeviceEvent

    .ends

endif

ifndef __IMSVidEncoder_INTERFACE_DEFINED__
define __IMSVidEncoder_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidEncoder, "C0020FD4-BEE7-43d9-A495-9F213117103D")

.comdef IMSVidEncoder : public IMSVidFeature

    get_VideoEncoderInterface proc :ptr ptr IUnknown
    get_AudioEncoderInterface proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidClosedCaptioning_INTERFACE_DEFINED__
define __IMSVidClosedCaptioning_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidClosedCaptioning, "99652EA1-C1F7-414f-BB7B-1C967DE75983")

.comdef IMSVidClosedCaptioning : public IMSVidFeature

    get_Enable		proc :ptr VARIANT_BOOL
    put_Enable		proc :VARIANT_BOOL
   .ends

endif

ifndef __IMSVidClosedCaptioning2_INTERFACE_DEFINED__
define __IMSVidClosedCaptioning2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidClosedCaptioning2, "E00CB864-A029-4310-9987-A873F5887D97")

.comdef IMSVidClosedCaptioning2 : public IMSVidClosedCaptioning

    get_Service		proc :ptr MSVidCCService
    put_Service		proc :MSVidCCService
   .ends

endif

ifndef __IMSVidClosedCaptioning3_INTERFACE_DEFINED__
define __IMSVidClosedCaptioning3_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidClosedCaptioning3, "C8638E8A-7625-4c51-9366-2F40A9831FC0")

.comdef IMSVidClosedCaptioning3 : public IMSVidClosedCaptioning2

    get_TeleTextFilter	proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidXDS_INTERFACE_DEFINED__
define __IMSVidXDS_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidXDS, "11EBC158-E712-4d1f-8BB3-01ED5274C4CE")

.comdef IMSVidXDS : public IMSVidFeature

    get_ChannelChangeInterface proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidXDSEvent_INTERFACE_DEFINED__
define __IMSVidXDSEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidXDSEvent, "6DB2317D-3B23-41ec-BA4B-701F407EAF3A")

.comdef IMSVidXDSEvent : public IMSVidFeatureEvent

    RatingChange	proc :EnTvRat_System, :EnTvRat_GenericLevel, :BfEnTvRat_GenericAttributes,
			     :EnTvRat_System, :EnTvRat_GenericLevel, :BfEnTvRat_GenericAttributes
    .ends

endif

ifndef __IMSVidDataServices_INTERFACE_DEFINED__
define __IMSVidDataServices_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidDataServices, "334125C1-77E5-11d3-B653-00C04F79498E")

.comdef IMSVidDataServices : public IMSVidFeature

    .ends

endif

ifndef __IMSVidDataServicesEvent_INTERFACE_DEFINED__
define __IMSVidDataServicesEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidDataServicesEvent, "334125C2-77E5-11d3-B653-00C04F79498E")

.comdef IMSVidDataServicesEvent : public IMSVidDeviceEvent

    .ends

endif

.enum SourceSizeList {
    sslFullSize = 0,
    sslClipByOverScan	= ( sslFullSize + 1 ) ,
    sslClipByClipRect	= ( sslClipByOverScan + 1 )
    }

ifndef __IMSVidVideoRenderer_INTERFACE_DEFINED__
define __IMSVidVideoRenderer_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVideoRenderer, "37B03540-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidVideoRenderer : public IMSVidOutputDevice

    get_CustomCompositorClass proc :ptr BSTR
    put_CustomCompositorClass proc :BSTR
    get__CustomCompositorClass proc :ptr GUID
    put__CustomCompositorClass proc :REFCLSID
    get__CustomCompositor proc :ptr ptr IVMRImageCompositor
    put__CustomCompositor proc :ptr IVMRImageCompositor
    get_MixerBitmap	proc :ptr ptr IPictureDisp
    get__MixerBitmap	proc :ptr ptr IVMRMixerBitmap
    put_MixerBitmap	proc :ptr IPictureDisp
    put__MixerBitmap	proc :ptr VMRALPHABITMAP
    get_MixerBitmapPositionRect proc :ptr ptr IMSVidRect
    put_MixerBitmapPositionRect proc :ptr IMSVidRect
    get_MixerBitmapOpacity proc :ptr SINT
    put_MixerBitmapOpacity proc :SINT
    SetupMixerBitmap	proc :ptr IPictureDisp, :LONG, :ptr IMSVidRect
    get_SourceSize	proc :ptr SourceSizeList
    put_SourceSize	proc :SourceSizeList
    get_OverScan	proc :ptr LONG
    put_OverScan	proc :LONG
    get_AvailableSourceRect proc :ptr ptr IMSVidRect
    get_MaxVidRect	proc :ptr ptr IMSVidRect
    get_MinVidRect	proc :ptr ptr IMSVidRect
    get_ClippedSourceRect proc :ptr ptr IMSVidRect
    put_ClippedSourceRect proc :ptr IMSVidRect
    get_UsingOverlay	proc :ptr VARIANT_BOOL
    put_UsingOverlay	proc :VARIANT_BOOL
    Capture		proc :ptr ptr IPictureDisp
    get_FramesPerSecond proc :ptr LONG
    get_DecimateInput	proc :ptr VARIANT_BOOL
    put_DecimateInput	proc :VARIANT_BOOL
   .ends

endif

ifndef __IMSVidVideoRendererEvent_INTERFACE_DEFINED__
define __IMSVidVideoRendererEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVideoRendererEvent, "37B03545-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidVideoRendererEvent : public IMSVidOutputDeviceEvent

    OverlayUnavailable	proc
   .ends

endif

ifndef __IMSVidGenericSink_INTERFACE_DEFINED__
define __IMSVidGenericSink_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidGenericSink, "6C29B41D-455B-4c33-963A-0D28E5E555EA")

.comdef IMSVidGenericSink : public IMSVidOutputDevice

    SetSinkFilter	proc :BSTR
    get_SinkStreams	proc :ptr MSVidSinkStreams
    put_SinkStreams	proc :MSVidSinkStreams
   .ends

endif

ifndef __IMSVidGenericSink2_INTERFACE_DEFINED__
define __IMSVidGenericSink2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidGenericSink2, "6B5A28F3-47F1-4092-B168-60CABEC08F1C")

.comdef IMSVidGenericSink2 : public IMSVidGenericSink

    AddFilter		proc :BSTR
    ResetFilterList	proc
   .ends

endif

ifndef __IMSVidStreamBufferRecordingControl_INTERFACE_DEFINED__
define __IMSVidStreamBufferRecordingControl_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferRecordingControl, "160621AA-BBBC-4326-A824-C395AEBC6E74")

.comdef IMSVidStreamBufferRecordingControl : public IDispatch

    get_StartTime	proc :ptr LONG
    put_StartTime	proc :LONG
    get_StopTime	proc :ptr LONG
    put_StopTime	proc :LONG
    get_RecordingStopped proc :ptr VARIANT_BOOL
    get_RecordingStarted proc :ptr VARIANT_BOOL
    get_RecordingType	proc :ptr RecordingType
    get_RecordingAttribute proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidStreamBufferSink_INTERFACE_DEFINED__
define __IMSVidStreamBufferSink_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSink, "159DBB45-CD1B-4dab-83EA-5CB1F4F21D07")

.comdef IMSVidStreamBufferSink : public IMSVidOutputDevice

    get_ContentRecorder proc :BSTR, :ptr ptr IMSVidStreamBufferRecordingControl
    get_ReferenceRecorder proc :BSTR, :ptr ptr IMSVidStreamBufferRecordingControl
    get_SinkName	proc :ptr BSTR
    put_SinkName	proc :BSTR
    NameSetLock		proc
    get_SBESink		proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidStreamBufferSink2_INTERFACE_DEFINED__
define __IMSVidStreamBufferSink2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSink2, "2CA9FC63-C131-4E5A-955A-544A47C67146")

.comdef IMSVidStreamBufferSink2 : public IMSVidStreamBufferSink

    UnlockProfile	proc
   .ends

endif

ifndef __IMSVidStreamBufferSink3_INTERFACE_DEFINED__
define __IMSVidStreamBufferSink3_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSink3, "4F8721D7-7D59-4D8B-99F5-A77775586BD5")

.comdef IMSVidStreamBufferSink3 : public IMSVidStreamBufferSink2

    SetMinSeek		proc :ptr LONG
    get_AudioCounter	proc :ptr ptr IUnknown
    get_VideoCounter	proc :ptr ptr IUnknown
    get_CCCounter	proc :ptr ptr IUnknown
    get_WSTCounter	proc :ptr ptr IUnknown
    put_AudioAnalysisFilter proc :BSTR
    get_AudioAnalysisFilter proc :ptr BSTR
    put__AudioAnalysisFilter proc :ptr GUID
    get__AudioAnalysisFilter proc :ptr GUID
    put_VideoAnalysisFilter proc :BSTR
    get_VideoAnalysisFilter proc :ptr BSTR
    put__VideoAnalysisFilter proc :ptr GUID
    get__VideoAnalysisFilter proc :ptr GUID
    put_DataAnalysisFilter proc :BSTR
    get_DataAnalysisFilter proc :ptr BSTR
    put__DataAnalysisFilter proc :ptr GUID
    get__DataAnalysisFilter proc :ptr GUID
    get_LicenseErrorCode proc :ptr HRESULT
   .ends

endif

ifndef __IMSVidStreamBufferSinkEvent_INTERFACE_DEFINED__
define __IMSVidStreamBufferSinkEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSinkEvent, "F798A36B-B05B-4bbe-9703-EAEA7D61CD51")

.comdef IMSVidStreamBufferSinkEvent : public IMSVidOutputDeviceEvent

    CertificateFailure	proc
    CertificateSuccess	proc
    WriteFailure	proc
   .ends

endif

ifndef __IMSVidStreamBufferSinkEvent2_INTERFACE_DEFINED__
define __IMSVidStreamBufferSinkEvent2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSinkEvent2, "3D7A5166-72D7-484b-A06F-286187B80CA1")

.comdef IMSVidStreamBufferSinkEvent2 : public IMSVidStreamBufferSinkEvent

    EncryptionOn	proc
    EncryptionOff	proc
   .ends

endif

ifndef __IMSVidStreamBufferSinkEvent3_INTERFACE_DEFINED__
define __IMSVidStreamBufferSinkEvent3_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSinkEvent3, "735AD8D5-C259-48e9-81E7-D27953665B23")

.comdef IMSVidStreamBufferSinkEvent3 : public IMSVidStreamBufferSinkEvent2

    LicenseChange	proc :LONG
   .ends

endif

ifndef __IMSVidStreamBufferSinkEvent4_INTERFACE_DEFINED__
define __IMSVidStreamBufferSinkEvent4_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSinkEvent4, "1B01DCB0-DAF0-412c-A5D1-590C7F62E2B8")

.comdef IMSVidStreamBufferSinkEvent4 : public IMSVidStreamBufferSinkEvent3

    WriteFailureClear	proc
   .ends

endif

ifndef __IMSVidStreamBufferSource_INTERFACE_DEFINED__
define __IMSVidStreamBufferSource_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSource, "EB0C8CF9-6950-4772-87B1-47D11CF3A02F")

.comdef IMSVidStreamBufferSource : public IMSVidFilePlayback

    get_Start		proc :ptr LONG
    get_RecordingAttribute proc :ptr ptr IUnknown
    CurrentRatings	proc :ptr EnTvRat_System, :ptr EnTvRat_GenericLevel, :ptr LONG
    MaxRatingsLevel	proc :EnTvRat_System, :EnTvRat_GenericLevel, :LONG
    put_BlockUnrated	proc :VARIANT_BOOL
    put_UnratedDelay	proc :LONG
    get_SBESource	proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidStreamBufferSource2_INTERFACE_DEFINED__
define __IMSVidStreamBufferSource2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSource2, "E4BA9059-B1CE-40D8-B9A0-D4EA4A9989D3")

.comdef IMSVidStreamBufferSource2 : public IMSVidStreamBufferSource

    put_RateEx		proc :real8, :DWORD
    get_AudioCounter	proc :ptr ptr IUnknown
    get_VideoCounter	proc :ptr ptr IUnknown
    get_CCCounter	proc :ptr ptr IUnknown
    get_WSTCounter	proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidStreamBufferSourceEvent_INTERFACE_DEFINED__
define __IMSVidStreamBufferSourceEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSourceEvent, "50CE8A7D-9C28-4DA8-9042-CDFA7116F979")

.comdef IMSVidStreamBufferSourceEvent : public IMSVidFilePlaybackEvent

    CertificateFailure	proc
    CertificateSuccess	proc
    RatingsBlocked	proc
    RatingsUnblocked	proc
    RatingsChanged	proc
    TimeHole		proc :LONG, :LONG
    StaleDataRead	proc
    ContentBecomingStale proc
    StaleFileDeleted	proc
   .ends

endif

ifndef __IMSVidStreamBufferSourceEvent2_INTERFACE_DEFINED__
define __IMSVidStreamBufferSourceEvent2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSourceEvent2, "7AEF50CE-8E22-4BA8-BC06-A92A458B4EF2")

.comdef IMSVidStreamBufferSourceEvent2 : public IMSVidStreamBufferSourceEvent

    RateChange		proc :real8, :real8
   .ends

endif

ifndef __IMSVidStreamBufferSourceEvent3_INTERFACE_DEFINED__
define __IMSVidStreamBufferSourceEvent3_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferSourceEvent3, "CEABD6AB-9B90-4570-ADF1-3CE76E00A763")

.comdef IMSVidStreamBufferSourceEvent3 : public IMSVidStreamBufferSourceEvent2

    BroadcastEvent	proc :BSTR
    BroadcastEventEx	proc :BSTR, :ULONG, :ULONG, :ULONG, :ULONG
    COPPBlocked		proc
    COPPUnblocked	proc
    ContentPrimarilyAudio proc
   .ends

endif

ifndef __IMSVidStreamBufferV2SourceEvent_INTERFACE_DEFINED__
define __IMSVidStreamBufferV2SourceEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidStreamBufferV2SourceEvent, "49C771F9-41B2-4CF7-9F9A-A313A8F6027E")

.comdef IMSVidStreamBufferV2SourceEvent : public IMSVidFilePlaybackEvent

    RatingsChanged	proc
    TimeHole		proc :LONG, :LONG
    StaleDataRead	proc
    ContentBecomingStale proc
    StaleFileDeleted	proc
    RateChange		proc :real8, :real8
    BroadcastEvent	proc :BSTR
    BroadcastEventEx	proc :BSTR, :ULONG, :ULONG, :ULONG, :ULONG
    ContentPrimarilyAudio proc
   .ends

endif

ifndef __IMSVidVideoRenderer2_INTERFACE_DEFINED__
define __IMSVidVideoRenderer2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVideoRenderer2, "6BDD5C1E-2810-4159-94BC-05511AE8549B")

.comdef IMSVidVideoRenderer2 : public IMSVidVideoRenderer

    get_Allocator	proc :ptr ptr IUnknown
    get__Allocator	proc :ptr ptr IVMRSurfaceAllocator
    get_Allocator_ID	proc :ptr LONG
    SetAllocator	proc :ptr IUnknown, :LONG
    _SetAllocator	proc :ptr IVMRSurfaceAllocator, :LONG
    put_SuppressEffects proc :VARIANT_BOOL
    get_SuppressEffects proc :ptr VARIANT_BOOL
   .ends

endif

ifndef __IMSVidVideoRendererEvent2_INTERFACE_DEFINED__
define __IMSVidVideoRendererEvent2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVideoRendererEvent2, "7145ED66-4730-4fdb-8A53-FDE7508D3E5E")

.comdef IMSVidVideoRendererEvent2 : public IMSVidOutputDeviceEvent

    OverlayUnavailable	proc
   .ends

endif

ifndef __IMSVidVMR9_INTERFACE_DEFINED__
define __IMSVidVMR9_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVMR9, "D58B0015-EBEF-44bb-BBDD-3F3699D76EA1")

.comdef IMSVidVMR9 : public IMSVidVideoRenderer

    get_Allocator_ID	proc :ptr LONG
    SetAllocator	proc :ptr IUnknown, :LONG
    put_SuppressEffects proc :VARIANT_BOOL
    get_SuppressEffects proc :ptr VARIANT_BOOL
    get_Allocator	proc :ptr ptr IUnknown
   .ends

endif

ifndef __IMSVidEVR_INTERFACE_DEFINED__
define __IMSVidEVR_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidEVR, "15E496AE-82A8-4cf9-A6B6-C561DC60398F")

.comdef IMSVidEVR : public IMSVidVideoRenderer

    get_Presenter	proc :ptr ptr IMFVideoPresenter
    put_Presenter	proc :ptr IMFVideoPresenter
    put_SuppressEffects proc :VARIANT_BOOL
    get_SuppressEffects proc :ptr VARIANT_BOOL
   .ends

endif

ifndef __IMSVidEVREvent_INTERFACE_DEFINED__
define __IMSVidEVREvent_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidEVREvent, "349ABB10-883C-4F22-8714-CECAEEE45D62")

.comdef IMSVidEVREvent : public IMSVidOutputDeviceEvent

    OnUserEvent		proc :LONG
   .ends

endif

ifndef __IMSVidAudioRenderer_INTERFACE_DEFINED__
define __IMSVidAudioRenderer_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidAudioRenderer, "37B0353F-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidAudioRenderer : public IMSVidOutputDevice

    put_Volume		proc :LONG
    get_Volume		proc :ptr LONG
    put_Balance		proc :LONG
    get_Balance		proc :ptr LONG
   .ends

endif

ifndef __IMSVidAudioRendererEvent_INTERFACE_DEFINED__
__IMSVidAudioRendererEvent_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMSVidAudioRendererEvent, "37B03541-A4C8-11d2-B634-00C04F79498E")

.comdef IMSVidAudioRendererEvent : public IMSVidOutputDeviceEvent

    .ends

endif

ifndef __IMSVidAudioRendererEvent2_INTERFACE_DEFINED__
define __IMSVidAudioRendererEvent2_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidAudioRendererEvent2, "E3F55729-353B-4c43-A028-50F79AA9A907")

.comdef IMSVidAudioRendererEvent2 : public IMSVidAudioRendererEvent

    AVDecAudioDualMono	proc
    AVAudioSampleRate	proc
    AVAudioChannelConfig proc
    AVAudioChannelCount proc
    AVDecCommonMeanBitRate proc
    AVDDSurroundMode	proc
    AVDecCommonInputFormat proc
    AVDecCommonOutputFormat proc
   .ends

endif

ifndef __IMSVidInputDevices_INTERFACE_DEFINED__
define __IMSVidInputDevices_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidInputDevices, "C5702CD1-9B79-11d3-B654-00C04F79498E")

.comdef IMSVidInputDevices : public IDispatch

    get_Count		proc :ptr LONG
    get__NewEnum	proc :ptr ptr IEnumVARIANT
    get_Item		proc :VARIANT, :ptr ptr IMSVidInputDevice
    _Add		proc :ptr IMSVidInputDevice
    Remove		proc :VARIANT
   .ends

endif

ifndef __IMSVidOutputDevices_INTERFACE_DEFINED__
define __IMSVidOutputDevices_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidOutputDevices, "C5702CD2-9B79-11d3-B654-00C04F79498E")

.comdef IMSVidOutputDevices : public IDispatch

    get_Count		proc :ptr LONG
    get__NewEnum	proc :ptr ptr IEnumVARIANT
    get_Item		proc :VARIANT, :ptr ptr IMSVidOutputDevice
    _Add		proc :ptr IMSVidOutputDevice
    Remove		proc :VARIANT
   .ends

endif

ifndef __IMSVidVideoRendererDevices_INTERFACE_DEFINED__
define __IMSVidVideoRendererDevices_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidVideoRendererDevices, "C5702CD3-9B79-11d3-B654-00C04F79498E")

.comdef IMSVidVideoRendererDevices : public IDispatch

    get_Count		proc :ptr LONG
    get__NewEnum	proc :ptr ptr IEnumVARIANT
    get_Item		proc :VARIANT, :ptr ptr IMSVidVideoRenderer
    _Add		proc :ptr IMSVidVideoRenderer
    Remove		proc :VARIANT
   .ends

endif

ifndef __IMSVidAudioRendererDevices_INTERFACE_DEFINED__
define __IMSVidAudioRendererDevices_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidAudioRendererDevices, "C5702CD4-9B79-11d3-B654-00C04F79498E")

.comdef IMSVidAudioRendererDevices : public IDispatch

    get_Count		proc :ptr LONG
    get__NewEnum	proc :ptr ptr IEnumVARIANT
    get_Item		proc :VARIANT, :ptr ptr IMSVidAudioRenderer
    _Add		proc :ptr IMSVidAudioRenderer
    Remove		proc :VARIANT
   .ends

endif

ifndef __IMSVidFeatures_INTERFACE_DEFINED__
define __IMSVidFeatures_INTERFACE_DEFINED__

DEFINE_IIDX(IMSVidFeatures, "C5702CD5-9B79-11d3-B654-00C04F79498E")

.comdef IMSVidFeatures : public IDispatch

    get_Count		proc :ptr LONG
    get__NewEnum	proc :ptr ptr IEnumVARIANT
    get_Item		proc :VARIANT, :ptr ptr IMSVidFeature
    _Add		proc :ptr IMSVidFeature
    Remove		proc :VARIANT
   .ends

endif
endif


BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

HDC_UserSize proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree proto WINAPI :ptr, :ptr

HWND_UserSize proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree proto WINAPI :ptr, :ptr

VARIANT_UserSize proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

HDC_UserSize64 proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree64 proto WINAPI :ptr, :ptr

HWND_UserSize64 proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree64 proto WINAPI :ptr, :ptr

VARIANT_UserSize64 proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree64 proto WINAPI :ptr, :ptr

endif
