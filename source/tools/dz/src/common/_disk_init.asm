include direct.inc
include dzlib.inc

    .code

_disk_init proc uses edi disk

    mov edi,disk
    .if !_disk_test(edi)

	.if _disk_select("Select disk")

	    _disk_init(eax)
	    mov edi,eax
	.endif
    .endif
    mov eax,edi
    ret

_disk_init endp

    END
