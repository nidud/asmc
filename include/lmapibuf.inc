ifndef _LMAPIBUF_
define _LMAPIBUF_
NetApiBufferAllocate proto WINAPI :DWORD, :ptr
NetApiBufferFree proto WINAPI :ptr
NetApiBufferReallocate proto WINAPI :ptr, :DWORD, :ptr
NetApiBufferSize proto WINAPI :ptr, :LPDWORD
NetapipBufferAllocate proto WINAPI :DWORD, :ptr
endif

