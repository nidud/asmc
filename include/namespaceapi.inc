ifndef _APISETNAMESPACE_
define _APISETNAMESPACE_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif
ifndef _MINWINBASE_
include minwinbase.inc
endif

define PRIVATE_NAMESPACE_FLAG_DESTROY      0x00000001

CreatePrivateNamespaceW proto WINAPI :LPSECURITY_ATTRIBUTES, :LPVOID, :LPCWSTR
OpenPrivateNamespaceW proto WINAPI :LPVOID, :LPCWSTR
ClosePrivateNamespace proto WINAPI :HANDLE, :ULONG
CreateBoundaryDescriptorW proto WINAPI :LPCWSTR, :ULONG
AddSIDToBoundaryDescriptor proto WINAPI :ptr, :PSID
DeleteBoundaryDescriptor proto WINAPI :HANDLE

endif
