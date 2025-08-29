ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __micaut_h__
define __micaut_h__

include oaidl.inc
include ocidl.inc
include msinkaut.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum MICUIELEMENT {
	MICUIELEMENT_BUTTON_WRITE		= ( 1 shl 0 ),
	MICUIELEMENT_BUTTON_ERASE		= ( 1 shl 1 ),
	MICUIELEMENT_BUTTON_CORRECT		= ( 1 shl 2 ),
	MICUIELEMENT_BUTTON_CLEAR		= ( 1 shl 3 ),
	MICUIELEMENT_BUTTON_UNDO		= ( 1 shl 4 ),
	MICUIELEMENT_BUTTON_REDO		= ( 1 shl 5 ),
	MICUIELEMENT_BUTTON_INSERT		= ( 1 shl 6 ),
	MICUIELEMENT_BUTTON_CANCEL		= ( 1 shl 7 ),
	MICUIELEMENT_INKPANEL_BACKGROUND	= ( 1 shl 8 ),
	MICUIELEMENT_RESULTPANEL_BACKGROUND	= ( 1 shl 9 )
	}

.enum MICUIELEMENTSTATE {
	MICUIELEMENTSTATE_NORMAL = 1,
	MICUIELEMENTSTATE_HOT,
	MICUIELEMENTSTATE_PRESSED,
	MICUIELEMENTSTATE_DISABLED
	}

.enum DISPID_MathInputControlEvents {
	DISPID_MICInsert,
	DISPID_MICClose,
	DISPID_MICPaint,
	DISPID_MICClear
	}

ifndef __IMathInputControl_INTERFACE_DEFINED__
define __IMathInputControl_INTERFACE_DEFINED__

DEFINE_IIDX(IMathInputControl, "EBA615AA-FAC6-4738-BA5F-FF09E9FE473E")

.comdef IMathInputControl : public IDispatch
    Show		proc
    Hide		proc
    IsVisible		proc :ptr
    GetPosition		proc :ptr, :ptr, :ptr, :ptr
    SetPosition		proc :LONG, :LONG, :LONG, :LONG
    Clear		proc
    SetCustomPaint	proc :LONG, :VARIANT_BOOL
    SetCaptionText	proc :BSTR
    LoadInk		proc :ptr
    SetOwnerWindow	proc :LONG_PTR
    EnableExtendedButtons proc :VARIANT_BOOL
    GetPreviewHeight	proc :ptr
    SetPreviewHeight	proc :LONG
    EnableAutoGrow	proc :VARIANT_BOOL
    AddFunctionName	proc :BSTR
    RemoveFunctionName	proc :BSTR
    GetHoverIcon	proc :ptr ptr
   .ends

endif

ifndef __micautLib_LIBRARY_DEFINED__
define __micautLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_micautLib, 0x928CEF0C,0x5A84,0x48AC,0xBF,0x37,0xC5,0xC2,0x10,0x39,0xB8,0x3A)

ifndef ___IMathInputControlEvents_DISPINTERFACE_DEFINED__
define ___IMathInputControlEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IMathInputControlEvents, "683336B5-A47D-4358-96F9-875A472AE70A")

.comdef _IMathInputControlEvents : public IDispatch
   .ends

endif

DEFINE_GUIDS(CLSID_MathInputControl, "C561816C-14D8-4090-830C-98D994B21C7B")

endif

endif

endif

