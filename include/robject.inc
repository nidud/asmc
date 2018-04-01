ifndef __ROBJECT_INC
__ROBJECT_INC equ <>
.xlist

ROBJECT	    STRUC BYTE
flags	    dw ?
count	    db ?
index	    db ?
x	    db ?
y	    db ?
col	    db ?
row	    db ?
ROBJECT	    ENDS

IDDOBJ	    STRUC BYTE
memsize	    dw ?
dialog	    ROBJECT <>
IDDOBJ	    ENDS

LPROBJECT   typedef ptr ROBJECT
LPIDDOBJ    typedef ptr IDDOBJ

.list
endif
