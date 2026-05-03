; UCONTEXT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __UCONTEXT_INC
define __UCONTEXT_INC

include signal.inc

.pragma pack(push, size_t)

stack_t     struct ; 24
ss_sp       ptr_t ?
ss_flags    int_t ?
ss_size     size_t ?
stack_t     ends

ifdef _AMD64_

greg_t typedef qword

define __NGREG  23
ifdef __USE_MISC
define NGREG __NGREG
endif

ifdef __USE_GNU

.enum {
  REG_R8 = 0,
  REG_R9,
  REG_R10,
  REG_R11,
  REG_R12,
  REG_R13,
  REG_R14,
  REG_R15,
  REG_RDI,
  REG_RSI,
  REG_RBP,
  REG_RBX,
  REG_RDX,
  REG_RAX,
  REG_RCX,
  REG_RSP,
  REG_RIP,
  REG_EFL,
  REG_CSGSFS,
  REG_ERR,
  REG_TRAPNO,
  REG_OLDMASK,
  REG_CR2
}
endif

_libc_fpxreg        struct
  significand       dw 4 dup(?)
  exponent          dw ?
  __glibc_reserved1 dw 3 dup(?)
_libc_fpxreg        ends

_libc_xmmreg        struct
  element           dd 4 dup(?)
_libc_xmmreg        ends

_libc_fpstate       struct ; 512
  _cwd              dw ?
  swd               dw ?
  ftw               dw ?
  fop               dw ?
  _rip              dq ?
  rdp               dq ?
  mxcsr             dd ?
  mxcr_mask         dd ?
  _st               _libc_fpxreg 8 dup(<>)
  _xmm              _libc_xmmreg 16 dup(<>)
  __glibc_reserved1 dd 24 dup(?)
_libc_fpstate       ends

mcontext_t          struct ; 256
  gregs             greg_t __NGREG dup(?)
  fpregs            ptr _libc_fpstate ?
  __reserved1       dq 8 dup(?)
mcontext_t          ends

ucontext_t          struct ; 968
  uc_flags          dd ?
  uc_link           ptr ucontext_t ?
  uc_stack          stack_t <>
  uc_mcontext       mcontext_t <>
  uc_sigmask        sigset_t <>
  __fpregs_mem      _libc_fpstate <>
  __ssp             dq 4 dup(?)
ucontext_t          ends

else

greg_t typedef int_t

define __NGREG 19
ifdef __USE_MISC
define NGREG __NGREG
endif

ifdef __USE_GNU

.enum {
  REG_GS = 0,
  REG_FS,
  REG_ES,
  REG_DS,
  REG_EDI,
  REG_ESI,
  REG_EBP,
  REG_ESP,
  REG_EBX,
  REG_EDX,
  REG_ECX,
  REG_EAX,
  REG_TRAPNO,
  REG_ERR,
  REG_EIP,
  REG_CS,
  REG_EFL,
  REG_UESP,
  REG_SS
}
endif

_libc_fpreg         struct
  significand       dw 4 dup(?)
  exponent          dw ?
_libc_fpreg         ends

_libc_fpstate       struct
  cw                dd ?
  sw                dd ?
  tag               dd ?
  ipoff             dd ?
  cssel             dd ?
  dataoff           dd ?
  datasel           dd ?
  _st               _libc_fpreg 8 dup(<>)
  status            dd ?
_libc_fpstate       ends

mcontext_t          struct
  gregs             greg_t __NGREG dup(?)
  fpregs            ptr _libc_fpstate ?
  oldmask           dd ?
  _cr2              dd ?
mcontext_t          ends

ucontext_t          struct
  uc_flags          dd ?
  uc_link           ptr ucontext_t ?
  uc_stack          stack_t <>
  uc_mcontext       mcontext_t <>
  uc_sigmask        sigset_t <>
  __fpregs_mem      _libc_fpstate <>
ucontext_t          ends

endif
.pragma pack(pop)
endif
