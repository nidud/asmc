
;--- v2.16: problem with invoke and size of MT_PTR argument.
;--- case: symbol is external ( total_size = 0! )
;--- general problem is that SizeFromMemtype() cannot handle MT_PTR properly.

	.386
	.model flat,stdcall
	option casemap:none

HINSTANCE typedef far32 ptr

externdef hInstance:HINSTANCE

	.code

proc2 proto :HINSTANCE, :DWORD, :dword, :dword, :dword

proc1 proc 

	invoke proc2, hInstance, 0, 0, 0, 0
	ret

proc1 endp

    end
