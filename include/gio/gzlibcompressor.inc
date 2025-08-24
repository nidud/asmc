ifndef __G_ZLIB_COMPRESSOR_H__
define __G_ZLIB_COMPRESSOR_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gconverter.inc
include gio/gfileinfo.inc

define G_TYPE_ZLIB_COMPRESSOR         <g_zlib_compressor_get_type ()>
G_ZLIB_COMPRESSOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_ZLIB_COMPRESSOR, GZlibCompressor))>
  endm
G_ZLIB_COMPRESSOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_ZLIB_COMPRESSOR, GZlibCompressorClass))>
  endm
G_IS_ZLIB_COMPRESSOR macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_ZLIB_COMPRESSOR))>
  endm
G_IS_ZLIB_COMPRESSOR_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_ZLIB_COMPRESSOR))>
  endm
G_ZLIB_COMPRESSOR_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_ZLIB_COMPRESSOR, GZlibCompressorClass))>
  endm

GZlibCompressorClass    struct
parent_class            GObjectClass <>
GZlibCompressorClass    ends

g_zlib_compressor_get_type proto
g_zlib_compressor_new proto :GZlibCompressorFormat, :sdword
g_zlib_compressor_get_file_info proto :ptr
g_zlib_compressor_set_file_info proto :ptr, :ptr

endif
