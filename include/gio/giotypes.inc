ifndef __GIO_TYPES_H__
define __GIO_TYPES_H__

if not defined (__GIO_GIO_H_INSIDE__) and not defined (GIO_COMPILATION)
.err <"Only gio/gio.h can be included directly.">
endif

include gio/gioenums.inc


;GAppLaunchContext       typedef _GAppLaunchContext
;GAppInfo                typedef _GAppInfo
;GAsyncResult            typedef _GAsyncResult
;GAsyncInitable          typedef _GAsyncInitable
;GBufferedInputStream    typedef _GBufferedInputStream
;GBufferedOutputStream   typedef _GBufferedOutputStream
;GCancellable            typedef _GCancellable
;GCharsetConverter       typedef _GCharsetConverter
;GConverter              typedef _GConverter
;GConverterInputStream   typedef _GConverterInputStream
;GConverterOutputStream  typedef _GConverterOutputStream
;GDatagramBased          typedef _GDatagramBased
;GDataInputStream        typedef _GDataInputStream
;GSimplePermission       typedef _GSimplePermission
;GZlibCompressor         typedef _GZlibCompressor
;GZlibDecompressor       typedef _GZlibDecompressor

;GSimpleActionGroup      typedef _GSimpleActionGroup
;GRemoteActionGroup      typedef _GRemoteActionGroup
;GDBusActionGroup        typedef _GDBusActionGroup
;GActionMap              typedef _GActionMap
;GActionGroup            typedef _GActionGroup
;GPropertyAction         typedef _GPropertyAction
;GSimpleAction           typedef _GSimpleAction
;GAction                 typedef _GAction
;GApplication            typedef _GApplication
;GApplicationCommandLine typedef _GApplicationCommandLine
;GSettingsBackend        typedef _GSettingsBackend
;GSettings               typedef _GSettings
;GPermission             typedef _GPermission

;GMenuModel              typedef _GMenuModel
;GNotification           typedef _GNotification


;GDrive                  typedef _GDrive
;GFileEnumerator         typedef _GFileEnumerator
;GFileMonitor            typedef _GFileMonitor
;GFilterInputStream      typedef _GFilterInputStream
;GFilterOutputStream     typedef _GFilterOutputStream


;GFile                   typedef _GFile
;GFileInfo               typedef _GFileInfo


;GFileAttributeMatcher   typedef _GFileAttributeMatcher
;GFileAttributeInfo      typedef _GFileAttributeInfo
;GFileAttributeInfoList  typedef _GFileAttributeInfoList
;GFileDescriptorBased    typedef _GFileDescriptorBased
;GFileInputStream        typedef _GFileInputStream
;GFileOutputStream       typedef _GFileOutputStream
;GFileIOStream           typedef _GFileIOStream
;GFileIcon               typedef _GFileIcon
;GFilenameCompleter      typedef _GFilenameCompleter


;GIcon                   typedef _GIcon
;GInetAddress            typedef _GInetAddress
;GInetAddressMask        typedef _GInetAddressMask
;GInetSocketAddress      typedef _GInetSocketAddress
;GNativeSocketAddress    typedef _GNativeSocketAddress
;GInputStream            typedef _GInputStream
;GInitable               typedef _GInitable
;GIOModule               typedef _GIOModule
;GIOExtensionPoint       typedef _GIOExtensionPoint
;GIOExtension            typedef _GIOExtension


;GIOSchedulerJob         typedef _GIOSchedulerJob
;GIOStreamAdapter        typedef _GIOStreamAdapter
;GLoadableIcon           typedef _GLoadableIcon
;GBytesIcon              typedef _GBytesIcon
;GMemoryInputStream      typedef _GMemoryInputStream
;GMemoryOutputStream     typedef _GMemoryOutputStream


;GMount                  typedef _GMount
;GMountOperation         typedef _GMountOperation
;GNetworkAddress         typedef _GNetworkAddress
;GNetworkMonitor         typedef _GNetworkMonitor
;GNetworkService         typedef _GNetworkService
;GOutputStream           typedef _GOutputStream
;GIOStream               typedef _GIOStream
;GSimpleIOStream         typedef _GSimpleIOStream
;GPollableInputStream    typedef _GPollableInputStream
;GPollableOutputStream   typedef _GPollableOutputStream
;GResolver               typedef _GResolver


;GResource               typedef _GResource
;GSeekable               typedef _GSeekable
;GSimpleAsyncResult      typedef _GSimpleAsyncResult


;GSocket                 typedef _GSocket


;GSocketControlMessage   typedef _GSocketControlMessage

;GSocketClient           typedef _GSocketClient

;GSocketConnection       typedef _GSocketConnection

;GSocketListener         typedef _GSocketListener

;GSocketService          typedef _GSocketService
;GSocketAddress          typedef _GSocketAddress
;GSocketAddressEnumerator typedef _GSocketAddressEnumerator
;GSocketConnectable      typedef _GSocketConnectable
;GSrvTarget              typedef _GSrvTarget
;GTask                   typedef _GTask

;GTcpConnection          typedef _GTcpConnection
;GTcpWrapperConnection   typedef _GTcpWrapperConnection

;GThreadedSocketService  typedef _GThreadedSocketService
;GDtlsConnection         typedef _GDtlsConnection
;GDtlsClientConnection   typedef _GDtlsClientConnection
;GDtlsServerConnection   typedef _GDtlsServerConnection
;GThemedIcon             typedef _GThemedIcon
;GTlsCertificate         typedef _GTlsCertificate
;GTlsClientConnection    typedef _GTlsClientConnection
;GTlsConnection          typedef _GTlsConnection
;GTlsDatabase            typedef _GTlsDatabase
;GTlsFileDatabase        typedef _GTlsFileDatabase
;GTlsInteraction         typedef _GTlsInteraction
;GTlsPassword            typedef _GTlsPassword
;GTlsServerConnection    typedef _GTlsServerConnection
;GVfs                    typedef _GVfs


;GProxyResolver          typedef _GProxyResolver
;GProxy                  typedef _GProxy
;GProxyAddress           typedef _GProxyAddress
;GProxyAddressEnumerator typedef _GProxyAddressEnumerator


;GVolume                 typedef _GVolume
;GVolumeMonitor          typedef _GVolumeMonitor


CALLBACK(GAsyncReadyCallback, :ptr, :ptr, :gpointer)
CALLBACK(GFileProgressCallback, :goffset, :goffset, :gpointer)
CALLBACK(GFileReadMoreCallback, :ptr, :goffset, :gpointer)
CALLBACK(GFileMeasureProgressCallback, :gboolean, :guint64, :guint64, :guint64, :gpointer)
CALLBACK(GIOSchedulerJobFunc, :ptr, :ptr, :gpointer)
CALLBACK(GSimpleAsyncThreadFunc, :ptr, :ptr, :ptr)
CALLBACK(GSocketSourceFunc, :ptr, :GIOCondition, :gpointer)
CALLBACK(GDatagramBasedSourceFunc, :ptr, :GIOCondition, :gpointer)

_GInputVector           struct
buffer                  gpointer ?
size                    gsize ?
_GInputVector           ends
GInputVector            typedef _GInputVector

_GInputMessage          struct
address                 ptr GSocketAddress ?
vectors                 ptr GInputVector ?
num_vectors             guint ?
bytes_received          gsize ?
flags                   gint ?
control_messages        ptr GSocketControlMessage ?
num_control_messages    ptr guint ?
_GInputMessage          ends
GInputMessage           typedef _GInputMessage

_GOutputVector          struct
buffer                  gconstpointer ?
size                    gsize ?
_GOutputVector          ends
GOutputVector           typedef _GOutputVector


_GOutputMessage         struct
address                 ptr GSocketAddress ?
vectors                 ptr GOutputVector ?
num_vectors             guint ?
bytes_sent              guint ?
control_messages        ptr GSocketControlMessage ?
num_control_messages    guint ?
_GOutputMessage         ends
GOutputMessage          typedef _GOutputMessage

;GCredentials            typedef _GCredentials
;GUnixCredentialsMessage typedef _GUnixCredentialsMessage
;GUnixFDList             typedef _GUnixFDList
;GDBusMessage            typedef _GDBusMessage
;GDBusConnection         typedef _GDBusConnection
;GDBusProxy              typedef _GDBusProxy
;GDBusMethodInvocation   typedef _GDBusMethodInvocation
;GDBusServer             typedef _GDBusServer
;GDBusAuthObserver       typedef _GDBusAuthObserver
;GDBusErrorEntry         typedef _GDBusErrorEntry
;GDBusInterfaceVTable    typedef _GDBusInterfaceVTable
;GDBusSubtreeVTable      typedef _GDBusSubtreeVTable
;GDBusAnnotationInfo     typedef _GDBusAnnotationInfo
;GDBusArgInfo            typedef _GDBusArgInfo
;GDBusMethodInfo         typedef _GDBusMethodInfo
;GDBusSignalInfo         typedef _GDBusSignalInfo
;GDBusPropertyInfo       typedef _GDBusPropertyInfo
;GDBusInterfaceInfo      typedef _GDBusInterfaceInfo
;GDBusNodeInfo           typedef _GDBusNodeInfo


CALLBACK(GCancellableSourceFunc, :ptr, :gpointer)
CALLBACK(GPollableSourceFunc, :ptr, :gpointer)

;GDBusInterface          typedef _GDBusInterface
;GDBusInterfaceSkeleton  typedef _GDBusInterfaceSkeleton
;GDBusObject             typedef _GDBusObject
;GDBusObjectSkeleton     typedef _GDBusObjectSkeleton
;GDBusObjectProxy        typedef _GDBusObjectProxy
;GDBusObjectManager      typedef _GDBusObjectManager
;GDBusObjectManagerClient typedef _GDBusObjectManagerClient
;GDBusObjectManagerServer typedef _GDBusObjectManagerServer


CALLBACK(GDBusProxyTypeFunc, :ptr, :ptr, :ptr, :gpointer)

;GTestDBus               typedef _GTestDBus


;GSubprocess             typedef _GSubprocess

;GSubprocessLauncher     typedef _GSubprocessLauncher

endif
