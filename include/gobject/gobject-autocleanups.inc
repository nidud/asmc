ifndef __G_AUTOCLEANUPS_H__
define __G_AUTOCLEANUPS_H__

if not defined (__GLIB_GOBJECT_H_INSIDE__) and not defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GClosure, g_closure_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GEnumClass, g_type_class_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GFlagsClass, g_type_class_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GObject, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GInitiallyUnowned, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GParamSpec, g_param_spec_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GTypeClass, g_type_class_unref)
G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC(GValue, g_value_unset)

endif
