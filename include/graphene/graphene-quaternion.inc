ifndef __GRAPHENE_RAY_H__
define __GRAPHENE_RAY_H__

if  not defined(GRAPHENE_H_INSIDE) and not defined(GRAPHENE_COMPILATION)
.err <"Only graphene.h can be included directly.">
endif

include graphene/graphene-types.inc
include graphene/graphene-vec4.inc

graphene_quaternion_t   STRUC
x                       real4 ?
y                       real4 ?
z                       real4 ?
w                       real4 ?
graphene_quaternion_t   ENDS

graphene_quaternion_alloc proto
graphene_quaternion_free proto :ptr

graphene_quaternion_init proto :ptr, :real4, :real4, :real4, :real4
graphene_quaternion_init_identity proto :ptr
graphene_quaternion_init_from_quaternion proto :ptr, :ptr
graphene_quaternion_init_from_vec4 proto :ptr, :ptr
graphene_quaternion_init_from_matrix proto :ptr, :ptr
graphene_quaternion_init_from_angles proto :ptr, :real4, :real4, :real4
graphene_quaternion_init_from_radians proto :ptr, :real4, :real4, :real4
graphene_quaternion_init_from_angle_vec3 proto :ptr, :real4, :ptr
graphene_quaternion_init_from_euler proto :ptr, :ptr

graphene_quaternion_to_vec4 proto :ptr, :ptr
graphene_quaternion_to_matrix proto :ptr, :ptr
graphene_quaternion_to_angles proto :ptr, :ptr, :ptr, :ptr
graphene_quaternion_to_radians proto :ptr, :ptr, :ptr, :ptr
graphene_quaternion_to_angle_vec3 proto :ptr, :ptr, :ptr

graphene_quaternion_equal proto :ptr, :ptr
graphene_quaternion_dot proto :ptr, :ptr
graphene_quaternion_invert proto :ptr, :ptr
graphene_quaternion_normalize proto :ptr, :ptr
graphene_quaternion_slerp proto :ptr, :ptr, :real4, :ptr
graphene_quaternion_multiply proto :ptr, :ptr, :ptr
graphene_quaternion_scale proto :ptr, :real4, :ptr
graphene_quaternion_add proto :ptr, :ptr, :ptr

endif

