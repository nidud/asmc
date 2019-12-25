ifndef __GDKCONFIG_H__
__GDKCONFIG_H__ equ <>
if NOT defined (__GDK_H_INSIDE__) AND NOT defined (GDK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include glib.inc

GDK_WINDOWING_X11       equ 1
GDK_WINDOWING_BROADWAY  equ 1
GDK_WINDOWING_WAYLAND   equ 1
GDK_WINDOWING_MIR       equ 1

endif
