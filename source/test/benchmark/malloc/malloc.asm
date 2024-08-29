; MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include string.inc
include pcg_basic.inc
include sselevel.inc
include tchar.inc

define MAXCNT 1000

.data
 alloc_size label size_t
 repeat MAXCNT
 size_t __pcg32_randw()
 endm

.data?
 alloc_ptr size_t MAXCNT dup(?)

.code

setsselev proc uses rbx

ifndef _WIN64
    pushfd
    pop     eax
    mov     ecx,0x200000
    mov     edx,eax
    xor     eax,ecx
    push    eax
    popfd
    pushfd
    pop     eax
    xor     eax,edx
    and     eax,ecx

    .ifnz
endif

        xor eax,eax
        cpuid
        .if rax
            .if ah == 5
                xor     eax,eax
            .else
                mov     eax,7
                xor     ecx,ecx
                cpuid               ; check AVX2 support
                xor     eax,eax
                bt      ebx,5       ; AVX2
                adc     eax,eax     ; into bit 9
                push    rax
                mov     eax,1
                cpuid
                pop     rax
                bt      ecx,28      ; AVX support by CPU
                adc     eax,eax     ; into bit 8
                bt      ecx,27      ; XGETBV supported
                adc     eax,eax     ; into bit 7
                bt      ecx,20      ; SSE4.2
                adc     eax,eax     ; into bit 6
                bt      ecx,19      ; SSE4.1
                adc     eax,eax     ; into bit 5
                bt      ecx,9       ; SSSE3
                adc     eax,eax     ; into bit 4
                bt      ecx,0       ; SSE3
                adc     eax,eax     ; into bit 3
                bt      edx,26      ; SSE2
                adc     eax,eax     ; into bit 2
                bt      edx,25      ; SSE
                adc     eax,eax     ; into bit 1
                bt      ecx,0       ; MMX
                adc     eax,eax     ; into bit 0
            .endif
        .endif
ifndef _WIN64
    .endif
endif
    ret

setsselev endp

_tmain proc argc:int_t, argv:array_t

   .new time_start:size_t
   .new free_start:size_t

ifndef __UNIX__
ifdef __PE__
   _tprintf( "MSVCRT:\n" )
else
   _tprintf( "LIBC:\n" )
endif
endif
    .ifd !( setsselev() & SSE_SSE2 )

        _tprintf( "CPU error: Need SSE2 level\n" )
        .return( 0 )
    .endif

    xor eax,eax
    cpuid
    rdtsc
    mov time_start,rax

    .for ( ebx = 0 : ebx < MAXCNT : ebx++ )

        lea rcx,alloc_size
        mov rcx,[rcx+rbx*size_t]
        malloc(rcx)
        lea rcx,alloc_ptr
        mov [rcx+rbx*size_t],rax
    .endf

    xor eax,eax
    cpuid
    rdtsc
    mov free_start,rax

    .for ( ebx = 0 : ebx < MAXCNT : ebx++ )

        lea rcx,alloc_ptr
        mov rcx,[rcx+rbx*size_t]
        free(rcx)
    .endf

    xor eax,eax
    cpuid
    rdtsc
    mov rdx,rax
    sub rax,time_start
    sub rdx,free_start
    mov rcx,free_start
    sub rcx,time_start

    _tprintf("%9zi cycles -- malloc: %9zi free: %9zi\n", rax, rcx, rdx)
   .return( 0 )

_tmain endp


    end _tstart
