ifndef __GTK_SYMBOLIC_PAINTABLE_H__
define __GTK_SYMBOLIC_PAINTABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtktypes.inc

define GTK_TYPE_SYMBOLIC_PAINTABLE <gtk_symbolic_paintable_get_type ()>

_GtkSymbolicPaintableInterface struct
g_iface                 GTypeInterface <>
snapshot_symbolic       proc :ptr, :ptr, :real8, :real8, :ptr, :gsize
_GtkSymbolicPaintableInterface ends

gtk_symbolic_paintable_snapshot_symbolic proto :ptr, :ptr, :real8, :real8, :ptr, :gsize

endif
