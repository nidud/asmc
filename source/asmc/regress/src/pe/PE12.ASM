
;--- pe binary without relocs
;--- v2.16: suppress .reloc section if it has zero relocations

	.386
	.MODEL FLAT
ifdef @pe_file_flags
@pe_file_flags = @pe_file_flags and not 1	; reset "relocs stripped" flag
endif
	.CODE

print_string proc
	pop esi
nextitem:
	lodsb
	cmp al,0
	jz done
	mov dl, al
	mov ah, 2
	int 21h
	jmp nextitem
done:
	push esi
	ret
print_string endp

main proc c

	call print_string
	db "Hello",13,10,0
	ret

main ENDP

	END main

