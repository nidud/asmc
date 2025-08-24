ifndef _TCPESTATS_
define _TCPESTATS_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

.enum TCP_ESTATS_TYPE {
    TcpConnectionEstatsSynOpts,
    TcpConnectionEstatsData,
    TcpConnectionEstatsSndCong,
    TcpConnectionEstatsPath,
    TcpConnectionEstatsSendBuff,
    TcpConnectionEstatsRec,
    TcpConnectionEstatsObsRec,
    TcpConnectionEstatsBandwidth,
    TcpConnectionEstatsFineRtt,
    TcpConnectionEstatsMaximum,
    }

.enum TCP_BOOLEAN_OPTIONAL {
    TcpBoolOptDisabled = 0,
    TcpBoolOptEnabled,
    TcpBoolOptUnchanged = -1
    }

TCP_ESTATS_SYN_OPTS_ROS_v0 struct
ActiveOpen		BOOLEAN ?
MssRcvd			ULONG ?
MssSent			ULONG ?
TCP_ESTATS_SYN_OPTS_ROS_v0 ends
PTCP_ESTATS_SYN_OPTS_ROS_v0 typedef ptr TCP_ESTATS_SYN_OPTS_ROS_v0

.enum TCP_SOFT_ERROR {
    TcpErrorNone = 0,
    TcpErrorBelowDataWindow,
    TcpErrorAboveDataWindow,
    TcpErrorBelowAckWindow,
    TcpErrorAboveAckWindow,
    TcpErrorBelowTsWindow,
    TcpErrorAboveTsWindow,
    TcpErrorDataChecksumError,
    TcpErrorDataLengthError,
    TcpErrorMaxSoftError
    }

TCP_ESTATS_DATA_ROD_v0	struct
DataBytesOut		ULONG64 ?
DataSegsOut		ULONG64 ?
DataBytesIn		ULONG64 ?
DataSegsIn		ULONG64 ?
SegsOut			ULONG64 ?
SegsIn			ULONG64 ?
SoftErrors		ULONG ?
SoftErrorReason		ULONG ?
SndUna			ULONG ?
SndNxt			ULONG ?
SndMax			ULONG ?
ThruBytesAcked		ULONG64 ?
RcvNxt			ULONG ?
ThruBytesReceived	ULONG64 ?
TCP_ESTATS_DATA_ROD_v0	ends
PTCP_ESTATS_DATA_ROD_v0 typedef ptr TCP_ESTATS_DATA_ROD_v0

TCP_ESTATS_DATA_RW_v0	struct
EnableCollection	BOOLEAN ?
TCP_ESTATS_DATA_RW_v0	ends
PTCP_ESTATS_DATA_RW_v0	typedef ptr TCP_ESTATS_DATA_RW_v0

TCP_ESTATS_SND_CONG_ROD_v0 struct
SndLimTransRwin		ULONG ?
SndLimTimeRwin		ULONG ?
SndLimBytesRwin		size_t ?
SndLimTransCwnd		ULONG ?
SndLimTimeCwnd		ULONG ?
SndLimBytesCwnd		size_t ?
SndLimTransSnd		ULONG ?
SndLimTimeSnd		ULONG ?
SndLimBytesSnd		size_t ?
SlowStart		ULONG ?
CongAvoid		ULONG ?
OtherReductions		ULONG ?
CurCwnd			ULONG ?
MaxSsCwnd		ULONG ?
MaxCaCwnd		ULONG ?
CurSsthresh		ULONG ?
MaxSsthresh		ULONG ?
MinSsthresh		ULONG ?
TCP_ESTATS_SND_CONG_ROD_v0 ends
PTCP_ESTATS_SND_CONG_ROD_v0 typedef ptr TCP_ESTATS_SND_CONG_ROD_v0

TCP_ESTATS_SND_CONG_ROS_v0 struct
LimCwnd			ULONG ?
TCP_ESTATS_SND_CONG_ROS_v0 ends
PTCP_ESTATS_SND_CONG_ROS_v0 typedef ptr TCP_ESTATS_SND_CONG_ROS_v0

TCP_ESTATS_SND_CONG_RW_v0 struct
EnableCollection	BOOLEAN ?
TCP_ESTATS_SND_CONG_RW_v0 ends
PTCP_ESTATS_SND_CONG_RW_v0 typedef ptr TCP_ESTATS_SND_CONG_RW_v0

TCP_ESTATS_PATH_ROD_v0 struct
FastRetran		ULONG ?
Timeouts		ULONG ?
SubsequentTimeouts	ULONG ?
CurTimeoutCount		ULONG ?
AbruptTimeouts		ULONG ?
PktsRetrans		ULONG ?
BytesRetrans		ULONG ?
DupAcksIn		ULONG ?
SacksRcvd		ULONG ?
SackBlocksRcvd		ULONG ?
CongSignals		ULONG ?
PreCongSumCwnd		ULONG ?
PreCongSumRtt		ULONG ?
PostCongSumRtt		ULONG ?
PostCongCountRtt	ULONG ?
EcnSignals		ULONG ?
EceRcvd			ULONG ?
SendStall		ULONG ?
QuenchRcvd		ULONG ?
RetranThresh		ULONG ?
SndDupAckEpisodes	ULONG ?
SumBytesReordered	ULONG ?
NonRecovDa		ULONG ?
NonRecovDaEpisodes	ULONG ?
AckAfterFr		ULONG ?
DsackDups		ULONG ?
SampleRtt		ULONG ?
SmoothedRtt		ULONG ?
RttVar			ULONG ?
MaxRtt			ULONG ?
MinRtt			ULONG ?
SumRtt			ULONG ?
CountRtt		ULONG ?
CurRto			ULONG ?
MaxRto			ULONG ?
MinRto			ULONG ?
CurMss			ULONG ?
MaxMss			ULONG ?
MinMss			ULONG ?
SpuriousRtoDetections	ULONG ?
TCP_ESTATS_PATH_ROD_v0 ends
PTCP_ESTATS_PATH_ROD_v0 typedef ptr TCP_ESTATS_PATH_ROD_v0

TCP_ESTATS_PATH_RW_v0	struct
EnableCollection	BOOLEAN ?
TCP_ESTATS_PATH_RW_v0	ends
PTCP_ESTATS_PATH_RW_v0	typedef ptr TCP_ESTATS_PATH_RW_v0

TCP_ESTATS_SEND_BUFF_ROD_v0 struct
CurRetxQueue		size_t ?
MaxRetxQueue		size_t ?
CurAppWQueue		size_t ?
MaxAppWQueue		size_t ?
TCP_ESTATS_SEND_BUFF_ROD_v0 ends
PTCP_ESTATS_SEND_BUFF_ROD_v0 typedef ptr TCP_ESTATS_SEND_BUFF_ROD_v0

TCP_ESTATS_SEND_BUFF_RW_v0 struct
EnableCollection	BOOLEAN ?
TCP_ESTATS_SEND_BUFF_RW_v0 ends
PTCP_ESTATS_SEND_BUFF_RW_v0 typedef ptr TCP_ESTATS_SEND_BUFF_RW_v0

TCP_ESTATS_REC_ROD_v0	struct
CurRwinSent		ULONG ?
MaxRwinSent		ULONG ?
MinRwinSent		ULONG ?
LimRwin			ULONG ?
DupAckEpisodes		ULONG ?
DupAcksOut		ULONG ?
CeRcvd			ULONG ?
EcnSent			ULONG ?
EcnNoncesRcvd		ULONG ?
CurReasmQueue		ULONG ?
MaxReasmQueue		ULONG ?
CurAppRQueue		size_t ?
MaxAppRQueue		size_t ?
WinScaleSent		UCHAR ?
TCP_ESTATS_REC_ROD_v0	ends
PTCP_ESTATS_REC_ROD_v0	typedef ptr TCP_ESTATS_REC_ROD_v0

TCP_ESTATS_REC_RW_v0	struct
EnableCollection	BOOLEAN ?
TCP_ESTATS_REC_RW_v0	ends
PTCP_ESTATS_REC_RW_v0	typedef ptr TCP_ESTATS_REC_RW_v0

TCP_ESTATS_OBS_REC_ROD_v0 struct
CurRwinRcvd		ULONG ?
MaxRwinRcvd		ULONG ?
MinRwinRcvd		ULONG ?
WinScaleRcvd		UCHAR ?
TCP_ESTATS_OBS_REC_ROD_v0 ends
PTCP_ESTATS_OBS_REC_ROD_v0 typedef ptr TCP_ESTATS_OBS_REC_ROD_v0

TCP_ESTATS_OBS_REC_RW_v0 struct
EnableCollection	BOOLEAN ?
TCP_ESTATS_OBS_REC_RW_v0 ends
PTCP_ESTATS_OBS_REC_RW_v0 typedef ptr TCP_ESTATS_OBS_REC_RW_v0

TCP_ESTATS_BANDWIDTH_RW_v0 struct
EnableCollectionOutbound TCP_BOOLEAN_OPTIONAL ?
EnableCollectionInbound TCP_BOOLEAN_OPTIONAL ?
TCP_ESTATS_BANDWIDTH_RW_v0 ends
PTCP_ESTATS_BANDWIDTH_RW_v0 typedef ptr TCP_ESTATS_BANDWIDTH_RW_v0

TCP_ESTATS_BANDWIDTH_ROD_v0 struct
OutboundBandwidth	ULONG64 ?
InboundBandwidth	ULONG64 ?
OutboundInstability	ULONG64 ?
InboundInstability	ULONG64 ?
OutboundBandwidthPeaked BOOLEAN ?
InboundBandwidthPeaked	BOOLEAN ?
TCP_ESTATS_BANDWIDTH_ROD_v0 ends
PTCP_ESTATS_BANDWIDTH_ROD_v0 typedef ptr TCP_ESTATS_BANDWIDTH_ROD_v0

TCP_ESTATS_FINE_RTT_RW_v0 struct
EnableCollection	BOOLEAN ?
TCP_ESTATS_FINE_RTT_RW_v0 ends
PTCP_ESTATS_FINE_RTT_RW_v0 typedef ptr TCP_ESTATS_FINE_RTT_RW_v0

TCP_ESTATS_FINE_RTT_ROD_v0 struct
RttVar			ULONG ?
MaxRtt			ULONG ?
MinRtt			ULONG ?
SumRtt			ULONG ?
TCP_ESTATS_FINE_RTT_ROD_v0 ends
PTCP_ESTATS_FINE_RTT_ROD_v0 typedef ptr TCP_ESTATS_FINE_RTT_ROD_v0

endif

endif
