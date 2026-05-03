; VSCANF.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/vscanf-vwscanf?view=msvc-170
;
; This program uses the vscanf and vwscanf functions
; to read formatted input.
;

include stdio.inc
include stdarg.inc
include tchar.inc

.code

call_vscanf proc format:string_t, arglist:vararg
    vscanf(format, &arglist)
    ret
    endp

ifndef __UNIX__
call_vwscanf proc format:wstring_t, arglist:vararg
    vwscanf(format, &arglist)
    ret
    endp
endif

_tmain proc

   .new i:int_t
   .new result:int_t
   .new fp:real4
   .new c:char_t
   .new s[81]:char_t
   .new wc:wchar_t
   .new ws[81]:wchar_t

    printf( "input fields: %%d %%f %%c %%C %%80s %%80S\n" )
    mov result,call_vscanf( "%d %f %c %C %80s %80S", &i, &fp, &c, &wc, s, ws )
    printf( "The number of fields input is %d\n", result )
    printf( "The contents are: %d %f %c %C %s %S\n", i, fp, c, wc, s, ws)
ifndef __UNIX__
    mov result,call_vwscanf( L"%d %f %hc %lc %80S %80ls", &i, &fp, &c, &wc, s, ws )
    wprintf( L"The number of fields input is %d\n", result )
    wprintf( L"The contents are: %d %f %C %c %hs %s\n", i, fp, c, wc, s, ws)
endif
    .return( 0 )
    endp
    end _tstart
