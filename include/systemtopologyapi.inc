ifndef _SYSTEMTOPOLOGY_H_
define _SYSTEMTOPOLOGY_H_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

GetNumaHighestNodeNumber proto WINAPI :PULONG

if _WIN32_WINNT ge 0x0601
GetNumaNodeProcessorMaskEx proto WINAPI :USHORT, :PGROUP_AFFINITY
endif
if _WIN32_WINNT ge 0x0601
GetNumaProximityNodeEx proto WINAPI :ULONG, :PUSHORT
endif

endif
