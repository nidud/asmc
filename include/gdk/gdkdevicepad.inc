ifndef __GDK_DEVICE_PAD_H__
define __GDK_DEVICE_PAD_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_DEVICE_PAD <gdk_device_pad_get_type ()>
GDK_DEVICE_PAD macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_DEVICE_PAD, GdkDevicePad))>
  endm
GDK_IS_DEVICE_PAD macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_DEVICE_PAD))>
  endm

.enum GdkDevicePadFeature {
  GDK_DEVICE_PAD_FEATURE_BUTTON,
  GDK_DEVICE_PAD_FEATURE_RING,
  GDK_DEVICE_PAD_FEATURE_STRIP
}

gdk_device_pad_get_type proto
gdk_device_pad_get_n_groups proto :ptr
gdk_device_pad_get_group_n_modes proto :ptr, :sdword
gdk_device_pad_get_n_features proto :ptr, :GdkDevicePadFeature
gdk_device_pad_get_feature_group proto :ptr, :GdkDevicePadFeature, :sdword

endif
