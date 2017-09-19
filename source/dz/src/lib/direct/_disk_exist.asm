include direct.inc
include dzlib.inc

    .code

_disk_exist proc uses edx disk
    mov eax,SIZE S_DISK
    mov edx,disk
    dec edx
    mul edx
    lea edx,drvinfo[eax]
    xor eax,eax
    .if [edx].S_DISK.di_flag == eax
	mov eax,edx
    .endif
    ret
_disk_exist endp

    END
