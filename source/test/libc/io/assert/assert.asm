; ASSERT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc
include stdlib.inc
include fcntl.inc
include sys/stat.inc
include assert.inc
include tchar.inc

.assert:on

.code

main proc

  local buf[4096]:byte
  local ff:_finddata_t
ifndef __UNIX__
  local wf:_wfinddata_t
endif
  local fd:int_t

    .assert _creat("test.fil",_S_IREAD or _S_IWRITE) != -1
    .assert _close(eax) == 0
    .assert _open("test.fil",O_RDWR) == 3
     mov fd,eax
    .assert _chsize(fd,0) == 0
    .assert _filelength(fd) == 0
     mov ebx,8192
    .assert _chsize(fd, rbx) == 0
    .assert _filelength(fd) == 8192
    .repeat
        .assert _read(fd, addr buf, 1) == 1
        .assert buf == 0
        dec ebx
    .until !ebx
    .assert _eof(fd) == 1
    .assert _filelength(fd) == 8192
    .assert _lseek(fd, 16384, SEEK_SET) == 16384
    .assert _tell(fd) == 16384
    .assert _write(fd, "!", 1) == 1
    .assert _lseek(fd, 8192, SEEK_SET) == 8192
    xor ebx,ebx
    .repeat
        .assert _read(fd, addr buf, 1) == 1
        .assert buf == 0
        inc ebx
    .until  ebx == 8192
    .assert _read(fd, addr buf, 1) == 1
    .assert buf == '!'
    .assertd _close(fd) == 0
    .assertd getfattr("test.fil") != -1
ifndef __UNIX__
    .assertd _wgetfattr(L"test.fil") != -1
endif
    .assertd remove("test.fil") == 0
    .assertd getfattr("test.fil") == -1
ifndef __UNIX__
    .assertd _wgetfattr(L"test.fil") == -1
endif
    .assert _findfirst("makefile", &ff) != -1
    .assert !_findclose(rax)
    .assert !strcmp(&ff.name, "makefile")
    .assert _findfirst("?akefile", &ff) != -1
    .assert !_findclose(rax)
ifndef __UNIX__
    .assert _wfindfirst(L"makefile", &wf) != -1
    .assert !_findclose(rax)
endif
    .return( 0 )

main endp

    end
