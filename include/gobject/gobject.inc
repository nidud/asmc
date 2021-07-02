ifndef __G_OBJECT_H__
__G_OBJECT_H__ equ 1

if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc
include gobject/gvalue.inc
include gobject/gparam.inc
include gobject/gclosure.inc
include gobject/gsignal.inc
include gobject/gboxed.inc

G_TYPE_IS_OBJECT macro type
	exitm<(G_TYPE_FUNDAMENTAL (type) EQ G_TYPE_OBJECT)>
	endm
G_OBJECT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), G_TYPE_OBJECT, GObject))>
	endm
G_OBJECT_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_OBJECT, GObjectClass))>
	endm
if GLIB_VERSION_MAX_ALLOWED GE GLIB_VERSION_2_42
G_IS_OBJECT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_FUNDAMENTAL_TYPE ((object), G_TYPE_OBJECT))>
	endm
else
G_IS_OBJECT macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), G_TYPE_OBJECT))>
	endm
endif
G_IS_OBJECT_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_OBJECT))>
	endm
G_OBJECT_GET_CLASS macro object
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((object), G_TYPE_OBJECT, GObjectClass))>
	endm
G_OBJECT_TYPE macro object
	exitm<(G_TYPE_FROM_INSTANCE (object))>
	endm
G_OBJECT_TYPE_NAME macro object
	exitm<(g_type_name (G_OBJECT_TYPE (object)))>
	endm
G_OBJECT_CLASS_TYPE macro class
	exitm<(G_TYPE_FROM_CLASS (class))>
	endm
G_OBJECT_CLASS_NAME macro class
	exitm<(g_type_name (G_OBJECT_CLASS_TYPE (class)))>
	endm
G_VALUE_HOLDS_OBJECT macro value
	exitm<(G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_OBJECT))>
	endm

G_TYPE_INITIALLY_UNOWNED equ <g_initially_unowned_get_type>

G_INITIALLY_UNOWNED macro object
	exitm<(G_TYPE_CHECK_INSTANCE_CAST ((object), G_TYPE_INITIALLY_UNOWNED, GInitiallyUnowned))>
	endm
G_INITIALLY_UNOWNED_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_INITIALLY_UNOWNED, GInitiallyUnownedClass))>
	endm
G_IS_INITIALLY_UNOWNED macro object
	exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((object), G_TYPE_INITIALLY_UNOWNED))>
	endm
G_IS_INITIALLY_UNOWNED_CLASS macro class
	exitm<(G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_INITIALLY_UNOWNED))>
	endm
G_INITIALLY_UNOWNED_GET_CLASS macro object
	exitm<(G_TYPE_INSTANCE_GET_CLASS ((object), G_TYPE_INITIALLY_UNOWNED, GInitiallyUnownedClass))>
	endm

CALLBACKC(GObjectGetPropertyFunc, :ptr GObject, :guint, :ptr GValue, :ptr GParamSpec)
CALLBACKC(GObjectSetPropertyFunc, :ptr GObject, :guint, :ptr GValue, :ptr GParamSpec)
CALLBACKC(GObjectFinalizeFunc, :ptr GObject)
CALLBACKC(GWeakNotify, :gpointer, :ptr)

quint			typedef dword

GObject			STRUC
g_type_instance		GTypeInstance <>
ref_count		guint ?
qdata			ptr_t ?
GObject			ENDS

GObjectClass		STRUC
g_type_class		GTypeClass <>
construct_properties	ptr_t ?
constructor		proc :GType, :quint, :ptr GObjectConstructParam
set_property		proc :ptr GObject, :guint, :ptr GValue, :ptr GParamSpec
get_property		proc :ptr GObject, :guint, :ptr GValue, :ptr GParamSpec
dispose			proc :ptr GObject
finalize		proc :ptr GObject
dispatch_properties_changed proc :ptr GObject, :guint, :ptr GParamSpec
notify			proc :ptr GObject, :ptr GParamSpec
constructed		proc :ptr GObject
flags			gsize ?
pdummy			gpointer 6 dup(?)
GObjectClass		ENDS

GInitiallyUnowned	typedef GObject
GInitiallyUnownedClass	typedef GObjectClass

GObjectConstructParam	STRUC
pspec			ptr_t ?
value			ptr_t ?
GObjectConstructParam	ENDS


g_initially_unowned_get_type proto __cdecl

g_object_class_install_property proto __cdecl \
		oclass: ptr GObjectClass,
	   property_id: guint,
		 pspec: ptr GParamSpec

g_object_class_find_property proto __cdecl \
		oclass: ptr GObjectClass,
	 property_name: string_t

g_object_class_list_properties proto __cdecl \
		oclass: ptr GObjectClass,
	  n_properties: ptr guint

g_object_class_override_property proto __cdecl \
		oclass: ptr GObjectClass,
	   property_id: guint,
		  name: ptr gchar

g_object_class_install_properties proto __cdecl \
		oclass: ptr GObjectClass,
	      n_pspecs: guint,
		pspecs: ptr GParamSpec


g_object_interface_install_property proto __cdecl \
	       g_iface: gpointer,
		 pspec: ptr GParamSpec

;GParamSpec*
g_object_interface_find_property proto __cdecl \
	       g_iface: gpointer,
	 property_name: ptr gchar

;GParamSpec**
g_object_interface_list_properties proto __cdecl \
	       g_iface: gpointer,
	n_properties_p: ptr guint


;GType
g_object_get_type proto __cdecl

;gpointer
g_object_new proto _CDecl \
	   object_type: GType,
   first_property_name: ptr gchar,
		      : vararg

;gpointer
g_object_newv proto __cdecl \
	   object_type: GType,
	  n_parameters: guint,
	    parameters: ptr GParameter

;GObject*
g_object_new_valist proto __cdecl \
	   object_type: GType,
   first_property_name: ptr gchar,
	      var_args: va_list

g_object_set proto _CDecl \
		object: gpointer,
   first_property_name: ptr gchar,
		      : vararg

g_object_get proto _CDecl \
		object: gpointer,
   first_property_name: ptr gchar,
		      : vararg

;gpointer
g_object_connect proto _CDecl \
		object: gpointer,
	   signal_spec: ptr gchar,
		      : vararg

g_object_disconnect proto _CDecl \
		object: gpointer,
	   signal_spec: ptr gchar,
		      : vararg

g_object_set_valist proto __cdecl \
		object: ptr GObject,
   first_property_name: ptr gchar,
	      var_args: va_list


g_object_get_valist proto __cdecl \
		object: ptr GObject,
   first_property_name: ptr gchar,
	      var_args: va_list

g_object_set_property proto __cdecl \
		object: ptr GObject,
	 property_name: ptr gchar,
		 value: ptr GValue

g_object_get_property proto __cdecl \
		object: ptr GObject,
	 property_name: ptr gchar,
		 value: ptr GValue

g_object_freeze_notify proto __cdecl \
		object: ptr GObject

g_object_notify proto __cdecl \
		object: ptr GObject,
	 property_name: ptr gchar

g_object_notify_by_pspec proto __cdecl \
		object: ptr GObject,
		 pspec: ptr GParamSpec

g_object_thaw_notify proto __cdecl \
		object: ptr GObject

g_object_is_floating proto __cdecl \
		object: gpointer

;gpointer
g_object_ref_sink proto __cdecl \
		object: gpointer

;gpointer
g_object_ref proto __cdecl \
		object: gpointer

g_object_unref proto __cdecl \
		object: gpointer

g_object_weak_ref proto __cdecl \
		object: ptr GObject,
		notify: GWeakNotify,
		  data: gpointer

g_object_weak_unref proto __cdecl \
		object: ptr GObject,
		notify: GWeakNotify,
		  data: gpointer

g_object_add_weak_pointer proto __cdecl \
		object: ptr GObject,
 weak_pointer_location: ptr gpointer

g_object_remove_weak_pointer proto __cdecl \
		object: ptr GObject,
 weak_pointer_location: ptr gpointer


CALLBACKC(GToggleNotify, :gpointer, :ptr GObject, :gboolean)

g_object_add_toggle_ref proto __cdecl \
		object: ptr GObject,
		notify: GToggleNotify,
		  data: gpointer

g_object_remove_toggle_ref proto __cdecl \
		object: ptr GObject,
		notify: GToggleNotify,
		  data: gpointer

;gpointer
g_object_get_qdata proto __cdecl \
		object: ptr GObject,
		 quark: GQuark

;void
g_object_set_qdata proto __cdecl \
		object: ptr GObject,
		 quark: GQuark,
		  data: gpointer

g_object_set_qdata_full proto __cdecl \
		object: ptr GObject,
		 quark: GQuark,
		  data: gpointer,
	       destroy: GDestroyNotify

;gpointer
g_object_steal_qdata proto __cdecl \
		object: ptr GObject,
		 quark: GQuark


;gpointer
g_object_dup_qdata proto __cdecl \
		object: ptr GObject,
		 quark: GQuark,
	      dup_func: GDuplicateFunc,
	     user_data: gpointer


g_object_replace_qdata proto __cdecl \
		object: ptr GObject,
		 quark: GQuark,
		oldval: gpointer,
		newval: gpointer,
	       destroy: GDestroyNotify,
	   old_destroy: ptr GDestroyNotify


;gpointer
g_object_get_data proto __cdecl \
		object: ptr GObject,
		   key: ptr gchar


g_object_set_data proto __cdecl \
		object: ptr GObject,
		   key: ptr gchar,
		  data: gpointer


g_object_set_data_full proto __cdecl \
		object: ptr GObject,
		   key: ptr gchar,
		  data: gpointer,
	       destroy: GDestroyNotify

;void
g_object_set_data proto __cdecl \
		object: ptr GObject,
		   key: ptr gchar,
		  data: gpointer

;gpointer
g_object_dup_data proto __cdecl \
		object: ptr GObject,
		   key: ptr gchar,
	      dup_func: GDuplicateFunc,
	     user_data: gpointer

g_object_replace_data proto __cdecl \
		object: ptr GObject,
		   key: ptr gchar,
		oldval: gpointer,
		newval: gpointer,
	       destroy: GDestroyNotify,
	   old_destroy: ptr GDestroyNotify


g_object_watch_closure proto __cdecl \
		object: ptr GObject,
	       closure: ptr GClosure

;GClosure*
g_cclosure_new_object proto __cdecl \
	 callback_func: GCallback,
		object: ptr GObject

;GClosure*
g_cclosure_new_object_swap proto __cdecl \
	 callback_func: GCallback,
		object: ptr GObject

;GClosure*
g_closure_new_object proto __cdecl \
	sizeof_closure: guint,
		object: ptr GObject

g_value_set_object proto __cdecl \
		 value: ptr GValue,
	      v_object: gpointer

;gpointer
g_value_get_object proto __cdecl \
		 value: ptr GValue

;gpointer
g_value_dup_object proto __cdecl \
		 value: ptr GValue

;gulong
g_signal_connect_object proto __cdecl \
	      instance: gpointer,
       detailed_signal: ptr gchar,
	     c_handler: GCallback,
	       gobject: gpointer,
	 connect_flags: GConnectFlags

g_object_force_floating proto __cdecl \
		object: ptr GObject

g_object_run_dispose proto __cdecl \
		object: ptr GObject



g_value_take_object proto __cdecl \
		 value: ptr GValue,
	      v_object: gpointer

;GLIB_DEPRECATED_FOR(g_value_take_object)

g_value_set_object_take_ownership proto __cdecl \
		 value: ptr GValue,
	      v_object: gpointer


g_object_compat_control proto __cdecl \
		  what: gsize,
		      : gpointer

;; --- implementation macros ---
G_OBJECT_WARN_INVALID_PSPEC macro object, pname, property_id, pspec
	exitm<.err>
	endm

G_OBJECT_WARN_INVALID_PROPERTY_ID macro object, property_id, pspec
	exitm<.err>
	endm

;g_clear_object proto __cdecl \
;	    object_ptr: ptr GObject

g_clear_object macro object_ptr
	exitm<g_clear_pointer((object_ptr), g_object_unref)>
	endm

g_set_object macro object_ptr, new_object
	exitm<.err>
	endm

g_weak_ref_init proto __cdecl \
	      weak_ref: ptr GWeakRef,
		object: gpointer

g_weak_ref_clear proto __cdecl \
	      weak_ref: ptr GWeakRef

g_weak_ref_get proto __cdecl \
	      weak_ref: ptr GWeakRef


g_weak_ref_set proto __cdecl \
	      weak_ref: ptr GWeakRef,
		object: gpointer

endif
