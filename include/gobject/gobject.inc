ifndef __G_OBJECT_H__
define __G_OBJECT_H__

.pragma comment(lib, "gobject-2.0")

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

include gobject/gtype.inc
include gobject/gvalue.inc
include gobject/gparam.inc
include gobject/gclosure.inc
include gobject/gsignal.inc
include gobject/gboxed.inc

G_TYPE_IS_OBJECT macro type
  exitm<(G_TYPE_FUNDAMENTAL (type) eq G_TYPE_OBJECT)>
  endm

G_OBJECT macro object
  exitm<G_TYPE_CHECK_INSTANCE_CAST (object, G_TYPE_OBJECT, GObject)>
  endm

G_OBJECT_CLASS macro class
  exitm<G_TYPE_CHECK_CLASS_CAST (class, G_TYPE_OBJECT, GObjectClass)>
  endm

if GLIB_VERSION_MAX_ALLOWED ge GLIB_VERSION_2_42
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
  exitm<G_TYPE_INSTANCE_GET_CLASS ((object), G_TYPE_OBJECT, GObjectClass)>
  endm

G_OBJECT_TYPE macro object
  exitm<G_TYPE_FROM_INSTANCE (object)>
  endm

G_OBJECT_TYPE_NAME macro object
  exitm<g_type_name (G_OBJECT_TYPE (object))>
  endm

G_OBJECT_CLASS_TYPE macro class
  exitm<G_TYPE_FROM_CLASS (class)>
  endm

G_OBJECT_CLASS_NAME macro class
  exitm<g_type_name (G_OBJECT_CLASS_TYPE (class))>
  endm

G_VALUE_HOLDS_OBJECT macro value
  exitm<G_TYPE_CHECK_VALUE_TYPE ((value), G_TYPE_OBJECT)>
  endm

define G_TYPE_INITIALLY_UNOWNED	      (g_initially_unowned_get_type())

G_INITIALLY_UNOWNED macro object
  exitm<G_TYPE_CHECK_INSTANCE_CAST ((object), G_TYPE_INITIALLY_UNOWNED, GInitiallyUnowned)>
  endm

G_INITIALLY_UNOWNED_CLASS macro class
  exitm<G_TYPE_CHECK_CLASS_CAST ((class), G_TYPE_INITIALLY_UNOWNED, GInitiallyUnownedClass)>
  endm

G_IS_INITIALLY_UNOWNED macro object
  exitm<G_TYPE_CHECK_INSTANCE_TYPE ((object), G_TYPE_INITIALLY_UNOWNED)>
  endm

G_IS_INITIALLY_UNOWNED_CLASS macro class
  exitm<G_TYPE_CHECK_CLASS_TYPE ((class), G_TYPE_INITIALLY_UNOWNED)>
  endm

G_INITIALLY_UNOWNED_GET_CLASS macro object
  exitm<G_TYPE_INSTANCE_GET_CLASS ((object), G_TYPE_INITIALLY_UNOWNED, GInitiallyUnownedClass)>
  endm

CALLBACK(GObjectGetPropertyFunc, :ptr, :guint, :ptr, :ptr)
CALLBACK(GObjectSetPropertyFunc, :ptr, :guint, :ptr, :ptr)
CALLBACK(GObjectFinalizeFunc, :ptr)
CALLBACK(GWeakNotify, :gpointer, :ptr)

GObject			struct
g_type_instance		GTypeInstance <>
ref_count		guint ?
qdata			ptr GData ?
GObject			ends

GObjectClass		struct
g_type_class		GTypeClass <>
construct_properties	ptr GSList ?
constructor		proc :GType, :guint, :ptr
set_property		proc :ptr, :guint, :ptr, :ptr
get_property		proc :ptr, :guint, :ptr, :ptr
dispose			proc :ptr
finalize		proc :ptr
dispatch_properties_changed proc :ptr, :guint, :ptr
notify			proc :ptr, :ptr
constructed		proc :ptr
flags			gsize ?
pdummy			gpointer 6 dup(?)
GObjectClass		ends

GObjectConstructParam	struct
pspec			ptr GParamSpec ?
value			ptr GValue ?
GObjectConstructParam	ends

GInitiallyUnowned	typedef GObject
GInitiallyUnownedClass	typedef GObjectClass

g_initially_unowned_get_type proto
g_object_class_install_property proto :ptr, :guint, :ptr
g_object_class_find_property proto :ptr, :ptr
g_object_class_list_properties proto :ptr, :ptr
g_object_class_override_property proto :ptr, :guint, :ptr
g_object_class_install_properties proto :ptr, :guint, :ptr

g_object_interface_install_property proto :gpointer, :ptr
g_object_interface_find_property proto :gpointer, :ptr
g_object_interface_list_properties proto :gpointer, :ptr

g_object_get_type proto
g_object_new proto :GType, :ptr, :vararg
g_object_new_with_properties proto :GType, :guint, :ptr, :GValue

g_object_newv proto :GType, :guint, :ptr

g_object_new_valist proto :GType, :ptr, :va_list
g_object_set proto :gpointer, :ptr, :vararg
g_object_get proto :gpointer, :ptr, :vararg
g_object_connect proto :gpointer, :ptr, :vararg
g_object_disconnect proto :gpointer, :ptr, :vararg
g_object_setv proto :ptr, :guint, :ptr, :GValue
g_object_set_valist proto :ptr, :ptr, :va_list
g_object_getv proto :ptr, :guint, :ptr, :GValue
g_object_get_valist proto :ptr, :ptr, :va_list
g_object_set_property proto :ptr, :ptr, :ptr
g_object_get_property proto :ptr, :ptr, :ptr
g_object_freeze_notify proto :ptr
g_object_notify proto :ptr, :ptr
g_object_notify_by_pspec proto :ptr, :ptr
g_object_thaw_notify proto :ptr
g_object_is_floating proto :gpointer
g_object_ref_sink proto :gpointer
g_object_take_ref proto :gpointer
g_object_ref proto :gpointer
g_object_unref proto :gpointer
g_object_weak_ref proto :ptr, :GWeakNotify, :gpointer
g_object_weak_unref proto :ptr, :GWeakNotify, :gpointer
g_object_add_weak_pointer proto :ptr, :ptr
g_object_remove_weak_pointer proto :ptr, :ptr

if defined(glib_typeof) and GLIB_VERSION_MAX_ALLOWED ge GLIB_VERSION_2_56

g_object_ref macro Obj
  exitm<((glib_typeof (Obj)) (g_object_ref) (Obj))>
  endm
g_object_ref_sink macro Obj
  exitm<((glib_typeof (Obj)) (g_object_ref_sink) (Obj))>
  endm
endif


CALLBACK(GToggleNotify, :gpointer, :ptr, :gboolean)

g_object_add_toggle_ref proto :ptr, :GToggleNotify, :gpointer
g_object_remove_toggle_ref proto :ptr, :GToggleNotify, :gpointer

g_object_get_qdata proto :ptr, :GQuark
g_object_set_qdata proto :ptr, :GQuark, :gpointer
g_object_set_qdata_full proto :ptr, :GQuark, :gpointer, :GDestroyNotify
g_object_steal_qdata proto :ptr, :GQuark

g_object_dup_qdata proto :ptr, :GQuark, :GDuplicateFunc, :gpointer
g_object_replace_qdata proto :ptr, :GQuark, :gpointer, :gpointer, :GDestroyNotify, :ptr

g_object_get_data proto :ptr, :ptr
g_object_set_data proto :ptr, :ptr, :gpointer
g_object_set_data_full proto :ptr, :ptr, :gpointer, :GDestroyNotify
g_object_steal_data proto :ptr, :ptr

g_object_dup_data proto :ptr, :ptr, :GDuplicateFunc, :gpointer
g_object_replace_data proto :ptr, :ptr, :gpointer, :gpointer, :GDestroyNotify, :ptr

g_object_watch_closure proto :ptr, :ptr
g_cclosure_new_object proto :GCallback, :ptr
g_cclosure_new_object_swap proto :GCallback, :ptr
g_closure_new_object proto :guint, :ptr
g_value_set_object proto :ptr, :gpointer
g_value_get_object proto :ptr
g_value_dup_object proto :ptr
g_signal_connect_object proto :gpointer, :ptr, :GCallback, :gpointer, :GConnectFlags

g_object_force_floating proto :ptr
g_object_run_dispose proto :ptr

g_value_take_object proto :ptr, :gpointer
g_value_set_object_take_ownership proto :ptr, :gpointer

g_object_compat_control proto :gsize, :gpointer

G_OBJECT_WARN_INVALID_PROPERTY_ID macro object, property_id, pspec
  exitm<G_OBJECT_WARN_INVALID_PSPEC ((object), "property", (property_id), (pspec))>
  endm

g_clear_object proto :ptr ptr
g_clear_object macro object_ptr
  exitm<g_clear_pointer ((object_ptr), g_object_unref)>
  endm

ifdef G_DISABLE_ASSERT
g_assert_finalize_object macro object
  exitm<g_object_unref (object)>
  endm
else
g_assert_finalize_object macro object
  exitm<(g_assert_finalize_object ((GObject *) object))>
  endm
endif

GWeakRef		struct
union priv
p			gpointer ?
ends
GWeakRef		ends

g_weak_ref_init proto :ptr, :gpointer
g_weak_ref_clear proto :ptr
g_weak_ref_get proto :ptr
g_weak_ref_set proto :ptr, :gpointer

endif
