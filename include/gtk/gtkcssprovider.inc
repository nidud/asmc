ifndef __GTK_CSS_PROVIDER_H__
__GTK_CSS_PROVIDER_H__ equ <>
include gio/gio.inc
include gtk/gtkcsssection.inc

G_BEGIN_DECLS

GTK_TYPE_CSS_PROVIDER	equ <gtk_css_provider_get_type>
GTK_CSS_PROVIDER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_CSS_PROVIDER, GtkCssProvider))>
	endm
GTK_CSS_PROVIDER_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_CAST	  ((c), GTK_TYPE_CSS_PROVIDER, GtkCssProviderClass))>
	endm
GTK_IS_CSS_PROVIDER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_CSS_PROVIDER))>
	endm
GTK_IS_CSS_PROVIDER_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_TYPE	  ((c), GTK_TYPE_CSS_PROVIDER))>
	endm
GTK_CSS_PROVIDER_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS  ((o), GTK_TYPE_CSS_PROVIDER, GtkCssProviderClass))>
	endm

GTK_CSS_PROVIDER_ERROR	equ <gtk_css_provider_error_quark>

.enum GtkCssProviderError {
  GTK_CSS_PROVIDER_ERROR_FAILED,
  GTK_CSS_PROVIDER_ERROR_SYNTAX,
  GTK_CSS_PROVIDER_ERROR_IMPORT,
  GTK_CSS_PROVIDER_ERROR_NAME,
  GTK_CSS_PROVIDER_ERROR_DEPRECATED,
  GTK_CSS_PROVIDER_ERROR_UNKNOWN_VALUE
}

;GQuark
gtk_css_provider_error_quark proto __cdecl

GtkCssProvider		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkCssProvider		ENDS

GtkCssProviderClass	STRUC
parent_class		GObjectClass <>
parsing_error		proc :ptr GtkCssProvider, :ptr GtkCssSection, :ptr GError
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkCssProviderClass	ENDS

;GType
gtk_css_provider_get_type proto __cdecl

;GtkCssProvider
gtk_css_provider_new proto __cdecl

;char
gtk_css_provider_to_string proto __cdecl \
	      provider: ptr GtkCssProvider


;gboolean
gtk_css_provider_load_from_data proto __cdecl \
	  css_provider: ptr GtkCssProvider,
		  data: ptr gchar,
		length: gssize,
		 error: ptr GError

;gboolean
gtk_css_provider_load_from_file proto __cdecl \
	  css_provider: ptr GtkCssProvider,
		  file: ptr GFile,
		 error: ptr GError

;gboolean
gtk_css_provider_load_from_path proto __cdecl \
	  css_provider: ptr GtkCssProvider,
		  path: ptr gchar,
		 error: ptr GError


;void
gtk_css_provider_load_from_resource proto __cdecl \
	  css_provider: ptr GtkCssProvider,
	 resource_path: ptr gchar


;GtkCssProvider
gtk_css_provider_get_default proto __cdecl

;GtkCssProvider
gtk_css_provider_get_named proto __cdecl \
		  name: ptr gchar,
	       variant: ptr gchar


G_END_DECLS

endif
