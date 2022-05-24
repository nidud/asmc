ifndef __GTK_CSS_PROVIDER_H__
define __GTK_CSS_PROVIDER_H__

include gio/gio.inc
include gtk/css/gtkcss.inc

define GTK_TYPE_CSS_PROVIDER <gtk_css_provider_get_type ()>
GTK_CSS_PROVIDER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_CSS_PROVIDER, GtkCssProvider))>
  endm
GTK_IS_CSS_PROVIDER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_CSS_PROVIDER))>
  endm

;GtkCssProviderClass     typedef _GtkCssProviderClass
;GtkCssProviderPrivate   typedef _GtkCssProviderPrivate

_GtkCssProvider         struct
parent_instance         GObject <>
_GtkCssProvider         ends
GtkCssProvider          typedef _GtkCssProvider

gtk_css_provider_get_type proto
gtk_css_provider_new proto
gtk_css_provider_to_string proto :ptr
gtk_css_provider_load_from_data proto :ptr, :ptr, :gssize
gtk_css_provider_load_from_file proto :ptr, :ptr
gtk_css_provider_load_from_path proto :ptr, :ptr
gtk_css_provider_load_from_resource proto :ptr, :ptr
gtk_css_provider_load_named proto :ptr, :ptr, :ptr

endif
