ifndef __GTK_ACCEL_MAP_H__
__GTK_ACCEL_MAP_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gtk/gtkaccelgroup.inc

G_BEGIN_DECLS

GTK_TYPE_ACCEL_MAP equ <gtk_accel_map_get_type>
GTK_ACCEL_MAP macro accel_map
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((accel_map), GTK_TYPE_ACCEL_MAP, GtkAccelMap))>
	endm
GTK_ACCEL_MAP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ACCEL_MAP, GtkAccelMapClass))>
	endm
GTK_IS_ACCEL_MAP macro accel_map
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((accel_map), GTK_TYPE_ACCEL_MAP))>
	endm
GTK_IS_ACCEL_MAP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ACCEL_MAP))>
	endm
GTK_ACCEL_MAP_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ACCEL_MAP, GtkAccelMapClass))>
	endm

CALLBACKC(GtkAccelMapForeach, :gpointer, :ptr gchar, :guint, :GdkModifierType, :gboolean)

;void
gtk_accel_map_add_entry proto __cdecl \
	    accel_path: ptr gchar,
	     accel_key: guint,
	    accel_mods: GdkModifierType

;gboolean
gtk_accel_map_lookup_entry proto __cdecl \
	    accel_path: ptr gchar,
		   key: ptr GtkAccelKey

;gboolean
gtk_accel_map_change_entry proto __cdecl \
	    accel_path: ptr gchar,
	     accel_key: guint,
	    accel_mods: GdkModifierType,
	       replace: gboolean

;void
gtk_accel_map_load proto __cdecl \
	     file_name: ptr gchar

;void
gtk_accel_map_save proto __cdecl \
	     file_name: ptr gchar

;void
gtk_accel_map_foreach proto __cdecl \
		  data: gpointer,
	  foreach_func: GtkAccelMapForeach

;void
gtk_accel_map_load_fd proto __cdecl \
		    fd: gint

;void
gtk_accel_map_load_scanner proto __cdecl \
	       scanner: ptr GScanner

;void
gtk_accel_map_save_fd proto __cdecl \
		    fd: gint


;void
gtk_accel_map_lock_path proto __cdecl \
	    accel_path: ptr gchar

;void
gtk_accel_map_unlock_path proto __cdecl \
	    accel_path: ptr gchar


;void
gtk_accel_map_add_filter proto __cdecl \
	filter_pattern: ptr gchar

;void
gtk_accel_map_foreach_unfiltered proto __cdecl \
		  data: gpointer,
	  foreach_func: GtkAccelMapForeach


;GType
gtk_accel_map_get_type proto __cdecl
;GtkAccelMap
gtk_accel_map_get proto __cdecl


G_END_DECLS

endif
