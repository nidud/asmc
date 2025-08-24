ifndef __GTK_RECENT_MANAGER_H__
define __GTK_RECENT_MANAGER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk-pixbuf/gdk-pixbuf.inc
include gdk/gdk.inc
include time.inc

define GTK_TYPE_RECENT_INFO	<gtk_recent_info_get_type ()>
define GTK_TYPE_RECENT_MANAGER	<gtk_recent_manager_get_type ()>
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

GtkRecentData		struct
display_name		ptr sbyte ?
description		ptr sbyte ?
mime_type		ptr sbyte ?
app_name		ptr sbyte ?
app_exec		ptr sbyte ?
groups			ptr sbyte ?
is_private		gboolean ?
GtkRecentData		ends

GtkRecentManager	struct
parent_instance		GObject <>
priv			ptr GtkRecentManagerPrivate ?
GtkRecentManager	ends

GtkRecentManagerClass	struct
parent_class		GObjectClass <>
changed			proc :ptr
_gtk_recent1		proc
_gtk_recent2		proc
_gtk_recent3		proc
_gtk_recent4		proc
GtkRecentManagerClass	ends

.enum GtkRecentManagerError {
  GTK_RECENT_MANAGER_ERROR_NOT_FOUND,
  GTK_RECENT_MANAGER_ERROR_INVALID_URI,
  GTK_RECENT_MANAGER_ERROR_INVALID_ENCODING,
  GTK_RECENT_MANAGER_ERROR_NOT_REGISTERED,
  GTK_RECENT_MANAGER_ERROR_READ,
  GTK_RECENT_MANAGER_ERROR_WRITE,
  GTK_RECENT_MANAGER_ERROR_UNKNOWN
}

define GTK_RECENT_MANAGER_ERROR <gtk_recent_manager_error_quark ()>
gtk_recent_manager_error_quark proto

gtk_recent_manager_get_type proto
gtk_recent_manager_new proto
gtk_recent_manager_get_default proto
gtk_recent_manager_add_item proto :ptr, :ptr
gtk_recent_manager_add_full proto :ptr, :ptr, :ptr
gtk_recent_manager_remove_item proto :ptr, :ptr, :ptr
gtk_recent_manager_lookup_item proto :ptr, :ptr, :ptr
gtk_recent_manager_has_item proto :ptr, :ptr
gtk_recent_manager_move_item proto :ptr, :ptr, :ptr, :ptr
gtk_recent_manager_get_items proto :ptr
gtk_recent_manager_purge_items proto :ptr, :ptr
gtk_recent_info_get_type proto
gtk_recent_info_ref proto :ptr
gtk_recent_info_unref proto :ptr
gtk_recent_info_get_uri proto :ptr
gtk_recent_info_get_display_name proto :ptr
gtk_recent_info_get_description proto :ptr
gtk_recent_info_get_mime_type proto :ptr
gtk_recent_info_get_added proto :ptr
gtk_recent_info_get_modified proto :ptr
gtk_recent_info_get_visited proto :ptr
gtk_recent_info_get_private_hint proto :ptr
gtk_recent_info_get_application_info proto :ptr, :ptr, :ptr, :ptr, :ptr
gtk_recent_info_create_app_info proto :ptr, :ptr, :ptr
gtk_recent_info_get_applications proto :ptr, :ptr
gtk_recent_info_last_application proto :ptr
gtk_recent_info_has_application proto :ptr, :ptr
gtk_recent_info_get_groups proto :ptr, :ptr
gtk_recent_info_has_group proto :ptr, :ptr
gtk_recent_info_get_gicon proto :ptr
gtk_recent_info_get_short_name proto :ptr
gtk_recent_info_get_uri_display proto :ptr
gtk_recent_info_get_age proto :ptr
gtk_recent_info_is_local proto :ptr
gtk_recent_info_exists proto :ptr
gtk_recent_info_match proto :ptr, :ptr

_gtk_recent_manager_sync proto

endif
