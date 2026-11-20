;
; Memory functions.
;
; VirtualAlloc and VirtualProtect is used for testing the limit
; for string and memory function. The trap is normally a "x\0"
; at the end of a protected page, which will trigger an
; exception if the function tries to read beyond the page.
;
; Use "memory -crash" to verify SIGSEGV on over-read
;
include stdio.inc
include string.inc
include memoryapi.inc
include heapapi.inc

.code

main proc argc:int_t, argv:ptr ptr char_t

   .new pHeap:string_t
   .new pPage:string_t
   .new oldProt:DWORD

   ; dummy process heap handle

   .new processHeap:HANDLE = GetProcessHeap()

    ; HeapAlloc / HeapReAlloc / HeapSize / HeapFree

    .if !HeapAlloc(processHeap, HEAP_ZERO_MEMORY, 32)
        printf("HeapAlloc failed\n")
       .return( 1 )
    .endif
    mov pHeap,rax
    strcpy(pHeap, "Hello Linux Heap")
    mov pHeap,HeapReAlloc(processHeap, HEAP_ZERO_MEMORY, pHeap, 128)
    printf("HeapReAlloc (%zu bytes): %s\n", HeapSize(processHeap, 0, pHeap), pHeap)
    HeapFree(processHeap, 0, pHeap)

    ; VirtualAlloc / VirtualProtect / VirtualFree

    .if !VirtualAlloc(NULL, 8192, MEM_COMMIT or MEM_RESERVE, PAGE_READWRITE)
        printf("VirtualAlloc failed\n")
       .return( 1 )
    .endif
    mov pPage,rax
    .ifd !VirtualProtect(addr [rax+4096], 4096, PAGE_NOACCESS, &oldProt)
        printf("VirtualProtect failed\n")
        .return( 1 )
    .endif
    mov rbx,pPage
    add rbx,4094
    strlen(strcpy(rbx, "x"))
    .if ( argc > 1 )
        mov rcx,argv
        mov rcx,[rcx+size_t]
        .ifd !strcmp(rcx, "-crash")
            movzx eax,byte ptr [rbx+2] ; Should trigger SIGSEGV
            printf("ERROR: Guard page failed to trap! Read: %02X\n", eax)
        .endif
    .endif
    VirtualFree(pPage, 0, MEM_RELEASE)
    .return( 0 )
    endp

    end
