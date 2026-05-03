ifndef __GDK_PANGO_H__
define __GDK_PANGO_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

gdk_pango_layout_line_get_clip_region proto :ptr, :sdword, :sdword, :ptr, :sdword
gdk_pango_layout_get_clip_region proto :ptr, :sdword, :sdword, :ptr, :sdword

endif
