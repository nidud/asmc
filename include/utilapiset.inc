ifndef _APISETUTIL_
define _APISETUTIL_
ifndef _APIQUERY2_H_
include apiquery2.inc
endif

EncodePointer proto WINAPI :ptr
DecodePointer proto WINAPI :ptr
EncodeSystemPointer proto WINAPI :ptr
DecodeSystemPointer proto WINAPI :ptr

EncodeRemotePointer proto WINAPI :HANDLE, :ptr, :ptr
DecodeRemotePointer proto WINAPI :HANDLE, :ptr, :ptr

Beep proto WINAPI :DWORD, :DWORD

endif
