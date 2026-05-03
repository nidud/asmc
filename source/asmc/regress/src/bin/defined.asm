    .486
    .model flat
    .code

__SYM__ equ 3

if defined(__SYM__) and __SYM__ ge 3
    mov eax,__SYM__
else
    .err <error>
endif

undef __SYM__

if defined(__SYM__) and __SYM__ ge 3
    .err <error>
else
    nop
endif

__SYM__ equ 2
if defined(__SYM__) and __SYM__ eq 2
    mov eax,__SYM__
else
    .err <error>
endif

undef __SYM__
__SYM__ equ <>
if defined(__SYM__)
    nop
else
    .err <error>
endif

if defined(__SYM2__) or defined(__SYM__)
    nop
else
    .err <error>
endif

if not defined(__SYM2__) and defined(__SYM__)
    nop
else
    .err <error>
endif

if defined(__SYM2__) and not defined(__SYM__)
    .err <error>
else
    nop
endif

    end
