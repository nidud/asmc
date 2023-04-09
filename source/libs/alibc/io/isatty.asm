; _ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include linux/kernel.inc

cc_t        typedef uchar_t
speed_t     typedef uint_t
tcflag_t    typedef uint_t

define TCGETS 0x5401

; The following corresponds to the values from the Linux 2.1.20 kernel.

define __KERNEL_NCCS 19

__kernel_termios struct
c_iflag     tcflag_t ?                  ; input mode flags
c_oflag     tcflag_t ?                  ; output mode flags
c_cflag     tcflag_t ?                  ; control mode flags
c_lflag     tcflag_t ?                  ; local mode flags
c_line      cc_t ?                      ; line discipline
c_cc        cc_t __KERNEL_NCCS dup(?)   ; control characters
__kernel_termios ends

    .code

isatty proc fd:int_t

    .new termios:__kernel_termios

    .if ( sys_ioctl(edi, TCGETS, &termios ) == 0 )
        .return true
    .endif
    .return false

isatty endp

    end
