.pragma list(push, 0)
ifndef __QUEUE_INC
__QUEUE_INC equ <>

; interface for queue.asm
; This file is included by asmc.inc

qnode	struct
next	ptr ?
union
 elmt	ptr ?
 sym	ptr asym ?
ends
qnode	ends
qnode_t typedef ptr qnode

qdesc	struct
head	ptr ?
tail	ptr ?
qdesc	ends
qdesc_t typedef ptr qdesc

QEnqueue proto fastcall :ptr qdesc, :ptr
QAddItem proto fastcall :ptr qdesc, :ptr

endif
.pragma list(pop)
