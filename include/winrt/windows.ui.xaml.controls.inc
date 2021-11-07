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

ifndef __windows2Eui2Examl2Econtrols_h__
define __windows2Eui2Examl2Econtrols_h__

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Controls

.enum ClickMode {
    ClickMode_Release	= 0,
    ClickMode_Press	= 1,
    ClickMode_Hover	= 2
    }

.enum IncrementalLoadingTrigger {
    IncrementalLoadingTrigger_None	= 0,
    IncrementalLoadingTrigger_Edge	= 1
    }

.enum ItemsUpdatingScrollMode {
    ItemsUpdatingScrollMode_KeepItemsInView	= 0,
    ItemsUpdatingScrollMode_KeepScrollOffset	= 1
    }

.enum ListViewSelectionMode {
    ListViewSelectionMode_None	= 0,
    ListViewSelectionMode_Single	= 1,
    ListViewSelectionMode_Multiple	= 2,
    ListViewSelectionMode_Extended	= 3
    }

.enum Orientation {
    Orientation_Vertical	= 0,
    Orientation_Horizontal	= 1
    }

.enum PanelScrollingDirection {
    PanelScrollingDirection_None	= 0,
    PanelScrollingDirection_Forward	= 1,
    PanelScrollingDirection_Backward	= 2
    }

.enum ScrollBarVisibility {
    ScrollBarVisibility_Disabled	= 0,
    ScrollBarVisibility_Auto	= 1,
    ScrollBarVisibility_Hidden	= 2,
    ScrollBarVisibility_Visible = 3
    }

.enum ScrollIntoViewAlignment {
    ScrollIntoViewAlignment_Default	= 0,
    ScrollIntoViewAlignment_Leading	= 1
    }

.enum ScrollMode {
    ScrollMode_Disabled = 0,
    ScrollMode_Enabled	= 1,
    ScrollMode_Auto	= 2
    }

.enum SelectionMode {
    SelectionMode_Single	= 0,
    SelectionMode_Multiple	= 1,
    SelectionMode_Extended	= 2
    }

.enum SnapPointsType {
    SnapPointsType_None = 0,
    SnapPointsType_Optional	= 1,
    SnapPointsType_Mandatory	= 2,
    SnapPointsType_OptionalSingle	= 3,
    SnapPointsType_MandatorySingle	= 4
    }

.enum StretchDirection {
    StretchDirection_UpOnly	= 0,
    StretchDirection_DownOnly	= 1,
    StretchDirection_Both	= 2
    }

.enum VirtualizationMode {
    VirtualizationMode_Standard = 0,
    VirtualizationMode_Recycling	= 1
    }

.enum ZoomMode {
    ZoomMode_Disabled	= 0,
    ZoomMode_Enabled	= 1
    }

.enum Symbol {
    Symbol_Previous	= 57600,
    Symbol_Next = 57601,
    Symbol_Play = 57602,
    Symbol_Pause	= 57603,
    Symbol_Edit = 57604,
    Symbol_Save = 57605,
    Symbol_Clear	= 57606,
    Symbol_Delete	= 57607,
    Symbol_Remove	= 57608,
    Symbol_Add	= 57609,
    Symbol_Cancel	= 57610,
    Symbol_Accept	= 57611,
    Symbol_More = 57612,
    Symbol_Redo = 57613,
    Symbol_Undo = 57614,
    Symbol_Home = 57615,
    Symbol_Up	= 57616,
    Symbol_Forward	= 57617,
    Symbol_Back = 57618,
    Symbol_Favorite	= 57619,
    Symbol_Camera	= 57620,
    Symbol_Setting	= 57621,
    Symbol_Video	= 57622,
    Symbol_Sync = 57623,
    Symbol_Download	= 57624,
    Symbol_Mail = 57625,
    Symbol_Find = 57626,
    Symbol_Help = 57627,
    Symbol_Upload	= 57628,
    Symbol_Emoji	= 57629,
    Symbol_TwoPage	= 57630,
    Symbol_LeaveChat	= 57631,
    Symbol_MailForward	= 57632,
    Symbol_Clock	= 57633,
    Symbol_Send = 57634,
    Symbol_Crop = 57635,
    Symbol_RotateCamera = 57636,
    Symbol_People	= 57637,
    Symbol_OpenPane	= 57638,
    Symbol_ClosePane	= 57639,
    Symbol_World	= 57640,
    Symbol_Flag = 57641,
    Symbol_PreviewLink	= 57642,
    Symbol_Globe	= 57643,
    Symbol_Trim = 57644,
    Symbol_AttachCamera = 57645,
    Symbol_ZoomIn	= 57646,
    Symbol_Bookmarks	= 57647,
    Symbol_Document	= 57648,
    Symbol_ProtectedDocument	= 57649,
    Symbol_Page = 57650,
    Symbol_Bullets	= 57651,
    Symbol_Comment	= 57652,
    Symbol_MailFilled	= 57653,
    Symbol_ContactInfo	= 57654,
    Symbol_HangUp	= 57655,
    Symbol_ViewAll	= 57656,
    Symbol_MapPin	= 57657,
    Symbol_Phone	= 57658,
    Symbol_VideoChat	= 57659,
    Symbol_Switch	= 57660,
    Symbol_Contact	= 57661,
    Symbol_Rename	= 57662,
    Symbol_Pin	= 57665,
    Symbol_MusicInfo	= 57666,
    Symbol_Go	= 57667,
    Symbol_Keyboard	= 57668,
    Symbol_DockLeft	= 57669,
    Symbol_DockRight	= 57670,
    Symbol_DockBottom	= 57671,
    Symbol_Remote	= 57672,
    Symbol_Refresh	= 57673,
    Symbol_Rotate	= 57674,
    Symbol_Shuffle	= 57675,
    Symbol_List = 57676,
    Symbol_Shop = 57677,
    Symbol_SelectAll	= 57678,
    Symbol_Orientation	= 57679,
    Symbol_Import	= 57680,
    Symbol_ImportAll	= 57681,
    Symbol_BrowsePhotos = 57685,
    Symbol_WebCam	= 57686,
    Symbol_Pictures	= 57688,
    Symbol_SaveLocal	= 57689,
    Symbol_Caption	= 57690,
    Symbol_Stop = 57691,
    Symbol_ShowResults	= 57692,
    Symbol_Volume	= 57693,
    Symbol_Repair	= 57694,
    Symbol_Message	= 57695,
    Symbol_Page2	= 57696,
    Symbol_CalendarDay	= 57697,
    Symbol_CalendarWeek = 57698,
    Symbol_Calendar	= 57699,
    Symbol_Character	= 57700,
    Symbol_MailReplyAll = 57701,
    Symbol_Read = 57702,
    Symbol_Link = 57703,
    Symbol_Account	= 57704,
    Symbol_ShowBcc	= 57705,
    Symbol_HideBcc	= 57706,
    Symbol_Cut	= 57707,
    Symbol_Attach	= 57708,
    Symbol_Paste	= 57709,
    Symbol_Filter	= 57710,
    Symbol_Copy = 57711,
    Symbol_Emoji2	= 57712,
    Symbol_Important	= 57713,
    Symbol_MailReply	= 57714,
    Symbol_SlideShow	= 57715,
    Symbol_Sort = 57716,
    Symbol_Manage	= 57720,
    Symbol_AllApps	= 57721,
    Symbol_DisconnectDrive	= 57722,
    Symbol_MapDrive	= 57723,
    Symbol_NewWindow	= 57724,
    Symbol_OpenWith	= 57725,
    Symbol_ContactPresence	= 57729,
    Symbol_Priority	= 57730,
    Symbol_GoToToday	= 57732,
    Symbol_Font = 57733,
    Symbol_FontColor	= 57734,
    Symbol_Contact2	= 57735,
    Symbol_Folder	= 57736,
    Symbol_Audio	= 57737,
    Symbol_Placeholder	= 57738,
    Symbol_View = 57739,
    Symbol_SetLockScreen	= 57740,
    Symbol_SetTile	= 57741,
    Symbol_ClosedCaption	= 57744,
    Symbol_StopSlideShow	= 57745,
    Symbol_Permissions	= 57746,
    Symbol_Highlight	= 57747,
    Symbol_DisableUpdates	= 57748,
    Symbol_UnFavorite	= 57749,
    Symbol_UnPin	= 57750,
    Symbol_OpenLocal	= 57751,
    Symbol_Mute = 57752,
    Symbol_Italic	= 57753,
    Symbol_Underline	= 57754,
    Symbol_Bold = 57755,
    Symbol_MoveToFolder = 57756,
    Symbol_LikeDislike	= 57757,
    Symbol_Dislike	= 57758,
    Symbol_Like = 57759,
    Symbol_AlignRight	= 57760,
    Symbol_AlignCenter	= 57761,
    Symbol_AlignLeft	= 57762,
    Symbol_Zoom = 57763,
    Symbol_ZoomOut	= 57764,
    Symbol_OpenFile	= 57765,
    Symbol_OtherUser	= 57766,
    Symbol_Admin	= 57767,
    Symbol_Street	= 57795,
    Symbol_Map	= 57796,
    Symbol_ClearSelection	= 57797,
    Symbol_FontDecrease = 57798,
    Symbol_FontIncrease = 57799,
    Symbol_FontSize	= 57800,
    Symbol_CellPhone	= 57801,
    Symbol_ReShare	= 57802,
    Symbol_Tag	= 57803,
    Symbol_RepeatOne	= 57804,
    Symbol_RepeatAll	= 57805,
    Symbol_OutlineStar	= 57806,
    Symbol_SolidStar	= 57807,
    Symbol_Calculator	= 57808,
    Symbol_Directions	= 57809,
    Symbol_Target	= 57810,
    Symbol_Library	= 57811,
    Symbol_PhoneBook	= 57812,
    Symbol_Memo = 57813,
    Symbol_Microphone	= 57814,
    Symbol_PostUpdate	= 57815,
    Symbol_BackToWindow = 57816,
    Symbol_FullScreen	= 57817,
    Symbol_NewFolder	= 57818,
    Symbol_CalendarReply	= 57819,
    Symbol_UnSyncFolder = 57821,
    Symbol_ReportHacked = 57822,
    Symbol_SyncFolder	= 57823,
    Symbol_BlockContact = 57824,
    Symbol_SwitchApps	= 57825,
    Symbol_AddFriend	= 57826,
    Symbol_TouchPointer = 57827,
    Symbol_GoToStart	= 57828,
    Symbol_ZeroBars	= 57829,
    Symbol_OneBar	= 57830,
    Symbol_TwoBars	= 57831,
    Symbol_ThreeBars	= 57832,
    Symbol_FourBars	= 57833,
    Symbol_Scan = 58004,
    Symbol_Preview	= 58005
    }

.endn
.endn
.endn
.endn

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.DataTransfer.inc
include Windows.ApplicationModel.Search.inc
include Windows.Media.Capture.inc
include Windows.Media.Core.inc
include Windows.Media.PlayTo.inc
include Windows.System.inc
include Windows.UI.Text.inc
include Windows.UI.Xaml.inc
include Windows.UI.Xaml.Documents.inc
include Windows.UI.Xaml.Navigation.inc
include Windows.Web.inc
include Windows.Web.Http.inc
include windows.foundation.collections.inc
ifndef __windows2Eui2Examl2Einput_h__
 include windows.ui.xaml.input.inc
endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CControls__CColumnDefinition, "264ebc1f-ed90-528e-bf80-e9f7e02c0ee4")

.comdef __FIIterator_1_Windows__CUI__CXaml__CControls__CColumnDefinition : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CControls__CColumnDefinition, "a99329f3-4130-55cc-a4f0-c2ba43ca0735")

.comdef __FIIterable_1_Windows__CUI__CXaml__CControls__CColumnDefinition : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CControls__CGroupStyle, "4b1bfdea-343f-5b34-96f4-753d57227eb9")

.comdef __FIIterator_1_Windows__CUI__CXaml__CControls__CGroupStyle : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CControls__CGroupStyle, "89be2766-2a52-5790-ad0e-d5cae305b07c")

.comdef __FIIterable_1_Windows__CUI__CXaml__CControls__CGroupStyle : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CControls__CHubSection, "4f845272-f53e-5652-b008-a8fbf1e091ef")

.comdef __FIIterator_1_Windows__CUI__CXaml__CControls__CHubSection : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CControls__CHubSection, "558c4082-463a-5c3d-b51e-10921b4a4d6c")

.comdef __FIIterable_1_Windows__CUI__CXaml__CControls__CHubSection : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CControls__CICommandBarElement, "cddb0380-e9d7-5264-ab5c-d72b642874c9")

.comdef __FIIterator_1_Windows__CUI__CXaml__CControls__CICommandBarElement : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CControls__CICommandBarElement, "d4c5a8e7-0d5e-5922-a7b4-59b5e634d335")

.comdef __FIIterable_1_Windows__CUI__CXaml__CControls__CICommandBarElement : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase, "2a8a81ef-f351-50a7-bcdc-8368df215280")

.comdef __FIIterator_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase, "0bb14d64-cc9a-58ae-b881-73fe0ecb99eb")

.comdef __FIIterable_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CControls__CRowDefinition, "2655d45d-38c6-53f0-8719-f3c3a739c1f9")

.comdef __FIIterator_1_Windows__CUI__CXaml__CControls__CRowDefinition : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CControls__CRowDefinition, "abef522a-7378-504f-9406-97d9f42643a7")

.comdef __FIIterable_1_Windows__CUI__CXaml__CControls__CRowDefinition : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CControls__CGroupStyle, "9abc1b42-9b12-5178-a898-bb33f04ece9d")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CControls__CGroupStyle : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CControls__CGroupStyle, "bfb6a4c1-12bb-5f22-a08a-8ebab3864396")

.comdef __FIVector_1_Windows__CUI__CXaml__CControls__CGroupStyle : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
define ____FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
DEFINE_IIDX(__FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CGroupStyle, "2caa8225-b3d4-5725-b0cf-5e6e61453b23")

.comdef __FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CGroupStyle : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIObservableVector_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
define ____FIObservableVector_1_Windows__CUI__CXaml__CControls__CGroupStyle_INTERFACE_DEFINED__
DEFINE_IIDX(__FIObservableVector_1_Windows__CUI__CXaml__CControls__CGroupStyle, "8144f56c-1f13-5a8d-835f-5e0c9325bff1")

.comdef __FIObservableVector_1_Windows__CUI__CXaml__CControls__CGroupStyle : public IInspectable

    add_VectorChanged	proc :ptr, :ptr
    remove_VectorChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CControls__CICommandBarElement, "a38e89ec-f1a4-5d7b-97c3-8aefb64a5f43")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CControls__CICommandBarElement : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement, "18ad7c66-a127-550f-8325-8cf1789176c1")

.comdef __FIVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
define ____FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CICommandBarElement, "20b884e1-c1da-5332-b801-4f1c21744ac8")

.comdef __FVectorChangedEventHandler_1_Windows__CUI__CXaml__CControls__CICommandBarElement : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIObservableVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
define ____FIObservableVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement_INTERFACE_DEFINED__
DEFINE_IIDX(__FIObservableVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement, "d5644006-717d-512d-8785-b48c17e73468")

.comdef __FIObservableVector_1_Windows__CUI__CXaml__CControls__CICommandBarElement : public IInspectable

    add_VectorChanged	proc :ptr, :ptr
    remove_VectorChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CControls__CColumnDefinition, "d8eba449-e161-5108-b4fb-70c2424ea198")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CControls__CColumnDefinition : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CControls__CHubSection, "19452449-44eb-54a4-92f5-12161eda9bd7")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CControls__CHubSection : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase, "a59e9e24-f5a6-5272-a97b-7dd01a3efdd0")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CControls__CRowDefinition, "27b5c835-b5ac-5f58-a770-c739f9e6665c")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CControls__CRowDefinition : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CControls__CColumnDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CControls__CColumnDefinition, "6e137874-dd39-5b4f-a7ec-2ea69e4c2229")

.comdef __FIVector_1_Windows__CUI__CXaml__CControls__CColumnDefinition : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CControls__CHubSection_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CControls__CHubSection, "8e47087a-3ce3-57dc-a583-7db9bf188fc4")

.comdef __FIVector_1_Windows__CUI__CXaml__CControls__CHubSection : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase, "f7f1c37b-b4df-5128-a476-fc8399bc10af")

.comdef __FIVector_1_Windows__CUI__CXaml__CControls__CMenuFlyoutItemBase : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CControls__CRowDefinition_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CControls__CRowDefinition, "62225981-7a0d-5d38-8088-7c6bb6d959be")

.comdef __FIVector_1_Windows__CUI__CXaml__CControls__CRowDefinition : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CDatePickerValueChangedEventArgs_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CDatePickerValueChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FIEventHandler_1_Windows__CUI__CXaml__CControls__CDatePickerValueChangedEventArgs, "18a84f8e-c1ec-5b25-ac98-818267e6f9a4")

.comdef __FIEventHandler_1_Windows__CUI__CXaml__CControls__CDatePickerValueChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangedEventArgs_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangedEventArgs, "354c0f34-e691-502a-a444-d5f07aee310e")

.comdef __FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangingEventArgs_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangingEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangingEventArgs, "e0c06ef2-dbc9-511c-bab6-25756dd516a3")

.comdef __FIEventHandler_1_Windows__CUI__CXaml__CControls__CScrollViewerViewChangingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CTimePickerValueChangedEventArgs_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CUI__CXaml__CControls__CTimePickerValueChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FIEventHandler_1_Windows__CUI__CXaml__CControls__CTimePickerValueChangedEventArgs, "ebc4d41b-356a-59ca-b135-0ec34f68c307")

.comdef __FIEventHandler_1_Windows__CUI__CXaml__CControls__CTimePickerValueChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CListViewBase_Windows__CUI__CXaml__CControls__CContainerContentChangingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CListViewBase_Windows__CUI__CXaml__CControls__CContainerContentChangingEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CListViewBase_Windows__CUI__CXaml__CControls__CContainerContentChangingEventArgs, "d01fb083-5e61-5c12-a18f-62947158faa8")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CListViewBase_Windows__CUI__CXaml__CControls__CContainerContentChangingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQueryChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQueryChangedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQueryChangedEventArgs, "b15ccc28-40f3-52da-9011-87621e9c60ea")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQueryChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQuerySubmittedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQuerySubmittedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQuerySubmittedEventArgs, "56d6c824-a5b2-51f4-8af7-7b8ee582c029")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxQuerySubmittedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxResultSuggestionChosenEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxResultSuggestionChosenEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxResultSuggestionChosenEventArgs, "8d18767b-a4b8-52fc-8767-f87d05b5172e")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxResultSuggestionChosenEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxSuggestionsRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxSuggestionsRequestedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxSuggestionsRequestedEventArgs, "287dd4fe-12fc-5289-ab8a-7c7217024a6b")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSearchBox_Windows__CUI__CXaml__CControls__CSearchBoxSuggestionsRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSwapChainPanel_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSwapChainPanel_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSwapChainPanel_IInspectable, "a8bbf146-b687-5c03-9a42-2ae2d55bfbb4")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CSwapChainPanel_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_IInspectable, "d9f52e0d-21fb-5a0b-b4c6-7d162af7fb9c")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewContentLoadingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewContentLoadingEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewContentLoadingEventArgs, "e7b42a9a-f140-52ad-a658-e237b9a3dcca")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewContentLoadingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewDOMContentLoadedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewDOMContentLoadedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewDOMContentLoadedEventArgs, "b9cc891c-4745-5a25-9845-e44d13425a38")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewDOMContentLoadedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewLongRunningScriptDetectedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewLongRunningScriptDetectedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewLongRunningScriptDetectedEventArgs, "ecdc76ef-a99b-5ce7-b9a4-c85e66fed1ee")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewLongRunningScriptDetectedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationCompletedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationCompletedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationCompletedEventArgs, "411136f7-770d-599c-8545-6d053a6a1799")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationCompletedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationStartingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationStartingEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationStartingEventArgs, "98055b5a-36bb-5962-971f-8b87619eb17e")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewNavigationStartingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewUnviewableContentIdentifiedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewUnviewableContentIdentifiedEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewUnviewableContentIdentifiedEventArgs, "f00e9fbf-d30e-5854-8927-c9512abd8118")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CControls__CWebView_Windows__CUI__CXaml__CControls__CWebViewUnviewableContentIdentifiedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Controls

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIBackClickEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIBackClickEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IBackClickEventHandler, "FA9BC21F-9892-482E-ABF6-EB2D607D32DE")

.comdef IBackClickEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICleanUpVirtualizedItemEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICleanUpVirtualizedItemEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ICleanUpVirtualizedItemEventHandler, "CACAD0D6-0F0D-4870-884D-F2DEDF674288")

.comdef ICleanUpVirtualizedItemEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContextMenuOpeningEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContextMenuOpeningEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IContextMenuOpeningEventHandler, "DF945151-745C-4446-B2FC-216D765847A0")

.comdef IContextMenuOpeningEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDragItemsStartingEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDragItemsStartingEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDragItemsStartingEventHandler, "3AAEAB4C-14CB-4434-BECC-88A8585C2F89")

.comdef IDragItemsStartingEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemClickEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemClickEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IItemClickEventHandler, "3DF6D14E-E18A-4A75-9395-627C5F3CD489")

.comdef IItemClickEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CINotifyEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CINotifyEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(INotifyEventHandler, "C2FDD1F8-7105-4A74-A109-DE29DFF56B98")

.comdef INotifyEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISelectionChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISelectionChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISelectionChangedEventHandler, "E1A05352-5AA0-42CA-9CD9-068A14DB6E68")

.comdef ISelectionChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomViewChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomViewChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISemanticZoomViewChangedEventHandler, "1FA9161D-5D73-44FB-81AC-D1C9384919D4")

.comdef ISemanticZoomViewChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ITextChangedEventHandler, "8EB35B97-AD87-40E8-818B-77DB24759566")

.comdef ITextChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextControlPasteEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextControlPasteEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ITextControlPasteEventHandler, "D56DB359-6F77-4296-AB9C-794939444365")

.comdef ITextControlPasteEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionHeaderClickEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionHeaderClickEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IHubSectionHeaderClickEventHandler, "AFE17B9B-9C63-4583-88E4-C59019B7F49D")

.comdef IHubSectionHeaderClickEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISectionsInViewChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISectionsInViewChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ISectionsInViewChangedEventHandler, "6BECAA6A-63F8-47FF-B6AC-76E7DA247D67")

.comdef ISectionsInViewChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationFailedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationFailedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IWebViewNavigationFailedEventHandler, "A31EAFE1-41DC-47F8-AE22-9706C8F143D4")

.comdef IWebViewNavigationFailedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIBackClickEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIBackClickEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IBackClickEventArgs <L"Windows.UI.Xaml.Controls.IBackClickEventArgs">
DEFINE_IIDX(IBackClickEventArgs, "2AE6146C-477E-48C9-8830-2C464B7C7104")

.comdef IBackClickEventArgs : public IInspectable

    get_Handled		proc :ptr
    put_Handled		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIBorder_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIBorder_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IBorder <L"Windows.UI.Xaml.Controls.IBorder">
DEFINE_IIDX(IBorder, "797C4539-45BD-4633-A044-BFB02EF5170F")

.comdef IBorder : public IInspectable

    get_BorderBrush	proc :ptr
    put_BorderBrush	proc :ptr
    get_BorderThickness proc :ptr
    put_BorderThickness proc :Windows::UI::Xaml::Thickness
    get_Background	proc :ptr
    put_Background	proc :ptr
    get_CornerRadius	proc :ptr
    put_CornerRadius	proc :Windows::UI::Xaml::CornerRadius
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
    get_Child		proc :ptr
    put_Child		proc :ptr
    get_ChildTransitions proc :ptr
    put_ChildTransitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIBorderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIBorderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IBorderStatics <L"Windows.UI.Xaml.Controls.IBorderStatics">
DEFINE_IIDX(IBorderStatics, "B81D1639-E911-4FD7-A4C4-B9C7F008B7FC")

.comdef IBorderStatics : public IInspectable

    get_BorderBrushProperty proc :ptr
    get_BorderThicknessProperty proc :ptr
    get_BackgroundProperty proc :ptr
    get_CornerRadiusProperty proc :ptr
    get_PaddingProperty proc :ptr
    get_ChildTransitionsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIButton_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIButton_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IButton <L"Windows.UI.Xaml.Controls.IButton">
DEFINE_IIDX(IButton, "280335AE-5570-46C7-8E0B-602BE71229A2")

.comdef IButton : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIButtonFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIButtonFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IButtonFactory <L"Windows.UI.Xaml.Controls.IButtonFactory">
DEFINE_IIDX(IButtonFactory, "80A13C19-843A-451C-8CF5-44C701B0E216")

.comdef IButtonFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIButtonWithFlyout_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIButtonWithFlyout_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IButtonWithFlyout <L"Windows.UI.Xaml.Controls.IButtonWithFlyout">
DEFINE_IIDX(IButtonWithFlyout, "09108F87-DF6C-4180-9B3A-E60845825811")

.comdef IButtonWithFlyout : public IInspectable

    get_Flyout		proc :ptr
    put_Flyout		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIButtonStaticsWithFlyout_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIButtonStaticsWithFlyout_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IButtonStaticsWithFlyout <L"Windows.UI.Xaml.Controls.IButtonStaticsWithFlyout">
DEFINE_IIDX(IButtonStaticsWithFlyout, "90143898-A16C-4759-B2F0-A5F7E625169E")

.comdef IButtonStaticsWithFlyout : public IInspectable

    get_FlyoutProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICanvas_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICanvas_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICanvas <L"Windows.UI.Xaml.Controls.ICanvas">
DEFINE_IIDX(ICanvas, "79190E19-CD38-4823-AEAE-64A77132F519")

.comdef ICanvas : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICanvasStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICanvasStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICanvasStatics <L"Windows.UI.Xaml.Controls.ICanvasStatics">
DEFINE_IIDX(ICanvasStatics, "40CE5C46-2962-446F-AAFB-4CDC486939C9")

.comdef ICanvasStatics : public IInspectable

    get_LeftProperty	proc :ptr
    GetLeft		proc :ptr, :ptr
    SetLeft		proc :ptr, :DOUBLE
    get_TopProperty	proc :ptr
    GetTop		proc :ptr, :ptr
    SetTop		proc :ptr, :DOUBLE
    get_ZIndexProperty	proc :ptr
    GetZIndex		proc :ptr, :ptr
    SetZIndex		proc :ptr, :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICanvasFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICanvasFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICanvasFactory <L"Windows.UI.Xaml.Controls.ICanvasFactory">
DEFINE_IIDX(ICanvasFactory, "1B328BD1-B400-4A8E-943B-5AD2C45BE0DF")

.comdef ICanvasFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICaptureElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICaptureElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICaptureElement <L"Windows.UI.Xaml.Controls.ICaptureElement">
DEFINE_IIDX(ICaptureElement, "31A5C0E7-F307-4D4A-B626-E978863F5B74")

.comdef ICaptureElement : public IInspectable

    get_Source		proc :ptr
    put_Source		proc :ptr
    get_Stretch		proc :ptr
    put_Stretch		proc :Windows::UI::Xaml::Media::Stretch
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICaptureElementStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICaptureElementStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICaptureElementStatics <L"Windows.UI.Xaml.Controls.ICaptureElementStatics">
DEFINE_IIDX(ICaptureElementStatics, "1E438DED-7DA6-409E-806E-305AE4AD9B3F")

.comdef ICaptureElementStatics : public IInspectable

    get_SourceProperty	proc :ptr
    get_StretchProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICheckBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICheckBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICheckBox <L"Windows.UI.Xaml.Controls.ICheckBox">
DEFINE_IIDX(ICheckBox, "2294C894-7E2A-4B70-B088-8F5D814875BA")

.comdef ICheckBox : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICheckBoxFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICheckBoxFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICheckBoxFactory <L"Windows.UI.Xaml.Controls.ICheckBoxFactory">
DEFINE_IIDX(ICheckBoxFactory, "4FA6AABB-3F4B-4301-BE07-1172EA61EEFB")

.comdef ICheckBoxFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICleanUpVirtualizedItemEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICleanUpVirtualizedItemEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICleanUpVirtualizedItemEventArgs <L"Windows.UI.Xaml.Controls.ICleanUpVirtualizedItemEventArgs">
DEFINE_IIDX(ICleanUpVirtualizedItemEventArgs, "EA05CCE9-937C-4120-8406-792185784338")

.comdef ICleanUpVirtualizedItemEventArgs : public IInspectable

    get_Value		proc :ptr
    get_UIElement	proc :ptr
    get_Cancel		proc :ptr
    put_Cancel		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIColumnDefinition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIColumnDefinition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IColumnDefinition <L"Windows.UI.Xaml.Controls.IColumnDefinition">
DEFINE_IIDX(IColumnDefinition, "F7F1B229-F024-467F-970A-7E705615DB7B")

.comdef IColumnDefinition : public IInspectable

    get_Width		proc :ptr
    put_Width		proc :Windows::UI::Xaml::GridLength
    get_MaxWidth	proc :ptr
    put_MaxWidth	proc :DOUBLE
    get_MinWidth	proc :ptr
    put_MinWidth	proc :DOUBLE
    get_ActualWidth	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIColumnDefinitionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIColumnDefinitionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IColumnDefinitionStatics <L"Windows.UI.Xaml.Controls.IColumnDefinitionStatics">
DEFINE_IIDX(IColumnDefinitionStatics, "06B0D728-D044-40C6-942E-AE60EAC74851")

.comdef IColumnDefinitionStatics : public IInspectable

    get_WidthProperty	proc :ptr
    get_MaxWidthProperty proc :ptr
    get_MinWidthProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBox <L"Windows.UI.Xaml.Controls.IComboBox">
DEFINE_IIDX(IComboBox, "B9A8D05C-AC97-47F1-A5F4-3F9F4D4B116C")

.comdef IComboBox : public IInspectable

    get_IsDropDownOpen	proc :ptr
    put_IsDropDownOpen	proc :boolean
    get_IsEditable	proc :ptr
    get_IsSelectionBoxHighlighted proc :ptr
    get_MaxDropDownHeight proc :ptr
    put_MaxDropDownHeight proc :DOUBLE
    get_SelectionBoxItem proc :ptr
    get_SelectionBoxItemTemplate proc :ptr
    get_TemplateSettings proc :ptr
    add_DropDownClosed	proc :ptr, :ptr
    remove_DropDownClosed proc :EventRegistrationToken
    add_DropDownOpened	proc :ptr, :ptr
    remove_DropDownOpened proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBoxOverrides <L"Windows.UI.Xaml.Controls.IComboBoxOverrides">
DEFINE_IIDX(IComboBoxOverrides, "4F016541-BCFE-4A22-8932-C914981C2240")

.comdef IComboBoxOverrides : public IInspectable

    OnDropDownClosed	proc :ptr
    OnDropDownOpened	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBoxStatics <L"Windows.UI.Xaml.Controls.IComboBoxStatics">
DEFINE_IIDX(IComboBoxStatics, "3E14C9B1-D15B-4DC9-8110-CF3A117B96E7")

.comdef IComboBoxStatics : public IInspectable

    get_IsDropDownOpenProperty proc :ptr
    get_MaxDropDownHeightProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBoxFactory <L"Windows.UI.Xaml.Controls.IComboBoxFactory">
DEFINE_IIDX(IComboBoxFactory, "AC0D0444-A65B-4ABD-86DF-3016049EFEDC")

.comdef IComboBoxFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBox2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBox2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBox2 <L"Windows.UI.Xaml.Controls.IComboBox2">
DEFINE_IIDX(IComboBox2, "EA0CBF91-CA36-4FAD-972A-2E53A6718B9F")

.comdef IComboBox2 : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_PlaceholderText proc :ptr
    put_PlaceholderText proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBoxStatics2 <L"Windows.UI.Xaml.Controls.IComboBoxStatics2">
DEFINE_IIDX(IComboBoxStatics2, "93988A11-402C-4B13-96D1-7220266B9220")

.comdef IComboBoxStatics2 : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_PlaceholderTextProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBoxItem <L"Windows.UI.Xaml.Controls.IComboBoxItem">
DEFINE_IIDX(IComboBoxItem, "993FD6D2-2AAE-4F3B-B44D-5648F4D06114")

.comdef IComboBoxItem : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIComboBoxItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IComboBoxItemFactory <L"Windows.UI.Xaml.Controls.IComboBoxItemFactory">
DEFINE_IIDX(IComboBoxItemFactory, "8FFFE867-D94C-4E87-8FC4-6EBCD63C5AC2")

.comdef IComboBoxItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContainerContentChangingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContainerContentChangingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContainerContentChangingEventArgs <L"Windows.UI.Xaml.Controls.IContainerContentChangingEventArgs">
DEFINE_IIDX(IContainerContentChangingEventArgs, "07DEEAA7-018F-4DDA-B399-FD4E13A31BEA")

.comdef IContainerContentChangingEventArgs : public IInspectable

    get_ItemContainer	proc :ptr
    get_InRecycleQueue	proc :ptr
    get_ItemIndex	proc :ptr
    get_Item		proc :ptr
    get_Phase		proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    RegisterUpdateCallback proc :ptr
    RegisterUpdateCallbackWithPhase proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControl_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentControl <L"Windows.UI.Xaml.Controls.IContentControl">
DEFINE_IIDX(IContentControl, "A26DD1DC-CD44-435C-BE94-01D6241C231C")

.comdef IContentControl : public IInspectable

    get_Content		proc :ptr
    put_Content		proc :ptr
    get_ContentTemplate proc :ptr
    put_ContentTemplate proc :ptr
    get_ContentTemplateSelector proc :ptr
    put_ContentTemplateSelector proc :ptr
    get_ContentTransitions proc :ptr
    put_ContentTransitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControlOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControlOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentControlOverrides <L"Windows.UI.Xaml.Controls.IContentControlOverrides">
DEFINE_IIDX(IContentControlOverrides, "5F4C0B10-E38E-4B5D-BE1A-5ED04246A635")

.comdef IContentControlOverrides : public IInspectable

    OnContentChanged	proc :ptr, :ptr
    OnContentTemplateChanged proc :ptr, :ptr
    OnContentTemplateSelectorChanged proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControlStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControlStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentControlStatics <L"Windows.UI.Xaml.Controls.IContentControlStatics">
DEFINE_IIDX(IContentControlStatics, "116982A4-5CF5-4C05-A53F-15E4876C85EC")

.comdef IContentControlStatics : public IInspectable

    get_ContentProperty proc :ptr
    get_ContentTemplateProperty proc :ptr
    get_ContentTemplateSelectorProperty proc :ptr
    get_ContentTransitionsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControlFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControlFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentControlFactory <L"Windows.UI.Xaml.Controls.IContentControlFactory">
DEFINE_IIDX(IContentControlFactory, "AB017B19-196E-4ED5-A27F-55C58FB1673F")

.comdef IContentControlFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControl2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentControl2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentControl2 <L"Windows.UI.Xaml.Controls.IContentControl2">
DEFINE_IIDX(IContentControl2, "652C208C-8CCF-4399-BD3E-5A015AA1BC03")

.comdef IContentControl2 : public IInspectable

    get_ContentTemplateRoot proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentPresenter <L"Windows.UI.Xaml.Controls.IContentPresenter">
DEFINE_IIDX(IContentPresenter, "79FDE5B4-CD37-491C-8845-DAF472DEFFF6")

.comdef IContentPresenter : public IInspectable

    get_Content		proc :ptr
    put_Content		proc :ptr
    get_ContentTemplate proc :ptr
    put_ContentTemplate proc :ptr
    get_ContentTemplateSelector proc :ptr
    put_ContentTemplateSelector proc :ptr
    get_ContentTransitions proc :ptr
    put_ContentTransitions proc :ptr
    get_FontSize	proc :ptr
    put_FontSize	proc :DOUBLE
    get_FontFamily	proc :ptr
    put_FontFamily	proc :ptr
    get_FontWeight	proc :ptr
    put_FontWeight	proc :Windows::UI::Text::FontWeight
    get_FontStyle	proc :ptr
    put_FontStyle	proc :Windows::UI::Text::FontStyle
    get_FontStretch	proc :ptr
    put_FontStretch	proc :Windows::UI::Text::FontStretch
    get_CharacterSpacing proc :ptr
    put_CharacterSpacing proc :INT32
    get_Foreground	proc :ptr
    put_Foreground	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentPresenterOverrides <L"Windows.UI.Xaml.Controls.IContentPresenterOverrides">
DEFINE_IIDX(IContentPresenterOverrides, "A76339ED-32FF-438B-AAD5-1D68FAE93426")

.comdef IContentPresenterOverrides : public IInspectable

    OnContentTemplateChanged proc :ptr, :ptr
    OnContentTemplateSelectorChanged proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentPresenterStatics <L"Windows.UI.Xaml.Controls.IContentPresenterStatics">
DEFINE_IIDX(IContentPresenterStatics, "18C2893B-DA2E-4426-B85A-2C7E2171BEDF")

.comdef IContentPresenterStatics : public IInspectable

    get_ContentProperty proc :ptr
    get_ContentTemplateProperty proc :ptr
    get_ContentTemplateSelectorProperty proc :ptr
    get_ContentTransitionsProperty proc :ptr
    get_FontSizeProperty proc :ptr
    get_FontFamilyProperty proc :ptr
    get_FontWeightProperty proc :ptr
    get_FontStyleProperty proc :ptr
    get_FontStretchProperty proc :ptr
    get_CharacterSpacingProperty proc :ptr
    get_ForegroundProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentPresenterFactory <L"Windows.UI.Xaml.Controls.IContentPresenterFactory">
DEFINE_IIDX(IContentPresenterFactory, "3339D4F7-4815-44C4-9F76-68C83880EF10")

.comdef IContentPresenterFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenter2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenter2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentPresenter2 <L"Windows.UI.Xaml.Controls.IContentPresenter2">
DEFINE_IIDX(IContentPresenter2, "5138E958-335D-4210-8BBB-0AA2B4B5C29E")

.comdef IContentPresenter2 : public IInspectable

    get_OpticalMarginAlignment proc :ptr
    put_OpticalMarginAlignment proc :Windows::UI::Xaml::OpticalMarginAlignment
    get_TextLineBounds	proc :ptr
    put_TextLineBounds	proc :Windows::UI::Xaml::TextLineBounds
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContentPresenterStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContentPresenterStatics2 <L"Windows.UI.Xaml.Controls.IContentPresenterStatics2">
DEFINE_IIDX(IContentPresenterStatics2, "C7D89DD9-06E6-46BE-A8A0-9C117D3024A3")

.comdef IContentPresenterStatics2 : public IInspectable

    get_OpticalMarginAlignmentProperty proc :ptr
    get_TextLineBoundsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIContextMenuEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIContextMenuEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IContextMenuEventArgs <L"Windows.UI.Xaml.Controls.IContextMenuEventArgs">
DEFINE_IIDX(IContextMenuEventArgs, "1F7DF263-C14B-4528-B6F0-637999D83CC6")

.comdef IContextMenuEventArgs : public IInspectable

    get_Handled		proc :ptr
    put_Handled		proc :boolean
    get_CursorLeft	proc :ptr
    get_CursorTop	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelector_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelector_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDataTemplateSelector <L"Windows.UI.Xaml.Controls.IDataTemplateSelector">
DEFINE_IIDX(IDataTemplateSelector, "A907D496-46A0-4CD7-8DBE-F9A581DF60B1")

.comdef IDataTemplateSelector : public IInspectable

    SelectTemplate	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelectorOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelectorOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDataTemplateSelectorOverrides <L"Windows.UI.Xaml.Controls.IDataTemplateSelectorOverrides">
DEFINE_IIDX(IDataTemplateSelectorOverrides, "2D162925-5966-4BFA-8638-4D345689F6CF")

.comdef IDataTemplateSelectorOverrides : public IInspectable

    SelectTemplateCore	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelectorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelectorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDataTemplateSelectorFactory <L"Windows.UI.Xaml.Controls.IDataTemplateSelectorFactory">
DEFINE_IIDX(IDataTemplateSelectorFactory, "511BAAD0-210A-457D-9521-433D2B11B7D2")

.comdef IDataTemplateSelectorFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelector2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelector2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDataTemplateSelector2 <L"Windows.UI.Xaml.Controls.IDataTemplateSelector2">
DEFINE_IIDX(IDataTemplateSelector2, "3792BC47-8C4B-4257-A5AE-CC3F8ED786EB")

.comdef IDataTemplateSelector2 : public IInspectable

    SelectTemplateForItem proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelectorOverrides2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDataTemplateSelectorOverrides2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDataTemplateSelectorOverrides2 <L"Windows.UI.Xaml.Controls.IDataTemplateSelectorOverrides2">
DEFINE_IIDX(IDataTemplateSelectorOverrides2, "6C3FB5FC-8E84-4C91-AC15-04A1D885500F")

.comdef IDataTemplateSelectorOverrides2 : public IInspectable

    SelectTemplateForItemCore proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePicker_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePicker_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDatePicker <L"Windows.UI.Xaml.Controls.IDatePicker">
DEFINE_IIDX(IDatePicker, "06DA3946-08B8-4103-8B8A-093EFD6A7657")

.comdef IDatePicker : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_CalendarIdentifier proc :ptr
    put_CalendarIdentifier proc :HSTRING
    get_Date		proc :ptr
    put_Date		proc :Windows::Foundation::DateTime
    get_DayVisible	proc :ptr
    put_DayVisible	proc :boolean
    get_MonthVisible	proc :ptr
    put_MonthVisible	proc :boolean
    get_YearVisible	proc :ptr
    put_YearVisible	proc :boolean
    get_DayFormat	proc :ptr
    put_DayFormat	proc :HSTRING
    get_MonthFormat	proc :ptr
    put_MonthFormat	proc :HSTRING
    get_YearFormat	proc :ptr
    put_YearFormat	proc :HSTRING
    get_MinYear		proc :ptr
    put_MinYear		proc :Windows::Foundation::DateTime
    get_MaxYear		proc :ptr
    put_MaxYear		proc :Windows::Foundation::DateTime
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    add_DateChanged	proc :ptr, :ptr
    remove_DateChanged	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePickerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePickerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDatePickerStatics <L"Windows.UI.Xaml.Controls.IDatePickerStatics">
DEFINE_IIDX(IDatePickerStatics, "182E7C69-2116-4C67-B513-713364831D79")

.comdef IDatePickerStatics : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_CalendarIdentifierProperty proc :ptr
    get_DateProperty	proc :ptr
    get_DayVisibleProperty proc :ptr
    get_MonthVisibleProperty proc :ptr
    get_YearVisibleProperty proc :ptr
    get_DayFormatProperty proc :ptr
    get_MonthFormatProperty proc :ptr
    get_YearFormatProperty proc :ptr
    get_MinYearProperty proc :ptr
    get_MaxYearProperty proc :ptr
    get_OrientationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePickerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePickerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDatePickerFactory <L"Windows.UI.Xaml.Controls.IDatePickerFactory">
DEFINE_IIDX(IDatePickerFactory, "EEC3CA84-9896-4A7D-BB35-6FB21EAECA11")

.comdef IDatePickerFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePickerValueChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDatePickerValueChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDatePickerValueChangedEventArgs <L"Windows.UI.Xaml.Controls.IDatePickerValueChangedEventArgs">
DEFINE_IIDX(IDatePickerValueChangedEventArgs, "1AE661B2-B1B4-4273-96E0-19DAFF187446")

.comdef IDatePickerValueChangedEventArgs : public IInspectable

    get_OldDate		proc :ptr
    get_NewDate		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIDragItemsStartingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIDragItemsStartingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IDragItemsStartingEventArgs <L"Windows.UI.Xaml.Controls.IDragItemsStartingEventArgs">
DEFINE_IIDX(IDragItemsStartingEventArgs, "71CF215C-DAED-4783-AA11-DC574D2713E9")

.comdef IDragItemsStartingEventArgs : public IInspectable

    get_Cancel		proc :ptr
    put_Cancel		proc :boolean
    get_Items		proc :ptr
    get_Data		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlipView <L"Windows.UI.Xaml.Controls.IFlipView">
DEFINE_IIDX(IFlipView, "A1582F68-3D7D-4D3B-B71D-488EED1E3493")

.comdef IFlipView : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlipViewFactory <L"Windows.UI.Xaml.Controls.IFlipViewFactory">
DEFINE_IIDX(IFlipViewFactory, "F1DEA9BE-9AE8-4D4B-AB43-16D31E05F4F3")

.comdef IFlipViewFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipView2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipView2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlipView2 <L"Windows.UI.Xaml.Controls.IFlipView2">
DEFINE_IIDX(IFlipView2, "C4FEA4FD-7AF3-4952-9FD9-9E0987FC4F29")

.comdef IFlipView2 : public IInspectable

    get_UseTouchAnimationsForAllNavigation proc :ptr
    put_UseTouchAnimationsForAllNavigation proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlipViewStatics2 <L"Windows.UI.Xaml.Controls.IFlipViewStatics2">
DEFINE_IIDX(IFlipViewStatics2, "70E3D93F-4308-4BA2-BBCE-E2CB0ED34476")

.comdef IFlipViewStatics2 : public IInspectable

    get_UseTouchAnimationsForAllNavigationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlipViewItem <L"Windows.UI.Xaml.Controls.IFlipViewItem">
DEFINE_IIDX(IFlipViewItem, "56196565-CE2B-4BDA-A36B-82A2B8B0D4C0")

.comdef IFlipViewItem : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlipViewItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlipViewItemFactory <L"Windows.UI.Xaml.Controls.IFlipViewItemFactory">
DEFINE_IIDX(IFlipViewItemFactory, "F21D91FE-22A0-4412-A853-9D6A6E8F2AAF")

.comdef IFlipViewItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGrid_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGrid_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGrid <L"Windows.UI.Xaml.Controls.IGrid">
DEFINE_IIDX(IGrid, "FD104460-2E15-4BA3-8B8F-FA693A4161E9")

.comdef IGrid : public IInspectable

    get_RowDefinitions	proc :ptr
    get_ColumnDefinitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridStatics <L"Windows.UI.Xaml.Controls.IGridStatics">
DEFINE_IIDX(IGridStatics, "64FE2E9F-F951-42B6-A9CE-BB179AF11595")

.comdef IGridStatics : public IInspectable

    get_RowProperty	proc :ptr
    GetRow		proc :ptr, :ptr
    SetRow		proc :ptr, :INT32
    get_ColumnProperty	proc :ptr
    GetColumn		proc :ptr, :ptr
    SetColumn		proc :ptr, :INT32
    get_RowSpanProperty proc :ptr
    GetRowSpan		proc :ptr, :ptr
    SetRowSpan		proc :ptr, :INT32
    get_ColumnSpanProperty proc :ptr
    GetColumnSpan	proc :ptr, :ptr
    SetColumnSpan	proc :ptr, :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridFactory <L"Windows.UI.Xaml.Controls.IGridFactory">
DEFINE_IIDX(IGridFactory, "AE814041-C531-43B4-BF99-12F506F7B01C")

.comdef IGridFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridView <L"Windows.UI.Xaml.Controls.IGridView">
DEFINE_IIDX(IGridView, "026AE934-B67E-4D80-8F72-8AA64B4D827B")

.comdef IGridView : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridViewFactory <L"Windows.UI.Xaml.Controls.IGridViewFactory">
DEFINE_IIDX(IGridViewFactory, "D9BCCA89-09F9-4C6E-A83E-F199146F0E7D")

.comdef IGridViewFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridViewItem <L"Windows.UI.Xaml.Controls.IGridViewItem">
DEFINE_IIDX(IGridViewItem, "7D9901F1-E7C1-4E83-B470-C9D6D7BDA9F5")

.comdef IGridViewItem : public IInspectable

    get_TemplateSettings proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridViewItemFactory <L"Windows.UI.Xaml.Controls.IGridViewItemFactory">
DEFINE_IIDX(IGridViewItemFactory, "229B00AF-3FA6-43E9-979D-07EA0D6280DC")

.comdef IGridViewItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupItem <L"Windows.UI.Xaml.Controls.IGroupItem">
DEFINE_IIDX(IGroupItem, "4AE8D5D1-7228-4A16-A61F-88C0E8F45C76")

.comdef IGroupItem : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupItemFactory <L"Windows.UI.Xaml.Controls.IGroupItemFactory">
DEFINE_IIDX(IGroupItemFactory, "D9A1D53E-B1E0-4319-9808-7A9E887E13B0")

.comdef IGroupItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyle_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyle_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupStyle <L"Windows.UI.Xaml.Controls.IGroupStyle">
DEFINE_IIDX(IGroupStyle, "71CA300B-B89E-4184-B0DF-A9E95447DE8D")

.comdef IGroupStyle : public IInspectable

    get_Panel		proc :ptr
    put_Panel		proc :ptr
    get_ContainerStyle	proc :ptr
    put_ContainerStyle	proc :ptr
    get_ContainerStyleSelector proc :ptr
    put_ContainerStyleSelector proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_HeaderTemplateSelector proc :ptr
    put_HeaderTemplateSelector proc :ptr
    get_HidesIfEmpty	proc :ptr
    put_HidesIfEmpty	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupStyleFactory <L"Windows.UI.Xaml.Controls.IGroupStyleFactory">
DEFINE_IIDX(IGroupStyleFactory, "56FF664F-E2D7-4F49-803D-C727CDF9372D")

.comdef IGroupStyleFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyle2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyle2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupStyle2 <L"Windows.UI.Xaml.Controls.IGroupStyle2">
DEFINE_IIDX(IGroupStyle2, "69F90679-3A11-4FE7-B4DF-2A0139D4018B")

.comdef IGroupStyle2 : public IInspectable

    get_HeaderContainerStyle proc :ptr
    put_HeaderContainerStyle proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleSelector_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleSelector_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupStyleSelector <L"Windows.UI.Xaml.Controls.IGroupStyleSelector">
DEFINE_IIDX(IGroupStyleSelector, "6DDA119E-9A74-478F-A339-5BB52DE6C51E")

.comdef IGroupStyleSelector : public IInspectable

    SelectGroupStyle	proc :ptr, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleSelectorOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleSelectorOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupStyleSelectorOverrides <L"Windows.UI.Xaml.Controls.IGroupStyleSelectorOverrides">
DEFINE_IIDX(IGroupStyleSelectorOverrides, "F691CAB2-77AD-4D3D-A51C-8EF9C3836456")

.comdef IGroupStyleSelectorOverrides : public IInspectable

    SelectGroupStyleCore proc :ptr, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleSelectorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGroupStyleSelectorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGroupStyleSelectorFactory <L"Windows.UI.Xaml.Controls.IGroupStyleSelectorFactory">
DEFINE_IIDX(IGroupStyleSelectorFactory, "BF570D33-B2F6-481F-A450-C80C291FB22D")

.comdef IGroupStyleSelectorFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHyperlinkButton_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHyperlinkButton_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHyperlinkButton <L"Windows.UI.Xaml.Controls.IHyperlinkButton">
DEFINE_IIDX(IHyperlinkButton, "CCEBACA3-3B5C-4F4C-9BFD-86887BC79772")

.comdef IHyperlinkButton : public IInspectable

    get_NavigateUri	proc :ptr
    put_NavigateUri	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHyperlinkButtonStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHyperlinkButtonStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHyperlinkButtonStatics <L"Windows.UI.Xaml.Controls.IHyperlinkButtonStatics">
DEFINE_IIDX(IHyperlinkButtonStatics,"FBAEB5C7-CDB7-4263-B7D6-3C0D2904ED98")

.comdef IHyperlinkButtonStatics : public IInspectable

    get_NavigateUriProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHyperlinkButtonFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHyperlinkButtonFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHyperlinkButtonFactory <L"Windows.UI.Xaml.Controls.IHyperlinkButtonFactory">
DEFINE_IIDX(IHyperlinkButtonFactory, "43521BAD-4E97-4DA9-A64D-935DFD8CEDF2")

.comdef IHyperlinkButtonFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemContainerMapping_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemContainerMapping_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemContainerMapping <L"Windows.UI.Xaml.Controls.IItemContainerMapping">
DEFINE_IIDX(IItemContainerMapping, "53C9F23A-F25D-446A-99B8-C7AEB839050F")

.comdef IItemContainerMapping : public IInspectable

    ItemFromContainer	proc :ptr, :ptr
    ContainerFromItem	proc :ptr, :ptr
    IndexFromContainer	proc :ptr, :ptr
    ContainerFromIndex	proc :INT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIImage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIImage_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IImage <L"Windows.UI.Xaml.Controls.IImage">
DEFINE_IIDX(IImage, "495B7402-9AF3-4E50-AA90-03388F3086D2")

.comdef IImage : public IInspectable

    get_Source		proc :ptr
    put_Source		proc :ptr
    get_Stretch		proc :ptr
    put_Stretch		proc :Windows::UI::Xaml::Media::Stretch
    get_NineGrid	proc :ptr
    put_NineGrid	proc :Windows::UI::Xaml::Thickness
    get_PlayToSource	proc :ptr
    add_ImageFailed	proc :ptr, :ptr
    remove_ImageFailed	proc :EventRegistrationToken
    add_ImageOpened	proc :ptr, :ptr
    remove_ImageOpened	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIImageStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIImageStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IImageStatics <L"Windows.UI.Xaml.Controls.IImageStatics">
DEFINE_IIDX(IImageStatics, "89903772-C336-43D1-9D51-C3BBD5D5D691")

.comdef IImageStatics : public IInspectable

    get_SourceProperty	proc :ptr
    get_StretchProperty proc :ptr
    get_NineGridProperty proc :ptr
    get_PlayToSourceProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CINavigate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CINavigate_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_INavigate <L"Windows.UI.Xaml.Controls.INavigate">
DEFINE_IIDX(INavigate, "BF2195A9-F4EA-4336-977C-F8FCF78B0D9E")

.comdef INavigate : public IInspectable

    Navigate		proc :Windows::UI::Xaml::Interop::TypeName, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISemanticZoomInformation <L"Windows.UI.Xaml.Controls.ISemanticZoomInformation">
DEFINE_IIDX(ISemanticZoomInformation, "A76A3B63-229B-4DC5-AA11-9D922FBF8A98")

.comdef ISemanticZoomInformation : public IInspectable

    get_SemanticZoomOwner proc :ptr
    put_SemanticZoomOwner proc :ptr
    get_IsActiveView	proc :ptr
    put_IsActiveView	proc :boolean
    get_IsZoomedInView	proc :ptr
    put_IsZoomedInView	proc :boolean
    InitializeViewChange proc
    CompleteViewChange	proc
    MakeVisible		proc :ptr
    StartViewChangeFrom proc :ptr, :ptr
    StartViewChangeTo	proc :ptr, :ptr
    CompleteViewChangeFrom proc :ptr, :ptr
    CompleteViewChangeTo proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemClickEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemClickEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemClickEventArgs <L"Windows.UI.Xaml.Controls.IItemClickEventArgs">
DEFINE_IIDX(IItemClickEventArgs, "9C314242-F29A-494D-A3A5-D4C7B2A46852")

.comdef IItemClickEventArgs : public IInspectable

    get_ClickedItem	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemContainerGenerator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemContainerGenerator_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemContainerGenerator <L"Windows.UI.Xaml.Controls.IItemContainerGenerator">
DEFINE_IIDX(IItemContainerGenerator, "40765F00-83F0-4D7F-B1B8-F19DE4F1D5DA")

.comdef IItemContainerGenerator : public IInspectable

    add_ItemsChanged	proc :ptr, :ptr
    remove_ItemsChanged proc :EventRegistrationToken
    ItemFromContainer	proc :ptr, :ptr
    ContainerFromItem	proc :ptr, :ptr
    IndexFromContainer	proc :ptr, :ptr
    ContainerFromIndex	proc :INT32, :ptr
    GetItemContainerGeneratorForPanel proc :ptr, :ptr
    StartAt		proc :Windows::UI::Xaml::Controls::Primitives::GeneratorPosition, :Windows::UI::Xaml::Controls::Primitives::GeneratorDirection, :boolean
    Stop		proc
    GenerateNext	proc :ptr, :ptr
    PrepareItemContainer proc :ptr
    RemoveAll		proc
    Remove		proc :Windows::UI::Xaml::Controls::Primitives::GeneratorPosition, :INT32
    GeneratorPositionFromIndex proc :INT32, :ptr
    IndexFromGeneratorPosition proc :Windows::UI::Xaml::Controls::Primitives::GeneratorPosition, :ptr
    Recycle		proc :Windows::UI::Xaml::Controls::Primitives::GeneratorPosition, :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControl_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsControl <L"Windows.UI.Xaml.Controls.IItemsControl">
DEFINE_IIDX(IItemsControl, "F4A91DD8-D979-4381-8652-BDA0342A765E")

.comdef IItemsControl : public IInspectable

    get_ItemsSource	proc :ptr
    put_ItemsSource	proc :ptr
    get_Items		proc :ptr
    get_ItemTemplate	proc :ptr
    put_ItemTemplate	proc :ptr
    get_ItemTemplateSelector proc :ptr
    put_ItemTemplateSelector proc :ptr
    get_ItemsPanel	proc :ptr
    put_ItemsPanel	proc :ptr
    get_DisplayMemberPath proc :ptr
    put_DisplayMemberPath proc :HSTRING
    get_ItemContainerStyle proc :ptr
    put_ItemContainerStyle proc :ptr
    get_ItemContainerStyleSelector proc :ptr
    put_ItemContainerStyleSelector proc :ptr
    get_ItemContainerGenerator proc :ptr
    get_ItemContainerTransitions proc :ptr
    put_ItemContainerTransitions proc :ptr
    get_GroupStyle	proc :ptr
    get_GroupStyleSelector proc :ptr
    put_GroupStyleSelector proc :ptr
    get_IsGrouping	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControlOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControlOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsControlOverrides <L"Windows.UI.Xaml.Controls.IItemsControlOverrides">
DEFINE_IIDX(IItemsControlOverrides, "C79BB41B-A084-4301-A496-72971F364ED1")

.comdef IItemsControlOverrides : public IInspectable

    IsItemItsOwnContainerOverride proc :ptr, :ptr
    GetContainerForItemOverride proc :ptr
    ClearContainerForItemOverride proc :ptr, :ptr
    PrepareContainerForItemOverride proc :ptr, :ptr
    OnItemsChanged	proc :ptr
    OnItemContainerStyleChanged proc :ptr, :ptr
    OnItemContainerStyleSelectorChanged proc :ptr, :ptr
    OnItemTemplateChanged proc :ptr, :ptr
    OnItemTemplateSelectorChanged proc :ptr, :ptr
    OnGroupStyleSelectorChanged proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControlStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControlStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsControlStatics <L"Windows.UI.Xaml.Controls.IItemsControlStatics">
DEFINE_IIDX(IItemsControlStatics, "37DABD89-DCFB-45B8-9AFE-874DF097905E")

.comdef IItemsControlStatics : public IInspectable

    get_ItemsSourceProperty proc :ptr
    get_ItemTemplateProperty proc :ptr
    get_ItemTemplateSelectorProperty proc :ptr
    get_ItemsPanelProperty proc :ptr
    get_DisplayMemberPathProperty proc :ptr
    get_ItemContainerStyleProperty proc :ptr
    get_ItemContainerStyleSelectorProperty proc :ptr
    get_ItemContainerTransitionsProperty proc :ptr
    get_GroupStyleSelectorProperty proc :ptr
    get_IsGroupingProperty proc :ptr
    GetItemsOwner	proc :ptr, :ptr
    ItemsControlFromItemContainer proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControlFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControlFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsControlFactory <L"Windows.UI.Xaml.Controls.IItemsControlFactory">
DEFINE_IIDX(IItemsControlFactory, "F7BBC359-F8FD-471C-BCB2-2C74BE8EBF8C")

.comdef IItemsControlFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControl2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsControl2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsControl2 <L"Windows.UI.Xaml.Controls.IItemsControl2">
DEFINE_IIDX(IItemsControl2, "754C3266-0529-45E3-8748-BF747D158357")

.comdef IItemsControl2 : public IInspectable

    get_ItemsPanelRoot	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPanelTemplate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPanelTemplate_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsPanelTemplate <L"Windows.UI.Xaml.Controls.IItemsPanelTemplate">
DEFINE_IIDX(IItemsPanelTemplate, "14EAD768-34B2-4B97-BF3C-E8D73230A2AA")

.comdef IItemsPanelTemplate : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsPresenter <L"Windows.UI.Xaml.Controls.IItemsPresenter">
DEFINE_IIDX(IItemsPresenter, "C271569B-6DCA-4E2B-8E14-C55136B02A71")

.comdef IItemsPresenter : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_HeaderTransitions proc :ptr
    put_HeaderTransitions proc :ptr
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenterStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenterStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsPresenterStatics <L"Windows.UI.Xaml.Controls.IItemsPresenterStatics">
DEFINE_IIDX(IItemsPresenterStatics, "18DE66CD-4A6C-4B2E-AA86-CB126C9A2920")

.comdef IItemsPresenterStatics : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_HeaderTransitionsProperty proc :ptr
    get_PaddingProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenter2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenter2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsPresenter2 <L"Windows.UI.Xaml.Controls.IItemsPresenter2">
DEFINE_IIDX(IItemsPresenter2, "5C04AA33-1DF3-4731-A4C9-DA818378D63D")

.comdef IItemsPresenter2 : public IInspectable

    get_Footer		proc :ptr
    put_Footer		proc :ptr
    get_FooterTemplate	proc :ptr
    put_FooterTemplate	proc :ptr
    get_FooterTransitions proc :ptr
    put_FooterTransitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenterStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsPresenterStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsPresenterStatics2 <L"Windows.UI.Xaml.Controls.IItemsPresenterStatics2">
DEFINE_IIDX(IItemsPresenterStatics2, "8971632E-7867-4D66-9630-29F1C5F7403F")

.comdef IItemsPresenterStatics2 : public IInspectable

    get_FooterProperty	proc :ptr
    get_FooterTemplateProperty proc :ptr
    get_FooterTransitionsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListBox <L"Windows.UI.Xaml.Controls.IListBox">
DEFINE_IIDX(IListBox, "E9F3B9FF-8E91-4ECF-A707-C927F694F881")

.comdef IListBox : public IInspectable

    get_SelectedItems	proc :ptr
    get_SelectionMode	proc :ptr
    put_SelectionMode	proc :Windows::UI::Xaml::Controls::SelectionMode
    ScrollIntoView	proc :ptr
    SelectAll		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListBoxStatics <L"Windows.UI.Xaml.Controls.IListBoxStatics">
DEFINE_IIDX(IListBoxStatics, "6D3F7F73-706A-4E53-A9AA-C9A53C9CDD70")

.comdef IListBoxStatics : public IInspectable

    get_SelectionModeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListBoxFactory <L"Windows.UI.Xaml.Controls.IListBoxFactory">
DEFINE_IIDX(IListBoxFactory, "60CDFDA2-2F44-444B-9C94-B8C9FDA46F59")

.comdef IListBoxFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListBoxItem <L"Windows.UI.Xaml.Controls.IListBoxItem">
DEFINE_IIDX(IListBoxItem, "43C13323-6EDF-4E4B-B6B2-3A93EEC41D95")

.comdef IListBoxItem : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListBoxItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListBoxItemFactory <L"Windows.UI.Xaml.Controls.IListBoxItemFactory">
DEFINE_IIDX(IListBoxItemFactory, "4398B8D4-A3DE-402C-B23D-190384B27CA8")

.comdef IListBoxItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListView <L"Windows.UI.Xaml.Controls.IListView">
DEFINE_IIDX(IListView, "F6CE8C6D-FE96-41AD-A64A-C2B81C4AF7F8")

.comdef IListView : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewFactory <L"Windows.UI.Xaml.Controls.IListViewFactory">
DEFINE_IIDX(IListViewFactory, "BDFF696D-3F22-41F9-97A6-883134A76113")

.comdef IListViewFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewBase <L"Windows.UI.Xaml.Controls.IListViewBase">
DEFINE_IIDX(IListViewBase, "3D0813BA-6890-4537-BFE5-796D9458EDD6")

.comdef IListViewBase : public IInspectable

    get_SelectedItems	proc :ptr
    get_SelectionMode	proc :ptr
    put_SelectionMode	proc :Windows::UI::Xaml::Controls::ListViewSelectionMode
    get_IsSwipeEnabled	proc :ptr
    put_IsSwipeEnabled	proc :boolean
    get_CanDragItems	proc :ptr
    put_CanDragItems	proc :boolean
    get_CanReorderItems proc :ptr
    put_CanReorderItems proc :boolean
    get_IsItemClickEnabled proc :ptr
    put_IsItemClickEnabled proc :boolean
    get_DataFetchSize	proc :ptr
    put_DataFetchSize	proc :DOUBLE
    get_IncrementalLoadingThreshold proc :ptr
    put_IncrementalLoadingThreshold proc :DOUBLE
    get_IncrementalLoadingTrigger proc :ptr
    put_IncrementalLoadingTrigger proc :Windows::UI::Xaml::Controls::IncrementalLoadingTrigger
    add_ItemClick	proc :ptr, :ptr
    remove_ItemClick	proc :EventRegistrationToken
    add_DragItemsStarting proc :ptr, :ptr
    remove_DragItemsStarting proc :EventRegistrationToken
    ScrollIntoView	proc :ptr
    SelectAll		proc
    LoadMoreItemsAsync	proc :ptr
    ScrollIntoViewWithAlignment proc :ptr, :Windows::UI::Xaml::Controls::ScrollIntoViewAlignment
    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_HeaderTransitions proc :ptr
    put_HeaderTransitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewBaseStatics <L"Windows.UI.Xaml.Controls.IListViewBaseStatics">
DEFINE_IIDX(IListViewBaseStatics, "8532B8F7-3E16-455B-89A8-C1346223F6D3")

.comdef IListViewBaseStatics : public IInspectable

    get_SelectionModeProperty proc :ptr
    get_IsSwipeEnabledProperty proc :ptr
    get_CanDragItemsProperty proc :ptr
    get_CanReorderItemsProperty proc :ptr
    get_IsItemClickEnabledProperty proc :ptr
    get_DataFetchSizeProperty proc :ptr
    get_IncrementalLoadingThresholdProperty proc :ptr
    get_IncrementalLoadingTriggerProperty proc :ptr
    get_SemanticZoomOwnerProperty proc :ptr
    get_IsActiveViewProperty proc :ptr
    get_IsZoomedInViewProperty proc :ptr
    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_HeaderTransitionsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewBaseFactory <L"Windows.UI.Xaml.Controls.IListViewBaseFactory">
DEFINE_IIDX(IListViewBaseFactory, "E67E6C7F-150F-46D0-A6AC-C5002BD9CA53")

.comdef IListViewBaseFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBase2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBase2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewBase2 <L"Windows.UI.Xaml.Controls.IListViewBase2">
DEFINE_IIDX(IListViewBase2, "D1C2A4F7-78A3-4491-86E0-2DDEBC007AC5")

.comdef IListViewBase2 : public IInspectable

    get_ShowsScrollingPlaceholders proc :ptr
    put_ShowsScrollingPlaceholders proc :boolean
    add_ContainerContentChanging proc :ptr, :ptr
    remove_ContainerContentChanging proc :EventRegistrationToken
    SetDesiredContainerUpdateDuration proc :Windows::Foundation::TimeSpan
    get_Footer		proc :ptr
    put_Footer		proc :ptr
    get_FooterTemplate	proc :ptr
    put_FooterTemplate	proc :ptr
    get_FooterTransitions proc :ptr
    put_FooterTransitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewBaseStatics2 <L"Windows.UI.Xaml.Controls.IListViewBaseStatics2">
DEFINE_IIDX(IListViewBaseStatics2, "821C00C8-78CC-411F-9F2E-A55758227F3E")

.comdef IListViewBaseStatics2 : public IInspectable

    get_ShowsScrollingPlaceholdersProperty proc :ptr
    get_FooterProperty	proc :ptr
    get_FooterTemplateProperty proc :ptr
    get_FooterTransitionsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewItem <L"Windows.UI.Xaml.Controls.IListViewItem">
DEFINE_IIDX(IListViewItem, "B7BB4305-3DD9-43DE-A8C0-C472F085BC11")

.comdef IListViewItem : public IInspectable

    get_TemplateSettings proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewItemFactory <L"Windows.UI.Xaml.Controls.IListViewItemFactory">
DEFINE_IIDX(IListViewItemFactory, "F431073D-9CAC-42A2-82DF-0F4490BC4E2E")

.comdef IListViewItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMediaElement <L"Windows.UI.Xaml.Controls.IMediaElement">
DEFINE_IIDX(IMediaElement, "A38ED2CF-13DE-4299-ADE2-AE18F74ED353")

.comdef IMediaElement : public IInspectable

    get_PosterSource	proc :ptr
    put_PosterSource	proc :ptr
    get_Source		proc :ptr
    put_Source		proc :ptr
    get_IsMuted		proc :ptr
    put_IsMuted		proc :boolean
    get_IsAudioOnly	proc :ptr
    get_AutoPlay	proc :ptr
    put_AutoPlay	proc :boolean
    get_Volume		proc :ptr
    put_Volume		proc :DOUBLE
    get_Balance		proc :ptr
    put_Balance		proc :DOUBLE
    get_NaturalVideoHeight proc :ptr
    get_NaturalVideoWidth proc :ptr
    get_NaturalDuration proc :ptr
    get_Position	proc :ptr
    put_Position	proc :Windows::Foundation::TimeSpan
    get_DownloadProgress proc :ptr
    get_BufferingProgress proc :ptr
    get_DownloadProgressOffset proc :ptr
    get_CurrentState	proc :ptr
    get_Markers		proc :ptr
    get_CanSeek		proc :ptr
    get_CanPause	proc :ptr
    get_AudioStreamCount proc :ptr
    get_AudioStreamIndex proc :ptr
    put_AudioStreamIndex proc :ptr
    get_PlaybackRate	proc :ptr
    put_PlaybackRate	proc :DOUBLE
    get_IsLooping	proc :ptr
    put_IsLooping	proc :boolean
    get_PlayToSource	proc :ptr
    get_DefaultPlaybackRate proc :ptr
    put_DefaultPlaybackRate proc :DOUBLE
    get_AspectRatioWidth proc :ptr
    get_AspectRatioHeight proc :ptr
    get_RealTimePlayback proc :ptr
    put_RealTimePlayback proc :boolean
    get_AudioCategory	proc :ptr
    put_AudioCategory	proc :Windows::UI::Xaml::Media::AudioCategory
    get_AudioDeviceType proc :ptr
    put_AudioDeviceType proc :Windows::UI::Xaml::Media::AudioDeviceType
    get_ProtectionManager proc :ptr
    put_ProtectionManager proc :ptr
    get_Stereo3DVideoPackingMode proc :ptr
    put_Stereo3DVideoPackingMode proc :Windows::UI::Xaml::Media::Stereo3DVideoPackingMode
    get_Stereo3DVideoRenderMode proc :ptr
    put_Stereo3DVideoRenderMode proc :Windows::UI::Xaml::Media::Stereo3DVideoRenderMode
    get_IsStereo3DVideo proc :ptr
    add_MediaOpened	proc :ptr, :ptr
    remove_MediaOpened	proc :EventRegistrationToken
    add_MediaEnded	proc :ptr, :ptr
    remove_MediaEnded	proc :EventRegistrationToken
    add_MediaFailed	proc :ptr, :ptr
    remove_MediaFailed	proc :EventRegistrationToken
    add_DownloadProgressChanged proc :ptr, :ptr
    remove_DownloadProgressChanged proc :EventRegistrationToken
    add_BufferingProgressChanged proc :ptr, :ptr
    remove_BufferingProgressChanged proc :EventRegistrationToken
    add_CurrentStateChanged proc :ptr, :ptr
    remove_CurrentStateChanged proc :EventRegistrationToken
    add_MarkerReached	proc :ptr, :ptr
    remove_MarkerReached proc :EventRegistrationToken
    add_RateChanged	proc :ptr, :ptr
    remove_RateChanged	proc :EventRegistrationToken
    add_VolumeChanged	proc :ptr, :ptr
    remove_VolumeChanged proc :EventRegistrationToken
    add_SeekCompleted	proc :ptr, :ptr
    remove_SeekCompleted proc :EventRegistrationToken
    Stop		proc
    Play		proc
    _Pause		proc
    CanPlayType		proc :HSTRING, :ptr
    SetSource		proc :ptr, :HSTRING
    GetAudioStreamLanguage proc :ptr, :ptr
    AddAudioEffect	proc :HSTRING, :boolean, :ptr
    AddVideoEffect	proc :HSTRING, :boolean, :ptr
    RemoveAllEffects	proc
    get_ActualStereo3DVideoPackingMode proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElementStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElementStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMediaElementStatics <L"Windows.UI.Xaml.Controls.IMediaElementStatics">
DEFINE_IIDX(IMediaElementStatics, "DCCD2CB9-7568-4682-A72A-8DDF2A2665CA")

.comdef IMediaElementStatics : public IInspectable

    get_PosterSourceProperty proc :ptr
    get_SourceProperty	proc :ptr
    get_IsMutedProperty proc :ptr
    get_IsAudioOnlyProperty proc :ptr
    get_AutoPlayProperty proc :ptr
    get_VolumeProperty	proc :ptr
    get_BalanceProperty proc :ptr
    get_NaturalVideoHeightProperty proc :ptr
    get_NaturalVideoWidthProperty proc :ptr
    get_NaturalDurationProperty proc :ptr
    get_PositionProperty proc :ptr
    get_DownloadProgressProperty proc :ptr
    get_BufferingProgressProperty proc :ptr
    get_DownloadProgressOffsetProperty proc :ptr
    get_CurrentStateProperty proc :ptr
    get_CanSeekProperty proc :ptr
    get_CanPauseProperty proc :ptr
    get_AudioStreamCountProperty proc :ptr
    get_AudioStreamIndexProperty proc :ptr
    get_PlaybackRateProperty proc :ptr
    get_IsLoopingProperty proc :ptr
    get_PlayToSourceProperty proc :ptr
    get_DefaultPlaybackRateProperty proc :ptr
    get_AspectRatioWidthProperty proc :ptr
    get_AspectRatioHeightProperty proc :ptr
    get_RealTimePlaybackProperty proc :ptr
    get_AudioCategoryProperty proc :ptr
    get_AudioDeviceTypeProperty proc :ptr
    get_ProtectionManagerProperty proc :ptr
    get_Stereo3DVideoPackingModeProperty proc :ptr
    get_Stereo3DVideoRenderModeProperty proc :ptr
    get_IsStereo3DVideoProperty proc :ptr
    get_ActualStereo3DVideoPackingModeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElement2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElement2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMediaElement2 <L"Windows.UI.Xaml.Controls.IMediaElement2">
DEFINE_IIDX(IMediaElement2, "FD53DA65-B186-4654-BFDB-180ED26CAD07")

.comdef IMediaElement2 : public IInspectable

    get_AreTransportControlsEnabled proc :ptr
    put_AreTransportControlsEnabled proc :boolean
    get_Stretch		proc :ptr
    put_Stretch		proc :Windows::UI::Xaml::Media::Stretch
    get_IsFullWindow	proc :ptr
    put_IsFullWindow	proc :boolean
    SetMediaStreamSource proc :ptr
    get_PlayToPreferredSourceUri proc :ptr
    put_PlayToPreferredSourceUri proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElementStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMediaElementStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMediaElementStatics2 <L"Windows.UI.Xaml.Controls.IMediaElementStatics2">
DEFINE_IIDX(IMediaElementStatics2, "9EE7F826-F154-4DC6-8014-A6EBA987F847")

.comdef IMediaElementStatics2 : public IInspectable

    get_AreTransportControlsEnabledProperty proc :ptr
    get_StretchProperty proc :ptr
    get_IsFullWindowProperty proc :ptr
    get_PlayToPreferredSourceUriProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CINotifyEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CINotifyEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_INotifyEventArgs <L"Windows.UI.Xaml.Controls.INotifyEventArgs">
DEFINE_IIDX(INotifyEventArgs, "AF0E05F7-C4B7-44C5-B09D-5CB7052B3A97")

.comdef INotifyEventArgs : public IInspectable

    get_Value		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CINotifyEventArgs2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CINotifyEventArgs2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_INotifyEventArgs2 <L"Windows.UI.Xaml.Controls.INotifyEventArgs2">
DEFINE_IIDX(INotifyEventArgs2, "0D140F56-1DCE-4FCD-85BC-5A5572273B9C")

.comdef INotifyEventArgs2 : public IInspectable

    get_CallingUri	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPanel <L"Windows.UI.Xaml.Controls.IPanel">
DEFINE_IIDX(IPanel, "A50A4BBD-8361-469C-90DA-E9A40C7474DF")

.comdef IPanel : public IInspectable

    get_Children	proc :ptr
    get_Background	proc :ptr
    put_Background	proc :ptr
    get_IsItemsHost	proc :ptr
    get_ChildrenTransitions proc :ptr
    put_ChildrenTransitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPanelStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPanelStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPanelStatics <L"Windows.UI.Xaml.Controls.IPanelStatics">
DEFINE_IIDX(IPanelStatics, "F23D6B5D-8330-47A6-A046-25F509B25232")

.comdef IPanelStatics : public IInspectable

    get_BackgroundProperty proc :ptr
    get_IsItemsHostProperty proc :ptr
    get_ChildrenTransitionsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPanelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPanelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPanelFactory <L"Windows.UI.Xaml.Controls.IPanelFactory">
DEFINE_IIDX(IPanelFactory, "EEE68111-C7CC-433F-95CD-D630C34302DD")

.comdef IPanelFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPasswordBox <L"Windows.UI.Xaml.Controls.IPasswordBox">
DEFINE_IIDX(IPasswordBox, "02B9AA11-0B47-4E7D-AD91-3A4168ED230D")

.comdef IPasswordBox : public IInspectable

    get_Password	proc :ptr
    put_Password	proc :HSTRING
    get_PasswordChar	proc :ptr
    put_PasswordChar	proc :HSTRING
    get_IsPasswordRevealButtonEnabled proc :ptr
    put_IsPasswordRevealButtonEnabled proc :boolean
    get_MaxLength	proc :ptr
    put_MaxLength	proc :INT32
    add_PasswordChanged proc :ptr, :ptr
    remove_PasswordChanged proc :EventRegistrationToken
    add_ContextMenuOpening proc :ptr, :ptr
    remove_ContextMenuOpening proc :EventRegistrationToken
    SelectAll		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBoxStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBoxStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPasswordBoxStatics <L"Windows.UI.Xaml.Controls.IPasswordBoxStatics">
DEFINE_IIDX(IPasswordBoxStatics, "5EE67563-2D74-4ACE-BD79-FCAB61A7D77B")

.comdef IPasswordBoxStatics : public IInspectable

    get_PasswordProperty proc :ptr
    get_PasswordCharProperty proc :ptr
    get_IsPasswordRevealButtonEnabledProperty proc :ptr
    get_MaxLengthProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBox2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBox2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPasswordBox2 <L"Windows.UI.Xaml.Controls.IPasswordBox2">
DEFINE_IIDX(IPasswordBox2, "5ED738DF-212F-4AEB-B5B8-2C219AEC3C0C")

.comdef IPasswordBox2 : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_PlaceholderText proc :ptr
    put_PlaceholderText proc :HSTRING
    get_SelectionHighlightColor proc :ptr
    put_SelectionHighlightColor proc :ptr
    get_PreventKeyboardDisplayOnProgrammaticFocus proc :ptr
    put_PreventKeyboardDisplayOnProgrammaticFocus proc :boolean
    add_Paste		proc :ptr, :ptr
    remove_Paste	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBoxStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPasswordBoxStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPasswordBoxStatics2 <L"Windows.UI.Xaml.Controls.IPasswordBoxStatics2">
DEFINE_IIDX(IPasswordBoxStatics2, "FC57935F-98FA-4066-B785-FA725ECDE232")

.comdef IPasswordBoxStatics2 : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_PlaceholderTextProperty proc :ptr
    get_SelectionHighlightColorProperty proc :ptr
    get_PreventKeyboardDisplayOnProgrammaticFocusProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressBar_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressBar_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IProgressBar <L"Windows.UI.Xaml.Controls.IProgressBar">
DEFINE_IIDX(IProgressBar, "AE752C89-0067-4963-BF4C-29DB0C4A507E")

.comdef IProgressBar : public IInspectable

    get_IsIndeterminate proc :ptr
    put_IsIndeterminate proc :boolean
    get_ShowError	proc :ptr
    put_ShowError	proc :boolean
    get_ShowPaused	proc :ptr
    put_ShowPaused	proc :boolean
    get_TemplateSettings proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressBarStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressBarStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IProgressBarStatics <L"Windows.UI.Xaml.Controls.IProgressBarStatics">
DEFINE_IIDX(IProgressBarStatics, "7A129FDA-5837-4E26-B3B4-E1C092CEBBEC")

.comdef IProgressBarStatics : public IInspectable

    get_IsIndeterminateProperty proc :ptr
    get_ShowErrorProperty proc :ptr
    get_ShowPausedProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressBarFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressBarFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IProgressBarFactory <L"Windows.UI.Xaml.Controls.IProgressBarFactory">
DEFINE_IIDX(IProgressBarFactory, "DA9A8C11-1591-400B-A993-0F1C5CC12F3B")

.comdef IProgressBarFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressRing_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressRing_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IProgressRing <L"Windows.UI.Xaml.Controls.IProgressRing">
DEFINE_IIDX(IProgressRing, "6DA5E49E-6E9D-425C-BD7C-02173E39763F")

.comdef IProgressRing : public IInspectable

    get_IsActive	proc :ptr
    put_IsActive	proc :boolean
    get_TemplateSettings proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressRingStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIProgressRingStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IProgressRingStatics <L"Windows.UI.Xaml.Controls.IProgressRingStatics">
DEFINE_IIDX(IProgressRingStatics, "E8B62507-4E2C-47D5-A54A-C6C48A5E6989")

.comdef IProgressRingStatics : public IInspectable

    get_IsActiveProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRadioButton_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRadioButton_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRadioButton <L"Windows.UI.Xaml.Controls.IRadioButton">
DEFINE_IIDX(IRadioButton, "325C44E0-9A03-4BF3-ABD6-6FBB46C9A486")

.comdef IRadioButton : public IInspectable

    get_GroupName	proc :ptr
    put_GroupName	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRadioButtonStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRadioButtonStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRadioButtonStatics <L"Windows.UI.Xaml.Controls.IRadioButtonStatics">
DEFINE_IIDX(IRadioButtonStatics, "6B149293-F50F-4BD8-B0AC-5C162F33A208")

.comdef IRadioButtonStatics : public IInspectable

    get_GroupNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRadioButtonFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRadioButtonFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRadioButtonFactory <L"Windows.UI.Xaml.Controls.IRadioButtonFactory">
DEFINE_IIDX(IRadioButtonFactory, "F1D04933-34E1-4A5C-B2AE-CA3B1C0B20DE")

.comdef IRadioButtonFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichEditBox <L"Windows.UI.Xaml.Controls.IRichEditBox">
DEFINE_IIDX(IRichEditBox, "90A57A40-80B6-4FCE-B1EC-E3C616284B6A")

.comdef IRichEditBox : public IInspectable

    get_IsReadOnly	proc :ptr
    put_IsReadOnly	proc :boolean
    get_AcceptsReturn	proc :ptr
    put_AcceptsReturn	proc :boolean
    get_TextAlignment	proc :ptr
    put_TextAlignment	proc :Windows::UI::Xaml::TextAlignment
    get_TextWrapping	proc :ptr
    put_TextWrapping	proc :Windows::UI::Xaml::TextWrapping
    get_IsSpellCheckEnabled proc :ptr
    put_IsSpellCheckEnabled proc :boolean
    get_IsTextPredictionEnabled proc :ptr
    put_IsTextPredictionEnabled proc :boolean
    get_Document	proc :ptr
    get_InputScope	proc :ptr
    put_InputScope	proc :ptr
    add_TextChanged	proc :ptr, :ptr
    remove_TextChanged	proc :EventRegistrationToken
    add_SelectionChanged proc :ptr, :ptr
    remove_SelectionChanged proc :EventRegistrationToken
    add_ContextMenuOpening proc :ptr, :ptr
    remove_ContextMenuOpening proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBoxStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBoxStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichEditBoxStatics <L"Windows.UI.Xaml.Controls.IRichEditBoxStatics">
DEFINE_IIDX(IRichEditBoxStatics, "F5E03A74-88EA-479B-9A05-37089FF30EDE")

.comdef IRichEditBoxStatics : public IInspectable

    get_IsReadOnlyProperty proc :ptr
    get_AcceptsReturnProperty proc :ptr
    get_TextAlignmentProperty proc :ptr
    get_TextWrappingProperty proc :ptr
    get_IsSpellCheckEnabledProperty proc :ptr
    get_IsTextPredictionEnabledProperty proc :ptr
    get_InputScopeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBoxFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBoxFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichEditBoxFactory <L"Windows.UI.Xaml.Controls.IRichEditBoxFactory">
DEFINE_IIDX(IRichEditBoxFactory, "61A1DF62-2806-41ED-88ED-AE21F47AB422")

.comdef IRichEditBoxFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBox2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBox2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichEditBox2 <L"Windows.UI.Xaml.Controls.IRichEditBox2">
DEFINE_IIDX(IRichEditBox2, "BBEA6EAD-E805-47A4-BBE7-47E59B8F74A7")

.comdef IRichEditBox2 : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_PlaceholderText proc :ptr
    put_PlaceholderText proc :HSTRING
    get_SelectionHighlightColor proc :ptr
    put_SelectionHighlightColor proc :ptr
    get_PreventKeyboardDisplayOnProgrammaticFocus proc :ptr
    put_PreventKeyboardDisplayOnProgrammaticFocus proc :boolean
    get_IsColorFontEnabled proc :ptr
    put_IsColorFontEnabled proc :boolean
    add_Paste		proc :ptr, :ptr
    remove_Paste	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBoxStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichEditBoxStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichEditBoxStatics2 <L"Windows.UI.Xaml.Controls.IRichEditBoxStatics2">
DEFINE_IIDX(IRichEditBoxStatics2, "E3EB26DE-2748-420B-B1FC-CE95B6E85EEC")

.comdef IRichEditBoxStatics2 : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_PlaceholderTextProperty proc :ptr
    get_SelectionHighlightColorProperty proc :ptr
    get_PreventKeyboardDisplayOnProgrammaticFocusProperty proc :ptr
    get_IsColorFontEnabledProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlock_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlock_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlock <L"Windows.UI.Xaml.Controls.IRichTextBlock">
DEFINE_IIDX(IRichTextBlock, "E5FFF9E2-B968-49E7-97D4-8CCA2AC3AE7C")

.comdef IRichTextBlock : public IInspectable

    get_FontSize	proc :ptr
    put_FontSize	proc :DOUBLE
    get_FontFamily	proc :ptr
    put_FontFamily	proc :ptr
    get_FontWeight	proc :ptr
    put_FontWeight	proc :Windows::UI::Text::FontWeight
    get_FontStyle	proc :ptr
    put_FontStyle	proc :Windows::UI::Text::FontStyle
    get_FontStretch	proc :ptr
    put_FontStretch	proc :Windows::UI::Text::FontStretch
    get_Foreground	proc :ptr
    put_Foreground	proc :ptr
    get_TextWrapping	proc :ptr
    put_TextWrapping	proc :Windows::UI::Xaml::TextWrapping
    get_TextTrimming	proc :ptr
    put_TextTrimming	proc :Windows::UI::Xaml::TextTrimming
    get_TextAlignment	proc :ptr
    put_TextAlignment	proc :Windows::UI::Xaml::TextAlignment
    get_Blocks		proc :ptr
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
    get_LineHeight	proc :ptr
    put_LineHeight	proc :DOUBLE
    get_LineStackingStrategy proc :ptr
    put_LineStackingStrategy proc :Windows::UI::Xaml::LineStackingStrategy
    get_CharacterSpacing proc :ptr
    put_CharacterSpacing proc :INT32
    get_OverflowContentTarget proc :ptr
    put_OverflowContentTarget proc :ptr
    get_IsTextSelectionEnabled proc :ptr
    put_IsTextSelectionEnabled proc :boolean
    get_HasOverflowContent proc :ptr
    get_SelectedText	proc :ptr
    get_ContentStart	proc :ptr
    get_ContentEnd	proc :ptr
    get_SelectionStart	proc :ptr
    get_SelectionEnd	proc :ptr
    get_BaselineOffset	proc :ptr
    add_SelectionChanged proc :ptr, :ptr
    remove_SelectionChanged proc :EventRegistrationToken
    add_ContextMenuOpening proc :ptr, :ptr
    remove_ContextMenuOpening proc :EventRegistrationToken
    SelectAll		proc
    Select		proc :ptr, :ptr
    GetPositionFromPoint proc :Windows::Foundation::Point, :ptr
    Focus		proc :Windows::UI::Xaml::FocusState, :ptr
    get_TextIndent	proc :ptr
    put_TextIndent	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlockStatics <L"Windows.UI.Xaml.Controls.IRichTextBlockStatics">
DEFINE_IIDX(IRichTextBlockStatics, "492D883C-ADEA-433C-BE1C-208A164262BE")

.comdef IRichTextBlockStatics : public IInspectable

    get_FontSizeProperty proc :ptr
    get_FontFamilyProperty proc :ptr
    get_FontWeightProperty proc :ptr
    get_FontStyleProperty proc :ptr
    get_FontStretchProperty proc :ptr
    get_ForegroundProperty proc :ptr
    get_TextWrappingProperty proc :ptr
    get_TextTrimmingProperty proc :ptr
    get_TextAlignmentProperty proc :ptr
    get_PaddingProperty proc :ptr
    get_LineHeightProperty proc :ptr
    get_LineStackingStrategyProperty proc :ptr
    get_CharacterSpacingProperty proc :ptr
    get_OverflowContentTargetProperty proc :ptr
    get_IsTextSelectionEnabledProperty proc :ptr
    get_HasOverflowContentProperty proc :ptr
    get_SelectedTextProperty proc :ptr
    get_TextIndentProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlock2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlock2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlock2 <L"Windows.UI.Xaml.Controls.IRichTextBlock2">
DEFINE_IIDX(IRichTextBlock2, "3F209013-03E7-4508-964A-91AEDAB3D11E")

.comdef IRichTextBlock2 : public IInspectable

    get_MaxLines	proc :ptr
    put_MaxLines	proc :INT32
    get_TextLineBounds	proc :ptr
    put_TextLineBounds	proc :Windows::UI::Xaml::TextLineBounds
    get_SelectionHighlightColor proc :ptr
    put_SelectionHighlightColor proc :ptr
    get_OpticalMarginAlignment proc :ptr
    put_OpticalMarginAlignment proc :Windows::UI::Xaml::OpticalMarginAlignment
    get_IsColorFontEnabled proc :ptr
    put_IsColorFontEnabled proc :boolean
    get_TextReadingOrder proc :ptr
    put_TextReadingOrder proc :Windows::UI::Xaml::TextReadingOrder
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlockStatics2 <L"Windows.UI.Xaml.Controls.IRichTextBlockStatics2">
DEFINE_IIDX(IRichTextBlockStatics2, "0D6131E1-AF29-48CE-8AAF-74ECC28BFBB0")

.comdef IRichTextBlockStatics2 : public IInspectable

    get_MaxLinesProperty proc :ptr
    get_TextLineBoundsProperty proc :ptr
    get_SelectionHighlightColorProperty proc :ptr
    get_OpticalMarginAlignmentProperty proc :ptr
    get_IsColorFontEnabledProperty proc :ptr
    get_TextReadingOrderProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlockOverflow <L"Windows.UI.Xaml.Controls.IRichTextBlockOverflow">
DEFINE_IIDX(IRichTextBlockOverflow, "4F93749B-DAC3-4A42-9CBB-99F0DE37C071")

.comdef IRichTextBlockOverflow : public IInspectable

    get_OverflowContentTarget proc :ptr
    put_OverflowContentTarget proc :ptr
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
    get_ContentSource	proc :ptr
    get_HasOverflowContent proc :ptr
    get_ContentStart	proc :ptr
    get_ContentEnd	proc :ptr
    get_BaselineOffset	proc :ptr
    GetPositionFromPoint proc :Windows::Foundation::Point, :ptr
    Focus		proc :Windows::UI::Xaml::FocusState, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflowStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflowStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlockOverflowStatics <L"Windows.UI.Xaml.Controls.IRichTextBlockOverflowStatics">
DEFINE_IIDX(IRichTextBlockOverflowStatics, "041AC2F7-4F2B-43C3-A122-3FEA9CA9DC87")

.comdef IRichTextBlockOverflowStatics : public IInspectable

    get_OverflowContentTargetProperty proc :ptr
    get_PaddingProperty proc :ptr
    get_HasOverflowContentProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflow2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflow2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlockOverflow2 <L"Windows.UI.Xaml.Controls.IRichTextBlockOverflow2">
DEFINE_IIDX(IRichTextBlockOverflow2, "8742624E-A882-4826-B929-4D5C3905B9A1")

.comdef IRichTextBlockOverflow2 : public IInspectable

    get_MaxLines	proc :ptr
    put_MaxLines	proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflowStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRichTextBlockOverflowStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRichTextBlockOverflowStatics2 <L"Windows.UI.Xaml.Controls.IRichTextBlockOverflowStatics2">
DEFINE_IIDX(IRichTextBlockOverflowStatics2, "B5EBED4C-F8C4-4A3A-907F-E53E78279FA3")

.comdef IRichTextBlockOverflowStatics2 : public IInspectable

    get_MaxLinesProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRowDefinition_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRowDefinition_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRowDefinition <L"Windows.UI.Xaml.Controls.IRowDefinition">
DEFINE_IIDX(IRowDefinition, "4ABAE829-D80C-4A5E-A48C-F8B3D3B6533D")

.comdef IRowDefinition : public IInspectable

    get_Height		proc :ptr
    put_Height		proc :Windows::UI::Xaml::GridLength
    get_MaxHeight	proc :ptr
    put_MaxHeight	proc :DOUBLE
    get_MinHeight	proc :ptr
    put_MinHeight	proc :DOUBLE
    get_ActualHeight	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIRowDefinitionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIRowDefinitionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IRowDefinitionStatics <L"Windows.UI.Xaml.Controls.IRowDefinitionStatics">
DEFINE_IIDX(IRowDefinitionStatics, "5ADF3FE5-2056-4724-94D6-E4812B022EC8")

.comdef IRowDefinitionStatics : public IInspectable

    get_HeightProperty	proc :ptr
    get_MaxHeightProperty proc :ptr
    get_MinHeightProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollContentPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollContentPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollContentPresenter <L"Windows.UI.Xaml.Controls.IScrollContentPresenter">
DEFINE_IIDX(IScrollContentPresenter, "5712EE2B-0EEB-46D3-AA31-5F6801B8DE20")

.comdef IScrollContentPresenter : public IInspectable

    get_CanVerticallyScroll proc :ptr
    put_CanVerticallyScroll proc :boolean
    get_CanHorizontallyScroll proc :ptr
    put_CanHorizontallyScroll proc :boolean
    get_ExtentWidth	proc :ptr
    get_ExtentHeight	proc :ptr
    get_ViewportWidth	proc :ptr
    get_ViewportHeight	proc :ptr
    get_HorizontalOffset proc :ptr
    get_VerticalOffset	proc :ptr
    get_ScrollOwner	proc :ptr
    put_ScrollOwner	proc :ptr
    LineUp		proc
    LineDown		proc
    LineLeft		proc
    LineRight		proc
    PageUp		proc
    PageDown		proc
    PageLeft		proc
    PageRight		proc
    MouseWheelUp	proc
    MouseWheelDown	proc
    MouseWheelLeft	proc
    MouseWheelRight	proc
    SetHorizontalOffset proc :DOUBLE
    SetVerticalOffset	proc :DOUBLE
    MakeVisible		proc :ptr, :Windows::Foundation::Rect, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollViewer <L"Windows.UI.Xaml.Controls.IScrollViewer">
DEFINE_IIDX(IScrollViewer, "64E9BE00-4DC1-493D-ABE7-CBD3C577490D")

.comdef IScrollViewer : public IInspectable

    get_HorizontalScrollBarVisibility proc :ptr
    put_HorizontalScrollBarVisibility proc :Windows::UI::Xaml::Controls::ScrollBarVisibility
    get_VerticalScrollBarVisibility proc :ptr
    put_VerticalScrollBarVisibility proc :Windows::UI::Xaml::Controls::ScrollBarVisibility
    get_IsHorizontalRailEnabled proc :ptr
    put_IsHorizontalRailEnabled proc :boolean
    get_IsVerticalRailEnabled proc :ptr
    put_IsVerticalRailEnabled proc :boolean
    get_IsHorizontalScrollChainingEnabled proc :ptr
    put_IsHorizontalScrollChainingEnabled proc :boolean
    get_IsVerticalScrollChainingEnabled proc :ptr
    put_IsVerticalScrollChainingEnabled proc :boolean
    get_IsZoomChainingEnabled proc :ptr
    put_IsZoomChainingEnabled proc :boolean
    get_IsScrollInertiaEnabled proc :ptr
    put_IsScrollInertiaEnabled proc :boolean
    get_IsZoomInertiaEnabled proc :ptr
    put_IsZoomInertiaEnabled proc :boolean
    get_HorizontalScrollMode proc :ptr
    put_HorizontalScrollMode proc :Windows::UI::Xaml::Controls::ScrollMode
    get_VerticalScrollMode proc :ptr
    put_VerticalScrollMode proc :Windows::UI::Xaml::Controls::ScrollMode
    get_ZoomMode	proc :ptr
    put_ZoomMode	proc :Windows::UI::Xaml::Controls::ZoomMode
    get_HorizontalSnapPointsAlignment proc :ptr
    put_HorizontalSnapPointsAlignment proc :Windows::UI::Xaml::Controls::Primitives::SnapPointsAlignment
    get_VerticalSnapPointsAlignment proc :ptr
    put_VerticalSnapPointsAlignment proc :Windows::UI::Xaml::Controls::Primitives::SnapPointsAlignment
    get_HorizontalSnapPointsType proc :ptr
    put_HorizontalSnapPointsType proc :Windows::UI::Xaml::Controls::SnapPointsType
    get_VerticalSnapPointsType proc :ptr
    put_VerticalSnapPointsType proc :Windows::UI::Xaml::Controls::SnapPointsType
    get_ZoomSnapPointsType proc :ptr
    put_ZoomSnapPointsType proc :Windows::UI::Xaml::Controls::SnapPointsType
    get_HorizontalOffset proc :ptr
    get_ViewportWidth	proc :ptr
    get_ScrollableWidth proc :ptr
    get_ComputedHorizontalScrollBarVisibility proc :ptr
    get_ExtentWidth	proc :ptr
    get_VerticalOffset	proc :ptr
    get_ViewportHeight	proc :ptr
    get_ScrollableHeight proc :ptr
    get_ComputedVerticalScrollBarVisibility proc :ptr
    get_ExtentHeight	proc :ptr
    get_MinZoomFactor	proc :ptr
    put_MinZoomFactor	proc :FLOAT
    get_MaxZoomFactor	proc :ptr
    put_MaxZoomFactor	proc :FLOAT
    get_ZoomFactor	proc :ptr
    get_ZoomSnapPoints	proc :ptr
    add_ViewChanged	proc :ptr, :ptr
    remove_ViewChanged	proc :EventRegistrationToken
    ScrollToHorizontalOffset proc :DOUBLE
    ScrollToVerticalOffset proc :DOUBLE
    ZoomToFactor	proc :FLOAT
    InvalidateScrollInfo proc
    get_IsDeferredScrollingEnabled proc :ptr
    put_IsDeferredScrollingEnabled proc :boolean
    get_BringIntoViewOnFocusChange proc :ptr
    put_BringIntoViewOnFocusChange proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollViewerStatics <L"Windows.UI.Xaml.Controls.IScrollViewerStatics">
DEFINE_IIDX(IScrollViewerStatics, "33D1299D-8D6E-4290-BF22-905CCCD04D31")

.comdef IScrollViewerStatics : public IInspectable

    get_HorizontalSnapPointsAlignmentProperty proc :ptr
    get_VerticalSnapPointsAlignmentProperty proc :ptr
    get_HorizontalSnapPointsTypeProperty proc :ptr
    get_VerticalSnapPointsTypeProperty proc :ptr
    get_ZoomSnapPointsTypeProperty proc :ptr
    get_HorizontalOffsetProperty proc :ptr
    get_ViewportWidthProperty proc :ptr
    get_ScrollableWidthProperty proc :ptr
    get_ComputedHorizontalScrollBarVisibilityProperty proc :ptr
    get_ExtentWidthProperty proc :ptr
    get_VerticalOffsetProperty proc :ptr
    get_ViewportHeightProperty proc :ptr
    get_ScrollableHeightProperty proc :ptr
    get_ComputedVerticalScrollBarVisibilityProperty proc :ptr
    get_ExtentHeightProperty proc :ptr
    get_MinZoomFactorProperty proc :ptr
    get_MaxZoomFactorProperty proc :ptr
    get_ZoomFactorProperty proc :ptr
    get_ZoomSnapPointsProperty proc :ptr
    get_HorizontalScrollBarVisibilityProperty proc :ptr
    GetHorizontalScrollBarVisibility proc :ptr, :ptr
    SetHorizontalScrollBarVisibility proc :ptr, :Windows::UI::Xaml::Controls::ScrollBarVisibility
    get_VerticalScrollBarVisibilityProperty proc :ptr
    GetVerticalScrollBarVisibility proc :ptr, :ptr
    SetVerticalScrollBarVisibility proc :ptr, :Windows::UI::Xaml::Controls::ScrollBarVisibility
    get_IsHorizontalRailEnabledProperty proc :ptr
    GetIsHorizontalRailEnabled proc :ptr, :ptr
    SetIsHorizontalRailEnabled proc :ptr, :boolean
    get_IsVerticalRailEnabledProperty proc :ptr
    GetIsVerticalRailEnabled proc :ptr, :ptr
    SetIsVerticalRailEnabled proc :ptr, :boolean
    get_IsHorizontalScrollChainingEnabledProperty proc :ptr
    GetIsHorizontalScrollChainingEnabled proc :ptr, :ptr
    SetIsHorizontalScrollChainingEnabled proc :ptr, :boolean
    get_IsVerticalScrollChainingEnabledProperty proc :ptr
    GetIsVerticalScrollChainingEnabled proc :ptr, :ptr
    SetIsVerticalScrollChainingEnabled proc :ptr, :boolean
    get_IsZoomChainingEnabledProperty proc :ptr
    GetIsZoomChainingEnabled proc :ptr, :ptr
    SetIsZoomChainingEnabled proc :ptr, :boolean
    get_IsScrollInertiaEnabledProperty proc :ptr
    GetIsScrollInertiaEnabled proc :ptr, :ptr
    SetIsScrollInertiaEnabled proc :ptr, :boolean
    get_IsZoomInertiaEnabledProperty proc :ptr
    GetIsZoomInertiaEnabled proc :ptr, :ptr
    SetIsZoomInertiaEnabled proc :ptr, :boolean
    get_HorizontalScrollModeProperty proc :ptr
    GetHorizontalScrollMode proc :ptr, :ptr
    SetHorizontalScrollMode proc :ptr, :Windows::UI::Xaml::Controls::ScrollMode
    get_VerticalScrollModeProperty proc :ptr
    GetVerticalScrollMode proc :ptr, :ptr
    SetVerticalScrollMode proc :ptr, :Windows::UI::Xaml::Controls::ScrollMode
    get_ZoomModeProperty proc :ptr
    GetZoomMode		proc :ptr, :ptr
    SetZoomMode		proc :ptr, :Windows::UI::Xaml::Controls::ZoomMode
    get_IsDeferredScrollingEnabledProperty proc :ptr
    GetIsDeferredScrollingEnabled proc :ptr, :ptr
    SetIsDeferredScrollingEnabled proc :ptr, :boolean
    get_BringIntoViewOnFocusChangeProperty proc :ptr
    GetBringIntoViewOnFocusChange proc :ptr, :ptr
    SetBringIntoViewOnFocusChange proc :ptr, :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewer2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewer2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollViewer2 <L"Windows.UI.Xaml.Controls.IScrollViewer2">
DEFINE_IIDX(IScrollViewer2, "64E9BE10-4DD1-494D-ABF7-CBD3C577491D")

.comdef IScrollViewer2 : public IInspectable

    get_TopLeftHeader	proc :ptr
    put_TopLeftHeader	proc :ptr
    get_LeftHeader	proc :ptr
    put_LeftHeader	proc :ptr
    get_TopHeader	proc :ptr
    put_TopHeader	proc :ptr
    add_ViewChanging	proc :ptr, :ptr
    remove_ViewChanging proc :EventRegistrationToken
    ChangeView		proc :ptr, :ptr, :ptr, :ptr
    ChangeViewWithOptionalAnimation proc :ptr, :ptr, :ptr, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollViewerStatics2 <L"Windows.UI.Xaml.Controls.IScrollViewerStatics2">
DEFINE_IIDX(IScrollViewerStatics2, "33D129AD-8D7E-42A0-BF32-905CCCD04D41")

.comdef IScrollViewerStatics2 : public IInspectable

    get_TopLeftHeaderProperty proc :ptr
    get_LeftHeaderProperty proc :ptr
    get_TopHeaderProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollViewerView <L"Windows.UI.Xaml.Controls.IScrollViewerView">
DEFINE_IIDX(IScrollViewerView, "64E9BE01-4DC2-493E-ABE8-CBD3C577490E")

.comdef IScrollViewerView : public IInspectable

    get_HorizontalOffset proc :ptr
    get_VerticalOffset	proc :ptr
    get_ZoomFactor	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerViewChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerViewChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollViewerViewChangedEventArgs <L"Windows.UI.Xaml.Controls.IScrollViewerViewChangedEventArgs">
DEFINE_IIDX(IScrollViewerViewChangedEventArgs, "4DD04F7E-7A11-4B2E-9933-577DF39252B6")

.comdef IScrollViewerViewChangedEventArgs : public IInspectable

    get_IsIntermediate	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerViewChangingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIScrollViewerViewChangingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IScrollViewerViewChangingEventArgs <L"Windows.UI.Xaml.Controls.IScrollViewerViewChangingEventArgs">
DEFINE_IIDX(IScrollViewerViewChangingEventArgs, "4DD04F7F-7A11-4B2E-9933-577DF39252B6")

.comdef IScrollViewerViewChangingEventArgs : public IInspectable

    get_NextView	proc :ptr
    get_FinalView	proc :ptr
    get_IsInertial	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISelectionChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISelectionChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISelectionChangedEventArgs <L"Windows.UI.Xaml.Controls.ISelectionChangedEventArgs">
DEFINE_IIDX(ISelectionChangedEventArgs, "C972D2DC-B609-4758-851E-A799C21DE97D")

.comdef ISelectionChangedEventArgs : public IInspectable

    get_AddedItems	proc :ptr
    get_RemovedItems	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISelectionChangedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISelectionChangedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISelectionChangedEventArgsFactory <L"Windows.UI.Xaml.Controls.ISelectionChangedEventArgsFactory">
DEFINE_IIDX(ISelectionChangedEventArgsFactory, "11A8B6B5-2830-4517-84CD-5524C8B88B45")

.comdef ISelectionChangedEventArgsFactory : public IInspectable

    CreateInstanceWithRemovedItemsAndAddedItems proc :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoom_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoom_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISemanticZoom <L"Windows.UI.Xaml.Controls.ISemanticZoom">
DEFINE_IIDX(ISemanticZoom, "019FFF21-ECE6-4FBC-BF40-8938D4813E27")

.comdef ISemanticZoom : public IInspectable

    get_ZoomedInView	proc :ptr
    put_ZoomedInView	proc :ptr
    get_ZoomedOutView	proc :ptr
    put_ZoomedOutView	proc :ptr
    get_IsZoomedInViewActive proc :ptr
    put_IsZoomedInViewActive proc :boolean
    get_CanChangeViews	proc :ptr
    put_CanChangeViews	proc :boolean
    add_ViewChangeStarted proc :ptr, :ptr
    remove_ViewChangeStarted proc :EventRegistrationToken
    add_ViewChangeCompleted proc :ptr, :ptr
    remove_ViewChangeCompleted proc :EventRegistrationToken
    ToggleActiveView	proc
    get_IsZoomOutButtonEnabled proc :ptr
    put_IsZoomOutButtonEnabled proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISemanticZoomStatics <L"Windows.UI.Xaml.Controls.ISemanticZoomStatics">
DEFINE_IIDX(ISemanticZoomStatics, "8EF17EF2-9898-4666-B285-3ED38A07910E")

.comdef ISemanticZoomStatics : public IInspectable

    get_ZoomedInViewProperty proc :ptr
    get_ZoomedOutViewProperty proc :ptr
    get_IsZoomedInViewActiveProperty proc :ptr
    get_CanChangeViewsProperty proc :ptr
    get_IsZoomOutButtonEnabledProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomLocation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomLocation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISemanticZoomLocation <L"Windows.UI.Xaml.Controls.ISemanticZoomLocation">
DEFINE_IIDX(ISemanticZoomLocation, "42011736-E3C2-496B-BC4E-D750D4375B9A")

.comdef ISemanticZoomLocation : public IInspectable

    get_Item		proc :ptr
    put_Item		proc :ptr
    get_Bounds		proc :ptr
    put_Bounds		proc :Windows::Foundation::Rect
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomViewChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISemanticZoomViewChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISemanticZoomViewChangedEventArgs <L"Windows.UI.Xaml.Controls.ISemanticZoomViewChangedEventArgs">
DEFINE_IIDX(ISemanticZoomViewChangedEventArgs, "47DFC068-B569-4B19-842D-8E6CF90989AF")

.comdef ISemanticZoomViewChangedEventArgs : public IInspectable

    get_IsSourceZoomedInView proc :ptr
    put_IsSourceZoomedInView proc :boolean
    get_SourceItem	proc :ptr
    put_SourceItem	proc :ptr
    get_DestinationItem proc :ptr
    put_DestinationItem proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISettingsFlyout_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISettingsFlyout_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISettingsFlyout <L"Windows.UI.Xaml.Controls.ISettingsFlyout">
DEFINE_IIDX(ISettingsFlyout, "830BA82B-C55B-4E32-A51C-5791E024C8AF")

.comdef ISettingsFlyout : public IInspectable

    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_HeaderBackground proc :ptr
    put_HeaderBackground proc :ptr
    get_HeaderForeground proc :ptr
    put_HeaderForeground proc :ptr
    get_IconSource	proc :ptr
    put_IconSource	proc :ptr
    get_TemplateSettings proc :ptr
    add_BackClick	proc :ptr, :ptr
    remove_BackClick	proc :EventRegistrationToken
    Show		proc
    ShowIndependent	proc
    Hide		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISettingsFlyoutStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISettingsFlyoutStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISettingsFlyoutStatics <L"Windows.UI.Xaml.Controls.ISettingsFlyoutStatics">
DEFINE_IIDX(ISettingsFlyoutStatics, "D0E3B535-9157-4BE4-A42A-F591698846AC")

.comdef ISettingsFlyoutStatics : public IInspectable

    get_TitleProperty	proc :ptr
    get_HeaderBackgroundProperty proc :ptr
    get_HeaderForegroundProperty proc :ptr
    get_IconSourceProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISettingsFlyoutFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISettingsFlyoutFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISettingsFlyoutFactory <L"Windows.UI.Xaml.Controls.ISettingsFlyoutFactory">
DEFINE_IIDX(ISettingsFlyoutFactory, "480C7011-57AA-4DB6-B6FD-EC676F6D414E")

.comdef ISettingsFlyoutFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISlider_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISlider_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISlider <L"Windows.UI.Xaml.Controls.ISlider">
DEFINE_IIDX(ISlider, "89572027-4C48-4700-8076-497BA73D9C18")

.comdef ISlider : public IInspectable

    get_IntermediateValue proc :ptr
    put_IntermediateValue proc :DOUBLE
    get_StepFrequency	proc :ptr
    put_StepFrequency	proc :DOUBLE
    get_SnapsTo		proc :ptr
    put_SnapsTo		proc :Windows::UI::Xaml::Controls::Primitives::SliderSnapsTo
    get_TickFrequency	proc :ptr
    put_TickFrequency	proc :DOUBLE
    get_TickPlacement	proc :ptr
    put_TickPlacement	proc :Windows::UI::Xaml::Controls::Primitives::TickPlacement
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    get_IsDirectionReversed proc :ptr
    put_IsDirectionReversed proc :boolean
    get_IsThumbToolTipEnabled proc :ptr
    put_IsThumbToolTipEnabled proc :boolean
    get_ThumbToolTipValueConverter proc :ptr
    put_ThumbToolTipValueConverter proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISliderStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISliderStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISliderStatics <L"Windows.UI.Xaml.Controls.ISliderStatics">
DEFINE_IIDX(ISliderStatics, "8A4363D7-7FDF-4D30-98FE-CE78C05B31CF")

.comdef ISliderStatics : public IInspectable

    get_IntermediateValueProperty proc :ptr
    get_StepFrequencyProperty proc :ptr
    get_SnapsToProperty proc :ptr
    get_TickFrequencyProperty proc :ptr
    get_TickPlacementProperty proc :ptr
    get_OrientationProperty proc :ptr
    get_IsDirectionReversedProperty proc :ptr
    get_IsThumbToolTipEnabledProperty proc :ptr
    get_ThumbToolTipValueConverterProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISliderFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISliderFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISliderFactory <L"Windows.UI.Xaml.Controls.ISliderFactory">
DEFINE_IIDX(ISliderFactory, "03A67B37-C7BF-437C-848F-8CB5B753EAB4")

.comdef ISliderFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISlider2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISlider2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISlider2 <L"Windows.UI.Xaml.Controls.ISlider2">
DEFINE_IIDX(ISlider2, "40A3C50E-87D6-4D2F-B1CF-B279CC996F26")

.comdef ISlider2 : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISliderStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISliderStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISliderStatics2 <L"Windows.UI.Xaml.Controls.ISliderStatics2">
DEFINE_IIDX(ISliderStatics2, "00E7935D-79A5-4759-96A6-29E0A94ADD33")

.comdef ISliderStatics2 : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIStackPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIStackPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IStackPanel <L"Windows.UI.Xaml.Controls.IStackPanel">
DEFINE_IIDX(IStackPanel, "B8AE8FE2-D641-4FD7-80B4-7439207D2798")

.comdef IStackPanel : public IInspectable

    get_AreScrollSnapPointsRegular proc :ptr
    put_AreScrollSnapPointsRegular proc :boolean
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIStackPanelStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIStackPanelStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IStackPanelStatics <L"Windows.UI.Xaml.Controls.IStackPanelStatics">
DEFINE_IIDX(IStackPanelStatics, "F0D0CD93-4DBC-48A7-9914-954924657771")

.comdef IStackPanelStatics : public IInspectable

    get_AreScrollSnapPointsRegularProperty proc :ptr
    get_OrientationProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIStackPanelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIStackPanelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IStackPanelFactory <L"Windows.UI.Xaml.Controls.IStackPanelFactory">
DEFINE_IIDX(IStackPanelFactory, "63D8248A-8B34-445A-808F-B6ECD62A27D9")

.comdef IStackPanelFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIStyleSelector_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIStyleSelector_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IStyleSelector <L"Windows.UI.Xaml.Controls.IStyleSelector">
DEFINE_IIDX(IStyleSelector, "D1113F67-D8C1-4AE4-98F0-D8504502F08B")

.comdef IStyleSelector : public IInspectable

    SelectStyle		proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIStyleSelectorOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIStyleSelectorOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IStyleSelectorOverrides <L"Windows.UI.Xaml.Controls.IStyleSelectorOverrides">
DEFINE_IIDX(IStyleSelectorOverrides, "08ADD66D-0E2E-43A0-AECA-8FAA94B9D017")

.comdef IStyleSelectorOverrides : public IInspectable

    SelectStyleCore	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIStyleSelectorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIStyleSelectorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IStyleSelectorFactory <L"Windows.UI.Xaml.Controls.IStyleSelectorFactory">
DEFINE_IIDX(IStyleSelectorFactory, "9E942AE7-3761-447F-8F97-29E39D5EB310")

.comdef IStyleSelectorFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlock_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlock_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBlock <L"Windows.UI.Xaml.Controls.ITextBlock">
DEFINE_IIDX(ITextBlock, "AE2D9271-3B4A-45FC-8468-F7949548F4D5")

.comdef ITextBlock : public IInspectable

    get_FontSize	proc :ptr
    put_FontSize	proc :DOUBLE
    get_FontFamily	proc :ptr
    put_FontFamily	proc :ptr
    get_FontWeight	proc :ptr
    put_FontWeight	proc :Windows::UI::Text::FontWeight
    get_FontStyle	proc :ptr
    put_FontStyle	proc :Windows::UI::Text::FontStyle
    get_FontStretch	proc :ptr
    put_FontStretch	proc :Windows::UI::Text::FontStretch
    get_CharacterSpacing proc :ptr
    put_CharacterSpacing proc :INT32
    get_Foreground	proc :ptr
    put_Foreground	proc :ptr
    get_TextWrapping	proc :ptr
    put_TextWrapping	proc :Windows::UI::Xaml::TextWrapping
    get_TextTrimming	proc :ptr
    put_TextTrimming	proc :Windows::UI::Xaml::TextTrimming
    get_TextAlignment	proc :ptr
    put_TextAlignment	proc :Windows::UI::Xaml::TextAlignment
    get_Text		proc :ptr
    put_Text		proc :HSTRING
    get_Inlines		proc :ptr
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
    get_LineHeight	proc :ptr
    put_LineHeight	proc :DOUBLE
    get_LineStackingStrategy proc :ptr
    put_LineStackingStrategy proc :Windows::UI::Xaml::LineStackingStrategy
    get_IsTextSelectionEnabled proc :ptr
    put_IsTextSelectionEnabled proc :boolean
    get_SelectedText	proc :ptr
    get_ContentStart	proc :ptr
    get_ContentEnd	proc :ptr
    get_SelectionStart	proc :ptr
    get_SelectionEnd	proc :ptr
    get_BaselineOffset	proc :ptr
    add_SelectionChanged proc :ptr, :ptr
    remove_SelectionChanged proc :EventRegistrationToken
    add_ContextMenuOpening proc :ptr, :ptr
    remove_ContextMenuOpening proc :EventRegistrationToken
    SelectAll		proc
    Select		proc :ptr, :ptr
    Focus		proc :Windows::UI::Xaml::FocusState, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlockStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlockStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBlockStatics <L"Windows.UI.Xaml.Controls.ITextBlockStatics">
DEFINE_IIDX(ITextBlockStatics, "193EC042-A847-4552-B4E8-DB36655B840A")

.comdef ITextBlockStatics : public IInspectable

    get_FontSizeProperty proc :ptr
    get_FontFamilyProperty proc :ptr
    get_FontWeightProperty proc :ptr
    get_FontStyleProperty proc :ptr
    get_FontStretchProperty proc :ptr
    get_CharacterSpacingProperty proc :ptr
    get_ForegroundProperty proc :ptr
    get_TextWrappingProperty proc :ptr
    get_TextTrimmingProperty proc :ptr
    get_TextAlignmentProperty proc :ptr
    get_TextProperty	proc :ptr
    get_PaddingProperty proc :ptr
    get_LineHeightProperty proc :ptr
    get_LineStackingStrategyProperty proc :ptr
    get_IsTextSelectionEnabledProperty proc :ptr
    get_SelectedTextProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlock2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlock2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBlock2 <L"Windows.UI.Xaml.Controls.ITextBlock2">
DEFINE_IIDX(ITextBlock2, "45206A4C-0A4E-4FBF-AEE9-335D5A205F6E")

.comdef ITextBlock2 : public IInspectable

    get_SelectionHighlightColor proc :ptr
    put_SelectionHighlightColor proc :ptr
    get_MaxLines	proc :ptr
    put_MaxLines	proc :INT32
    get_TextLineBounds	proc :ptr
    put_TextLineBounds	proc :Windows::UI::Xaml::TextLineBounds
    get_OpticalMarginAlignment proc :ptr
    put_OpticalMarginAlignment proc :Windows::UI::Xaml::OpticalMarginAlignment
    get_IsColorFontEnabled proc :ptr
    put_IsColorFontEnabled proc :boolean
    get_TextReadingOrder proc :ptr
    put_TextReadingOrder proc :Windows::UI::Xaml::TextReadingOrder
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlockStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBlockStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBlockStatics2 <L"Windows.UI.Xaml.Controls.ITextBlockStatics2">
DEFINE_IIDX(ITextBlockStatics2, "88100B1B-FF24-4B93-A0E6-F029C94871F1")

.comdef ITextBlockStatics2 : public IInspectable

    get_SelectionHighlightColorProperty proc :ptr
    get_MaxLinesProperty proc :ptr
    get_TextLineBoundsProperty proc :ptr
    get_OpticalMarginAlignmentProperty proc :ptr
    get_IsColorFontEnabledProperty proc :ptr
    get_TextReadingOrderProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBox <L"Windows.UI.Xaml.Controls.ITextBox">
DEFINE_IIDX(ITextBox, "E48F5A8B-1DFF-4352-A1F4-E516514EC882")

.comdef ITextBox : public IInspectable

    get_Text		proc :ptr
    put_Text		proc :HSTRING
    get_SelectedText	proc :ptr
    put_SelectedText	proc :HSTRING
    get_SelectionLength proc :ptr
    put_SelectionLength proc :INT32
    get_SelectionStart	proc :ptr
    put_SelectionStart	proc :INT32
    get_MaxLength	proc :ptr
    put_MaxLength	proc :INT32
    get_IsReadOnly	proc :ptr
    put_IsReadOnly	proc :boolean
    get_AcceptsReturn	proc :ptr
    put_AcceptsReturn	proc :boolean
    get_TextAlignment	proc :ptr
    put_TextAlignment	proc :Windows::UI::Xaml::TextAlignment
    get_TextWrapping	proc :ptr
    put_TextWrapping	proc :Windows::UI::Xaml::TextWrapping
    get_IsSpellCheckEnabled proc :ptr
    put_IsSpellCheckEnabled proc :boolean
    get_IsTextPredictionEnabled proc :ptr
    put_IsTextPredictionEnabled proc :boolean
    get_InputScope	proc :ptr
    put_InputScope	proc :ptr
    add_TextChanged	proc :ptr, :ptr
    remove_TextChanged	proc :EventRegistrationToken
    add_SelectionChanged proc :ptr, :ptr
    remove_SelectionChanged proc :EventRegistrationToken
    add_ContextMenuOpening proc :ptr, :ptr
    remove_ContextMenuOpening proc :EventRegistrationToken
    Select		proc :INT32, :INT32
    SelectAll		proc
    GetRectFromCharacterIndex proc :INT32, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBoxStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBoxStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBoxStatics <L"Windows.UI.Xaml.Controls.ITextBoxStatics">
DEFINE_IIDX(ITextBoxStatics, "7E37F4FB-A4BC-4625-8838-8EB2A9091283")

.comdef ITextBoxStatics : public IInspectable

    get_TextProperty	proc :ptr
    get_MaxLengthProperty proc :ptr
    get_IsReadOnlyProperty proc :ptr
    get_AcceptsReturnProperty proc :ptr
    get_TextAlignmentProperty proc :ptr
    get_TextWrappingProperty proc :ptr
    get_IsSpellCheckEnabledProperty proc :ptr
    get_IsTextPredictionEnabledProperty proc :ptr
    get_InputScopeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBoxFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBoxFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBoxFactory <L"Windows.UI.Xaml.Controls.ITextBoxFactory">
DEFINE_IIDX(ITextBoxFactory, "710E4278-8529-47D3-8D8E-307E34CFF081")

.comdef ITextBoxFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBox2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBox2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBox2 <L"Windows.UI.Xaml.Controls.ITextBox2">
DEFINE_IIDX(ITextBox2, "F7168C00-1432-462A-9405-38F385BFC37C")

.comdef ITextBox2 : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_PlaceholderText proc :ptr
    put_PlaceholderText proc :HSTRING
    get_SelectionHighlightColor proc :ptr
    put_SelectionHighlightColor proc :ptr
    get_PreventKeyboardDisplayOnProgrammaticFocus proc :ptr
    put_PreventKeyboardDisplayOnProgrammaticFocus proc :boolean
    get_IsColorFontEnabled proc :ptr
    put_IsColorFontEnabled proc :boolean
    add_Paste		proc :ptr, :ptr
    remove_Paste	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBoxStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextBoxStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextBoxStatics2 <L"Windows.UI.Xaml.Controls.ITextBoxStatics2">
DEFINE_IIDX(ITextBoxStatics2, "7592F37D-4E76-4EE4-8E0F-7D6E1A23326B")

.comdef ITextBoxStatics2 : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_PlaceholderTextProperty proc :ptr
    get_SelectionHighlightColorProperty proc :ptr
    get_PreventKeyboardDisplayOnProgrammaticFocusProperty proc :ptr
    get_IsColorFontEnabledProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextChangedEventArgs <L"Windows.UI.Xaml.Controls.ITextChangedEventArgs">
DEFINE_IIDX(ITextChangedEventArgs, "4DD04F7D-7A11-4B2E-9933-577DF39252B6")

.comdef ITextChangedEventArgs : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITextControlPasteEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITextControlPasteEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITextControlPasteEventArgs <L"Windows.UI.Xaml.Controls.ITextControlPasteEventArgs">
DEFINE_IIDX(ITextControlPasteEventArgs, "4BD1D625-221A-477E-BB2C-AD0C1ED125E7")

.comdef ITextControlPasteEventArgs : public IInspectable

    get_Handled		proc :ptr
    put_Handled		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleSwitch_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleSwitch_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToggleSwitch <L"Windows.UI.Xaml.Controls.IToggleSwitch">
DEFINE_IIDX(IToggleSwitch, "331D8F00-C5F9-46A5-B6C8-EDE539304567")

.comdef IToggleSwitch : public IInspectable

    get_IsOn		proc :ptr
    put_IsOn		proc :boolean
    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_OnContent	proc :ptr
    put_OnContent	proc :ptr
    get_OnContentTemplate proc :ptr
    put_OnContentTemplate proc :ptr
    get_OffContent	proc :ptr
    put_OffContent	proc :ptr
    get_OffContentTemplate proc :ptr
    put_OffContentTemplate proc :ptr
    get_TemplateSettings proc :ptr
    add_Toggled		proc :ptr, :ptr
    remove_Toggled	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleSwitchOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleSwitchOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToggleSwitchOverrides <L"Windows.UI.Xaml.Controls.IToggleSwitchOverrides">
DEFINE_IIDX(IToggleSwitchOverrides, "BFD07F53-F8CA-4E47-949E-9E80429B3D16")

.comdef IToggleSwitchOverrides : public IInspectable

    OnToggled		proc
    OnOnContentChanged	proc :ptr, :ptr
    OnOffContentChanged proc :ptr, :ptr
    OnHeaderChanged	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleSwitchStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleSwitchStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToggleSwitchStatics <L"Windows.UI.Xaml.Controls.IToggleSwitchStatics">
DEFINE_IIDX(IToggleSwitchStatics, "1D37147F-97DF-4226-92CA-DDF453D7FD5A")

.comdef IToggleSwitchStatics : public IInspectable

    get_IsOnProperty	proc :ptr
    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_OnContentProperty proc :ptr
    get_OnContentTemplateProperty proc :ptr
    get_OffContentProperty proc :ptr
    get_OffContentTemplateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTip_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTip_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToolTip <L"Windows.UI.Xaml.Controls.IToolTip">
DEFINE_IIDX(IToolTip, "7DE5D75F-4415-429F-B523-699BDB8C30DB")

.comdef IToolTip : public IInspectable

    get_HorizontalOffset proc :ptr
    put_HorizontalOffset proc :DOUBLE
    get_IsOpen		proc :ptr
    put_IsOpen		proc :boolean
    get_Placement	proc :ptr
    put_Placement	proc :Windows::UI::Xaml::Controls::Primitives::PlacementMode
    get_PlacementTarget proc :ptr
    put_PlacementTarget proc :ptr
    get_VerticalOffset	proc :ptr
    put_VerticalOffset	proc :DOUBLE
    get_TemplateSettings proc :ptr
    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
    add_Opened		proc :ptr, :ptr
    remove_Opened	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToolTipStatics <L"Windows.UI.Xaml.Controls.IToolTipStatics">
DEFINE_IIDX(IToolTipStatics, "F00285B8-4BA9-4F4F-86A7-86003813CEB3")

.comdef IToolTipStatics : public IInspectable

    get_HorizontalOffsetProperty proc :ptr
    get_IsOpenProperty	proc :ptr
    get_PlacementProperty proc :ptr
    get_PlacementTargetProperty proc :ptr
    get_VerticalOffsetProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToolTipFactory <L"Windows.UI.Xaml.Controls.IToolTipFactory">
DEFINE_IIDX(IToolTipFactory, "89839403-B538-49E3-A430-3AC037DC6FE0")

.comdef IToolTipFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipService_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipService_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToolTipService <L"Windows.UI.Xaml.Controls.IToolTipService">
DEFINE_IIDX(IToolTipService, "03A55F87-BFCC-4A1E-8FEA-98F610832CEA")

.comdef IToolTipService : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipServiceStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToolTipServiceStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToolTipServiceStatics <L"Windows.UI.Xaml.Controls.IToolTipServiceStatics">
DEFINE_IIDX(IToolTipServiceStatics, "86E649F8-E245-48AA-A8C8-D1073ED76319")

.comdef IToolTipServiceStatics : public IInspectable

    get_PlacementProperty proc :ptr
    GetPlacement	proc :ptr, :ptr
    SetPlacement	proc :ptr, :Windows::UI::Xaml::Controls::Primitives::PlacementMode
    get_PlacementTargetProperty proc :ptr
    GetPlacementTarget	proc :ptr, :ptr
    SetPlacementTarget	proc :ptr, :ptr
    get_ToolTipProperty proc :ptr
    GetToolTip		proc :ptr, :ptr
    SetToolTip		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIUIElementCollection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIUIElementCollection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IUIElementCollection <L"Windows.UI.Xaml.Controls.IUIElementCollection">
DEFINE_IIDX(IUIElementCollection, "D6602D54-88F6-43F6-85D8-A9D914A6DD3B")

.comdef IUIElementCollection : public IInspectable

    Move		proc :UINT32, :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIUserControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIUserControl_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IUserControl <L"Windows.UI.Xaml.Controls.IUserControl">
DEFINE_IIDX(IUserControl, "A7A69EC9-EA35-4679-BF29-F4F09286D314")

.comdef IUserControl : public IInspectable

    get_Content		proc :ptr
    put_Content		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIUserControlStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIUserControlStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IUserControlStatics <L"Windows.UI.Xaml.Controls.IUserControlStatics">
DEFINE_IIDX(IUserControlStatics, "E8887976-2C5C-41CF-BE6A-9E44BEFDF655")

.comdef IUserControlStatics : public IInspectable

    get_ContentProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIUserControlFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIUserControlFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IUserControlFactory <L"Windows.UI.Xaml.Controls.IUserControlFactory">
DEFINE_IIDX(IUserControlFactory, "38B1ED92-A28A-4972-93DF-F4F759B8AFD2")

.comdef IUserControlFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVariableSizedWrapGrid_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVariableSizedWrapGrid_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVariableSizedWrapGrid <L"Windows.UI.Xaml.Controls.IVariableSizedWrapGrid">
DEFINE_IIDX(IVariableSizedWrapGrid, "9CA507C7-23C9-4F01-B80F-BE5C21EEF474")

.comdef IVariableSizedWrapGrid : public IInspectable

    get_ItemHeight	proc :ptr
    put_ItemHeight	proc :DOUBLE
    get_ItemWidth	proc :ptr
    put_ItemWidth	proc :DOUBLE
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    get_HorizontalChildrenAlignment proc :ptr
    put_HorizontalChildrenAlignment proc :Windows::UI::Xaml::HorizontalAlignment
    get_VerticalChildrenAlignment proc :ptr
    put_VerticalChildrenAlignment proc :Windows::UI::Xaml::VerticalAlignment
    get_MaximumRowsOrColumns proc :ptr
    put_MaximumRowsOrColumns proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVariableSizedWrapGridStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVariableSizedWrapGridStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVariableSizedWrapGridStatics <L"Windows.UI.Xaml.Controls.IVariableSizedWrapGridStatics">
DEFINE_IIDX(IVariableSizedWrapGridStatics, "FE9DB859-8127-4AEF-B7A2-949847486E96")

.comdef IVariableSizedWrapGridStatics : public IInspectable

    get_ItemHeightProperty proc :ptr
    get_ItemWidthProperty proc :ptr
    get_OrientationProperty proc :ptr
    get_HorizontalChildrenAlignmentProperty proc :ptr
    get_VerticalChildrenAlignmentProperty proc :ptr
    get_MaximumRowsOrColumnsProperty proc :ptr
    get_RowSpanProperty proc :ptr
    GetRowSpan		proc :ptr, :ptr
    SetRowSpan		proc :ptr, :INT32
    get_ColumnSpanProperty proc :ptr
    GetColumnSpan	proc :ptr, :ptr
    SetColumnSpan	proc :ptr, :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIViewbox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIViewbox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IViewbox <L"Windows.UI.Xaml.Controls.IViewbox">
DEFINE_IIDX(IViewbox, "05252C58-BA9D-4809-9EC3-FA0D16710BA1")

.comdef IViewbox : public IInspectable

    get_Child		proc :ptr
    put_Child		proc :ptr
    get_Stretch		proc :ptr
    put_Stretch		proc :Windows::UI::Xaml::Media::Stretch
    get_StretchDirection proc :ptr
    put_StretchDirection proc :Windows::UI::Xaml::Controls::StretchDirection
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIViewboxStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIViewboxStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IViewboxStatics <L"Windows.UI.Xaml.Controls.IViewboxStatics">
DEFINE_IIDX(IViewboxStatics, "5CD1E72D-E8D3-4865-8F08-B6B2D689ADF1")

.comdef IViewboxStatics : public IInspectable

    get_StretchProperty proc :ptr
    get_StretchDirectionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVirtualizingPanel <L"Windows.UI.Xaml.Controls.IVirtualizingPanel">
DEFINE_IIDX(IVirtualizingPanel, "38AAD50C-12CF-4D1E-A884-C9DF85F07CD9")

.comdef IVirtualizingPanel : public IInspectable

    get_ItemContainerGenerator proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanelOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanelOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVirtualizingPanelOverrides <L"Windows.UI.Xaml.Controls.IVirtualizingPanelOverrides">
DEFINE_IIDX(IVirtualizingPanelOverrides, "5EF6BD7D-677F-408D-A96C-B19507750466")

.comdef IVirtualizingPanelOverrides : public IInspectable

    OnItemsChanged	proc :ptr, :ptr
    OnClearChildren	proc
    BringIndexIntoView	proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanelProtected_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanelProtected_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVirtualizingPanelProtected <L"Windows.UI.Xaml.Controls.IVirtualizingPanelProtected">
DEFINE_IIDX(IVirtualizingPanelProtected, "C9C9AB42-C232-479D-A7C9-5E7611196A45")

.comdef IVirtualizingPanelProtected : public IInspectable

    AddInternalChild	proc :ptr
    InsertInternalChild proc :INT32, :ptr
    RemoveInternalChildRange proc :INT32, :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingPanelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVirtualizingPanelFactory <L"Windows.UI.Xaml.Controls.IVirtualizingPanelFactory">
DEFINE_IIDX(IVirtualizingPanelFactory, "BE19F839-CBD0-43E9-A5D0-0BDBA0FFBD38")

.comdef IVirtualizingPanelFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingStackPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingStackPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVirtualizingStackPanel <L"Windows.UI.Xaml.Controls.IVirtualizingStackPanel">
DEFINE_IIDX(IVirtualizingStackPanel, "7567CD9A-A3B4-4DEA-BB11-549E2C2F919D")

.comdef IVirtualizingStackPanel : public IInspectable

    get_AreScrollSnapPointsRegular proc :ptr
    put_AreScrollSnapPointsRegular proc :boolean
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    add_CleanUpVirtualizedItemEvent proc :ptr, :ptr
    remove_CleanUpVirtualizedItemEvent proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingStackPanelOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingStackPanelOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVirtualizingStackPanelOverrides <L"Windows.UI.Xaml.Controls.IVirtualizingStackPanelOverrides">
DEFINE_IIDX(IVirtualizingStackPanelOverrides, "CBE6F72C-2892-46D1-987F-58CA1081F040")

.comdef IVirtualizingStackPanelOverrides : public IInspectable

    OnCleanUpVirtualizedItem proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingStackPanelStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIVirtualizingStackPanelStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IVirtualizingStackPanelStatics <L"Windows.UI.Xaml.Controls.IVirtualizingStackPanelStatics">
DEFINE_IIDX(IVirtualizingStackPanelStatics, "8314E778-91D3-4D56-AC09-223ADCD2BD3F")

.comdef IVirtualizingStackPanelStatics : public IInspectable

    get_AreScrollSnapPointsRegularProperty proc :ptr
    get_OrientationProperty proc :ptr
    get_VirtualizationModeProperty proc :ptr
    GetVirtualizationMode proc :ptr, :ptr
    SetVirtualizationMode proc :ptr, :Windows::UI::Xaml::Controls::VirtualizationMode
    get_IsVirtualizingProperty proc :ptr
    GetIsVirtualizing	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBar_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBar_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBar <L"Windows.UI.Xaml.Controls.IAppBar">
DEFINE_IIDX(IAppBar, "7B0FC253-86A5-4B43-9872-0B8A6234B74B")

.comdef IAppBar : public IInspectable

    get_IsOpen		proc :ptr
    put_IsOpen		proc :boolean
    get_IsSticky	proc :ptr
    put_IsSticky	proc :boolean
    add_Opened		proc :ptr, :ptr
    remove_Opened	proc :EventRegistrationToken
    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarOverrides <L"Windows.UI.Xaml.Controls.IAppBarOverrides">
DEFINE_IIDX(IAppBarOverrides, "F003E4E2-7B0F-4F4A-970D-AE8A0EAA9B70")

.comdef IAppBarOverrides : public IInspectable

    OnClosed		proc :ptr
    OnOpened		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarStatics <L"Windows.UI.Xaml.Controls.IAppBarStatics">
DEFINE_IIDX(IAppBarStatics, "79BB7E8D-DCA9-4B5F-A448-37B13238ED76")

.comdef IAppBarStatics : public IInspectable

    get_IsOpenProperty	proc :ptr
    get_IsStickyProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarFactory <L"Windows.UI.Xaml.Controls.IAppBarFactory">
DEFINE_IIDX(IAppBarFactory, "614708D1-8E65-43CB-92D7-8EEE17515F8D")

.comdef IAppBarFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarButton_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarButton_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarButton <L"Windows.UI.Xaml.Controls.IAppBarButton">
DEFINE_IIDX(IAppBarButton, "4459A451-69E8-440C-9896-4BB4F5F642D1")

.comdef IAppBarButton : public IInspectable

    get_Label		proc :ptr
    put_Label		proc :HSTRING
    get_Icon		proc :ptr
    put_Icon		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarButtonStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarButtonStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarButtonStatics <L"Windows.UI.Xaml.Controls.IAppBarButtonStatics">
DEFINE_IIDX(IAppBarButtonStatics, "7CCD13E6-5301-407F-874E-DC9160AA07AF")

.comdef IAppBarButtonStatics : public IInspectable

    get_LabelProperty	proc :ptr
    get_IconProperty	proc :ptr
    get_IsCompactProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarButtonFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarButtonFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarButtonFactory <L"Windows.UI.Xaml.Controls.IAppBarButtonFactory">
DEFINE_IIDX(IAppBarButtonFactory, "BDBB1BB6-CB2E-4276-ABD6-7935130510E0")

.comdef IAppBarButtonFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarSeparator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarSeparator_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarSeparator <L"Windows.UI.Xaml.Controls.IAppBarSeparator">
DEFINE_IIDX(IAppBarSeparator, "1B0795A1-1BC1-4D53-95EA-FB0A2CCCC905")

.comdef IAppBarSeparator : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarSeparatorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarSeparatorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarSeparatorStatics <L"Windows.UI.Xaml.Controls.IAppBarSeparatorStatics">
DEFINE_IIDX(IAppBarSeparatorStatics, "37F23484-5B35-4663-A75D-F2D50CB9C619")

.comdef IAppBarSeparatorStatics : public IInspectable

    get_IsCompactProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarSeparatorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarSeparatorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarSeparatorFactory <L"Windows.UI.Xaml.Controls.IAppBarSeparatorFactory">
DEFINE_IIDX(IAppBarSeparatorFactory, "05DA25CD-F407-48DE-8B50-FF87D1E2818F")

.comdef IAppBarSeparatorFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarToggleButton_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarToggleButton_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarToggleButton <L"Windows.UI.Xaml.Controls.IAppBarToggleButton">
DEFINE_IIDX(IAppBarToggleButton, "2E914438-FD53-4B8D-858B-3644269F8E4D")

.comdef IAppBarToggleButton : public IInspectable

    get_Label		proc :ptr
    put_Label		proc :HSTRING
    get_Icon		proc :ptr
    put_Icon		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarToggleButtonStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarToggleButtonStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarToggleButtonStatics <L"Windows.UI.Xaml.Controls.IAppBarToggleButtonStatics">
DEFINE_IIDX(IAppBarToggleButtonStatics, "FE5AAF96-7929-4DA1-AA67-CDDF73A3E4B5")

.comdef IAppBarToggleButtonStatics : public IInspectable

    get_LabelProperty	proc :ptr
    get_IconProperty	proc :ptr
    get_IsCompactProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarToggleButtonFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIAppBarToggleButtonFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IAppBarToggleButtonFactory <L"Windows.UI.Xaml.Controls.IAppBarToggleButtonFactory">
DEFINE_IIDX(IAppBarToggleButtonFactory, "028AA7D4-8F54-45A6-9F90-13605656D793")

.comdef IAppBarToggleButtonFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIBitmapIcon_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIBitmapIcon_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IBitmapIcon <L"Windows.UI.Xaml.Controls.IBitmapIcon">
DEFINE_IIDX(IBitmapIcon, "E8FE17CB-35F7-40F3-A185-48B397B73E68")

.comdef IBitmapIcon : public IInspectable

    get_UriSource	proc :ptr
    put_UriSource	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIBitmapIconStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIBitmapIconStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IBitmapIconStatics <L"Windows.UI.Xaml.Controls.IBitmapIconStatics">
DEFINE_IIDX(IBitmapIconStatics, "E072D117-E4E7-4E0C-9470-53FF1CE84F67")

.comdef IBitmapIconStatics : public IInspectable

    get_UriSourceProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIBitmapIconFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIBitmapIconFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IBitmapIconFactory <L"Windows.UI.Xaml.Controls.IBitmapIconFactory">
DEFINE_IIDX(IBitmapIconFactory, "46D64B1D-7A49-4F66-9729-2848C788E402")

.comdef IBitmapIconFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBar_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBar_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICommandBar <L"Windows.UI.Xaml.Controls.ICommandBar">
DEFINE_IIDX(ICommandBar, "98BC4280-4A3D-4CEE-BD07-22CE94C5AF76")

.comdef ICommandBar : public IInspectable

    get_PrimaryCommands proc :ptr
    get_SecondaryCommands proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBarElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBarElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICommandBarElement <L"Windows.UI.Xaml.Controls.ICommandBarElement">
DEFINE_IIDX(ICommandBarElement, "67918E1B-F2D5-44D1-8B84-92B87F80A350")

.comdef ICommandBarElement : public IInspectable

    get_IsCompact	proc :ptr
    put_IsCompact	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBarStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBarStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICommandBarStatics <L"Windows.UI.Xaml.Controls.ICommandBarStatics">
DEFINE_IIDX(ICommandBarStatics, "5BD981EA-E278-409C-B522-F946CA253B44")

.comdef ICommandBarStatics : public IInspectable

    get_PrimaryCommandsProperty proc :ptr
    get_SecondaryCommandsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBarFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CICommandBarFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ICommandBarFactory <L"Windows.UI.Xaml.Controls.ICommandBarFactory">
DEFINE_IIDX(ICommandBarFactory, "67BDEB44-20E1-4177-AD44-F617B374E8E8")

.comdef ICommandBarFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyout_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyout_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlyout <L"Windows.UI.Xaml.Controls.IFlyout">
DEFINE_IIDX(IFlyout, "6584EBDF-CBC7-4E19-843A-A14F24A793EA")

.comdef IFlyout : public IInspectable

    get_Content		proc :ptr
    put_Content		proc :ptr
    get_FlyoutPresenterStyle proc :ptr
    put_FlyoutPresenterStyle proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlyoutStatics <L"Windows.UI.Xaml.Controls.IFlyoutStatics">
DEFINE_IIDX(IFlyoutStatics, "61364E0B-DB75-47E1-B2C3-5B901C3D74B6")

.comdef IFlyoutStatics : public IInspectable

    get_ContentProperty proc :ptr
    get_FlyoutPresenterStyleProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlyoutFactory <L"Windows.UI.Xaml.Controls.IFlyoutFactory">
DEFINE_IIDX(IFlyoutFactory, "4BED4933-008E-4B03-A385-79FE5266DDBA")

.comdef IFlyoutFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlyoutPresenter <L"Windows.UI.Xaml.Controls.IFlyoutPresenter">
DEFINE_IIDX(IFlyoutPresenter, "827D5B79-E37B-46A5-8D44-63A11A580E83")

.comdef IFlyoutPresenter : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutPresenterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFlyoutPresenterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFlyoutPresenterFactory <L"Windows.UI.Xaml.Controls.IFlyoutPresenterFactory">
DEFINE_IIDX(IFlyoutPresenterFactory, "EE4D668F-DA76-469A-ACD7-3060E613ADE7")

.comdef IFlyoutPresenterFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFontIcon_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFontIcon_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFontIcon <L"Windows.UI.Xaml.Controls.IFontIcon">
DEFINE_IIDX(IFontIcon, "D4D61391-39AC-4950-9166-3606C264418B")

.comdef IFontIcon : public IInspectable

    get_Glyph		proc :ptr
    put_Glyph		proc :HSTRING
    get_FontSize	proc :ptr
    put_FontSize	proc :DOUBLE
    get_FontFamily	proc :ptr
    put_FontFamily	proc :ptr
    get_FontWeight	proc :ptr
    put_FontWeight	proc :Windows::UI::Text::FontWeight
    get_FontStyle	proc :ptr
    put_FontStyle	proc :Windows::UI::Text::FontStyle
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFontIconStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFontIconStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFontIconStatics <L"Windows.UI.Xaml.Controls.IFontIconStatics">
DEFINE_IIDX(IFontIconStatics, "B3BE7BF6-1467-4086-BBCB-4E21D97A7B4D")

.comdef IFontIconStatics : public IInspectable

    get_GlyphProperty	proc :ptr
    get_FontSizeProperty proc :ptr
    get_FontFamilyProperty proc :ptr
    get_FontWeightProperty proc :ptr
    get_FontStyleProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFontIconFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFontIconFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFontIconFactory <L"Windows.UI.Xaml.Controls.IFontIconFactory">
DEFINE_IIDX(IFontIconFactory, "1C781B6B-37BF-4DDC-A1A8-1B77DB3CF0EA")

.comdef IFontIconFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrame_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrame_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFrame <L"Windows.UI.Xaml.Controls.IFrame">
DEFINE_IIDX(IFrame, "68EA500B-3FE9-4735-B6A0-E7601933B089")

.comdef IFrame : public IInspectable

    get_CacheSize	proc :ptr
    put_CacheSize	proc :INT32
    get_CanGoBack	proc :ptr
    get_CanGoForward	proc :ptr
    get_CurrentSourcePageType proc :ptr
    get_SourcePageType	proc :ptr
    put_SourcePageType	proc :Windows::UI::Xaml::Interop::TypeName
    get_BackStackDepth	proc :ptr
    add_Navigated	proc :ptr, :ptr
    remove_Navigated	proc :EventRegistrationToken
    add_Navigating	proc :ptr, :ptr
    remove_Navigating	proc :EventRegistrationToken
    add_NavigationFailed proc :ptr, :ptr
    remove_NavigationFailed proc :EventRegistrationToken
    add_NavigationStopped proc :ptr, :ptr
    remove_NavigationStopped proc :EventRegistrationToken
    GoBack		proc
    GoForward		proc
    Navigate		proc :Windows::UI::Xaml::Interop::TypeName, :ptr, :ptr
    GetNavigationState	proc :ptr
    SetNavigationState	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrameStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrameStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFrameStatics <L"Windows.UI.Xaml.Controls.IFrameStatics">
DEFINE_IIDX(IFrameStatics, "D5ACF0E9-D967-471B-8459-C8AF4341511B")

.comdef IFrameStatics : public IInspectable

    get_CacheSizeProperty proc :ptr
    get_CanGoBackProperty proc :ptr
    get_CanGoForwardProperty proc :ptr
    get_CurrentSourcePageTypeProperty proc :ptr
    get_SourcePageTypeProperty proc :ptr
    get_BackStackDepthProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrameFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrameFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFrameFactory <L"Windows.UI.Xaml.Controls.IFrameFactory">
DEFINE_IIDX(IFrameFactory, "02EE93D4-448E-469E-9799-0A8A1F70F171")

.comdef IFrameFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrame2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrame2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFrame2 <L"Windows.UI.Xaml.Controls.IFrame2">
DEFINE_IIDX(IFrame2, "3F367F87-9F5A-4B04-B818-B554C069597A")

.comdef IFrame2 : public IInspectable

    get_BackStack	proc :ptr
    get_ForwardStack	proc :ptr
    Navigate		proc :Windows::UI::Xaml::Interop::TypeName, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrameStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIFrameStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IFrameStatics2 <L"Windows.UI.Xaml.Controls.IFrameStatics2">
DEFINE_IIDX(IFrameStatics2, "E4B5CDFE-42F0-4462-A1C1-5D259DD82A03")

.comdef IFrameStatics2 : public IInspectable

    get_BackStackProperty proc :ptr
    get_ForwardStackProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewHeaderItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewHeaderItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridViewHeaderItem <L"Windows.UI.Xaml.Controls.IGridViewHeaderItem">
DEFINE_IIDX(IGridViewHeaderItem, "72D75D7E-5DC3-4FFC-9B1C-939B5C37161C")

.comdef IGridViewHeaderItem : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewHeaderItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIGridViewHeaderItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IGridViewHeaderItemFactory <L"Windows.UI.Xaml.Controls.IGridViewHeaderItemFactory">
DEFINE_IIDX(IGridViewHeaderItemFactory, "36E0C96E-B56A-4B3B-8BAC-7AEF5E6F9945")

.comdef IGridViewHeaderItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHub_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHub_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHub <L"Windows.UI.Xaml.Controls.IHub">
DEFINE_IIDX(IHub, "AE692E82-7314-4F51-AB11-2AF1ED4A19F8")

.comdef IHub : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    get_DefaultSectionIndex proc :ptr
    put_DefaultSectionIndex proc :INT32
    get_Sections	proc :ptr
    get_SectionsInView	proc :ptr
    get_SectionHeaders	proc :ptr
    add_SectionHeaderClick proc :ptr, :ptr
    remove_SectionHeaderClick proc :EventRegistrationToken
    add_SectionsInViewChanged proc :ptr, :ptr
    remove_SectionsInViewChanged proc :EventRegistrationToken
    ScrollToSection	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHubStatics <L"Windows.UI.Xaml.Controls.IHubStatics">
DEFINE_IIDX(IHubStatics, "0E6FA034-AD3C-4F32-B701-E24FAB562028")

.comdef IHubStatics : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_OrientationProperty proc :ptr
    get_DefaultSectionIndexProperty proc :ptr
    get_SemanticZoomOwnerProperty proc :ptr
    get_IsActiveViewProperty proc :ptr
    get_IsZoomedInViewProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHubFactory <L"Windows.UI.Xaml.Controls.IHubFactory">
DEFINE_IIDX(IHubFactory, "DCA6B2BA-C6F5-4961-9953-C51873DB5424")

.comdef IHubFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHubSection <L"Windows.UI.Xaml.Controls.IHubSection">
DEFINE_IIDX(IHubSection, "A4E66CB7-7FDD-4FE0-AB49-C246639DCCF9")

.comdef IHubSection : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_ContentTemplate proc :ptr
    put_ContentTemplate proc :ptr
    get_IsHeaderInteractive proc :ptr
    put_IsHeaderInteractive proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHubSectionStatics <L"Windows.UI.Xaml.Controls.IHubSectionStatics">
DEFINE_IIDX(IHubSectionStatics, "12D2D85A-EA27-42D1-998B-61E52AED842B")

.comdef IHubSectionStatics : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_ContentTemplateProperty proc :ptr
    get_IsHeaderInteractiveProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHubSectionFactory <L"Windows.UI.Xaml.Controls.IHubSectionFactory">
DEFINE_IIDX(IHubSectionFactory, "FFF55FA2-ECE4-4BBA-AA3B-9804AEF47883")

.comdef IHubSectionFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionHeaderClickEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIHubSectionHeaderClickEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IHubSectionHeaderClickEventArgs <L"Windows.UI.Xaml.Controls.IHubSectionHeaderClickEventArgs">
DEFINE_IIDX(IHubSectionHeaderClickEventArgs, "E1C5EF04-1EDD-4112-AEEB-996C96400698")

.comdef IHubSectionHeaderClickEventArgs : public IInspectable

    get_Section		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIIconElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIIconElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IIconElement <L"Windows.UI.Xaml.Controls.IIconElement">
DEFINE_IIDX(IIconElement, "9AF0803B-D04C-467A-BBD5-9B81F02D9A56")

.comdef IIconElement : public IInspectable

    get_Foreground	proc :ptr
    put_Foreground	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIIconElementStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIIconElementStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IIconElementStatics <L"Windows.UI.Xaml.Controls.IIconElementStatics">
DEFINE_IIDX(IIconElementStatics, "BE19A623-77CF-472F-82EA-047801D12012")

.comdef IIconElementStatics : public IInspectable

    get_ForegroundProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIIconElementFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIIconElementFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IIconElementFactory <L"Windows.UI.Xaml.Controls.IIconElementFactory">
DEFINE_IIDX(IIconElementFactory, "CF37A562-0424-43C7-8BEA-720FBA973EF1")

.comdef IIconElementFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsStackPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsStackPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsStackPanel <L"Windows.UI.Xaml.Controls.IItemsStackPanel">
DEFINE_IIDX(IItemsStackPanel, "DF7AB79D-7AD5-4B58-9363-919AF90226E6")

.comdef IItemsStackPanel : public IInspectable

    get_GroupPadding	proc :ptr
    put_GroupPadding	proc :Windows::UI::Xaml::Thickness
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    get_FirstCacheIndex proc :ptr
    get_FirstVisibleIndex proc :ptr
    get_LastVisibleIndex proc :ptr
    get_LastCacheIndex	proc :ptr
    get_ScrollingDirection proc :ptr
    get_GroupHeaderPlacement proc :ptr
    put_GroupHeaderPlacement proc :Windows::UI::Xaml::Controls::Primitives::GroupHeaderPlacement
    get_ItemsUpdatingScrollMode proc :ptr
    put_ItemsUpdatingScrollMode proc :Windows::UI::Xaml::Controls::ItemsUpdatingScrollMode
    get_CacheLength	proc :ptr
    put_CacheLength	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsStackPanelStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsStackPanelStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsStackPanelStatics <L"Windows.UI.Xaml.Controls.IItemsStackPanelStatics">
DEFINE_IIDX(IItemsStackPanelStatics, "CA25D63F-044F-4B6B-B315-0B60E0B4F87D")

.comdef IItemsStackPanelStatics : public IInspectable

    get_GroupPaddingProperty proc :ptr
    get_OrientationProperty proc :ptr
    get_GroupHeaderPlacementProperty proc :ptr
    get_CacheLengthProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsWrapGrid_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsWrapGrid_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsWrapGrid <L"Windows.UI.Xaml.Controls.IItemsWrapGrid">
DEFINE_IIDX(IItemsWrapGrid, "DDFE6B5F-BA88-4A7D-8A5B-E58CAF0F4E2D")

.comdef IItemsWrapGrid : public IInspectable

    get_GroupPadding	proc :ptr
    put_GroupPadding	proc :Windows::UI::Xaml::Thickness
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    get_MaximumRowsOrColumns proc :ptr
    put_MaximumRowsOrColumns proc :INT32
    get_ItemWidth	proc :ptr
    put_ItemWidth	proc :DOUBLE
    get_ItemHeight	proc :ptr
    put_ItemHeight	proc :DOUBLE
    get_FirstCacheIndex proc :ptr
    get_FirstVisibleIndex proc :ptr
    get_LastVisibleIndex proc :ptr
    get_LastCacheIndex	proc :ptr
    get_ScrollingDirection proc :ptr
    get_GroupHeaderPlacement proc :ptr
    put_GroupHeaderPlacement proc :Windows::UI::Xaml::Controls::Primitives::GroupHeaderPlacement
    get_CacheLength	proc :ptr
    put_CacheLength	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsWrapGridStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIItemsWrapGridStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IItemsWrapGridStatics <L"Windows.UI.Xaml.Controls.IItemsWrapGridStatics">
DEFINE_IIDX(IItemsWrapGridStatics, "4EC5427D-24A0-449A-B763-3077BA0F2DD5")

.comdef IItemsWrapGridStatics : public IInspectable

    get_GroupPaddingProperty proc :ptr
    get_OrientationProperty proc :ptr
    get_MaximumRowsOrColumnsProperty proc :ptr
    get_ItemWidthProperty proc :ptr
    get_ItemHeightProperty proc :ptr
    get_GroupHeaderPlacementProperty proc :ptr
    get_CacheLengthProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseHeaderItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseHeaderItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewBaseHeaderItem <L"Windows.UI.Xaml.Controls.IListViewBaseHeaderItem">
DEFINE_IIDX(IListViewBaseHeaderItem, "6D0DED27-0D19-4091-8917-CE7C85C1E630")

.comdef IListViewBaseHeaderItem : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseHeaderItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewBaseHeaderItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewBaseHeaderItemFactory <L"Windows.UI.Xaml.Controls.IListViewBaseHeaderItemFactory">
DEFINE_IIDX(IListViewBaseHeaderItemFactory, "3872A6A1-EA19-455F-9DF7-147CC41D329C")

.comdef IListViewBaseHeaderItemFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewHeaderItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewHeaderItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewHeaderItem <L"Windows.UI.Xaml.Controls.IListViewHeaderItem">
DEFINE_IIDX(IListViewHeaderItem, "1B61BAEB-E196-4B3B-A5F9-1ED636F3F79B")

.comdef IListViewHeaderItem : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewHeaderItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIListViewHeaderItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IListViewHeaderItemFactory <L"Windows.UI.Xaml.Controls.IListViewHeaderItemFactory">
DEFINE_IIDX(IListViewHeaderItemFactory, "68D2C96A-96B0-4F08-A7A5-F1086720A0FA")

.comdef IListViewHeaderItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyout_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyout_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyout <L"Windows.UI.Xaml.Controls.IMenuFlyout">
DEFINE_IIDX(IMenuFlyout, "AD3210F1-985B-4171-BBBA-67BCC729649B")

.comdef IMenuFlyout : public IInspectable

    get_Items		proc :ptr
    get_MenuFlyoutPresenterStyle proc :ptr
    put_MenuFlyoutPresenterStyle proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutStatics <L"Windows.UI.Xaml.Controls.IMenuFlyoutStatics">
DEFINE_IIDX(IMenuFlyoutStatics, "3DBEFBA1-9522-4045-9E58-C99B13AAB9B9")

.comdef IMenuFlyoutStatics : public IInspectable

    get_MenuFlyoutPresenterStyleProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutFactory <L"Windows.UI.Xaml.Controls.IMenuFlyoutFactory">
DEFINE_IIDX(IMenuFlyoutFactory, "644533AB-BBB9-499B-9FF3-30D40E2C56D8")

.comdef IMenuFlyoutFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutItem <L"Windows.UI.Xaml.Controls.IMenuFlyoutItem">
DEFINE_IIDX(IMenuFlyoutItem, "160775CF-B598-44AF-A488-C3CE2AF6D3F0")

.comdef IMenuFlyoutItem : public IInspectable

    get_Text		proc :ptr
    put_Text		proc :HSTRING
    get_Command		proc :ptr
    put_Command		proc :ptr
    get_CommandParameter proc :ptr
    put_CommandParameter proc :ptr
    add_Click		proc :ptr, :ptr
    remove_Click	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutItemStatics <L"Windows.UI.Xaml.Controls.IMenuFlyoutItemStatics">
DEFINE_IIDX(IMenuFlyoutItemStatics, "4950B424-A43A-41F7-AA3A-9CE9619747D5")

.comdef IMenuFlyoutItemStatics : public IInspectable

    get_TextProperty	proc :ptr
    get_CommandProperty proc :ptr
    get_CommandParameterProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutItemFactory <L"Windows.UI.Xaml.Controls.IMenuFlyoutItemFactory">
DEFINE_IIDX(IMenuFlyoutItemFactory, "C5AA39E2-44F3-455E-9C5B-62BB6AFCE3AD")

.comdef IMenuFlyoutItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutItemBase <L"Windows.UI.Xaml.Controls.IMenuFlyoutItemBase">
DEFINE_IIDX(IMenuFlyoutItemBase, "F9B56047-8DA6-4730-9208-144125C6B396")

.comdef IMenuFlyoutItemBase : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutItemBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutItemBaseFactory <L"Windows.UI.Xaml.Controls.IMenuFlyoutItemBaseFactory">
DEFINE_IIDX(IMenuFlyoutItemBaseFactory, "83E6DBAD-FC67-41D5-8797-60ACD1CEB1D9")

.comdef IMenuFlyoutItemBaseFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutPresenter <L"Windows.UI.Xaml.Controls.IMenuFlyoutPresenter">
DEFINE_IIDX(IMenuFlyoutPresenter, "906E0304-254E-413F-B219-C7B97F003752")

.comdef IMenuFlyoutPresenter : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutPresenterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutPresenterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutPresenterFactory <L"Windows.UI.Xaml.Controls.IMenuFlyoutPresenterFactory">
DEFINE_IIDX(IMenuFlyoutPresenterFactory, "B88B5091-101C-41F8-AAC1-1B105C14FB99")

.comdef IMenuFlyoutPresenterFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutSeparator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutSeparator_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutSeparator <L"Windows.UI.Xaml.Controls.IMenuFlyoutSeparator">
DEFINE_IIDX(IMenuFlyoutSeparator, "71FA2B7D-0B51-4950-A1A4-BBC42EAC4C12")

.comdef IMenuFlyoutSeparator : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutSeparatorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIMenuFlyoutSeparatorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IMenuFlyoutSeparatorFactory <L"Windows.UI.Xaml.Controls.IMenuFlyoutSeparatorFactory">
DEFINE_IIDX(IMenuFlyoutSeparatorFactory, "C159DCC8-B437-44E0-B24B-5720AEA1DBAC")

.comdef IMenuFlyoutSeparatorFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPage_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPage <L"Windows.UI.Xaml.Controls.IPage">
DEFINE_IIDX(IPage, "C4B27075-E641-453E-824D-012FC7CF95CF")

.comdef IPage : public IInspectable

    get_Frame		proc :ptr
    get_NavigationCacheMode proc :ptr
    put_NavigationCacheMode proc :Windows::UI::Xaml::Navigation::NavigationCacheMode
    get_TopAppBar	proc :ptr
    put_TopAppBar	proc :ptr
    get_BottomAppBar	proc :ptr
    put_BottomAppBar	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPageOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPageOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPageOverrides <L"Windows.UI.Xaml.Controls.IPageOverrides">
DEFINE_IIDX(IPageOverrides, "230B9CB8-3419-4306-AABE-4A8E680D3627")

.comdef IPageOverrides : public IInspectable

    OnNavigatedFrom	proc :ptr
    OnNavigatedTo	proc :ptr
    OnNavigatingFrom	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPageStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPageStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPageStatics <L"Windows.UI.Xaml.Controls.IPageStatics">
DEFINE_IIDX(IPageStatics, "376DDE71-F725-46DD-8D80-EEEAF7DA74E5")

.comdef IPageStatics : public IInspectable

    get_FrameProperty	proc :ptr
    get_TopAppBarProperty proc :ptr
    get_BottomAppBarProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPageFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPageFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPageFactory <L"Windows.UI.Xaml.Controls.IPageFactory">
DEFINE_IIDX(IPageFactory, "DFA149AC-1849-445E-937C-40A9590CC076")

.comdef IPageFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPathIcon_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPathIcon_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPathIcon <L"Windows.UI.Xaml.Controls.IPathIcon">
DEFINE_IIDX(IPathIcon, "214C62DB-C366-4A0E-B9AD-DCF168D7EC0C")

.comdef IPathIcon : public IInspectable

    get_Data		proc :ptr
    put_Data		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPathIconStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPathIconStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPathIconStatics <L"Windows.UI.Xaml.Controls.IPathIconStatics">
DEFINE_IIDX(IPathIconStatics, "77B75DB8-FB15-491A-B6E3-7DBBA911BAFE")

.comdef IPathIconStatics : public IInspectable

    get_DataProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIPathIconFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIPathIconFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IPathIconFactory <L"Windows.UI.Xaml.Controls.IPathIconFactory">
DEFINE_IIDX(IPathIconFactory, "AF9D9652-9C5D-4A37-9E1A-044ABEEF792B")

.comdef IPathIconFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBox_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBox_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISearchBox <L"Windows.UI.Xaml.Controls.ISearchBox">
DEFINE_IIDX(ISearchBox, "F89ECC5A-99BA-4BD4-966C-F11FA443D13C")

.comdef ISearchBox : public IInspectable

    get_SearchHistoryEnabled proc :ptr
    put_SearchHistoryEnabled proc :boolean
    get_SearchHistoryContext proc :ptr
    put_SearchHistoryContext proc :HSTRING
    get_PlaceholderText proc :ptr
    put_PlaceholderText proc :HSTRING
    get_QueryText	proc :ptr
    put_QueryText	proc :HSTRING
    get_FocusOnKeyboardInput proc :ptr
    put_FocusOnKeyboardInput proc :boolean
    get_ChooseSuggestionOnEnter proc :ptr
    put_ChooseSuggestionOnEnter proc :boolean
    add_QueryChanged	proc :ptr, :ptr
    remove_QueryChanged proc :EventRegistrationToken
    add_SuggestionsRequested proc :ptr, :ptr
    remove_SuggestionsRequested proc :EventRegistrationToken
    add_QuerySubmitted	proc :ptr, :ptr
    remove_QuerySubmitted proc :EventRegistrationToken
    add_ResultSuggestionChosen proc :ptr, :ptr
    remove_ResultSuggestionChosen proc :EventRegistrationToken
    add_PrepareForFocusOnKeyboardInput proc :ptr, :ptr
    remove_PrepareForFocusOnKeyboardInput proc :EventRegistrationToken
    SetLocalContentSuggestionSettings proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISearchBoxStatics <L"Windows.UI.Xaml.Controls.ISearchBoxStatics">
DEFINE_IIDX(ISearchBoxStatics, "B123634F-6871-48CD-92DF-4CFF22459082")

.comdef ISearchBoxStatics : public IInspectable

    get_SearchHistoryEnabledProperty proc :ptr
    get_SearchHistoryContextProperty proc :ptr
    get_PlaceholderTextProperty proc :ptr
    get_QueryTextProperty proc :ptr
    get_FocusOnKeyboardInputProperty proc :ptr
    get_ChooseSuggestionOnEnterProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISearchBoxFactory <L"Windows.UI.Xaml.Controls.ISearchBoxFactory">
DEFINE_IIDX(ISearchBoxFactory, "CD743F6D-8685-46B4-9DDD-202F6941B701")

.comdef ISearchBoxFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxQueryChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxQueryChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISearchBoxQueryChangedEventArgs <L"Windows.UI.Xaml.Controls.ISearchBoxQueryChangedEventArgs">
DEFINE_IIDX(ISearchBoxQueryChangedEventArgs, "A9A70F8F-0CB0-4BD2-9998-2FB57AD5E731")

.comdef ISearchBoxQueryChangedEventArgs : public IInspectable

    get_QueryText	proc :ptr
    get_Language	proc :ptr
    get_LinguisticDetails proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxQuerySubmittedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxQuerySubmittedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISearchBoxQuerySubmittedEventArgs <L"Windows.UI.Xaml.Controls.ISearchBoxQuerySubmittedEventArgs">
DEFINE_IIDX(ISearchBoxQuerySubmittedEventArgs, "126E90FD-3C4E-4CCB-9AEF-4705D19FE548")

.comdef ISearchBoxQuerySubmittedEventArgs : public IInspectable

    get_QueryText	proc :ptr
    get_Language	proc :ptr
    get_LinguisticDetails proc :ptr
    get_KeyModifiers	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxResultSuggestionChosenEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxResultSuggestionChosenEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISearchBoxResultSuggestionChosenEventArgs <L"Windows.UI.Xaml.Controls.ISearchBoxResultSuggestionChosenEventArgs">
DEFINE_IIDX(ISearchBoxResultSuggestionChosenEventArgs, "18918C23-E4C3-4662-A03B-D054FFD0F905")

.comdef ISearchBoxResultSuggestionChosenEventArgs : public IInspectable

    get_Tag		proc :ptr
    get_KeyModifiers	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxSuggestionsRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISearchBoxSuggestionsRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISearchBoxSuggestionsRequestedEventArgs <L"Windows.UI.Xaml.Controls.ISearchBoxSuggestionsRequestedEventArgs">
DEFINE_IIDX(ISearchBoxSuggestionsRequestedEventArgs, "DA15170E-E566-48CB-BD11-FE4B0F30A44D")

.comdef ISearchBoxSuggestionsRequestedEventArgs : public IInspectable

    get_QueryText	proc :ptr
    get_Language	proc :ptr
    get_LinguisticDetails proc :ptr
    get_Request		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISectionsInViewChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISectionsInViewChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISectionsInViewChangedEventArgs <L"Windows.UI.Xaml.Controls.ISectionsInViewChangedEventArgs">
DEFINE_IIDX(ISectionsInViewChangedEventArgs, "DD49EE6B-D165-430F-A37D-B807064F85E1")

.comdef ISectionsInViewChangedEventArgs : public IInspectable

    get_AddedSections	proc :ptr
    get_RemovedSections proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISectionsInViewChangedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISectionsInViewChangedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISectionsInViewChangedEventArgsFactory <L"Windows.UI.Xaml.Controls.ISectionsInViewChangedEventArgsFactory">
DEFINE_IIDX(ISectionsInViewChangedEventArgsFactory, "557F5244-92F8-4150-B730-E6346E8F50D1")

.comdef ISectionsInViewChangedEventArgsFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainBackgroundPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainBackgroundPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISwapChainBackgroundPanel <L"Windows.UI.Xaml.Controls.ISwapChainBackgroundPanel">
DEFINE_IIDX(ISwapChainBackgroundPanel, "1C59DB48-8233-4C0C-BCF5-02A5FB35AE00")

.comdef ISwapChainBackgroundPanel : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainBackgroundPanelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainBackgroundPanelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISwapChainBackgroundPanelFactory <L"Windows.UI.Xaml.Controls.ISwapChainBackgroundPanelFactory">
DEFINE_IIDX(ISwapChainBackgroundPanelFactory, "198289D4-C89B-49B2-896C-5917BF8ADCAE")

.comdef ISwapChainBackgroundPanelFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainBackgroundPanel2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainBackgroundPanel2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISwapChainBackgroundPanel2 <L"Windows.UI.Xaml.Controls.ISwapChainBackgroundPanel2">
DEFINE_IIDX(ISwapChainBackgroundPanel2, "21E672F2-2592-4C38-870F-28FBCF52C095")

.comdef ISwapChainBackgroundPanel2 : public IInspectable

    CreateCoreIndependentInputSource proc :Windows::UI::Core::CoreInputDeviceTypes, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISwapChainPanel <L"Windows.UI.Xaml.Controls.ISwapChainPanel">
DEFINE_IIDX(ISwapChainPanel, "C589644F-EBA8-427A-B75A-9F1F93A11AE9")

.comdef ISwapChainPanel : public IInspectable

    get_CompositionScaleX proc :ptr
    get_CompositionScaleY proc :ptr
    add_CompositionScaleChanged proc :ptr, :ptr
    remove_CompositionScaleChanged proc :EventRegistrationToken
    CreateCoreIndependentInputSource proc :Windows::UI::Core::CoreInputDeviceTypes, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainPanelStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainPanelStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISwapChainPanelStatics <L"Windows.UI.Xaml.Controls.ISwapChainPanelStatics">
DEFINE_IIDX(ISwapChainPanelStatics, "F89C0297-EEA8-498C-99C4-257E3660DF7E")

.comdef ISwapChainPanelStatics : public IInspectable

    get_CompositionScaleXProperty proc :ptr
    get_CompositionScaleYProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainPanelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISwapChainPanelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISwapChainPanelFactory <L"Windows.UI.Xaml.Controls.ISwapChainPanelFactory">
DEFINE_IIDX(ISwapChainPanelFactory, "F38F8D7F-1A48-49CB-86D2-10EAAAF6FD70")

.comdef ISwapChainPanelFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISymbolIcon_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISymbolIcon_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISymbolIcon <L"Windows.UI.Xaml.Controls.ISymbolIcon">
DEFINE_IIDX(ISymbolIcon, "7A4774C9-A6A3-4B30-8FF1-9081D70E9A5C")

.comdef ISymbolIcon : public IInspectable

    get_Symbol		proc :ptr
    put_Symbol		proc :Windows::UI::Xaml::Controls::Symbol
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISymbolIconStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISymbolIconStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISymbolIconStatics <L"Windows.UI.Xaml.Controls.ISymbolIconStatics">
DEFINE_IIDX(ISymbolIconStatics, "8624FBDF-952C-4F76-B03F-30833BE99572")

.comdef ISymbolIconStatics : public IInspectable

    get_SymbolProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CISymbolIconFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CISymbolIconFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ISymbolIconFactory <L"Windows.UI.Xaml.Controls.ISymbolIconFactory">
DEFINE_IIDX(ISymbolIconFactory, "C7252B88-E76C-4B44-8A05-046B9DC772B8")

.comdef ISymbolIconFactory : public IInspectable

    CreateInstanceWithSymbol proc :Windows::UI::Xaml::Controls::Symbol, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePicker_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePicker_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITimePicker <L"Windows.UI.Xaml.Controls.ITimePicker">
DEFINE_IIDX(ITimePicker, "E39099F2-3AFF-4792-909E-2D9941EC0357")

.comdef ITimePicker : public IInspectable

    get_Header		proc :ptr
    put_Header		proc :ptr
    get_HeaderTemplate	proc :ptr
    put_HeaderTemplate	proc :ptr
    get_ClockIdentifier proc :ptr
    put_ClockIdentifier proc :HSTRING
    get_MinuteIncrement proc :ptr
    put_MinuteIncrement proc :INT32
    get_Time		proc :ptr
    put_Time		proc :Windows::Foundation::TimeSpan
    add_TimeChanged	proc :ptr, :ptr
    remove_TimeChanged	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePickerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePickerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITimePickerStatics <L"Windows.UI.Xaml.Controls.ITimePickerStatics">
DEFINE_IIDX(ITimePickerStatics, "FA71DFB1-233E-4F31-B8BE-A6EA670C25CD")

.comdef ITimePickerStatics : public IInspectable

    get_HeaderProperty	proc :ptr
    get_HeaderTemplateProperty proc :ptr
    get_ClockIdentifierProperty proc :ptr
    get_MinuteIncrementProperty proc :ptr
    get_TimeProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePickerFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePickerFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITimePickerFactory <L"Windows.UI.Xaml.Controls.ITimePickerFactory">
DEFINE_IIDX(ITimePickerFactory, "553FE413-6CD7-46A9-A97B-A18BDC4B4CA3")

.comdef ITimePickerFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePickerValueChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CITimePickerValueChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_ITimePickerValueChangedEventArgs <L"Windows.UI.Xaml.Controls.ITimePickerValueChangedEventArgs">
DEFINE_IIDX(ITimePickerValueChangedEventArgs, "2F4EDB8D-B995-4E31-8BA9-C4DCDEB21CA3")

.comdef ITimePickerValueChangedEventArgs : public IInspectable

    get_OldTime		proc :ptr
    get_NewTime		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleMenuFlyoutItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleMenuFlyoutItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToggleMenuFlyoutItem <L"Windows.UI.Xaml.Controls.IToggleMenuFlyoutItem">
DEFINE_IIDX(IToggleMenuFlyoutItem, "49841EDD-88E9-4663-A701-CD4FD25E398F")

.comdef IToggleMenuFlyoutItem : public IInspectable

    get_IsChecked	proc :ptr
    put_IsChecked	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleMenuFlyoutItemStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleMenuFlyoutItemStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToggleMenuFlyoutItemStatics <L"Windows.UI.Xaml.Controls.IToggleMenuFlyoutItemStatics">
DEFINE_IIDX(IToggleMenuFlyoutItemStatics, "16C724FB-6C1A-4852-9258-08C038367907")

.comdef IToggleMenuFlyoutItemStatics : public IInspectable

    get_IsCheckedProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleMenuFlyoutItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIToggleMenuFlyoutItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IToggleMenuFlyoutItemFactory <L"Windows.UI.Xaml.Controls.IToggleMenuFlyoutItemFactory">
DEFINE_IIDX(IToggleMenuFlyoutItemFactory, "A151966F-3BF7-46B6-B61C-9B2C1BA68843")

.comdef IToggleMenuFlyoutItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebView <L"Windows.UI.Xaml.Controls.IWebView">
DEFINE_IIDX(IWebView, "5862CC46-1F7D-479B-92A6-DE7858FE8D54")

.comdef IWebView : public IInspectable

    get_Source		proc :ptr
    put_Source		proc :ptr
    get_AllowedScriptNotifyUris proc :ptr
    put_AllowedScriptNotifyUris proc :ptr
    get_DataTransferPackage proc :ptr
    add_LoadCompleted	proc :ptr, :ptr
    remove_LoadCompleted proc :EventRegistrationToken
    add_ScriptNotify	proc :ptr, :ptr
    remove_ScriptNotify proc :EventRegistrationToken
    add_NavigationFailed proc :ptr, :ptr
    remove_NavigationFailed proc :EventRegistrationToken
    InvokeScript	proc :HSTRING, :UINT32
    Navigate		proc :ptr
    NavigateToString	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewStatics <L"Windows.UI.Xaml.Controls.IWebViewStatics">
DEFINE_IIDX(IWebViewStatics, "A0B561DE-5FDB-443B-B9F0-5C30F6B7A1F4")

.comdef IWebViewStatics : public IInspectable

    get_AnyScriptNotifyUri proc :ptr
    get_SourceProperty	proc :ptr
    get_AllowedScriptNotifyUrisProperty proc :ptr
    get_DataTransferPackageProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebView2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebView2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebView2 <L"Windows.UI.Xaml.Controls.IWebView2">
DEFINE_IIDX(IWebView2, "D481759E-3EFF-4462-823D-FD52F9BA4CC8")

.comdef IWebView2 : public IInspectable

    get_CanGoBack	proc :ptr
    get_CanGoForward	proc :ptr
    get_DocumentTitle	proc :ptr
    add_NavigationStarting proc :ptr, :ptr
    remove_NavigationStarting proc :EventRegistrationToken
    add_ContentLoading	proc :ptr, :ptr
    remove_ContentLoading proc :EventRegistrationToken
    add_DOMContentLoaded proc :ptr, :ptr
    remove_DOMContentLoaded proc :EventRegistrationToken
    GoForward		proc
    GoBack		proc
    Refresh		proc
    Stop		proc
    CapturePreviewToStreamAsync proc :ptr, :ptr
    InvokeScriptAsync	proc :HSTRING, :ptr, :ptr
    CaptureSelectedContentToDataPackageAsync proc :ptr
    NavigateToLocalStreamUri proc :ptr, :ptr
    BuildLocalStreamUri proc :HSTRING, :HSTRING, :ptr
    get_DefaultBackgroundColor proc :ptr
    put_DefaultBackgroundColor proc :Windows::UI::Color
    add_NavigationCompleted proc :ptr, :ptr
    remove_NavigationCompleted proc :EventRegistrationToken
    add_FrameNavigationStarting proc :ptr, :ptr
    remove_FrameNavigationStarting proc :EventRegistrationToken
    add_FrameContentLoading proc :ptr, :ptr
    remove_FrameContentLoading proc :EventRegistrationToken
    add_FrameDOMContentLoaded proc :ptr, :ptr
    remove_FrameDOMContentLoaded proc :EventRegistrationToken
    add_FrameNavigationCompleted proc :ptr, :ptr
    remove_FrameNavigationCompleted proc :EventRegistrationToken
    add_LongRunningScriptDetected proc :ptr, :ptr
    remove_LongRunningScriptDetected proc :EventRegistrationToken
    add_UnsafeContentWarningDisplaying proc :ptr, :ptr
    remove_UnsafeContentWarningDisplaying proc :EventRegistrationToken
    add_UnviewableContentIdentified proc :ptr, :ptr
    remove_UnviewableContentIdentified proc :EventRegistrationToken
    NavigateWithHttpRequestMessage proc :ptr
    Focus		proc :Windows::UI::Xaml::FocusState, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewStatics2 <L"Windows.UI.Xaml.Controls.IWebViewStatics2">
DEFINE_IIDX(IWebViewStatics2, "322F8780-E812-466B-9E50-8E9FEC24018A")

.comdef IWebViewStatics2 : public IInspectable

    get_CanGoBackProperty proc :ptr
    get_CanGoForwardProperty proc :ptr
    get_DocumentTitleProperty proc :ptr
    get_DefaultBackgroundColorProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewBrush_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewBrush_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewBrush <L"Windows.UI.Xaml.Controls.IWebViewBrush">
DEFINE_IIDX(IWebViewBrush, "40E86F75-0CF4-4B72-A4D6-CF5D15780116")

.comdef IWebViewBrush : public IInspectable

    get_SourceName	proc :ptr
    put_SourceName	proc :HSTRING
    Redraw		proc
    SetSource		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewBrushStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewBrushStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewBrushStatics <L"Windows.UI.Xaml.Controls.IWebViewBrushStatics">
DEFINE_IIDX(IWebViewBrushStatics, "D74DAA24-1D05-463E-B028-6BAA4420E762")

.comdef IWebViewBrushStatics : public IInspectable

    get_SourceNameProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewContentLoadingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewContentLoadingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewContentLoadingEventArgs <L"Windows.UI.Xaml.Controls.IWebViewContentLoadingEventArgs">
DEFINE_IIDX(IWebViewContentLoadingEventArgs, "6E2980BB-98B8-413E-8129-971C6F7E4C8A")

.comdef IWebViewContentLoadingEventArgs : public IInspectable

    get_Uri		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewDOMContentLoadedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewDOMContentLoadedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewDOMContentLoadedEventArgs <L"Windows.UI.Xaml.Controls.IWebViewDOMContentLoadedEventArgs">
DEFINE_IIDX(IWebViewDOMContentLoadedEventArgs, "C47EBA15-DC6B-4B36-9D80-82FB8817B988")

.comdef IWebViewDOMContentLoadedEventArgs : public IInspectable

    get_Uri		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewLongRunningScriptDetectedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewLongRunningScriptDetectedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewLongRunningScriptDetectedEventArgs <L"Windows.UI.Xaml.Controls.IWebViewLongRunningScriptDetectedEventArgs">
DEFINE_IIDX(IWebViewLongRunningScriptDetectedEventArgs, "F3F020AB-A46C-42B0-9EFE-69764D5CFFA6")

.comdef IWebViewLongRunningScriptDetectedEventArgs : public IInspectable

    get_ExecutionTime	proc :ptr
    get_StopPageScriptExecution proc :ptr
    put_StopPageScriptExecution proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewNavigationCompletedEventArgs <L"Windows.UI.Xaml.Controls.IWebViewNavigationCompletedEventArgs">
DEFINE_IIDX(IWebViewNavigationCompletedEventArgs, "11E6F20B-EBA7-44C0-889B-EDEB6A064DDD")

.comdef IWebViewNavigationCompletedEventArgs : public IInspectable

    get_Uri		proc :ptr
    get_IsSuccess	proc :ptr
    get_WebErrorStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationFailedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationFailedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewNavigationFailedEventArgs <L"Windows.UI.Xaml.Controls.IWebViewNavigationFailedEventArgs">
DEFINE_IIDX(IWebViewNavigationFailedEventArgs, "AF09609A-129C-4170-9E9C-E2CDF025DCA4")

.comdef IWebViewNavigationFailedEventArgs : public IInspectable

    get_Uri		proc :ptr
    get_WebErrorStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationStartingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewNavigationStartingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewNavigationStartingEventArgs <L"Windows.UI.Xaml.Controls.IWebViewNavigationStartingEventArgs">
DEFINE_IIDX(IWebViewNavigationStartingEventArgs, "94CB8668-8367-43D5-91BB-96EBA37EC784")

.comdef IWebViewNavigationStartingEventArgs : public IInspectable

    get_Uri		proc :ptr
    get_Cancel		proc :ptr
    put_Cancel		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewUnviewableContentIdentifiedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWebViewUnviewableContentIdentifiedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWebViewUnviewableContentIdentifiedEventArgs <L"Windows.UI.Xaml.Controls.IWebViewUnviewableContentIdentifiedEventArgs">
DEFINE_IIDX(IWebViewUnviewableContentIdentifiedEventArgs, "37BC16E1-6062-4678-B20B-6C36AC9C59AC")

.comdef IWebViewUnviewableContentIdentifiedEventArgs : public IInspectable

    get_Uri		proc :ptr
    get_Referrer	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWrapGrid_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWrapGrid_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWrapGrid <L"Windows.UI.Xaml.Controls.IWrapGrid">
DEFINE_IIDX(IWrapGrid, "0552178B-7567-47C2-BD5C-AD8394C828BA")

.comdef IWrapGrid : public IInspectable

    get_ItemWidth	proc :ptr
    put_ItemWidth	proc :DOUBLE
    get_ItemHeight	proc :ptr
    put_ItemHeight	proc :DOUBLE
    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    get_HorizontalChildrenAlignment proc :ptr
    put_HorizontalChildrenAlignment proc :Windows::UI::Xaml::HorizontalAlignment
    get_VerticalChildrenAlignment proc :ptr
    put_VerticalChildrenAlignment proc :Windows::UI::Xaml::VerticalAlignment
    get_MaximumRowsOrColumns proc :ptr
    put_MaximumRowsOrColumns proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIWrapGridStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIWrapGridStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IWrapGridStatics <L"Windows.UI.Xaml.Controls.IWrapGridStatics">
DEFINE_IIDX(IWrapGridStatics, "D04A6B97-13CB-479C-A285-E4E56846C4CB")

.comdef IWrapGridStatics : public IInspectable

    get_ItemWidthProperty proc :ptr
    get_ItemHeightProperty proc :ptr
    get_OrientationProperty proc :ptr
    get_HorizontalChildrenAlignmentProperty proc :ptr
    get_VerticalChildrenAlignmentProperty proc :ptr
    get_MaximumRowsOrColumnsProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIControl_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IControl <L"Windows.UI.Xaml.Controls.IControl">
DEFINE_IIDX(IControl, "A8912263-2951-4F58-A9C5-5A134EAA7F07")

.comdef IControl : public IInspectable

    get_FontSize	proc :ptr
    put_FontSize	proc :DOUBLE
    get_FontFamily	proc :ptr
    put_FontFamily	proc :ptr
    get_FontWeight	proc :ptr
    put_FontWeight	proc :Windows::UI::Text::FontWeight
    get_FontStyle	proc :ptr
    put_FontStyle	proc :Windows::UI::Text::FontStyle
    get_FontStretch	proc :ptr
    put_FontStretch	proc :Windows::UI::Text::FontStretch
    get_CharacterSpacing proc :ptr
    put_CharacterSpacing proc :INT32
    get_Foreground	proc :ptr
    put_Foreground	proc :ptr
    get_IsTabStop	proc :ptr
    put_IsTabStop	proc :boolean
    get_IsEnabled	proc :ptr
    put_IsEnabled	proc :boolean
    get_TabIndex	proc :ptr
    put_TabIndex	proc :INT32
    get_TabNavigation	proc :ptr
    put_TabNavigation	proc :Windows::UI::Xaml::Input::KeyboardNavigationMode
    get_Template	proc :ptr
    put_Template	proc :ptr
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
    get_HorizontalContentAlignment proc :ptr
    put_HorizontalContentAlignment proc :Windows::UI::Xaml::HorizontalAlignment
    get_VerticalContentAlignment proc :ptr
    put_VerticalContentAlignment proc :Windows::UI::Xaml::VerticalAlignment
    get_Background	proc :ptr
    put_Background	proc :ptr
    get_BorderThickness proc :ptr
    put_BorderThickness proc :Windows::UI::Xaml::Thickness
    get_BorderBrush	proc :ptr
    put_BorderBrush	proc :ptr
    get_FocusState	proc :ptr
    add_IsEnabledChanged proc :ptr, :ptr
    remove_IsEnabledChanged proc :EventRegistrationToken
    ApplyTemplate	proc :ptr
    Focus		proc :Windows::UI::Xaml::FocusState, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IControlOverrides <L"Windows.UI.Xaml.Controls.IControlOverrides">
DEFINE_IIDX(IControlOverrides, "A09691DF-9824-41FE-B530-B0D8990E64C1")

.comdef IControlOverrides : public IInspectable

    OnPointerEntered	proc :ptr
    OnPointerPressed	proc :ptr
    OnPointerMoved	proc :ptr
    OnPointerReleased	proc :ptr
    OnPointerExited	proc :ptr
    OnPointerCaptureLost proc :ptr
    OnPointerCanceled	proc :ptr
    OnPointerWheelChanged proc :ptr
    OnTapped		proc :ptr
    OnDoubleTapped	proc :ptr
    OnHolding		proc :ptr
    OnRightTapped	proc :ptr
    OnManipulationStarting proc :ptr
    OnManipulationInertiaStarting proc :ptr
    OnManipulationStarted proc :ptr
    OnManipulationDelta proc :ptr
    OnManipulationCompleted proc :ptr
    OnKeyUp		proc :ptr
    OnKeyDown		proc :ptr
    OnGotFocus		proc :ptr
    OnLostFocus		proc :ptr
    OnDragEnter		proc :ptr
    OnDragLeave		proc :ptr
    OnDragOver		proc :ptr
    OnDrop		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlProtected_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlProtected_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IControlProtected <L"Windows.UI.Xaml.Controls.IControlProtected">
DEFINE_IIDX(IControlProtected, "1791587A-2A7C-4981-A2D8-AB99FFFC65B9")

.comdef IControlProtected : public IInspectable

    get_DefaultStyleKey proc :ptr
    put_DefaultStyleKey proc :ptr
    GetTemplateChild	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IControlStatics <L"Windows.UI.Xaml.Controls.IControlStatics">
DEFINE_IIDX(IControlStatics, "473B305B-877D-4C35-8FCA-46A05F96607A")

.comdef IControlStatics : public IInspectable

    get_FontSizeProperty proc :ptr
    get_FontFamilyProperty proc :ptr
    get_FontWeightProperty proc :ptr
    get_FontStyleProperty proc :ptr
    get_FontStretchProperty proc :ptr
    get_CharacterSpacingProperty proc :ptr
    get_ForegroundProperty proc :ptr
    get_IsTabStopProperty proc :ptr
    get_IsEnabledProperty proc :ptr
    get_TabIndexProperty proc :ptr
    get_TabNavigationProperty proc :ptr
    get_TemplateProperty proc :ptr
    get_PaddingProperty proc :ptr
    get_HorizontalContentAlignmentProperty proc :ptr
    get_VerticalContentAlignmentProperty proc :ptr
    get_BackgroundProperty proc :ptr
    get_BorderThicknessProperty proc :ptr
    get_BorderBrushProperty proc :ptr
    get_DefaultStyleKeyProperty proc :ptr
    get_FocusStateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IControlFactory <L"Windows.UI.Xaml.Controls.IControlFactory">
DEFINE_IIDX(IControlFactory, "B12B1D5A-6419-4E16-B212-A45336B75778")

.comdef IControlFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlTemplate_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CIControlTemplate_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_IControlTemplate <L"Windows.UI.Xaml.Controls.IControlTemplate">
DEFINE_IIDX(IControlTemplate, "EFD2418E-41E0-48BB-8B82-91EDA1BA3FE2")

.comdef IControlTemplate : public IInspectable

    get_TargetType	proc :ptr
    put_TargetType	proc :Windows::UI::Xaml::Interop::TypeName
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_BackClickEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_BackClickEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_BackClickEventArgs <L"Windows.UI.Xaml.Controls.BackClickEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_DragItemsStartingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_DragItemsStartingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_DragItemsStartingEventArgs <L"Windows.UI.Xaml.Controls.DragItemsStartingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_NotifyEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_NotifyEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_NotifyEventArgs <L"Windows.UI.Xaml.Controls.NotifyEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SemanticZoomViewChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SemanticZoomViewChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SemanticZoomViewChangedEventArgs <L"Windows.UI.Xaml.Controls.SemanticZoomViewChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_TextControlPasteEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_TextControlPasteEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_TextControlPasteEventArgs <L"Windows.UI.Xaml.Controls.TextControlPasteEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ColumnDefinitionCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ColumnDefinitionCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinitionCollection <L"Windows.UI.Xaml.Controls.ColumnDefinitionCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ContainerContentChangingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ContainerContentChangingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ContainerContentChangingEventArgs <L"Windows.UI.Xaml.Controls.ContainerContentChangingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_DataTemplateSelector_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_DataTemplateSelector_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_DataTemplateSelector <L"Windows.UI.Xaml.Controls.DataTemplateSelector">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_DatePickerValueChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_DatePickerValueChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_DatePickerValueChangedEventArgs <L"Windows.UI.Xaml.Controls.DatePickerValueChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_RowDefinitionCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_RowDefinitionCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_RowDefinitionCollection <L"Windows.UI.Xaml.Controls.RowDefinitionCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_StyleSelector_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_StyleSelector_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_StyleSelector <L"Windows.UI.Xaml.Controls.StyleSelector">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_GroupStyle_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_GroupStyle_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_GroupStyle <L"Windows.UI.Xaml.Controls.GroupStyle">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_GroupStyleSelector_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_GroupStyleSelector_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_GroupStyleSelector <L"Windows.UI.Xaml.Controls.GroupStyleSelector">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SemanticZoomLocation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SemanticZoomLocation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SemanticZoomLocation <L"Windows.UI.Xaml.Controls.SemanticZoomLocation">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemCollection <L"Windows.UI.Xaml.Controls.ItemCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemContainerGenerator_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemContainerGenerator_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemContainerGenerator <L"Windows.UI.Xaml.Controls.ItemContainerGenerator">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_UIElementCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_UIElementCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_UIElementCollection <L"Windows.UI.Xaml.Controls.UIElementCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewerViewChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewerViewChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ScrollViewerViewChangedEventArgs <L"Windows.UI.Xaml.Controls.ScrollViewerViewChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewerViewChangingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewerViewChangingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ScrollViewerViewChangingEventArgs <L"Windows.UI.Xaml.Controls.ScrollViewerViewChangingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewerView_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewerView_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ScrollViewerView <L"Windows.UI.Xaml.Controls.ScrollViewerView">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ToolTipService_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ToolTipService_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ToolTipService <L"Windows.UI.Xaml.Controls.ToolTipService">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_HubSectionHeaderClickEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_HubSectionHeaderClickEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_HubSectionHeaderClickEventArgs <L"Windows.UI.Xaml.Controls.HubSectionHeaderClickEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SectionsInViewChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SectionsInViewChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SectionsInViewChangedEventArgs <L"Windows.UI.Xaml.Controls.SectionsInViewChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewNavigationFailedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewNavigationFailedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewNavigationFailedEventArgs <L"Windows.UI.Xaml.Controls.WebViewNavigationFailedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_HubSectionCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_HubSectionCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_HubSectionCollection <L"Windows.UI.Xaml.Controls.HubSectionCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxQueryChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxQueryChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SearchBoxQueryChangedEventArgs <L"Windows.UI.Xaml.Controls.SearchBoxQueryChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxSuggestionsRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxSuggestionsRequestedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SearchBoxSuggestionsRequestedEventArgs <L"Windows.UI.Xaml.Controls.SearchBoxSuggestionsRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxQuerySubmittedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxQuerySubmittedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SearchBoxQuerySubmittedEventArgs <L"Windows.UI.Xaml.Controls.SearchBoxQuerySubmittedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxResultSuggestionChosenEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBoxResultSuggestionChosenEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SearchBoxResultSuggestionChosenEventArgs <L"Windows.UI.Xaml.Controls.SearchBoxResultSuggestionChosenEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_TimePickerValueChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_TimePickerValueChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_TimePickerValueChangedEventArgs <L"Windows.UI.Xaml.Controls.TimePickerValueChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewNavigationStartingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewNavigationStartingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewNavigationStartingEventArgs <L"Windows.UI.Xaml.Controls.WebViewNavigationStartingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewContentLoadingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewContentLoadingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewContentLoadingEventArgs <L"Windows.UI.Xaml.Controls.WebViewContentLoadingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewDOMContentLoadedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewDOMContentLoadedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewDOMContentLoadedEventArgs <L"Windows.UI.Xaml.Controls.WebViewDOMContentLoadedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewNavigationCompletedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewNavigationCompletedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewNavigationCompletedEventArgs <L"Windows.UI.Xaml.Controls.WebViewNavigationCompletedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewLongRunningScriptDetectedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewLongRunningScriptDetectedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewLongRunningScriptDetectedEventArgs <L"Windows.UI.Xaml.Controls.WebViewLongRunningScriptDetectedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewUnviewableContentIdentifiedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewUnviewableContentIdentifiedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewUnviewableContentIdentifiedEventArgs <L"Windows.UI.Xaml.Controls.WebViewUnviewableContentIdentifiedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ColumnDefinition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ColumnDefinition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ColumnDefinition <L"Windows.UI.Xaml.Controls.ColumnDefinition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_RowDefinition_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_RowDefinition_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_RowDefinition <L"Windows.UI.Xaml.Controls.RowDefinition">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Flyout_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Flyout_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Flyout <L"Windows.UI.Xaml.Controls.Flyout">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyout_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyout_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyout <L"Windows.UI.Xaml.Controls.MenuFlyout">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_CleanUpVirtualizedItemEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_CleanUpVirtualizedItemEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_CleanUpVirtualizedItemEventArgs <L"Windows.UI.Xaml.Controls.CleanUpVirtualizedItemEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ContextMenuEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ContextMenuEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ContextMenuEventArgs <L"Windows.UI.Xaml.Controls.ContextMenuEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemClickEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemClickEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemClickEventArgs <L"Windows.UI.Xaml.Controls.ItemClickEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SelectionChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SelectionChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SelectionChangedEventArgs <L"Windows.UI.Xaml.Controls.SelectionChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_TextChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_TextChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_TextChangedEventArgs <L"Windows.UI.Xaml.Controls.TextChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsPanelTemplate_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsPanelTemplate_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemsPanelTemplate <L"Windows.UI.Xaml.Controls.ItemsPanelTemplate">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Border_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Border_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Border <L"Windows.UI.Xaml.Controls.Border">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_CaptureElement_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_CaptureElement_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_CaptureElement <L"Windows.UI.Xaml.Controls.CaptureElement">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ContentPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ContentPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ContentPresenter <L"Windows.UI.Xaml.Controls.ContentPresenter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Image_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Image_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Image <L"Windows.UI.Xaml.Controls.Image">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Panel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Panel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Panel <L"Windows.UI.Xaml.Controls.Panel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Canvas_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Canvas_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Canvas <L"Windows.UI.Xaml.Controls.Canvas">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Grid_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Grid_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Grid <L"Windows.UI.Xaml.Controls.Grid">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemsPresenter <L"Windows.UI.Xaml.Controls.ItemsPresenter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_MediaElement_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_MediaElement_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_MediaElement <L"Windows.UI.Xaml.Controls.MediaElement">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_RichTextBlockOverflow_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_RichTextBlockOverflow_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_RichTextBlockOverflow <L"Windows.UI.Xaml.Controls.RichTextBlockOverflow">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_RichTextBlock_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_RichTextBlock_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_RichTextBlock <L"Windows.UI.Xaml.Controls.RichTextBlock">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollContentPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollContentPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ScrollContentPresenter <L"Windows.UI.Xaml.Controls.ScrollContentPresenter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_StackPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_StackPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_StackPanel <L"Windows.UI.Xaml.Controls.StackPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_TextBlock_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_TextBlock_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_TextBlock <L"Windows.UI.Xaml.Controls.TextBlock">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_VariableSizedWrapGrid_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_VariableSizedWrapGrid_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_VariableSizedWrapGrid <L"Windows.UI.Xaml.Controls.VariableSizedWrapGrid">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Viewbox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Viewbox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Viewbox <L"Windows.UI.Xaml.Controls.Viewbox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_VirtualizingPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_VirtualizingPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_VirtualizingPanel <L"Windows.UI.Xaml.Controls.VirtualizingPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_VirtualizingStackPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_VirtualizingStackPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_VirtualizingStackPanel <L"Windows.UI.Xaml.Controls.VirtualizingStackPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_IconElement_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_IconElement_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_IconElement <L"Windows.UI.Xaml.Controls.IconElement">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_BitmapIcon_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_BitmapIcon_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_BitmapIcon <L"Windows.UI.Xaml.Controls.BitmapIcon">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_FontIcon_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_FontIcon_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_FontIcon <L"Windows.UI.Xaml.Controls.FontIcon">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsStackPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsStackPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemsStackPanel <L"Windows.UI.Xaml.Controls.ItemsStackPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsWrapGrid_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsWrapGrid_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemsWrapGrid <L"Windows.UI.Xaml.Controls.ItemsWrapGrid">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_PathIcon_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_PathIcon_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_PathIcon <L"Windows.UI.Xaml.Controls.PathIcon">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SwapChainBackgroundPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SwapChainBackgroundPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SwapChainBackgroundPanel <L"Windows.UI.Xaml.Controls.SwapChainBackgroundPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SwapChainPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SwapChainPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SwapChainPanel <L"Windows.UI.Xaml.Controls.SwapChainPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SymbolIcon_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SymbolIcon_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SymbolIcon <L"Windows.UI.Xaml.Controls.SymbolIcon">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebView_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebView_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebView <L"Windows.UI.Xaml.Controls.WebView">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WrapGrid_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WrapGrid_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WrapGrid <L"Windows.UI.Xaml.Controls.WrapGrid">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewBrush_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_WebViewBrush_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_WebViewBrush <L"Windows.UI.Xaml.Controls.WebViewBrush">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Control_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Control_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Control <L"Windows.UI.Xaml.Controls.Control">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ContentControl_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ContentControl_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ContentControl <L"Windows.UI.Xaml.Controls.ContentControl">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ComboBoxItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ComboBoxItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ComboBoxItem <L"Windows.UI.Xaml.Controls.ComboBoxItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_DatePicker_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_DatePicker_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_DatePicker <L"Windows.UI.Xaml.Controls.DatePicker">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_FlipViewItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_FlipViewItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_FlipViewItem <L"Windows.UI.Xaml.Controls.FlipViewItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_GridViewItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_GridViewItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_GridViewItem <L"Windows.UI.Xaml.Controls.GridViewItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_GroupItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_GroupItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_GroupItem <L"Windows.UI.Xaml.Controls.GroupItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SemanticZoom_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SemanticZoom_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SemanticZoom <L"Windows.UI.Xaml.Controls.SemanticZoom">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsControl_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ItemsControl_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ItemsControl <L"Windows.UI.Xaml.Controls.ItemsControl">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ListBoxItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ListBoxItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ListBoxItem <L"Windows.UI.Xaml.Controls.ListBoxItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ListViewItem <L"Windows.UI.Xaml.Controls.ListViewItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_PasswordBox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_PasswordBox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_PasswordBox <L"Windows.UI.Xaml.Controls.PasswordBox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ProgressRing_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ProgressRing_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ProgressRing <L"Windows.UI.Xaml.Controls.ProgressRing">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_RichEditBox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_RichEditBox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_RichEditBox <L"Windows.UI.Xaml.Controls.RichEditBox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ScrollViewer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ScrollViewer <L"Windows.UI.Xaml.Controls.ScrollViewer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SettingsFlyout_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SettingsFlyout_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SettingsFlyout <L"Windows.UI.Xaml.Controls.SettingsFlyout">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_TextBox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_TextBox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_TextBox <L"Windows.UI.Xaml.Controls.TextBox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ToggleSwitch_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ToggleSwitch_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ToggleSwitch <L"Windows.UI.Xaml.Controls.ToggleSwitch">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ToolTip_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ToolTip_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ToolTip <L"Windows.UI.Xaml.Controls.ToolTip">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_UserControl_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_UserControl_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_UserControl <L"Windows.UI.Xaml.Controls.UserControl">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Button_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Button_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Button <L"Windows.UI.Xaml.Controls.Button">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_HyperlinkButton_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_HyperlinkButton_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_HyperlinkButton <L"Windows.UI.Xaml.Controls.HyperlinkButton">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ProgressBar_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ProgressBar_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ProgressBar <L"Windows.UI.Xaml.Controls.ProgressBar">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Slider_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Slider_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Slider <L"Windows.UI.Xaml.Controls.Slider">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ComboBox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ComboBox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ComboBox <L"Windows.UI.Xaml.Controls.ComboBox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ListViewBase <L"Windows.UI.Xaml.Controls.ListViewBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_FlipView_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_FlipView_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_FlipView <L"Windows.UI.Xaml.Controls.FlipView">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_GridView_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_GridView_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_GridView <L"Windows.UI.Xaml.Controls.GridView">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ListBox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ListBox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ListBox <L"Windows.UI.Xaml.Controls.ListBox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ListView_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ListView_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ListView <L"Windows.UI.Xaml.Controls.ListView">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_CheckBox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_CheckBox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_CheckBox <L"Windows.UI.Xaml.Controls.CheckBox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_RadioButton_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_RadioButton_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_RadioButton <L"Windows.UI.Xaml.Controls.RadioButton">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBar_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBar_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_AppBar <L"Windows.UI.Xaml.Controls.AppBar">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBarButton_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBarButton_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_AppBarButton <L"Windows.UI.Xaml.Controls.AppBarButton">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBarSeparator_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBarSeparator_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_AppBarSeparator <L"Windows.UI.Xaml.Controls.AppBarSeparator">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBarToggleButton_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_AppBarToggleButton_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_AppBarToggleButton <L"Windows.UI.Xaml.Controls.AppBarToggleButton">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_CommandBar_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_CommandBar_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_CommandBar <L"Windows.UI.Xaml.Controls.CommandBar">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_FlyoutPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_FlyoutPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_FlyoutPresenter <L"Windows.UI.Xaml.Controls.FlyoutPresenter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Frame_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Frame_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Frame <L"Windows.UI.Xaml.Controls.Frame">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_HubSection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_HubSection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_HubSection <L"Windows.UI.Xaml.Controls.HubSection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Hub_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Hub_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Hub <L"Windows.UI.Xaml.Controls.Hub">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewBaseHeaderItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewBaseHeaderItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ListViewBaseHeaderItem <L"Windows.UI.Xaml.Controls.ListViewBaseHeaderItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_GridViewHeaderItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_GridViewHeaderItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_GridViewHeaderItem <L"Windows.UI.Xaml.Controls.GridViewHeaderItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewHeaderItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ListViewHeaderItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ListViewHeaderItem <L"Windows.UI.Xaml.Controls.ListViewHeaderItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutItemBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutItemBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyoutItemBase <L"Windows.UI.Xaml.Controls.MenuFlyoutItemBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyoutItem <L"Windows.UI.Xaml.Controls.MenuFlyoutItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyoutPresenter <L"Windows.UI.Xaml.Controls.MenuFlyoutPresenter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutSeparator_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_MenuFlyoutSeparator_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_MenuFlyoutSeparator <L"Windows.UI.Xaml.Controls.MenuFlyoutSeparator">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Page_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Page_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Page <L"Windows.UI.Xaml.Controls.Page">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBox_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_SearchBox_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_SearchBox <L"Windows.UI.Xaml.Controls.SearchBox">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_TimePicker_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_TimePicker_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_TimePicker <L"Windows.UI.Xaml.Controls.TimePicker">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ToggleMenuFlyoutItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ToggleMenuFlyoutItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ToggleMenuFlyoutItem <L"Windows.UI.Xaml.Controls.ToggleMenuFlyoutItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_ControlTemplate_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_ControlTemplate_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_ControlTemplate <L"Windows.UI.Xaml.Controls.ControlTemplate">
endif

endif
