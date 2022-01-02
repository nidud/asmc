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
