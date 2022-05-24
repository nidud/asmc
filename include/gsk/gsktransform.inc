ifndef __GSK_TRANSFORM_H__
define __GSK_TRANSFORM_H__

if not defined (__GSK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gsk/gsk.h can be included directly.">
endif

include gsk/gskenums.inc
include gsk/gsktypes.inc

define GSK_TYPE_TRANSFORM <gsk_transform_get_type ()>

gsk_transform_get_type proto
gsk_transform_ref proto :ptr
gsk_transform_unref proto :ptr

gsk_transform_print proto :ptr, :ptr
gsk_transform_to_string proto :ptr
gsk_transform_parse proto :ptr, :ptr
gsk_transform_to_matrix proto :ptr, :ptr
gsk_transform_to_2d proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gsk_transform_to_2d_components proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
gsk_transform_to_affine proto :ptr, :ptr, :ptr, :ptr, :ptr
gsk_transform_to_translate proto :ptr, :ptr, :ptr

gsk_transform_get_category proto :ptr
gsk_transform_equal proto :ptr, :ptr

gsk_transform_new proto
gsk_transform_transform proto :ptr, :ptr
gsk_transform_invert proto :ptr
gsk_transform_matrix proto :ptr, :ptr
gsk_transform_translate proto :ptr, :ptr
gsk_transform_translate_3d proto :ptr, :ptr
gsk_transform_skew proto :ptr, :real4, :real4
gsk_transform_rotate proto :ptr, :real4
gsk_transform_rotate_3d proto :ptr, :real4, :ptr
gsk_transform_scale proto :ptr, :real4, :real4
gsk_transform_scale_3d proto :ptr, :real4, :real4, :real4
gsk_transform_perspective proto :ptr, :real4

gsk_transform_transform_bounds proto :ptr, :ptr, :ptr
gsk_transform_transform_point proto :ptr, :ptr, :ptr

endif
