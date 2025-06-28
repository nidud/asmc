; ABORT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

.data
 abortmsg char_t 'Abnormal program termination', 13, 10

.code

abort proc

    mov cx,sizeof(abortmsg)
    mov dx,offset abortmsg
    mov ah,0x40
    mov bx,2
    int 0x21
    exit( 3 )

abort endp

    end
