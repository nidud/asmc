ifndef _EVNTCONS_H_
define _EVNTCONS_H_

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include wmistr.inc
include evntrace.inc
include evntprov.inc

EVENT_HEADER_EXT_TYPE_RELATED_ACTIVITYID equ 0x0001
EVENT_HEADER_EXT_TYPE_SID equ 0x0002
EVENT_HEADER_EXT_TYPE_TS_ID equ 0x0003
EVENT_HEADER_EXT_TYPE_INSTANCE_INFO equ 0x0004
EVENT_HEADER_EXT_TYPE_STACK_TRACE32 equ 0x0005
EVENT_HEADER_EXT_TYPE_STACK_TRACE64 equ 0x0006
EVENT_HEADER_EXT_TYPE_PEBS_INDEX equ 0x0007
EVENT_HEADER_EXT_TYPE_PMC_COUNTERS equ 0x0008
EVENT_HEADER_EXT_TYPE_PSM_KEY equ 0x0009
EVENT_HEADER_EXT_TYPE_EVENT_SCHEMA_TL equ 0x000B
EVENT_HEADER_EXT_TYPE_PROV_TRAITS equ 0x000C
EVENT_HEADER_EXT_TYPE_PROCESS_START_KEY equ 0x000D
EVENT_HEADER_EXT_TYPE_MAX equ 0x000E

ifndef EVENT_HEADER_EXTENDED_DATA_ITEM_DEF
define EVENT_HEADER_EXTENDED_DATA_ITEM_DEF
EVENT_HEADER_EXTENDED_DATA_ITEM STRUC
Reserved1               USHORT ?
ExtType                 USHORT ?
STRUC
 Linkage                USHORT ? ; : 1
 ;Reserved2             USHORT ? ; : 15
ENDS
DataSize                USHORT ?
DataPtr                 ULONGLONG ?
EVENT_HEADER_EXTENDED_DATA_ITEM ENDS
PEVENT_HEADER_EXTENDED_DATA_ITEM typedef ptr EVENT_HEADER_EXTENDED_DATA_ITEM
endif

EVENT_EXTENDED_ITEM_INSTANCE STRUC
InstanceId              ULONG ?
ParentInstanceId        ULONG ?
ParentGuid              GUID <>
EVENT_EXTENDED_ITEM_INSTANCE ENDS
PEVENT_EXTENDED_ITEM_INSTANCE typedef ptr EVENT_EXTENDED_ITEM_INSTANCE

EVENT_EXTENDED_ITEM_RELATED_ACTIVITYID  STRUC
RelatedActivityId       GUID <>
EVENT_EXTENDED_ITEM_RELATED_ACTIVITYID ENDS
PEVENT_EXTENDED_ITEM_RELATED_ACTIVITYID typedef ptr EVENT_EXTENDED_ITEM_RELATED_ACTIVITYID

EVENT_EXTENDED_ITEM_TS_ID  STRUC
SessionId               ULONG ?
EVENT_EXTENDED_ITEM_TS_ID ENDS
PEVENT_EXTENDED_ITEM_TS_ID typedef ptr EVENT_EXTENDED_ITEM_TS_ID

EVENT_EXTENDED_ITEM_STACK_TRACE32 STRUC
MatchId                 ULONG64 ?
Address                 ULONG ANYSIZE_ARRAY dup(?)
EVENT_EXTENDED_ITEM_STACK_TRACE32 ENDS
PEVENT_EXTENDED_ITEM_STACK_TRACE32 typedef ptr EVENT_EXTENDED_ITEM_STACK_TRACE32

EVENT_EXTENDED_ITEM_STACK_TRACE64 STRUC
MatchId                 ULONG64 ?
Address                 ULONG64 ANYSIZE_ARRAY dup(?)
EVENT_EXTENDED_ITEM_STACK_TRACE64 ENDS
PEVENT_EXTENDED_ITEM_STACK_TRACE64 typedef ptr EVENT_EXTENDED_ITEM_STACK_TRACE64

EVENT_EXTENDED_ITEM_PEBS_INDEX STRUC
PebsIndex               ULONG64 ?
EVENT_EXTENDED_ITEM_PEBS_INDEX ENDS
PEVENT_EXTENDED_ITEM_PEBS_INDEX typedef ptr EVENT_EXTENDED_ITEM_PEBS_INDEX

EVENT_EXTENDED_ITEM_PMC_COUNTERS STRUC
Counter                 ULONG64 ANYSIZE_ARRAY dup(?)
EVENT_EXTENDED_ITEM_PMC_COUNTERS ENDS
PEVENT_EXTENDED_ITEM_PMC_COUNTERS typedef ptr EVENT_EXTENDED_ITEM_PMC_COUNTERS

EVENT_EXTENDED_ITEM_PROCESS_START_KEY STRUC
ProcessStartKey         ULONG64 ?
EVENT_EXTENDED_ITEM_PROCESS_START_KEY ENDS
PEVENT_EXTENDED_ITEM_PROCESS_START_KEY typedef ptr EVENT_EXTENDED_ITEM_PROCESS_START_KEY

EVENT_HEADER_PROPERTY_XML equ 0x0001
EVENT_HEADER_PROPERTY_FORWARDED_XML equ 0x0002
EVENT_HEADER_PROPERTY_LEGACY_EVENTLOG equ 0x0004

EVENT_HEADER_FLAG_EXTENDED_INFO equ 0x0001
EVENT_HEADER_FLAG_PRIVATE_SESSION equ 0x0002
EVENT_HEADER_FLAG_STRING_ONLY equ 0x0004
EVENT_HEADER_FLAG_TRACE_MESSAGE equ 0x0008
EVENT_HEADER_FLAG_NO_CPUTIME equ 0x0010
EVENT_HEADER_FLAG_32_BIT_HEADER equ 0x0020
EVENT_HEADER_FLAG_64_BIT_HEADER equ 0x0040
EVENT_HEADER_FLAG_CLASSIC_HEADER equ 0x0100
EVENT_HEADER_FLAG_PROCESSOR_INDEX equ 0x0200

ifndef EVENT_HEADER_DEF
define EVENT_HEADER_DEF
EVENT_HEADER            STRUC
Size                    USHORT ?
HeaderType              USHORT ?
Flags                   USHORT ?
EventProperty           USHORT ?
ThreadId                ULONG ?
ProcessId               ULONG ?
TimeStamp               LARGE_INTEGER <>
ProviderId              GUID <>
EventDescriptor         EVENT_DESCRIPTOR <>
UNION
 STRUC
  KernelTime            ULONG ?
  UserTime              ULONG ?
 ENDS
 ProcessorTime          ULONG64 ?
ENDS
ActivityId              GUID <>
EVENT_HEADER            ENDS
PEVENT_HEADER           typedef ptr EVENT_HEADER
endif

ifndef EVENT_RECORD_DEF
define EVENT_RECORD_DEF
EVENT_RECORD            STRUC
EventHeader             EVENT_HEADER <>
BufferContext           ETW_BUFFER_CONTEXT <>
ExtendedDataCount       USHORT ?
UserDataLength          USHORT ?
ExtendedData            PEVENT_HEADER_EXTENDED_DATA_ITEM ?
UserData                PVOID ?
UserContext             PVOID ?
EVENT_RECORD            ENDS
PEVENT_RECORD           typedef ptr EVENT_RECORD
PCEVENT_RECORD          typedef ptr EVENT_RECORD
endif

EVENT_ENABLE_PROPERTY_SID equ 0x00000001
EVENT_ENABLE_PROPERTY_TS_ID equ 0x00000002
EVENT_ENABLE_PROPERTY_STACK_TRACE equ 0x00000004
EVENT_ENABLE_PROPERTY_PSM_KEY equ 0x00000008
EVENT_ENABLE_PROPERTY_IGNORE_KEYWORD_0 equ 0x00000010
EVENT_ENABLE_PROPERTY_PROVIDER_GROUP equ 0x00000020
EVENT_ENABLE_PROPERTY_ENABLE_KEYWORD_0 equ 0x00000040
EVENT_ENABLE_PROPERTY_PROCESS_START_KEY equ 0x00000080

PROCESS_TRACE_MODE_REAL_TIME equ 0x00000100
PROCESS_TRACE_MODE_RAW_TIMESTAMP equ 0x00001000
PROCESS_TRACE_MODE_EVENT_RECORD equ 0x10000000

;ULONG
GetEventProcessorIndex proto :PCEVENT_RECORD {
    mov eax,[_1].EVENT_RECORD.BufferContext.ProcessorNumber
    .if [_1].EVENT_RECORD.EventHeader.Flags & EVENT_HEADER_FLAG_PROCESSOR_INDEX
        mov eax,[_1].EVENT_RECORD.BufferContext.ProcessorIndex
    .endif
    }

.enum {
    EtwProviderTraitTypeGroup = 1,
    EtwProviderTraitTypeMax
    }

EtwGetTraitFromProviderTraits proto :PVOID, :UCHAR, :ptr PVOID, :PUSHORT {

    push rsi
    push rdi
    push rbx
    push rbp
    push r12

    mov rbp,rcx
    mov esi,edx
    mov rdi,r8
    mov rbx,r9

    movzx edx,word ptr [rbp]
    lea r12,[rbp+rdx]
    xor eax,eax
    mov [rdi],rax
    mov [rbx],ax

    ;;
    ;; Abort on invalid size.
    ;;

    .if edx >= 3

        ;;
        ;; Skip byte counts
        ;;

        add rbp,2

        ;;
        ;; Skip the Provider Name, including the Null termination
        ;;

        sub edx,3
        sub rsp,32+8
        add rbp,strnlen(rbp, rdx)
        add rbp,1
        add rsp,32+8

        ;;
        ;; Loop through the rest of the traits until one of the
        ;; desired type is located.
        ;;

        .while rbp < r12

            movzx ecx,word ptr [rbp]

            ;;
            ;; Abort on invalid trait size.
            ;;

            .break .if ecx < 3
            lea rax,[rbp+rcx]
            .if [rbp+2] == sil && rax <= r12

                add rbp,3
                mov [rdi],rbp
                sub ecx,3
                mov [rbx],cx
                .break
            .endif
            add rbp,rcx
        .endw
    .endif
    pop r12
    pop rbp
    pop rbx
    pop rdi
    pop rsi
    }


.enum {
    EventSecuritySetDACL,
    EventSecuritySetSACL,
    EventSecurityAddDACL,
    EventSecurityAddSACL,
    EventSecurityMax
    }

if (WINVER GE _WIN32_WINNT_LONGHORN)
EventAccessControl proto __cdecl :LPGUID, :ULONG, :PSID, :ULONG, :BOOLEAN
EventAccessQuery proto __cdecl :LPGUID, :PSECURITY_DESCRIPTOR, :PULONG
EventAccessRemove proto __cdecl :LPGUID
endif
endif
endif
