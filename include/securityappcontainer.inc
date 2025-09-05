ifndef _APIAPPCONTAINER_
define _APIAPPCONTAINER_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif
if NTDDI_VERSION ge NTDDI_WIN8
GetAppContainerNamedObjectPath proto WINAPI :HANDLE, :PSID, :ULONG, :LPWSTR, :PULONG
endif
endif
