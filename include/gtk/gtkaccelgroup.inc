ifndef __GTK_ACCEL_GROUP_H__
__GTK_ACCEL_GROUP_H__ equ 1
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

GTK_TYPE_ACCEL_GROUP equ <gtk_accel_group_get_type>
GTK_ACCEL_GROUP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), GTK_TYPE_ACCEL_GROUP, GtkAccelGroup))>
	endm
GTK_ACCEL_GROUP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GTK_TYPE_ACCEL_GROUP, GtkAccelGroupClass))>
	endm
GTK_IS_ACCEL_GROUP macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), GTK_TYPE_ACCEL_GROUP))>
	endm
GTK_IS_ACCEL_GROUP_CLASS macro klass
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_ACCEL_GROUP))>
	endm
GTK_ACCEL_GROUP_GET_CLASS macro obj
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GTK_TYPE_ACCEL_GROUP, GtkAccelGroupClass))>
	endm

.enum GtkAccelFlags {
    GTK_ACCEL_VISIBLE	= 1 shl 0
    GTK_ACCEL_LOCKED	= 1 shl 1
    GTK_ACCEL_MASK	= 0x07
}


CALLBACKC(GtkAccelGroupActivate, :ptr GtkAccelGroup,:ptr GObject, :guint, :GdkModifierType)
CALLBACKC(GtkAccelGroupFindFunc, :ptr GtkAccelKey, :ptr GClosure, :gpointer)

GtkAccelGroup		STRUC
parent			GObject <>
priv			ptr_t ?
GtkAccelGroup		ENDS

GtkAccelGroupClass	STRUC
parent_class		GObjectClass <>
accel_changed		proc :ptr GtkAccelGroup, :guint, :GdkModifierType, :ptr GClosure
_gtk_reserved1		proc
_gtk_reserved2		proc
_gtk_reserved3		proc
_gtk_reserved4		proc
GtkAccelGroupClass	ENDS

GtkAccelKey		STRUC
accel_key		guint ?
accel_mods		GdkModifierType ?
;accel_flags : 16	guint ?
accel_flags		dw ?
GtkAccelKey		ENDS


;GType
gtk_accel_group_get_type proto __cdecl
;GtkAccelGroup*
gtk_accel_group_new proto __cdecl
;gboolean
gtk_accel_group_get_is_locked proto __cdecl \
	   accel_group: ptr GtkAccelGroup

;GdkModifierType
gtk_accel_group_get_modifier_mask proto __cdecl \
	   accel_group: ptr GtkAccelGroup

;void
gtk_accel_group_lock proto __cdecl \
	   accel_group: ptr GtkAccelGroup

;void
gtk_accel_group_unlock proto __cdecl \
	   accel_group: ptr GtkAccelGroup

;void
gtk_accel_group_connect proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
	     accel_key: guint,
	    accel_mods: GdkModifierType,
	   accel_flags: GtkAccelFlags,
	       closure: ptr GClosure

;void
gtk_accel_group_connect_by_path proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
	    accel_path: ptr gchar,
	       closure: ptr GClosure

;gboolean
gtk_accel_group_disconnect proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
	       closure: ptr GClosure

;gboolean
gtk_accel_group_disconnect_key proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
	     accel_key: guint,
	    accel_mods: GdkModifierType

;gboolean
gtk_accel_group_activate proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
	   accel_quark: GQuark,
	 acceleratable: ptr GObject,
	     accel_key: guint,
	    accel_mods: GdkModifierType



;void
_gtk_accel_group_attach proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
		object: ptr GObject

;void
_gtk_accel_group_detach proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
		object: ptr GObject

;gboolean
gtk_accel_groups_activate proto __cdecl \
		object: ptr GObject,
	     accel_key: guint,
	    accel_mods: GdkModifierType

;GSList*
gtk_accel_groups_from_object proto __cdecl \
		object: ptr GObject

;GtkAccelKey*
gtk_accel_group_find proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
	     find_func: GtkAccelGroupFindFunc,
		  data: gpointer

;GtkAccelGroup*
gtk_accel_group_from_accel_closure proto __cdecl \
	       closure: ptr GClosure



;gboolean
gtk_accelerator_valid proto __cdecl \
		keyval: guint,
	     modifiers: GdkModifierType

;void
gtk_accelerator_parse proto __cdecl \
	   accelerator: ptr gchar,
       accelerator_key: ptr guint,
      accelerator_mods: ptr GdkModifierType

;void
gtk_accelerator_parse_with_keycode proto __cdecl \
	   accelerator: ptr gchar,
       accelerator_key: ptr guint,
     accelerator_codes: ptr guint,
      accelerator_mods: ptr GdkModifierType

;gchar*
gtk_accelerator_name proto __cdecl \
       accelerator_key: guint,
      accelerator_mods: GdkModifierType

;gchar*
gtk_accelerator_name_with_keycode proto __cdecl \
	       display: ptr GdkDisplay,
       accelerator_key: guint,
	       keycode: guint,
      accelerator_mods: GdkModifierType

;gchar*
gtk_accelerator_get_label proto __cdecl \
       accelerator_key: guint,
      accelerator_mods: GdkModifierType

;gchar*
gtk_accelerator_get_label_with_keycode proto __cdecl \
	       display: ptr GdkDisplay,
       accelerator_key: guint,
	       keycode: guint,
      accelerator_mods: GdkModifierType

;void
gtk_accelerator_set_default_mod_mask proto __cdecl \
      default_mod_mask: GdkModifierType

;GdkModifierType
gtk_accelerator_get_default_mod_mask proto __cdecl

;GtkAccelGroupEntry*
gtk_accel_group_query proto __cdecl \
	   accel_group: ptr GtkAccelGroup,
	     accel_key: guint,
	    accel_mods: GdkModifierType,
	     n_entries: ptr guint


GtkAccelGroupEntry	STRUC
key			GtkAccelKey <>
closure			ptr_t ?
accel_path_quark	GQuark ?
GtkAccelGroupEntry	ENDS

endif
