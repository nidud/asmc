;
; https://blogs.msdn.microsoft.com/oldnewthing/20110228-00/?p=11363
;

include stdio.inc
include tchar.inc
include ole2.inc

    .code

_tmain proc argc:int_t, argv:ptr PTSTR

  local h:HANDLE, hRoot:HANDLE, desc:FILE_ID_DESCRIPTOR
  local b:BYTE, cb:DWORD

    .if ( ecx == 2 )

        .ifd CreateFile("D:\\", 0,
                FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
                NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS,
                NULL) != INVALID_HANDLE_VALUE

            mov hRoot,rax
            mov rcx,argv
            mov desc.dwSize,sizeof(desc)
            mov desc.Type,ObjectIdType

            .ifd (CLSIDFromString([rcx+8], &desc.ObjectId)) == S_OK

                .ifd OpenFileById(hRoot, &desc, GENERIC_READ,
                        FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
                        NULL, 0) != INVALID_HANDLE_VALUE

                    mov h,rax
                    .if ReadFile(rax, &b, 1, &cb, NULL)

                        _tprintf("First byte of file is 0x%02x\n", b)
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

