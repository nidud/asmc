ifndef __GDK_MEMORY_TEXTURE__H__
define __GDK_MEMORY_TEXTURE__H__

if not defined (__GDK_H_INSIDE__) and not defined (GTK_COMPILATION)
.err <"Only gdk/gdk.h can be included directly.">
endif

include gdk/gdkenums.inc
include gdk/gdktexture.inc

if G_BYTE_ORDER eq G_LITTLE_ENDIAN
define GDK_MEMORY_DEFAULT GDK_MEMORY_B8G8R8A8_PREMULTIPLIED
elseif G_BYTE_ORDER eq G_BIG_ENDIAN
define GDK_MEMORY_DEFAULT GDK_MEMORY_A8R8G8B8_PREMULTIPLIED
else
.err <"Unknown byte order for GDK_MEMORY_DEFAULT">
endif

define GDK_TYPE_MEMORY_TEXTURE <gdk_memory_texture_get_type ()>

GDK_MEMORY_TEXTURE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDK_TYPE_MEMORY_TEXTURE, GdkMemoryTexture))>
  endm
GDK_IS_MEMORY_TEXTURE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDK_TYPE_MEMORY_TEXTURE))>
  endm

;GdkMemoryTexture        typedef _GdkMemoryTexture
;GdkMemoryTextureClass   typedef _GdkMemoryTextureClass

gdk_memory_texture_get_type proto
gdk_memory_texture_new proto :sdword, :sdword, :GdkMemoryFormat, :ptr, :gsize

endif
