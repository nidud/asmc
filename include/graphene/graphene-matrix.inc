ifndef __GRAPHENE_MATRIX_H__
define __GRAPHENE_MATRIX_H__

include graphene/graphene-types.inc

graphene_matrix_t       STRUC
value                   real4 4 dup(?)
graphene_matrix_t       ENDS

graphene_matrix_alloc proto
graphene_matrix_free proto :ptr

graphene_matrix_init_identity proto :ptr
graphene_matrix_init_from_float proto :ptr, :ptr
graphene_matrix_init_from_vec4 proto :ptr, :ptr, :ptr, :ptr, :ptr
graphene_matrix_init_from_matrix proto :ptr, :ptr
graphene_matrix_init_perspective proto :ptr, :real4, :real4, :real4, :real4
graphene_matrix_init_ortho proto :ptr, :real4, :real4, :real4, :real4, :real4, :real4
graphene_matrix_init_look_at proto :ptr, :ptr, :ptr, :ptr
graphene_matrix_init_frustum proto :ptr, :real4, :real4, :real4, :real4, :real4, :real4
graphene_matrix_init_scale proto :ptr, :real4, :real4, :real4
graphene_matrix_init_translate proto :ptr, :ptr
graphene_matrix_init_rotate proto :ptr, :real4, :ptr
graphene_matrix_init_skew proto :ptr, :real4, :real4
graphene_matrix_init_from_2d proto :ptr, :real8, :real8, :real8, :real8, :real8, :real8

graphene_matrix_is_identity proto :ptr
graphene_matrix_is_2d proto :ptr
graphene_matrix_is_backface_visible proto :ptr
graphene_matrix_is_singular proto :ptr

graphene_matrix_to_float proto :ptr, :ptr
graphene_matrix_to_2d proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr


graphene_matrix_get_row proto :ptr, :dword, :ptr
graphene_matrix_get_value proto :ptr, :dword, :dword

graphene_matrix_multiply proto :ptr, :ptr, :ptr
graphene_matrix_determinant proto :ptr

graphene_matrix_transform_vec4 proto :ptr, :ptr, :ptr
graphene_matrix_transform_vec3 proto :ptr, :ptr, :ptr
graphene_matrix_transform_point proto :ptr, :ptr, :ptr
graphene_matrix_transform_point3d proto :ptr, :ptr, :ptr
graphene_matrix_transform_rect proto :ptr, :ptr, :ptr
graphene_matrix_transform_bounds proto :ptr, :ptr, :ptr
graphene_matrix_transform_sphere proto :ptr, :ptr, :ptr
graphene_matrix_transform_box proto :ptr, :ptr, :ptr
graphene_matrix_transform_ray proto :ptr, :ptr, :ptr

graphene_matrix_project_point proto :ptr, :ptr, :ptr
graphene_matrix_project_rect_bounds proto :ptr, :ptr, :ptr
graphene_matrix_project_rect proto :ptr, :ptr, :ptr
graphene_matrix_untransform_point proto :ptr, :ptr, :ptr, :ptr
graphene_matrix_untransform_bounds proto :ptr, :ptr, :ptr, :ptr
graphene_matrix_unproject_point3d proto :ptr, :ptr, :ptr, :ptr

graphene_matrix_translate proto :ptr, :ptr
graphene_matrix_rotate proto :ptr, :real4, :ptr
graphene_matrix_rotate_x proto :ptr, :real4
graphene_matrix_rotate_y proto :ptr, :real4
graphene_matrix_rotate_z proto :ptr, :real4
graphene_matrix_rotate_quaternion proto :ptr, :ptr
graphene_matrix_rotate_euler proto :ptr, :ptr
graphene_matrix_scale proto :ptr, :real4, :real4, :real4
graphene_matrix_skew_xy proto :ptr, :real4
graphene_matrix_skew_xz proto :ptr, :real4
graphene_matrix_skew_yz proto :ptr, :real4

graphene_matrix_transpose proto :ptr, :ptr
graphene_matrix_inverse proto :ptr, :ptr
graphene_matrix_perspective proto :ptr, :real4, :ptr
graphene_matrix_normalize proto :ptr, :ptr

graphene_matrix_get_x_translation proto :ptr
graphene_matrix_get_y_translation proto :ptr
graphene_matrix_get_z_translation proto :ptr

graphene_matrix_get_x_scale proto :ptr
graphene_matrix_get_y_scale proto :ptr
graphene_matrix_get_z_scale proto :ptr

graphene_matrix_interpolate proto :ptr, :ptr, :real8, :ptr

graphene_matrix_near proto :ptr, :ptr, :real4
graphene_matrix_equal proto :ptr, :ptr
graphene_matrix_equal_fast proto :ptr, :ptr

graphene_matrix_print proto :ptr

graphene_matrix_decompose proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr

endif

