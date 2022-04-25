; FOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include errno.inc

    .code

main proc

    .new fp:ptr FILE = fopen("fopen.txt", "w")
    .if ( fp != NULL )
        fprintf(fp, "fopen(\"fopen.txt\", \"w\") ._file: %d\n", [rax].FILE._file)
        fclose(fp)
        mov fp,fopen("fopen.txt", "a")
        .if ( fp != NULL )
            fprintf(fp, "appending\n")
            fclose(fp)
        .else
            perror("error fopen(a)")
        .endif
    .else
        perror("error fopen(w)")
    .endif
    ret

main endp

    end

