if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

ifndef __GI_SCANNER__

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkAppLaunchContext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkCursor, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkDevice, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkDeviceManager, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkDisplay, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkDisplayManager, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkDragContext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkFrameClock, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkGLContext, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkKeymap, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkScreen, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkVisual, g_object_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkWindow, g_object_unref)

G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkEvent, gdk_event_free)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkFrameTimings, gdk_frame_timings_unref)
G_DEFINE_AUTOPTR_CLEANUP_FUNC(GdkRGBA, gdk_rgba_free)

endif
