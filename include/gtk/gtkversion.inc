if not defined (__GTK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gtk/gtk.h can be included directly.">
endif

ifndef __GTK_VERSION_H__
define __GTK_VERSION_H__

include gdk/gdk.inc

define GTK_MAJOR_VERSION (4)
define GTK_MINOR_VERSION (6)
define GTK_MICRO_VERSION (3)
define GTK_BINARY_AGE    (603)
define GTK_INTERFACE_AGE (3)

GTK_CHECK_VERSION macro major,minor,micro
  if (GTK_MAJOR_VERSION gt (major) or
      (GTK_MAJOR_VERSION eq (major) and GTK_MINOR_VERSION gt (minor)) or
      (GTK_MAJOR_VERSION eq (major) and GTK_MINOR_VERSION eq (minor) and
       GTK_MICRO_VERSION ge (micro)))
    exitm<1>
  else
    exitm<0>
  endif
  endm

gtk_get_major_version proto
gtk_get_minor_version proto
gtk_get_micro_version proto
gtk_get_binary_age proto
gtk_get_interface_age proto

gtk_check_version proto :guint, :guint, :guint

endif
