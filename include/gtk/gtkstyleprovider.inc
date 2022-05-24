ifndef __GTK_STYLE_PROVIDER_H__
define __GTK_STYLE_PROVIDER_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc
include gtk/gtktypes.inc

define GTK_TYPE_STYLE_PROVIDER <gtk_style_provider_get_type ()>
GTK_STYLE_PROVIDER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_STYLE_PROVIDER, GtkStyleProvider))>
  endm
GTK_IS_STYLE_PROVIDER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_STYLE_PROVIDER))>
  endm


define GTK_STYLE_PROVIDER_PRIORITY_FALLBACK      1
define GTK_STYLE_PROVIDER_PRIORITY_THEME     200
define GTK_STYLE_PROVIDER_PRIORITY_SETTINGS    400
define GTK_STYLE_PROVIDER_PRIORITY_APPLICATION 600
define GTK_STYLE_PROVIDER_PRIORITY_USER        800

;GtkStyleProvider        typedef _GtkStyleProvider

gtk_style_provider_get_type proto

endif
