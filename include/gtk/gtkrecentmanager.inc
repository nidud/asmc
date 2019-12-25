ifndef __GTK_RECENT_MANAGER_H__
__GTK_RECENT_MANAGER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

;include gdk-pixbuf/gdk-pixbuf.inc
include gdk/gdk.inc
include time.inc

G_BEGIN_DECLS

GTK_TYPE_RECENT_INFO equ <gtk_recent_info_get_type>

GTK_TYPE_RECENT_MANAGER equ (gtk_recent_manager_get_type ())
GTK_RECENT_MANAGER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_RECENT_MANAGER, GtkRecentManager))>
	endm
GTK_IS_RECENT_MANAGER macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_RECENT_MANAGER))>
	endm
GTK_RECENT_MANAGER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_RECENT_MANAGER, GtkRecentManagerClass))>
	endm
GTK_IS_RECENT_MANAGER_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_RECENT_MANAGER))>
	endm
GTK_RECENT_MANAGER_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_RECENT_MANAGER, GtkRecentManagerClass))>
	endm

GtkRecentData		STRUC
display_name		string_t ?
description		string_t ?
mime_type		string_t ?
app_name		string_t ?
app_exec		string_t ?
groups			string_t ?
is_private		gboolean ?
GtkRecentData		ENDS

GtkRecentManager	STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkRecentManager	ENDS

GtkRecentManagerClass	STRUC
parent_class		GObjectClass <>
changed			proc :ptr GtkRecentManager
_gtk_recent1		proc
_gtk_recent2		proc
_gtk_recent3		proc
_gtk_recent4		proc
GtkRecentManagerClass	ENDS

.enum GtkRecentManagerError {
  GTK_RECENT_MANAGER_ERROR_NOT_FOUND,
  GTK_RECENT_MANAGER_ERROR_INVALID_URI,
  GTK_RECENT_MANAGER_ERROR_INVALID_ENCODING,
  GTK_RECENT_MANAGER_ERROR_NOT_REGISTERED,
  GTK_RECENT_MANAGER_ERROR_READ,
  GTK_RECENT_MANAGER_ERROR_WRITE,
  GTK_RECENT_MANAGER_ERROR_UNKNOWN
}

GTK_RECENT_MANAGER_ERROR equ <gtk_recent_manager_error_quark>
;GQuark
gtk_recent_manager_error_quark proto __cdecl


;GType
gtk_recent_manager_get_type proto __cdecl

;GtkRecentManager
gtk_recent_manager_new proto __cdecl
;GtkRecentManager
gtk_recent_manager_get_default proto __cdecl

;gboolean
gtk_recent_manager_add_item proto __cdecl \
	       manager: ptr GtkRecentManager,
		   uri: ptr gchar

;gboolean
gtk_recent_manager_add_full proto __cdecl \
	       manager: ptr GtkRecentManager,
		   uri: ptr gchar,
	   recent_data: ptr GtkRecentData

;gboolean
gtk_recent_manager_remove_item proto __cdecl \
	       manager: ptr GtkRecentManager,
		   uri: ptr gchar,
		 error: ptr GError

;GtkRecentInfo
gtk_recent_manager_lookup_item proto __cdecl \
	       manager: ptr GtkRecentManager,
		   uri: ptr gchar,
		 error: ptr GError

;gboolean
gtk_recent_manager_has_item proto __cdecl \
	       manager: ptr GtkRecentManager,
		   uri: ptr gchar

;gboolean
gtk_recent_manager_move_item proto __cdecl \
	       manager: ptr GtkRecentManager,
		   uri: ptr gchar,
	       new_uri: ptr gchar,
		 error: ptr GError

;GList
gtk_recent_manager_get_items proto __cdecl \
	       manager: ptr GtkRecentManager

;gint
gtk_recent_manager_purge_items proto __cdecl \
	       manager: ptr GtkRecentManager,
		 error: ptr GError



;GType
gtk_recent_info_get_type proto __cdecl

;GtkRecentInfo
gtk_recent_info_ref proto __cdecl \
		  info: ptr GtkRecentInfo

;void
gtk_recent_info_unref proto __cdecl \
		  info: ptr GtkRecentInfo


;const
gtk_recent_info_get_uri proto __cdecl \
		  info: ptr GtkRecentInfo

;const
gtk_recent_info_get_display_name proto __cdecl \
		  info: ptr GtkRecentInfo

;const
gtk_recent_info_get_description proto __cdecl \
		  info: ptr GtkRecentInfo

;const
gtk_recent_info_get_mime_type proto __cdecl \
		  info: ptr GtkRecentInfo

;time_t
gtk_recent_info_get_added proto __cdecl \
		  info: ptr GtkRecentInfo

;time_t
gtk_recent_info_get_modified proto __cdecl \
		  info: ptr GtkRecentInfo

;time_t
gtk_recent_info_get_visited proto __cdecl \
		  info: ptr GtkRecentInfo

;gboolean
gtk_recent_info_get_private_hint proto __cdecl \
		  info: ptr GtkRecentInfo

;gboolean
gtk_recent_info_get_application_info proto __cdecl \
		  info: ptr GtkRecentInfo,
	      app_name: ptr gchar,
	      app_exec: ptr gchar,
		 count: ptr guint,
		 time_: ptr time_t

;GAppInfo
gtk_recent_info_create_app_info proto __cdecl \
		  info: ptr GtkRecentInfo,
	      app_name: ptr gchar,
		 error: ptr GError

;gchar
gtk_recent_info_get_applications proto __cdecl \
		  info: ptr GtkRecentInfo,
		length: ptr gsize

;gchar
gtk_recent_info_last_application proto __cdecl \
		  info: ptr GtkRecentInfo

;gboolean
gtk_recent_info_has_application proto __cdecl \
		  info: ptr GtkRecentInfo,
	      app_name: ptr gchar

;gchar
gtk_recent_info_get_groups proto __cdecl \
		  info: ptr GtkRecentInfo,
		length: ptr gsize

;gboolean
gtk_recent_info_has_group proto __cdecl \
		  info: ptr GtkRecentInfo,
	    group_name: ptr gchar

;GdkPixbuf
gtk_recent_info_get_icon proto __cdecl \
		  info: ptr GtkRecentInfo,
		  size: gint

;GIcon
gtk_recent_info_get_gicon proto __cdecl \
		  info: ptr GtkRecentInfo

;gchar
gtk_recent_info_get_short_name proto __cdecl \
		  info: ptr GtkRecentInfo

;gchar
gtk_recent_info_get_uri_display proto __cdecl \
		  info: ptr GtkRecentInfo

;gint
gtk_recent_info_get_age proto __cdecl \
		  info: ptr GtkRecentInfo

;gboolean
gtk_recent_info_is_local proto __cdecl \
		  info: ptr GtkRecentInfo

;gboolean
gtk_recent_info_exists proto __cdecl \
		  info: ptr GtkRecentInfo

;gboolean
gtk_recent_info_match proto __cdecl \
		info_a: ptr GtkRecentInfo,
		info_b: ptr GtkRecentInfo


;void
_gtk_recent_manager_sync proto __cdecl

G_END_DECLS

endif
