
;; the MS COFF declarations, as far as it's relevant for JWasm.
;; The full declarations can be found in MS PSDK, WinNT.h.

;; Machine values
IMAGE_FILE_MACHINE_I386  equ 0x014c ;; Intel 386 or later processors
IMAGE_FILE_MACHINE_AMD64 equ 0x8664 ;; AMD64 (K8)

;; Characteristics flags
IMAGE_FILE_RELOCS_STRIPPED           equ 0x0001  ;; no relocations
IMAGE_FILE_EXECUTABLE_IMAGE          equ 0x0002  ;; is executable
IMAGE_FILE_LINE_NUMS_STRIPPED        equ 0x0004  ;; no line number info
IMAGE_FILE_LOCAL_SYMS_STRIPPED       equ 0x0008  ;; no local symbols
IMAGE_FILE_LARGE_ADDRESS_AWARE       equ 0x0020  ;; App can handle >2gb addresses
IMAGE_FILE_32BIT_MACHINE             equ 0x0100  ;; 32 bit word machine.

IMAGE_FILE_HEADER       struct
Machine                 dw ?
NumberOfSections        dw ?
TimeDateStamp           dd ?
PointerToSymbolTable    dd ?
NumberOfSymbols         dd ?
SizeOfOptionalHeader    dw ?
Characteristics         dw ?
IMAGE_FILE_HEADER       ends

IMAGE_SIZEOF_SHORT_NAME equ 8

IMAGE_SECTION_HEADER    struct
Name                    char_t IMAGE_SIZEOF_SHORT_NAME dup(?)
union Misc
 PhysicalAddress        dd ?
 VirtualSize            dd ?
ends
VirtualAddress          dd ?
SizeOfRawData           dd ?
PointerToRawData        dd ?
PointerToRelocations    dd ?
PointerToLinenumbers    dd ?
NumberOfRelocations     dw ?
NumberOfLinenumbers     dw ?
Characteristics         dd ?
IMAGE_SECTION_HEADER    ends

IMAGE_NUMBEROF_DIRECTORY_ENTRIES equ 16

IMAGE_SCN_TYPE_REG      equ 0
IMAGE_SCN_TYPE_DSECT    equ 1
IMAGE_SCN_TYPE_NOLOAD   equ 2
IMAGE_SCN_TYPE_GROUP    equ 4
IMAGE_SCN_TYPE_NO_PAD   equ 8
IMAGE_SCN_TYPE_COPY     equ 16
IMAGE_SCN_CNT_CODE      equ 0x00000020
IMAGE_SCN_CNT_INITIALIZED_DATA   equ 0x00000040
IMAGE_SCN_CNT_UNINITIALIZED_DATA equ 0x00000080
IMAGE_SCN_LNK_OTHER       equ 0x00000100
IMAGE_SCN_LNK_INFO        equ 0x00000200
IMAGE_SCN_TYPE_OVER       equ 0x00000400
IMAGE_SCN_LNK_REMOVE      equ 0x00000800
IMAGE_SCN_LNK_COMDAT      equ 0x00001000
IMAGE_SCN_GPREL           equ 0x00008000 ;; Valid only for IA64
IMAGE_SCN_MEM_FARDATA     equ 0x00008000 ;; Not in PECOFF v8 spec
IMAGE_SCN_MEM_PURGEABLE   equ 0x00020000
IMAGE_SCN_MEM_16BIT       equ 0x00020000
IMAGE_SCN_MEM_LOCKED      equ 0x00040000
IMAGE_SCN_MEM_PRELOAD     equ 0x00080000
IMAGE_SCN_ALIGN_1BYTES    equ 0x00100000
IMAGE_SCN_ALIGN_2BYTES    equ 0x00200000
IMAGE_SCN_ALIGN_4BYTES    equ 0x00300000
IMAGE_SCN_ALIGN_8BYTES    equ 0x00400000
IMAGE_SCN_ALIGN_16BYTES   equ 0x00500000
IMAGE_SCN_ALIGN_32BYTES   equ 0x00600000
IMAGE_SCN_ALIGN_64BYTES   equ 0x00700000
IMAGE_SCN_ALIGN_128BYTES  equ 0x00800000
IMAGE_SCN_ALIGN_256BYTES  equ 0x00900000
IMAGE_SCN_ALIGN_512BYTES  equ 0x00a00000
IMAGE_SCN_ALIGN_1024BYTES equ 0x00b00000
IMAGE_SCN_ALIGN_2048BYTES equ 0x00c00000
IMAGE_SCN_ALIGN_4096BYTES equ 0x00d00000
IMAGE_SCN_ALIGN_8192BYTES equ 0x00e00000
IMAGE_SCN_LNK_NRELOC_OVFL equ 0x01000000
IMAGE_SCN_MEM_DISCARDABLE equ 0x02000000
IMAGE_SCN_MEM_NOT_CACHED  equ 0x04000000
IMAGE_SCN_MEM_NOT_PAGED   equ 0x08000000
IMAGE_SCN_MEM_SHARED      equ 0x10000000
IMAGE_SCN_MEM_EXECUTE     equ 0x20000000
IMAGE_SCN_MEM_READ        equ 0x40000000
IMAGE_SCN_MEM_WRITE       equ 0x80000000

.pragma pack(push,2)
IMAGE_RELOCATION    struct
union
 VirtualAddress     dd ?
 RelocCount         dd ?
ends
SymbolTableIndex    dd ?
Type                dw ?
IMAGE_RELOCATION    ends
.pragma pack(pop)

IMAGE_REL_I386_ABSOLUTE equ 0x0000 ;; relocation is ignored
IMAGE_REL_I386_DIR16    equ 0x0001 ;; 16bit VA
IMAGE_REL_I386_REL16    equ 0x0002 ;; 16bit PC-relative offset
IMAGE_REL_I386_DIR32    equ 0x0006 ;; 32bit VA
IMAGE_REL_I386_DIR32NB  equ 0x0007 ;; 32bit RVA (IMAGEREL)
IMAGE_REL_I386_SEG12    equ 0x0009 ;; ???
IMAGE_REL_I386_SECTION  equ 0x000A ;; 16bit section index
IMAGE_REL_I386_SECREL   equ 0x000B ;; 32bit offset (SECTIONREL)
IMAGE_REL_I386_TOKEN    equ 0x000C ;; CLR token
IMAGE_REL_I386_SECREL7  equ 0x000D ;; 7bit offset
IMAGE_REL_I386_REL32    equ 0x0014 ;; 32bit PC-relative offset

;; X86-64 relocations

IMAGE_REL_AMD64_ABSOLUTE        equ 0x0000  ;; Reference is absolute, no relocation is necessary
IMAGE_REL_AMD64_ADDR64          equ 0x0001  ;; 64-bit address (VA).
IMAGE_REL_AMD64_ADDR32          equ 0x0002  ;; 32-bit address (VA).
IMAGE_REL_AMD64_ADDR32NB        equ 0x0003  ;; 32-bit address w/o image base (RVA).
IMAGE_REL_AMD64_REL32           equ 0x0004  ;; 32-bit relative address from byte following reloc
IMAGE_REL_AMD64_REL32_1         equ 0x0005  ;; 32-bit relative address from byte distance 1 from reloc
IMAGE_REL_AMD64_REL32_2         equ 0x0006  ;; 32-bit relative address from byte distance 2 from reloc
IMAGE_REL_AMD64_REL32_3         equ 0x0007  ;; 32-bit relative address from byte distance 3 from reloc
IMAGE_REL_AMD64_REL32_4         equ 0x0008  ;; 32-bit relative address from byte distance 4 from reloc
IMAGE_REL_AMD64_REL32_5         equ 0x0009  ;; 32-bit relative address from byte distance 5 from reloc
IMAGE_REL_AMD64_SECTION         equ 0x000A  ;; Section index
IMAGE_REL_AMD64_SECREL          equ 0x000B  ;; 32 bit offset from base of section containing target
IMAGE_REL_AMD64_SECREL7         equ 0x000C  ;; 7 bit unsigned offset from base of section containing target
IMAGE_REL_AMD64_TOKEN           equ 0x000D  ;; 32 bit metadata token

IMAGE_SIZEOF_SYMBOL     equ 18
IMAGE_SIZEOF_AUX_SYMBOL equ 18

.pragma pack(push,2)

IMAGE_SYMBOL        struct
union N
 ;; v2.08
 ShortName          db 8 dup(?)
 struct Name
  _Short            dd ?
  Long              dd ?
 ends
 ;; v2.07: don't use pointers in COFF structures!
 LongName           dd 2 dup(?)
ends
Value               dd ?
SectionNumber       dw ?
Type                dw ?
StorageClass        db ?
NumberOfAuxSymbols  db ?
IMAGE_SYMBOL        ends

;; special section numbers

IMAGE_SYM_UNDEFINED     equ 0
IMAGE_SYM_ABSOLUTE      equ (-1)
IMAGE_SYM_DEBUG         equ (-2)

IMAGE_SYM_TYPE_NULL     equ 0
IMAGE_SYM_TYPE_VOID     equ 1
IMAGE_SYM_TYPE_CHAR     equ 2
IMAGE_SYM_TYPE_SHORT    equ 3
IMAGE_SYM_TYPE_INT      equ 4
IMAGE_SYM_TYPE_LONG     equ 5
IMAGE_SYM_TYPE_FLOAT    equ 6
IMAGE_SYM_TYPE_DOUBLE   equ 7
IMAGE_SYM_TYPE_STRUCT   equ 8
IMAGE_SYM_TYPE_UNION    equ 9
IMAGE_SYM_TYPE_ENUM     equ 10
IMAGE_SYM_TYPE_MOE      equ 11
IMAGE_SYM_TYPE_BYTE     equ 12
IMAGE_SYM_TYPE_WORD     equ 13
IMAGE_SYM_TYPE_UINT     equ 14
IMAGE_SYM_TYPE_DWORD    equ 15
IMAGE_SYM_TYPE_PCODE    equ 32768

IMAGE_SYM_DTYPE_NULL    equ 0
IMAGE_SYM_DTYPE_POINTER equ 1
IMAGE_SYM_DTYPE_FUNCTION equ 2
IMAGE_SYM_DTYPE_ARRAY   equ 3

;; StorageClass values

IMAGE_SYM_CLASS_END_OF_FUNCTION     equ (-1)
IMAGE_SYM_CLASS_NULL                equ 0
IMAGE_SYM_CLASS_AUTOMATIC           equ 1
IMAGE_SYM_CLASS_EXTERNAL            equ 2
IMAGE_SYM_CLASS_STATIC              equ 3
IMAGE_SYM_CLASS_REGISTER            equ 4
IMAGE_SYM_CLASS_EXTERNAL_DEF        equ 5
IMAGE_SYM_CLASS_LABEL               equ 6
IMAGE_SYM_CLASS_UNDEFINED_LABEL     equ 7
IMAGE_SYM_CLASS_MEMBER_OF_STRUCT    equ 8
IMAGE_SYM_CLASS_ARGUMENT            equ 9
IMAGE_SYM_CLASS_STRUCT_TAG          equ 10
IMAGE_SYM_CLASS_MEMBER_OF_UNION     equ 11
IMAGE_SYM_CLASS_UNION_TAG           equ 12
IMAGE_SYM_CLASS_TYPE_DEFINITION     equ 13
IMAGE_SYM_CLASS_UNDEFINED_STATIC    equ 14
IMAGE_SYM_CLASS_ENUM_TAG            equ 15
IMAGE_SYM_CLASS_MEMBER_OF_ENUM      equ 16
IMAGE_SYM_CLASS_REGISTER_PARAM      equ 17
IMAGE_SYM_CLASS_BIT_FIELD           equ 18
IMAGE_SYM_CLASS_FAR_EXTERNAL        equ 68 ;; Not in PECOFF v8 spec
IMAGE_SYM_CLASS_BLOCK               equ 100
IMAGE_SYM_CLASS_FUNCTION            equ 101
IMAGE_SYM_CLASS_END_OF_STRUCT       equ 102
IMAGE_SYM_CLASS_FILE                equ 103
IMAGE_SYM_CLASS_SECTION             equ 104
IMAGE_SYM_CLASS_WEAK_EXTERNAL       equ 105
IMAGE_SYM_CLASS_CLR_TOKEN           equ 107

;; values for IMAGE_AUX_SYMBOL.Section.Selection
IMAGE_COMDAT_SELECT_NODUPLICATES    equ 1
IMAGE_COMDAT_SELECT_ANY             equ 2
IMAGE_COMDAT_SELECT_SAME_SIZE       equ 3
IMAGE_COMDAT_SELECT_EXACT_MATCH     equ 4
IMAGE_COMDAT_SELECT_ASSOCIATIVE     equ 5
IMAGE_COMDAT_SELECT_LARGEST         equ 6
IMAGE_COMDAT_SELECT_NEWEST          equ 7

;; values for IMAGE_AUX_SYMBOL.Sym.Characteristics(=TotalSize)
IMAGE_WEAK_EXTERN_SEARCH_NOLIBRARY  equ 1
IMAGE_WEAK_EXTERN_SEARCH_LIBRARY    equ 2
IMAGE_WEAK_EXTERN_SEARCH_ALIAS      equ 3

IMAGE_AUX_SYMBOL    union
struct Sym          ;; AUX format 2: .bf and .ef entries
 TagIndex           dd ?
 union Misc
  struct LnSz
   Linenumber       dw ?
   Size             dw ?
  ends
  TotalSize         dd ?
 ends
 union FcnAry
  struct Function
   PointerToLinenumber dd ?
   PointerToNextFunction dd ?
  ends
  struct Array
   Dimension        dw 4 dup(?)
  ends
 ends
 TvIndex            dw ?
ends
struct File         ;; AUX format 4: file entries
 ;; v2.08
 Name               db IMAGE_SIZEOF_SYMBOL dup(?)
ends
struct Section      ;; AUX format 5: section entries
 Length             dd ?
 NumberOfRelocations dw ?
 NumberOfLinenumbers dw ?
 CheckSum           dd ?
 Number             dw ?
 Selection          db ?
ends
IMAGE_AUX_SYMBOL    ends
.pragma pack(pop)

IMAGE_COFF_SYMBOLS_HEADER   struct
NumberOfSymbols             dd ?
LvaToFirstSymbol            dd ?
NumberOfLinenumbers         dd ?
LvaToFirstLinenumber        dd ?
RvaToFirstByteOfCode        dd ?
RvaToLastByteOfCode         dd ?
RvaToFirstByteOfData        dd ?
RvaToLastByteOfData         dd ?
IMAGE_COFF_SYMBOLS_HEADER   ends

.pragma pack(push,2)
IMAGE_LINENUMBER    struct
union Type
 SymbolTableIndex   dd ?
 VirtualAddress     dd ?
ends
Linenumber          dw ?
IMAGE_LINENUMBER    ends
.pragma pack(pop)
