; SIGACTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc
include stdlib.inc

ifdef __UNIX__
ifdef _AMD64_

define __USE_GNU
include ucontext.inc

sig_restore proto

    .code

sigaction proc sig:int_t, act:ptr sigaction_t, oact:ptr sigaction_t

   .new a:compat_sigaction = {0}

    mov eax,-1
    .switch edi
    .case SIGABRT   : inc eax
    .case SIGBREAK  : inc eax
    .case SIGTERM   : inc eax
    .case SIGSEGV   : inc eax
    .case SIGFPE    : inc eax
    .case SIGILL    : inc eax
    .case SIGINT    : inc eax
    .endsw

    .if ( rsi == 0 || eax == -1 )

        .return( _set_errno( EINVAL ) )
    .endif

    mov a.sa_handler,   [rsi].sigaction_t.sa_handler
    mov a.sa_flags,     [rsi].sigaction_t.sa_flags
    mov a.sa_restorer,  [rsi].sigaction_t.sa_restorer
    mov a.sa_mask,      [rsi].sigaction_t.sa_mask

    .if ( !( a.sa_flags & SA_RESTORER ) || a.sa_restorer == NULL )

        or  a.sa_flags,SA_RESTORER
        mov a.sa_restorer,&sig_restore
    .endif

    .ifsd ( sys_rt_sigaction(edi, rsi, rdx) < 0 )

        neg eax
        _set_errno(eax)
    .endif
    ret

sigaction endp

endif
endif
    end
