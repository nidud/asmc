ifndef __GTK_RECENT_FILTER_H__
__GTK_RECENT_FILTER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc

G_BEGIN_DECLS

GTK_TYPE_RECENT_FILTER	equ <gtk_recent_filter_get_type>
GTK_RECENT_FILTER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RECENT_FILTER, GtkRecentFilter))>
	endm
GTK_IS_RECENT_FILTER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RECENT_FILTER))>
	endm

.enum GtkRecentFilterFlags {
  GTK_RECENT_FILTER_URI		 = 1 shl 0,
  GTK_RECENT_FILTER_DISPLAY_NAME = 1 shl 1,
  GTK_RECENT_FILTER_MIME_TYPE	 = 1 shl 2,
  GTK_RECENT_FILTER_APPLICATION	 = 1 shl 3,
  GTK_RECENT_FILTER_GROUP	 = 1 shl 4,
  GTK_RECENT_FILTER_AGE		 = 1 shl 5
}

CALLBACKC(GtkRecentFilterFunc, :ptr GtkRecentFilterInfo, :gpointer)

GtkRecentFilterInfo	STRUC
contains		GtkRecentFilterFlags ?
uri			string_t ?
display_name		string_t ?
mime_type		string_t ?
applications		string_t ?
groups			string_t ?
age			gint ?
GtkRecentFilterInfo	ENDS

;GType
gtk_recent_filter_get_type proto __cdecl

;GtkRecentFilter
gtk_recent_filter_new proto __cdecl
;void
gtk_recent_filter_set_name proto __cdecl \
		filter: ptr GtkRecentFilter,
		  name: ptr gchar

;const
gtk_recent_filter_get_name proto __cdecl \
		filter: ptr GtkRecentFilter


;void
gtk_recent_filter_add_mime_type proto __cdecl \
		filter: ptr GtkRecentFilter,
	     mime_type: ptr gchar

;void
gtk_recent_filter_add_pattern proto __cdecl \
		filter: ptr GtkRecentFilter,
	       pattern: ptr gchar

;void
gtk_recent_filter_add_pixbuf_formats proto __cdecl \
		filter: ptr GtkRecentFilter

;void
gtk_recent_filter_add_application proto __cdecl \
		filter: ptr GtkRecentFilter,
	   application: ptr gchar

;void
gtk_recent_filter_add_group proto __cdecl \
		filter: ptr GtkRecentFilter,
		_group: ptr gchar

;void
gtk_recent_filter_add_age proto __cdecl \
		filter: ptr GtkRecentFilter,
		  days: gint

;void
gtk_recent_filter_add_custom proto __cdecl \
		filter: ptr GtkRecentFilter,
		needed: GtkRecentFilterFlags,
		  func: GtkRecentFilterFunc,
		  data: gpointer,
	  data_destroy: GDestroyNotify


;GtkRecentFilterFlags
gtk_recent_filter_get_needed proto __cdecl \
		filter: ptr GtkRecentFilter

;gboolean
gtk_recent_filter_filter proto __cdecl \
		filter: ptr GtkRecentFilter,
	   filter_info: ptr GtkRecentFilterInfo

G_END_DECLS

endif
