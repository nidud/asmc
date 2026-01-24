; PLT.ASM--
;
; Linking to shared libraries using -fplt
;

include stdio.inc

define got_stdin  <__acrt_iob_func(0)>
define got_stdout <__acrt_iob_func(1)>
define got_stderr <__acrt_iob_func(2)>

.code

main proc
    fprintf(got_stdout,
        "Linking to %d-bit shared libraries: Asmc %d.%d\n",
        size_t shl 3, __ASMC__ / 100, __ASMC__ mod 100)
    xor eax,eax
    ret
    endp

    end
