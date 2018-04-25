ifndef __ROBJECT_INC
__ROBJECT_INC equ <>
.pragma list(push, 0)
.pragma pack(push, 1)

ROBJECT	    STRUC
flags	    dw ?
count	    db ?
index	    db ?
x	    db ?
y	    db ?
col	    db ?
row	    db ?
ROBJECT	    ENDS

IDDOBJ	    STRUC
memsize	    dw ?
dialog	    ROBJECT <>
IDDOBJ	    ENDS

.pragma pack(pop)

LPROBJECT   typedef ptr ROBJECT
LPIDDOBJ    typedef ptr IDDOBJ

.pragma list(pop)
endif
