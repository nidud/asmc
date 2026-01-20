include stdio.inc

externdef export my_data1 :int_t
ifdef __DLL__ ; Internal data
externdef my_data2 :int_t
endif

my_func1 proto __cdecl _CRTIMP :int_t
my_func2 proto __cdecl _CRTIMP

GETGOT macro
    call @F
@@: pop eax
    add eax,_GLOBAL_OFFSET_TABLE_ + 2
ifndef __DLL__
    mov ebx,eax
endif
    retm<eax>
    endm

Increment proto watcall got:ptr {
    mov ecx,my_data1[got]
    inc int_t ptr [ecx]
    }