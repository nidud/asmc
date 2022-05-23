ifndef __G_CHARSET_CONVERTER_H__
define __G_CHARSET_CONVERTER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gconverter.inc

define G_TYPE_CHARSET_CONVERTER         <g_charset_converter_get_type>
G_CHARSET_CONVERTER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_CHARSET_CONVERTER, GCharsetConverter))>
  endm
G_CHARSET_CONVERTER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_CHARSET_CONVERTER, GCharsetConverterClass))>
  endm
G_IS_CHARSET_CONVERTER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_CHARSET_CONVERTER))>
  endm
G_IS_CHARSET_CONVERTER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_CHARSET_CONVERTER))>
  endm
G_CHARSET_CONVERTER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_CHARSET_CONVERTER, GCharsetConverterClass))>
  endm

_GCharsetConverterClass struct
parent_class            GObjectClass <>
_GCharsetConverterClass ends
GCharsetConverterClass  typedef _GCharsetConverterClass

g_charset_converter_get_type proto

g_charset_converter_new proto :ptr, :ptr, :ptr
g_charset_converter_set_use_fallback proto :ptr, :gboolean
g_charset_converter_get_use_fallback proto :ptr
g_charset_converter_get_num_fallbacks proto :ptr

endif
