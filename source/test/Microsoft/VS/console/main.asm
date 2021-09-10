
include stdio.inc

; Add startup module

.pragma comment(linker,"/DEFAULTLIB:libcmtd.lib")

console proto :string_t

    .code

main proc argc:int_t, argv:array_t, environment:ptr string_t

  ; register arguments is not saved to the stack unless used

    mov eax,argc
    mov rax,argv
    mov rax,environment

  ; load some values to locals

  .new string:string_t = "hello world\n"
  .new array[2]:string_t = {"String 1", "String 2"}

  ; jump to next file

    .return console( string )

main endp

    end
