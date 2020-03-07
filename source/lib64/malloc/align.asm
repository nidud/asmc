include stdio.inc
include errno.inc
include string.inc
include malloc.inc
include stddef.inc
include stdlib.inc
include internal.inc

_expand proto __cdecl :ptr, :ptr

IS_2_POW_N macro X
   exitm<(((X) and (X-1)) eq 0)>
   endm

PTR_SZ equ sizeof(ptr_t)

.code

_aligned_free_base proc memblock:ptr

    .if (rcx != NULL)

        free(rcx)
    .endif
    ret

_aligned_free_base endp

_aligned_offset_malloc_base proc size:size_t, alignment:size_t, _offset:size_t

  local p               : uintptr_t,
        retptr          : uintptr_t,
        gap             : uintptr_t,
        nonuser_size    : size_t,
        block_size      : size_t

    ; validation section

    mov rax,rdx
    dec rax
    and rax,rdx
    .ifnz
        _set_errno(EINVAL)
        .return NULL
    .endif
    .if (r8 == 0 || r8 < rcx)
        _set_errno(EINVAL)
        .return NULL
    .endif
    .if rdx < PTR_SZ
        mov edx,PTR_SZ
    .endif
    dec rdx

    ;; gap = number of bytes needed to round up offset to align with PTR_SZ

    xor eax,eax
    sub eax,r8d
    and eax,PTR_SZ-1

    mov gap,rax
    add rax,PTR_SZ
    add rax,rdx

    mov nonuser_size,rax
    add rax,rcx
    mov block_size,rax

    .if (rcx <= rax)

        _set_errno(ENOMEM)
        .return NULL
    .endif

    .return .if malloc(rax) == NULL

    mov p,rax
    add rax,nonuser_size
    add rax,_offset
    mov rdx,alignment
    not rdx
    and rax,rdx
    sub rax,_offset
    mov retptr,rax

    mov rcx,p
    lea rdx,[rcx-HEAP]
    mov [rax-HEAP].HEAP.prev,rdx
    mov [rax-HEAP].HEAP.type,_HEAP_ALIGNED
    ret

_aligned_offset_malloc_base endp

_aligned_malloc_base proc size:size_t, alignment:size_t

    .return _aligned_offset_malloc_base(rcx, rdx, 0)

_aligned_malloc_base endp

_aligned_offset_realloc_base proc memblock:ptr, size:size_t, alignment:size_t, _offset:size_t

  local p       : uintptr_t,
        retptr  : uintptr_t,
        gap     : uintptr_t,
        stptr   : uintptr_t,
        diff    : uintptr_t,
        movsz   : uintptr_t,
        reqsz   : uintptr_t,
        bFree   : int_t

    mov bFree,0

    ; special cases
    .if (rcx == NULL)

        .return _aligned_offset_malloc_base(size, alignment, r9)
    .endif
    .if (rdx == 0)

        _aligned_free_base(rcx)
        .return NULL
    .endif

    ; validation section

    mov rax,r8
    dec rax
    and rax,r8
    .ifnz
        _set_errno(EINVAL)
        .return NULL
    .endif
    .if (r9 == 0 || r9 < rdx)
        _set_errno(EINVAL)
        .return NULL
    .endif

    mov rax,memblock
    and rax,not ( PTR_SZ - 1 )
    sub rax,PTR_SZ
    mov rcx,[rax]
    mov stptr,rcx       ; ptr points to the start of the aligned memory block

    mov rax,alignment
    .if rax < PTR_SZ
        mov eax,PTR_SZ
    .endif
    dec rax
    mov alignment,rax

    ; gap = number of bytes needed to round up offset to align with PTR_SZ

    xor eax,eax
    sub rax,_offset
    and rax,PTR_SZ - 1
    mov gap,rax


    mov diff,memblock
    sub diff,stptr

    ; Mov size is min of the size of data available and sizw requested.

    ;CRT_WARNING_DISABLE_PUSH(22018, "Silence prefast about overflow/underflow")

    _msize(stptr)
    mov rcx,memblock
    sub rcx,stptr
    sub rax,rcx
    mov movsz,rax

    ;CRT_WARNING_POP
    .if movsz > size
        mov movsz,size
    .endif
    mov eax,PTR_SZ
    add rax,gap
    add rax,alignment
    add rax,size
    mov reqsz,rax

    .if (size <= reqsz)
        _set_errno(ENOMEM)
        .return NULL
    .endif

    ; First check if we can expand(reducing or expanding using expand) data
    ; safely, ie no data is lost. eg, reducing alignment and keeping size
    ; same might result in loss of data at the tail of data block while
    ; expanding.
    ;
    ; If no, use malloc to allocate the new data and move data.
    ;
    ; If yes, expand and then check if we need to move the data.
    ;
    mov rax,stptr
    add rax,alignment
    add rax,PTR_SZ
    add rax,gap
    .if (rax < memblock)

        mov p,malloc(reqsz)
        .if rax == NULL
            .return
        .endif
        mov bFree,1

    .else

        ; we need to save errno, which can be modified by _expand
        .new save_errno:errno_t

        mov save_errno,errno
        .if _expand(stptr, reqsz) == NULL

            _set_errno(save_errno)
            .if malloc(reqsz) == NULL
                .return NULL
            .endif
            mov bFree,1
            mov p,rax

        .else
            mov stptr,p
        .endif
    .endif

    mov rcx,memblock
    sub rcx,diff
    mov rdx,memblock
    add rdx,gap
    add rdx,_offset
    mov r8,alignment
    not r8
    and rdx,r8

    .if ( rax == rcx && !rdx )

        .return memblock
    .endif

    mov rax,p
    add rax,PTR_SZ
    add rax,gap
    add rax,alignment
    add rax,_offset
    and rax,r8
    sub rax,_offset
    mov retptr,rax

    mov rdx,stptr
    add rdx,diff
    memmove(rax, rdx, movsz)

    .if bFree
        free(stptr)
    .endif

    mov rax,p
    mov rcx,retptr
    sub rcx,gap
    mov [rcx-8],rax

    .return retptr

_aligned_offset_realloc_base endp

_aligned_realloc_base proc memblock:ptr, size:size_t, alignment:size_t

    .return _aligned_offset_realloc_base(rcx, rdx, r8, 0)

_aligned_realloc_base endp


_aligned_msize_base proc memblock:ptr, _align:size_t, _offset:size_t

  local header_size : size_t,
        footer_size : size_t,
        total_size  : size_t,
        user_size   : size_t,
        gap         : uintptr_t,
        p           : uintptr_t


    mov header_size,0   ; Size of the header block
    mov footer_size,0   ; Size of the footer block
    mov total_size,0    ; total size of the allocated block
    mov user_size,0     ; size of the user block
    mov gap,0           ; keep the alignment of the data block
                        ; after the sizeof(void*) aligned pointer
                        ; to the beginning of the allocated block
    mov p,0             ; computes the beginning of the allocated block


    .if (memblock != NULL)

        _set_errno(EINVAL)
        .return -1
    .endif

    ;; HEADER SIZE + FOOTER SIZE = GAP + ALIGN + SIZE OF A POINTER
    ;; HEADER SIZE + USER SIZE + FOOTER SIZE = TOTAL SIZE

    mov rax,memblock    ; ptr points to the start of the aligned memory block
    and rax,not ( PTR_SZ - 1 )
    sub rax,PTR_SZ      ; ptr is one position behind memblock
                        ; the value in ptr is the start of the real allocated block
    mov rcx,[rax]       ; after dereference ptr points to the beginning of the allocated block
    mov p,rcx

    mov total_size,_msize(rcx)
    mov rax,memblock
    sub rax,p
    mov header_size,rax

    xor eax,eax
    sub rax,_offset
    and rax,PTR_SZ - 1
    mov gap,rax

    ; Alignment cannot be less than sizeof(void*)
    mov rax,_align
    .if rax < PTR_SZ
        mov eax,PTR_SZ
    .endif

    dec rax
    mov _align,rax

    add rax,gap
    add rax,PTR_SZ
    sub rax,header_size
    mov footer_size,rax

    mov rax,total_size
    sub rax,header_size
    sub rax,footer_size
    ret

_aligned_msize_base endp

_aligned_offset_recalloc_base proc memblock:ptr, count:size_t, size:size_t, alignment:size_t, _offset:size_t

  local user_size  : size_t,
        start_fill : size_t,
        retptr     : ptr_t,
        p          : uintptr_t

    xor eax,eax
    mov user_size,rax   ; wanted size, passed to aligned realoc
    mov start_fill,rax  ; location where aligned recalloc starts to fill with 0
                        ; filling must start from the end of the previous user block
    mov retptr,rax      ; result of aligned recalloc
    mov p,rax           ; points to the beginning of the allocated block

    ;; ensure that (size * num) does not overflow

    .if rdx > 0

        xor edx,edx
        mov rax,_HEAP_MAXREQ
        div count

        .if (rax >= r8)

            _set_errno(ENOMEM)
            .return NULL
        .endif
    .endif

    mov rax,r8
    mul count
    mov user_size,rax

    .if rcx != NULL

        mov start_fill,_aligned_msize(rcx, r9, _offset)
    .endif

    mov retptr,_aligned_offset_realloc_base(memblock, user_size, alignment, _offset)

    .if rax != NULL
        mov rdx,start_fill
        mov r8,user_size
        .if rdx < r8
            add rax,rdx
            sub r8,rdx
            memset(rax, 0, r8)
        .endif
    .endif
    .return retptr

_aligned_offset_recalloc_base endp

_aligned_recalloc_base proc memblock:ptr, count:size_t, size:size_t, alignment:size_t

    .return _aligned_offset_recalloc_base(rcx, rdx, r8, r9, 0)

_aligned_recalloc_base endp

    end

