ifndef _ADSPROP_H_
define _ADSPROP_H_
.pragma list(push, 0)

WM_ADSPROP_NOTIFY_PAGEINIT equ (WM_USER + 1101)
WM_ADSPROP_NOTIFY_PAGEHWND equ (WM_USER + 1102)
WM_ADSPROP_NOTIFY_CHANGE equ (WM_USER + 1103)
WM_ADSPROP_NOTIFY_APPLY equ (WM_USER + 1104)
WM_ADSPROP_NOTIFY_SETFOCUS equ (WM_USER + 1105)
WM_ADSPROP_NOTIFY_FOREGROUND equ (WM_USER + 1106)
WM_ADSPROP_NOTIFY_EXIT	equ (WM_USER + 1107)
WM_ADSPROP_NOTIFY_ERROR equ (WM_USER + 1110)

ADSPROPINITPARAMS	STRUC
dwSize			dd ?
dwFlags			dd ?
hr			HRESULT ?
pDsObj			PVOID ?
pwzCN			LPWSTR ?
pWritableAttrs		PADS_ATTR_INFO ?
ADSPROPINITPARAMS	ENDS
PADSPROPINITPARAMS	typedef ptr ADSPROPINITPARAMS

ADSPROPERROR		STRUC
hwndPage		HWND ?
pszPageTitle		PWSTR ?
pszObjPath		PWSTR ?
pszObjClass		PWSTR ?
hr			HRESULT ?
pszError		PWSTR ?
ADSPROPERROR		ENDS
PADSPROPERROR		typedef ptr ADSPROPERROR

;STDAPI
ADsPropCreateNotifyObj proto WINAPI \
	pAppThdDataObj: LPDATAOBJECT,
	 pwzADsObjName: PWSTR,
	   phNotifyObj: ptr

;STDAPI_(BOOL)
ADsPropGetInitInfo proto WINAPI \
	    hNotifyObj: HWND,
	   pInitParams: PADSPROPINITPARAMS

ADsPropSetHwndWithTitle proto WINAPI \
	    hNotifyObj: HWND,
		 hPage: HWND,
	      ptzTitle: PTSTR

ADsPropSetHwnd proto WINAPI \
	    hNotifyObj: HWND,
		 hPage: HWND

ADsPropCheckIfWritable proto WINAPI \
	       pwzAttr: PWSTR,
	pWritableAttrs: PADS_ATTR_INFO

ADsPropSendErrorMessage proto WINAPI \
	    hNotifyObj: HWND,
		pError: PADSPROPERROR

ADsPropShowErrorDialog proto WINAPI \
	    hNotifyObj: HWND,
		 hPage: HWND

.pragma list(pop)
endif
