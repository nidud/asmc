ifndef __G_CONVERTER_H__
define __G_CONVERTER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_CONVERTER            <g_converter_get_type>
G_CONVERTER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_CONVERTER, GConverter))>
  endm
G_IS_CONVERTER macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_CONVERTER))>
  endm
G_CONVERTER_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_CONVERTER, GConverterIface))>
  endm


_GConverterIface        struct
g_iface                 GTypeInterface <>
convert                 proc :ptr, :ptr, :gsize, :ptr, :gsize, :GConverterFlags, :ptr, :ptr, :ptr
reset                   proc :ptr
_GConverterIface        ends
GConverterIface         typedef _GConverterIface

g_converter_get_type proto
g_converter_convert proto :ptr, :ptr, :gsize, :ptr, :gsize, :GConverterFlags, :ptr, :ptr, :ptr
g_converter_reset proto :ptr

endif
