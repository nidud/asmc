ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;;    Header file for the Performance Monitor data.
;;
;;    This file contains the definitions of the data structures returned
;;    by the Configuration Registry in response to a request for
;;    performance data.	 This file is used by both the Configuration
;;    Registry and the Performance Monitor to define their interface.
;;    The complete interface is described here, except for the name
;;    of the node to query in the registry.  It is
;;
;;		     HKEY_PERFORMANCE_DATA.
;;
;;    By querying that node with a subkey of "Global" the caller will
;;    retrieve the structures described here.
;;
;;    There is no need to RegOpenKey() the reserved handle HKEY_PERFORMANCE_DATA,
;;    but the caller should RegCloseKey() the handle so that network transports
;;    and drivers can be removed or installed (which cannot happen while
;;    they are open for monitoring.)  Remote requests must first
;;    RegConnectRegistry().
;;
ifndef _WINPERF_
_WINPERF_ equ 1

;;  Data structure definitions.

;;  In order for data to be returned through the Configuration Registry
;;  in a system-independent fashion, it must be self-describing.

;;  In the following, all offsets are in bytes.

;;
;;  Data is returned through the Configuration Registry in a
;;  a data block which begins with a _PERF_DATA_BLOCK structure.
;;

PERF_DATA_VERSION	equ 1
PERF_DATA_REVISION	equ 1


PERF_DATA_BLOCK		STRUC
Signature		dw 4 dup(?) ;; Signature: Unicode "PERF"
LittleEndian		dd ?	;; 0 = Big Endian, 1 = Little Endian
Version			dd ?	;; Version of these data structures
				;; starting at 1
Revision		dd ?	;; Revision of these data structures
				;; starting at 0 for each Version
TotalByteLength		dd ?	;; Total length of data block
HeaderLength		dd ?	;; Length of this structure
NumObjectTypes		dd ?	;; Number of types of objects
				;; being reported
DefaultObject		LONG ?	;; Object Title Index of default
				;; object to display when data from
				;; this system is retrieved (-1 =
				;; none, but this is not expected to
				;; be used)
SystemTime		SYSTEMTIME <>	;; Time at the system under
					;; measurement
PerfTime		LARGE_INTEGER <> ;; Performance counter value
				;; at the system under measurement
PerfFreq		LARGE_INTEGER <> ;; Performance counter frequency
				;; at the system under measurement
PerfTime100nSec		LARGE_INTEGER <> ;; Performance counter time in 100 nsec
				;; units at the system under measurement
SystemNameLength	dd ?	;; Length of the system name
SystemNameOffset	dd ?	;; Offset, from beginning of this
				;; structure, to name of system
				;; being measured
PERF_DATA_BLOCK		ENDS
PPERF_DATA_BLOCK	typedef ptr PERF_DATA_BLOCK


;;
;;  The _PERF_DATA_BLOCK structure is followed by NumObjectTypes of
;;  data sections, one for each type of object measured.  Each object
;;  type section begins with a _PERF_OBJECT_TYPE structure.
;;


PERF_OBJECT_TYPE	STRUC
TotalByteLength		dd ?	;; Length of this object definition
				;; including this structure, the ;; ?
				;; counter definitions, and the ;; ?
				;; instance definitions and the ;; ?
				;; counter blocks for each instance: ;; ?
				;; This is the offset from this ;; ?
				;; structure to the next object, if ;; ?
				;; any			   ;; ?
DefinitionLength	dd ?	;; Length of object definition,
				;; which includes this structure ;; ?
				;; and the counter definition ;; ?
				;; structures for this object: this ;; ?
				;; is the offset of the first ;; ?
				;; instance or of the counters ;; ?
				;; for this object if there is ;; ?
				;; no instance		   ;; ?
HeaderLength		dd ?	;; Length of this structure: this
				;; is the offset to the first ;; ?
				;; counter definition for this ;; ?
				;; object		   ;; ?
ObjectNameTitleIndex	dd ?
				;; Index to name in Title Database ;; ?
ObjectNameTitle		LPWSTR ?	;; Initially NULL, for use by
				;; analysis program to point to ;; ?
				;; retrieved title string  ;; ?
ObjectHelpTitleIndex	dd ?
				;; Index to Help in Title Database ;; ?
ObjectHelpTitle		LPWSTR ?	;; Initially NULL, for use by
				;; analysis program to point to ;; ?
				;; retrieved title string  ;; ?
DetailLevel		dd ?	;; Object level of detail (for
				;; controlling display complexity) ;; ?
				;; will be min of detail levels ;; ?
				;; for all this object's counters ;; ?
NumCounters		dd ?	;; Number of counters in each
				;; counter block (one counter ;; ?
				;; block per instance)	   ;; ?
DefaultCounter		LONG ?	;; Default counter to display when
				;; this object is selected, index ;; ?
				;; starting at 0 (-1 = none, but ;; ?
				;; this is not expected to be used) ;; ?
NumInstances		LONG ?	;; Number of object instances
				;; for which counters are being ;; ?
				;; returned from the system under ;; ?
				;; measurement. If the object defined ;; ?
				;; will never have any instance data ;; ?
				;; structures (PERF_INSTANCE_DEFINITION) ;; ?
				;; then this value should be -1, if the ;; ?
				;; object can have 0 or more instances, ;; ?
				;; but has none present, then this ;; ?
				;; should be 0, otherwise this field ;; ?
				;; contains the number of instances of ;; ?
				;; this counter.	   ;; ?
				;; CodePage		   dd ? ;; 0 if instance strings are in
				;; UNICODE, else the Code Page of ;; ?
				;; the instance names	   ;; ?
PerfTime		LARGE_INTEGER <> ;; Sample Time in "Object" units
PerfFreq		LARGE_INTEGER <> ;; Frequency of "Object" units in
				;; counts per second.	   ;; ?
PERF_OBJECT_TYPE	ENDS
PPERF_OBJECT_TYPE	typedef ptr PERF_OBJECT_TYPE

PERF_NO_INSTANCES	equ -1	;; no instances (see NumInstances above)
;;
;; - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
;;
;;  PERF_COUNTER_DEFINITION.CounterType field values
;;
;;
;;	  Counter ID Field Definition:
;;
;;   3	    2	     2	  2    2	1	 1    1
;;   1	    8	     4	  2    0	6	 2    0	   8		    0
;;  +--------+--------+----+----+--------+--------+----+----+----------------+
;;  |Display |Calculation  |Time|Counter |	  |Ctr |Size|		     |
;;  |Flags   |Modifiers	   |Base|SubType |Reserved|Type|Fld |	Reserved     |
;;  +--------+--------+----+----+--------+--------+----+----+----------------+
;;
;;
;;  The counter type is the "or" of the following values as described below
;;
;;  select one of the following to indicate the counter's data size
;;
PERF_SIZE_DWORD		equ 0x00000000
PERF_SIZE_LARGE		equ 0x00000100
PERF_SIZE_ZERO		equ 0x00000200	;; for Zero Length fields
PERF_SIZE_VARIABLE_LEN	equ 0x00000300	;; length is in CounterLength field
					;; of Counter Definition struct ;; ?
;;
;;  select one of the following values to indicate the counter field usage
;;
PERF_TYPE_NUMBER	equ 0x00000000	;; a number (not a counter)
PERF_TYPE_COUNTER	equ 0x00000400	;; an increasing numeric value
PERF_TYPE_TEXT		equ 0x00000800	;; a text field
PERF_TYPE_ZERO		equ 0x00000C00	;; displays a zero
;;
;;  If the PERF_TYPE_NUMBER field was selected, then select one of the
;;  following to describe the Number
;;
PERF_NUMBER_HEX		equ 0x00000000	;; display as HEX value
PERF_NUMBER_DECIMAL	equ 0x00010000	;; display as a decimal integer
PERF_NUMBER_DEC_1000	equ 0x00020000	;; display as a decimal/1000
;;
;;  If the PERF_TYPE_COUNTER value was selected then select one of the
;;  following to indicate the type of counter
;;
PERF_COUNTER_VALUE	equ 0x00000000	;; display counter value
PERF_COUNTER_RATE	equ 0x00010000	;; divide ctr / delta time
PERF_COUNTER_FRACTION	equ 0x00020000	;; divide ctr / base
PERF_COUNTER_BASE	equ 0x00030000	;; base value used in fractions
PERF_COUNTER_ELAPSED	equ 0x00040000	;; subtract counter from current time
PERF_COUNTER_QUEUELEN	equ 0x00050000	;; Use Queuelen processing func.
PERF_COUNTER_HISTOGRAM	equ 0x00060000	;; Counter begins or ends a histogram
;;
;;  If the PERF_TYPE_TEXT value was selected, then select one of the
;;  following to indicate the type of TEXT data.
;;
PERF_TEXT_UNICODE	equ 0x00000000	;; type of text in text field
PERF_TEXT_ASCII		equ 0x00010000	;; ASCII using the CodePage field
;;
;;  Timer SubTypes
;;
PERF_TIMER_TICK		equ 0x00000000	;; use system perf. freq for base
PERF_TIMER_100NS	equ 0x00100000	;; use 100 NS timer time base units
PERF_OBJECT_TIMER	equ 0x00200000	;; use the object timer freq
;;
;;  Any types that have calculations performed can use one or more of
;;  the following calculation modification flags listed here
;;
PERF_DELTA_COUNTER	equ 0x00400000	;; compute difference first
PERF_DELTA_BASE		equ 0x00800000	;; compute base diff as well
PERF_INVERSE_COUNTER	equ 0x01000000	;; show as 1.00-value (assumes:
PERF_MULTI_COUNTER	equ 0x02000000	;; sum of multiple instances
;;
;;  Select one of the following values to indicate the display suffix (if any)
;;
PERF_DISPLAY_NO_SUFFIX	equ 0x00000000	;; no suffix
PERF_DISPLAY_PER_SEC	equ 0x10000000	;; "/sec"
PERF_DISPLAY_PERCENT	equ 0x20000000	;; "%"
PERF_DISPLAY_SECONDS	equ 0x30000000	;; "secs"
PERF_DISPLAY_NOSHOW	equ 0x40000000	;; value is not displayed
;;
;;  Predefined counter types
;;

;; 32-bit Counter.  Divide delta by delta time.	 Display suffix: "/sec"
PERF_COUNTER_COUNTER	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_TICK OR PERF_DELTA_COUNTER OR PERF_DISPLAY_PER_SEC)


;; 64-bit Timer.  Divide delta by delta time.  Display suffix: "%"
PERF_COUNTER_TIMER	equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_TICK OR PERF_DELTA_COUNTER OR PERF_DISPLAY_PERCENT)

;; Queue Length Space-Time Product. Divide delta by delta time. No Display Suffix.
PERF_COUNTER_QUEUELEN_TYPE equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_QUEUELEN OR PERF_TIMER_TICK OR PERF_DELTA_COUNTER OR PERF_DISPLAY_NO_SUFFIX)

;; Queue Length Space-Time Product. Divide delta by delta time. No Display Suffix.
PERF_COUNTER_LARGE_QUEUELEN_TYPE equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_QUEUELEN OR PERF_TIMER_TICK OR PERF_DELTA_COUNTER OR PERF_DISPLAY_NO_SUFFIX)

;; 64-bit Counter.  Divide delta by delta time. Display Suffix: "/sec"
PERF_COUNTER_BULK_COUNT equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_TICK OR PERF_DELTA_COUNTER OR PERF_DISPLAY_PER_SEC)

;; Indicates the counter is not a  counter but rather Unicode text Display as text.
PERF_COUNTER_TEXT	equ (PERF_SIZE_VARIABLE_LEN OR PERF_TYPE_TEXT OR PERF_TEXT_UNICODE OR PERF_DISPLAY_NO_SUFFIX)

;; Indicates the data is a counter  which should not be
;; time averaged on display (such as an error counter on a serial line)
;; Display as is.  No Display Suffix.
PERF_COUNTER_RAWCOUNT	equ (PERF_SIZE_DWORD OR PERF_TYPE_NUMBER OR PERF_NUMBER_DECIMAL OR PERF_DISPLAY_NO_SUFFIX)

;; Same as PERF_COUNTER_RAWCOUNT except its size is a large integer
PERF_COUNTER_LARGE_RAWCOUNT equ (PERF_SIZE_LARGE OR PERF_TYPE_NUMBER OR PERF_NUMBER_DECIMAL OR PERF_DISPLAY_NO_SUFFIX)

;; Special case for RAWCOUNT that want to be displayed in hex
;; Indicates the data is a counter  which should not be
;; time averaged on display (such as an error counter on a serial line)
;; Display as is.  No Display Suffix.
PERF_COUNTER_RAWCOUNT_HEX equ (PERF_SIZE_DWORD OR PERF_TYPE_NUMBER OR PERF_NUMBER_HEX OR PERF_DISPLAY_NO_SUFFIX)

;; Same as PERF_COUNTER_RAWCOUNT_HEX except its size is a large integer
PERF_COUNTER_LARGE_RAWCOUNT_HEX equ (PERF_SIZE_LARGE OR PERF_TYPE_NUMBER OR PERF_NUMBER_HEX OR PERF_DISPLAY_NO_SUFFIX)


;; A count which is either 1 or 0 on each sampling interrupt (% busy)
;; Divide delta by delta base. Display Suffix: "%"
PERF_SAMPLE_FRACTION	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_FRACTION OR PERF_DELTA_COUNTER OR PERF_DELTA_BASE OR PERF_DISPLAY_PERCENT)

;; A count which is sampled on each sampling interrupt (queue length)
;; Divide delta by delta time. No Display Suffix.
PERF_SAMPLE_COUNTER	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_TICK OR PERF_DELTA_COUNTER OR PERF_DISPLAY_NO_SUFFIX)

;; A label: no data is associated with this counter (it has 0 length)
;; Do not display.
PERF_COUNTER_NODATA	equ (PERF_SIZE_ZERO OR PERF_DISPLAY_NOSHOW)

;; 64-bit Timer inverse (e.g., idle is measured, but display busy %)
;; Display 100 - delta divided by delta time.  Display suffix: "%"
PERF_COUNTER_TIMER_INV	equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_TICK OR PERF_DELTA_COUNTER OR PERF_INVERSE_COUNTER OR PERF_DISPLAY_PERCENT)

;; The divisor for a sample, used with the previous counter to form a
;; sampled %.  You must check for >0 before dividing by this!  This
;; counter will directly follow the  numerator counter.	 It should not
;; be displayed to the user.
PERF_SAMPLE_BASE	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_BASE OR PERF_DISPLAY_NOSHOW OR 0x00000001)  ;; for compatibility with pre-beta versions

;; A timer which, when divided by an average base, produces a time
;; in seconds which is the average time of some operation.  This
;; timer times total operations, and  the base is the number of opera-
;; tions.  Display Suffix: "sec"
PERF_AVERAGE_TIMER	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_FRACTION OR PERF_DISPLAY_SECONDS)

;; Used as the denominator in the computation of time or count
;; averages.  Must directly follow the numerator counter.  Not dis-
;; played to the user.
PERF_AVERAGE_BASE	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_BASE OR PERF_DISPLAY_NOSHOW OR 0x00000002)	;; for compatibility with pre-beta versions


;; A bulk count which, when divided (typically) by the number of
;; operations, gives (typically) the number of bytes per operation.
;; No Display Suffix.
PERF_AVERAGE_BULK	equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_FRACTION OR PERF_DISPLAY_NOSHOW)

;; 64-bit Timer in 100 nsec units. Display delta divided by
;; delta time.	Display suffix: "%"
PERF_100NSEC_TIMER	equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_100NS OR PERF_DELTA_COUNTER OR PERF_DISPLAY_PERCENT)

;; 64-bit Timer inverse (e.g., idle is measured, but display busy %)
;; Display 100 - delta divided by delta time.  Display suffix: "%"
PERF_100NSEC_TIMER_INV	equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_100NS OR PERF_DELTA_COUNTER OR PERF_INVERSE_COUNTER OR PERF_DISPLAY_PERCENT)

;; 64-bit Timer.  Divide delta by delta time.  Display suffix: "%"
;; Timer for multiple instances, so result can exceed 100%.
PERF_COUNTER_MULTI_TIMER equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_DELTA_COUNTER OR PERF_TIMER_TICK OR PERF_MULTI_COUNTER OR PERF_DISPLAY_PERCENT)

;; 64-bit Timer inverse (e.g., idle is measured, but display busy %)
;; Display 100 * _MULTI_BASE - delta divided by delta time.
;; Display suffix: "%" Timer for multiple instances, so result
;; can exceed 100%.  Followed by a counter of type _MULTI_BASE.
PERF_COUNTER_MULTI_TIMER_INV equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_RATE OR PERF_DELTA_COUNTER OR PERF_MULTI_COUNTER OR PERF_TIMER_TICK OR PERF_INVERSE_COUNTER OR PERF_DISPLAY_PERCENT)

;; Number of instances to which the preceding _MULTI_..._INV counter
;; applies.  Used as a factor to get the percentage.
PERF_COUNTER_MULTI_BASE equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_BASE OR PERF_MULTI_COUNTER OR PERF_DISPLAY_NOSHOW)

;; 64-bit Timer in 100 nsec units. Display delta divided by delta time.
;; Display suffix: "%" Timer for multiple instances, so result can exceed 100%.
PERF_100NSEC_MULTI_TIMER equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_DELTA_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_100NS OR PERF_MULTI_COUNTER OR PERF_DISPLAY_PERCENT)

;; 64-bit Timer inverse (e.g., idle is measured, but display busy %)
;; Display 100 * _MULTI_BASE - delta divided by delta time.
;; Display suffix: "%" Timer for multiple instances, so result
;; can exceed 100%.  Followed by a counter of type _MULTI_BASE.
PERF_100NSEC_MULTI_TIMER_INV equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_DELTA_COUNTER OR PERF_COUNTER_RATE OR PERF_TIMER_100NS OR PERF_MULTI_COUNTER OR PERF_INVERSE_COUNTER OR PERF_DISPLAY_PERCENT)

;; Indicates the data is a fraction of the following counter  which
;; should not be time averaged on display (such as free space over
;; total space.) Display as is.	 Display the quotient as "%".
PERF_RAW_FRACTION	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_FRACTION OR PERF_DISPLAY_PERCENT)

;; Indicates the data is a base for the preceding counter which should
;; not be time averaged on display (such as free space over total space.)
PERF_RAW_BASE		equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_BASE OR PERF_DISPLAY_NOSHOW OR 0x00000003)  ;; for compatibility with pre-beta versions

;; The data collected in this counter is actually the start time of the
;; item being measured. For display, this data is subtracted from the
;; sample time to yield the elapsed time as the difference between the two.
;; In the definition below, the PerfTime field of the Object contains
;; the sample time as indicated by the PERF_OBJECT_TIMER bit and the
;; difference is scaled by the PerfFreq of the Object to convert the time
;; units into seconds.
PERF_ELAPSED_TIME	equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_ELAPSED OR PERF_OBJECT_TIMER OR PERF_DISPLAY_SECONDS)
;;
;;  The following counter type can be used with the preceding types to
;;  define a range of values to be displayed in a histogram.
;;

PERF_COUNTER_HISTOGRAM_TYPE equ 0x80000000
;;  Counter begins or ends a histogram
;;
;;  This counter is used to display the difference from one sample
;;  to the next. The counter value is a constantly increasing number
;;  and the value displayed is the difference between the current
;;  value and the previous value. Negative numbers are not allowed
;;  which shouldn't be a problem as long as the counter value is
;;  increasing or unchanged.
;;
PERF_COUNTER_DELTA	equ (PERF_SIZE_DWORD OR PERF_TYPE_COUNTER OR PERF_COUNTER_VALUE OR PERF_DELTA_COUNTER OR PERF_DISPLAY_NO_SUFFIX)

PERF_COUNTER_LARGE_DELTA equ (PERF_SIZE_LARGE OR PERF_TYPE_COUNTER OR PERF_COUNTER_VALUE OR PERF_DELTA_COUNTER OR PERF_DISPLAY_NO_SUFFIX)
;;
;;  The following are used to determine the level of detail associated
;;  with the counter.  The user will be setting the level of detail
;;  that should be displayed at any given time.
;;

PERF_DETAIL_NOVICE	equ 100 ;; The uninformed can understand it
PERF_DETAIL_ADVANCED	equ 200 ;; For the advanced user
PERF_DETAIL_EXPERT	equ 300 ;; For the expert user
PERF_DETAIL_WIZARD	equ 400 ;; For the system designer

;;
;;  There is one of the following for each of the
;;  PERF_OBJECT_TYPE.NumCounters.  The Unicode names in this structure MUST
;;  come from a message file.
;;

PERF_COUNTER_DEFINITION	 STRUC
ByteLength		dd ?	;; Length in bytes of this structure
CounterNameTitleIndex	dd ?
				;; Index of Counter name into ;; ?
				;; Title Database	   ;; ?
CounterNameTitle	LPWSTR ?	;; Initially NULL, for use by
				;; analysis program to point to ;; ?
				;; retrieved title string  ;; ?
CounterHelpTitleIndex	dd ?
				;; Index of Counter Help into ;; ?
				;; Title Database	   ;; ?
CounterHelpTitle	LPWSTR ?	;; Initially NULL, for use by
				;; analysis program to point to ;; ?
				;; retrieved title string  ;; ?
DefaultScale		LONG ?	;; Power of 10 by which to scale
				;; chart line if vertical axis is 100 ;; ?
				;; 0 ==> 1, 1 ==> 10, -1 ==>1/10, etc. ;; ?
DetailLevel		dd ?	;; Counter level of detail (for
				;; controlling display complexity) ;; ?
CounterType		dd ?	;; Type of counter
CounterSize		dd ?	;; Size of counter in bytes
CounterOffset		dd ?	;; Offset from the start of the
				;; PERF_COUNTER_BLOCK to the first ;; ?
				;; byte of this counter	   ;; ?
PERF_COUNTER_DEFINITION ENDS
PPERF_COUNTER_DEFINITION typedef ptr PERF_COUNTER_DEFINITION

;;
;;  If (PERF_DATA_BLOCK.NumInstances >= 0) then there will be
;;  PERF_DATA_BLOCK.NumInstances of a (PERF_INSTANCE_DEFINITION
;;  followed by a PERF_COUNTER_BLOCK followed by the counter data fields)
;;  for each instance.
;;
;;  If (PERF_DATA_BLOCK.NumInstances < 0) then the counter definition
;;  strucutre above will be followed by only a PERF_COUNTER_BLOCK and the
;;  counter data for that COUNTER.
;;

PERF_NO_UNIQUE_ID	equ -1

PERF_INSTANCE_DEFINITION  STRUC
ByteLength		dd ?	;; Length in bytes of this structure,
				;; including the subsequent name ;; ?
ParentObjectTitleIndex	dd ?
				;; Title Index to name of "parent" ;; ?
				;; object (e.g., if thread, then ;; ?
				;; process is parent object type) ;; ?
				;; if logical drive, the physical ;; ?
				;; drive is parent object type ;; ?
ParentObjectInstance	dd ?
				;; Index to instance of parent object ;; ?
				;; type which is the parent of this ;; ?
				;; instance.		   ;; ?
UniqueID		LONG ?	;; A unique ID used instead of
				;; matching the name to identify ;; ?
				;; this instance, -1 = none ;; ?
NameOffset		dd ?	;; Offset from beginning of
				;; this struct to the Unicode name ;; ?
				;; of this instance	   ;; ?
NameLength		dd ?	;; Length in bytes of name; 0 = none
				;; this length includes the characters ;; ?
				;; in the string plus the size of the ;; ?
				;; terminating NULL char. It does not ;; ?
				;; include any additional pad bytes to ;; ?
				;; correct structure alignment ;; ?
PERF_INSTANCE_DEFINITION ENDS
PPERF_INSTANCE_DEFINITION typedef ptr PERF_INSTANCE_DEFINITION
;;
;;  If .ParentObjectName is 0, there
;;  is no parent-child hierarchy for this object type.	Otherwise,
;;   the .ParentObjectInstance is an index, starting at 0, into the
;;  instances reported for the parent object type.  It is only
;;  meaningful if .ParentObjectName is not 0.  The purpose of all this
;;  is to permit reporting/summation of object instances like threads
;;  within processes, and logical drives within physical drives.
;;
;;
;;  The PERF_INSTANCE_DEFINITION will be followed by a PERF_COUNTER_BLOCK.
;;

PERF_COUNTER_BLOCK	STRUC
ByteLength		dd ?	;; Length in bytes of this structure,
				;; including the following counters ;; ?
PERF_COUNTER_BLOCK	ENDS
PPERF_COUNTER_BLOCK	typedef ptr PERF_COUNTER_BLOCK

;;
;;  The PERF_COUNTER_BLOCK is followed by PERF_OBJECT_TYPE.NumCounters
;;  number of counters.
;;

;;
;; Support for New Extensible API starting with NT 5.0
;;
PERF_QUERY_OBJECTS	equ 0x80000000
PERF_QUERY_GLOBAL	equ 0x80000001
PERF_QUERY_COSTLY	equ 0x80000002

;;
;;  function typedefs for extensible counter function prototypes
;;
PM_OPEN_PROC_T typedef proto _CType \
		      : LPWSTR
PM_COLLECT_PROC_T typedef proto _CType \
		      : LPWSTR,
		      : LPVOID,
		      : LPDWORD,
		      : LPDWORD
PM_CLOSE_PROC_T typedef proto _CType
PM_QUERY_PROC_T typedef proto _CType \
		      : LPDWORD,
		      : LPVOID,
		      : LPDWORD,
		      : LPDWORD
PM_OPEN_PROC		typedef ptr PM_OPEN_PROC_T
PM_COLLECT_PROC		typedef ptr PM_COLLECT_PROC_T
PM_CLOSE_PROC		typedef ptr PM_CLOSE_PROC_T
PM_QUERY_PROC		typedef ptr PM_QUERY_PROC_T

MAX_PERF_OBJECTS_IN_QUERY_FUNCTION equ (8)
endif ;; _WINPERF_

.list
