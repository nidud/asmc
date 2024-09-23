ifndef _LMSTATS_
define _LMSTATS_

include lmcons.inc

NetStatisticsGet proto WINAPI :LPTSTR, :LPTSTR, :DWORD, :DWORD, :ptr

ifdef LM20_WORKSTATION_STATISTICS
STAT_WORKSTATION_0	STRUC
stw0_start		dd ?
stw0_numNCB_r		dd ?
stw0_numNCB_s		dd ?
stw0_numNCB_a		dd ?
stw0_fiNCB_r		dd ?
stw0_fiNCB_s		dd ?
stw0_fiNCB_a		dd ?
stw0_fcNCB_r		dd ?
stw0_fcNCB_s		dd ?
stw0_fcNCB_a		dd ?
stw0_sesstart		dd ?
stw0_sessfailcon	dd ?
stw0_sessbroke		dd ?
stw0_uses		dd ?
stw0_usefail		dd ?
stw0_autorec		dd ?
stw0_bytessent_r_lo	dd ?
stw0_bytessent_r_hi	dd ?
stw0_bytesrcvd_r_lo	dd ?
stw0_bytesrcvd_r_hi	dd ?
stw0_bytessent_s_lo	dd ?
stw0_bytessent_s_hi	dd ?
stw0_bytesrcvd_s_lo	dd ?
stw0_bytesrcvd_s_hi	dd ?
stw0_bytessent_a_lo	dd ?
stw0_bytessent_a_hi	dd ?
stw0_bytesrcvd_a_lo	dd ?
stw0_bytesrcvd_a_hi	dd ?
stw0_reqbufneed		dd ?
stw0_bigbufneed		dd ?
STAT_WORKSTATION_0	ENDS
PSTAT_WORKSTATION_0	typedef ptr STAT_WORKSTATION_0
LPSTAT_WORKSTATION_0	typedef ptr STAT_WORKSTATION_0
else

STAT_WORKSTATION_0	STRUC
StatisticsStartTime	LARGE_INTEGER <>
BytesReceived		LARGE_INTEGER <>
SmbsReceived		LARGE_INTEGER <>
PagingReadBytesRequested LARGE_INTEGER <>
NonPagingReadBytesRequested LARGE_INTEGER <>
CacheReadBytesRequested LARGE_INTEGER <>
NetworkReadBytesRequested LARGE_INTEGER <>
BytesTransmitted	LARGE_INTEGER <>
SmbsTransmitted		LARGE_INTEGER <>
PagingWriteBytesRequested LARGE_INTEGER <>
NonPagingWriteBytesRequested LARGE_INTEGER <>
CacheWriteBytesRequested LARGE_INTEGER <>
NetworkWriteBytesRequested LARGE_INTEGER <>
InitiallyFailedOperations dd ?
FailedCompletionOperations dd ?
ReadOperations		dd ?
RandomReadOperations	dd ?
ReadSmbs		dd ?
LargeReadSmbs		dd ?
SmallReadSmbs		dd ?
WriteOperations		dd ?
RandomWriteOperations	dd ?
WriteSmbs		dd ?
LargeWriteSmbs		dd ?
SmallWriteSmbs		dd ?
RawReadsDenied		dd ?
RawWritesDenied		dd ?
NetworkErrors		dd ?
Sessions		dd ?
FailedSessions		dd ?
Reconnects		dd ?
CoreConnects		dd ?
Lanman20Connects	dd ?
Lanman21Connects	dd ?
LanmanNtConnects	dd ?
ServerDisconnects	dd ?
HungSessions		dd ?
UseCount		dd ?
FailedUseCount		dd ?
CurrentCommands		dd ?
STAT_WORKSTATION_0	ENDS
PSTAT_WORKSTATION_0	typedef ptr STAT_WORKSTATION_0
LPSTAT_WORKSTATION_0	typedef ptr STAT_WORKSTATION_0
endif

STAT_SERVER_0		STRUC
sts0_start		dd ?
sts0_fopens		dd ?
sts0_devopens		dd ?
sts0_jobsqueued		dd ?
sts0_sopens		dd ?
sts0_stimedout		dd ?
sts0_serrorout		dd ?
sts0_pwerrors		dd ?
sts0_permerrors		dd ?
sts0_syserrors		dd ?
sts0_bytessent_low	dd ?
sts0_bytessent_high	dd ?
sts0_bytesrcvd_low	dd ?
sts0_bytesrcvd_high	dd ?
sts0_avresponse		dd ?
sts0_reqbufneed		dd ?
sts0_bigbufneed		dd ?
STAT_SERVER_0		ENDS
PSTAT_SERVER_0		typedef ptr STAT_SERVER_0
LPSTAT_SERVER_0		typedef ptr STAT_SERVER_0

STATSOPT_CLR		equ 1
STATS_NO_VALUE		equ (-1)
STATS_OVERFLOW		equ (-2)

endif ;; _LMSTATS.H
