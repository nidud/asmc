ifndef __GTK_ICON_THEME_H__
define __GTK_ICON_THEME_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

define GTK_TYPE_ICON_PAINTABLE <gtk_icon_paintable_get_type ()>
GTK_ICON_PAINTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ICON_PAINTABLE, GtkIconPaintable))>
  endm
GTK_IS_ICON_PAINTABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ICON_PAINTABLE))>
  endm

define GTK_TYPE_ICON_THEME <gtk_icon_theme_get_type ()>
GTK_ICON_THEME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_ICON_THEME, GtkIconTheme))>
  endm
GTK_IS_ICON_THEME macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_ICON_THEME))>
  endm

;GtkIconPaintable        typedef _GtkIconPaintable
;GtkIconTheme            typedef _GtkIconTheme

.enum GtkIconLookupFlags {
  GTK_ICON_LOOKUP_FORCE_REGULAR  = 1 shl 0,
  GTK_ICON_LOOKUP_FORCE_SYMBOLIC = 1 shl 1,
  GTK_ICON_LOOKUP_PRELOAD        = 1 shl 2,
  }

define GTK_ICON_THEME_ERROR <gtk_icon_theme_error_quark ()>

.enum GtkIconThemeError {
  GTK_ICON_THEME_NOT_FOUND,
  GTK_ICON_THEME_FAILED
  }

gtk_icon_theme_error_quark proto
gtk_icon_theme_get_type proto
gtk_icon_theme_new proto
gtk_icon_theme_get_for_display proto :ptr
gtk_icon_theme_get_display proto :ptr
gtk_icon_theme_set_search_path proto :ptr, :ptr
gtk_icon_theme_get_search_path proto :ptr
gtk_icon_theme_add_search_path proto :ptr, :ptr
gtk_icon_theme_set_resource_path proto :ptr, :ptr
gtk_icon_theme_get_resource_path proto :ptr
gtk_icon_theme_add_resource_path proto :ptr, :ptr
gtk_icon_theme_set_theme_name proto :ptr, :ptr
gtk_icon_theme_get_theme_name proto :ptr
gtk_icon_theme_has_icon proto :ptr, :ptr
gtk_icon_theme_has_gicon proto :ptr, :ptr
gtk_icon_theme_get_icon_sizes proto :ptr, :ptr
gtk_icon_theme_lookup_icon proto :ptr, :ptr, :ptr, :sdword, :sdword, :GtkTextDirection, :GtkIconLookupFlags
gtk_icon_theme_lookup_by_gicon proto :ptr, :ptr, :sdword, :sdword, :GtkTextDirection, :GtkIconLookupFlags
gtk_icon_paintable_new_for_file proto :ptr, :sdword, :sdword
gtk_icon_theme_get_icon_names proto :ptr
gtk_icon_paintable_get_type proto
gtk_icon_paintable_get_file proto :ptr
gtk_icon_paintable_get_icon_name proto :ptr
gtk_icon_paintable_is_symbolic proto :ptr

endif
