ifndef __GRAPHENE_EULER_H__
define __GRAPHENE_EULER_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-vec3.inc

.enum graphene_euler_order_t {
  GRAPHENE_EULER_ORDER_DEFAULT = -1,
  GRAPHENE_EULER_ORDER_XYZ = 0,
  GRAPHENE_EULER_ORDER_YZX,
  GRAPHENE_EULER_ORDER_ZXY,
  GRAPHENE_EULER_ORDER_XZY,
  GRAPHENE_EULER_ORDER_YXZ,
  GRAPHENE_EULER_ORDER_ZYX,
  GRAPHENE_EULER_ORDER_SXYZ,
  GRAPHENE_EULER_ORDER_SXYX,
  GRAPHENE_EULER_ORDER_SXZY,
  GRAPHENE_EULER_ORDER_SXZX,
  GRAPHENE_EULER_ORDER_SYZX,
  GRAPHENE_EULER_ORDER_SYZY,
  GRAPHENE_EULER_ORDER_SYXZ,
  GRAPHENE_EULER_ORDER_SYXY,
  GRAPHENE_EULER_ORDER_SZXY,
  GRAPHENE_EULER_ORDER_SZXZ,
  GRAPHENE_EULER_ORDER_SZYX,
  GRAPHENE_EULER_ORDER_SZYZ,
  GRAPHENE_EULER_ORDER_RZYX,
  GRAPHENE_EULER_ORDER_RXYX,
  GRAPHENE_EULER_ORDER_RYZX,
  GRAPHENE_EULER_ORDER_RXZX,
  GRAPHENE_EULER_ORDER_RXZY,
  GRAPHENE_EULER_ORDER_RYZY,
  GRAPHENE_EULER_ORDER_RZXY,
  GRAPHENE_EULER_ORDER_RYXY,
  GRAPHENE_EULER_ORDER_RYXZ,
  GRAPHENE_EULER_ORDER_RZXZ,
  GRAPHENE_EULER_ORDER_RXYZ,
  GRAPHENE_EULER_ORDER_RZYZ
}


graphene_euler_t        STRUC
angles                  graphene_vec3_t <>
order                   graphene_euler_order_t ?
graphene_euler_t        ENDS

graphene_euler_alloc proto
graphene_euler_free proto :ptr

graphene_euler_init proto :ptr, :real4, :real4, :real4
graphene_euler_init_with_order proto :ptr, :real4, :real4, :real4, :graphene_euler_order_t
graphene_euler_init_from_matrix proto :ptr, :ptr, :graphene_euler_order_t
graphene_euler_init_from_quaternion proto :ptr, :ptr, :graphene_euler_order_t
graphene_euler_init_from_vec3 proto :ptr, :ptr, :graphene_euler_order_t
graphene_euler_init_from_euler proto :ptr, :ptr
graphene_euler_init_from_radians proto :ptr, :real4, :real4, :real4, :graphene_euler_order_t

graphene_euler_equal proto :ptr, :ptr

graphene_euler_get_x proto :ptr
graphene_euler_get_y proto :ptr
graphene_euler_get_z proto :ptr
graphene_euler_get_order proto :ptr

graphene_euler_get_alpha proto :ptr
graphene_euler_get_beta proto :ptr
graphene_euler_get_gamma proto :ptr

graphene_euler_to_vec3 proto :ptr, :ptr
graphene_euler_to_matrix proto :ptr, :ptr
graphene_euler_to_quaternion proto :ptr, :ptr

graphene_euler_reorder proto :ptr, :graphene_euler_order_t, :ptr

endif

