ifndef GDK_PIXBUF_AUTOCLEANUPS_H
define GDK_PIXBUF_AUTOCLEANUPS_H

if defined(GDK_PIXBUF_DISABLE_SINGLE_INCLUDES) AND NOT defined (GDK_PIXBUF_H_INSIDE) AND NOT defined (GDK_PIXBUF_COMPILATION)
.err <"Only gdk-pixbuf/gdk-pixbuf.h can be included directly.">
endif

ifdef G_DEFINE_AUTOPTR_CLEANUP_FUNC

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkPixbuf, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkPixbufAnimation, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkPixbufAnimationIter, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkPixbufLoader, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkPixbufSimpleAnim, g_object_unref)

endif

endif
