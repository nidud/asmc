
;--- direct addressing with constant addresses
;--- Note that ML64 has a different syntax!

ifndef __ASMC64__
	.x64
	.model flat
endif
	assume gs:nothing

	.code

start proc

ifdef __JWASM__
	mov cl,flat:[80000000h]
	mov cl,flat:[0ffffffff7fffffffh]
else
	mov cl,[80000000h]
	mov cl,[0ffffffff7fffffffh]
endif

start endp

end
