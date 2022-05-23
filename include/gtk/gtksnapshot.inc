ifndef __GTK_SNAPSHOT_H__
define __GTK_SNAPSHOT_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gsk/gsk.inc
include gtk/gtktypes.inc

;GtkSnapshotClass        typedef _GtkSnapshotClass

define GTK_TYPE_SNAPSHOT <gtk_snapshot_get_type>
GTK_SNAPSHOT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SNAPSHOT, GtkSnapshot))>
  endm
GTK_IS_SNAPSHOT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SNAPSHOT))>
  endm

gtk_snapshot_get_type proto
gtk_snapshot_new proto
gtk_snapshot_free_to_node proto :ptr
gtk_snapshot_free_to_paintable proto :ptr, :ptr
gtk_snapshot_to_node proto :ptr
gtk_snapshot_to_paintable proto :ptr, :ptr

gtk_snapshot_push_debug proto :ptr, :ptr, :vararg
gtk_snapshot_push_opacity proto :ptr, :real8
gtk_snapshot_push_blur proto :ptr, :real8
gtk_snapshot_push_color_matrix proto :ptr, :ptr, :ptr
gtk_snapshot_push_repeat proto :ptr, :ptr, :ptr
gtk_snapshot_push_clip proto :ptr, :ptr
gtk_snapshot_push_rounded_clip proto :ptr, :ptr
gtk_snapshot_push_shadow proto :ptr, :ptr, :gsize
gtk_snapshot_push_blend proto :ptr, :GskBlendMode
gtk_snapshot_push_cross_fade proto :ptr, :real8
gtk_snapshot_push_gl_shader proto :ptr, :ptr, :ptr, :ptr
gtk_snapshot_gl_shader_pop_texture proto :ptr
gtk_snapshot_pop proto :ptr
gtk_snapshot_save proto :ptr
gtk_snapshot_restore proto :ptr
gtk_snapshot_transform proto :ptr, :ptr
gtk_snapshot_transform_matrix proto :ptr, :ptr
gtk_snapshot_translate proto :ptr, :ptr
gtk_snapshot_translate_3d proto :ptr, :ptr
gtk_snapshot_rotate proto :ptr, :real4
gtk_snapshot_rotate_3d proto :ptr, :real4, :ptr
gtk_snapshot_scale proto :ptr, :real4, :real4
gtk_snapshot_scale_3d proto :ptr, :real4, :real4, :real4
gtk_snapshot_perspective proto :ptr, :real4
gtk_snapshot_append_node proto :ptr, :ptr
gtk_snapshot_append_cairo proto :ptr, :ptr
gtk_snapshot_append_texture proto :ptr, :ptr, :ptr
gtk_snapshot_append_color proto :ptr, :ptr, :ptr
gtk_snapshot_append_linear_gradient proto :ptr, :ptr, :ptr, :ptr, :ptr, :gsize
gtk_snapshot_append_repeating_linear_gradient proto :ptr, :ptr, :ptr, :ptr, :ptr, :gsize
gtk_snapshot_append_radial_gradient proto :ptr, :ptr, :ptr, :real4, :real4, :real4, :real4, :ptr, :gsize
gtk_snapshot_append_repeating_radial_gradient proto :ptr, :ptr, :ptr, :real4, :real4, :real4, :real4, :ptr, :gsize
gtk_snapshot_append_conic_gradient proto :ptr, :ptr, :ptr, :real4, :ptr, :gsize
gtk_snapshot_append_border proto :ptr, :ptr, :real4, :real4;:border_width, :border_color
gtk_snapshot_append_inset_shadow proto :ptr, :ptr, :ptr, :real4, :real4, :real4, :real4
gtk_snapshot_append_outset_shadow proto :ptr, :ptr, :ptr, :real4, :real4, :real4, :real4

gtk_snapshot_append_layout proto :ptr, :ptr, :ptr

gtk_snapshot_render_background proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_snapshot_render_frame proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_snapshot_render_focus proto :ptr, :ptr, :real8, :real8, :real8, :real8
gtk_snapshot_render_layout proto :ptr, :ptr, :real8, :real8, :ptr
gtk_snapshot_render_insertion_cursor proto :ptr, :ptr, :real8, :real8, :ptr, :sdword, :PangoDirection

endif
