; STAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include sys/stat.inc
include tchar.inc

.code

_tmain proc

ifdef _WIN64

   .new q:_tstati64

    .if _tstat64("makefile", &q)

        _tperror("_stat64()")
       .return( 1 )
    .endif

ifdef __UNIX__
    printf(
        "_stati64:\n"
        " .st_dev      %p\n"
        " .st_ino      %p\n"
        " .st_nlink    %p\n"
        " .st_mode     %d\n"
        " .st_uid      %d\n"
        " .st_gid      %d\n"
        " .st_pad      %d\n"
        " .st_rdev     %p\n"
        " .st_size     %p\n"
        " .st_blksize  %p\n"
        " .st_blocks   %p\n"
        " .st_atime    %p\n"
        " .st_atimesec %p\n"
        " .st_mtime    %p\n"
        " .st_mtimesec %p\n"
        " .st_ctime    %p\n"
        " .st_ctimesec %p\n",
        q.st_dev,
        q.st_ino,
        q.st_nlink,
        q.st_mode,
        q.st_uid,
        q.st_gid,
        q.st_pad,
        q.st_rdev,
        q.st_size,
        q.st_blksize,
        q.st_blocks,
        q.st_atime,
        q.st_atimesec,
        q.st_mtime,
        q.st_mtimesec,
        q.st_ctime,
        q.st_ctimesec)
else
    _tprintf(
        "_stati64:\n"
        " .st_dev      %d\n"
        " .st_ino      %d\n"
        " .st_mode     %x\n"
        " .st_nlink    %d\n"
        " .st_uid      %d\n"
        " .st_gid      %d\n"
        " .st_rdev     %d\n"
        " .st_size     %d\n"
        " .st_atime    %p\n"
        " .st_mtime    %p\n"
        " .st_ctime    %p\n",
        q.st_dev,
        q.st_ino,
        q.st_mode,
        q.st_nlink,
        q.st_uid,
        q.st_gid,
        q.st_rdev,
        q.st_size,
        q.st_atime,
        q.st_mtime,
        q.st_ctime)
endif

else
    .new p:_tstat32

    .if _tstat("makefile", &p)

        _tperror("_stat()")
       .return( 1 )
    .endif

ifdef __UNIX__
    printf(
        "_stat32:\n"
        " .st_dev      %p\n"
        " .st_ino      %p\n"
        " .st_nlink    %p\n"
        " .st_mode     %d\n"
        " .st_uid      %d\n"
        " .st_gid      %d\n"
        " .st_pad      %d\n"
        " .st_rdev     %p\n"
        " .st_size     %p\n"
        " .st_blksize  %p\n"
        " .st_blocks   %p\n"
        " .st_atime    %p\n"
        " .st_atimesec %p\n"
        " .st_mtime    %p\n"
        " .st_mtimesec %p\n"
        " .st_ctime    %p\n"
        " .st_ctimesec %p\n",
        p.st_dev,
        p.st_ino,
        p.st_nlink,
        p.st_mode,
        p.st_uid,
        p.st_gid,
        p.st_pad,
        p.st_rdev,
        p.st_size,
        p.st_blksize,
        p.st_blocks,
        p.st_atime,
        p.st_atimesec,
        p.st_mtime,
        p.st_mtimesec,
        p.st_ctime,
        p.st_ctimesec)
else
    _tprintf(
        "_stat32:\n"
        " .st_dev      %d\n"
        " .st_ino      %d\n"
        " .st_mode     %x\n"
        " .st_nlink    %d\n"
        " .st_uid      %d\n"
        " .st_gid      %d\n"
        " .st_rdev     %d\n"
        " .st_size     %d\n"
        " .st_atime    %p\n"
        " .st_mtime    %p\n"
        " .st_ctime    %p\n",
        p.st_dev,
        p.st_ino,
        p.st_mode,
        p.st_nlink,
        p.st_uid,
        p.st_gid,
        p.st_rdev,
        p.st_size,
        p.st_atime,
        p.st_mtime,
        p.st_ctime)
endif
endif
   .return(0)

_tmain endp

    end _tstart
