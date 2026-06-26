
;--- v2.17: if model is != flat, but current segment is 64-bit,
;--- don't reject FLAT override for constant addresses. Also,
;--- ensure that no address prefix is generated.

	.model small
	.x64

_TEXT64 segment use64 public 'CODE'
_TEXT64 ends

	.code _TEXT64
	inc dword ptr flat:[46Ch]

	end
