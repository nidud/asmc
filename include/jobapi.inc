ifndef _JOBAPISET_H_
define _JOBAPISET_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

if (_WIN32_WINNT ge 0x0501)
IsProcessInJob proto WINAPI :HANDLE, :HANDLE, :PBOOL
endif

endif
