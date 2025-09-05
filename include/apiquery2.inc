ifndef _APIQUERY2_H_
define _APIQUERY2_H_
ifndef _LIBC_
include libc.inc
endif
include apiset.inc
include apisetcconv.inc
ifndef _MINWINDEF_
include minwindef.inc
endif
IsApiSetImplemented proto WINAPI :PCSTR

endif
