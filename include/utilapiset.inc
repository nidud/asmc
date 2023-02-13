ifndef _APISETUTIL_
define _APISETUTIL_

include apiset.inc
include apisetcconv.inc
include minwindef.inc

EncodePointer proto WINAPI :ptr
DecodePointer proto WINAPI :ptr
EncodeSystemPointer proto WINAPI :ptr
DecodeSystemPointer proto WINAPI :ptr

EncodeRemotePointer proto WINAPI :HANDLE, :ptr, :ptr
DecodeRemotePointer proto WINAPI :HANDLE, :ptr, :ptr

Beep proto WINAPI :DWORD, :DWORD

endif
