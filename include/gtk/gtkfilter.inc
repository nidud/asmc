ifndef __GTK_FILTER_H__
define __GTK_FILTER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc

.enum GtkFilterMatch {
  GTK_FILTER_MATCH_SOME = 0,
  GTK_FILTER_MATCH_NONE,
  GTK_FILTER_MATCH_ALL
}


.enum GtkFilterChange {
  GTK_FILTER_CHANGE_DIFFERENT = 0,
  GTK_FILTER_CHANGE_LESS_STRICT,
  GTK_FILTER_CHANGE_MORE_STRICT,
}

define GTK_TYPE_FILTER <gtk_filter_get_type ()>


_GtkFilterClass         struct
parent_class            GObjectClass <>
match                   proc :ptr, :gpointer
get_strictness          proc :ptr
_gtk_reserved1          proc
_gtk_reserved2          proc
_gtk_reserved3          proc
_gtk_reserved4          proc
_gtk_reserved5          proc
_gtk_reserved6          proc
_gtk_reserved7          proc
_gtk_reserved8          proc
_GtkFilterClass         ends

gtk_filter_match proto :ptr, :gpointer
gtk_filter_get_strictness proto :ptr
gtk_filter_changed proto :ptr, :GtkFilterChange

endif
