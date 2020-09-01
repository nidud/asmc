; STRINGVPRINTFWORKERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include strsafe.inc

.code

StringVPrintfWorkerA proc WINAPI pszDest:STRSAFE_LPSTR, cchDest:size_t, pcchNewDestLength:ptr size_t,
         pszFormat:STRSAFE_LPCSTR, argList:va_list

  local hr:HRESULT
  local retval:SINT
  local cchMax:size_t
  local cchNewDestLength:size_t

    mov hr,S_OK
    mov cchNewDestLength,0

    ;; leave the last space for the null terminator
    mov eax,cchDest
    dec eax
    mov cchMax,eax

if (STRSAFE_USE_SECURE_CRT eq 1) and not defined(STRSAFE_LIB_IMPL)
    mov retval,_vsnprintf_s(pszDest, cchDest, cchMax, pszFormat, argList)
else
    mov retval,_vsnprintf(pszDest, cchMax, pszFormat, argList)
endif
    ;; ASSERT((iRet < 0) || (((size_t)iRet) <= cchMax));

    .if ((retval < 0) || (eax > cchMax))

        ;; need to null terminate the string
        mov ecx,pszDest
        mov eax,cchMax
        mov byte ptr [ecx+eax],0

        mov cchNewDestLength,eax

        ;; we have truncated pszDest
        mov hr,STRSAFE_E_INSUFFICIENT_BUFFER

    .elseif (eax == cchMax)

        ;; need to null terminate the string
        mov ecx,pszDest
        mov eax,cchMax
        mov byte ptr [ecx+eax],0

        mov cchNewDestLength,eax

    .else

        mov cchNewDestLength,eax
    .endif

    mov ecx,pcchNewDestLength
    mov eax,cchNewDestLength
    .if (ecx)

        mov [ecx],eax
    .endif

    mov eax,hr
    ret

StringVPrintfWorkerA endp

    end
