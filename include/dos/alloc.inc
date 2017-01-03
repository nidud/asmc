ifndef __LIBC_INC
 include libc.inc
endif

.xlist

palloc		PROTO _CType	; <-- ax size in para
malloc		PROTO _CType :WORD
free		PROTO _CType :DWORD
coreleft	PROTO _CType
nalloc		PROTO _CType :WORD
nfree		PROTO _CType :WORD

EMMPAGE equ	4000h

externdef	dzemm:BYTE		; dzemm.dll

emmcoreleft	PROTO _CType		; dx:ax core left : NULL
emmalloc	PROTO _CType :WORD	; (pages) ax handle : -1
emmfree		PROTO _CType :WORD	; (handle) ax 0 : ?
emmread		PROTO _CType :DWORD, :WORD, :WORD ; (void *, handle, page) ax 0 : ?
emmwrite	PROTO _CType :DWORD, :WORD, :WORD ; (void *, handle, page) ax 0 : ?
emmversion	PROTO _CType		; ax version : 0
emmnumfreep	PROTO _CType		; ax unallocated page count : 0

.list

