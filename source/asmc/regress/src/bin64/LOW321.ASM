
ifndef __ASMC64__
    .x64
    .model flat
endif

	.code

	add rax,low32 v1

v1	db 0

end
