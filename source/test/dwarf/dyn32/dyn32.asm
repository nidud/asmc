include stdio.inc

externdef _GLOBAL_OFFSET_TABLE_:near

`__x86.get_pc_thunk.bx` proto

GOT macro string
    call `__x86.get_pc_thunk.bx`
    add ebx,_GLOBAL_OFFSET_TABLE_ + 2
    lea eax,[ebx+(sectionrel @CStr(string))]
    exitm<eax>
    endm

`.note.GNU-stack` segment info
`.note.GNU-stack` ends

.code

main proc

    printf(GOT("GOT: %X\n"), ebx)
    xor eax,eax
    ret
    endp

    end
