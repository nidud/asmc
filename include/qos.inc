ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;; This module defines the Quality of Service structures and types used
;; by Winsock applications.
;;
ifndef __QOS_H_
__QOS_H_ equ 1
;;
;;  Definitions for Service Type for each direction of data flow.
;;
SERVICETYPE		typedef ULONG
SERVICETYPE_NOTRAFFIC	equ 0x00000000	;; No data in this
;; direction
SERVICETYPE_BESTEFFORT	equ 0x00000001	;; Best Effort
SERVICETYPE_CONTROLLEDLOAD equ 0x00000002	;; Controlled Load
SERVICETYPE_GUARANTEED	equ 0x00000003	;; Guaranteed
SERVICETYPE_NETWORK_UNAVAILABLE equ 0x00000004	;; Used to notify
;; change to user
SERVICETYPE_GENERAL_INFORMATION equ 0x00000005	;; corresponds to
;; "General Parameters"
;; defined by IntServ
SERVICETYPE_NOCHANGE	equ 0x00000006	;; used to indicate
;; that the flow spec
;; contains no change
;; from any previous
;; one

;;
;; to turn on immediate traffic control, OR ( | ) this flag with the
;; ServiceType field in the FLOWSPEC
;;
SERVICE_IMMEDIATE_TRAFFIC_CONTROL equ 0x80000000

;;
;; this flag can be used with the immediate traffic control flag above to
;; prevent any rsvp signaling messages from being sent. Local traffic
;; control will be invoked, but no RSVP Path messages will be sent.This flag
;; can also be used in conjunction with a receiving flowspec to suppress
;; the automatic generation of a Reserve message.  The application would
;; receive notification that a Path  message had arrived and would then need
;; to alter the QOS by issuing WSAIoctl( SIO_SET_QOS ), to unset this flag
;; and thereby cause Reserve messages to go out.
;;
SERVICE_NO_QOS_SIGNALING equ 0x40000000

;;
;;  Flow Specifications for each direction of data flow.
;;
FLOWSPEC		STRUC
TokenRate		ULONG ? ;; In Bytes/sec
TokenBucketSize		ULONG ? ;; In Bytes
PeakBandwidth		ULONG ? ;; In Bytes/sec
Latency			ULONG ? ;; In microseconds
DelayVariation		ULONG ? ;; In microseconds
ServiceType		SERVICETYPE ?
MaxSduSize		ULONG ? ;; In Bytes
MinimumPolicedSize	ULONG ? ;; In Bytes

FLOWSPEC		ENDS
PFLOWSPEC		typedef ptr FLOWSPEC
LPFLOWSPEC		typedef ptr FLOWSPEC

;;
;; the provider specific structure can have a number of objects in it.
;; Each next structure in the
;; ProviderSpecific will be the QOS_OBJECT_HDR struct that prefaces the actual
;; data with a type and length for that object.	 This QOS_OBJECT struct can
;; repeat several times if there are several objects.  This list of objects
;; terminates either when the buffer length has been reached ( WSABUF ) or
;; an object of type QOS_END_OF_LIST is encountered.
;;

;;
;; define the type of objects that can go into the ProviderSpecific buffer
;; in the QOS structure
;;

QOS_OBJECT_HDR		STRUC

ObjectType		ULONG ?
ObjectLength		ULONG ? ;; the length of object buffer INCLUDING
;; this header

QOS_OBJECT_HDR		ENDS
LPQOS_OBJECT_HDR	typedef ptr QOS_OBJECT_HDR

;;
;; Definition of object Types
;;
;;
;; define the values for ObjectType above - RSVP Objects ids start at an
;; offset from zero to allow for ATM objects that might be defined in the
;; lower number range.
;;
RSVP_OBJECT_ID_BASE	equ 1000
RSVP_OBJECT_STATUS_INFO equ (0x00000000 + RSVP_OBJECT_ID_BASE)
;; RSVP_STATUS_INFO structure passed
RSVP_OBJECT_RESERVE_INFO equ (0x00000001 + RSVP_OBJECT_ID_BASE)
;; RSVP_RESERVE_INFO structure passed
RSVP_OBJECT_ADSPEC	equ (0x00000002 + RSVP_OBJECT_ID_BASE)
;; RSVP_ADSPEC structure passed

;;
;; general QOS objects start at this offset from the base and have a range
;; of 1000
;;
QOS_GENERAL_ID_BASE	equ 2000
QOS_OBJECT_PRIORITY	equ (0x00000000 + QOS_GENERA_ID_BASE)
;; QOS_PRIORITY structure passed
QOS_OBJECT_END_OF_LIST	equ (0x00000001 + QOS_GENERA_ID_BASE)
;; QOS_End_of_list structure passed
QOS_OBJECT_SD_MODE	equ (0x00000002 + QOS_GENERA_ID_BASE)
;; QOS_ShapeDiscard structure passed
QOS_OBJECT_TRAFFIC_CLASS equ (0x00000003 + QOS_GENERA_ID_BASE)
;; QOS_Traffic class structure passed

;;
;; this value can be used in the FLOWSPEC structure to instruct the Rsvp Service
;; provider to derive the appropriate default value for the parameter.	Note
;; that not all values in the FLOWSPEC structure can be defaults. In the
;; ReceivingFlowspec, all parameters can be defaulted except the ServiceType.
;; In the SendingFlowspec, the MaxSduSize and MinimumPolicedSize can be
;; defaulted. Other defaults may be possible. Refer to the appropriate
;; documentation.
;;
QOS_NOT_SPECIFIED	equ 0xFFFFFFFF

;;
;; define a value that can be used for the PeakBandwidth, which will map into
;; positive infinity when the FLOWSPEC is converted into IntServ floating point
;; format.  We can't use (-1) because that value was previously defined to mean
;; "select the default".
;;
POSITIVE_INFINITY_RATE	equ 0xFFFFFFFE

;;
;; IPV6 addressing for RSVP FILTERSPECS
;;
IN_ADDR_IPV4		UNION
_Addr			ULONG ?
AddrBytes		db 4 dup(?)
IN_ADDR_IPV4		ENDS
LPIN_ADDR_IPV4		typedef ptr IN_ADDR_IPV4

;;
;; IPV6 addressing for RSVP FILTERSPECS
;;
IN_ADDR_IPV6		STRUC
_Addr			db 16 dup(?)	;;IPV6 address
IN_ADDR_IPV6		ENDS
LPIN_ADDR_IPV6		typedef ptr IN_ADDR_IPV6
LPCIN_ADDR_IPV6		typedef ptr IN_ADDR_IPV6

;;
;; IPV4 addressing for RSVP FILTERSPECS
;;
RSVP_FILTERSPEC_V4	STRUC
Address			IN_ADDR_IPV4 <>
Unused			dw ?
Port			dw ?
RSVP_FILTERSPEC_V4	ENDS
LPRSVP_FILTERSPEC_V4	typedef ptr RSVP_FILTERSPEC_V4

RSVP_FILTERSPEC_V6	STRUC
Address			IN_ADDR_IPV6 <>
UnUsed			dw ?
Port			dw ?
RSVP_FILTERSPEC_V6	ENDS
LPRSVP_FILTERSPEC_V6	typedef ptr RSVP_FILTERSPEC_V6


RSVP_FILTERSPEC_V6_FLOW	 STRUC
Address			IN_ADDR_IPV6 <>
UnUsed			db ?
FlowLabel		db 3 dup(?)
RSVP_FILTERSPEC_V6_FLOW ENDS
LPRSVP_FILTERSPEC_V6_FLOW typedef ptr RSVP_FILTERSPEC_V6_FLOW

RSVP_FILTERSPEC_V4_GPI	STRUC
Address			IN_ADDR_IPV4 <>
GeneralPortId		dd ?
RSVP_FILTERSPEC_V4_GPI	ENDS
LPRSVP_FILTERSPEC_V4_GPI typedef ptr RSVP_FILTERSPEC_V4_GPI

RSVP_FILTERSPEC_V6_GPI	STRUC
Address			IN_ADDR_IPV6 <>
GeneralPortId		dd ?
RSVP_FILTERSPEC_V6_GPI	ENDS
LPRSVP_FILTERSPEC_V6_GPI typedef ptr RSVP_FILTERSPEC_V6_GPI


;;
;; FILTERSPEC TYPES used in making reservations.
;;
FilterType		typedef LONG
FILTERSPECV4		equ 1
FILTERSPECV6		equ 2
FILTERSPECV6_FLOW	equ 3
FILTERSPECV4_GPI	equ 4
FILTERSPECV6_GPI	equ 5
FILTERSPEC_END		equ 6

RSVP_FILTERSPEC		STRUC
FilterType		dd ?
UNION
 FilterSpecV4		RSVP_FILTERSPEC_V4 <>
 FilterSpecV6		RSVP_FILTERSPEC_V6 <>
 FilterSpecV6Flow	RSVP_FILTERSPEC_V6_FLOW <>
 FilterSpecV4Gpi	RSVP_FILTERSPEC_V4_GPI <>
 FilterSpecV6Gpi	RSVP_FILTERSPEC_V6_GPI <>
ENDS
RSVP_FILTERSPEC		ENDS
LPRSVP_FILTERSPEC	typedef ptr RSVP_FILTERSPEC

;;
;; FLOWDESCRIPTOR Structure used for specifying one or more
;; Filters per Flowspec.
;;
FLOWDESCRIPTOR		STRUC
FlowSpec		FLOWSPEC <>
NumFilters		dd ?
FilterList		LPRSVP_FILTERSPEC ?
FLOWDESCRIPTOR		ENDS
LPFLOWDESCRIPTOR	typedef ptr FLOWDESCRIPTOR

;;
;; RSVP_POLICY contains undefined policy data.	RSVP transports this
;; data on behalf of the Policy Control component.
;;
RSVP_POLICY		STRUC
_Type			HANDLE ?	;; Pointer to structure: TBD
RSVP_POLICY		ENDS
LPRSVP_POLICY		typedef ptr RSVP_POLICY
LPCRSVP_POLICY		typedef ptr RSVP_POLICY


;;
;; RSVP_RESERVE_INFO Structure used for storing RSVP specific
;; information for fine tuning interaction via the Winsock2
;; Generic QoS API via the provider specific buffer. This structure
;; includes the QOS_OBJECT_HDR structure directly
;;

RSVP_RESERVE_INFO	STRUC
ObjectHdr		QOS_OBJECT_HDR <>	;; type and length of this object
Style			dd ?			;; RSVP Style (FF,WF,SE)
ConfirmRequest		dd ?			;; Non Zero for Confirm Request
Policy			LPRSVP_POLICY ?		;; Optional policy data
NumFlowDesc		dd ?			;; Number of FlowDesc
FlowDescList		LPFLOWDESCRIPTOR ?	;; FlowDesc list
RSVP_RESERVE_INFO	ENDS
LPRSVP_RESERVE_INFO	typedef ptr RSVP_RESERVE_INFO
LPCRSVP_RESERVE_INFO	typedef ptr RSVP_RESERVE_INFO

;;
;; definitions for the ulStyle in the previous structure
;;
RSVP_WILDCARD_STYLE	equ 0x00000001
RSVP_FIXED_FILTER_STYLE equ 0x00000002
RSVP_SHARED_EXPLICIT_STYLE equ 0x00000003

;;
;; RSVP_STATUS_INFO Structure used for storing RSVP specific
;; error of status indications.	 This also serves as a header
;; for additional objects in the provider specific buffer when
;; interacting via Winsock2 Generic QoS API. This structure includes
;; the QOS_OBJECT_COUNT and QOS_OBJECT_HDR structures directly It is
;; expected to be the first structure in the provider specific structure
;; since it includes the QOS_OBJECT_COUNT
;;

RSVP_STATUS_INFO	STRUC
ObjectHdr		QOS_OBJECT_HDR <>	;; Object Hdr
StatusCode		dd ?	;; Error or Status Information see
				;; Winsock2.h
ExtendedStatus1		dd ?	;; Provider specific status extension
ExtendedStatus2		dd ?	;; Provider specific status extension
RSVP_STATUS_INFO	ENDS
LPRSVP_STATUS_INFO	typedef ptr RSVP_STATUS_INFO
LPCRSVP_STATUS_INFO	typedef ptr RSVP_STATUS_INFO

;;
;; This structure defines the absolute priorty of the flow.  Priorities in the
;; range of 0-7 are currently defined. Receive Priority is not currently used,
;; but may at some point in the future.
;;
QOS_PRIORITY		STRUC
ObjectHdr		QOS_OBJECT_HDR <>
SendPriority		db ?	;; this gets mapped to layer 2 priority.
SendFlags		db ?	;; there are none currently defined.
ReceivePriority		db ?	;; this could be used to decide who
;; gets forwarded up the stack first
;; - not used now
Unused			db ?
QOS_PRIORITY		ENDS
LPQOS_PRIORITY		typedef ptr QOS_PRIORITY


;;
;; This structure is used to define the behaviour that the traffic
;; control packet shaper will apply to the flow.
;;
;; PS_NONCONF_BORROW - the flow will receive resources remaining
;;  after all higher priority flows have been serviced. If a
;;  TokenRate is specified, packets may be non-conforming and
;;  will be demoted to less than best-effort priority.
;;
;; PS_NONCONF_SHAPE - TokenRate must be specified. Non-conforming
;;  packets will be retianed in the packet shaper until they become
;;  conforming.
;;
;; PS_NONCONF_DISCARD - TokenRate must be specified. Non-conforming
;;  packets will be discarded.
;;
;;


QOS_SD_MODE		STRUC
ObjectHdr		QOS_OBJECT_HDR <>
ShapeDiscardMode	dd ?
QOS_SD_MODE		ENDS
LPQOS_SD_MODE		typedef ptr QOS_SD_MODE

TC_NONCONF_BORROW	equ 0
TC_NONCONF_SHAPE	equ 1
TC_NONCONF_DISCARD	equ 2

;;
;; This structure may carry an 802.1 TrafficClass parameter which
;; has been provided to the host by a layer 2 network, for example,
;; in an 802.1 extended RSVP RESV message. If this object is obtained
;; from the network, hosts will stamp the MAC headers of corresponding
;; transmitted packets, with the value in the object. Otherwise, hosts
;; may select a value based on the standard Intserv mapping of
;; ServiceType to 802.1 TrafficClass.
;;
;;

QOS_TRAFFIC_CLASS	STRUC
ObjectHdr		QOS_OBJECT_HDR <>
TrafficClass		dd ?
QOS_TRAFFIC_CLASS	ENDS
LPQOS_TRAFFIC_CLASS	typedef ptr QOS_TRAFFIC_CLASS

;;
;; this structure defines the "General Characterization Parameters" contained in
;; the RSVP Adspec object
;;
AD_GENERAL_PARAMS	STRUC
IntServAwareHopCount	dd ?	;; number of hops that conform to
				;; Integrated Services requirements
PathBandwidthEstimate	dd ?	;; minimum bandwidth available from
				;; sender to receiver
MinimumLatency		dd ?	;; sum of minimum latency of the packet
				;; forwarding process in routers
				;; (in usec)
PathMTU			dd ?	;; max transmission unit end to end that
				;; will not incur fragmentation
Flags			dd ? ;; used to hold break bits.
AD_GENERAL_PARAMS	ENDS
LPAD_GENERAL_PARAMS	typedef ptr AD_GENERAL_PARAMS

;;
;; Minimum Latency may be set to this "undefined" value
;;
INDETERMINATE_LATENCY	equ 0xFFFFFFFF;

;;
;; This Flag is used to indicate the existence of a network element not
;; supporting  QoS control services somewhere in the data path. If this bit
;; is set in the specific service override then it indicates that that
;; service was not supported at at least one hop.
;;
AD_FLAG_BREAK_BIT	equ 0x00000001

;;
;; this structure describes the Guaranteed service parameters
;;
AD_GUARANTEED		STRUC
CTotal			dd ?
DTotal			dd ?
CSum			dd ?
DSum			dd ?
AD_GUARANTEED		ENDS
LPAD_GUARANTEED		typedef ptr AD_GUARANTEED

;;
;; this structure describes the format of the parameter buffer that can be
;; included in the Service_Type structure below.  This structure allows an
;; application to include any valid Int Serv service parameter in the Buffer
;; value, after providing the Int Serv parameter id in the ParameterId field.
;;
PARAM_BUFFER		STRUC
ParameterId		dd ?	;; Int Server parameter ID
_Length			dd ?	;; total length of this structure
				;; ( 8 bytes + length of Buffer )
Buffer			db ?	;; Paramter itself
PARAM_BUFFER		ENDS
LPPARAM_BUFFER		typedef ptr PARAM_BUFFER

;;
;; this structure contains the service types supported
;;
CONTROL_SERVICE		STRUC
;;
;; the length of this entire structure including the following buffer.
;; This length value can be added to the ptr to the structure to get the ptr
;; to the next SERVICE_TYPE structure in the list, until the
;; NumberOfServices count has been exhausted.
;;
_Length			dd ?
Service			SERVICETYPE ?
Overrides		AD_GENERAL_PARAMS <>
;;
;; service specific information ( controlled load has no service specific
;; info here )
;;
UNION
 Guaranteed		 AD_GUARANTEED <>
 ParamBuffer		 PARAM_BUFFER <> ;; allows for other services down the road
ENDS
CONTROL_SERVICE		ENDS
LPCONTROL_SERVICE	typedef ptr CONTROL_SERVICE

;;
;; This structure defines the information which is carried in the Rsvp
;; Adspec.  This Rsvp object typically indicates which service types are
;; available ( Controlled Load and/or Guaranteed Service ), if a non-Rsvp
;; hop has been encountered by the Path message, and the minumum MTU along
;; the path. The services array indicates which services are supported
;;
RSVP_ADSPEC		STRUC
ObjectHdr		QOS_OBJECT_HDR <>
GeneralParams		AD_GENERAL_PARAMS <>	;; contains the general
						;; characterization paramters
NumberOfServices	dd ?			;; count of the number of services
Services		CONTROL_SERVICE <>	;; a list of the services
;; supported/requested
RSVP_ADSPEC		ENDS
LPRSVP_ADSPEC		typedef ptr RSVP_ADSPEC

endif	;; __QOS_H_

.list
