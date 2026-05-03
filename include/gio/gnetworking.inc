ifndef __G_NETWORKING_H__
define __G_NETWORKING_H__

include glib.inc

ifdef G_OS_WIN32
include winsock2.inc
include ws2tcpip.inc
include windns.inc
include mswsock.inc
include wspiapi.inc
include iphlpapi.inc
undef interface

else

include sys/types.inc

include netdb.inc
include netinet/in.inc
include netinet/tcp.inc
include resolv.inc
include sys/socket.inc
include sys/un.inc
include net/if.inc

include arpa/inet.inc
include arpa/nameser.inc

ifndef T_SRV
define T_SRV 33
endif

ifndef _PATH_RESCONF
define _PATH_RESCONF <"/etc/resolv.conf">
endif

ifndef CMSG_LEN

CMSG_LEN macro len
  exitm<((size_t)CMSG_DATA((struct cmsghdr *)NULL) + (len))>
  endm


GLIB_ALIGN_TO_SIZEOF macro len, obj
  exitm<(((len) + sizeof (obj) - 1) & ~(sizeof (obj) - 1))>
  endm
CMSG_SPACE macro len
  exitm<GLIB_ALIGN_TO_SIZEOF (CMSG_LEN (len), struct cmsghdr)>
  endm
endif
endif

g_networking_init proto

endif
