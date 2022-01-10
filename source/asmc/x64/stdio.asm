; STDIO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

define CMASK 644 ; rw-r--r--

.data
_iob    _iobuf <0,0,0,_IOREAD,0,0,0>
stdout  _iobuf <0,0,0,_IOWRT,1,0,0>    ; stdout
stderr  _iobuf <0,0,0,_IOWRT,2,0,0>    ; stderr
_first  _iobuf _NSTREAM_ - 4 dup(<0,0,0,0,-1,0,0>)
_last   _iobuf <0,0,0,0,-1,0,0>

    .code

    assume rsi:LPFILE

fopen proc uses rsi rdi rbx fname:LPSTR, mode:LPSTR

    .for ( rsi = &_first,
           r10 = &_last,
           eax = 0 : rsi <= r10 : rsi += FILE )

        .if !( [rsi]._flag & _IOREAD or _IOWRT or _IORW )

            mov [rsi]._cnt,eax
            mov [rsi]._flag,eax
            mov [rsi]._ptr,rax
            mov [rsi]._base,rax
            dec eax
            mov [rsi]._file,eax
            mov rax,rsi
           .break
        .endif
    .endf
    .return .if !rax

    mov eax,[rdx]
    .if al == 'r'
        mov r9d,_IOREAD
        mov edx,O_RDONLY
    .elseif al == 'w'
        mov r9d,_IOWRT
        mov edx,O_WRONLY or O_CREAT or O_TRUNC
    .else
        .return 0
    .endif
    .if ah == 't'
        or  edx,O_TEXT
    .elseif ah == 'b'
        or  edx,O_BINARY
    .endif

    mov [rsi]._flag,r9d

    .new SecurityAttributes:SECURITY_ATTRIBUTES = { SECURITY_ATTRIBUTES, NULL, TRUE }
    .new c:byte

    xor eax,eax
    xor ebx,ebx
    ;
    ; figure out binary/text mode
    ;
    .if !( edx & O_BINARY )
        or bl,FH_TEXT
    .endif
    ;
    ; decode the access flags
    ;
    mov eax,edx
    and eax,O_RDONLY or O_WRONLY or O_RDWR
    mov edi,GENERIC_READ        ; read access
    .if ( eax != O_RDONLY )
        mov edi,GENERIC_WRITE   ; write access
        .if ( eax != O_WRONLY )
            mov edi,GENERIC_READ or GENERIC_WRITE
            .if ( eax != O_RDWR )
                .return NULL
            .endif
        .endif
    .endif

    mov r8d,FILE_SHARE_READ or FILE_SHARE_WRITE
    ;
    ; decode open/create method flags
    ;
    mov eax,edx
    and eax,O_CREAT or O_EXCL or O_TRUNC
    .if eax == O_CREAT or O_TRUNC
        mov eax,CREATE_ALWAYS
    .elseif eax
        .return NULL
    .endif

    mov r10d,FILE_ATTRIBUTE_NORMAL
    .if ( edx & O_CREAT )
        mov r9d,CMASK
        .if !( r9d & _S_IWRITE )
            mov r10d,FILE_ATTRIBUTE_READONLY
        .endif
    .endif


    .return( rsi )

fopen endp

    end
