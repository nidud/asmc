ifndef _LMAPIBUF_
define _LMAPIBUF_

;NET_API_STATUS
NetApiBufferAllocate proto WINAPI \
             ByteCount: DWORD,
                Buffer: ptr LPVOID

;NET_API_STATUS
NetApiBufferFree proto WINAPI \
                Buffer: LPVOID

;NET_API_STATUS
NetApiBufferReallocate proto WINAPI \
             OldBuffer: LPVOID,
          NewByteCount: DWORD,
             NewBuffer: ptr LPVOID

;NET_API_STATUS
NetApiBufferSize proto WINAPI \
                Buffer: LPVOID,
             ByteCount: LPDWORD

;NET_API_STATUS
NetapipBufferAllocate proto WINAPI \
             ByteCount: DWORD,
                Buffer: ptr LPVOID

endif ;; _LMAPIBUF_

