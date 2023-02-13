ifndef _APIAPPCONTAINER_
define _APIAPPCONTAINER_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

if NTDDI_VERSION ge NTDDI_WIN8
GetAppContainerNamedObjectPath proto WINAPI :HANDLE, :PSID, :ULONG, :LPWSTR, :PULONG
endif

endif
