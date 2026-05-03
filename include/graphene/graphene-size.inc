ifndef __GRAPHENE_SIZE_H__
define __GRAPHENE_SIZE_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc

GRAPHENE_SIZE_INIT macro _w,_h
  exitm<{ _w, _h }>
  endm

define GRAPHENE_SIZE_INIT_ZERO  <GRAPHENE_SIZE_INIT (0.0, 0.0)>

graphene_size_t         STRUC
width                   real4 ?
height                  real4 ?
graphene_size_t         ENDS

graphene_size_alloc proto
graphene_size_free proto :ptr
graphene_size_init proto :ptr, :real4, :real4
graphene_size_init_from_size proto :ptr, :ptr
graphene_size_equal proto :ptr, :ptr

graphene_size_scale proto :ptr, :real4, :ptr
graphene_size_interpolate proto :ptr, :ptr, :real8, :ptr

graphene_size_zero proto

endif
