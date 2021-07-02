ifndef __GTK_STYLE_PROVIDER_H__
__GTK_STYLE_PROVIDER_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gtk/gtkenums.inc
include gtk/deprecated/gtkiconfactory.inc
include gtk/deprecated/gtkstyleproperties.inc
include gtk/gtktypes.inc

G_BEGIN_DECLS

GTK_TYPE_STYLE_PROVIDER equ <gtk_style_provider_get_type>
GTK_STYLE_PROVIDER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_STYLE_PROVIDER, GtkStyleProvider))>
	endm
GTK_IS_STYLE_PROVIDER macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_STYLE_PROVIDER))>
	endm
GTK_STYLE_PROVIDER_GET_IFACE macro o
	exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((o), GTK_TYPE_STYLE_PROVIDER, GtkStyleProviderIface))>
	endm

GTK_STYLE_PROVIDER_PRIORITY_FALLBACK equ 1
GTK_STYLE_PROVIDER_PRIORITY_THEME equ 200
GTK_STYLE_PROVIDER_PRIORITY_SETTINGS equ 400
GTK_STYLE_PROVIDER_PRIORITY_APPLICATION equ 600
GTK_STYLE_PROVIDER_PRIORITY_USER equ 800

GtkStyleProviderIface	STRUC
g_iface			GTypeInterface <>
get_style		proc :ptr GtkStyleProvider, :ptr GtkWidgetPath
get_style_property	proc :ptr GtkStyleProvider, :ptr GtkWidgetPath,
				:GtkStateFlags, :ptr GParamSpec, :ptr GValue
get_icon_factory	proc :ptr GtkStyleProvider, :ptr GtkWidgetPath
GtkStyleProviderIface	ENDS

;GType
gtk_style_provider_get_type proto __cdecl

;GtkStyleProperties
gtk_style_provider_get_style proto __cdecl \
	      provider: ptr GtkStyleProvider,
		  path: ptr GtkWidgetPath


;gboolean
gtk_style_provider_get_style_property proto __cdecl \
	      provider: ptr GtkStyleProvider,
		  path: ptr GtkWidgetPath,
		 state: GtkStateFlags,
		 pspec: ptr GParamSpec,
		 value: ptr GValue


;GtkIconFactory
gtk_style_provider_get_icon_factory proto __cdecl \
	      provider: ptr GtkStyleProvider,
		  path: ptr GtkWidgetPath


G_END_DECLS

endif
