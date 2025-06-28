; DOSCALL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __DOSCALL_INC
define __DOSCALL_INC

.pragma aux(dx, ax, cx)

.enum {

ifdef __LFN__
    DOS_CHDIR                   = 0x713B,
    DOS_RMDIR                   = 0x713A,
    DOS_MKDIR                   = 0x7139,
    DOS_GETCWD                  = 0x7147,
else
    DOS_CHDIR                   = 0x3B00,
    DOS_RMDIR                   = 0x3A00,
    DOS_MKDIR                   = 0x3900,
    DOS_GETCWD                  = 0x4700,
endif
    DOS_CHDRIVE                 = 0x0E00,

    DOS_READ                    = 0,
    DOS_WRITE                   = 1,
    DOS_OPEN                    = 2,
    DOS_CLOSE                   = 3,
    DOS_STAT                    = 4,
    DOS_LSEEK                   = 8,
    DOS_ACCESS                  = 21,
    }

dos_call macro dos
    pushl   ds
    movl    ds,ax
    mov     ax,dos
    int     0x21
    popl    ds
    mov     dx,ax
    sbb     ax,ax
    exitm   <>
    endm

dos_chdir proto asmcall :string_t {
    dos_call(DOS_CHDIR)
    retm<!ZERO?>
    }
dos_rmdir proto asmcall :string_t {
    dos_call(DOS_RMDIR)
    retm<!ZERO?>
    }
dos_mkdir proto asmcall :string_t {
    dos_call(DOS_MKDIR)
    retm<!ZERO?>
    }
dos_getcwd proto asmcall :string_t {
    pushl   ds
    push    si
    movl    ds,ax
    mov     si,dx
    mov     ax,DOS_GETCWD
    xor     dx,dx
    int     0x21
    movl    dx,ds
    mov     cx,ax
    mov     ax,si
    pop     si
    popl    ds
    retm    <CARRY?>
    }
dos_chdrive proto asmcall :int_t {
    mov     ax,DOS_CHDRIVE
    int     0x21
    mov     dx,ax
    sbb     ax,ax
    retm    <!ZERO?>
    }

endif
