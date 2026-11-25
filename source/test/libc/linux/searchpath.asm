
include stdlib.inc
include processenv.inc
include iostream

.code

main proc argc:int_t, argv:array_t
    .new buffer[MAX_PATH]:char_t
    .new fullPath:string_t = &buffer
    .new filePart:string_t = nullptr
    .new len:dword
    .if ( argc < 2 )
        cout << "Usage: searchpath <file>" << endl
        exit(0)
    .endif
    ldr rbx,argv
    mov len,SearchPathA(
        nullptr,        ; Use default system search path
        [rbx+string_t], ; File to find
        nullptr,        ; No extra extension needed
        MAX_PATH,
        fullPath,
        &filePart
    )
    .if ( len > 0 && len < MAX_PATH )
        cout << "Full path: " << fullPath << endl
        .if ( filePart )
            cout << "File name: " << filePart << endl
        .endif
    .endif
    .return( 0 )
    endp

    end
