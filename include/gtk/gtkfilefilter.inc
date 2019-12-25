ifndef __GTK_FILE_FILTER_H__
__GTK_FILE_FILTER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

G_BEGIN_DECLS

GTK_TYPE_FILE_FILTER equ <gtk_file_filter_get_type>
GTK_FILE_FILTER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_FILE_FILTER, GtkFileFilter))>
	endm
GTK_IS_FILE_FILTER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_FILE_FILTER))>
	endm

.enum GtkFileFilterFlags {
  GTK_FILE_FILTER_FILENAME     = 1 shl 0,
  GTK_FILE_FILTER_URI	       = 1 shl 1,
  GTK_FILE_FILTER_DISPLAY_NAME = 1 shl 2,
  GTK_FILE_FILTER_MIME_TYPE    = 1 shl 3
}

CALLBACKC(GtkFileFilterFunc, :ptr GtkFileFilterInfo, :gpointer)

GtkFileFilterInfo	STRUC
contains		GtkFileFilterFlags ?
filename		string_t ?
uri			string_t ?
display_name		string_t ?
mime_type		string_t ?
GtkFileFilterInfo	ENDS

;GType
gtk_file_filter_get_type proto __cdecl

;GtkFileFilter
gtk_file_filter_new proto __cdecl
;void
gtk_file_filter_set_name proto __cdecl \
		filter: ptr GtkFileFilter,
		  name: ptr gchar

;const
gtk_file_filter_get_name proto __cdecl \
		filter: ptr GtkFileFilter

;void
gtk_file_filter_add_mime_type proto __cdecl \
		filter: ptr GtkFileFilter,
	     mime_type: ptr gchar

;void
gtk_file_filter_add_pattern proto __cdecl \
		filter: ptr GtkFileFilter,
	       pattern: ptr gchar

;void
gtk_file_filter_add_pixbuf_formats proto __cdecl \
		filter: ptr GtkFileFilter

;void
gtk_file_filter_add_custom proto __cdecl \
		filter: ptr GtkFileFilter,
		needed: GtkFileFilterFlags,
		  func: GtkFileFilterFunc,
		  data: gpointer,
		notify: GDestroyNotify

;GtkFileFilterFlags
gtk_file_filter_get_needed proto __cdecl \
		filter: ptr GtkFileFilter

;gboolean
gtk_file_filter_filter proto __cdecl \
		filter: ptr GtkFileFilter,
	   filter_info: ptr GtkFileFilterInfo

G_END_DECLS

endif
