ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 440
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

ifndef __atliface_h__
define __atliface_h__

include oaidl.inc
include ocidl.inc
include oleacc.inc

MIDL_user_allocate proto WINAPI :size_t
MIDL_user_free proto WINAPI :ptr

externdef CLSID_Registrar:CLSID


ifndef __IRegistrarBase_INTERFACE_DEFINED__
define __IRegistrarBase_INTERFACE_DEFINED__

DEFINE_IIDX(IRegistrarBase, "e21f8a85-b05d-4243-8183-c7cb405588f7")

.comdef IRegistrarBase : public IUnknown

    AddReplacement	proc :LPCOLESTR, :LPCOLESTR
    ClearReplacements	proc
   .ENDS

endif

ifndef __IRegistrar_INTERFACE_DEFINED__
define __IRegistrar_INTERFACE_DEFINED__

DEFINE_IIDX(IRegistrar, "44EC053B-400F-11D0-9DCD-00A0C90391D3")

.comdef IRegistrar : public IRegistrarBase

    ResourceRegisterSz	proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR
    ResourceUnregisterSz proc :LPCOLESTR, :LPCOLESTR, :LPCOLESTR
    FileRegister	proc :LPCOLESTR
    FileUnregister	proc :LPCOLESTR
    StringRegister	proc :LPCOLESTR
    StringUnregister	proc :LPCOLESTR
    ResourceRegister	proc :LPCOLESTR, :UINT, :LPCOLESTR
    ResourceUnregister	proc :LPCOLESTR, :UINT, :LPCOLESTR
   .ENDS

endif


ifndef __IDocHostUIHandlerDispatch_INTERFACE_DEFINED__
define __IDocHostUIHandlerDispatch_INTERFACE_DEFINED__


.enum DOCHOSTUIDBLCLKDispatch {
	docHostUIDblClkDEFAULT	= 0,
	docHostUIDblClkSHOWPROPERTIES = 1,
	docHostUIDblClkSHOWCODE = 2
	}

.enum DocHostUIFlagDispatch {
	docHostUIFlagDIALOG	= 1,
	docHostUIFlagDISABLE_HELP_MENU = 2,
	docHostUIFlagNO3DBORDER = 4,
	docHostUIFlagSCROLL_NO	= 8,
	docHostUIFlagDISABLE_SCRIPT_INACTIVE = 16,
	docHostUIFlagOPENNEWWIN = 32,
	docHostUIFlagDISABLE_OFFSCREEN = 64,
	docHostUIFlagFLAT_SCROLLBAR = 128,
	docHostUIFlagDIV_BLOCKDEFAULT = 256,
	docHostUIFlagACTIVATE_CLIENTHIT_ONLY = 512
	}


DEFINE_IIDX(IDocHostUIHandlerDispatch, "425B5AF0-65F1-11d1-9611-0000F81E0D0D")

.comdef IDocHostUIHandlerDispatch : public IDispatch

    ShowContextMenu	proc :DWORD, :DWORD, :DWORD, :ptr IUnknown, :ptr IDispatch, :ptr HRESULT
    GetHostInfo		proc :ptr DWORD, :ptr DWORD
    ShowUI		proc :DWORD, :ptr IUnknown, :ptr IUnknown, :ptr IUnknown, :ptr IUnknown, :ptr HRESULT
    HideUI		proc
    UpdateUI		proc
    EnableModeless	proc :VARIANT_BOOL
    OnDocWindowActivate proc :VARIANT_BOOL
    OnFrameWindowActivate proc :VARIANT_BOOL
    ResizeBorder	proc :LONG, :LONG, :LONG, :LONG, :ptr IUnknown, :VARIANT_BOOL
    TranslateAccelerator proc :DWORD_PTR, :DWORD, :DWORD_PTR, :DWORD_PTR, :BSTR, :DWORD, :ptr HRESULT
    GetOptionKeyPath	proc :ptr BSTR, :DWORD
    GetDropTarget	proc :ptr IUnknown, :ptr ptr IUnknown
    GetExternal		proc :ptr ptr IDispatch
    TranslateUrl	proc :DWORD, :BSTR, :ptr BSTR
    FilterDataObject	proc :ptr IUnknown, :ptr ptr IUnknown
   .ENDS

endif


ifndef __IAxWinHostWindow_INTERFACE_DEFINED__
define __IAxWinHostWindow_INTERFACE_DEFINED__

DEFINE_IIDX(IAxWinHostWindow, "B6EA2050-048A-11d1-82B9-00C04FB9942E")

.comdef IAxWinHostWindow : public IUnknown

    CreateControl	proc :LPCOLESTR, :HWND, :ptr IStream
    CreateControlEx	proc :LPCOLESTR, :HWND, :ptr IStream, :ptr ptr IUnknown, :REFIID, :ptr IUnknown
    AttachControl	proc :ptr IUnknown, :HWND
    QueryControl	proc :REFIID, :ptr ptr
    SetExternalDispatch proc :ptr IDispatch
    SetExternalUIHandler proc :ptr IDocHostUIHandlerDispatch
   .ENDS

endif


ifndef __IAxWinHostWindowLic_INTERFACE_DEFINED__
define __IAxWinHostWindowLic_INTERFACE_DEFINED__

DEFINE_IIDX(IAxWinHostWindowLic, "3935BDA8-4ED9-495c-8650-E01FC1E38A4B")

.comdef IAxWinHostWindowLic : public IAxWinHostWindow

    CreateControlLic	proc :LPCOLESTR, :HWND, :ptr IStream, :BSTR
    CreateControlLicEx	proc :LPCOLESTR, :HWND, :ptr IStream, :ptr ptr IUnknown, :REFIID, :ptr IUnknown, :BSTR
   .ENDS

endif


ifndef __IAxWinAmbientDispatch_INTERFACE_DEFINED__
define __IAxWinAmbientDispatch_INTERFACE_DEFINED__

DEFINE_IIDX(IAxWinAmbientDispatch, "B6EA2051-048A-11d1-82B9-00C04FB9942E")

.comdef IAxWinAmbientDispatch : public IDispatch

    put_AllowWindowlessActivation proc :VARIANT_BOOL
    get_AllowWindowlessActivation proc :ptr VARIANT_BOOL
    put_BackColor	proc :OLE_COLOR
    get_BackColor	proc :ptr OLE_COLOR
    put_ForeColor	proc :OLE_COLOR
    get_ForeColor	proc :ptr OLE_COLOR
    put_LocaleID	proc :LCID
    get_LocaleID	proc :ptr LCID
    put_UserMode	proc :VARIANT_BOOL
    get_UserMode	proc :ptr VARIANT_BOOL
    put_DisplayAsDefault proc :VARIANT_BOOL
    get_DisplayAsDefault proc :ptr VARIANT_BOOL
    put_Font		proc :ptr IFontDisp
    get_Font		proc :ptr ptr IFontDisp
    put_MessageReflect	proc :VARIANT_BOOL
    get_MessageReflect	proc :ptr VARIANT_BOOL
    get_ShowGrabHandles proc :ptr VARIANT_BOOL
    get_ShowHatching	proc :ptr VARIANT_BOOL
    put_DocHostFlags	proc :DWORD
    get_DocHostFlags	proc :ptr DWORD
    put_DocHostDoubleClickFlags proc :DWORD
    get_DocHostDoubleClickFlags proc :ptr DWORD
    put_AllowContextMenu proc :VARIANT_BOOL
    get_AllowContextMenu proc :ptr VARIANT_BOOL
    put_AllowShowUI	proc :VARIANT_BOOL
    get_AllowShowUI	proc :ptr VARIANT_BOOL
    put_OptionKeyPath	proc :BSTR
    get_OptionKeyPath	proc :ptr BSTR
   .ENDS

endif

ifndef __IAxWinAmbientDispatchEx_INTERFACE_DEFINED__
define __IAxWinAmbientDispatchEx_INTERFACE_DEFINED__

DEFINE_IIDX(IAxWinAmbientDispatchEx, "B2D0778B-AC99-4c58-A5C8-E7724E5316B5")

.comdef IAxWinAmbientDispatchEx : public IAxWinAmbientDispatch

    SetAmbientDispatch	proc :ptr IDispatch
   .ENDS

endif


ifndef __IInternalConnection_INTERFACE_DEFINED__
define __IInternalConnection_INTERFACE_DEFINED__

DEFINE_IIDX(IInternalConnection, "72AD0770-6A9F-11d1-BCEC-0060088F444E")

.comdef IInternalConnection : public IUnknown

    AddConnection	proc
    ReleaseConnection	proc
   .ENDS

endif

ifndef _ATL_PACKING
define _ATL_PACKING 8
endif

.pragma pack(push, _ATL_PACKING)

include atldef.inc

AtlAxDialogBoxW proto WINAPI \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCWSTR,
	    hWndParent: HWND,
	  lpDialogProc: DLGPROC,
	   dwInitParam: LPARAM

AtlAxDialogBoxA proto WINAPI \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCSTR,
	    hWndParent: HWND,
	  lpDialogProc: DLGPROC,
	   dwInitParam: LPARAM

ifdef _UNICODE
AtlAxDialogBox equ <AtlAxDialogBoxW>
else
AtlAxDialogBox equ <AtlAxDialogBoxA>
endif

AtlAxCreateDialogW proto WINAPI \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCWSTR,
	    hWndParent: HWND,
	  lpDialogProc: DLGPROC,
	   dwInitParam: LPARAM

AtlAxCreateDialogA proto WINAPI \
	     hInstance: HINSTANCE,
	lpTemplateName: LPCSTR,
	    hWndParent: HWND,
	  lpDialogProc: DLGPROC,
	   dwInitParam: LPARAM

ifdef _UNICODE
AtlAxCreateDialog equ <AtlAxCreateDialogW>
else
AtlAxCreateDialog equ <AtlAxCreateDialogA>
endif

AtlAxCreateControl proto WINAPI \
	      lpszName: LPCOLESTR,
		  hWnd: HWND,
	       pStream: ptr IStream,
	ppUnkContainer: ptr ptr IUnknown

AtlAxCreateControlEx proto WINAPI \
	      lpszName: LPCOLESTR,
		  hWnd: HWND,
	       pStream: ptr IStream,
	ppUnkContainer: ptr ptr IUnknown,
	  ppUnkControl: ptr ptr IUnknown,
	       iidSink: REFIID,
	      punkSink: ptr IUnknown

AtlAxCreateControlLic proto WINAPI \
	      lpszName: LPCOLESTR,
		  hWnd: HWND,
	       pStream: ptr IStream,
	ppUnkContainer: ptr ptr IUnknown,
	       bstrLic: BSTR

AtlAxCreateControlLicEx proto WINAPI \
	      lpszName: LPCOLESTR,
		  hWnd: HWND,
	       pStream: ptr IStream,
	ppUnkContainer: ptr ptr IUnknown,
	  ppUnkControl: ptr ptr IUnknown,
	       iidSink: REFIID,
	      punkSink: ptr IUnknown,
	       bstrLic: BSTR

AtlAxAttachControl proto WINAPI \
	      pControl: ptr IUnknown,
		  hWnd: HWND,
	ppUnkContainer: ptr ptr IUnknown

AtlAxWinInit proto WINAPI

AtlAxGetHost proto WINAPI \
		     h: HWND,
		    pp: ptr ptr IUnknown

AtlAxGetControl proto WINAPI \
		     h: HWND,
		    pp: ptr ptr IUnknown


.pragma pack(pop)

ifndef __IAccessibleProxy_INTERFACE_DEFINED__
define __IAccessibleProxy_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibleProxy, "7A7D9DCF-B7A1-4019-9031-258268846980")

.comdef IAccessibleProxy : public IUnknown

    SetServer		proc :ptr IAccessible, :ptr IAccessibleServer
   .ENDS

endif


ifndef __IAccessibleServer_INTERFACE_DEFINED__
define __IAccessibleServer_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibleServer, "52C8FB5E-D779-4e77-AE9F-F611FA7E9D7A")

.comdef IAccessibleServer : public IUnknown

    SetProxy		proc :ptr IAccessibleProxy
    GetHWND		proc :ptr HWND
    GetEnumVariant	proc :ptr ptr IEnumVARIANT
   .ENDS

endif


BSTR_UserSize		proto WINAPI :ptr ULONG, :ULONG, :ptr BSTR
BSTR_UserMarshal	proto WINAPI :ptr ULONG, :ptr SBYTE, :ptr BSTR
BSTR_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr SBYTE, :ptr BSTR
BSTR_UserFree		proto WINAPI :ptr ULONG, :ptr BSTR

HWND_UserSize		proto WINAPI :ptr ULONG, :ULONG, :ptr HWND
HWND_UserMarshal	proto WINAPI :ptr ULONG, :ptr SBYTE, :ptr HWND
HWND_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr SBYTE, :ptr HWND
HWND_UserFree		proto WINAPI :ptr ULONG, :ptr HWND

endif

