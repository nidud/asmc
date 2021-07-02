

ifndef __GDK_H__
__GDK_H__ equ 1

__GDK_H_INSIDE__ equ 1

include gdk/gdkconfig.inc
include gdk/gdkversionmacros.inc
include gdk/gdkapplaunchcontext.inc
include gdk/gdkcairo.inc
include gdk/gdkcursor.inc
include gdk/gdkdevice.inc
include gdk/gdkdevicemanager.inc
include gdk/gdkdisplay.inc
include gdk/gdkdisplaymanager.inc
include gdk/gdkdnd.inc
include gdk/gdkenumtypes.inc
include gdk/gdkevents.inc
include gdk/gdkframeclock.inc
include gdk/gdkframetimings.inc
include gdk/gdkglcontext.inc
include gdk/gdkkeys.inc
include gdk/gdkkeysyms.inc
include gdk/gdkmain.inc
include gdk/gdkpango.inc
include gdk/gdkpixbuf.inc
include gdk/gdkproperty.inc
include gdk/gdkrectangle.inc
include gdk/gdkrgba.inc
include gdk/gdkscreen.inc
include gdk/gdkselection.inc
include gdk/gdktestutils.inc
include gdk/gdkthreads.inc
include gdk/gdktypes.inc
include gdk/gdkvisual.inc
include gdk/gdkwindow.inc

ifndef GDK_DISABLE_DEPRECATED
include gdk/deprecated/gdkcolor.inc
endif

include gdk/gdk-autocleanup.inc

undef __GDK_H_INSIDE__

endif
