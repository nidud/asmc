ifndef __CHEAP_INC
__CHEAP_INC equ <>
include libc.inc
.xlist

_GRANULARITY    equ 0x10    ; align 16

.classdef CHeap BufferSize:UINT

    heap_base   PVOID ?
    heap_free   PVOID ?

    Alloc       proc :UINT
    Free        proc :PVOID
    Realloc     proc :PVOID, :UINT
    Aligned     proc :UINT, :UINT
    NewString   proc :LPSTR
    Coreleft    proc

    .ends

.classdef CStack BufferSize:UINT, ReservedStack:UINT

    heap_base   PVOID ?
    heap_free   PVOID ?
    stack_ptr   SIZE_T ?

    Alloc       proc :UINT
    Free        proc :PVOID
    Realloc     proc :PVOID, :UINT
    Aligned     proc :UINT, :UINT
    NewString   proc :LPSTR
    Coreleft    proc

    .ends

.list
endif

