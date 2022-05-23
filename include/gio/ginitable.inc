ifndef __G_INITABLE_H__
define __G_INITABLE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_INITABLE            <g_initable_get_type>
G_INITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((obj), G_TYPE_INITABLE, GInitable))>
  endm
G_IS_INITABLE macro obj
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((obj), G_TYPE_INITABLE))>
  endm
G_INITABLE_GET_IFACE macro obj
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((obj), G_TYPE_INITABLE, GInitableIface))>
  endm
G_TYPE_IS_INITABLE macro type
  exitm<<g_type_is_a>ype), G_TYPE_INITABLE))>
  endm


_GInitableIface         struct
g_iface                 GTypeInterface <>
init                    proc :ptr, :ptr, :ptr
_GInitableIface         ends
GInitableIface          typedef _GInitableIface


g_initable_get_type proto
g_initable_init proto :ptr, :ptr, :ptr
g_initable_new proto :GType, :ptr, :ptr, :ptr, :vararg

g_initable_newv proto :GType, :guint, :ptr, :ptr, :ptr
g_initable_new_valist proto :GType, :ptr, :va_list, :ptr, :ptr

endif
