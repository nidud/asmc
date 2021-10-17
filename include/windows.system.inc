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

ifndef __windows2Esystem_h__
define __windows2Esystem_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include Windows.UI.Popups.inc
include Windows.UI.ViewManagement.inc
include windows.foundation.collections.inc


.namespace ABI
.namespace Windows
.namespace System

.enum ProcessorArchitecture {
    ProcessorArchitecture_X86	= 0,
    ProcessorArchitecture_Arm	= 5,
    ProcessorArchitecture_X64	= 9,
    ProcessorArchitecture_Neutral = 11,
    ProcessorArchitecture_Unknown = 65535
    }

.enum VirtualKeyModifiers {
    VirtualKeyModifiers_None	= 0,
    VirtualKeyModifiers_Control = 0x1,
    VirtualKeyModifiers_Menu	= 0x2,
    VirtualKeyModifiers_Shift	= 0x4,
    VirtualKeyModifiers_Windows = 0x8
    }

.enum VirtualKey {
    VirtualKey_None	= 0,
    VirtualKey_LeftButton = 1,
    VirtualKey_RightButton = 2,
    VirtualKey_Cancel	= 3,
    VirtualKey_MiddleButton = 4,
    VirtualKey_XButton1 = 5,
    VirtualKey_XButton2 = 6,
    VirtualKey_Back	= 8,
    VirtualKey_Tab	= 9,
    VirtualKey_Clear	= 12,
    VirtualKey_Enter	= 13,
    VirtualKey_Shift	= 16,
    VirtualKey_Control	= 17,
    VirtualKey_Menu	= 18,
    VirtualKey_Pause	= 19,
    VirtualKey_CapitalLock = 20,
    VirtualKey_Kana	= 21,
    VirtualKey_Hangul	= 21,
    VirtualKey_Junja	= 23,
    VirtualKey_Final	= 24,
    VirtualKey_Hanja	= 25,
    VirtualKey_Kanji	= 25,
    VirtualKey_Escape	= 27,
    VirtualKey_Convert	= 28,
    VirtualKey_NonConvert = 29,
    VirtualKey_Accept	= 30,
    VirtualKey_ModeChange = 31,
    VirtualKey_Space	= 32,
    VirtualKey_PageUp	= 33,
    VirtualKey_PageDown = 34,
    VirtualKey_End	= 35,
    VirtualKey_Home	= 36,
    VirtualKey_Left	= 37,
    VirtualKey_Up	= 38,
    VirtualKey_Right	= 39,
    VirtualKey_Down	= 40,
    VirtualKey_Select	= 41,
    VirtualKey_Print	= 42,
    VirtualKey_Execute	= 43,
    VirtualKey_Snapshot = 44,
    VirtualKey_Insert	= 45,
    VirtualKey_Delete	= 46,
    VirtualKey_Help	= 47,
    VirtualKey_Number0	= 48,
    VirtualKey_Number1	= 49,
    VirtualKey_Number2	= 50,
    VirtualKey_Number3	= 51,
    VirtualKey_Number4	= 52,
    VirtualKey_Number5	= 53,
    VirtualKey_Number6	= 54,
    VirtualKey_Number7	= 55,
    VirtualKey_Number8	= 56,
    VirtualKey_Number9	= 57,
    VirtualKey_A	= 65,
    VirtualKey_B	= 66,
    VirtualKey_C	= 67,
    VirtualKey_D	= 68,
    VirtualKey_E	= 69,
    VirtualKey_F	= 70,
    VirtualKey_G	= 71,
    VirtualKey_H	= 72,
    VirtualKey_I	= 73,
    VirtualKey_J	= 74,
    VirtualKey_K	= 75,
    VirtualKey_L	= 76,
    VirtualKey_M	= 77,
    VirtualKey_N	= 78,
    VirtualKey_O	= 79,
    VirtualKey_P	= 80,
    VirtualKey_Q	= 81,
    VirtualKey_R	= 82,
    VirtualKey_S	= 83,
    VirtualKey_T	= 84,
    VirtualKey_U	= 85,
    VirtualKey_V	= 86,
    VirtualKey_W	= 87,
    VirtualKey_X	= 88,
    VirtualKey_Y	= 89,
    VirtualKey_Z	= 90,
    VirtualKey_LeftWindows	= 91,
    VirtualKey_RightWindows	= 92,
    VirtualKey_Application	= 93,
    VirtualKey_Sleep	= 95,
    VirtualKey_NumberPad0	= 96,
    VirtualKey_NumberPad1	= 97,
    VirtualKey_NumberPad2	= 98,
    VirtualKey_NumberPad3	= 99,
    VirtualKey_NumberPad4	= 100,
    VirtualKey_NumberPad5	= 101,
    VirtualKey_NumberPad6	= 102,
    VirtualKey_NumberPad7	= 103,
    VirtualKey_NumberPad8	= 104,
    VirtualKey_NumberPad9	= 105,
    VirtualKey_Multiply = 106,
    VirtualKey_Add	= 107,
    VirtualKey_Separator	= 108,
    VirtualKey_Subtract = 109,
    VirtualKey_Decimal	= 110,
    VirtualKey_Divide	= 111,
    VirtualKey_F1	= 112,
    VirtualKey_F2	= 113,
    VirtualKey_F3	= 114,
    VirtualKey_F4	= 115,
    VirtualKey_F5	= 116,
    VirtualKey_F6	= 117,
    VirtualKey_F7	= 118,
    VirtualKey_F8	= 119,
    VirtualKey_F9	= 120,
    VirtualKey_F10	= 121,
    VirtualKey_F11	= 122,
    VirtualKey_F12	= 123,
    VirtualKey_F13	= 124,
    VirtualKey_F14	= 125,
    VirtualKey_F15	= 126,
    VirtualKey_F16	= 127,
    VirtualKey_F17	= 128,
    VirtualKey_F18	= 129,
    VirtualKey_F19	= 130,
    VirtualKey_F20	= 131,
    VirtualKey_F21	= 132,
    VirtualKey_F22	= 133,
    VirtualKey_F23	= 134,
    VirtualKey_F24	= 135,
    VirtualKey_NumberKeyLock = 144,
    VirtualKey_Scroll	= 145,
    VirtualKey_LeftShift = 160,
    VirtualKey_RightShift = 161,
    VirtualKey_LeftControl = 162,
    VirtualKey_RightControl = 163,
    VirtualKey_LeftMenu = 164,
    VirtualKey_RightMenu = 165,
    VirtualKey_GoBack	= 166,
    VirtualKey_GoForward = 167,
    VirtualKey_Refresh	= 168,
    VirtualKey_Stop	= 169,
    VirtualKey_Search	= 170,
    VirtualKey_Favorites = 171,
    VirtualKey_GoHome	= 172
    }

ifndef ____x_ABI_CWindows_CSystem_CILauncherUIOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CILauncherUIOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_System_ILauncherUIOptions <L"Windows.System.ILauncherUIOptions">

DEFINE_IIDX(ILauncherUIOptions, "1B25DA6E-8AA6-41E9-8251-4165F5985F49")

.comdef ILauncherUIOptions : public IInspectable

    get_InvocationPoint proc :ptr
    put_InvocationPoint proc :ptr
    get_SelectionRect	proc :ptr
    put_SelectionRect	proc :ptr
    get_PreferredPlacement proc :ptr
    put_PreferredPlacement proc :LONG
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CILauncherOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CILauncherOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_System_ILauncherOptions <L"Windows.System.ILauncherOptions">

DEFINE_IIDX(ILauncherOptions, "BAFA21D8-B071-4CD8-853E-341203E557D3")

.comdef ILauncherOptions : public IInspectable

    get_TreatAsUntrusted proc :ptr
    put_TreatAsUntrusted proc :boolean
    get_DisplayApplicationPicker proc :ptr
    put_DisplayApplicationPicker proc :boolean
    get_UI		proc :ptr
    get_PreferredApplicationPackageFamilyName proc :ptr
    put_PreferredApplicationPackageFamilyName proc :HSTRING
    get_PreferredApplicationDisplayName proc :ptr
    put_PreferredApplicationDisplayName proc :HSTRING
    get_FallbackUri	proc :ptr
    put_FallbackUri	proc :ptr
    get_ContentType	proc :ptr
    put_ContentType	proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CILauncherViewOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CILauncherViewOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_System_ILauncherViewOptions <L"Windows.System.ILauncherViewOptions">

DEFINE_IIDX(ILauncherViewOptions, "8A9B29F1-7CA7-49DE-9BD3-3C5B7184F616")

.comdef ILauncherViewOptions : public IInspectable

    get_DesiredRemainingView proc :ptr
    put_DesiredRemainingView proc :LONG
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CILauncherStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CILauncherStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_ILauncherStatics <L"Windows.System.ILauncherStatics">

DEFINE_IIDX(ILauncherStatics, "277151C3-9E3E-42F6-91A4-5DFDEB232451")

.comdef ILauncherStatics : public IInspectable

    LaunchFileAsync	proc :ptr, :ptr
    LaunchFileWithOptionsAsync proc :ptr, :ptr, :ptr
    LaunchUriAsync	proc :ptr, :ptr
    LaunchUriWithOptionsAsync proc :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_System_LauncherUIOptions_DEFINED
define RUNTIMECLASS_Windows_System_LauncherUIOptions_DEFINED
define RuntimeClass_Windows_System_LauncherUIOptions <L"Windows.System.LauncherUIOptions">
endif
ifndef RUNTIMECLASS_Windows_System_LauncherOptions_DEFINED
define RUNTIMECLASS_Windows_System_LauncherOptions_DEFINED
define RuntimeClass_Windows_System_LauncherOptions <L"Windows.System.LauncherOptions">
endif
ifndef RUNTIMECLASS_Windows_System_Launcher_DEFINED
define RUNTIMECLASS_Windows_System_Launcher_DEFINED
define RuntimeClass_Windows_System_Launcher <L"Windows.System.Launcher">
endif

HSTRING_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr DWORD, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr DWORD, :ptr HSTRING

endif
