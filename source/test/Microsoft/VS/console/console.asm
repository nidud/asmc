
include stdio.inc

    .code

console proc string:string_t

  local result:int_t

    mov result,printf( string )
    sub result,12

    .return result

console endp

    end
