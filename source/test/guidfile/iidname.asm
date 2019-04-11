;
; https://blogs.msdn.microsoft.com/oldnewthing/20110228-00/?p=11363
;

include stdio.inc
include tchar.inc
include ole2.inc

    .code

_tmain proc argc:int_t, argv:ptr PTSTR

  local h:HANDLE, hRoot:HANDLE, desc:FILE_ID_DESCRIPTOR
  local buffer[MAX_PATH]:TCHAR
  local result:DWORD

    .if ( ecx == 2 )

        mov hRoot,CreateFile("C:\\", 0,
                 FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
                 NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL)

        .if (eax != INVALID_HANDLE_VALUE)

            mov desc.dwSize,sizeof(desc)
            mov desc._Type,ObjectIdType

            mov rdx,argv
            .ifd (CLSIDFromString([rdx+8], &desc.ObjectId)) == S_OK

                mov h,OpenFileById(hRoot, &desc, GENERIC_READ,
                    FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE, NULL, 0)

                .if (eax != INVALID_HANDLE_VALUE)

                    mov result,GetFinalPathNameByHandle(h, &buffer, ARRAYSIZE(buffer), VOLUME_NAME_NT)
                    .if (result > 0 && result < ARRAYSIZE(buffer))
                         _tprintf("Final path is %s\n", &buffer)
                    .endif
                    CloseHandle(h)
                .endif
            .endif
            CloseHandle(hRoot)
        .endif
    .endif
    xor eax,eax
    ret

_tmain endp

    end _tstart

