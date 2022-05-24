ifndef __G_ZLIB_DECOMPRESSOR_H__
define __G_ZLIB_DECOMPRESSOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gconverter.inc
include gio/gfileinfo.inc

define G_TYPE_ZLIB_DECOMPRESSOR         <g_zlib_decompressor_get_type ()>
G_ZLIB_DECOMPRESSOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_ZLIB_DECOMPRESSOR, GZlibDecompressor))>
  endm
G_ZLIB_DECOMPRESSOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_ZLIB_DECOMPRESSOR, GZlibDecompressorClass))>
  endm
G_IS_ZLIB_DECOMPRESSOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_ZLIB_DECOMPRESSOR))>
  endm
G_IS_ZLIB_DECOMPRESSOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_ZLIB_DECOMPRESSOR))>
  endm
G_ZLIB_DECOMPRESSOR_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_ZLIB_DECOMPRESSOR, GZlibDecompressorClass))>
  endm

_GZlibDecompressorClass struct
parent_class            GObjectClass <>
_GZlibDecompressorClass ends
GZlibDecompressorClass  typedef _GZlibDecompressorClass

g_zlib_decompressor_get_type proto
g_zlib_decompressor_new proto :GZlibCompressorFormat
g_zlib_decompressor_get_file_info proto :ptr


endif
