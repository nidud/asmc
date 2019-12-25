ifndef __GTK_BINDINGS_H__
__GTK_BINDINGS_H__ equ <>
if NOT defined (__GTK_H_INSIDE__) AND NOT defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkenums.inc

G_BEGIN_DECLS

GtkBindingSet		STRUC
set_name		ptr_t ?
priority		gint ?
widget_path_pspecs	ptr_t ?
widget_class_pspecs	ptr_t ?
class_branch_pspecs	ptr_t ?
entries			ptr_t ?
current			ptr_t ?
parsed			guint ? ; : 1
GtkBindingSet		ENDS

GtkBindingEntry		STRUC
keyval			guint ?
modifiers		GdkModifierType ?
binding_set		ptr_t ?
destroyed		guint ? ; : 1
;in_emission   : 1	 guint ?
;marks_unbound : 1	 guint ?
set_next		ptr_t ?
hash_next		ptr_t ?
signals			ptr_t ?
GtkBindingEntry		ENDS

GtkBindingArg		STRUC
arg_type		GType ?
UNION ; {
long_data		glong ?
double_data		gdouble ?
string_data		ptr_t ?
ENDS ;d
GtkBindingArg		ENDS

GtkBindingSignal	STRUC
next			ptr_t ?
signal_name		ptr_t ?
n_args			guint ?
args			ptr_t ?
GtkBindingSignal	ENDS

;GtkBindingSet
gtk_binding_set_new proto __cdecl \
	      set_name: ptr gchar

;GtkBindingSet
gtk_binding_set_by_class proto __cdecl \
	  object_class: gpointer

;GtkBindingSet
gtk_binding_set_find proto __cdecl \
	      set_name: ptr gchar


;gboolean
gtk_bindings_activate proto __cdecl \
		object: ptr GObject,
		keyval: guint,
	     modifiers: GdkModifierType

;gboolean
gtk_bindings_activate_event proto __cdecl \
		object: ptr GObject,
		 event: ptr GdkEventKey

;gboolean
gtk_binding_set_activate proto __cdecl \
	   binding_set: ptr GtkBindingSet,
		keyval: guint,
	     modifiers: GdkModifierType,
		object: ptr GObject


;void
gtk_binding_entry_skip proto __cdecl \
	   binding_set: ptr GtkBindingSet,
		keyval: guint,
	     modifiers: GdkModifierType

;void
gtk_binding_entry_add_signal proto _CDecl \
	   binding_set: ptr GtkBindingSet,
		keyval: guint,
	     modifiers: GdkModifierType,
	   signal_name: ptr gchar,
		n_args: guint,
		      : vararg

;void
gtk_binding_entry_add_signall proto __cdecl \
	   binding_set: ptr GtkBindingSet,
		keyval: guint,
	     modifiers: GdkModifierType,
	   signal_name: ptr gchar,
	  binding_args: ptr GSList


;GTokenType
gtk_binding_entry_add_signal_from_string proto __cdecl \
	   binding_set: ptr GtkBindingSet,
	   signal_desc: ptr gchar


;void
gtk_binding_entry_remove proto __cdecl \
	   binding_set: ptr GtkBindingSet,
		keyval: guint,
	     modifiers: GdkModifierType

G_END_DECLS

endif
