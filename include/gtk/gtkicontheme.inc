ifndef __GTK_ICON_THEME_H__
__GTK_ICON_THEME_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk-pixbuf/gdk-pixbuf.inc
include gdk/gdk.inc
include gtk/gtkstylecontext.inc

G_BEGIN_DECLS

GTK_TYPE_ICON_INFO equ <gtk_icon_info_get_type>
GTK_ICON_INFO macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ICON_INFO, GtkIconInfo))>
	endm
GTK_ICON_INFO_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ICON_INFO, GtkIconInfoClass))>
	endm
GTK_IS_ICON_INFO macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ICON_INFO))>
	endm
GTK_IS_ICON_INFO_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ICON_INFO))>
	endm
GTK_ICON_INFO_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ICON_INFO, GtkIconInfoClass))>
	endm

GTK_TYPE_ICON_THEME equ <gtk_icon_theme_get_type>
GTK_ICON_THEME macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ICON_THEME, GtkIconTheme))>
	endm
GTK_ICON_THEME_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ICON_THEME, GtkIconThemeClass))>
	endm
GTK_IS_ICON_THEME macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ICON_THEME))>
	endm
GTK_IS_ICON_THEME_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ICON_THEME))>
	endm
GTK_ICON_THEME_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ICON_THEME, GtkIconThemeClass))>
	endm

GtkIconTheme		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkIconTheme		ENDS

GtkIconThemeClass	STRUC
parent_class		GObjectClass <>
changed			proc :ptr GtkIconTheme
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkIconThemeClass	ENDS

GTK_ICON_LOOKUP_NO_SVG	equ 1 << 0
GTK_ICON_LOOKUP_FORCE_SVG equ 1 << 1
GTK_ICON_LOOKUP_USE_BUILTIN equ 1 << 2
GTK_ICON_LOOKUP_GENERIC_FALLBACK equ 1 << 3
GTK_ICON_LOOKUP_FORCE_SIZE equ 1 << 4
GTK_ICON_LOOKUP_FORCE_REGULAR equ 1 << 5
GTK_ICON_LOOKUP_FORCE_SYMBOLIC equ 1 << 6
GTK_ICON_LOOKUP_DIR_LTR equ 1 << 7
GTK_ICON_LOOKUP_DIR_RTL equ 1 << 8

GTK_ICON_THEME_ERROR	equ <gtk_icon_theme_error_quark>

GTK_ICON_THEME_NOT_FOUND equ 0
GTK_ICON_THEME_FAILED	equ 1

;GQuark
gtk_icon_theme_error_quark proto __cdecl

;GType
gtk_icon_theme_get_type proto __cdecl

;GtkIconTheme
gtk_icon_theme_new proto __cdecl
;GtkIconTheme
gtk_icon_theme_get_default proto __cdecl
;GtkIconTheme
gtk_icon_theme_get_for_screen proto __cdecl \
		screen: ptr GdkScreen

;void
gtk_icon_theme_set_screen proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		screen: ptr GdkScreen


;void
gtk_icon_theme_set_search_path proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		path[]: ptr gchar,
	    n_elements: gint

;void
gtk_icon_theme_get_search_path proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		path[]: ptr gchar,
	    n_elements: ptr gint

;void
gtk_icon_theme_append_search_path proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		  path: ptr gchar

;void
gtk_icon_theme_prepend_search_path proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		  path: ptr gchar


;void
gtk_icon_theme_add_resource_path proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		  path: ptr gchar


;void
gtk_icon_theme_set_custom_theme proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	    theme_name: ptr gchar


;gboolean
gtk_icon_theme_has_icon proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	     icon_name: ptr gchar

;gint
gtk_icon_theme_get_icon_sizes proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	     icon_name: ptr gchar

;GtkIconInfo
gtk_icon_theme_lookup_icon proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	     icon_name: ptr gchar,
		  size: gint,
		 flags: GtkIconLookupFlags

;GtkIconInfo
gtk_icon_theme_lookup_icon_for_scale proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	     icon_name: ptr gchar,
		  size: gint,
		 scale: gint,
		 flags: GtkIconLookupFlags


;GtkIconInfo
gtk_icon_theme_choose_icon proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	  icon_names[]: ptr gchar,
		  size: gint,
		 flags: GtkIconLookupFlags

;GtkIconInfo
gtk_icon_theme_choose_icon_for_scale proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	  icon_names[]: ptr gchar,
		  size: gint,
		 scale: gint,
		 flags: GtkIconLookupFlags

;GdkPixbuf
gtk_icon_theme_load_icon proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	     icon_name: ptr gchar,
		  size: gint,
		 flags: GtkIconLookupFlags,
		 error: ptr GError

;GdkPixbuf
gtk_icon_theme_load_icon_for_scale proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	     icon_name: ptr gchar,
		  size: gint,
		 scale: gint,
		 flags: GtkIconLookupFlags,
		 error: ptr GError

;cairo_surface_t
gtk_icon_theme_load_surface proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	     icon_name: ptr gchar,
		  size: gint,
		 scale: gint,
	    for_window: ptr GdkWindow,
		 flags: GtkIconLookupFlags,
		 error: ptr GError


;GtkIconInfo
gtk_icon_theme_lookup_by_gicon proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		  icon: ptr GIcon,
		  size: gint,
		 flags: GtkIconLookupFlags

;GtkIconInfo
gtk_icon_theme_lookup_by_gicon_for_scale proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		  icon: ptr GIcon,
		  size: gint,
		 scale: gint,
		 flags: GtkIconLookupFlags



;GList
gtk_icon_theme_list_icons proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
	       context: ptr gchar

;GList
gtk_icon_theme_list_contexts proto __cdecl \
	    icon_theme: ptr GtkIconTheme

;char
gtk_icon_theme_get_example_icon_name proto __cdecl \
	    icon_theme: ptr GtkIconTheme


;gboolean
gtk_icon_theme_rescan_if_needed proto __cdecl \
	    icon_theme: ptr GtkIconTheme


;void
gtk_icon_theme_add_builtin_icon proto __cdecl \
	     icon_name: ptr gchar,
		  size: gint,
		pixbuf: ptr GdkPixbuf


;GType
gtk_icon_info_get_type proto __cdecl
;GtkIconInfo
gtk_icon_info_copy proto __cdecl \
	     icon_info: ptr GtkIconInfo

;void
gtk_icon_info_free proto __cdecl \
	     icon_info: ptr GtkIconInfo


;GtkIconInfo
gtk_icon_info_new_for_pixbuf proto __cdecl \
	    icon_theme: ptr GtkIconTheme,
		pixbuf: ptr GdkPixbuf


;gint
gtk_icon_info_get_base_size proto __cdecl \
	     icon_info: ptr GtkIconInfo

;gint
gtk_icon_info_get_base_scale proto __cdecl \
	     icon_info: ptr GtkIconInfo

;const
gtk_icon_info_get_filename proto __cdecl \
	     icon_info: ptr GtkIconInfo

;GdkPixbuf
gtk_icon_info_get_builtin_pixbuf proto __cdecl \
	     icon_info: ptr GtkIconInfo

;gboolean
gtk_icon_info_is_symbolic proto __cdecl \
	     icon_info: ptr GtkIconInfo

;GdkPixbuf
gtk_icon_info_load_icon proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		 error: ptr GError

;cairo_surface_t
gtk_icon_info_load_surface proto __cdecl \
	     icon_info: ptr GtkIconInfo,
	    for_window: ptr GdkWindow,
		 error: ptr GError

;void
gtk_icon_info_load_icon_async proto __cdecl \
	     icon_info: ptr GtkIconInfo,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GdkPixbuf
gtk_icon_info_load_icon_finish proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		   res: ptr GAsyncResult,
		 error: ptr GError

;GdkPixbuf
gtk_icon_info_load_symbolic proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		    fg: ptr GdkRGBA,
	 success_color: ptr GdkRGBA,
	 warning_color: ptr GdkRGBA,
	   error_color: ptr GdkRGBA,
	  was_symbolic: ptr gboolean,
		 error: ptr GError

;void
gtk_icon_info_load_symbolic_async proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		    fg: ptr GdkRGBA,
	 success_color: ptr GdkRGBA,
	 warning_color: ptr GdkRGBA,
	   error_color: ptr GdkRGBA,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GdkPixbuf
gtk_icon_info_load_symbolic_finish proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		   res: ptr GAsyncResult,
	  was_symbolic: ptr gboolean,
		 error: ptr GError

;GdkPixbuf
gtk_icon_info_load_symbolic_for_context proto __cdecl \
	     icon_info: ptr GtkIconInfo,
	       context: ptr GtkStyleContext,
	  was_symbolic: ptr gboolean,
		 error: ptr GError

;void
gtk_icon_info_load_symbolic_for_context_async proto __cdecl \
	     icon_info: ptr GtkIconInfo,
	       context: ptr GtkStyleContext,
	   cancellable: ptr GCancellable,
	      callback: GAsyncReadyCallback,
	     user_data: gpointer

;GdkPixbuf
gtk_icon_info_load_symbolic_for_context_finish proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		   res: ptr GAsyncResult,
	  was_symbolic: ptr gboolean,
		 error: ptr GError

;GdkPixbuf
gtk_icon_info_load_symbolic_for_style proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		 style: ptr GtkStyle,
		 state: GtkStateType,
	  was_symbolic: ptr gboolean,
		 error: ptr GError

;void
gtk_icon_info_set_raw_coordinates proto __cdecl \
	     icon_info: ptr GtkIconInfo,
       raw_coordinates: gboolean


;gboolean
gtk_icon_info_get_embedded_rect proto __cdecl \
	     icon_info: ptr GtkIconInfo,
	     rectangle: ptr GdkRectangle

;gboolean
gtk_icon_info_get_attach_points proto __cdecl \
	     icon_info: ptr GtkIconInfo,
		points: ptr GdkPoint,
	      n_points: ptr gint

;const
gtk_icon_info_get_display_name proto __cdecl \
	     icon_info: ptr GtkIconInfo


G_END_DECLS

endif
