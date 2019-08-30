.pragma list(push, 0)
ifndef __QUEUE_INC
__QUEUE_INC equ <>

;; interface for queue.asm
;; This file is included by asmc.inc

qnode	struct
next	ptr_t ?
union
 elmt	ptr_t ?
 sym	asym_t ?
ends
qnode	ends
qnode_t typedef ptr qnode

qdesc	struct
head	ptr_t ?
tail	ptr_t ?
qdesc	ends
qdesc_t typedef ptr qdesc

QEnqueue proto fastcall :qdesc_t, :ptr
QAddItem proto fastcall :qdesc_t, :ptr

endif
.pragma list(pop)
