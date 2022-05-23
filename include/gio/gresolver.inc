ifndef __G_RESOLVER_H__
define __G_RESOLVER_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_RESOLVER         <g_resolver_get_type>
G_RESOLVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((o), G_TYPE_RESOLVER, GResolver))>
  endm
G_RESOLVER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_CAST((k), G_TYPE_RESOLVER, GResolverClass))>
  endm
G_IS_RESOLVER macro o
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((o), G_TYPE_RESOLVER))>
  endm
G_IS_RESOLVER_CLASS macro k
  exitm<(G_TYPE_CHECK_CLASS_TYPE ((k), G_TYPE_RESOLVER))>
  endm
G_RESOLVER_GET_CLASS macro o
  exitm<(G_TYPE_INSTANCE_GET_CLASS ((o), G_TYPE_RESOLVER, GResolverClass))>
  endm

;GResolverPrivate        typedef _GResolverPrivate

_GResolver              struct
parent_instance         GObject <>
priv                    ptr GResolverPrivate ?
_GResolver              ends
GResolver               typedef _GResolver


.enum GResolverNameLookupFlags {
  G_RESOLVER_NAME_LOOKUP_FLAGS_DEFAULT = 0,
  G_RESOLVER_NAME_LOOKUP_FLAGS_IPV4_ONLY = 1 shl 0,
  G_RESOLVER_NAME_LOOKUP_FLAGS_IPV6_ONLY = 1 shl 1,
}

_GResolverClass         struct
parent_class            GObjectClass <>
reload                  proc :ptr
lookup_by_name          proc :ptr, :ptr, :ptr, :ptr
lookup_by_name_async    proc :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
lookup_by_name_finish   proc :ptr, :ptr, :ptr
lookup_by_address       proc :ptr, :ptr, :ptr, :ptr
lookup_by_address_async proc :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
lookup_by_address_finish proc :ptr, :ptr, :ptr
lookup_service          proc :ptr, :ptr, :ptr, :ptr
lookup_service_async    proc :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
lookup_service_finish   proc :ptr, :ptr, :ptr
lookup_records          proc :ptr, :ptr, :GResolverRecordType, :ptr, :ptr
lookup_records_async    proc :ptr, :ptr, :GResolverRecordType, :ptr, :GAsyncReadyCallback, :gpointer
lookup_records_finish   proc :ptr, :ptr, :ptr
lookup_by_name_with_flags_async proc :ptr, :ptr, :GResolverNameLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
lookup_by_name_with_flags_finish proc :ptr, :ptr, :ptr
lookup_by_name_with_flags proc :ptr, :ptr, :GResolverNameLookupFlags, :ptr, :ptr
_GResolverClass         ends
GResolverClass          typedef _GResolverClass

g_resolver_get_type proto
g_resolver_get_default proto
g_resolver_set_default proto :ptr
g_resolver_lookup_by_name proto :ptr, :ptr, :ptr, :ptr
g_resolver_lookup_by_name_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_resolver_lookup_by_name_finish proto :ptr, :ptr, :ptr
g_resolver_lookup_by_name_with_flags_async proto :ptr, :ptr, :GResolverNameLookupFlags, :ptr, :GAsyncReadyCallback, :gpointer
g_resolver_lookup_by_name_with_flags_finish proto :ptr, :ptr, :ptr
g_resolver_lookup_by_name_with_flags proto :ptr, :ptr, :GResolverNameLookupFlags, :ptr, :ptr
g_resolver_free_addresses proto :ptr
g_resolver_lookup_by_address proto :ptr, :ptr, :ptr, :ptr
g_resolver_lookup_by_address_async proto :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_resolver_lookup_by_address_finish proto :ptr, :ptr, :ptr
g_resolver_lookup_service proto :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
g_resolver_lookup_service_async proto :ptr, :ptr, :ptr, :ptr, :ptr, :GAsyncReadyCallback, :gpointer
g_resolver_lookup_service_finish proto :ptr, :ptr, :ptr
g_resolver_lookup_records proto :ptr, :ptr, :GResolverRecordType, :ptr, :ptr
g_resolver_lookup_records_async proto :ptr, :ptr, :GResolverRecordType, :ptr, :GAsyncReadyCallback, :gpointer
g_resolver_lookup_records_finish proto :ptr, :ptr, :ptr
g_resolver_free_targets proto :ptr

define G_RESOLVER_ERROR <g_resolver_error_quark>
g_resolver_error_quark proto

endif
