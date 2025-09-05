ifndef _PROCESSTOPOLOGYAPI_H_
define _PROCESSTOPOLOGYAPI_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

if (_WIN32_WINNT ge 0x0601)
GetProcessGroupAffinity proto WINAPI :HANDLE, :PUSHORT, :PUSHORT
endif
if (_WIN32_WINNT ge 0x0601)
GetThreadGroupAffinity proto WINAPI :HANDLE, :PGROUP_AFFINITY
SetThreadGroupAffinity proto WINAPI :HANDLE, :ptr, :PGROUP_AFFINITY
endif

endif
