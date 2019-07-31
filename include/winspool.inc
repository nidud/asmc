ifndef _WINSPOOL_
_WINSPOOL_ equ <>
.pragma list(push, 0)

ifdef _WINUSER_
include prsht.inc
endif

PRINTER_INFO_1A		STRUC
Flags			dd ?
pDescription		LPSTR ?
pName			LPSTR ?
pComment		LPSTR ?
PRINTER_INFO_1A		ENDS
PPRINTER_INFO_1A	typedef ptr PRINTER_INFO_1A
LPPRINTER_INFO_1A	typedef ptr PRINTER_INFO_1A
PRINTER_INFO_1W		STRUC
Flags			dd ?
pDescription		LPWSTR ?
pName			LPWSTR ?
pComment		LPWSTR ?
PRINTER_INFO_1W		ENDS
PPRINTER_INFO_1W	typedef ptr PRINTER_INFO_1W
LPPRINTER_INFO_1W	typedef ptr PRINTER_INFO_1W
ifdef _UNICODE
PRINTER_INFO_1		typedef PRINTER_INFO_1W
PPRINTER_INFO_1		typedef PPRINTER_INFO_1W
LPPRINTER_INFO_1	typedef LPPRINTER_INFO_1W
else
PRINTER_INFO_1		typedef PRINTER_INFO_1A
PPRINTER_INFO_1		typedef PPRINTER_INFO_1A
LPPRINTER_INFO_1	typedef LPPRINTER_INFO_1A
endif

PRINTER_INFO_2A		STRUC
pServerName		LPSTR ?
pPrinterName		LPSTR ?
pShareName		LPSTR ?
pPortName		LPSTR ?
pDriverName		LPSTR ?
pComment		LPSTR ?
pLocation		LPSTR ?
pDevMode		LPDEVMODEA ?
pSepFile		LPSTR ?
pPrintProcessor		LPSTR ?
pDatatype		LPSTR ?
pParameters		LPSTR ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
Attributes		dd ?
Priority		dd ?
DefaultPriority		dd ?
StartTime		dd ?
UntilTime		dd ?
Status			dd ?
cJobs			dd ?
AveragePPM		dd ?
PRINTER_INFO_2A		ENDS
PPRINTER_INFO_2A	typedef ptr PRINTER_INFO_2A
LPPRINTER_INFO_2A	typedef ptr PRINTER_INFO_2A
PRINTER_INFO_2W		STRUC
pServerName		LPWSTR ?
pPrinterName		LPWSTR ?
pShareName		LPWSTR ?
pPortName		LPWSTR ?
pDriverName		LPWSTR ?
pComment		LPWSTR ?
pLocation		LPWSTR ?
pDevMode		LPDEVMODEW ?
pSepFile		LPWSTR ?
pPrintProcessor		LPWSTR ?
pDatatype		LPWSTR ?
pParameters		LPWSTR ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
Attributes		dd ?
Priority		dd ?
DefaultPriority		dd ?
StartTime		dd ?
UntilTime		dd ?
Status			dd ?
cJobs			dd ?
AveragePPM		dd ?
PRINTER_INFO_2W		ENDS
PPRINTER_INFO_2W	typedef ptr PRINTER_INFO_2W
LPPRINTER_INFO_2W	typedef ptr PRINTER_INFO_2W
ifdef _UNICODE
PRINTER_INFO_2		typedef PRINTER_INFO_2W
PPRINTER_INFO_2		typedef PPRINTER_INFO_2W
LPPRINTER_INFO_2	typedef LPPRINTER_INFO_2W
else
PRINTER_INFO_2		typedef PRINTER_INFO_2A
PPRINTER_INFO_2		typedef PPRINTER_INFO_2A
LPPRINTER_INFO_2	typedef LPPRINTER_INFO_2A
endif

PRINTER_INFO_3		STRUC
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
PRINTER_INFO_3		ENDS
PPRINTER_INFO_3		typedef ptr PRINTER_INFO_3
LPPRINTER_INFO_3	typedef ptr PRINTER_INFO_3

PRINTER_INFO_4A		STRUC
pPrinterName		LPSTR ?
pServerName		LPSTR ?
Attributes		dd ?
PRINTER_INFO_4A		ENDS
PPRINTER_INFO_4A	typedef ptr PRINTER_INFO_4A
LPPRINTER_INFO_4A	typedef ptr PRINTER_INFO_4A
PRINTER_INFO_4W		STRUC
pPrinterName		LPWSTR ?
pServerName		LPWSTR ?
Attributes		dd ?
PRINTER_INFO_4W		ENDS
PPRINTER_INFO_4W	typedef ptr PRINTER_INFO_4W
LPPRINTER_INFO_4W	typedef ptr PRINTER_INFO_4W
ifdef _UNICODE
PRINTER_INFO_4		typedef PRINTER_INFO_4W
PPRINTER_INFO_4		typedef PPRINTER_INFO_4W
LPPRINTER_INFO_4	typedef LPPRINTER_INFO_4W
else
PRINTER_INFO_4		typedef PRINTER_INFO_4A
PPRINTER_INFO_4		typedef PPRINTER_INFO_4A
LPPRINTER_INFO_4	typedef LPPRINTER_INFO_4A
endif

PRINTER_INFO_5A		STRUC
pPrinterName		LPSTR ?
pPortName		LPSTR ?
Attributes		dd ?
DeviceNotSelectedTimeout dd ?
TransmissionRetryTimeout dd ?
PRINTER_INFO_5A		ENDS
PPRINTER_INFO_5A	typedef ptr PRINTER_INFO_5A
LPPRINTER_INFO_5A	typedef ptr PRINTER_INFO_5A
PRINTER_INFO_5W		STRUC
pPrinterName		LPWSTR ?
pPortName		LPWSTR ?
Attributes		dd ?
DeviceNotSelectedTimeout dd ?
TransmissionRetryTimeout dd ?
PRINTER_INFO_5W		ENDS
PPRINTER_INFO_5W	typedef ptr PRINTER_INFO_5W
LPPRINTER_INFO_5W	typedef ptr PRINTER_INFO_5W
ifdef _UNICODE
PRINTER_INFO_5		typedef PRINTER_INFO_5W
PPRINTER_INFO_5		typedef PPRINTER_INFO_5W
LPPRINTER_INFO_5	typedef LPPRINTER_INFO_5W
else
PRINTER_INFO_5		typedef PRINTER_INFO_5A
PPRINTER_INFO_5		typedef PPRINTER_INFO_5A
LPPRINTER_INFO_5	typedef LPPRINTER_INFO_5A
endif

PRINTER_INFO_6		STRUC
dwStatus		dd ?
PRINTER_INFO_6		ENDS
PPRINTER_INFO_6		typedef ptr PRINTER_INFO_6
LPPRINTER_INFO_6	typedef ptr PRINTER_INFO_6

PRINTER_INFO_7A		STRUC
pszObjectGUID		LPSTR ?
dwAction		dd ?
PRINTER_INFO_7A		ENDS
PPRINTER_INFO_7A	typedef ptr PRINTER_INFO_7A
LPPRINTER_INFO_7A	typedef ptr PRINTER_INFO_7A
PRINTER_INFO_7W		STRUC
pszObjectGUID		LPWSTR ?
dwAction		dd ?
PRINTER_INFO_7W		ENDS
PPRINTER_INFO_7W	typedef ptr PRINTER_INFO_7W
LPPRINTER_INFO_7W	typedef ptr PRINTER_INFO_7W
ifdef _UNICODE
PRINTER_INFO_7		typedef PRINTER_INFO_7W
PPRINTER_INFO_7		typedef PPRINTER_INFO_7W
LPPRINTER_INFO_7	typedef LPPRINTER_INFO_7W
else
PRINTER_INFO_7		typedef PRINTER_INFO_7A
PPRINTER_INFO_7		typedef PPRINTER_INFO_7A
LPPRINTER_INFO_7	typedef LPPRINTER_INFO_7A
endif

DSPRINT_PUBLISH		equ 1
DSPRINT_UPDATE		equ 2
DSPRINT_UNPUBLISH	equ 3

PRINTER_CONTROL_PAUSE	equ 1
PRINTER_CONTROL_RESUME	equ 2
PRINTER_CONTROL_PURGE	equ 3
PRINTER_CONTROL_SET_STATUS equ 4

PRINTER_STATUS_PAUSED	equ 0x00000001
PRINTER_STATUS_ERROR	equ 0x00000002
PRINTER_STATUS_PENDING_DELETION equ 0x00000004
PRINTER_STATUS_PAPER_JAM equ 0x00000008
PRINTER_STATUS_PAPER_OUT equ 0x00000010
PRINTER_STATUS_MANUAL_FEED equ 0x00000020
PRINTER_STATUS_PAPER_PROBLEM equ 0x00000040
PRINTER_STATUS_OFFLINE	equ 0x00000080
PRINTER_STATUS_IO_ACTIVE equ 0x00000100
PRINTER_STATUS_BUSY	equ 0x00000200
PRINTER_STATUS_PRINTING equ 0x00000400
PRINTER_STATUS_OUTPUT_BIN_FULL equ 0x00000800
PRINTER_STATUS_NOT_AVAILABLE equ 0x00001000
PRINTER_STATUS_WAITING	equ 0x00002000
PRINTER_STATUS_PROCESSING equ 0x00004000
PRINTER_STATUS_INITIALIZING equ 0x00008000
PRINTER_STATUS_WARMING_UP equ 0x00010000
PRINTER_STATUS_TONER_LOW equ 0x00020000
PRINTER_STATUS_NO_TONER equ 0x00040000
PRINTER_STATUS_PAGE_PUNT equ 0x00080000
PRINTER_STATUS_USER_INTERVENTION equ 0x00100000
PRINTER_STATUS_OUT_OF_MEMORY equ 0x00200000
PRINTER_STATUS_DOOR_OPEN equ 0x00400000
PRINTER_STATUS_SERVER_UNKNOWN equ 0x00800000
PRINTER_STATUS_POWER_SAVE equ 0x01000000

PRINTER_ATTRIBUTE_QUEUED equ 0x00000001
PRINTER_ATTRIBUTE_DIRECT equ 0x00000002
PRINTER_ATTRIBUTE_DEFAULT equ 0x00000004
PRINTER_ATTRIBUTE_SHARED equ 0x00000008
PRINTER_ATTRIBUTE_NETWORK equ 0x00000010
PRINTER_ATTRIBUTE_HIDDEN equ 0x00000020
PRINTER_ATTRIBUTE_LOCAL equ 0x00000040

PRINTER_ATTRIBUTE_ENABLE_DEVQ equ 0x00000080
PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS equ 0x00000100
PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST equ 0x00000200

PRINTER_ATTRIBUTE_WORK_OFFLINE equ 0x00000400
PRINTER_ATTRIBUTE_ENABLE_BIDI equ 0x00000800
PRINTER_ATTRIBUTE_RAW_ONLY equ 0x00001000
PRINTER_ATTRIBUTE_PUBLISHED equ 0x00002000


NO_PRIORITY		equ 0
MAX_PRIORITY		equ 99
MIN_PRIORITY		equ 1
DEF_PRIORITY		equ 1

JOB_INFO_1A		STRUC
JobId			dd ?
pPrinterName		LPSTR ?
pMachineName		LPSTR ?
pUserName		LPSTR ?
pDocument		LPSTR ?
pDatatype		LPSTR ?
pStatus			LPSTR ?
Status			dd ?
Priority		dd ?
Position		dd ?
TotalPages		dd ?
PagesPrinted		dd ?
Submitted		SYSTEMTIME <>
JOB_INFO_1A		ENDS
PJOB_INFO_1A		typedef ptr JOB_INFO_1A
LPJOB_INFO_1A		typedef ptr JOB_INFO_1A
JOB_INFO_1W		STRUC
JobId			dd ?
pPrinterName		LPWSTR ?
pMachineName		LPWSTR ?
pUserName		LPWSTR ?
pDocument		LPWSTR ?
pDatatype		LPWSTR ?
pStatus			LPWSTR ?
Status			dd ?
Priority		dd ?
Position		dd ?
TotalPages		dd ?
PagesPrinted		dd ?
Submitted		SYSTEMTIME <>
JOB_INFO_1W		ENDS
PJOB_INFO_1W		typedef ptr JOB_INFO_1W
LPJOB_INFO_1W		typedef ptr JOB_INFO_1W
ifdef _UNICODE
JOB_INFO_1		typedef JOB_INFO_1W
PJOB_INFO_1		typedef PJOB_INFO_1W
LPJOB_INFO_1		typedef LPJOB_INFO_1W
else
JOB_INFO_1		typedef JOB_INFO_1A
PJOB_INFO_1		typedef PJOB_INFO_1A
LPJOB_INFO_1		typedef LPJOB_INFO_1A
endif

JOB_INFO_2A		STRUC
JobId			dd ?
pPrinterName		LPSTR ?
pMachineName		LPSTR ?
pUserName		LPSTR ?
pDocument		LPSTR ?
pNotifyName		LPSTR ?
pDatatype		LPSTR ?
pPrintProcessor		LPSTR ?
pParameters		LPSTR ?
pDriverName		LPSTR ?
pDevMode		LPDEVMODEA ?
pStatus			LPSTR ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
Status			dd ?
Priority		dd ?
Position		dd ?
StartTime		dd ?
UntilTime		dd ?
TotalPages		dd ?
Size			dd ?
Submitted		SYSTEMTIME <>
Time			dd ?
PagesPrinted		dd ?
JOB_INFO_2A		ENDS
PJOB_INFO_2A		typedef ptr JOB_INFO_2A
LPJOB_INFO_2A		typedef ptr JOB_INFO_2A
JOB_INFO_2W		STRUC
JobId			dd ?
pPrinterName		LPWSTR ?
pMachineName		LPWSTR ?
pUserName		LPWSTR ?
pDocument		LPWSTR ?
pNotifyName		LPWSTR ?
pDatatype		LPWSTR ?
pPrintProcessor		LPWSTR ?
pParameters		LPWSTR ?
pDriverName		LPWSTR ?
pDevMode		LPDEVMODEW ?
pStatus			LPWSTR ?
pSecurityDescriptor	PSECURITY_DESCRIPTOR ?
Status			dd ?
Priority		dd ?
Position		dd ?
StartTime		dd ?
UntilTime		dd ?
TotalPages		dd ?
Size			dd ?
Submitted		SYSTEMTIME <>
Time			dd ?
PagesPrinted		dd ?
JOB_INFO_2W		ENDS
PJOB_INFO_2W		typedef ptr JOB_INFO_2W
LPJOB_INFO_2W		typedef ptr JOB_INFO_2W
ifdef _UNICODE
JOB_INFO_2		typedef JOB_INFO_2W
PJOB_INFO_2		typedef PJOB_INFO_2W
LPJOB_INFO_2		typedef LPJOB_INFO_2W
else
JOB_INFO_2		typedef JOB_INFO_2A
PJOB_INFO_2		typedef PJOB_INFO_2A
LPJOB_INFO_2		typedef LPJOB_INFO_2A
endif

JOB_INFO_3		STRUC
JobId			dd ?
NextJobId		dd ?
Reserved		dd ?
JOB_INFO_3		ENDS
PJOB_INFO_3		typedef ptr JOB_INFO_3
LPJOB_INFO_3		typedef ptr JOB_INFO_3

JOB_CONTROL_PAUSE	equ 1
JOB_CONTROL_RESUME	equ 2
JOB_CONTROL_CANCEL	equ 3
JOB_CONTROL_RESTART	equ 4
JOB_CONTROL_DELETE	equ 5
JOB_CONTROL_SENT_TO_PRINTER equ 6
JOB_CONTROL_LAST_PAGE_EJECTED equ 7

JOB_STATUS_PAUSED	equ 0x00000001
JOB_STATUS_ERROR	equ 0x00000002
JOB_STATUS_DELETING	equ 0x00000004
JOB_STATUS_SPOOLING	equ 0x00000008
JOB_STATUS_PRINTING	equ 0x00000010
JOB_STATUS_OFFLINE	equ 0x00000020
JOB_STATUS_PAPEROUT	equ 0x00000040
JOB_STATUS_PRINTED	equ 0x00000080
JOB_STATUS_DELETED	equ 0x00000100
JOB_STATUS_BLOCKED_DEVQ equ 0x00000200
JOB_STATUS_USER_INTERVENTION equ 0x00000400
JOB_STATUS_RESTART	equ 0x00000800

JOB_POSITION_UNSPECIFIED equ 0

ADDJOB_INFO_1A		STRUC
Path			LPSTR ?
JobId			dd ?
ADDJOB_INFO_1A		ENDS
PADDJOB_INFO_1A		typedef ptr ADDJOB_INFO_1A
LPADDJOB_INFO_1A	typedef ptr ADDJOB_INFO_1A
ADDJOB_INFO_1W		STRUC
Path			LPWSTR ?
JobId			dd ?
ADDJOB_INFO_1W		ENDS
PADDJOB_INFO_1W		typedef ptr ADDJOB_INFO_1W
LPADDJOB_INFO_1W	typedef ptr ADDJOB_INFO_1W
ifdef _UNICODE
ADDJOB_INFO_1		typedef ADDJOB_INFO_1W
PADDJOB_INFO_1		typedef PADDJOB_INFO_1W
LPADDJOB_INFO_1		typedef LPADDJOB_INFO_1W
else
ADDJOB_INFO_1		typedef ADDJOB_INFO_1A
PADDJOB_INFO_1		typedef PADDJOB_INFO_1A
LPADDJOB_INFO_1		typedef LPADDJOB_INFO_1A
endif

DRIVER_INFO_1A		STRUC
pName			LPSTR ?
DRIVER_INFO_1A		ENDS
PDRIVER_INFO_1A		typedef ptr DRIVER_INFO_1A
LPDRIVER_INFO_1A	typedef ptr DRIVER_INFO_1A
DRIVER_INFO_1W		STRUC
pName			LPWSTR ?
DRIVER_INFO_1W		ENDS
PDRIVER_INFO_1W		typedef ptr DRIVER_INFO_1W
LPDRIVER_INFO_1W	typedef ptr DRIVER_INFO_1W
ifdef _UNICODE
DRIVER_INFO_1		typedef DRIVER_INFO_1W
PDRIVER_INFO_1		typedef PDRIVER_INFO_1W
LPDRIVER_INFO_1		typedef LPDRIVER_INFO_1W
else
DRIVER_INFO_1		typedef DRIVER_INFO_1A
PDRIVER_INFO_1		typedef PDRIVER_INFO_1A
LPDRIVER_INFO_1		typedef LPDRIVER_INFO_1A
endif

DRIVER_INFO_2A		STRUC
cVersion		dd ?
pName			LPSTR ?
pEnvironment		LPSTR ?
pDriverPath		LPSTR ?
pDataFile		LPSTR ?
pConfigFile		LPSTR ?
DRIVER_INFO_2A		ENDS
PDRIVER_INFO_2A		typedef ptr DRIVER_INFO_2A
LPDRIVER_INFO_2A	typedef ptr DRIVER_INFO_2A
DRIVER_INFO_2W		STRUC
cVersion		dd ?
pName			LPWSTR ?
pEnvironment		LPWSTR ?
pDriverPath		LPWSTR ?
pDataFile		LPWSTR ?
pConfigFile		LPWSTR ?
DRIVER_INFO_2W		ENDS
PDRIVER_INFO_2W		typedef ptr DRIVER_INFO_2W
LPDRIVER_INFO_2W	typedef ptr DRIVER_INFO_2W
ifdef _UNICODE
DRIVER_INFO_2		typedef DRIVER_INFO_2W
PDRIVER_INFO_2		typedef PDRIVER_INFO_2W
LPDRIVER_INFO_2		typedef LPDRIVER_INFO_2W
else
DRIVER_INFO_2		typedef DRIVER_INFO_2A
PDRIVER_INFO_2		typedef PDRIVER_INFO_2A
LPDRIVER_INFO_2		typedef LPDRIVER_INFO_2A
endif

DRIVER_INFO_3A		STRUC
cVersion		dd ?
pName			LPSTR ?
pEnvironment		LPSTR ?
pDriverPath		LPSTR ?
pDataFile		LPSTR ?
pConfigFile		LPSTR ?
pHelpFile		LPSTR ?
pDependentFiles		LPSTR ?
pMonitorName		LPSTR ?
pDefaultDataType	LPSTR ?
DRIVER_INFO_3A		ENDS
PDRIVER_INFO_3A		typedef ptr DRIVER_INFO_3A
LPDRIVER_INFO_3A	typedef ptr DRIVER_INFO_3A
DRIVER_INFO_3W		STRUC
cVersion		dd ?
pName			LPWSTR ?
pEnvironment		LPWSTR ?
pDriverPath		LPWSTR ?
pDataFile		LPWSTR ?
pConfigFile		LPWSTR ?
pHelpFile		LPWSTR ?
pDependentFiles		LPWSTR ?
pMonitorName		LPWSTR ?
pDefaultDataType	LPWSTR ?
DRIVER_INFO_3W		ENDS
PDRIVER_INFO_3W		typedef ptr DRIVER_INFO_3W
LPDRIVER_INFO_3W	typedef ptr DRIVER_INFO_3W
ifdef _UNICODE
DRIVER_INFO_3		typedef DRIVER_INFO_3W
PDRIVER_INFO_3		typedef PDRIVER_INFO_3W
LPDRIVER_INFO_3		typedef LPDRIVER_INFO_3W
else
DRIVER_INFO_3		typedef DRIVER_INFO_3A
PDRIVER_INFO_3		typedef PDRIVER_INFO_3A
LPDRIVER_INFO_3		typedef LPDRIVER_INFO_3A
endif

DPD_DELETE_UNUSED_FILES equ 0x00000001
DPD_DELETE_SPECIFIC_VERSION equ 0x00000002
DPD_DELETE_ALL_FILES	equ 0x00000004

APD_STRICT_UPGRADE	equ 0x00000001
APD_STRICT_DOWNGRADE	equ 0x00000002
APD_COPY_ALL_FILES	equ 0x00000004
APD_COPY_NEW_FILES	equ 0x00000008

DOC_INFO_1A		STRUC
pDocName		LPSTR ?
pOutputFile		LPSTR ?
pDatatype		LPSTR ?
DOC_INFO_1A		ENDS
PDOC_INFO_1A		typedef ptr DOC_INFO_1A
LPDOC_INFO_1A		typedef ptr DOC_INFO_1A
DOC_INFO_1W		STRUC
pDocName		LPWSTR ?
pOutputFile		LPWSTR ?
pDatatype		LPWSTR ?
DOC_INFO_1W		ENDS
PDOC_INFO_1W		typedef ptr DOC_INFO_1W
LPDOC_INFO_1W		typedef ptr DOC_INFO_1W
ifdef _UNICODE
DOC_INFO_1		typedef DOC_INFO_1W
PDOC_INFO_1		typedef PDOC_INFO_1W
LPDOC_INFO_1		typedef LPDOC_INFO_1W
else
DOC_INFO_1		typedef DOC_INFO_1A
PDOC_INFO_1		typedef PDOC_INFO_1A
LPDOC_INFO_1		typedef LPDOC_INFO_1A
endif

FORM_INFO_1A		STRUC
Flags			dd ?
pName			LPSTR ?
Size			SIZEL <>
ImageableArea		RECTL <>
FORM_INFO_1A		ENDS
PFORM_INFO_1A		typedef ptr FORM_INFO_1A
LPFORM_INFO_1A		typedef ptr FORM_INFO_1A
FORM_INFO_1W		STRUC
Flags			dd ?
pName			LPWSTR ?
Size			SIZEL <>
ImageableArea		RECTL <>
FORM_INFO_1W		ENDS
PFORM_INFO_1W		typedef ptr FORM_INFO_1W
LPFORM_INFO_1W		typedef ptr FORM_INFO_1W
ifdef _UNICODE
FORM_INFO_1		typedef FORM_INFO_1W
PFORM_INFO_1		typedef PFORM_INFO_1W
LPFORM_INFO_1		typedef LPFORM_INFO_1W
else
FORM_INFO_1		typedef FORM_INFO_1A
PFORM_INFO_1		typedef PFORM_INFO_1A
LPFORM_INFO_1		typedef LPFORM_INFO_1A
endif

DOC_INFO_2A		STRUC
pDocName		LPSTR ?
pOutputFile		LPSTR ?
pDatatype		LPSTR ?
dwMode			dd ?
JobId			dd ?
DOC_INFO_2A		ENDS
PDOC_INFO_2A		typedef ptr DOC_INFO_2A
LPDOC_INFO_2A		typedef ptr DOC_INFO_2A
DOC_INFO_2W		STRUC
pDocName		LPWSTR ?
pOutputFile		LPWSTR ?
pDatatype		LPWSTR ?
dwMode			dd ?
JobId			dd ?
DOC_INFO_2W		ENDS
PDOC_INFO_2W		typedef ptr DOC_INFO_2W
LPDOC_INFO_2W		typedef ptr DOC_INFO_2W
ifdef _UNICODE
DOC_INFO_2		typedef DOC_INFO_2W
PDOC_INFO_2		typedef PDOC_INFO_2W
LPDOC_INFO_2		typedef LPDOC_INFO_2W
else
DOC_INFO_2		typedef DOC_INFO_2A
PDOC_INFO_2		typedef PDOC_INFO_2A
LPDOC_INFO_2		typedef LPDOC_INFO_2A
endif

DI_CHANNEL		equ 1
DI_READ_SPOOL_JOB	equ 3

FORM_USER		equ 0x00000000
FORM_BUILTIN		equ 0x00000001
FORM_PRINTER		equ 0x00000002

PRINTPROCESSOR_INFO_1A	STRUC
pName			LPSTR ?
PRINTPROCESSOR_INFO_1A	ENDS
PPRINTPROCESSOR_INFO_1A typedef ptr PRINTPROCESSOR_INFO_1A
LPPRINTPROCESSOR_INFO_1A typedef ptr PRINTPROCESSOR_INFO_1A
PRINTPROCESSOR_INFO_1W	STRUC
pName			LPWSTR ?
PRINTPROCESSOR_INFO_1W	ENDS
PPRINTPROCESSOR_INFO_1W typedef ptr PRINTPROCESSOR_INFO_1W
LPPRINTPROCESSOR_INFO_1W typedef ptr PRINTPROCESSOR_INFO_1W
ifdef _UNICODE
PRINTPROCESSOR_INFO_1	typedef PRINTPROCESSOR_INFO_1W
PPRINTPROCESSOR_INFO_1	typedef PPRINTPROCESSOR_INFO_1W
LPPRINTPROCESSOR_INFO_1 typedef LPPRINTPROCESSOR_INFO_1W
else
PRINTPROCESSOR_INFO_1	typedef PRINTPROCESSOR_INFO_1A
PPRINTPROCESSOR_INFO_1	typedef PPRINTPROCESSOR_INFO_1A
LPPRINTPROCESSOR_INFO_1 typedef LPPRINTPROCESSOR_INFO_1A
endif

PRINTPROCESSOR_CAPS_1	STRUC
dwLevel			dd ?
dwNupOptions		dd ?
dwPageOrderFlags	dd ?
dwNumberOfCopies	dd ?
PRINTPROCESSOR_CAPS_1	ENDS
PPRINTPROCESSOR_CAPS_1	typedef ptr PRINTPROCESSOR_CAPS_1

PORT_INFO_1A		STRUC
pName			LPSTR ?
PORT_INFO_1A		ENDS
PPORT_INFO_1A		typedef ptr PORT_INFO_1A
LPPORT_INFO_1A		typedef ptr PORT_INFO_1A
PORT_INFO_1W		STRUC
pName			LPWSTR ?
PORT_INFO_1W		ENDS
PPORT_INFO_1W		typedef ptr PORT_INFO_1W
LPPORT_INFO_1W		typedef ptr PORT_INFO_1W
ifdef _UNICODE
PORT_INFO_1		typedef PORT_INFO_1W
PPORT_INFO_1		typedef PPORT_INFO_1W
LPPORT_INFO_1		typedef LPPORT_INFO_1W
else
PORT_INFO_1		typedef PORT_INFO_1A
PPORT_INFO_1		typedef PPORT_INFO_1A
LPPORT_INFO_1		typedef LPPORT_INFO_1A
endif

PORT_INFO_2A		STRUC
pPortName		LPSTR ?
pMonitorName		LPSTR ?
pDescription		LPSTR ?
fPortType		dd ?
Reserved		dd ?
PORT_INFO_2A		ENDS
PPORT_INFO_2A		typedef ptr PORT_INFO_2A
LPPORT_INFO_2A		typedef ptr PORT_INFO_2A
PORT_INFO_2W		STRUC
pPortName		LPWSTR ?
pMonitorName		LPWSTR ?
pDescription		LPWSTR ?
fPortType		dd ?
Reserved		dd ?
PORT_INFO_2W		ENDS
PPORT_INFO_2W		typedef ptr PORT_INFO_2W
LPPORT_INFO_2W		typedef ptr PORT_INFO_2W
ifdef _UNICODE
PORT_INFO_2		typedef PORT_INFO_2W
PPORT_INFO_2		typedef PPORT_INFO_2W
LPPORT_INFO_2		typedef LPPORT_INFO_2W
else
PORT_INFO_2		typedef PORT_INFO_2A
PPORT_INFO_2		typedef PPORT_INFO_2A
LPPORT_INFO_2		typedef LPPORT_INFO_2A
endif

PORT_TYPE_WRITE		equ 0x0001
PORT_TYPE_READ		equ 0x0002
PORT_TYPE_REDIRECTED	equ 0x0004
PORT_TYPE_NET_ATTACHED	equ 0x0008

PORT_INFO_3A		STRUC
dwStatus		dd ?
pszStatus		LPSTR ?
dwSeverity		dd ?
PORT_INFO_3A		ENDS
PPORT_INFO_3A		typedef ptr PORT_INFO_3A
LPPORT_INFO_3A		typedef ptr PORT_INFO_3A
PORT_INFO_3W		STRUC
dwStatus		dd ?
pszStatus		LPWSTR ?
dwSeverity		dd ?
PORT_INFO_3W		ENDS
PPORT_INFO_3W		typedef ptr PORT_INFO_3W
LPPORT_INFO_3W		typedef ptr PORT_INFO_3W
ifdef _UNICODE
PORT_INFO_3		typedef PORT_INFO_3W
PPORT_INFO_3		typedef PPORT_INFO_3W
LPPORT_INFO_3		typedef LPPORT_INFO_3W
else
PORT_INFO_3		typedef PORT_INFO_3A
PPORT_INFO_3		typedef PPORT_INFO_3A
LPPORT_INFO_3		typedef LPPORT_INFO_3A
endif

PORT_STATUS_TYPE_ERROR	equ 1
PORT_STATUS_TYPE_WARNING equ 2
PORT_STATUS_TYPE_INFO	equ 3

PORT_STATUS_OFFLINE	equ 1
PORT_STATUS_PAPER_JAM	equ 2
PORT_STATUS_PAPER_OUT	equ 3
PORT_STATUS_OUTPUT_BIN_FULL equ 4
PORT_STATUS_PAPER_PROBLEM equ 5
PORT_STATUS_NO_TONER	equ 6
PORT_STATUS_DOOR_OPEN	equ 7
PORT_STATUS_USER_INTERVENTION equ 8
PORT_STATUS_OUT_OF_MEMORY equ 9
PORT_STATUS_TONER_LOW	equ 10
PORT_STATUS_WARMING_UP	equ 11
PORT_STATUS_POWER_SAVE	equ 12

MONITOR_INFO_1A		STRUC
pName			LPSTR ?
MONITOR_INFO_1A		ENDS
PMONITOR_INFO_1A	typedef ptr MONITOR_INFO_1A
LPMONITOR_INFO_1A	typedef ptr MONITOR_INFO_1A
MONITOR_INFO_1W		STRUC
pName			LPWSTR ?
MONITOR_INFO_1W		ENDS
PMONITOR_INFO_1W	typedef ptr MONITOR_INFO_1W
LPMONITOR_INFO_1W	typedef ptr MONITOR_INFO_1W
ifdef _UNICODE
MONITOR_INFO_1		typedef MONITOR_INFO_1W
PMONITOR_INFO_1		typedef PMONITOR_INFO_1W
LPMONITOR_INFO_1	typedef LPMONITOR_INFO_1W
else
MONITOR_INFO_1		typedef MONITOR_INFO_1A
PMONITOR_INFO_1		typedef PMONITOR_INFO_1A
LPMONITOR_INFO_1	typedef LPMONITOR_INFO_1A
endif

MONITOR_INFO_2A		STRUC
pName			LPSTR ?
pEnvironment		LPSTR ?
pDLLName		LPSTR ?
MONITOR_INFO_2A		ENDS
PMONITOR_INFO_2A	typedef ptr MONITOR_INFO_2A
LPMONITOR_INFO_2A	typedef ptr MONITOR_INFO_2A
MONITOR_INFO_2W		STRUC
pName			LPWSTR ?
pEnvironment		LPWSTR ?
pDLLName		LPWSTR ?
MONITOR_INFO_2W		ENDS
PMONITOR_INFO_2W	typedef ptr MONITOR_INFO_2W
LPMONITOR_INFO_2W	typedef ptr MONITOR_INFO_2W
ifdef _UNICODE
MONITOR_INFO_2		typedef MONITOR_INFO_2W
PMONITOR_INFO_2		typedef PMONITOR_INFO_2W
LPMONITOR_INFO_2	typedef LPMONITOR_INFO_2W
else
MONITOR_INFO_2		typedef MONITOR_INFO_2A
PMONITOR_INFO_2		typedef PMONITOR_INFO_2A
LPMONITOR_INFO_2	typedef LPMONITOR_INFO_2A
endif

DATATYPES_INFO_1A	STRUC
pName			LPSTR ?
DATATYPES_INFO_1A	ENDS
PDATATYPES_INFO_1A	typedef ptr DATATYPES_INFO_1A
LPDATATYPES_INFO_1A	typedef ptr DATATYPES_INFO_1A
DATATYPES_INFO_1W	STRUC
pName			LPWSTR ?
DATATYPES_INFO_1W	ENDS
PDATATYPES_INFO_1W	typedef ptr DATATYPES_INFO_1W
LPDATATYPES_INFO_1W	typedef ptr DATATYPES_INFO_1W
ifdef _UNICODE
DATATYPES_INFO_1	typedef DATATYPES_INFO_1W
PDATATYPES_INFO_1	typedef PDATATYPES_INFO_1W
LPDATATYPES_INFO_1	typedef LPDATATYPES_INFO_1W
else
DATATYPES_INFO_1	typedef DATATYPES_INFO_1A
PDATATYPES_INFO_1	typedef PDATATYPES_INFO_1A
LPDATATYPES_INFO_1	typedef LPDATATYPES_INFO_1A
endif

PRINTER_DEFAULTSA	STRUC
pDatatype		LPSTR ?
pDevMode		LPDEVMODEA ?
DesiredAccess		ACCESS_MASK ?
PRINTER_DEFAULTSA	ENDS
PPRINTER_DEFAULTSA	typedef ptr PRINTER_DEFAULTSA
LPPRINTER_DEFAULTSA	typedef ptr PRINTER_DEFAULTSA
PRINTER_DEFAULTSW	STRUC
pDatatype		LPWSTR ?
pDevMode		LPDEVMODEW ?
DesiredAccess		ACCESS_MASK ?
PRINTER_DEFAULTSW	ENDS
PPRINTER_DEFAULTSW	typedef ptr PRINTER_DEFAULTSW
LPPRINTER_DEFAULTSW	typedef ptr PRINTER_DEFAULTSW
ifdef _UNICODE
PRINTER_DEFAULTS	typedef PRINTER_DEFAULTSW
PPRINTER_DEFAULTS	typedef PPRINTER_DEFAULTSW
LPPRINTER_DEFAULTS	typedef LPPRINTER_DEFAULTSW
else
PRINTER_DEFAULTS	typedef PRINTER_DEFAULTSA
PPRINTER_DEFAULTS	typedef PPRINTER_DEFAULTSA
LPPRINTER_DEFAULTS	typedef LPPRINTER_DEFAULTSA
endif

PRINTER_ENUM_VALUESA	STRUC
pValueName		LPSTR ?
cbValueName		dd ?
dwType			dd ?
pData			LPBYTE ?
cbData			dd ?
PRINTER_ENUM_VALUESA	ENDS
PPRINTER_ENUM_VALUESA	typedef ptr PRINTER_ENUM_VALUESA
LPPRINTER_ENUM_VALUESA	typedef ptr PRINTER_ENUM_VALUESA
PRINTER_ENUM_VALUESW	STRUC
pValueName		LPWSTR ?
cbValueName		dd ?
dwType			dd ?
pData			LPBYTE ?
cbData			dd ?
PRINTER_ENUM_VALUESW	ENDS
PPRINTER_ENUM_VALUESW	typedef ptr PRINTER_ENUM_VALUESW
LPPRINTER_ENUM_VALUESW	typedef ptr PRINTER_ENUM_VALUESW
ifdef _UNICODE
PRINTER_ENUM_VALUES	typedef PRINTER_ENUM_VALUESW
PPRINTER_ENUM_VALUES	typedef PPRINTER_ENUM_VALUESW
LPPRINTER_ENUM_VALUES	typedef LPPRINTER_ENUM_VALUESW
else
PRINTER_ENUM_VALUES	typedef PRINTER_ENUM_VALUESA
PPRINTER_ENUM_VALUES	typedef PPRINTER_ENUM_VALUESA
LPPRINTER_ENUM_VALUES	typedef LPPRINTER_ENUM_VALUESA
endif

;BOOL
EnumPrintersA proto WINAPI \
		 Flags: DWORD,
		  Name: LPSTR,
		 Level: DWORD,
	  pPrinterEnum: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumPrintersW proto WINAPI \
		 Flags: DWORD,
		  Name: LPWSTR,
		 Level: DWORD,
	  pPrinterEnum: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumPrinters		equ <EnumPrintersW>
else
EnumPrinters		equ <EnumPrintersA>
endif

PRINTER_ENUM_DEFAULT	equ 0x00000001
PRINTER_ENUM_LOCAL	equ 0x00000002
PRINTER_ENUM_CONNECTIONS equ 0x00000004
PRINTER_ENUM_FAVORITE	equ 0x00000004
PRINTER_ENUM_NAME	equ 0x00000008
PRINTER_ENUM_REMOTE	equ 0x00000010
PRINTER_ENUM_SHARED	equ 0x00000020
PRINTER_ENUM_NETWORK	equ 0x00000040
PRINTER_ENUM_EXPAND	equ 0x00004000
PRINTER_ENUM_CONTAINER	equ 0x00008000
PRINTER_ENUM_ICONMASK	equ 0x00ff0000
PRINTER_ENUM_ICON1	equ 0x00010000
PRINTER_ENUM_ICON2	equ 0x00020000
PRINTER_ENUM_ICON3	equ 0x00040000
PRINTER_ENUM_ICON4	equ 0x00080000
PRINTER_ENUM_ICON5	equ 0x00100000
PRINTER_ENUM_ICON6	equ 0x00200000
PRINTER_ENUM_ICON7	equ 0x00400000
PRINTER_ENUM_ICON8	equ 0x00800000

;BOOL
OpenPrinterA proto WINAPI \
	  pPrinterName: LPSTR,
	     phPrinter: LPHANDLE,
	      pDefault: LPPRINTER_DEFAULTSA
;BOOL
OpenPrinterW proto WINAPI \
	  pPrinterName: LPWSTR,
	     phPrinter: LPHANDLE,
	      pDefault: LPPRINTER_DEFAULTSW
ifdef _UNICODE
OpenPrinter		equ <OpenPrinterW>
else
OpenPrinter		equ <OpenPrinterA>
endif

;BOOL
ResetPrinterA proto WINAPI \
	      hPrinter: HANDLE,
	      pDefault: LPPRINTER_DEFAULTSA
;BOOL
ResetPrinterW proto WINAPI \
	      hPrinter: HANDLE,
	      pDefault: LPPRINTER_DEFAULTSW
ifdef _UNICODE
ResetPrinter		equ <ResetPrinterW>
else
ResetPrinter		equ <ResetPrinterA>
endif

;BOOL
SetJobA proto WINAPI \
	      hPrinter: HANDLE,
		 JobId: DWORD,
		 Level: DWORD,
		  pJob: LPBYTE,
	       Command: DWORD
;BOOL
SetJobW proto WINAPI \
	      hPrinter: HANDLE,
		 JobId: DWORD,
		 Level: DWORD,
		  pJob: LPBYTE,
	       Command: DWORD
ifdef _UNICODE
SetJob			equ <SetJobW>
else
SetJob			equ <SetJobA>
endif

;BOOL
GetJobA proto WINAPI \
	      hPrinter: HANDLE,
		 JobId: DWORD,
		 Level: DWORD,
		  pJob: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
;BOOL
GetJobW proto WINAPI \
	      hPrinter: HANDLE,
		 JobId: DWORD,
		 Level: DWORD,
		  pJob: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetJob			equ <GetJobW>
else
GetJob			equ <GetJobA>
endif

;BOOL
EnumJobsA proto WINAPI \
	      hPrinter: HANDLE,
	      FirstJob: DWORD,
		NoJobs: DWORD,
		 Level: DWORD,
		  pJob: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumJobsW proto WINAPI \
	      hPrinter: HANDLE,
	      FirstJob: DWORD,
		NoJobs: DWORD,
		 Level: DWORD,
		  pJob: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumJobs		equ <EnumJobsW>
else
EnumJobs		equ <EnumJobsA>
endif

;HANDLE
AddPrinterA proto WINAPI \
		 pName: LPSTR,
		 Level: DWORD,
	      pPrinter: LPBYTE
;HANDLE
AddPrinterW proto WINAPI \
		 pName: LPWSTR,
		 Level: DWORD,
	      pPrinter: LPBYTE
ifdef _UNICODE
AddPrinter		equ <AddPrinterW>
else
AddPrinter		equ <AddPrinterA>
endif

;BOOL
DeletePrinter proto WINAPI \
	      hPrinter: HANDLE

;BOOL
SetPrinterA proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
	      pPrinter: LPBYTE,
	       Command: DWORD
;BOOL
SetPrinterW proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
	      pPrinter: LPBYTE,
	       Command: DWORD
ifdef _UNICODE
SetPrinter		equ <SetPrinterW>
else
SetPrinter		equ <SetPrinterA>
endif

;BOOL
GetPrinterA proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
	      pPrinter: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
;BOOL
GetPrinterW proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
	      pPrinter: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetPrinter		equ <GetPrinterW>
else
GetPrinter		equ <GetPrinterA>
endif

;BOOL
AddPrinterDriverA proto WINAPI \
		 pName: LPSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE
;BOOL
AddPrinterDriverW proto WINAPI \
		 pName: LPWSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE
ifdef _UNICODE
AddPrinterDriver	equ <AddPrinterDriverW>
else
AddPrinterDriver	equ <AddPrinterDriverA>
endif

;BOOL
AddPrinterDriverExA proto WINAPI \
		 pName: LPSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE,
       dwFileCopyFlags: DWORD
;BOOL
AddPrinterDriverExW proto WINAPI \
		 pName: LPWSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE,
       dwFileCopyFlags: DWORD
ifdef _UNICODE
AddPrinterDriverEx	equ <AddPrinterDriverExW>
else
AddPrinterDriverEx	equ <AddPrinterDriverExA>
endif

;BOOL
EnumPrinterDriversA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumPrinterDriversW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumPrinterDrivers	equ <EnumPrinterDriversW>
else
EnumPrinterDrivers	equ <EnumPrinterDriversA>
endif

;BOOL
GetPrinterDriverA proto WINAPI \
	      hPrinter: HANDLE,
	  pEnvironment: LPSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
;BOOL
GetPrinterDriverW proto WINAPI \
	      hPrinter: HANDLE,
	  pEnvironment: LPWSTR,
		 Level: DWORD,
	   pDriverInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetPrinterDriver	equ <GetPrinterDriverW>
else
GetPrinterDriver	equ <GetPrinterDriverA>
endif

;BOOL
GetPrinterDriverDirectoryA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
		 Level: DWORD,
      pDriverDirectory: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
;BOOL
GetPrinterDriverDirectoryW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
		 Level: DWORD,
      pDriverDirectory: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetPrinterDriverDirectory equ <GetPrinterDriverDirectoryW>
else
GetPrinterDriverDirectory equ <GetPrinterDriverDirectoryA>
endif

;BOOL
DeletePrinterDriverA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
	   pDriverName: LPSTR
;BOOL
DeletePrinterDriverW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
	   pDriverName: LPWSTR
ifdef _UNICODE
DeletePrinterDriver	equ <DeletePrinterDriverW>
else
DeletePrinterDriver	equ <DeletePrinterDriverA>
endif

;BOOL
DeletePrinterDriverExA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
	   pDriverName: LPSTR,
	  dwDeleteFlag: DWORD,
	 dwVersionFlag: DWORD
;BOOL
DeletePrinterDriverExW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
	   pDriverName: LPWSTR,
	  dwDeleteFlag: DWORD,
	 dwVersionFlag: DWORD
ifdef _UNICODE
DeletePrinterDriverEx	equ <DeletePrinterDriverExW>
else
DeletePrinterDriverEx	equ <DeletePrinterDriverExA>
endif

;BOOL
AddPerMachineConnectionA proto WINAPI \
	       pServer: LPCSTR,
	  pPrinterName: LPCSTR,
	  pPrintServer: LPCSTR,
	     pProvider: LPCSTR
;BOOL
AddPerMachineConnectionW proto WINAPI \
	       pServer: LPCWSTR,
	  pPrinterName: LPCWSTR,
	  pPrintServer: LPCWSTR,
	     pProvider: LPCWSTR
ifdef _UNICODE
AddPerMachineConnection equ <AddPerMachineConnectionW>
else
AddPerMachineConnection equ <AddPerMachineConnectionA>
endif

;BOOL
DeletePerMachineConnectionA proto WINAPI \
	       pServer: LPCSTR,
	  pPrinterName: LPCSTR
;BOOL
DeletePerMachineConnectionW proto WINAPI \
	       pServer: LPCWSTR,
	  pPrinterName: LPCWSTR
ifdef _UNICODE
DeletePerMachineConnection equ <DeletePerMachineConnectionW>
else
DeletePerMachineConnection equ <DeletePerMachineConnectionA>
endif

;BOOL
EnumPerMachineConnectionsA proto WINAPI \
	       pServer: LPCSTR,
	  pPrinterEnum: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumPerMachineConnectionsW proto WINAPI \
	       pServer: LPCWSTR,
	  pPrinterEnum: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumPerMachineConnections equ <EnumPerMachineConnectionsW>
else
EnumPerMachineConnections equ <EnumPerMachineConnectionsA>
endif

;BOOL
AddPrintProcessorA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
	     pPathName: LPSTR,
   pPrintProcessorName: LPSTR
;BOOL
AddPrintProcessorW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
	     pPathName: LPWSTR,
   pPrintProcessorName: LPWSTR
ifdef _UNICODE
AddPrintProcessor	equ <AddPrintProcessorW>
else
AddPrintProcessor	equ <AddPrintProcessorA>
endif

;BOOL
EnumPrintProcessorsA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
		 Level: DWORD,
   pPrintProcessorInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumPrintProcessorsW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
		 Level: DWORD,
   pPrintProcessorInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumPrintProcessors	equ <EnumPrintProcessorsW>
else
EnumPrintProcessors	equ <EnumPrintProcessorsA>
endif

;BOOL
GetPrintProcessorDirectoryA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
		 Level: DWORD,
   pPrintProcessorInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
;BOOL
GetPrintProcessorDirectoryW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
		 Level: DWORD,
   pPrintProcessorInfo: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetPrintProcessorDirectory equ <GetPrintProcessorDirectoryW>
else
GetPrintProcessorDirectory equ <GetPrintProcessorDirectoryA>
endif

;BOOL
EnumPrintProcessorDatatypesA proto WINAPI \
		 pName: LPSTR,
   pPrintProcessorName: LPSTR,
		 Level: DWORD,
	    pDatatypes: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumPrintProcessorDatatypesW proto WINAPI \
		 pName: LPWSTR,
   pPrintProcessorName: LPWSTR,
		 Level: DWORD,
	    pDatatypes: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumPrintProcessorDatatypes equ <EnumPrintProcessorDatatypesW>
else
EnumPrintProcessorDatatypes equ <EnumPrintProcessorDatatypesA>
endif

;BOOL
DeletePrintProcessorA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
   pPrintProcessorName: LPSTR
;BOOL
DeletePrintProcessorW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
   pPrintProcessorName: LPWSTR
ifdef _UNICODE
DeletePrintProcessor	equ <DeletePrintProcessorW>
else
DeletePrintProcessor	equ <DeletePrintProcessorA>
endif

;DWORD
StartDocPrinterA proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
	      pDocInfo: LPBYTE
;DWORD
StartDocPrinterW proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
	      pDocInfo: LPBYTE
ifdef _UNICODE
StartDocPrinter		equ <StartDocPrinterW>
else
StartDocPrinter		equ <StartDocPrinterA>
endif

;BOOL
StartPagePrinter proto WINAPI \
	      hPrinter: HANDLE

;BOOL
WritePrinter proto WINAPI \
	      hPrinter: HANDLE,
		  pBuf: LPVOID,
		 cbBuf: DWORD,
	     pcWritten: LPDWORD

;BOOL
EndPagePrinter proto WINAPI \
	      hPrinter: HANDLE

;BOOL
AbortPrinter proto WINAPI \
	      hPrinter: HANDLE

;BOOL
ReadPrinter proto WINAPI \
	      hPrinter: HANDLE,
		  pBuf: LPVOID,
		 cbBuf: DWORD,
	  pNoBytesRead: LPDWORD

;BOOL
EndDocPrinter proto WINAPI \
	      hPrinter: HANDLE

;BOOL
AddJobA proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
		 pData: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
;BOOL
AddJobW proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
		 pData: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
AddJob			equ <AddJobW>
else
AddJob			equ <AddJobA>
endif

;BOOL
ScheduleJob proto WINAPI \
	      hPrinter: HANDLE,
		 JobId: DWORD

;BOOL
PrinterProperties proto WINAPI \
		  hWnd: HWND,
	      hPrinter: HANDLE

;LONG
DocumentPropertiesA proto WINAPI \
		  hWnd: HWND,
	      hPrinter: HANDLE,
	   pDeviceName: LPSTR,
	pDevModeOutput: PDEVMODEA,
	 pDevModeInput: PDEVMODEA,
		 fMode: DWORD
;LONG
DocumentPropertiesW proto WINAPI \
		  hWnd: HWND,
	      hPrinter: HANDLE,
	   pDeviceName: LPWSTR,
	pDevModeOutput: PDEVMODEW,
	 pDevModeInput: PDEVMODEW,
		 fMode: DWORD
ifdef _UNICODE
DocumentProperties	equ <DocumentPropertiesW>
else
DocumentProperties	equ <DocumentPropertiesA>
endif

;LONG
AdvancedDocumentPropertiesA proto WINAPI \
		  hWnd: HWND,
	      hPrinter: HANDLE,
	   pDeviceName: LPSTR,
	pDevModeOutput: PDEVMODEA,
	 pDevModeInput: PDEVMODEA
;LONG
AdvancedDocumentPropertiesW proto WINAPI \
		  hWnd: HWND,
	      hPrinter: HANDLE,
	   pDeviceName: LPWSTR,
	pDevModeOutput: PDEVMODEW,
	 pDevModeInput: PDEVMODEW
ifdef _UNICODE
AdvancedDocumentProperties equ <AdvancedDocumentPropertiesW>
else
AdvancedDocumentProperties equ <AdvancedDocumentPropertiesA>
endif

;DWORD
GetPrinterDataA proto WINAPI \
	      hPrinter: HANDLE,
	    pValueName: LPSTR,
		 pType: LPDWORD,
		 pData: LPBYTE,
		 nSize: DWORD,
	     pcbNeeded: LPDWORD
;DWORD
GetPrinterDataW proto WINAPI \
	      hPrinter: HANDLE,
	    pValueName: LPWSTR,
		 pType: LPDWORD,
		 pData: LPBYTE,
		 nSize: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetPrinterData		equ <GetPrinterDataW>
else
GetPrinterData		equ <GetPrinterDataA>
endif

;DWORD
GetPrinterDataExA proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCSTR,
	    pValueName: LPCSTR,
		 pType: LPDWORD,
		 pData: LPBYTE,
		 nSize: DWORD,
	     pcbNeeded: LPDWORD
;DWORD
GetPrinterDataExW proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCWSTR,
	    pValueName: LPCWSTR,
		 pType: LPDWORD,
		 pData: LPBYTE,
		 nSize: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetPrinterDataEx	equ <GetPrinterDataExW>
else
GetPrinterDataEx	equ <GetPrinterDataExA>
endif

;DWORD
EnumPrinterDataA proto WINAPI \
	      hPrinter: HANDLE,
	       dwIndex: DWORD,
	    pValueName: LPSTR,
	   cbValueName: DWORD,
	  pcbValueName: LPDWORD,
		 pType: LPDWORD,
		 pData: LPBYTE,
		cbData: DWORD,
	       pcbData: LPDWORD
;DWORD
EnumPrinterDataW proto WINAPI \
	      hPrinter: HANDLE,
	       dwIndex: DWORD,
	    pValueName: LPWSTR,
	   cbValueName: DWORD,
	  pcbValueName: LPDWORD,
		 pType: LPDWORD,
		 pData: LPBYTE,
		cbData: DWORD,
	       pcbData: LPDWORD
ifdef _UNICODE
EnumPrinterData		equ <EnumPrinterDataW>
else
EnumPrinterData		equ <EnumPrinterDataA>
endif

;DWORD
EnumPrinterDataExA proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCSTR,
	   pEnumValues: LPBYTE,
	  cbEnumValues: DWORD,
	 pcbEnumValues: LPDWORD,
	  pnEnumValues: LPDWORD
;DWORD
EnumPrinterDataExW proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCWSTR,
	   pEnumValues: LPBYTE,
	  cbEnumValues: DWORD,
	 pcbEnumValues: LPDWORD,
	  pnEnumValues: LPDWORD
ifdef _UNICODE
EnumPrinterDataEx	equ <EnumPrinterDataExW>
else
EnumPrinterDataEx	equ <EnumPrinterDataExA>
endif

;DWORD
EnumPrinterKeyA proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCSTR,
	       pSubkey: LPSTR,
	      cbSubkey: DWORD,
	     pcbSubkey: LPDWORD
;DWORD
EnumPrinterKeyW proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCWSTR,
	       pSubkey: LPWSTR,
	      cbSubkey: DWORD,
	     pcbSubkey: LPDWORD
ifdef _UNICODE
EnumPrinterKey		equ <EnumPrinterKeyW>
else
EnumPrinterKey		equ <EnumPrinterKeyA>
endif

;DWORD
SetPrinterDataA proto WINAPI \
	      hPrinter: HANDLE,
	    pValueName: LPSTR,
		  Type: DWORD,
		 pData: LPBYTE,
		cbData: DWORD
;DWORD
SetPrinterDataW proto WINAPI \
	      hPrinter: HANDLE,
	    pValueName: LPWSTR,
		  Type: DWORD,
		 pData: LPBYTE,
		cbData: DWORD
ifdef _UNICODE
SetPrinterData		equ <SetPrinterDataW>
else
SetPrinterData		equ <SetPrinterDataA>
endif

;DWORD
SetPrinterDataExA proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCSTR,
	    pValueName: LPCSTR,
		  Type: DWORD,
		 pData: LPBYTE,
		cbData: DWORD
;DWORD
SetPrinterDataExW proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCWSTR,
	    pValueName: LPCWSTR,
		  Type: DWORD,
		 pData: LPBYTE,
		cbData: DWORD
ifdef _UNICODE
SetPrinterDataEx	equ <SetPrinterDataExW>
else
SetPrinterDataEx	equ <SetPrinterDataExA>
endif

;DWORD
DeletePrinterDataA proto WINAPI \
	      hPrinter: HANDLE,
	    pValueName: LPSTR
;DWORD
DeletePrinterDataW proto WINAPI \
	      hPrinter: HANDLE,
	    pValueName: LPWSTR
ifdef _UNICODE
DeletePrinterData	equ <DeletePrinterDataW>
else
DeletePrinterData	equ <DeletePrinterDataA>
endif

;DWORD
DeletePrinterDataExA proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCSTR,
	    pValueName: LPCSTR
;DWORD
DeletePrinterDataExW proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCWSTR,
	    pValueName: LPCWSTR
ifdef _UNICODE
DeletePrinterDataEx	equ <DeletePrinterDataExW>
else
DeletePrinterDataEx	equ <DeletePrinterDataExA>
endif

;DWORD
DeletePrinterKeyA proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCSTR
;DWORD
DeletePrinterKeyW proto WINAPI \
	      hPrinter: HANDLE,
	      pKeyName: LPCWSTR
ifdef _UNICODE
DeletePrinterKey	equ <DeletePrinterKeyW>
else
DeletePrinterKey	equ <DeletePrinterKeyA>
endif

PRINTER_NOTIFY_TYPE	equ 0x00
JOB_NOTIFY_TYPE		equ 0x01

PRINTER_NOTIFY_FIELD_SERVER_NAME equ 0x00
PRINTER_NOTIFY_FIELD_PRINTER_NAME equ 0x01
PRINTER_NOTIFY_FIELD_SHARE_NAME equ 0x02
PRINTER_NOTIFY_FIELD_PORT_NAME equ 0x03
PRINTER_NOTIFY_FIELD_DRIVER_NAME equ 0x04
PRINTER_NOTIFY_FIELD_COMMENT equ 0x05
PRINTER_NOTIFY_FIELD_LOCATION equ 0x06
PRINTER_NOTIFY_FIELD_DEVMODE equ 0x07
PRINTER_NOTIFY_FIELD_SEPFILE equ 0x08
PRINTER_NOTIFY_FIELD_PRINT_PROCESSOR equ 0x09
PRINTER_NOTIFY_FIELD_PARAMETERS equ 0x0A
PRINTER_NOTIFY_FIELD_DATATYPE equ 0x0B
PRINTER_NOTIFY_FIELD_SECURITY_DESCRIPTOR equ 0x0C
PRINTER_NOTIFY_FIELD_ATTRIBUTES equ 0x0D
PRINTER_NOTIFY_FIELD_PRIORITY equ 0x0E
PRINTER_NOTIFY_FIELD_DEFAULT_PRIORITY equ 0x0F
PRINTER_NOTIFY_FIELD_START_TIME equ 0x10
PRINTER_NOTIFY_FIELD_UNTIL_TIME equ 0x11
PRINTER_NOTIFY_FIELD_STATUS equ 0x12
PRINTER_NOTIFY_FIELD_STATUS_STRING equ 0x13
PRINTER_NOTIFY_FIELD_CJOBS equ 0x14
PRINTER_NOTIFY_FIELD_AVERAGE_PPM equ 0x15
PRINTER_NOTIFY_FIELD_TOTAL_PAGES equ 0x16
PRINTER_NOTIFY_FIELD_PAGES_PRINTED equ 0x17
PRINTER_NOTIFY_FIELD_TOTAL_BYTES equ 0x18
PRINTER_NOTIFY_FIELD_BYTES_PRINTED equ 0x19
PRINTER_NOTIFY_FIELD_OBJECT_GUID equ 0x1A

JOB_NOTIFY_FIELD_PRINTER_NAME equ 0x00
JOB_NOTIFY_FIELD_MACHINE_NAME equ 0x01
JOB_NOTIFY_FIELD_PORT_NAME equ 0x02
JOB_NOTIFY_FIELD_USER_NAME equ 0x03
JOB_NOTIFY_FIELD_NOTIFY_NAME equ 0x04
JOB_NOTIFY_FIELD_DATATYPE equ 0x05
JOB_NOTIFY_FIELD_PRINT_PROCESSOR equ 0x06
JOB_NOTIFY_FIELD_PARAMETERS equ 0x07
JOB_NOTIFY_FIELD_DRIVER_NAME equ 0x08
JOB_NOTIFY_FIELD_DEVMODE equ 0x09
JOB_NOTIFY_FIELD_STATUS equ 0x0A
JOB_NOTIFY_FIELD_STATUS_STRING equ 0x0B
JOB_NOTIFY_FIELD_SECURITY_DESCRIPTOR equ 0x0C
JOB_NOTIFY_FIELD_DOCUMENT equ 0x0D
JOB_NOTIFY_FIELD_PRIORITY equ 0x0E
JOB_NOTIFY_FIELD_POSITION equ 0x0F
JOB_NOTIFY_FIELD_SUBMITTED equ 0x10
JOB_NOTIFY_FIELD_START_TIME equ 0x11
JOB_NOTIFY_FIELD_UNTIL_TIME equ 0x12
JOB_NOTIFY_FIELD_TIME	equ 0x13
JOB_NOTIFY_FIELD_TOTAL_PAGES equ 0x14
JOB_NOTIFY_FIELD_PAGES_PRINTED equ 0x15
JOB_NOTIFY_FIELD_TOTAL_BYTES equ 0x16
JOB_NOTIFY_FIELD_BYTES_PRINTED equ 0x17

PRINTER_NOTIFY_OPTIONS_TYPE  STRUC
Type			dw ?
Reserved0		dw ?
Reserved1		dd ?
Reserved2		dd ?
Count			dd ?
pFields			PWORD ?
PRINTER_NOTIFY_OPTIONS_TYPE ENDS
PPRINTER_NOTIFY_OPTIONS_TYPE typedef ptr PRINTER_NOTIFY_OPTIONS_TYPE
LPPRINTER_NOTIFY_OPTIONS_TYPE typedef ptr PRINTER_NOTIFY_OPTIONS_TYPE

PRINTER_NOTIFY_OPTIONS_REFRESH equ 0x01

PRINTER_NOTIFY_OPTIONS	STRUC
Version			dd ?
Flags			dd ?
Count			dd ?
pTypes			PPRINTER_NOTIFY_OPTIONS_TYPE ?
PRINTER_NOTIFY_OPTIONS	ENDS
PPRINTER_NOTIFY_OPTIONS typedef ptr PRINTER_NOTIFY_OPTIONS
LPPRINTER_NOTIFY_OPTIONS typedef ptr PRINTER_NOTIFY_OPTIONS

PRINTER_NOTIFY_INFO_DISCARDED equ 0x01

PRINTER_NOTIFY_INFO_DATA  STRUC
Type			dw ?
Field			dw ?
Reserved		dd ?
Id			dd ?
UNION NotifyData
 adwData			dd 2 dup(?)
 STRUC Data
  cbBuf			 dd ?
  pBuf			 LPVOID ?
 ENDS
ENDS
PRINTER_NOTIFY_INFO_DATA ENDS
PPRINTER_NOTIFY_INFO_DATA typedef ptr PRINTER_NOTIFY_INFO_DATA
LPPRINTER_NOTIFY_INFO_DATA typedef ptr PRINTER_NOTIFY_INFO_DATA

PRINTER_NOTIFY_INFO	STRUC
Version			dd ?
Flags			dd ?
Count			dd ?
aData			PRINTER_NOTIFY_INFO_DATA <>
PRINTER_NOTIFY_INFO	ENDS
PPRINTER_NOTIFY_INFO	typedef ptr PRINTER_NOTIFY_INFO
LPPRINTER_NOTIFY_INFO	typedef ptr PRINTER_NOTIFY_INFO

;DWORD
WaitForPrinterChange proto WINAPI \
	      hPrinter: HANDLE,
		 Flags: DWORD

;HANDLE
FindFirstPrinterChangeNotification proto WINAPI \
	      hPrinter: HANDLE,
	      fdwFlags: DWORD,
	    fdwOptions: DWORD,
 pPrinterNotifyOptions: LPVOID

;BOOL
FindNextPrinterChangeNotification proto WINAPI \
	       hChange: HANDLE,
	     pdwChange: PDWORD,
	    pvReserved: LPVOID,
   ppPrinterNotifyInfo: LPVOID

;BOOL
FreePrinterNotifyInfo proto WINAPI \
    pPrinterNotifyInfo: PPRINTER_NOTIFY_INFO

;BOOL
FindClosePrinterChangeNotification proto WINAPI \
	       hChange: HANDLE

PRINTER_CHANGE_ADD_PRINTER equ 0x00000001
PRINTER_CHANGE_SET_PRINTER equ 0x00000002
PRINTER_CHANGE_DELETE_PRINTER equ 0x00000004
PRINTER_CHANGE_FAILED_CONNECTION_PRINTER equ 0x00000008
PRINTER_CHANGE_PRINTER	equ 0x000000FF
PRINTER_CHANGE_ADD_JOB	equ 0x00000100
PRINTER_CHANGE_SET_JOB	equ 0x00000200
PRINTER_CHANGE_DELETE_JOB equ 0x00000400
PRINTER_CHANGE_WRITE_JOB equ 0x00000800
PRINTER_CHANGE_JOB	equ 0x0000FF00
PRINTER_CHANGE_ADD_FORM equ 0x00010000
PRINTER_CHANGE_SET_FORM equ 0x00020000
PRINTER_CHANGE_DELETE_FORM equ 0x00040000
PRINTER_CHANGE_FORM	equ 0x00070000
PRINTER_CHANGE_ADD_PORT equ 0x00100000
PRINTER_CHANGE_CONFIGURE_PORT equ 0x00200000
PRINTER_CHANGE_DELETE_PORT equ 0x00400000
PRINTER_CHANGE_PORT	equ 0x00700000
PRINTER_CHANGE_ADD_PRINT_PROCESSOR equ 0x01000000
PRINTER_CHANGE_DELETE_PRINT_PROCESSOR equ 0x04000000
PRINTER_CHANGE_PRINT_PROCESSOR equ 0x07000000
PRINTER_CHANGE_ADD_PRINTER_DRIVER equ 0x10000000
PRINTER_CHANGE_SET_PRINTER_DRIVER equ 0x20000000
PRINTER_CHANGE_DELETE_PRINTER_DRIVER equ 0x40000000
PRINTER_CHANGE_PRINTER_DRIVER equ 0x70000000
PRINTER_CHANGE_TIMEOUT	equ 0x80000000
PRINTER_CHANGE_ALL	equ 0x7777FFFF

;DWORD
PrinterMessageBoxA proto WINAPI \
	      hPrinter: HANDLE,
		 Error: DWORD,
		  hWnd: HWND,
		 pText: LPSTR,
	      pCaption: LPSTR,
		dwType: DWORD
;DWORD
PrinterMessageBoxW proto WINAPI \
	      hPrinter: HANDLE,
		 Error: DWORD,
		  hWnd: HWND,
		 pText: LPWSTR,
	      pCaption: LPWSTR,
		dwType: DWORD
ifdef _UNICODE
PrinterMessageBox	equ <PrinterMessageBoxW>
else
PrinterMessageBox	equ <PrinterMessageBoxA>
endif

PRINTER_ERROR_INFORMATION equ 0x80000000
PRINTER_ERROR_WARNING	equ 0x40000000
PRINTER_ERROR_SEVERE	equ 0x20000000
PRINTER_ERROR_OUTOFPAPER equ 0x00000001
PRINTER_ERROR_JAM	equ 0x00000002
PRINTER_ERROR_OUTOFTONER equ 0x00000004

;BOOL
ClosePrinter proto WINAPI \
	      hPrinter: HANDLE

;BOOL
AddFormA proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
		 pForm: LPBYTE
;BOOL
AddFormW proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
		 pForm: LPBYTE
ifdef _UNICODE
AddForm			equ <AddFormW>
else
AddForm			equ <AddFormA>
endif

;BOOL
DeleteFormA proto WINAPI \
	      hPrinter: HANDLE,
	     pFormName: LPSTR
;BOOL
DeleteFormW proto WINAPI \
	      hPrinter: HANDLE,
	     pFormName: LPWSTR
ifdef _UNICODE
DeleteForm		equ <DeleteFormW>
else
DeleteForm		equ <DeleteFormA>
endif

;BOOL
GetFormA proto WINAPI \
	      hPrinter: HANDLE,
	     pFormName: LPSTR,
		 Level: DWORD,
		 pForm: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
;BOOL
GetFormW proto WINAPI \
	      hPrinter: HANDLE,
	     pFormName: LPWSTR,
		 Level: DWORD,
		 pForm: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetForm			equ <GetFormW>
else
GetForm			equ <GetFormA>
endif

;BOOL
SetFormA proto WINAPI \
	      hPrinter: HANDLE,
	     pFormName: LPSTR,
		 Level: DWORD,
		 pForm: LPBYTE
;BOOL
SetFormW proto WINAPI \
	      hPrinter: HANDLE,
	     pFormName: LPWSTR,
		 Level: DWORD,
		 pForm: LPBYTE
ifdef _UNICODE
SetForm			equ <SetFormW>
else
SetForm			equ <SetFormA>
endif

;BOOL
EnumFormsA proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
		 pForm: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumFormsW proto WINAPI \
	      hPrinter: HANDLE,
		 Level: DWORD,
		 pForm: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumForms		equ <EnumFormsW>
else
EnumForms		equ <EnumFormsA>
endif

;BOOL
EnumMonitorsA proto WINAPI \
		 pName: LPSTR,
		 Level: DWORD,
	     pMonitors: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumMonitorsW proto WINAPI \
		 pName: LPWSTR,
		 Level: DWORD,
	     pMonitors: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumMonitors		equ <EnumMonitorsW>
else
EnumMonitors		equ <EnumMonitorsA>
endif

;BOOL
AddMonitorA proto WINAPI \
		 pName: LPSTR,
		 Level: DWORD,
	     pMonitors: LPBYTE
;BOOL
AddMonitorW proto WINAPI \
		 pName: LPWSTR,
		 Level: DWORD,
	     pMonitors: LPBYTE
ifdef _UNICODE
AddMonitor		equ <AddMonitorW>
else
AddMonitor		equ <AddMonitorA>
endif

;BOOL
DeleteMonitorA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
	  pMonitorName: LPSTR
;BOOL
DeleteMonitorW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
	  pMonitorName: LPWSTR
ifdef _UNICODE
DeleteMonitor		equ <DeleteMonitorW>
else
DeleteMonitor		equ <DeleteMonitorA>
endif

;BOOL
EnumPortsA proto WINAPI \
		 pName: LPSTR,
		 Level: DWORD,
		pPorts: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
;BOOL
EnumPortsW proto WINAPI \
		 pName: LPWSTR,
		 Level: DWORD,
		pPorts: LPBYTE,
		 cbBuf: DWORD,
	     pcbNeeded: LPDWORD,
	    pcReturned: LPDWORD
ifdef _UNICODE
EnumPorts		equ <EnumPortsW>
else
EnumPorts		equ <EnumPortsA>
endif

;BOOL
AddPortA proto WINAPI \
		 pName: LPSTR,
		  hWnd: HWND,
	  pMonitorName: LPSTR
;BOOL
AddPortW proto WINAPI \
		 pName: LPWSTR,
		  hWnd: HWND,
	  pMonitorName: LPWSTR
ifdef _UNICODE
AddPort			equ <AddPortW>
else
AddPort			equ <AddPortA>
endif

;BOOL
ConfigurePortA proto WINAPI \
		 pName: LPSTR,
		  hWnd: HWND,
	     pPortName: LPSTR
;BOOL
ConfigurePortW proto WINAPI \
		 pName: LPWSTR,
		  hWnd: HWND,
	     pPortName: LPWSTR
ifdef _UNICODE
ConfigurePort		equ <ConfigurePortW>
else
ConfigurePort		equ <ConfigurePortA>
endif

;BOOL
DeletePortA proto WINAPI \
		 pName: LPSTR,
		  hWnd: HWND,
	     pPortName: LPSTR
;BOOL
DeletePortW proto WINAPI \
		 pName: LPWSTR,
		  hWnd: HWND,
	     pPortName: LPWSTR
ifdef _UNICODE
DeletePort		equ <DeletePortW>
else
DeletePort		equ <DeletePortA>
endif

;BOOL
XcvDataW proto WINAPI \
		  hXcv: HANDLE,
	   pszDataName: PCWSTR,
	    pInputData: PBYTE,
	   cbInputData: DWORD,
	   pOutputData: PBYTE,
	  cbOutputData: DWORD,
       pcbOutputNeeded: PDWORD,
	     pdwStatus: PDWORD
XcvData			equ <XcvDataW>

;BOOL
SetPortA proto WINAPI \
		 pName: LPSTR,
	     pPortName: LPSTR,
	       dwLevel: DWORD,
	     pPortInfo: LPBYTE
;BOOL
SetPortW proto WINAPI \
		 pName: LPWSTR,
	     pPortName: LPWSTR,
	       dwLevel: DWORD,
	     pPortInfo: LPBYTE
ifdef _UNICODE
SetPort			equ <SetPortW>
else
SetPort			equ <SetPortA>
endif

;BOOL
AddPrinterConnectionA proto WINAPI \
		 pName: LPSTR
;BOOL
AddPrinterConnectionW proto WINAPI \
		 pName: LPWSTR
ifdef _UNICODE
AddPrinterConnection	equ <AddPrinterConnectionW>
else
AddPrinterConnection	equ <AddPrinterConnectionA>
endif

;BOOL
DeletePrinterConnectionA proto WINAPI \
		 pName: LPSTR
;BOOL
DeletePrinterConnectionW proto WINAPI \
		 pName: LPWSTR
ifdef _UNICODE
DeletePrinterConnection equ <DeletePrinterConnectionW>
else
DeletePrinterConnection equ <DeletePrinterConnectionA>
endif

;HANDLE
ConnectToPrinterDlg proto WINAPI \
		  hwnd: HWND,
		 Flags: DWORD

PROVIDOR_INFO_1A	STRUC
pName			LPSTR ?
pEnvironment		LPSTR ?
pDLLName		LPSTR ?
PROVIDOR_INFO_1A	ENDS
PPROVIDOR_INFO_1A	typedef ptr PROVIDOR_INFO_1A
LPPROVIDOR_INFO_1A	typedef ptr PROVIDOR_INFO_1A
PROVIDOR_INFO_1W	STRUC
pName			LPWSTR ?
pEnvironment		LPWSTR ?
pDLLName		LPWSTR ?
PROVIDOR_INFO_1W	ENDS
PPROVIDOR_INFO_1W	typedef ptr PROVIDOR_INFO_1W
LPPROVIDOR_INFO_1W	typedef ptr PROVIDOR_INFO_1W
ifdef _UNICODE
PROVIDOR_INFO_1		typedef PROVIDOR_INFO_1W
PPROVIDOR_INFO_1	typedef PPROVIDOR_INFO_1W
LPPROVIDOR_INFO_1	typedef LPPROVIDOR_INFO_1W
else
PROVIDOR_INFO_1		typedef PROVIDOR_INFO_1A
PPROVIDOR_INFO_1	typedef PPROVIDOR_INFO_1A
LPPROVIDOR_INFO_1	typedef LPPROVIDOR_INFO_1A
endif

;BOOL
AddPrintProvidorA proto WINAPI \
		 pName: LPSTR,
		 level: DWORD,
	 pProvidorInfo: LPBYTE
;BOOL
AddPrintProvidorW proto WINAPI \
		 pName: LPWSTR,
		 level: DWORD,
	 pProvidorInfo: LPBYTE
ifdef _UNICODE
AddPrintProvidor	equ <AddPrintProvidorW>
else
AddPrintProvidor	equ <AddPrintProvidorA>
endif

;BOOL
DeletePrintProvidorA proto WINAPI \
		 pName: LPSTR,
	  pEnvironment: LPSTR,
    pPrintProvidorName: LPSTR
;BOOL
DeletePrintProvidorW proto WINAPI \
		 pName: LPWSTR,
	  pEnvironment: LPWSTR,
    pPrintProvidorName: LPWSTR
ifdef _UNICODE
DeletePrintProvidor	equ <DeletePrintProvidorW>
else
DeletePrintProvidor	equ <DeletePrintProvidorA>
endif

SPLREG_DEFAULT_SPOOL_DIRECTORY equ <"DefaultSpoolDirectory">
SPLREG_PORT_THREAD_PRIORITY_DEFAULT equ <"PortThreadPriorityDefault">
SPLREG_PORT_THREAD_PRIORITY equ <"PortThreadPriority">
SPLREG_SCHEDULER_THREAD_PRIORITY_DEFAULT equ <"SchedulerThreadPriorityDefault">
SPLREG_SCHEDULER_THREAD_PRIORITY equ <"SchedulerThreadPriority">
SPLREG_BEEP_ENABLED	equ <"BeepEnabled">
SPLREG_NET_POPUP	equ <"NetPopup">
SPLREG_EVENT_LOG	equ <"EventLog">
SPLREG_MAJOR_VERSION	equ <"MajorVersion">
SPLREG_MINOR_VERSION	equ <"MinorVersion">
SPLREG_ARCHITECTURE	equ <"Architecture">
SPLREG_OS_VERSION	equ <"OSVersion">
SPLREG_DS_PRESENT	equ <"DsPresent">

SERVER_ACCESS_ADMINISTER equ 0x00000001
SERVER_ACCESS_ENUMERATE equ 0x00000002

PRINTER_ACCESS_ADMINISTER equ 0x00000004
PRINTER_ACCESS_USE	equ 0x00000008

JOB_ACCESS_ADMINISTER	equ 0x00000010

SERVER_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED OR SERVER_ACCESS_ADMINISTER OR SERVER_ACCESS_ENUMERATE
SERVER_READ		equ STANDARD_RIGHTS_READ OR SERVER_ACCESS_ENUMERATE
SERVER_WRITE		equ STANDARD_RIGHTS_WRITE OR SERVER_ACCESS_ADMINISTER OR SERVER_ACCESS_ENUMERATE
SERVER_EXECUTE		equ STANDARD_RIGHTS_EXECUTE OR SERVER_ACCESS_ENUMERATE

PRINTER_ALL_ACCESS	equ STANDARD_RIGHTS_REQUIRED OR PRINTER_ACCESS_ADMINISTER OR PRINTER_ACCESS_USE
PRINTER_READ		equ STANDARD_RIGHTS_READ OR PRINTER_ACCESS_USE
PRINTER_WRITE		equ STANDARD_RIGHTS_WRITE OR PRINTER_ACCESS_USE
PRINTER_EXECUTE		equ STANDARD_RIGHTS_EXECUTE OR PRINTER_ACCESS_USE

JOB_ALL_ACCESS		equ STANDARD_RIGHTS_REQUIRED OR JOB_ACCESS_ADMINISTER
JOB_READ		equ STANDARD_RIGHTS_READ OR JOB_ACCESS_ADMINISTER
JOB_WRITE		equ STANDARD_RIGHTS_WRITE OR JOB_ACCESS_ADMINISTER
JOB_EXECUTE		equ STANDARD_RIGHTS_EXECUTE OR JOB_ACCESS_ADMINISTER

SPLDS_SPOOLER_KEY	equ <"DsSpooler">
SPLDS_DRIVER_KEY	equ <"DsDriver">
SPLDS_USER_KEY		equ <"DsUser">

SPLDS_ASSET_NUMBER	equ <"assetNumber">
SPLDS_BYTES_PER_MINUTE	equ <"bytesPerMinute">
SPLDS_DESCRIPTION	equ <"description">
SPLDS_DRIVER_NAME	equ <"driverName">
SPLDS_DRIVER_VERSION	equ <"driverVersion">
SPLDS_LOCATION		equ <"location">
SPLDS_PORT_NAME		equ <"portName">
SPLDS_PRINT_ATTRIBUTES	equ <"printAttributes">
SPLDS_PRINT_BIN_NAMES	equ <"printBinNames">
SPLDS_PRINT_COLLATE	equ <"printCollate">
SPLDS_PRINT_COLOR	equ <"printColor">
SPLDS_PRINT_DUPLEX_SUPPORTED equ <"printDuplexSupported">
SPLDS_PRINT_END_TIME	equ <"printEndTime">
SPLDS_PRINTER_CLASS	equ <"printQueue">
SPLDS_PRINTER_NAME	equ <"printerName">
SPLDS_PRINT_KEEP_PRINTED_JOBS equ <"printKeepPrintedJobs">
SPLDS_PRINT_LANGUAGE	equ <"printLanguage">
SPLDS_PRINT_MAC_ADDRESS equ <"printMACAddress">
SPLDS_PRINT_MAX_X_EXTENT equ <"printMaxXExtent">
SPLDS_PRINT_MAX_Y_EXTENT equ <"printMaxYExtent">
SPLDS_PRINT_MAX_RESOLUTION_SUPPORTED equ <"printMaxResolutionSupported">
SPLDS_PRINT_MEDIA_READY equ <"printMediaReady">
SPLDS_PRINT_MEDIA_SUPPORTED equ <"printMediaSupported">
SPLDS_PRINT_MEMORY	equ <"printMemory">
SPLDS_PRINT_MIN_X_EXTENT equ <"printMinXExtent">
SPLDS_PRINT_MIN_Y_EXTENT equ <"printMinYExtent">
SPLDS_PRINT_NETWORK_ADDRESS equ <"printNetworkAddress">
SPLDS_PRINT_NOTIFY	equ <"printNotify">
SPLDS_PRINT_NUMBER_UP	equ <"printNumberUp">
SPLDS_PRINT_ORIENTATIONS_SUPPORTED equ <"printOrientationsSupported">
SPLDS_PRINT_OWNER	equ <"printOwner">
SPLDS_PRINT_RATE	equ <"printRate">
SPLDS_PRINT_RATE_UNIT	equ <"printRateUnit">
SPLDS_PRINT_SEPARATOR_FILE equ <"printSeparatorFile">
SPLDS_PRINT_SHARE_NAME	equ <"printShareName">
SPLDS_PRINT_SPOOLING	equ <"printSpooling">
SPLDS_PRINT_STAPLING_SUPPORTED equ <"printStaplingSupported">
SPLDS_PRINT_START_TIME	equ <"printStartTime">
SPLDS_PRINT_STATUS	equ <"printStatus">
SPLDS_PRIORITY		equ <"priority">
SPLDS_SERVER_NAME	equ <"serverName">
SPLDS_UNC_NAME		equ <"uNCName">
SPLDS_URL		equ <"url">
SPLDS_VERSION_NUMBER	equ <"versionNumber">

SPLDS_PRINTER_NAME_ALIASES equ <"printerNameAliases">
SPLDS_PRINTER_LOCATIONS equ <"printerLocations">
SPLDS_PRINTER_MODEL	equ <"printerModel">

PRINTER_HTML_VIEW_QUEUE equ 0
PRINTER_HTML_VIEW_PRINTPROPERTIES equ 1
PRINTER_HTML_VIEW_INSTALL equ 2
PRINTER_HTML_VIEW_JOBPROPERTIES equ 3

;DWORD
SetPrinterHTMLViewA proto WINAPI \
	      hPrinter: HANDLE,
		dwView: DWORD,
	      lpszPath: LPCSTR
;DWORD
SetPrinterHTMLViewW proto WINAPI \
	      hPrinter: HANDLE,
		dwView: DWORD,
	      lpszPath: LPCWSTR
ifdef _UNICODE
SetPrinterHTMLView	equ <SetPrinterHTMLViewW>
else
SetPrinterHTMLView	equ <SetPrinterHTMLViewA>
endif

;DWORD
GetPrinterHTMLViewA proto WINAPI \
	      hPrinter: HANDLE,
		dwView: DWORD,
	      lpszPath: LPSTR,
		 nSize: DWORD,
	     pcbNeeded: LPDWORD
;DWORD
GetPrinterHTMLViewW proto WINAPI \
	      hPrinter: HANDLE,
		dwView: DWORD,
	      lpszPath: LPWSTR,
		 nSize: DWORD,
	     pcbNeeded: LPDWORD
ifdef _UNICODE
GetPrinterHTMLView	equ <GetPrinterHTMLViewW>
else
GetPrinterHTMLView	equ <GetPrinterHTMLViewA>
endif

.pragma list(pop)
endif
