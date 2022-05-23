ifndef __GDK_PAINTABLE_H__
define __GDK_PAINTABLE_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

define GDK_TYPE_PAINTABLE               <gdk_paintable_get_type>

.enum GdkPaintableFlags {
  GDK_PAINTABLE_STATIC_SIZE = 1 shl 0,
  GDK_PAINTABLE_STATIC_CONTENTS = 1 shl 1
}

_GdkPaintableInterface  struct
g_iface                 GTypeInterface <>
snapshot                proc :ptr, :ptr, :real8, :real8
get_current_image       proc :ptr
get_flags               proc :ptr
get_intrinsic_width     proc :ptr
get_intrinsic_height    proc :ptr
get_intrinsic_aspect_ratio proc :ptr
_GdkPaintableInterface  ends
GdkPaintableInterface   typedef _GdkPaintableInterface

gdk_paintable_snapshot proto :ptr, :ptr, :real8, :real8
gdk_paintable_get_current_image proto :ptr
gdk_paintable_get_flags proto :ptr
gdk_paintable_get_intrinsic_width proto :ptr
gdk_paintable_get_intrinsic_height proto :ptr
gdk_paintable_get_intrinsic_aspect_ratio proto :ptr
gdk_paintable_compute_concrete_size proto :ptr, :real8, :real8, :real8, :real8, :ptr, :ptr
gdk_paintable_invalidate_contents proto :ptr
gdk_paintable_invalidate_size proto :ptr
gdk_paintable_new_empty proto :sdword, :sdword

endif
