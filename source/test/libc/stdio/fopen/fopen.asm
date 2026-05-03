
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
    .return(0)

main endp

    end

