include alloc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

alloca	PROC byte_count:UINT
	lea eax,[esp+8]
	mov ecx,[eax-4] ; size to probe
	cmp ecx,1000h	; probe pages
	jnb probe
done:
	sub eax,ecx
	and eax,-16	; align 16
	test [eax],eax	; probe page
	mov ecx,[esp]
	mov esp,eax
	jmp ecx
probe:
	sub eax,1000h
	test [eax],eax
	sub ecx,1000h
	cmp ecx,1000h	; probe pages
	jb  done
	jmp probe
alloca	ENDP

	END
