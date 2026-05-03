; TSTRING.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Preserve RSI and RDI for System-V calls.
;
ifndef __TSTRING_INC
define __TSTRING_INC

include string.inc

tgetenv     proto fastcall :string_t

ifdef _LIN64
tmemcpy     proto fastcall :ptr, :ptr, :uint_t
tmemset     proto fastcall :ptr, :int_t, :uint_t
tmemcmp     proto fastcall :ptr, :ptr, :uint_t
tmemicmp    proto fastcall :ptr, :ptr, :uint_t
tstrlen     proto fastcall :string_t
tstrchr     proto fastcall :string_t, :int_t
tstrrchr    proto fastcall :string_t, :int_t
tstrcpy     proto fastcall :string_t, :string_t
tstrcat     proto fastcall :string_t, :string_t
tstrncpy    proto fastcall :string_t, :string_t, :int_t
tstrcmp     proto fastcall :string_t, :string_t
tstricmp    proto fastcall :string_t, :string_t
tstrstr     proto fastcall :string_t, :string_t
tfwrite     proto fastcall :string_t, :int_t, :int_t, :LPFILE
tfseek      proto fastcall :LPFILE, :size_t, :int_t
else
define tmemcpy      <memcpy>
define tmemmove     <memmove>
define tmemset      <memset>
define tmemcmp      <memcmp>
define tmemicmp     <_memicmp>
define tstrlen      <strlen>
define tstrchr      <strchr>
define tstrrchr     <strrchr>
define tstrcpy      <strcpy>
define tstrcat      <strcat>
define tstrncpy     <strncpy>
define tstrcmp      <strcmp>
define tstricmp     <_stricmp>
define tstrstr      <strstr>
define tfwrite      <fwrite>
define tfseek       <fseek>
endif

endif
