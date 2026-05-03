include stdio.inc

externdef export my_data1 :size_t
ifdef __DLL__ ; Internal data
externdef my_data2 :size_t
endif

my_func1 proto __cdecl _CRTIMP :int_t
my_func2 proto __cdecl _CRTIMP

ifdef _WIN64
define GOT 0
else
define GOT <ebx>
endif

Increment proto {
ifdef _WIN64
    mov rcx,my_data1
else
    call @F
@@: pop eax
    add eax,_GLOBAL_OFFSET_TABLE_ + 2
ifndef __DLL__
    mov ebx,eax
endif
    mov ecx,my_data1[eax]
endif
    inc size_t ptr [rcx]
    }
