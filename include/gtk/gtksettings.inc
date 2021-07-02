ifndef __GTK_SETTINGS_H__
__GTK_SETTINGS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtktypes.inc

G_BEGIN_DECLS

GTK_TYPE_SETTINGS equ <gtk_settings_get_type>
GTK_SETTINGS macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GTK_TYPE_SETTINGS, GtkSettings))>
	endm
GTK_SETTINGS_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_SETTINGS, GtkSettingsClass))>
	endm
GTK_IS_SETTINGS macro obj
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTK_TYPE_SETTINGS))>
	endm
GTK_IS_SETTINGS_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_SETTINGS))>
	endm
GTK_SETTINGS_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_SETTINGS, GtkSettingsClass))>
	endm


GtkSettings		STRUC
parent_instance		GObject <>
priv			ptr_t ?
GtkSettings		ENDS

GtkSettingsClass	STRUC
parent_class		GObjectClass <>
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkSettingsClass	ENDS

GtkSettingsValue	STRUC
origin			string_t ?
value			GValue <>
GtkSettingsValue	ENDS

;GType
gtk_settings_get_type proto __cdecl
;GtkSettings*
gtk_settings_get_default proto __cdecl
;GtkSettings*
gtk_settings_get_for_screen proto __cdecl \
		screen: ptr GdkScreen


;void
gtk_settings_install_property proto __cdecl \
		 pspec: ptr GParamSpec

;void
gtk_settings_install_property_parser proto __cdecl \
		 pspec: ptr GParamSpec,
		parser: GtkRcPropertyParser


;gboolean
gtk_rc_property_parse_color proto __cdecl \
		 pspec: ptr GParamSpec,
	       gstring: ptr GString,
	property_value: ptr GValue

;gboolean
gtk_rc_property_parse_enum proto __cdecl \
		 pspec: ptr GParamSpec,
	       gstring: ptr GString,
	property_value: ptr GValue

;gboolean
gtk_rc_property_parse_flags proto __cdecl \
		 pspec: ptr GParamSpec,
	       gstring: ptr GString,
	property_value: ptr GValue

;gboolean
gtk_rc_property_parse_requisition proto __cdecl \
		 pspec: ptr GParamSpec,
	       gstring: ptr GString,
	property_value: ptr GValue

;gboolean
gtk_rc_property_parse_border proto __cdecl \
		 pspec: ptr GParamSpec,
	       gstring: ptr GString,
	property_value: ptr GValue


;void
gtk_settings_set_property_value proto __cdecl \
	      settings: ptr GtkSettings,
		  name: ptr gchar,
		svalue: ptr GtkSettingsValue

;void
gtk_settings_set_string_property proto __cdecl \
	      settings: ptr GtkSettings,
		  name: ptr gchar,
	      v_string: ptr gchar,
		origin: ptr gchar

;void
gtk_settings_set_long_property proto __cdecl \
	      settings: ptr GtkSettings,
		  name: ptr gchar,
		v_long: glong,
		origin: ptr gchar

;void
gtk_settings_set_double_property proto __cdecl \
	      settings: ptr GtkSettings,
		  name: ptr gchar,
	      v_double: gdouble,
		origin: ptr gchar

G_END_DECLS

endif
