ifndef __GTK_STYLE_PROPERTIES_H__
__GTK_STYLE_PROPERTIES_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include glib-object.inc
include gdk/gdk.inc
include gtk/gtkenums.inc

G_BEGIN_DECLS

GTK_TYPE_STYLE_PROPERTIES equ <gtk_style_properties_get_type>
GTK_STYLE_PROPERTIES macro o
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GTK_TYPE_STYLE_PROPERTIES, GtkStyleProperties))>
	endm
GTK_STYLE_PROPERTIES_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_CAST	  ((c), GTK_TYPE_STYLE_PROPERTIES, GtkStylePropertiesClass))>
	endm
GTK_IS_STYLE_PROPERTIES macro o
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GTK_TYPE_STYLE_PROPERTIES))>
	endm
GTK_IS_STYLE_PROPERTIES_CLASS macro c
	exitm<(G_TYPE_CHECK_CLASS_TYPE	  ((c), GTK_TYPE_STYLE_PROPERTIES))>
	endm
GTK_STYLE_PROPERTIES_GET_CLASS macro o
	exitm<(G_TYPE_INSTANCE_GET_CLASS  ((o), GTK_TYPE_STYLE_PROPERTIES, GtkStylePropertiesClass))>
	endm

GtkStyleProperties	STRUC
parent_object		GObject <>
priv			ptr_t ?
GtkStyleProperties	ENDS

GtkStylePropertiesClass STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkStylePropertiesClass ENDS

CALLBACKC(GtkStylePropertyParser, :ptr gchar, :ptr GValue, :ptr ptr GError)

;GType
gtk_style_properties_get_type proto __cdecl

;void
gtk_style_properties_register_property proto __cdecl \
	    parse_func: GtkStylePropertyParser,
		 pspec: ptr GParamSpec

;gboolean
gtk_style_properties_lookup_property proto __cdecl \
	 property_name: ptr gchar,
	    parse_func: ptr GtkStylePropertyParser,
		 pspec: ptr GParamSpec


;GtkStyleProperties
gtk_style_properties_new proto __cdecl

;void
gtk_style_properties_map_color proto __cdecl \
		 props: ptr GtkStyleProperties,
		  name: ptr gchar,
		 color: ptr GtkSymbolicColor

;GtkSymbolicColor
gtk_style_properties_lookup_color proto __cdecl \
		 props: ptr GtkStyleProperties,
		  name: ptr gchar


;void
gtk_style_properties_set_property proto __cdecl \
		 props: ptr GtkStyleProperties,
	      property: ptr gchar,
		 state: GtkStateFlags,
		 value: ptr GValue

;void
gtk_style_properties_set_valist proto __cdecl \
		 props: ptr GtkStyleProperties,
		 state: GtkStateFlags,
		  args: va_list

;void
gtk_style_properties_set proto _CDecl \
		 props: ptr GtkStyleProperties,
		 state: GtkStateFlags,
		      : vararg

;gboolean
gtk_style_properties_get_property proto __cdecl \
		 props: ptr GtkStyleProperties,
	      property: ptr gchar,
		 state: GtkStateFlags,
		 value: ptr GValue

;void
gtk_style_properties_get_valist proto __cdecl \
		 props: ptr GtkStyleProperties,
		 state: GtkStateFlags,
		  args: va_list

;void
gtk_style_properties_get proto _CDecl \
		 props: ptr GtkStyleProperties,
		 state: GtkStateFlags,
		      : vararg

;void
gtk_style_properties_unset_property proto __cdecl \
		 props: ptr GtkStyleProperties,
	      property: ptr gchar,
		 state: GtkStateFlags


;void
gtk_style_properties_clear proto __cdecl \
		 props: ptr GtkStyleProperties


;void
gtk_style_properties_merge proto __cdecl \
		 props: ptr GtkStyleProperties,
	props_to_merge: ptr GtkStyleProperties,
	       replace: gboolean

G_END_DECLS

endif
