ifndef __GDKCONFIG_H__
define __GDKCONFIG_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib.inc

ifdef __UNIX__
define GDK_WINDOWING_X11
define GDK_WINDOWING_BROADWAY
define GDK_WINDOWING_WAYLAND
define GDK_WINDOWING_MIR
else
undef GDK_WINDOWING_X11
undef GDK_WINDOWING_BROADWAY
undef GDK_WINDOWING_MACOS
undef GDK_WINDOWING_WAYLAND
define GDK_WINDOWING_WIN32
undef GDK_RENDERING_VULKAN
endif

endif
