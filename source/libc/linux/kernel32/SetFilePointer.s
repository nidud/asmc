; SETFILEPOINTER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include winbase.inc

.code

 SetFilePointer proc WINAPI uses rbx hFile:HANDLE, lDistanceToMove:LONG,
        lpDistanceToMoveHigh:PLONG, dwMoveMethod:DWORD

   .new dist:LARGE_INTEGER
   .new pos:LARGE_INTEGER
    ldr rcx,hFile
    ldr eax,lDistanceToMove
    ldr rbx,lpDistanceToMoveHigh
    cdq
    .if ( rbx )
        mov edx,[rbx]
    .endif
    mov dword ptr dist,eax
    mov dword ptr dist,edx
    .ifd ( !SetFilePointerEx(rcx, dist, &pos, ldr(dwMoveMethod)) )
        .return( INVALID_SET_FILE_POINTER )
    .endif
    mov eax,dword ptr pos
    mov edx,dword ptr pos
    .if ( rbx )
        mov [rbx],edx
        .if ( eax == INVALID_SET_FILE_POINTER )
            SetLastError( NO_ERROR )
            mov eax,INVALID_SET_FILE_POINTER
        .endif
    .else
        .if ( edx != 0 || eax >= INVALID_SET_FILE_POINTER )
            SetLastError( ERROR_NEGATIVE_SEEK )
           .return( INVALID_SET_FILE_POINTER )
        .endif
    .endif
    ret
    endp

    end
