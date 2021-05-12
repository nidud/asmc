
;--- invoke argument is forward ref (pointer)

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

x1 proto :ptr
x2 proto :dword, :dword, :dword, :dword, :ptr

	.code
	invoke x1, vq
	invoke x2, 1, 2, 3, 4, vq
vq dq ?

x1 proc a1:ptr
	ret
x1 endp

x2 proc a1:dword, a2:dword, a3:dword, a4:dword, a5:ptr
	ret
x2 endp

end
