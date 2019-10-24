
;; PE definitions
;; see also: coffspec.inc

ifndef PE_H
PE_H equ <>

IMAGE_DOS_HEADER	STRUC
e_magic			dw ?
e_cblp			dw ?
e_cp			dw ?
e_crlc			dw ?
e_cparhdr		dw ?
e_minalloc		dw ?
e_maxalloc		dw ?
e_ss			dw ?
e_sp			dw ?
e_csum			dw ?
e_ip			dw ?
e_cs			dw ?
e_lfarlc		dw ?
e_ovno			dw ?
e_res			dw 4 dup(?)
e_oemid			dw ?
e_oeminfo		dw ?
e_res2			dw 10 dup(?)
e_lfanew		dd ?
IMAGE_DOS_HEADER	ENDS

IMAGE_DATA_DIRECTORY	STRUC
VirtualAddress		dd ?
Size			dd ?
IMAGE_DATA_DIRECTORY	ENDS

IMAGE_DIRECTORY_ENTRY_EXPORT		equ 0
IMAGE_DIRECTORY_ENTRY_IMPORT		equ 1
IMAGE_DIRECTORY_ENTRY_RESOURCE		equ 2
IMAGE_DIRECTORY_ENTRY_EXCEPTION		equ 3
IMAGE_DIRECTORY_ENTRY_SECURITY		equ 4
IMAGE_DIRECTORY_ENTRY_BASERELOC		equ 5
IMAGE_DIRECTORY_ENTRY_DEBUG		equ 6
IMAGE_DIRECTORY_ENTRY_ARCHITECTURE	equ 7
IMAGE_DIRECTORY_ENTRY_GLOBALPTR		equ 8
IMAGE_DIRECTORY_ENTRY_TLS		equ 9
IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG	equ 10
IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT	equ 11
IMAGE_DIRECTORY_ENTRY_IAT		equ 12

IMAGE_NT_OPTIONAL_HDR32_MAGIC		equ 0x10b
IMAGE_NT_OPTIONAL_HDR64_MAGIC		equ 0x20b

IMAGE_SUBSYSTEM_UNKNOWN			equ 0
IMAGE_SUBSYSTEM_NATIVE			equ 1
IMAGE_SUBSYSTEM_WINDOWS_GUI		equ 2
IMAGE_SUBSYSTEM_WINDOWS_CUI		equ 3
IMAGE_SUBSYSTEM_OS2_CUI			equ 5
IMAGE_SUBSYSTEM_POSIX_CUI		equ 7
IMAGE_SUBSYSTEM_NATIVE_WINDOWS		equ 8
IMAGE_SUBSYSTEM_WINDOWS_CE_GUI		equ 9
IMAGE_SUBSYSTEM_EFI_APPLICATION		equ 10
IMAGE_SUBSYSTEM_EFI_BOOT_SERVICE_DRIVER equ 11
IMAGE_SUBSYSTEM_EFI_RUNTIME_DRIVER	equ 12
IMAGE_SUBSYSTEM_EFI_ROM			equ 13
IMAGE_SUBSYSTEM_XBOX			equ 14

IMAGE_OPTIONAL_HEADER32		STRUC
Magic				dw ?
MajorLinkerVersion		db ?
MinorLinkerVersion		db ?
SizeOfCode			dd ?
SizeOfInitializedData		dd ?
SizeOfUninitializedData		dd ?
AddressOfEntryPoint		dd ?
BaseOfCode			dd ?
BaseOfData			dd ?
ImageBase			dd ?
SectionAlignment		dd ?
FileAlignment			dd ?
MajorOperatingSystemVersion	dw ?
MinorOperatingSystemVersion	dw ?
MajorImageVersion		dw ?
MinorImageVersion		dw ?
MajorSubsystemVersion		dw ?
MinorSubsystemVersion		dw ?
Win32VersionValue		dd ?
SizeOfImage			dd ?
SizeOfHeaders			dd ?
CheckSum			dd ?
Subsystem			dw ?
DllCharacteristics		dw ?
SizeOfStackReserve		dd ?
SizeOfStackCommit		dd ?
SizeOfHeapReserve		dd ?
SizeOfHeapCommit		dd ?
LoaderFlags			dd ?
NumberOfRvaAndSizes		dd ?
DataDirectory			IMAGE_DATA_DIRECTORY IMAGE_NUMBEROF_DIRECTORY_ENTRIES dup(<>)
IMAGE_OPTIONAL_HEADER32		ENDS

IMAGE_PE_HEADER32		struct
Signature			dd ?
FileHeader			IMAGE_FILE_HEADER <>
OptionalHeader			IMAGE_OPTIONAL_HEADER32 <>
IMAGE_PE_HEADER32		ends

IMAGE_OPTIONAL_HEADER64		STRUC
Magic				dw ?
MajorLinkerVersion		db ?
MinorLinkerVersion		db ?
SizeOfCode			dd ?
SizeOfInitializedData		dd ?
SizeOfUninitializedData		dd ?
AddressOfEntryPoint		dd ?
BaseOfCode			dd ?
ImageBase			dq ?
SectionAlignment		dd ?
FileAlignment			dd ?
MajorOperatingSystemVersion	dw ?
MinorOperatingSystemVersion	dw ?
MajorImageVersion		dw ?
MinorImageVersion		dw ?
MajorSubsystemVersion		dw ?
MinorSubsystemVersion		dw ?
Win32VersionValue		dd ?
SizeOfImage			dd ?
SizeOfHeaders			dd ?
CheckSum			dd ?
Subsystem			dw ?
DllCharacteristics		dw ?
SizeOfStackReserve		dq ?
SizeOfStackCommit		dq ?
SizeOfHeapReserve		dq ?
SizeOfHeapCommit		dq ?
LoaderFlags			dd ?
NumberOfRvaAndSizes		dd ?
DataDirectory			IMAGE_DATA_DIRECTORY IMAGE_NUMBEROF_DIRECTORY_ENTRIES dup(<>)
IMAGE_OPTIONAL_HEADER64		ENDS


IMAGE_PE_HEADER64		STRUC
Signature			dd ?
FileHeader			IMAGE_FILE_HEADER <>
OptionalHeader			IMAGE_OPTIONAL_HEADER64 <>
IMAGE_PE_HEADER64		ENDS

;; base relocations

IMAGE_BASE_RELOCATION		STRUC
VirtualAddress			dd ?
SizeOfBlock			dd ?
IMAGE_BASE_RELOCATION		ENDS

IMAGE_REL_BASED_ABSOLUTE	equ 0  ;; relocation is skipped
IMAGE_REL_BASED_HIGH		equ 1  ;; high 16-bits of a 32-bit target
IMAGE_REL_BASED_LOW		equ 2  ;; low 16-bits of a 32-bit target
IMAGE_REL_BASED_HIGHLOW		equ 3  ;; 32-bit target
IMAGE_REL_BASED_HIGHADJ		equ 4  ;; 32-bit target; first high 16-bits, then low 16-bits in next slot
IMAGE_REL_BASED_DIR64		equ 10 ;; 64-bit target

;; PE resource directory structure

IMAGE_RESOURCE_DIRECTORY	STRUC
Characteristics			dd ?
TimeDateStamp			dd ?
MajorVersion			dw ?
MinorVersion			dw ?
NumberOfNamedEntries		dw ?
NumberOfIdEntries		dw ?
IMAGE_RESOURCE_DIRECTORY	ENDS

IMAGE_RESOURCE_DIRECTORY_ENTRY	STRUC
UNION
  NameOffset			dd ?
  Name				dd ? ;; ID is an offset to an IMAGE_RESOURCE_DIR_STRING_U struct
  Id				dw ? ;; ID is an integer (usually a resource type )
ENDS
UNION
  OffsetToData			dd ?
  OffsetToDirectory		dd ?
ENDS
IMAGE_RESOURCE_DIRECTORY_ENTRY	ENDS

IMAGE_RESOURCE_DIR_STRING_U	STRUC
Length				dw ?
NameString			dw ?
IMAGE_RESOURCE_DIR_STRING_U	ENDS

IMAGE_RESOURCE_DATA_ENTRY	STRUC
OffsetToData			dd ?
Size				dd ?
CodePage			dd ?
Reserved			dd ?
IMAGE_RESOURCE_DATA_ENTRY	ENDS

endif
