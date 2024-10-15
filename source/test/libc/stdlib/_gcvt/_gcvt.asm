; _GCVT.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/gcvt?view=msvc-170
;

include stdio.inc
include stdlib.inc
include tchar.inc
ifdef __PE__
define INFO <"MSVCRT">
elseifdef _WIN64
define INFO <"LIBC64">
else
define INFO <"LIBC32">
endif

.code

_tmain proc argc:int_t, argv:array_t

   .new buffer[_CVTBUFSIZE]:char_t
   .new value:double_t = -1234567890.123

    printf( INFO " converted by _gcvt(value,12,buffer):\n" )

    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )
ifdef __SSE__
    movsd xmm0,value
    mulsd xmm0,10.0
    movsd value,xmm0

    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )

    movsd xmm0,value
    mulsd xmm0,10.0
    movsd value,xmm0

    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )

    movsd xmm0,value
    mulsd xmm0,10.0
    movsd value,xmm0

    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )

    ;printf( "\n" );
    movsd xmm0,-12.34567890123
    movsd value,xmm0

    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )

    movsd xmm0,value
    divsd xmm0,10.0
    movsd value,xmm0
    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )

    movsd xmm0,value
    divsd xmm0,10.0
    movsd value,xmm0
    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )

    movsd xmm0,value
    divsd xmm0,10.0
    movsd value,xmm0
    _gcvt( value, 12, &buffer )
    printf( "buffer: '%s' (%d chars)\n", &buffer, strlen(&buffer) )

endif
   .return(0)

_tmain endp

    end _tstart
