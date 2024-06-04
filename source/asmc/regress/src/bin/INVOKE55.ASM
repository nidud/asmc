
;--- v2.17: accept 32-bit register as vararg argument in non-win64 mode

    .x64
    .model flat
    option casemap:none
    option proc:private

	.const

fmt1 db "%02X",10,0

    .code

printf proc c fmt:ptr, args:vararg
	ret
printf endp

main proc
    invoke printf, addr fmt1, eax
    ret
main endp

    end main
