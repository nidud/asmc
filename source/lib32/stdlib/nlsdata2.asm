ifndef DLL_FOR_WIN32S

include setlocal.inc
include winnls.inc

.data
;
; Locale handles.
;
__lc_handle UINT ?
	UINT _CLOCALEHANDLE
	UINT _CLOCALEHANDLE
	UINT _CLOCALEHANDLE
	UINT _CLOCALEHANDLE
	UINT _CLOCALEHANDLE
	UINT _CLOCALEHANDLE
;
;  Code page.
;
__lc_codepage dd _CLOCALECP

endif  ; DLL_FOR_WIN32S

	end
