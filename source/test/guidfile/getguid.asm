;
; https://blogs.msdn.microsoft.com/oldnewthing/20110228-00/?p=11363
;

include stdio.inc
include tchar.inc
include ole2.inc
include winioctl.inc

    .code

_tmain proc argc:int_t, argv:ptr PTSTR

  local h:HANDLE, buf:FILE_OBJECTID_BUFFER, cbOut:DWORD
  local guid:GUID, szGuid[39]:WCHAR

    .if ( ecx == 2 )
        mov h,CreateFile([rdx+8], 0,
                 FILE_SHARE_READ or FILE_SHARE_WRITE or FILE_SHARE_DELETE,
                 NULL,
                 OPEN_EXISTING, 0, NULL)

        .if (eax != INVALID_HANDLE_VALUE)

            .if (DeviceIoControl(h, FSCTL_CREATE_OR_GET_OBJECT_ID,
                 NULL, 0, &buf, sizeof(buf),
                 &cbOut, NULL))

                CopyMemory(&guid, &buf.ObjectId, sizeof(GUID))
                StringFromGUID2(&guid, &szGuid, 39)
                _tprintf("GUID is %ws\n", &szGuid)
            .endif
            CloseHandle(h)
        .endif
    .endif
    xor eax,eax
    ret

_tmain endp

    end _tstart

