; DEFLATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include deflate.inc

.code

main proc

   .new fp:LPFILE = fopen("deflated", "wb")

    deflate(__FILE__, fp, NULL)
    printf("deflate(): %d\n", eax)
    fclose(fp)
    ret

main endp

    end
