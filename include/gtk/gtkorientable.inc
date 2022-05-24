ifndef __GTK_ORIENTABLE_H__
define __GTK_ORIENTABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkwidget.inc

define GTK_TYPE_ORIENTABLE <gtk_orientable_get_type ()>
GTK_ORIENTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ORIENTABLE, GtkOrientable))>
  endm
GTK_IS_ORIENTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ORIENTABLE))>
  endm
GTK_ORIENTABLE_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_ORIENTABLE, GtkOrientableIface))>
  endm

;GtkOrientable           typedef _GtkOrientable

_GtkOrientableIface     struct
base_iface              GTypeInterface <>
_GtkOrientableIface     ends
GtkOrientableIface      typedef _GtkOrientableIface

gtk_orientable_get_type proto
gtk_orientable_set_orientation proto :ptr, :GtkOrientation
gtk_orientable_get_orientation proto :ptr

endif
