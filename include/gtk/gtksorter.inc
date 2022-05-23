ifndef __GTK_SORTER_H__
define __GTK_SORTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

.enum GtkSorterOrder {
  GTK_SORTER_ORDER_PARTIAL,
  GTK_SORTER_ORDER_NONE,
  GTK_SORTER_ORDER_TOTAL
}


.enum GtkSorterChange {
  GTK_SORTER_CHANGE_DIFFERENT,
  GTK_SORTER_CHANGE_INVERTED,
  GTK_SORTER_CHANGE_LESS_STRICT,
  GTK_SORTER_CHANGE_MORE_STRICT
}

define GTK_TYPE_SORTER <gtk_sorter_get_type>

_GtkSorterClass         struct
parent_class            GObjectClass <>
compare                 proc :ptr, :gpointer, :gpointer
get_order               proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_gtk_reserved5          proc
_gtk_reserved6          proc
_gtk_reserved7          proc
_gtk_reserved8          proc
_GtkSorterClass         ends

gtk_sorter_compare proto :ptr, :gpointer, :gpointer
gtk_sorter_get_order proto :ptr

gtk_sorter_changed proto :ptr, :GtkSorterChange

endif

