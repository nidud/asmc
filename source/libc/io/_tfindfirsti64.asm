; _TFINDFIRSTI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include time.inc
include winbase.inc
include tchar.inc

.code

 assume rbx:ptr _tfinddatai64_t, rcx:LPWIN32_FIND_DATA

 _lk_copyblk proc private pFindFileData:LPWIN32_FIND_DATA
    ldr rcx,pFindFileData
    mov eax,[rcx].dwFileAttributes
ifndef __UNIX__
    .if ( eax == FILE_ATTRIBUTE_NORMAL )
        xor eax,eax
    .endif
endif
    mov [rbx].attrib,eax
    mov eax,[rcx].nFileSizeLow
    mov dword ptr [rbx].size,eax
if sizeof(_tfinddatai64_t.size) eq 8
    mov eax,[rcx].nFileSizeHigh
    mov dword ptr [rbx].size[4],eax
endif
    mov [rbx].time_create,__timet_from_ft( &[rcx].ftCreationTime )
    mov rcx,pFindFileData
    mov [rbx].time_access,__timet_from_ft( &[rcx].ftLastAccessTime )
    mov rcx,pFindFileData
    mov [rbx].time_write,__timet_from_ft( &[rcx].ftLastWriteTime )
    mov rcx,pFindFileData
    _tcsncpy( &[rbx].name, &[rcx].cFileName, lengthof(WIN32_FIND_DATA.cFileName) )
    ret
    endp


 _tfindfirsti64 proc uses rbx lpFileName:tstring_t, ff:ptr _tfinddatai64_t
   .new findFileData:WIN32_FIND_DATA
   .new hFindFile:HANDLE
    ldr rbx,ff
    .ifd ( FindFirstFile( ldr(lpFileName), &findFileData ) != -1 )
        mov hFindFile,rax
        _lk_copyblk(&findFileData)
        mov rax,hFindFile
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret
    endp


 _tfindnexti64 proc uses rbx hFindFile:ptr, ff:ptr _tfinddatai64_t
   .new findFileData:WIN32_FIND_DATA
    ldr rbx,ff
    .if FindNextFile( ldr(hFindFile), &findFileData )
        _lk_copyblk(&findFileData)
        xor eax,eax
    .else
        _dosmaperr( GetLastError() )
    .endif
    ret
    endp

    end
