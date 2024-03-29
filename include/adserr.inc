.pragma list(push, 0)

_HRESULT_TYPEDEF_ macro _sc
	exitm<_sc>
	endm

FACILITY_WINDOWS	equ 8
FACILITY_STORAGE	equ 3
FACILITY_RPC		equ 1
FACILITY_SSPI		equ 9
FACILITY_WIN32		equ 7
FACILITY_CONTROL	equ 10
FACILITY_NULL		equ 0
FACILITY_ITF		equ 4
FACILITY_DISPATCH	equ 2

E_ADS_BAD_PATHNAME	equ 0x80005000
E_ADS_INVALID_DOMAIN_OBJECT equ 0x80005001
E_ADS_INVALID_USER_OBJECT equ 0x80005002
E_ADS_INVALID_COMPUTER_OBJECT equ 0x80005003
E_ADS_UNKNOWN_OBJECT	equ 0x80005004
E_ADS_PROPERTY_NOT_SET	equ 0x80005005
E_ADS_PROPERTY_NOT_SUPPORTED equ 0x80005006
E_ADS_PROPERTY_INVALID	equ 0x80005007
E_ADS_BAD_PARAMETER	equ 0x80005008
E_ADS_OBJECT_UNBOUND	equ 0x80005009
E_ADS_PROPERTY_NOT_MODIFIED equ 0x8000500A
E_ADS_PROPERTY_MODIFIED equ 0x8000500B
E_ADS_CANT_CONVERT_DATATYPE equ 0x8000500C
E_ADS_PROPERTY_NOT_FOUND equ 0x8000500D
E_ADS_OBJECT_EXISTS	equ 0x8000500E
E_ADS_SCHEMA_VIOLATION	equ 0x8000500F
E_ADS_COLUMN_NOT_SET	equ 0x80005010
S_ADS_ERRORSOCCURRED	equ 0x00005011
S_ADS_NOMORE_ROWS	equ 0x00005012
S_ADS_NOMORE_COLUMNS	equ 0x00005013
E_ADS_INVALID_FILTER	equ 0x80005014

.pragma list(pop)
