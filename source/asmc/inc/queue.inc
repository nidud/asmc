; QUEUE.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; interface for queue.asm
; This file is included by asmc.inc
;
ifndef __QUEUE_INC
define __QUEUE_INC

qnode_t typedef ptr qnode
qdesc_t typedef ptr qdesc

qnode	struct
next	qnode_t ?
union
 elmt	qnode_t ?
 sym	asym_t ?
ends
qnode	ends

qdesc	struct
head	qdesc_t ?
tail	qdesc_t ?
qdesc	ends

QEnqueue proto fastcall :qdesc_t, :ptr
QAddItem proto fastcall :qdesc_t, :ptr

endif
