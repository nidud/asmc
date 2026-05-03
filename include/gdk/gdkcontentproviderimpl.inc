ifndef __GDK_CONTENT_PROVIDER_IMPL_H__
define __GDK_CONTENT_PROVIDER_IMPL_H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkversionmacros.inc
include gdk/gdktypes.inc

gdk_content_provider_new_for_value proto :ptr
gdk_content_provider_new_typed proto :GType, :vararg
gdk_content_provider_new_union proto :ptr, :gsize
gdk_content_provider_new_for_bytes proto :ptr, :ptr

endif
