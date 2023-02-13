ifndef _APISETNAMESPACE_
define _APISETNAMESPACE_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

define PRIVATE_NAMESPACE_FLAG_DESTROY      0x00000001

CreatePrivateNamespaceW proto WINAPI :LPSECURITY_ATTRIBUTES, :LPVOID, :LPCWSTR
OpenPrivateNamespaceW proto WINAPI :LPVOID, :LPCWSTR
ClosePrivateNamespace proto WINAPI :HANDLE, :ULONG
CreateBoundaryDescriptorW proto WINAPI :LPCWSTR, :ULONG
AddSIDToBoundaryDescriptor proto WINAPI :ptr, :PSID
DeleteBoundaryDescriptor proto WINAPI :HANDLE

endif
