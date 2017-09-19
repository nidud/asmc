include errno.inc

FORMAT_MESSAGE_ALLOCATE_BUFFER	equ 00000100h
FORMAT_MESSAGE_FROM_SYSTEM  equ 00001000h
FORMAT_MESSAGE_IGNORE_INSERTS	equ 00000200h

FormatMessageA proto :dword, :dword, :dword, :dword, :dword, :dword, :dword

    .data

    default db "Unknown error",0

    .code

getsyserr proc errcode:SIZE_T
    local msg
    .if FormatMessageA(1300h, 0, errcode, 0400h, addr msg, 0, 0)
	mov eax,msg
    .else
	lea eax,default
    .endif
    ret
getsyserr endp

    END
