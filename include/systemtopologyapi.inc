ifndef _SYSTEMTOPOLOGY_H_
define _SYSTEMTOPOLOGY_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

GetNumaHighestNodeNumber proto WINAPI :PULONG

if _WIN32_WINNT ge 0x0601
GetNumaNodeProcessorMaskEx proto WINAPI :USHORT, :PGROUP_AFFINITY
endif
if _WIN32_WINNT ge 0x0601
GetNumaProximityNodeEx proto WINAPI :ULONG, :PUSHORT
endif

endif
