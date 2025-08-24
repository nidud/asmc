ifndef __G_NETWORK_SERVICE_H__
define __G_NETWORK_SERVICE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_NETWORK_SERVICE         <g_network_service_get_type ()>
G_NETWORK_SERVICE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_NETWORK_SERVICE, GNetworkService))>
  endm
G_NETWORK_SERVICE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_NETWORK_SERVICE, GNetworkServiceClass))>
  endm
G_IS_NETWORK_SERVICE macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_NETWORK_SERVICE))>
  endm
G_IS_NETWORK_SERVICE_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_NETWORK_SERVICE))>
  endm
G_NETWORK_SERVICE_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_NETWORK_SERVICE, GNetworkServiceClass))>
  endm

GNetworkService         struct
parent_instance         GObject <>
priv                    ptr GNetworkServicePrivate ?
GNetworkService         ends

GNetworkServiceClass    struct
parent_class            GObjectClass <>
GNetworkServiceClass    ends

g_network_service_get_type proto
g_network_service_new proto :ptr, :ptr, :ptr
g_network_service_get_service proto :ptr
g_network_service_get_protocol proto :ptr
g_network_service_get_domain proto :ptr
g_network_service_get_scheme proto :ptr
g_network_service_set_scheme proto :ptr, :ptr

endif
