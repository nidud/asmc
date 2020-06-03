ifndef _GDIPLUSBASE_H
_GDIPLUSBASE_H equ <>

GdipSetStatus macro this
    test    eax,eax
    cmovz   eax,this.lastResult
    mov     this.lastResult,eax
    exitm   <>
    endm

endif


