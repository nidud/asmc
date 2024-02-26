; TMACRO.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
.pragma list(push, 0)

ifndef _INC_TMACRO
define _INC_TMACRO
ifndef _INC_TCHAR
include tchar.inc
endif

option dotname

ifdef _UNICODE
define __a      <ax>
define __b      <bx>
define __c      <cx>
define __d      <dx>
define .scasb   <scasw>
define .stosb   <stosw>
define .lodsb   <lodsw>
define .movsb   <movsw>
else
define __a      <al>
define __b      <bl>
define __c      <cl>
define __d      <dl>
define .scasb   <scasb>
define .stosb   <stosb>
define .lodsb   <lodsb>
define .movsb   <movsb>
endif
endif
.pragma list(pop)
