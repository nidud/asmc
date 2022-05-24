ifndef __GDK_CONTENT_PROVIDER_H__
define __GDK_CONTENT_PROVIDER_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

define GDK_TYPE_CONTENT_PROVIDER            <gdk_content_provider_get_type ()>
GDK_CONTENT_PROVIDER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_CONTENT_PROVIDER, GdkContentProvider))>
  endm
GDK_IS_CONTENT_PROVIDER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_CONTENT_PROVIDER))>
  endm
GDK_CONTENT_PROVIDER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_CONTENT_PROVIDER, GdkContentProviderClass))>
  endm
GDK_IS_CONTENT_PROVIDER_CLASS macro klass
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_CONTENT_PROVIDER))>
  endm
GDK_CONTENT_PROVIDER_GET_CLASS macro obj
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_CONTENT_PROVIDER, GdkContentProviderClass))>
  endm

_GdkContentProvider     struct
parent                  GObject <>
_GdkContentProvider     ends
GdkContentProvider      typedef _GdkContentProvider

_GdkContentProviderClass struct
parent_class            GObjectClass <>
content_changed         proc :ptr
attach_clipboard        proc :ptr, :ptr
detach_clipboard        proc :ptr, :ptr
ref_formats             proc :ptr
ref_storable_formats    proc :ptr
write_mime_type_async   proc :ptr, :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
write_mime_type_finish  proc :ptr, :ptr, :ptr
get_value               proc :ptr, :ptr, :ptr
padding                 gpointer 8 dup(?)
_GdkContentProviderClass ends
GdkContentProviderClass typedef _GdkContentProviderClass


gdk_content_provider_get_type proto
gdk_content_provider_ref_formats proto :ptr
gdk_content_provider_ref_storable_formats proto :ptr
gdk_content_provider_content_changed proto :ptr
gdk_content_provider_write_mime_type_async proto :ptr, :ptr, :ptr, :sdword, :ptr, :GAsyncReadyCallback, :gpointer
gdk_content_provider_write_mime_type_finish proto :ptr, :ptr, :ptr
gdk_content_provider_get_value proto :ptr, :ptr, :ptr

endif
