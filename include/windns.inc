ifndef _WINDNS_INCLUDED_
_WINDNS_INCLUDED_ equ <>
.pragma list(push, 0)

ifndef _WINDEF_
 include windef.inc
endif

PQWORD			typedef ptr QWORD
DNS_STATUS		typedef SDWORD
PDNS_STATUS		typedef ptr DNS_STATUS
IP4_ADDRESS		typedef DWORD
PIP4_ADDRESS		typedef ptr DWORD

SIZEOF_IP4_ADDRESS	equ (4)
IP4_ADDRESS_STRING_LENGTH equ (16)
IP4_ADDRESS_STRING_BUFFER_LENGTH equ (16)

IP4_ARRAY		STRUC
AddrCount		dd ?
ifdef MIDL_PASS
AddrArray		IP4_ADDRESS [size_is(AddrCount)] dup(?)
else
AddrArray		IP4_ADDRESS 1 dup(?)
endif
IP4_ARRAY		ENDS
PIP4_ARRAY		typedef ptr IP4_ARRAY

ifdef MIDL_PASS

ifdef _WIN64
IP6_ADDRESS		STRUC 8
else
IP6_ADDRESS		STRUC 4
endif
IP6Qword		QWORD 2 dup(?)
IP6_ADDRESS		ENDS
PIP6_ADDRESS		typedef ptr IP6_ADDRESS

else ;; MIDL_PASS

IP6_ADDRESS		UNION
IP6Qword		dq 2 dup(?)
IP6Dword		dd 4 dup(?)
IP6Word			dw 8 dup(?)
IP6Byte			db 16 dup(?)
ifdef  IN6_ADDR
In6			IN6_ADDR ?
endif
IP6_ADDRESS		ENDS
PIP6_ADDRESS		typedef ptr IP6_ADDRESS

endif ;; MIDL_PASS

IP6_ADDRESS_STRING_LENGTH equ (65)
IP6_ADDRESS_STRING_BUFFER_LENGTH equ (65)

DNS_ADDRESS_STRING_LENGTH equ (IP6_ADDRESS_STRING_LENGTH)

INLINE_WORD_FLIP macro _out, _in
	mov ax,_in
	xchg al,ah
	exitm<mov _out,ax>
	endm
INLINE_HTONS macro _out, _in
	exitm<INLINE_WORD_FLIP(_out, _in)>
	endm
INLINE_NTOHS macro _out, _in
	exitm<INLINE_WORD_FLIP(_out, _in)>
	endm

INLINE_DWORD_FLIP macro _out, _in
	mov eax,_in
	bswap eax
	exitm<mov _out,eax>
	endm
INLINE_NTOHL macro out, in
	exitm<INLINE_DWORD_FLIP(_out, _in)>
	endm
INLINE_HTONL macro _out, _in
	exitm<INLINE_DWORD_FLIP(_out, _in)>
	endm

INLINE_WRITE_FLIPPED_WORD macro pout, _in
	exitm<INLINE_WORD_FLIP([pout], _in)>
	endm
INLINE_WRITE_FLIPPED_DWORD macro pout, _in
	exitm<INLINE_DWORD_FLIP([pout], _in)>
	endm

DNS_PORT_HOST_ORDER	equ 0x0035	;; port 53
DNS_PORT_NET_ORDER	equ 0x3500

DNS_RFC_MAX_UDP_PACKET_LENGTH equ 512

DNS_MAX_NAME_LENGTH	equ 255
DNS_MAX_LABEL_LENGTH	equ 63

DNS_MAX_NAME_BUFFER_LENGTH equ 256
DNS_MAX_LABEL_BUFFER_LENGTH equ 64

DNS_IP4_REVERSE_DOMAIN_STRING_A equ <"in-addr.arpa.">
DNS_IP4_REVERSE_DOMAIN_STRING_W equ <L"in-addr.arpa.">

DNS_MAX_IP4_REVERSE_NAME_LENGTH equ (IP4_ADDRESS_STRING_LENGTH+15)

DNS_IP6_REVERSE_DOMAIN_STRING_A equ <"ip6.arpa.">
DNS_IP6_REVERSE_DOMAIN_STRING_W equ <L"ip6.arpa.">

DNS_MAX_IP6_REVERSE_NAME_LENGTH equ 75

DNS_MAX_REVERSE_NAME_LENGTH equ DNS_MAX_IP6_REVERSE_NAME_LENGTH

ifdef _UNICODE
DNS_IP4_REVERSE_DOMAIN_STRING equ <DNS_IP4_REVERSE_DOMAIN_STRING_W>
DNS_IP6_REVERSE_DOMAIN_STRING equ <DNS_IP6_REVERSE_DOMAIN_STRING_W>
else
DNS_IP4_REVERSE_DOMAIN_STRING equ <DNS_IP4_REVERSE_DOMAIN_STRING_A>
DNS_IP6_REVERSE_DOMAIN_STRING equ <DNS_IP6_REVERSE_DOMAIN_STRING_A>
endif

DNS_MAX_IP4_REVERSE_NAME_BUFFER_LENGTH equ DNS_MAX_IP4_REVERSE_NAME_LENGTH
DNS_MAX_IP6_REVERSE_NAME_BUFFER_LENGTH equ DNS_MAX_IP6_REVERSE_NAME_LENGTH
DNS_MAX_REVERSE_NAME_BUFFER_LENGTH equ DNS_MAX_REVERSE_NAME_LENGTH

DNS_MAX_TEXT_STRING_LENGTH equ 255

.pragma pack(push, 1)

;;
;;  DNS Message Header
;;

DNS_HEADER		STRUC
Xid			dw ?

;RecursionDesired : 1	db ?
;Truncation : 1		db ?
;Authoritative : 1	db ?
;Opcode : 4		db ?
;IsResponse : 1		db ?
flag1			db ?

;ResponseCode : 4	db ?
;CheckingDisabled : 1	db ?
;AuthenticatedData : 1	db ?
;Reserved : 1		db ?
;RecursionAvailable : 1 db ?
flag2			db ?

QuestionCount		dw ?
AnswerCount		dw ?
NameServerCount		dw ?
AdditionalCount		dw ?
DNS_HEADER		ENDS
PDNS_HEADER		typedef ptr DNS_HEADER

DNS_HEADER_EXT		STRUC
;Reserved : 15		dw ?
;DnssecOk : 1		dw ?
flag1			dw ?
chRcode			db ?
chVersion		db ?
DNS_HEADER_EXT		ENDS
PDNS_HEADER_EXT		typedef ptr DNS_HEADER_EXT

DNS_HEADER_FLAGS macro pHead
	exitm<WORD PTR [pHead+2]>
	endm

DNS_BYTE_FLIP_HEADER_COUNTS macro pHeader
	exitm<.err>
	endm

DNS_OFFSET_TO_QUESTION_NAME equ sizeof(DNS_HEADER)
DNS_COMPRESSED_QUESTION_NAME equ 0xC00C

DNS_QUESTION_NAME_FROM_HEADER macro _pHeader_
	exitm<BYTE PTR [_pHeader_+1]>
	endm

DNS_ANSWER_FROM_QUESTION macro _pQuestion_
	exitm<BYTE PTR [_pQuestion_+1]>
	endm

DNS_WIRE_QUESTION	STRUC
QuestionType		dw ?
QuestionClass		dw ?
DNS_WIRE_QUESTION	ENDS
PDNS_WIRE_QUESTION	typedef ptr DNS_WIRE_QUESTION

DNS_WIRE_RECORD		STRUC
RecordType		dw ?
RecordClass		dw ?
TimeToLive		dd ?
DataLength		dw ?
DNS_WIRE_RECORD		ENDS
PDNS_WIRE_RECORD	typedef ptr DNS_WIRE_RECORD

.pragma pack(pop)

DNS_OPCODE_QUERY	equ 0
DNS_OPCODE_IQUERY	equ 1
DNS_OPCODE_SERVER_STATUS equ 2
DNS_OPCODE_UNKNOWN	equ 3
DNS_OPCODE_NOTIFY	equ 4
DNS_OPCODE_UPDATE	equ 5

DNS_RCODE_NOERROR	equ 0
DNS_RCODE_FORMERR	equ 1
DNS_RCODE_SERVFAIL	equ 2
DNS_RCODE_NXDOMAIN	equ 3
DNS_RCODE_NOTIMPL	equ 4
DNS_RCODE_REFUSED	equ 5
DNS_RCODE_YXDOMAIN	equ 6
DNS_RCODE_YXRRSET	equ 7
DNS_RCODE_NXRRSET	equ 8
DNS_RCODE_NOTAUTH	equ 9
DNS_RCODE_NOTZONE	equ 10
DNS_RCODE_MAX		equ 15

DNS_RCODE_BADVERS	equ 16
DNS_RCODE_BADSIG	equ 16
DNS_RCODE_BADKEY	equ 17
DNS_RCODE_BADTIME	equ 18

DNS_RCODE_NO_ERROR	equ DNS_RCODE_NOERROR
DNS_RCODE_FORMAT_ERROR	equ DNS_RCODE_FORMERR
DNS_RCODE_SERVER_FAILURE equ DNS_RCODE_SERVFAIL
DNS_RCODE_NAME_ERROR	equ DNS_RCODE_NXDOMAIN
DNS_RCODE_NOT_IMPLEMENTED equ DNS_RCODE_NOTIMPL

DNS_CLASS_INTERNET	equ 0x0001
DNS_CLASS_CSNET		equ 0x0002
DNS_CLASS_CHAOS		equ 0x0003
DNS_CLASS_HESIOD	equ 0x0004
DNS_CLASS_NONE		equ 0x00fe
DNS_CLASS_ALL		equ 0x00ff
DNS_CLASS_ANY		equ 0x00ff

DNS_RCLASS_INTERNET	equ 0x0100
DNS_RCLASS_CSNET	equ 0x0200
DNS_RCLASS_CHAOS	equ 0x0300
DNS_RCLASS_HESIOD	equ 0x0400
DNS_RCLASS_NONE		equ 0xfe00
DNS_RCLASS_ALL		equ 0xff00
DNS_RCLASS_ANY		equ 0xff00

DNS_TYPE_ZERO		equ 0x0000

DNS_TYPE_A		equ 0x0001
DNS_TYPE_NS		equ 0x0002
DNS_TYPE_MD		equ 0x0003
DNS_TYPE_MF		equ 0x0004
DNS_TYPE_CNAME		equ 0x0005
DNS_TYPE_SOA		equ 0x0006
DNS_TYPE_MB		equ 0x0007
DNS_TYPE_MG		equ 0x0008
DNS_TYPE_MR		equ 0x0009
DNS_TYPE_NULL		equ 0x000a
DNS_TYPE_WKS		equ 0x000b
DNS_TYPE_PTR		equ 0x000c
DNS_TYPE_HINFO		equ 0x000d
DNS_TYPE_MINFO		equ 0x000e
DNS_TYPE_MX		equ 0x000f
DNS_TYPE_TEXT		equ 0x0010

DNS_TYPE_RP		equ 0x0011
DNS_TYPE_AFSDB		equ 0x0012
DNS_TYPE_X25		equ 0x0013
DNS_TYPE_ISDN		equ 0x0014
DNS_TYPE_RT		equ 0x0015

DNS_TYPE_NSAP		equ 0x0016
DNS_TYPE_NSAPPTR	equ 0x0017
DNS_TYPE_SIG		equ 0x0018
DNS_TYPE_KEY		equ 0x0019
DNS_TYPE_PX		equ 0x001a
DNS_TYPE_GPOS		equ 0x001b
DNS_TYPE_AAAA		equ 0x001c
DNS_TYPE_LOC		equ 0x001d
DNS_TYPE_NXT		equ 0x001e
DNS_TYPE_EID		equ 0x001f
DNS_TYPE_NIMLOC		equ 0x0020
DNS_TYPE_SRV		equ 0x0021
DNS_TYPE_ATMA		equ 0x0022
DNS_TYPE_NAPTR		equ 0x0023
DNS_TYPE_KX		equ 0x0024
DNS_TYPE_CERT		equ 0x0025
DNS_TYPE_A6		equ 0x0026
DNS_TYPE_DNAME		equ 0x0027
DNS_TYPE_SINK		equ 0x0028
DNS_TYPE_OPT		equ 0x0029
DNS_TYPE_DS		equ 0x002b
DNS_TYPE_RRSIG		equ 0x002e
DNS_TYPE_NSEC		equ 0x002f
DNS_TYPE_DNSKEY		equ 0x0030
DNS_TYPE_DHCID		equ 0x0031

DNS_TYPE_UINFO		equ 0x0064
DNS_TYPE_UID		equ 0x0065
DNS_TYPE_GID		equ 0x0066
DNS_TYPE_UNSPEC		equ 0x0067

DNS_TYPE_ADDRS		equ 0x00f8
DNS_TYPE_TKEY		equ 0x00f9
DNS_TYPE_TSIG		equ 0x00fa
DNS_TYPE_IXFR		equ 0x00fb
DNS_TYPE_AXFR		equ 0x00fc
DNS_TYPE_MAILB		equ 0x00fd
DNS_TYPE_MAILA		equ 0x00fe
DNS_TYPE_ALL		equ 0x00ff
DNS_TYPE_ANY		equ 0x00ff

DNS_TYPE_WINS		equ 0xff01
DNS_TYPE_WINSR		equ 0xff02
DNS_TYPE_NBSTAT		equ (DNS_TYPE_WINSR)

DNS_RTYPE_A		equ 0x0100
DNS_RTYPE_NS		equ 0x0200
DNS_RTYPE_MD		equ 0x0300
DNS_RTYPE_MF		equ 0x0400
DNS_RTYPE_CNAME		equ 0x0500
DNS_RTYPE_SOA		equ 0x0600
DNS_RTYPE_MB		equ 0x0700
DNS_RTYPE_MG		equ 0x0800
DNS_RTYPE_MR		equ 0x0900
DNS_RTYPE_NULL		equ 0x0a00
DNS_RTYPE_WKS		equ 0x0b00
DNS_RTYPE_PTR		equ 0x0c00
DNS_RTYPE_HINFO		equ 0x0d00
DNS_RTYPE_MINFO		equ 0x0e00
DNS_RTYPE_MX		equ 0x0f00
DNS_RTYPE_TEXT		equ 0x1000
DNS_RTYPE_RP		equ 0x1100
DNS_RTYPE_AFSDB		equ 0x1200
DNS_RTYPE_X25		equ 0x1300
DNS_RTYPE_ISDN		equ 0x1400
DNS_RTYPE_RT		equ 0x1500
DNS_RTYPE_NSAP		equ 0x1600
DNS_RTYPE_NSAPPTR	equ 0x1700
DNS_RTYPE_SIG		equ 0x1800
DNS_RTYPE_KEY		equ 0x1900
DNS_RTYPE_PX		equ 0x1a00
DNS_RTYPE_GPOS		equ 0x1b00
DNS_RTYPE_AAAA		equ 0x1c00
DNS_RTYPE_LOC		equ 0x1d00
DNS_RTYPE_NXT		equ 0x1e00
DNS_RTYPE_EID		equ 0x1f00
DNS_RTYPE_NIMLOC	equ 0x2000
DNS_RTYPE_SRV		equ 0x2100
DNS_RTYPE_ATMA		equ 0x2200
DNS_RTYPE_NAPTR		equ 0x2300
DNS_RTYPE_KX		equ 0x2400
DNS_RTYPE_CERT		equ 0x2500
DNS_RTYPE_A6		equ 0x2600
DNS_RTYPE_DNAME		equ 0x2700
DNS_RTYPE_SINK		equ 0x2800
DNS_RTYPE_OPT		equ 0x2900

DNS_RTYPE_DS		equ 0x2b00
DNS_RTYPE_RRSIG		equ 0x2e00
DNS_RTYPE_NSEC		equ 0x2f00
DNS_RTYPE_DNSKEY	equ 0x3000
DNS_RTYPE_DHCID		equ 0x3100

DNS_RTYPE_UINFO		equ 0x6400
DNS_RTYPE_UID		equ 0x6500
DNS_RTYPE_GID		equ 0x6600
DNS_RTYPE_UNSPEC	equ 0x6700

DNS_RTYPE_TKEY		equ 0xf900
DNS_RTYPE_TSIG		equ 0xfa00
DNS_RTYPE_IXFR		equ 0xfb00
DNS_RTYPE_AXFR		equ 0xfc00
DNS_RTYPE_MAILB		equ 0xfd00
DNS_RTYPE_MAILA		equ 0xfe00
DNS_RTYPE_ALL		equ 0xff00
DNS_RTYPE_ANY		equ 0xff00

DNS_RTYPE_WINS		equ 0x01ff
DNS_RTYPE_WINSR		equ 0x02ff

ifndef	ATMA_E164
DNS_ATMA_FORMAT_E164	equ 1
DNS_ATMA_FORMAT_AESA	equ 2
DNS_ATMA_MAX_ADDR_LENGTH equ (20)
else
DNS_ATMA_FORMAT_E164	equ ATM_E164
DNS_ATMA_FORMAT_AESA	equ <ATM_AESA>
DNS_ATMA_MAX_ADDR_LENGTH equ ATM_ADDR_SIZE
endif

DNS_ATMA_AESA_ADDR_LENGTH equ (20)
DNS_ATMA_MAX_RECORD_LENGTH equ (DNS_ATMA_MAX_ADDR_LENGTH+1)

DNSSEC_ALGORITHM_RSAMD5 equ 1
DNSSEC_ALGORITHM_RSASHA1 equ 5
DNSSEC_ALGORITHM_NULL	equ 253
DNSSEC_ALGORITHM_PRIVATE equ 254

DNSSEC_PROTOCOL_NONE	equ 0
DNSSEC_PROTOCOL_TLS	equ 1
DNSSEC_PROTOCOL_EMAIL	equ 2
DNSSEC_PROTOCOL_DNSSEC	equ 3
DNSSEC_PROTOCOL_IPSEC	equ 4

DNSSEC_KEY_FLAG_NOAUTH	equ 0x0001
DNSSEC_KEY_FLAG_NOCONF	equ 0x0002
DNSSEC_KEY_FLAG_FLAG2	equ 0x0004
DNSSEC_KEY_FLAG_EXTEND	equ 0x0008
DNSSEC_KEY_FLAG_	equ 1
DNSSEC_KEY_FLAG_FLAG4	equ 0x0010
DNSSEC_KEY_FLAG_FLAG5	equ 0x0020

DNSSEC_KEY_FLAG_USER	equ 0x0000
DNSSEC_KEY_FLAG_ZONE	equ 0x0040
DNSSEC_KEY_FLAG_HOST	equ 0x0080
DNSSEC_KEY_FLAG_NTPE3	equ 0x00c0

DNSSEC_KEY_FLAG_FLAG8	equ 0x0100
DNSSEC_KEY_FLAG_FLAG9	equ 0x0200
DNSSEC_KEY_FLAG_FLAG10	equ 0x0400
DNSSEC_KEY_FLAG_FLAG11	equ 0x0800

DNSSEC_KEY_FLAG_SIG0	equ 0x0000
DNSSEC_KEY_FLAG_SIG1	equ 0x1000
DNSSEC_KEY_FLAG_SIG2	equ 0x2000
DNSSEC_KEY_FLAG_SIG3	equ 0x3000
DNSSEC_KEY_FLAG_SIG4	equ 0x4000
DNSSEC_KEY_FLAG_SIG5	equ 0x5000
DNSSEC_KEY_FLAG_SIG6	equ 0x6000
DNSSEC_KEY_FLAG_SIG7	equ 0x7000
DNSSEC_KEY_FLAG_SIG8	equ 0x8000
DNSSEC_KEY_FLAG_SIG9	equ 0x9000
DNSSEC_KEY_FLAG_SIG10	equ 0xa000
DNSSEC_KEY_FLAG_SIG11	equ 0xb000
DNSSEC_KEY_FLAG_SIG12	equ 0xc000
DNSSEC_KEY_FLAG_SIG13	equ 0xd000
DNSSEC_KEY_FLAG_SIG14	equ 0xe000
DNSSEC_KEY_FLAG_SIG15	equ 0xf000

DNS_TKEY_MODE_SERVER_ASSIGN equ 1
DNS_TKEY_MODE_DIFFIE_HELLMAN equ 2
DNS_TKEY_MODE_GSS	equ 3
DNS_TKEY_MODE_RESOLVER_ASSIGN equ 4

DNS_WINS_FLAG_SCOPE	equ (0x80000000)
DNS_WINS_FLAG_LOCAL	equ (0x00010000)

IS_WORD_ALIGNED macro p
	exitm<( NOT ((p) AND 1) )>
	endm
IS_DWORD_ALIGNED macro p
	exitm<( NOT ((p) AND 3) )>
	endm
IS_QWORD_ALIGNED macro p
	exitm<( NOT ((p) AND 7) )>
	endm

DnsConfigPrimaryDomainName_W equ 0
DnsConfigPrimaryDomainName_A equ 1
DnsConfigPrimaryDomainName_UTF8 equ 2
DnsConfigAdapterDomainName_W equ 3
DnsConfigAdapterDomainName_A equ 4
DnsConfigAdapterDomainName_UTF8 equ 5
DnsConfigDnsServerList	equ 6
DnsConfigSearchList	equ 7
DnsConfigAdapterInfo	equ 8
DnsConfigPrimaryHostNameRegistrationEnabled equ 9
DnsConfigAdapterHostNameRegistrationEnabled equ 10
DnsConfigAddressRegistrationMaxCount equ 11
DnsConfigHostName_W	equ 12
DnsConfigHostName_A	equ 13
DnsConfigHostName_UTF8	equ 14
DnsConfigFullHostName_W equ 15
DnsConfigFullHostName_A equ 16
DnsConfigFullHostName_UTF8 equ 17
DNS_CONFIG_TYPE		typedef SDWORD

DNS_CONFIG_FLAG_ALLOC	equ (0x00000001)

;DNS_STATUS
DnsQueryConfig proto WINAPI \
		Config: DNS_CONFIG_TYPE,
		  Flag: DWORD,
	pwsAdapterName: PCWSTR,
	     pReserved: PVOID,
	       pBuffer: PVOID,
	       pBufLen: PDWORD

DNS_A_DATA		STRUC
IpAddress		IP4_ADDRESS ?
DNS_A_DATA		ENDS
PDNS_A_DATA		typedef ptr DNS_A_DATA

DNS_PTR_DATAW		STRUC
pNameHost		PWSTR ?
DNS_PTR_DATAW		ENDS
PDNS_PTR_DATAW		typedef ptr DNS_PTR_DATAW

DNS_PTR_DATAA		STRUC
pNameHost		PSTR ?
DNS_PTR_DATAA		ENDS
PDNS_PTR_DATAA		typedef ptr DNS_PTR_DATAA

DNS_SOA_DATAW		STRUC
pNamePrimaryServer	PWSTR ?
pNameAdministrator	PWSTR ?
dwSerialNo		dd ?
dwRefresh		dd ?
dwRetry			dd ?
dwExpire		dd ?
dwDefaultTtl		dd ?
DNS_SOA_DATAW		ENDS
PDNS_SOA_DATAW		typedef ptr DNS_SOA_DATAW

DNS_SOA_DATAA		STRUC
pNamePrimaryServer	PSTR ?
pNameAdministrator	PSTR ?
dwSerialNo		dd ?
dwRefresh		dd ?
dwRetry			dd ?
dwExpire		dd ?
dwDefaultTtl		dd ?
DNS_SOA_DATAA		ENDS
PDNS_SOA_DATAA		typedef ptr DNS_SOA_DATAA

DNS_MINFO_DATAW		STRUC
pNameMailbox		PWSTR ?
pNameErrorsMailbox	PWSTR ?
DNS_MINFO_DATAW		ENDS
PDNS_MINFO_DATAW	typedef ptr DNS_MINFO_DATAW

DNS_MINFO_DATAA		STRUC
pNameMailbox		PSTR ?
pNameErrorsMailbox	PSTR ?
DNS_MINFO_DATAA		ENDS
PDNS_MINFO_DATAA	typedef ptr DNS_MINFO_DATAA

DNS_MX_DATAW		STRUC
pNameExchange		PWSTR ?
wPreference		dw ?
Pad			dw ?
DNS_MX_DATAW		ENDS
PDNS_MX_DATAW		typedef ptr DNS_MX_DATAW

DNS_MX_DATAA		STRUC
pNameExchange		PSTR ?
wPreference		dw ?
Pad			dw ?
DNS_MX_DATAA		ENDS
PDNS_MX_DATAA		typedef ptr DNS_MX_DATAA

DNS_TXT_DATAW		STRUC
dwStringCount		dd ?
ifdef MIDL_PASS
pStringArray		PWSTR [size_is(dwStringCount)] dup(?)
else
pStringArray		PWSTR 1 dup(?)
endif
DNS_TXT_DATAW		ENDS
PDNS_TXT_DATAW		typedef ptr DNS_TXT_DATAW

DNS_TXT_DATAA		STRUC
dwStringCount		dd ?
ifdef MIDL_PASS
pStringArray		PSTR [size_is(dwStringCount)] dup(?)
else
pStringArray		PSTR 1 dup(?)
endif
DNS_TXT_DATAA		ENDS
PDNS_TXT_DATAA		typedef ptr DNS_TXT_DATAA

DNS_NULL_DATA		STRUC
dwByteCount		dd ?
ifdef MIDL_PASS
Data			BYTE [size_is(dwByteCount)] dup(?)
else
Data			db 1 dup(?)
endif
DNS_NULL_DATA		ENDS
PDNS_NULL_DATA		typedef ptr DNS_NULL_DATA

DNS_WKS_DATA		STRUC
IpAddress		IP4_ADDRESS ?
chProtocol		UCHAR ?
BitMask			db 1 dup(?)
DNS_WKS_DATA		ENDS
PDNS_WKS_DATA		typedef ptr DNS_WKS_DATA

DNS_AAAA_DATA		STRUC
Ip6Address		IP6_ADDRESS <>
DNS_AAAA_DATA		ENDS
PDNS_AAAA_DATA		typedef ptr DNS_AAAA_DATA

DNS_SIG_DATAW		STRUC
wTypeCovered		dw ?
chAlgorithm		db ?
chLabelCount		db ?
dwOriginalTtl		dd ?
dwExpiration		dd ?
dwTimeSigned		dd ?
wKeyTag			dw ?
wSignatureLength	dw ?
pNameSigner		PWSTR ?
Signature		db 1 dup(?)
DNS_SIG_DATAW		ENDS
PDNS_SIG_DATAW		typedef ptr DNS_SIG_DATAW
DNS_RRSIG_DATAW		typedef DNS_SIG_DATAW
PDNS_RRSIG_DATAW	typedef ptr DNS_SIG_DATAW

DNS_SIG_DATAA		STRUC
wTypeCovered		dw ?
chAlgorithm		db ?
chLabelCount		db ?
dwOriginalTtl		dd ?
dwExpiration		dd ?
dwTimeSigned		dd ?
wKeyTag			dw ?
wSignatureLength	dw ?
pNameSigner		PSTR ?
Signature		db 1 dup(?)
DNS_SIG_DATAA		ENDS
PDNS_SIG_DATAA		typedef ptr DNS_SIG_DATAA
DNS_RRSIG_DATAA		typedef DNS_SIG_DATAA
PDNS_RRSIG_DATAA	typedef ptr DNS_SIG_DATAA

DNS_KEY_DATA		STRUC
wFlags			dw ?
chProtocol		db ?
chAlgorithm		db ?
wKeyLength		dw ?
wPad			dw ?	;; keep byte field aligned
Key			db 1 dup(?)
DNS_KEY_DATA		ENDS
PDNS_KEY_DATA		typedef ptr DNS_KEY_DATA
DNS_DNSKEY_DATA		typedef DNS_KEY_DATA
PDNS_DNSKEY_DATA	typedef ptr DNS_KEY_DATA

DNS_DHCID_DATA		STRUC
dwByteCount		dd ?
ifdef MIDL_PASS
DHCID			BYTE [size_is(dwByteCount)] dup(?)
else
DHCID			db 1 dup(?)
endif
DNS_DHCID_DATA		ENDS
PDNS_DHCID_DATA		typedef ptr DNS_DHCID_DATA

DNS_NSEC_DATAW		STRUC
pNextDomainName		PWSTR ?
wTypeBitMapsLength	dw ?
wPad			dw ?	;; keep byte field aligned
TypeBitMaps		db 1 dup(?)
DNS_NSEC_DATAW		ENDS
PDNS_NSEC_DATAW		typedef ptr DNS_NSEC_DATAW

DNS_NSEC_DATAA		STRUC
pNextDomainName		PSTR ?
wTypeBitMapsLength	dw ?
wPad			dw ?	;; keep byte field aligned
TypeBitMaps		db 1 dup(?)
DNS_NSEC_DATAA		ENDS
PDNS_NSEC_DATAA		typedef ptr DNS_NSEC_DATAA

DNS_DS_DATA		STRUC
wKeyTag			dw ?
chAlgorithm		db ?
chDigestType		db ?
wDigestLength		dw ?
wPad			dw ?	;; keep byte field aligned
Digest			db 1 dup(?)
DNS_DS_DATA		ENDS
PDNS_DS_DATA		typedef ptr DNS_DS_DATA

DNS_OPT_DATA		STRUC
wDataLength		dw ?
wPad			dw ?	;; keep byte field aligned
Data			db 1 dup(?)
DNS_OPT_DATA		ENDS
PDNS_OPT_DATA		typedef ptr DNS_OPT_DATA

DNS_LOC_DATA		STRUC
wVersion		dw ?
wSize			dw ?
wHorPrec		dw ?
wVerPrec		dw ?
dwLatitude		dd ?
dwLongitude		dd ?
dwAltitude		dd ?
DNS_LOC_DATA		ENDS
PDNS_LOC_DATA		typedef ptr DNS_LOC_DATA

DNS_NXT_DATAW		STRUC
pNameNext		PWSTR ?
wNumTypes		dw ?
wTypes			dw 1 dup(?)
DNS_NXT_DATAW		ENDS
PDNS_NXT_DATAW		typedef ptr DNS_NXT_DATAW

DNS_NXT_DATAA		STRUC
pNameNext		PSTR ?
wNumTypes		dw ?
wTypes			dw 1 dup(?)
DNS_NXT_DATAA		ENDS
PDNS_NXT_DATAA		typedef ptr DNS_NXT_DATAA

DNS_SRV_DATAW		STRUC
pNameTarget		PWSTR ?
wPriority		dw ?
wWeight			dw ?
wPort			dw ?
Pad			dw ?	;; keep ptrs DWORD aligned
DNS_SRV_DATAW		ENDS
PDNS_SRV_DATAW		typedef ptr DNS_SRV_DATAW

DNS_SRV_DATAA		STRUC
pNameTarget		PSTR ?
wPriority		dw ?
wWeight			dw ?
wPort			dw ?
Pad			dw ?	;; keep ptrs DWORD aligned
DNS_SRV_DATAA		ENDS
PDNS_SRV_DATAA		typedef ptr DNS_SRV_DATAA

DNS_NAPTR_DATAW		STRUC
wOrder			dw ?
wPreference		dw ?
pFlags			PWSTR ?
pService		PWSTR ?
pRegularExpression	PWSTR ?
pReplacement		PWSTR ?
DNS_NAPTR_DATAW		ENDS
PDNS_NAPTR_DATAW	typedef ptr DNS_NAPTR_DATAW

DNS_NAPTR_DATAA		STRUC
wOrder			dw ?
wPreference		dw ?
pFlags			PSTR ?
pService		PSTR ?
pRegularExpression	PSTR ?
pReplacement		PSTR ?
DNS_NAPTR_DATAA		ENDS
PDNS_NAPTR_DATAA	typedef ptr DNS_NAPTR_DATAA


DNS_ATMA_DATA		STRUC
AddressType		db ?
Address			db  DNS_ATMA_MAX_ADDR_LENGTH dup(?)
DNS_ATMA_DATA		ENDS
PDNS_ATMA_DATA		typedef ptr DNS_ATMA_DATA

DNS_TKEY_DATAW		STRUC
pNameAlgorithm		PWSTR ?
pAlgorithmPacket	PBYTE ?
pKey			PBYTE ?
pOtherData		PBYTE ?
dwCreateTime		dd ?
dwExpireTime		dd ?
wMode			dw ?
wError			dw ?
wKeyLength		dw ?
wOtherLength		dw ?
cAlgNameLength		UCHAR ?
bPacketPointers		BOOL ?
DNS_TKEY_DATAW		ENDS
PDNS_TKEY_DATAW		typedef ptr DNS_TKEY_DATAW

DNS_TKEY_DATAA		STRUC
pNameAlgorithm		PSTR ?
pAlgorithmPacket	PBYTE ?
pKey			PBYTE ?
pOtherData		PBYTE ?
dwCreateTime		dd ?
dwExpireTime		dd ?
wMode			dw ?
wError			dw ?
wKeyLength		dw ?
wOtherLength		dw ?
cAlgNameLength		UCHAR ?
bPacketPointers		BOOL ?
DNS_TKEY_DATAA		ENDS
PDNS_TKEY_DATAA		typedef ptr DNS_TKEY_DATAA

DNS_TSIG_DATAW		STRUC
pNameAlgorithm		PWSTR ?
pAlgorithmPacket	PBYTE ?
pSignature		PBYTE ?
pOtherData		PBYTE ?
i64CreateTime		LONGLONG ?
wFudgeTime		dw ?
wOriginalXid		dw ?
wError			dw ?
wSigLength		dw ?
wOtherLength		dw ?
cAlgNameLength		UCHAR ?
bPacketPointers		BOOL ?
DNS_TSIG_DATAW		ENDS
PDNS_TSIG_DATAW		typedef ptr DNS_TSIG_DATAW

DNS_TSIG_DATAA		STRUC
pNameAlgorithm		PSTR ?
pAlgorithmPacket	PBYTE ?
pSignature		PBYTE ?
pOtherData		PBYTE ?
i64CreateTime		LONGLONG ?
wFudgeTime		dw ?
wOriginalXid		dw ?
wError			dw ?
wSigLength		dw ?
wOtherLength		dw ?
cAlgNameLength		UCHAR ?
bPacketPointers		BOOL ?
DNS_TSIG_DATAA		ENDS
PDNS_TSIG_DATAA		typedef ptr DNS_TSIG_DATAA

DNS_WINS_DATA		STRUC
dwMappingFlag		dd ?
dwLookupTimeout		dd ?
dwCacheTimeout		dd ?
cWinsServerCount	dd ?
WinsServers		IP4_ADDRESS 1 dup(?)
DNS_WINS_DATA		ENDS
PDNS_WINS_DATA		typedef ptr DNS_WINS_DATA

DNS_WINSR_DATAW		STRUC
dwMappingFlag		dd ?
dwLookupTimeout		dd ?
dwCacheTimeout		dd ?
pNameResultDomain	PWSTR ?
DNS_WINSR_DATAW		ENDS
PDNS_WINSR_DATAW	typedef ptr DNS_WINSR_DATAW

DNS_WINSR_DATAA		STRUC
dwMappingFlag		dd ?
dwLookupTimeout		dd ?
dwCacheTimeout		dd ?
pNameResultDomain	PSTR ?
DNS_WINSR_DATAA		ENDS
PDNS_WINSR_DATAA	typedef ptr DNS_WINSR_DATAA

ifdef _UNICODE
DNS_PTR_DATA		typedef DNS_PTR_DATAW
DNS_SOA_DATA		typedef DNS_SOA_DATAW
DNS_MINFO_DATA		typedef DNS_MINFO_DATAW
DNS_MX_DATA		typedef DNS_MX_DATAW
DNS_TXT_DATA		typedef DNS_TXT_DATAW
DNS_SIG_DATA		typedef DNS_SIG_DATAW
DNS_NXT_DATA		typedef DNS_NXT_DATAW
DNS_SRV_DATA		typedef DNS_SRV_DATAW
DNS_NAPTR_DATA		typedef DNS_NAPTR_DATAW
DNS_RRSIG_DATA		typedef DNS_RRSIG_DATAW
DNS_NSEC_DATA		typedef DNS_NSEC_DATAW
DNS_TKEY_DATA		typedef DNS_TKEY_DATAW
DNS_TSIG_DATA		typedef DNS_TSIG_DATAW
DNS_WINSR_DATA		typedef DNS_WINSR_DATAW
PDNS_PTR_DATA		typedef ptr DNS_PTR_DATAW
PDNS_SOA_DATA		typedef ptr DNS_SOA_DATAW
PDNS_MINFO_DATA		typedef ptr DNS_MINFO_DATAW
PDNS_MX_DATA		typedef ptr DNS_MX_DATAW
PDNS_TXT_DATA		typedef ptr DNS_TXT_DATAW
PDNS_SIG_DATA		typedef ptr DNS_SIG_DATAW
PDNS_NXT_DATA		typedef ptr DNS_NXT_DATAW
PDNS_SRV_DATA		typedef ptr DNS_SRV_DATAW
PDNS_NAPTR_DATA		typedef ptr DNS_NAPTR_DATAW
PDNS_RRSIG_DATA		typedef ptr DNS_RRSIG_DATAW
PDNS_NSEC_DATA		typedef ptr DNS_NSEC_DATAW
PDNS_TKEY_DATA		typedef ptr DNS_TKEY_DATAW
PDNS_TSIG_DATA		typedef ptr DNS_TSIG_DATAW
PDNS_WINSR_DATA		typedef ptr DNS_WINSR_DATAW
else
DNS_PTR_DATA		typedef DNS_PTR_DATAA
DNS_SOA_DATA		typedef DNS_SOA_DATAA
DNS_MINFO_DATA		typedef DNS_MINFO_DATAA
DNS_MX_DATA		typedef DNS_MX_DATAA
DNS_TXT_DATA		typedef DNS_TXT_DATAA
DNS_SIG_DATA		typedef DNS_SIG_DATAA
DNS_NXT_DATA		typedef DNS_NXT_DATAA
DNS_SRV_DATA		typedef DNS_SRV_DATAA
DNS_NAPTR_DATA		typedef DNS_NAPTR_DATAA
DNS_RRSIG_DATA		typedef DNS_RRSIG_DATAA
DNS_NSEC_DATA		typedef DNS_NSEC_DATAA
DNS_TKEY_DATA		typedef DNS_TKEY_DATAA
DNS_TSIG_DATA		typedef DNS_TSIG_DATAA
DNS_WINSR_DATA		typedef DNS_WINSR_DATAA
PDNS_PTR_DATA		typedef ptr DNS_PTR_DATAA
PDNS_SOA_DATA		typedef ptr DNS_SOA_DATAA
PDNS_MINFO_DATA		typedef ptr DNS_MINFO_DATAA
PDNS_MX_DATA		typedef ptr DNS_MX_DATAA
PDNS_TXT_DATA		typedef ptr DNS_TXT_DATAA
PDNS_SIG_DATA		typedef ptr DNS_SIG_DATAA
PDNS_NXT_DATA		typedef ptr DNS_NXT_DATAA
PDNS_SRV_DATA		typedef ptr DNS_SRV_DATAA
PDNS_NAPTR_DATA		typedef ptr DNS_NAPTR_DATAA
PDNS_RRSIG_DATA		typedef ptr DNS_RRSIG_DATAA
PDNS_NSEC_DATA		typedef ptr DNS_NSEC_DATAA
PDNS_TKEY_DATA		typedef ptr DNS_TKEY_DATAA
PDNS_TSIG_DATA		typedef ptr DNS_TSIG_DATAA
PDNS_WINSR_DATA		typedef ptr DNS_WINSR_DATAA
endif

DNS_TEXT_RECORD_LENGTH macro StringCount
	exitm<FIELD_OFFSET(DNS_TXT_DATA, pStringArray) + ((StringCount) * sizeof(PCHAR))>
	endm

DNS_NULL_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_NULL_DATA, Data) + (ByteCount)>
	endm

DNS_WKS_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_WKS_DATA, BitMask) + (ByteCount)>
	endm

DNS_WINS_RECORD_LENGTH macro IpCount
	exitm<FIELD_OFFSET(DNS_WINS_DATA, WinsServers) + ((IpCount) * sizeof(IP4_ADDRESS))>
	endm

DNS_KEY_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_KEY_DATA, Key) + (ByteCount)>
	endm

DNS_SIG_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_SIG_DATA, Signature) + (ByteCount)>
	endm

DNS_NSEC_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_NSEC_DATA, TypeBitMaps) + (ByteCount)>
	endm

DNS_DS_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_DS_DATA, Digest) + (ByteCount)>
	endm

DNS_OPT_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_OPT_DATA, Data) + (ByteCount)>
	endm

DNS_DHCID_RECORD_LENGTH macro ByteCount
	exitm<FIELD_OFFSET(DNS_DHCID_DATA, DHCID) + (ByteCount)>
	endm

DNS_RECORD_FLAGS	STRUC
;Section    : 2		dd ?
;Delete	    : 1		dd ?
;CharSet    : 2		dd ?
;Unused	    : 3		dd ?
;Reserved   : 24	dd ?
Flags			dd ?
DNS_RECORD_FLAGS	ENDS

DNS_SECTION		typedef SDWORD
DnsSectionQuestion	equ 0
DnsSectionAnswer	equ 1
DnsSectionAuthority	equ 2
DnsSectionAddtional	equ 3

DnsSectionZone		equ DnsSectionQuestion
DnsSectionPrereq	equ DnsSectionAnswer
DnsSectionUpdate	equ DnsSectionAuthority

DNSREC_SECTION		equ (0x00000003)
DNSREC_QUESTION		equ (0x00000000)
DNSREC_ANSWER		equ (0x00000001)
DNSREC_AUTHORITY	equ (0x00000002)
DNSREC_ADDITIONAL	equ (0x00000003)

DNSREC_ZONE		equ (0x00000000)
DNSREC_PREREQ		equ (0x00000001)
DNSREC_UPDATE		equ (0x00000002)

DNSREC_DELETE		equ (0x00000004)
DNSREC_NOEXIST		equ (0x00000004)

ifdef MIDL_PASS

PDNS_RECORD		equ PVOID
PDNS_RECORDA		equ PVOID
PDNS_RECORDW		equ PVOID

else

DNS_RECORDW		STRUC
pNext			PVOID ?
pName			PWSTR ?
wType			dw ?
wDataLength		dw ?
UNION Flags
 _DW			dd ?
 S			DNS_RECORD_FLAGS <>
ENDS
dwTtl			dd ?
dwReserved		dd ?
UNION _Data
 A			DNS_A_DATA <>
 SOA			DNS_SOA_DATAW <>
 Soa			DNS_SOA_DATAW <>
 _PTR			DNS_PTR_DATAW <>
 _Ptr			DNS_PTR_DATAW <>
 Ns			DNS_PTR_DATAW <>
 NS			DNS_PTR_DATAW <>
 Cname			DNS_PTR_DATAW <>
 CNAME			DNS_PTR_DATAW <>
 Dname			DNS_PTR_DATAW <>
 DNAME			DNS_PTR_DATAW <>
 Mb			DNS_PTR_DATAW <>
 MB			DNS_PTR_DATAW <>
 Md			DNS_PTR_DATAW <>
 MD			DNS_PTR_DATAW <>
 Mf			DNS_PTR_DATAW <>
 MF			DNS_PTR_DATAW <>
 Mg			DNS_PTR_DATAW <>
 MG			DNS_PTR_DATAW <>
 Mr			DNS_PTR_DATAW <>
 MR			DNS_PTR_DATAW <>
 MINFO			DNS_MINFO_DATAW <>
 Minfo			DNS_MINFO_DATAW <>
 Rp			DNS_MINFO_DATAW <>
 RP			DNS_MINFO_DATAW <>
 MX			DNS_MX_DATAW <>
 Mx			DNS_MX_DATAW <>
 Afsdb			DNS_MX_DATAW <>
 AFSDB			DNS_MX_DATAW <>
 Rt			DNS_MX_DATAW <>
 RT			DNS_MX_DATAW <>
 HINFO			DNS_TXT_DATAW <>
 Hinfo			DNS_TXT_DATAW <>
 Isdn			DNS_TXT_DATAW <>
 ISDN			DNS_TXT_DATAW <>
 Txt			DNS_TXT_DATAW <>
 TXT			DNS_TXT_DATAW <>
 Null			DNS_NULL_DATA <>
 WKS			DNS_WKS_DATA <>
 Wks			DNS_WKS_DATA <>
 AAAA			DNS_AAAA_DATA <>
 KEY			DNS_KEY_DATA <>
 Key			DNS_KEY_DATA <>
 SIG			DNS_SIG_DATAW <>
 Sig			DNS_SIG_DATAW <>
 ATMA			DNS_ATMA_DATA <>
 Atma			DNS_ATMA_DATA <>
 NXT			DNS_NXT_DATAW <>
 Nxt			DNS_NXT_DATAW <>
 SRV			DNS_SRV_DATAW <>
 Srv			DNS_SRV_DATAW <>
 NAPTR			DNS_NAPTR_DATAW <>
 Naptr			DNS_NAPTR_DATAW <>
 OPT			DNS_OPT_DATA <>
 Opt			DNS_OPT_DATA <>
 _DS			DNS_DS_DATA <>
 _Ds			DNS_DS_DATA <>
 RRSIG			DNS_RRSIG_DATAW <>
 Rrsig			DNS_RRSIG_DATAW <>
 NSEC			DNS_NSEC_DATAW <>
 Nsec			DNS_NSEC_DATAW <>
 DNSKEY			DNS_DNSKEY_DATA <>
 Dnskey			DNS_DNSKEY_DATA <>
 TKEY			DNS_TKEY_DATAW <>
 Tkey			DNS_TKEY_DATAW <>
 TSIG			DNS_TSIG_DATAW <>
 Tsig			DNS_TSIG_DATAW <>
 WINS			DNS_WINS_DATA <>
 Wins			DNS_WINS_DATA <>
 WINSR			DNS_WINSR_DATAW <>
 WinsR			DNS_WINSR_DATAW <>
 NBSTAT			DNS_WINSR_DATAW <>
 Nbstat			DNS_WINSR_DATAW <>
 DHCID			DNS_DHCID_DATA <>
ENDS
DNS_RECORDW		ENDS
PDNS_RECORDW		typedef ptr DNS_RECORDW

DNS_RECORD_OPTW		STRUC
pNext			PVOID ?
pName			PWSTR ?
wType			dw ?
wDataLength		dw ?
UNION Flags
 _DW			dd ?
 S			DNS_RECORD_FLAGS <>
ENDS
ExtHeader		DNS_HEADER_EXT <>
wPayloadSize		dw ?
wReserved		dw ?
UNION __Data
 OPT			DNS_OPT_DATA <>
 Opt			DNS_OPT_DATA <>
ENDS
DNS_RECORD_OPTW		ENDS
PDNS_RECORD_OPTW	typedef ptr DNS_RECORD_OPTW

DNS_RECORDA		STRUC
pNext			PVOID ?
pName			PSTR ?
wType			dw ?
wDataLength		dw ?
UNION Flags
 _DW			dd ?
 S			DNS_RECORD_FLAGS <>
ENDS
dwTtl			dd ?
dwReserved		dd ?
UNION ; Data
 A			DNS_A_DATA <>
 SOA			DNS_SOA_DATAA <>
 Soa			DNS_SOA_DATAA <>
 _PTR			DNS_PTR_DATAA <>
 _Ptr			DNS_PTR_DATAA <>
 Ns			DNS_PTR_DATAA <>
 NS			DNS_PTR_DATAA <>
 Cname			DNS_PTR_DATAA <>
 CNAME			DNS_PTR_DATAA <>
 Dname			DNS_PTR_DATAA <>
 DNAME			DNS_PTR_DATAA <>
 Mb			DNS_PTR_DATAA <>
 MB			DNS_PTR_DATAA <>
 Md			DNS_PTR_DATAA <>
 MD			DNS_PTR_DATAA <>
 Mf			DNS_PTR_DATAA <>
 MF			DNS_PTR_DATAA <>
 Mg			DNS_PTR_DATAA <>
 MG			DNS_PTR_DATAA <>
 Mr			DNS_PTR_DATAA <>
 MR			DNS_PTR_DATAA <>
 MINFO			DNS_MINFO_DATAA <>
 Minfo			DNS_MINFO_DATAA <>
 Rp			DNS_MINFO_DATAA <>
 RP			DNS_MINFO_DATAA <>
 MX			DNS_MX_DATAA <>
 Mx			DNS_MX_DATAA <>
 Afsdb			DNS_MX_DATAA <>
 AFSDB			DNS_MX_DATAA <>
 Rt			DNS_MX_DATAA <>
 RT			DNS_MX_DATAA <>
 HINFO			DNS_TXT_DATAA <>
 Hinfo			DNS_TXT_DATAA <>
 Isdn			DNS_TXT_DATAA <>
 ISDN			DNS_TXT_DATAA <>
 Txt			DNS_TXT_DATAA <>
 TXT			DNS_TXT_DATAA <>
 Null			DNS_NULL_DATA <>
 WKS			DNS_WKS_DATA <>
 Wks			DNS_WKS_DATA <>
 AAAA			DNS_AAAA_DATA <>
 KEY			DNS_KEY_DATA <>
 Key			DNS_KEY_DATA <>
 SIG			DNS_SIG_DATAA <>
 Sig			DNS_SIG_DATAA <>
 ATMA			DNS_ATMA_DATA <>
 Atma			DNS_ATMA_DATA <>
 NXT			DNS_NXT_DATAA <>
 Nxt			DNS_NXT_DATAA <>
 SRV			DNS_SRV_DATAA <>
 Srv			DNS_SRV_DATAA <>
 NAPTR			DNS_NAPTR_DATAA <>
 Naptr			DNS_NAPTR_DATAA <>
 OPT			DNS_OPT_DATA <>
 Opt			DNS_OPT_DATA <>
 _DS			DNS_DS_DATA <>
 _Ds			DNS_DS_DATA <>
 RRSIG			DNS_RRSIG_DATAA <>
 Rrsig			DNS_RRSIG_DATAA <>
 NSEC			DNS_NSEC_DATAA <>
 Nsec			DNS_NSEC_DATAA <>
 DNSKEY			DNS_DNSKEY_DATA <>
 Dnskey			DNS_DNSKEY_DATA <>
 TKEY			DNS_TKEY_DATAA <>
 Tkey			DNS_TKEY_DATAA <>
 TSIG			DNS_TSIG_DATAA <>
 Tsig			DNS_TSIG_DATAA <>
 WINS			DNS_WINS_DATA <>
 Wins			DNS_WINS_DATA <>
 WINSR			DNS_WINSR_DATAA <>
 WinsR			DNS_WINSR_DATAA <>
 NBSTAT			DNS_WINSR_DATAA <>
 Nbstat			DNS_WINSR_DATAA <>
 DHCID			DNS_DHCID_DATA <>
ENDS
DNS_RECORDA		ENDS
PDNS_RECORDA		typedef ptr DNS_RECORDA

DNS_RECORD_OPTA		STRUC
pNext			PVOID ?
pName			PSTR ?
wType			dw ?
wDataLength		dw ?
UNION Flags
 _DW			dd ?
 S			DNS_RECORD_FLAGS <>
ENDS
ExtHeader		DNS_HEADER_EXT <>
wPayloadSize		dw ?
wReserved		dw ?
UNION ; Data
 OPT			DNS_OPT_DATA <>
 Opt			DNS_OPT_DATA <>
ENDS
DNS_RECORD_OPTA		ENDS
PDNS_RECORD_OPTA	typedef ptr DNS_RECORD_OPTA

ifdef _UNICODE
DNS_RECORD		typedef DNS_RECORDW
DNS_RECORD_OPT		typedef DNS_RECORD_OPTW
PDNS_RECORD		typedef ptr DNS_RECORDW
PDNS_RECORD_OPT		typedef ptr DNS_RECORD_OPTW
else
DNS_RECORD		typedef DNS_RECORDA
DNS_RECORD_OPT		typedef DNS_RECORD_OPTA
PDNS_RECORD		typedef ptr DNS_RECORDA
PDNS_RECORD_OPT		typedef ptr DNS_RECORD_OPTA
endif

DNS_RECORD_FIXED_SIZE	equ FIELD_OFFSET( DNS_RECORD, Data )
SIZEOF_DNS_RECORD_HEADER equ DNS_RECORD_FIXED_SIZE

endif  ;; PRIVATE_DNS_RECORD

DNS_RRSET		STRUC
pFirstRR		PDNS_RECORD ?
pLastRR			PDNS_RECORD ?
DNS_RRSET		ENDS
PDNS_RRSET		typedef ptr DNS_RRSET

DNS_RRSET_INIT macro rrset
	exitm<.err>
	endm

DNS_RRSET_ADD macro rrset, pnewRR
	exitm<.err>
	endm

DNS_RRSET_TERMINATE macro rrset
	exitm<.err>
	endm

CALLBACK(DNS_PROXY_COMPLETION_ROUTINE, :ptr, :DNS_STATUS)

DNS_PROXY_INFORMATION_TYPE typedef SDWORD
DNS_PROXY_INFORMATION_DIRECT equ 0
DNS_PROXY_INFORMATION_DEFAULT_SETTINGS equ 1
DNS_PROXY_INFORMATION_PROXY_NAME equ 2
DNS_PROXY_INFORMATION_DOES_NOT_EXIST equ 3

DNS_PROXY_INFORMATION	STRUC
version			ULONG ?
proxyInformationType	DNS_PROXY_INFORMATION_TYPE ?
proxyName		PWSTR ?
DNS_PROXY_INFORMATION	ENDS

DNS_CHARSET		typedef SDWORD
DnsCharSetUnknown	equ 0
DnsCharSetUnicode	equ 1
DnsCharSetUtf8		equ 2
DnsCharSetAnsi		equ 3

;PDNS_RECORD
DnsRecordCopyEx proto WINAPI \
	       pRecord: PDNS_RECORD,
	     CharSetIn: DNS_CHARSET,
	    CharSetOut: DNS_CHARSET

;PDNS_RECORD
DnsRecordSetCopyEx proto WINAPI \
	    pRecordSet: PDNS_RECORD,
	     CharSetIn: DNS_CHARSET,
	    CharSetOut: DNS_CHARSET

ifdef _UNICODE
DnsRecordCopy macro pRR
	exitm<DnsRecordCopyEx( (pRR), DnsCharSetUnicode, DnsCharSetUnicode )>
	endm
DnsRecordSetCopy macro pRR
	exitm<DnsRecordSetCopyEx( (pRR), DnsCharSetUnicode, DnsCharSetUnicode )>
	endm
else
DnsRecordCopy macro pRR
	exitm<DnsRecordCopyEx( (pRR), DnsCharSetAnsi, DnsCharSetAnsi )>
	endm
DnsRecordSetCopy macro pRR
	exitm<DnsRecordSetCopyEx( (pRR), DnsCharSetAnsi, DnsCharSetAnsi )>
	endm
endif

;BOOL
DnsRecordCompare proto WINAPI \
	      pRecord1: PDNS_RECORD,
	      pRecord2: PDNS_RECORD

;BOOL
DnsRecordSetCompare proto WINAPI \
		  pRR1: PDNS_RECORD,
		  pRR2: PDNS_RECORD,
	       ppDiff1: ptr PDNS_RECORD,
	       ppDiff2: ptr PDNS_RECORD

;PDNS_RECORD
DnsRecordSetDetach proto WINAPI \
	   pRecordList: PDNS_RECORD


DnsFreeFlat		equ 0
DnsFreeRecordList	equ 1
DnsFreeParsedMessageFields equ 2
DNS_FREE_TYPE		typedef SDWORD

;VOID
DnsFree proto WINAPI \
		 pData: PVOID,
	      FreeType: DNS_FREE_TYPE

DnsFreeRecordListDeep	equ <DnsFreeRecordList>

if(_WIN32_WINNT GE 0x0501)
DnsRecordListFree macro p,t
	exitm<DnsFree(p,DnsFreeRecordList)>
	endm
else
;VOID
DnsRecordListFree proto WINAPI \
	   pRecordList: PDNS_RECORD,
	      FreeType: DNS_FREE_TYPE

endif ;; _WIN32_WINNT GE 0x0501

DNS_QUERY_STANDARD	equ 0x00000000
DNS_QUERY_ACCEPT_TRUNCATED_RESPONSE equ 0x00000001
DNS_QUERY_USE_TCP_ONLY	equ 0x00000002
DNS_QUERY_NO_RECURSION	equ 0x00000004
DNS_QUERY_BYPASS_CACHE	equ 0x00000008

DNS_QUERY_NO_WIRE_QUERY equ 0x00000010
DNS_QUERY_NO_LOCAL_NAME equ 0x00000020
DNS_QUERY_NO_HOSTS_FILE equ 0x00000040
DNS_QUERY_NO_NETBT	equ 0x00000080

DNS_QUERY_WIRE_ONLY	equ 0x00000100
DNS_QUERY_RETURN_MESSAGE equ 0x00000200

DNS_QUERY_MULTICAST_ONLY equ 0x00000400
DNS_QUERY_NO_MULTICAST	equ 0x00000800

DNS_QUERY_TREAT_AS_FQDN equ 0x00001000
DNS_QUERY_APPEND_MULTILABEL equ 0x00800000

DNS_QUERY_DONT_RESET_TTL_VALUES equ 0x00100000
DNS_QUERY_RESERVED	equ 0xf0000000

DNS_QUERY_CACHE_ONLY	equ DNS_QUERY_NO_WIRE_QUERY


;DNS_STATUS
DnsQuery_A proto WINAPI \
	       pszName: PCSTR,
		 wType: WORD,
	       Options: DWORD,
		pExtra: PVOID,
	ppQueryResults: PDNS_RECORD,
	     pReserved: PVOID

;DNS_STATUS
DnsQuery_UTF8 proto WINAPI \
	       pszName: PCSTR,
		 wType: WORD,
	       Options: DWORD,
		pExtra: PVOID,
	ppQueryResults: PDNS_RECORD,
	     pReserved: PVOID

;DNS_STATUS
DnsQuery_W proto WINAPI \
	       pszName: PCWSTR,
		 wType: WORD,
	       Options: DWORD,
		pExtra: PVOID,
	ppQueryResults: PDNS_RECORD,
	     pReserved: PVOID

ifdef _UNICODE
DnsQuery		equ <DnsQuery_W>
else
DnsQuery		equ <DnsQuery_A>
endif

DNS_UPDATE_SECURITY_USE_DEFAULT equ 0x00000000
DNS_UPDATE_SECURITY_OFF equ 0x00000010
DNS_UPDATE_SECURITY_ON	equ 0x00000020
DNS_UPDATE_SECURITY_ONLY equ 0x00000100
DNS_UPDATE_CACHE_SECURITY_CONTEXT equ 0x00000200
DNS_UPDATE_TEST_USE_LOCAL_SYS_ACCT equ 0x00000400
DNS_UPDATE_FORCE_SECURITY_NEGO equ 0x00000800
DNS_UPDATE_TRY_ALL_MASTER_SERVERS equ 0x00001000
DNS_UPDATE_SKIP_NO_UPDATE_ADAPTERS equ 0x00002000
DNS_UPDATE_REMOTE_SERVER equ 0x00004000
DNS_UPDATE_RESERVED	equ 0xffff0000

;DNS_STATUS
DnsAcquireContextHandle_W proto WINAPI \
       CredentialFlags: DWORD,
	   Credentials: PVOID,
	      pContext: PHANDLE

;DNS_STATUS
DnsAcquireContextHandle_A proto WINAPI \
       CredentialFlags: DWORD,
	   Credentials: PVOID,
	      pContext: PHANDLE
ifdef _UNICODE
DnsAcquireContextHandle equ <DnsAcquireContextHandle_W>
else
DnsAcquireContextHandle equ <DnsAcquireContextHandle_A>
endif

;VOID
DnsReleaseContextHandle proto WINAPI \
	      hContext: HANDLE

;DNS_STATUS
DnsModifyRecordsInSet_W proto WINAPI \
	   pAddRecords: PDNS_RECORD,
	pDeleteRecords: PDNS_RECORD,
	       Options: DWORD,
	  hCredentials: HANDLE,
	    pExtraList: PVOID,
	     pReserved: PVOID

;DNS_STATUS
DnsModifyRecordsInSet_A proto WINAPI \
	   pAddRecords: PDNS_RECORD,
	pDeleteRecords: PDNS_RECORD,
	       Options: DWORD,
	  hCredentials: HANDLE,
	    pExtraList: PVOID,
	     pReserved: PVOID

;DNS_STATUS
DnsModifyRecordsInSet_UTF8 proto WINAPI \
	   pAddRecords: PDNS_RECORD,
	pDeleteRecords: PDNS_RECORD,
	       Options: DWORD,
	  hCredentials: HANDLE,
	    pExtraList: PVOID,
	     pReserved: PVOID

ifdef _UNICODE
DnsModifyRecordsInSet	equ <DnsModifyRecordsInSet_W>
else
DnsModifyRecordsInSet	equ <DnsModifyRecordsInSet_A>
endif


;DNS_STATUS
DnsReplaceRecordSetW proto WINAPI \
	   pReplaceSet: PDNS_RECORD,
	       Options: DWORD,
	      hContext: HANDLE,
	    pExtraInfo: PVOID,
	     pReserved: PVOID

;DNS_STATUS
DnsReplaceRecordSetA proto WINAPI \
	   pReplaceSet: PDNS_RECORD,
	       Options: DWORD,
	      hContext: HANDLE,
	    pExtraInfo: PVOID,
	     pReserved: PVOID

;DNS_STATUS
DnsReplaceRecordSetUTF8 proto WINAPI \
	   pReplaceSet: PDNS_RECORD,
	       Options: DWORD,
	      hContext: HANDLE,
	    pExtraInfo: PVOID,
	     pReserved: PVOID

ifdef _UNICODE
DnsReplaceRecordSet	equ <DnsReplaceRecordSetW>
else
DnsReplaceRecordSet	equ <DnsReplaceRecordSetA>
endif

DNS_NAME_FORMAT		typedef SDWORD
DnsNameDomain		equ 0
DnsNameDomainLabel	equ 1
DnsNameHostnameFull	equ 2
DnsNameHostnameLabel	equ 3
DnsNameWildcard		equ 4
DnsNameSrvRecord	equ 5
DnsNameValidateTld	equ 6


;DNS_STATUS
DnsValidateName_W proto WINAPI \
	       pszName: PCWSTR,
		Format: DNS_NAME_FORMAT

;DNS_STATUS
DnsValidateName_A proto WINAPI \
	       pszName: PCSTR,
		Format: DNS_NAME_FORMAT

;DNS_STATUS
DnsValidateName_UTF8 proto WINAPI \
	       pszName: PCSTR,
		Format: DNS_NAME_FORMAT

ifdef _UNICODE
DnsValidateName macro p,f
	exitm<DnsValidateName_W( (p), (f) )>
	endm
else
DnsValidateName macro p,f
	exitm<DnsValidateName_A( (p), (f) )>
	endm
endif

DNS_VALSVR_ERROR_INVALID_ADDR equ 0x01
DNS_VALSVR_ERROR_INVALID_NAME equ 0x02
DNS_VALSVR_ERROR_UNREACHABLE equ 0x03
DNS_VALSVR_ERROR_NO_RESPONSE equ 0x04
DNS_VALSVR_ERROR_NO_AUTH equ 0x05
DNS_VALSVR_ERROR_REFUSED equ 0x06

DNS_VALSVR_ERROR_NO_TCP equ 0x10
DNS_VALSVR_ERROR_UNKNOWN equ 0xFF

;; Winsock2.h must be included before windns.h to use the validate server function
ifdef _WS2DEF_

DNS_STATUS
DnsValidateServerStatus proto WINAPI \
		server: PSOCKADDR,
	     queryName: PCWSTR,
	  serverStatus: PDWORD

endif

;BOOL
DnsNameCompare_A proto WINAPI \
		pName1: PCSTR,
		pName2: PCSTR
DnsNameCompare_W proto WINAPI \
		pName1: PCWSTR,
		pName2: PCWSTR

ifdef _UNICODE
DnsNameCompare macro n1,n2
	exitm<DnsNameCompare_W( (n1),(n2) )>
	endm
else
DnsNameCompare macro n1,n2
	exitm<DnsNameCompare_A( (n1),(n2) )>
	endm
endif

DNS_MESSAGE_BUFFER	STRUC
MessageHead		DNS_HEADER <>
MessageBody		sbyte 1 dup(?)
DNS_MESSAGE_BUFFER	ENDS
PDNS_MESSAGE_BUFFER	typedef ptr DNS_MESSAGE_BUFFER

;BOOL
DnsWriteQuestionToBuffer_W proto WINAPI \
	    pDnsBuffer: PDNS_MESSAGE_BUFFER,
	 pdwBufferSize: PDWORD,
	       pszName: PCWSTR,
		 wType: WORD,
		   Xid: WORD,
     fRecursionDesired: BOOL


;BOOL
DnsWriteQuestionToBuffer_UTF8 proto WINAPI \
	    pDnsBuffer: PDNS_MESSAGE_BUFFER,
	 pdwBufferSize: PDWORD,
	       pszName: PCSTR,
		 wType: WORD,
		   Xid: WORD,
     fRecursionDesired: BOOL

;DNS_STATUS
DnsExtractRecordsFromMessage_W proto WINAPI \
	    pDnsBuffer: PDNS_MESSAGE_BUFFER,
	wMessageLength: WORD,
	      ppRecord: PDNS_RECORD

;DNS_STATUS
DnsExtractRecordsFromMessage_UTF8 proto WINAPI \
	    pDnsBuffer: PDNS_MESSAGE_BUFFER,
	wMessageLength: WORD,
	      ppRecord: PDNS_RECORD

;DWORD
DnsGetProxyInformation proto WINAPI \
	      hostName: PCWSTR,
      proxyInformation: ptr DNS_PROXY_INFORMATION,
defaultProxyInformation: ptr DNS_PROXY_INFORMATION,
     completionRoutine: DNS_PROXY_COMPLETION_ROUTINE,
     completionContext: PVOID

;VOID
DnsFreeProxyName proto WINAPI \
	     proxyName: PWSTR

.pragma list(pop)
endif
