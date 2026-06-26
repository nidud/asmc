
;--- v2.16: if pe binary contained relocations and a data? section,
;--- space for the data? section was reserved in the binary, bloating it
;--- with uninitialized data.
;--- also, .data and .data? sections weren't merged.

	.386
	.MODEL flat

IMAGE_FILE_RELOCS_STRIPPED equ 1

ifdef @pe_file_flags
@pe_file_flags = @pe_file_flags and not IMAGE_FILE_RELOCS_STRIPPED
endif

	.data

var1 dd 55aa55aah

	.data?

var2 db 1024 dup (?)

	.code

start proc c
	mov edx, offset var2	;create a base relocation
	ret
start endp

	END start
