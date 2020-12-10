
include stdio.inc

; Add startup module: adjust the path

.pragma comment(linker,"/DEFAULTLIB:\VS19\VC\Tools\MSVC\14.28.29333\lib\x64\libcmtd.lib")

console proto :string_t

    .code

main proc argc:int_t, argv:array_t, environment:ptr string_t
  local string:string_t,
        array[2]:string_t

  ; register arguments is not saved to the stack unless used

    mov eax,argc
    mov rax,argv
    mov rax,environment

  ; load some values to locals

    mov string,&@CStr( "hello world\n" )
    mov array[0],&@CStr( "String 1" )
    mov array[8],&@CStr( "String 2" )

  ; jump to next file

    .return console( string )

main endp

    end
