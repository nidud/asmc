ifndef _RPC500_
include rpc500.inc
endif
ifndef __inked_h__
define __inked_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include msinkaut.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

define INKEDIT_CLASSW  <L"INKEDIT">
ifdef _UNICODE
define INKEDIT_CLASS   <INKEDIT_CLASSW>
else
define INKEDIT_CLASS   <"INKEDIT">
endif

IEC_STROKEINFO		struct
nmhdr			NMHDR <>
Cursor			ptr IInkCursor ?
Stroke			ptr IInkStrokeDisp ?
IEC_STROKEINFO		ends

IEC_GESTUREINFO		struct
nmhdr			NMHDR <>
Cursor			ptr IInkCursor ?
Strokes			ptr IInkStrokes ?
Gestures		VARIANT <>
IEC_GESTUREINFO		ends

IEC_RECOGNITIONRESULTINFO struct
nmhdr			NMHDR <>
RecognitionResult	ptr IInkRecognitionResult ?
IEC_RECOGNITIONRESULTINFO ends

define IEC__BASE	   (WM_USER + 0x0200)
define EM_GETINKMODE	   (IEC__BASE + 1)
define EM_SETINKMODE	   (IEC__BASE + 2)
define EM_GETINKINSERTMODE (IEC__BASE + 3)
define EM_SETINKINSERTMODE (IEC__BASE + 4)
define EM_GETDRAWATTR	   (IEC__BASE + 5)
define EM_SETDRAWATTR	   (IEC__BASE + 6)
define EM_GETRECOTIMEOUT   (IEC__BASE + 7)
define EM_SETRECOTIMEOUT   (IEC__BASE + 8)
define EM_GETGESTURESTATUS (IEC__BASE + 9)
define EM_SETGESTURESTATUS (IEC__BASE + 10)
define EM_GETRECOGNIZER	   (IEC__BASE + 11)
define EM_SETRECOGNIZER	   (IEC__BASE + 12)
define EM_GETFACTOID	   (IEC__BASE + 13)
define EM_SETFACTOID	   (IEC__BASE + 14)
define EM_GETSELINK	   (IEC__BASE + 15)
define EM_SETSELINK	   (IEC__BASE + 16)
define EM_GETMOUSEICON	   (IEC__BASE + 17)
define EM_SETMOUSEICON	   (IEC__BASE + 18)
define EM_GETMOUSEPOINTER  (IEC__BASE + 19)
define EM_SETMOUSEPOINTER  (IEC__BASE + 20)
define EM_GETSTATUS	   (IEC__BASE + 21)
define EM_RECOGNIZE	   (IEC__BASE + 22)
define EM_GETUSEMOUSEFORINPUT	(IEC__BASE + 23)
define EM_SETUSEMOUSEFORINPUT	(IEC__BASE + 24)
define EM_SETSELINKDISPLAYMODE	(IEC__BASE + 25)
define EM_GETSELINKDISPLAYMODE	(IEC__BASE + 26)

define IECN__BASE	      (0x0800)
define IECN_STROKE	      (IECN__BASE + 1)
define IECN_GESTURE	      (IECN__BASE + 2)
define IECN_RECOGNITIONRESULT (IECN__BASE + 3)

ifndef __INKEDLib_LIBRARY_DEFINED__
define __INKEDLib_LIBRARY_DEFINED__

.enum MouseButton {
	NO_BUTTON	= 0,
	LEFT_BUTTON	= 0x1,
	RIGHT_BUTTON	= 0x2,
	MIDDLE_BUTTON	= 0x4
	}

.enum SelAlignmentConstants {
	rtfLeft,
	rtfRight,
	rtfCenter
	}

.enum DISPID_InkEdit {
	DISPID_Text		= DISPID_VALUE,
	DISPID_TextRTF,
	DISPID_Hwnd,
	DISPID_DisableNoScroll,
	DISPID_Locked,
	DISPID_Enabled,
	DISPID_MaxLength,
	DISPID_MultiLine,
	DISPID_ScrollBars,
	DISPID_RTSelStart,
	DISPID_RTSelLength,
	DISPID_RTSelText,
	DISPID_SelAlignment,
	DISPID_SelBold,
	DISPID_SelCharOffset,
	DISPID_SelColor,
	DISPID_SelFontName,
	DISPID_SelFontSize,
	DISPID_SelItalic,
	DISPID_SelRTF,
	DISPID_SelUnderline,
	DISPID_DragIcon,
	DISPID_Status,
	DISPID_UseMouseForInput,
	DISPID_InkMode,
	DISPID_InkInsertMode,
	DISPID_RecoTimeout,
	DISPID_DrawAttr,
	DISPID_Recognizer,
	DISPID_Factoid,
	DISPID_SelInk,
	DISPID_SelInksDisplayMode,
	DISPID_Recognize,
	DISPID_GetGestStatus,
	DISPID_SetGestStatus,
	DISPID_Refresh
	}

.enum DISPID_InkEditEvents {
	DISPID_IeeChange	= 1,
	DISPID_IeeSelChange	= 2,
	DISPID_IeeKeyDown	= 3,
	DISPID_IeeKeyUp		= 4,
	DISPID_IeeMouseUp	= 5,
	DISPID_IeeMouseDown	= 6,
	DISPID_IeeKeyPress	= 7,
	DISPID_IeeDblClick	= 8,
	DISPID_IeeClick		= 9,
	DISPID_IeeMouseMove	= 10,
	DISPID_IeeCursorDown	= 21,
	DISPID_IeeStroke	= 22,
	DISPID_IeeGesture	= 23,
	DISPID_IeeRecognitionResult	= 24
	}

externdef LIBID_INKEDLib:IID

ifndef __IInkEdit_INTERFACE_DEFINED__
define __IInkEdit_INTERFACE_DEFINED__

.enum InkMode {
	IEM_Disabled		= 0,
	IEM_Ink			= 1,
	IEM_InkAndGesture	= 2
	}

.enum InkInsertMode {
	IEM_InsertText,
	IEM_InsertInk
	}

.enum InkEditStatus {
	IES_Idle,
	IES_Collecting,
	IES_Recognizing
	}

.enum InkDisplayMode {
	IDM_Ink,
	IDM_Text
	}

.enum AppearanceConstants {
	rtfFlat,
	rtfThreeD
	}

.enum BorderStyleConstants {
	rtfNoBorder,
	rtfFixedSingle
	}

.enum ScrollBarsConstants {
	rtfNone,
	rtfHorizontal,
	rtfVertical,
	rtfBoth
	}

DEFINE_IIDX(IInkEdit, "F2127A19-FBFB-4AED-8464-3F36D78CFEFB")

.comdef IInkEdit : public IDispatch
    get_Status		proc :ptr
    get_UseMouseForInput proc :ptr
    put_UseMouseForInput proc :VARIANT_BOOL
    get_InkMode		proc :ptr
    put_InkMode		proc :InkMode
    get_InkInsertMode	proc :ptr
    put_InkInsertMode	proc :InkInsertMode
    get_DrawingAttributes proc :ptr ptr
    putref_DrawingAttributes proc :ptr
    get_RecognitionTimeout proc :ptr
    put_RecognitionTimeout proc :LONG
    get_Recognizer	proc :ptr ptr
    putref_Recognizer	proc :ptr
    get_Factoid		proc :ptr
    put_Factoid		proc :BSTR
    get_SelInks		proc :ptr
    put_SelInks		proc :VARIANT
    get_SelInksDisplayMode proc :ptr
    put_SelInksDisplayMode proc :InkDisplayMode
    Recognize		proc
    GetGestureStatus	proc :InkApplicationGesture, :ptr
    SetGestureStatus	proc :InkApplicationGesture, :VARIANT_BOOL
    put_BackColor	proc :OLE_COLOR
    get_BackColor	proc :ptr
    get_Appearance	proc :ptr
    put_Appearance	proc :AppearanceConstants
    get_BorderStyle	proc :ptr
    put_BorderStyle	proc :BorderStyleConstants
    get_Hwnd		proc :ptr
    get_Font		proc :ptr ptr
    putref_Font		proc :ptr
    get_Text		proc :ptr
    put_Text		proc :BSTR
    get_MouseIcon	proc :ptr ptr
    put_MouseIcon	proc :ptr
    putref_MouseIcon	proc :ptr
    get_MousePointer	proc :ptr
    put_MousePointer	proc :InkMousePointer
    get_Locked		proc :ptr
    put_Locked		proc :VARIANT_BOOL
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
    get_MaxLength	proc :ptr
    put_MaxLength	proc :LONG
    get_MultiLine	proc :ptr
    put_MultiLine	proc :VARIANT_BOOL
    get_ScrollBars	proc :ptr
    put_ScrollBars	proc :ScrollBarsConstants
    get_DisableNoScroll proc :ptr
    put_DisableNoScroll proc :VARIANT_BOOL
    get_SelAlignment	proc :ptr
    put_SelAlignment	proc :VARIANT
    get_SelBold		proc :ptr
    put_SelBold		proc :VARIANT
    get_SelItalic	proc :ptr
    put_SelItalic	proc :VARIANT
    get_SelUnderline	proc :ptr
    put_SelUnderline	proc :VARIANT
    get_SelColor	proc :ptr
    put_SelColor	proc :VARIANT
    get_SelFontName	proc :ptr
    put_SelFontName	proc :VARIANT
    get_SelFontSize	proc :ptr
    put_SelFontSize	proc :VARIANT
    get_SelCharOffset	proc :ptr
    put_SelCharOffset	proc :VARIANT
    get_TextRTF		proc :ptr
    put_TextRTF		proc :BSTR
    get_SelStart	proc :ptr
    put_SelStart	proc :LONG
    get_SelLength	proc :ptr
    put_SelLength	proc :LONG
    get_SelText		proc :ptr
    put_SelText		proc :BSTR
    get_SelRTF		proc :ptr
    put_SelRTF		proc :BSTR
    Refresh		proc
   .ends

endif

ifndef ___IInkEditEvents_DISPINTERFACE_DEFINED__
define ___IInkEditEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IInkEditEvents, "E3B0B797-A72E-46DB-A0D7-6C9EBA8E9BBC")

.comdef _IInkEditEvents : public IDispatch
   .ends

endif

DEFINE_GUIDS(CLSID_InkEdit, "E5CA59F5-57C4-4DD8-9BD6-1DEEEDD27AF4")

endif

endif

endif
