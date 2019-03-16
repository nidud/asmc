; NLSDATA2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef DLL_FOR_WIN32S

public __lc_handle
public __lc_codepage

include mtdll.inc
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
