ifndef __GTK_SCROLLABLE_H__
define __GTK_SCROLLABLE_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc
include gtk/gtktypes.inc
include gtk/gtkborder.inc

define GTK_TYPE_SCROLLABLE <gtk_scrollable_get_type ()>
GTK_SCROLLABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj),     GTK_TYPE_SCROLLABLE, GtkScrollable))>
  endm
GTK_IS_SCROLLABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj),     GTK_TYPE_SCROLLABLE))>
  endm
GTK_SCROLLABLE_GET_IFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), GTK_TYPE_SCROLLABLE, GtkScrollableInterface))>
  endm

;GtkScrollable           typedef _GtkScrollable

_GtkScrollableInterface struct
base_iface              GTypeInterface <>
get_border              proc :ptr, :ptr
_GtkScrollableInterface ends
GtkScrollableInterface  typedef _GtkScrollableInterface

gtk_scrollable_get_type proto
gtk_scrollable_get_hadjustment proto :ptr
gtk_scrollable_set_hadjustment proto :ptr, :ptr
gtk_scrollable_get_vadjustment proto :ptr
gtk_scrollable_set_vadjustment proto :ptr, :ptr
gtk_scrollable_get_hscroll_policy proto :ptr
gtk_scrollable_set_hscroll_policy proto :ptr, :GtkScrollablePolicy
gtk_scrollable_get_vscroll_policy proto :ptr
gtk_scrollable_set_vscroll_policy proto :ptr, :GtkScrollablePolicy

gtk_scrollable_get_border proto :ptr, :ptr

endif
