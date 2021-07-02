if NOT defined (__GLIB_GOBJECT_H_INSIDE__) AND NOT defined (GOBJECT_COMPILATION)
.err <"Only glib-object.h can be included directly.">
endif

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GObject, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GInitiallyUnowned, g_object_unref)
G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC(GValue, g_value_unset)
