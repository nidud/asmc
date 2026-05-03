ifndef _JOBAPISET_H_
define _JOBAPISET_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

if (_WIN32_WINNT ge 0x0501)
IsProcessInJob proto WINAPI :HANDLE, :HANDLE, :PBOOL
endif

endif
