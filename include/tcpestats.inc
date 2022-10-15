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

_TCP_ESTATS_SYN_OPTS_ROS_v0 struct
ActiveOpen              BOOLEAN ?
MssRcvd                 ULONG ?
MssSent                 ULONG ?
_TCP_ESTATS_SYN_OPTS_ROS_v0 ends
TCP_ESTATS_SYN_OPTS_ROS_v0 typedef _TCP_ESTATS_SYN_OPTS_ROS_v0
PTCP_ESTATS_SYN_OPTS_ROS_v0 typedef ptr _TCP_ESTATS_SYN_OPTS_ROS_v0

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

_TCP_ESTATS_DATA_ROD_v0 struct
DataBytesOut            ULONG64 ?
DataSegsOut             ULONG64 ?
DataBytesIn             ULONG64 ?
DataSegsIn              ULONG64 ?
SegsOut                 ULONG64 ?
SegsIn                  ULONG64 ?
SoftErrors              ULONG ?
SoftErrorReason         ULONG ?
SndUna                  ULONG ?
SndNxt                  ULONG ?
SndMax                  ULONG ?
ThruBytesAcked          ULONG64 ?
RcvNxt                  ULONG ?
ThruBytesReceived       ULONG64 ?
_TCP_ESTATS_DATA_ROD_v0 ends
TCP_ESTATS_DATA_ROD_v0  typedef _TCP_ESTATS_DATA_ROD_v0
PTCP_ESTATS_DATA_ROD_v0 typedef ptr _TCP_ESTATS_DATA_ROD_v0

_TCP_ESTATS_DATA_RW_v0  struct
EnableCollection        BOOLEAN ?
_TCP_ESTATS_DATA_RW_v0  ends
TCP_ESTATS_DATA_RW_v0   typedef _TCP_ESTATS_DATA_RW_v0
PTCP_ESTATS_DATA_RW_v0  typedef ptr _TCP_ESTATS_DATA_RW_v0

_TCP_ESTATS_SND_CONG_ROD_v0 struct
SndLimTransRwin         ULONG ?
SndLimTimeRwin          ULONG ?
SndLimBytesRwin         SIZE_T ?
SndLimTransCwnd         ULONG ?
SndLimTimeCwnd          ULONG ?
SndLimBytesCwnd         SIZE_T ?
SndLimTransSnd          ULONG ?
SndLimTimeSnd           ULONG ?
SndLimBytesSnd          SIZE_T ?
SlowStart               ULONG ?
CongAvoid               ULONG ?
OtherReductions         ULONG ?
CurCwnd                 ULONG ?
MaxSsCwnd               ULONG ?
MaxCaCwnd               ULONG ?
CurSsthresh             ULONG ?
MaxSsthresh             ULONG ?
MinSsthresh             ULONG ?
_TCP_ESTATS_SND_CONG_ROD_v0 ends
TCP_ESTATS_SND_CONG_ROD_v0 typedef _TCP_ESTATS_SND_CONG_ROD_v0
PTCP_ESTATS_SND_CONG_ROD_v0 typedef ptr _TCP_ESTATS_SND_CONG_ROD_v0

_TCP_ESTATS_SND_CONG_ROS_v0 struct
LimCwnd                 ULONG ?
_TCP_ESTATS_SND_CONG_ROS_v0 ends
TCP_ESTATS_SND_CONG_ROS_v0 typedef _TCP_ESTATS_SND_CONG_ROS_v0
PTCP_ESTATS_SND_CONG_ROS_v0 typedef ptr _TCP_ESTATS_SND_CONG_ROS_v0

_TCP_ESTATS_SND_CONG_RW_v0 struct
EnableCollection        BOOLEAN ?
_TCP_ESTATS_SND_CONG_RW_v0 ends
TCP_ESTATS_SND_CONG_RW_v0 typedef _TCP_ESTATS_SND_CONG_RW_v0
PTCP_ESTATS_SND_CONG_RW_v0 typedef ptr _TCP_ESTATS_SND_CONG_RW_v0

_TCP_ESTATS_PATH_ROD_v0 struct
FastRetran              ULONG ?
Timeouts                ULONG ?
SubsequentTimeouts      ULONG ?
CurTimeoutCount         ULONG ?
AbruptTimeouts          ULONG ?
PktsRetrans             ULONG ?
BytesRetrans            ULONG ?
DupAcksIn               ULONG ?
SacksRcvd               ULONG ?
SackBlocksRcvd          ULONG ?
CongSignals             ULONG ?
PreCongSumCwnd          ULONG ?
PreCongSumRtt           ULONG ?
PostCongSumRtt          ULONG ?
PostCongCountRtt        ULONG ?
EcnSignals              ULONG ?
EceRcvd                 ULONG ?
SendStall               ULONG ?
QuenchRcvd              ULONG ?
RetranThresh            ULONG ?
SndDupAckEpisodes       ULONG ?
SumBytesReordered       ULONG ?
NonRecovDa              ULONG ?
NonRecovDaEpisodes      ULONG ?
AckAfterFr              ULONG ?
DsackDups               ULONG ?
SampleRtt               ULONG ?
SmoothedRtt             ULONG ?
RttVar                  ULONG ?
MaxRtt                  ULONG ?
MinRtt                  ULONG ?
SumRtt                  ULONG ?
CountRtt                ULONG ?
CurRto                  ULONG ?
MaxRto                  ULONG ?
MinRto                  ULONG ?
CurMss                  ULONG ?
MaxMss                  ULONG ?
MinMss                  ULONG ?
SpuriousRtoDetections   ULONG ?
_TCP_ESTATS_PATH_ROD_v0 ends
TCP_ESTATS_PATH_ROD_v0  typedef _TCP_ESTATS_PATH_ROD_v0
PTCP_ESTATS_PATH_ROD_v0 typedef ptr _TCP_ESTATS_PATH_ROD_v0

_TCP_ESTATS_PATH_RW_v0  struct
EnableCollection        BOOLEAN ?
_TCP_ESTATS_PATH_RW_v0  ends
TCP_ESTATS_PATH_RW_v0   typedef _TCP_ESTATS_PATH_RW_v0
PTCP_ESTATS_PATH_RW_v0  typedef ptr _TCP_ESTATS_PATH_RW_v0

_TCP_ESTATS_SEND_BUFF_ROD_v0 struct
CurRetxQueue            SIZE_T ?
MaxRetxQueue            SIZE_T ?
CurAppWQueue            SIZE_T ?
MaxAppWQueue            SIZE_T ?
_TCP_ESTATS_SEND_BUFF_ROD_v0 ends
TCP_ESTATS_SEND_BUFF_ROD_v0 typedef _TCP_ESTATS_SEND_BUFF_ROD_v0
PTCP_ESTATS_SEND_BUFF_ROD_v0 typedef ptr _TCP_ESTATS_SEND_BUFF_ROD_v0

_TCP_ESTATS_SEND_BUFF_RW_v0 struct
EnableCollection        BOOLEAN ?
_TCP_ESTATS_SEND_BUFF_RW_v0 ends
TCP_ESTATS_SEND_BUFF_RW_v0 typedef _TCP_ESTATS_SEND_BUFF_RW_v0
PTCP_ESTATS_SEND_BUFF_RW_v0 typedef ptr _TCP_ESTATS_SEND_BUFF_RW_v0

_TCP_ESTATS_REC_ROD_v0  struct
CurRwinSent             ULONG ?
MaxRwinSent             ULONG ?
MinRwinSent             ULONG ?
LimRwin                 ULONG ?
DupAckEpisodes          ULONG ?
DupAcksOut              ULONG ?
CeRcvd                  ULONG ?
EcnSent                 ULONG ?
EcnNoncesRcvd           ULONG ?
CurReasmQueue           ULONG ?
MaxReasmQueue           ULONG ?
CurAppRQueue            SIZE_T ?
MaxAppRQueue            SIZE_T ?
WinScaleSent            UCHAR ?
_TCP_ESTATS_REC_ROD_v0  ends
TCP_ESTATS_REC_ROD_v0   typedef _TCP_ESTATS_REC_ROD_v0
PTCP_ESTATS_REC_ROD_v0  typedef ptr _TCP_ESTATS_REC_ROD_v0

_TCP_ESTATS_REC_RW_v0   struct
EnableCollection        BOOLEAN ?
_TCP_ESTATS_REC_RW_v0   ends
TCP_ESTATS_REC_RW_v0    typedef _TCP_ESTATS_REC_RW_v0
PTCP_ESTATS_REC_RW_v0   typedef ptr _TCP_ESTATS_REC_RW_v0

_TCP_ESTATS_OBS_REC_ROD_v0 struct
CurRwinRcvd             ULONG ?
MaxRwinRcvd             ULONG ?
MinRwinRcvd             ULONG ?
WinScaleRcvd            UCHAR ?
_TCP_ESTATS_OBS_REC_ROD_v0 ends
TCP_ESTATS_OBS_REC_ROD_v0 typedef _TCP_ESTATS_OBS_REC_ROD_v0
PTCP_ESTATS_OBS_REC_ROD_v0 typedef ptr _TCP_ESTATS_OBS_REC_ROD_v0

_TCP_ESTATS_OBS_REC_RW_v0 struct
EnableCollection        BOOLEAN ?
_TCP_ESTATS_OBS_REC_RW_v0 ends
TCP_ESTATS_OBS_REC_RW_v0 typedef _TCP_ESTATS_OBS_REC_RW_v0
PTCP_ESTATS_OBS_REC_RW_v0 typedef ptr _TCP_ESTATS_OBS_REC_RW_v0

_TCP_ESTATS_BANDWIDTH_RW_v0 struct
EnableCollectionOutbound TCP_BOOLEAN_OPTIONAL ?
EnableCollectionInbound TCP_BOOLEAN_OPTIONAL ?
_TCP_ESTATS_BANDWIDTH_RW_v0 ends
TCP_ESTATS_BANDWIDTH_RW_v0 typedef _TCP_ESTATS_BANDWIDTH_RW_v0
PTCP_ESTATS_BANDWIDTH_RW_v0 typedef ptr _TCP_ESTATS_BANDWIDTH_RW_v0

_TCP_ESTATS_BANDWIDTH_ROD_v0 struct
OutboundBandwidth       ULONG64 ?
InboundBandwidth        ULONG64 ?
OutboundInstability     ULONG64 ?
InboundInstability      ULONG64 ?
OutboundBandwidthPeaked BOOLEAN ?
InboundBandwidthPeaked  BOOLEAN ?
_TCP_ESTATS_BANDWIDTH_ROD_v0 ends
TCP_ESTATS_BANDWIDTH_ROD_v0 typedef _TCP_ESTATS_BANDWIDTH_ROD_v0
PTCP_ESTATS_BANDWIDTH_ROD_v0 typedef ptr _TCP_ESTATS_BANDWIDTH_ROD_v0

_TCP_ESTATS_FINE_RTT_RW_v0 struct
EnableCollection        BOOLEAN ?
_TCP_ESTATS_FINE_RTT_RW_v0 ends
TCP_ESTATS_FINE_RTT_RW_v0 typedef _TCP_ESTATS_FINE_RTT_RW_v0
PTCP_ESTATS_FINE_RTT_RW_v0 typedef ptr _TCP_ESTATS_FINE_RTT_RW_v0

_TCP_ESTATS_FINE_RTT_ROD_v0 struct
RttVar                  ULONG ?
MaxRtt                  ULONG ?
MinRtt                  ULONG ?
SumRtt                  ULONG ?
_TCP_ESTATS_FINE_RTT_ROD_v0 ends
TCP_ESTATS_FINE_RTT_ROD_v0 typedef _TCP_ESTATS_FINE_RTT_ROD_v0
PTCP_ESTATS_FINE_RTT_ROD_v0 typedef ptr _TCP_ESTATS_FINE_RTT_ROD_v0

endif

endif
