ifndef __G_TLS_FILE_DATABASE_H__
define __G_TLS_FILE_DATABASE_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/giotypes.inc

define G_TYPE_TLS_FILE_DATABASE                <g_tls_file_database_get_type>
G_TLS_FILE_DATABASE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_CAST ((inst), G_TYPE_TLS_FILE_DATABASE, GTlsFileDatabase))>
  endm
G_IS_TLS_FILE_DATABASE macro inst
  exitm<(G_TYPE_CHECK_INSTANCE_TYPE ((inst), G_TYPE_TLS_FILE_DATABASE))>
  endm
G_TLS_FILE_DATABASE_GET_INTERFACE macro inst
  exitm<(G_TYPE_INSTANCE_GET_INTERFACE ((inst), G_TYPE_TLS_FILE_DATABASE, GTlsFileDatabaseInterface))>
  endm

_GTlsFileDatabaseInterface struct
g_iface                 GTypeInterface <>
padding                 gpointer 8 dup(?)
_GTlsFileDatabaseInterface ends
GTlsFileDatabaseInterface typedef _GTlsFileDatabaseInterface

g_tls_file_database_get_type proto
g_tls_file_database_new proto :ptr, :ptr

endif
