ifndef __GDK_SNAPSHOT_H__
define __GDK_SNAPSHOT_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdktypes.inc
include gdk/gdkversionmacros.inc

;GdkSnapshotClass        typedef _GdkSnapshotClass

define GDK_TYPE_SNAPSHOT <gdk_snapshot_get_type ()>

GDK_SNAPSHOT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_SNAPSHOT, GdkSnapshot))>
  endm
GDK_IS_SNAPSHOT macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_SNAPSHOT))>
  endm

gdk_snapshot_get_type proto

endif
