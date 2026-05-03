ifndef __G_INET_ADDRESS_MASK_H__
define __G_INET_ADDRESS_MASK_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_INET_ADDRESS_MASK         <g_inet_address_mask_get_type ()>
G_INET_ADDRESS_MASK macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_INET_ADDRESS_MASK, GInetAddressMask))>
  endm
G_INET_ADDRESS_MASK_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_INET_ADDRESS_MASK, GInetAddressMaskClass))>
  endm
G_IS_INET_ADDRESS_MASK macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_INET_ADDRESS_MASK))>
  endm
G_IS_INET_ADDRESS_MASK_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_INET_ADDRESS_MASK))>
  endm
G_INET_ADDRESS_MASK_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_INET_ADDRESS_MASK, GInetAddressMaskClass))>
  endm

GInetAddressMask        struct
parent_instance         GObject <>
priv                    ptr GInetAddressMaskPrivate ?
GInetAddressMask        ends

GInetAddressMaskClass   struct
parent_class            GObjectClass <>
GInetAddressMaskClass   ends

g_inet_address_mask_get_type proto
g_inet_address_mask_new proto :ptr, :guint, :ptr
g_inet_address_mask_new_from_string proto :ptr, :ptr
g_inet_address_mask_to_string proto :ptr
g_inet_address_mask_get_family proto :ptr
g_inet_address_mask_get_address proto :ptr
g_inet_address_mask_get_length proto :ptr
g_inet_address_mask_matches proto :ptr, :ptr
g_inet_address_mask_equal proto :ptr, :ptr

endif
