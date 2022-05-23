ifndef __GTK_MAIN_H__
define __GTK_MAIN_H__

if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

include gdk/gdk.inc
include gtk/gtkwidget.inc
ifdef G_PLATFORM_WIN32
include gtk/gtkbox.inc
include gtk/gtkwindow.inc
endif

define GTK_PRIORITY_RESIZE (G_PRIORITY_HIGH_IDLE + 10)

gtk_init proto
gtk_init_check proto
gtk_is_initialized proto

ifdef G_OS_WIN32

gtk_init_abi_check proto :sdword, :size_t, :size_t
gtk_init_check_abi_check proto :sdword, :size_t, :size_t

gtk_init macro
  exitm<gtk_init_abi_check (2, sizeof (GtkWindow), sizeof (GtkBox))>
  endm
gtk_init_check macro
  exitm<gtk_init_check_abi_check (2, sizeof (GtkWindow), sizeof (GtkBox))>
  endm

endif

gtk_disable_setlocale proto
gtk_get_default_language proto
gtk_get_locale_direction proto

endif
