include string.inc
include stdio.inc

.code

wmain proc argc:SINT, argv:ptr

    mov esi,argv
    mov edi,argc

    .while edi
	lodsd
	wprintf( "%s\n", eax )
	dec edi
    .endw

    xor eax,eax
    ret

wmain endp

    end
