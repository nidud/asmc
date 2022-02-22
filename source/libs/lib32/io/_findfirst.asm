; _FINDFIRST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include time.inc
include winbase.inc

    .code

_findnext proc uses esi edi handle:HANDLE, ff:ptr _finddata_t

  local FindFileData:WIN32_FIND_DATAA

    mov edi,ff
    lea esi,FindFileData
    .if FindNextFileA(handle, esi)
        copyblock()
    .else
        osmaperr()
    .endif
    ret

_findnext endp

_findfirst proc uses esi edi ebx lpFileName:LPSTR, ff:ptr _finddata_t

  local FindFileData:WIN32_FIND_DATAA

    mov edi,ff
    lea esi,FindFileData
    mov ebx,FindFirstFileA(lpFileName, esi)
    .if ebx != -1
        copyblock()
    .else
        osmaperr()
    .endif
    mov eax,ebx
    ret

_findfirst endp

    ASSUME esi:ptr WIN32_FIND_DATAA
    ASSUME edi:ptr _finddata_t

copyblock:
    mov eax,[esi].dwFileAttributes
    mov [edi].attrib,eax
    mov eax,[esi].nFileSizeLow
    mov [edi].size,eax
    mov [edi].time_create,FileTimeToTime(&[esi].ftCreationTime)
    mov [edi].time_access,FileTimeToTime(&[esi].ftLastAccessTime)
    mov [edi].time_write, FileTimeToTime(&[esi].ftLastWriteTime)
    lea esi,[esi].cFileName
    lea edi,[edi].name
    mov ecx,260/4
    rep movsd
    xor eax,eax
    ret

    END
