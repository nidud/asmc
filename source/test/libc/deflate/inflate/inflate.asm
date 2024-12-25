; INFLATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include deflate.inc

.code

main proc

   .new lz:ZIPLOCAL
   .new fp:LPFILE = fopen("deflated", "wb")
   .new rc:int_t = deflate(__FILE__, fp, &lz)

    printf("deflate(): %d\n", eax)
    fclose(fp)
    .if ( rc > 0 )

        mov fp,fopen("deflated", "rb")
        mov rc,inflate("inflated", fp, &lz)
        printf("inflate(): %d\n", eax)
        fclose(fp)
    .endif
    ret

main endp

    end
