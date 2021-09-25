ifndef _GDIPLUSBASE_H
define _GDIPLUSBASE_H

GdipSetStatus macro this
    test    eax,eax
    cmovz   eax,this.lastResult
    mov     this.lastResult,eax
    exitm   <>
    endm

endif


