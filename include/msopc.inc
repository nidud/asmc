ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __msopc_h__
define __msopc_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include wincrypt.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if (NTDDI_VERSION GE NTDDI_WIN7)

if (NTDDI_VERSION GE NTDDI_WIN7)

ifndef __IOpcUri_INTERFACE_DEFINED__
define __IOpcUri_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcUri, "bc9c1b9b-d62c-49eb-aef0-3b4e0b28ebed")

.comdef IOpcUri : public IUri

    GetRelationshipsPartUri proc :ptr
    GetRelativeUri	proc :ptr, :ptr
    CombinePartUri	proc :ptr, :ptr
   .ends

endif


ifndef __IOpcPartUri_INTERFACE_DEFINED__
define __IOpcPartUri_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcPartUri, "7d3babe7-88b2-46ba-85cb-4203cb016c87")

.comdef IOpcPartUri : public IOpcUri

    ;CombinePartUri	 proc :ptr, :ptr
    ComparePartUri	proc :ptr, :ptr
    GetSourceUri	proc :ptr
    IsRelationshipsPartUri proc :ptr
   .ends

endif

endif ;; (NTDDI GE NTDDI_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __MSOPC_LIBRARY_DEFINED__
define __MSOPC_LIBRARY_DEFINED__

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if (NTDDI_VERSION GE NTDDI_WIN7)

.enum OPC_URI_TARGET_MODE {
    OPC_URI_TARGET_MODE_INTERNAL	= 0,
    OPC_URI_TARGET_MODE_EXTERNAL	= 1
    }

.enum OPC_COMPRESSION_OPTIONS {
    OPC_COMPRESSION_NONE	= -1,
    OPC_COMPRESSION_NORMAL	= 0,
    OPC_COMPRESSION_MAXIMUM	= 1,
    OPC_COMPRESSION_FAST	= 2,
    OPC_COMPRESSION_SUPERFAST	= 3
    }

.enum OPC_STREAM_IO_MODE {
    OPC_STREAM_IO_READ	= 1,
    OPC_STREAM_IO_WRITE = 2
    }

IS_OPC_CONFORMANCE_ERROR macro x
    if (((x) AND 0x1FFFF000) EQ (0x0000+(FACILITY_OPC SHL 16)))
	exitm<1>
    else
	exitm<0>
    endif
    endm
IS_ZIP_CONFORMANCE_ERROR macro x
    if (((x) AND 0x1FFFF000) EQ (0x1000+(FACILITY_OPC SHL 16)))
	exitm<1>
    else
	exitm<0>
    endif
    endm

OPC_E_NONCONFORMING_URI equ MAKE_HRESULT(1, FACILITY_OPC, 0x1)
OPC_E_RELATIVE_URI_REQUIRED equ MAKE_HRESULT(1, FACILITY_OPC, 0x2)
OPC_E_RELATIONSHIP_URI_REQUIRED equ MAKE_HRESULT(1, FACILITY_OPC, 0x3)
OPC_E_PART_CANNOT_BE_DIRECTORY equ MAKE_HRESULT(1, FACILITY_OPC, 0x4)
OPC_E_UNEXPECTED_CONTENT_TYPE equ MAKE_HRESULT(1, FACILITY_OPC, 0x5)
OPC_E_INVALID_CONTENT_TYPE_XML equ MAKE_HRESULT(1, FACILITY_OPC, 0x6)
OPC_E_MISSING_CONTENT_TYPES equ MAKE_HRESULT(1, FACILITY_OPC, 0x7)
OPC_E_NONCONFORMING_CONTENT_TYPES_XML equ MAKE_HRESULT(1, FACILITY_OPC, 0x8)
OPC_E_NONCONFORMING_RELS_XML equ MAKE_HRESULT(1, FACILITY_OPC, 0x9)
OPC_E_INVALID_RELS_XML	equ MAKE_HRESULT(1, FACILITY_OPC, 0xA)
OPC_E_DUPLICATE_PART	equ MAKE_HRESULT(1, FACILITY_OPC, 0xB)
OPC_E_INVALID_OVERRIDE_PART_NAME equ MAKE_HRESULT(1, FACILITY_OPC, 0xC)
OPC_E_DUPLICATE_OVERRIDE_PART equ MAKE_HRESULT(1, FACILITY_OPC, 0xD)
OPC_E_INVALID_DEFAULT_EXTENSION equ MAKE_HRESULT(1, FACILITY_OPC, 0xE)
OPC_E_DUPLICATE_DEFAULT_EXTENSION equ MAKE_HRESULT(1, FACILITY_OPC, 0xF)
OPC_E_INVALID_RELATIONSHIP_ID equ MAKE_HRESULT(1, FACILITY_OPC, 0x10)
OPC_E_INVALID_RELATIONSHIP_TYPE equ MAKE_HRESULT(1, FACILITY_OPC, 0x11)
OPC_E_INVALID_RELATIONSHIP_TARGET equ MAKE_HRESULT(1, FACILITY_OPC, 0x12)
OPC_E_DUPLICATE_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_OPC, 0x13)
OPC_E_CONFLICTING_SETTINGS equ MAKE_HRESULT(1, FACILITY_OPC, 0x14)
OPC_E_DUPLICATE_PIECE	equ MAKE_HRESULT(1, FACILITY_OPC, 0x15)
OPC_E_INVALID_PIECE	equ MAKE_HRESULT(1, FACILITY_OPC, 0x16)
OPC_E_MISSING_PIECE	equ MAKE_HRESULT(1, FACILITY_OPC, 0x17)
OPC_E_NO_SUCH_PART	equ MAKE_HRESULT(1, FACILITY_OPC, 0x18)
OPC_E_DS_SIGNATURE_CORRUPT equ MAKE_HRESULT(1, FACILITY_OPC, 0x19)
OPC_E_DS_DIGEST_VALUE_ERROR equ MAKE_HRESULT(1, FACILITY_OPC, 0x1A)
OPC_E_DS_DUPLICATE_SIGNATURE_ORIGIN_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_OPC, 0x1B)
OPC_E_DS_INVALID_SIGNATURE_ORIGIN_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_OPC, 0x1C)
OPC_E_DS_INVALID_CERTIFICATE_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_OPC, 0x1D)
OPC_E_DS_EXTERNAL_SIGNATURE equ MAKE_HRESULT(1, FACILITY_OPC, 0x1E)
OPC_E_DS_MISSING_SIGNATURE_ORIGIN_PART equ MAKE_HRESULT(1, FACILITY_OPC, 0x1F)
OPC_E_DS_MISSING_SIGNATURE_PART equ MAKE_HRESULT(1, FACILITY_OPC, 0x20)
OPC_E_DS_INVALID_RELATIONSHIP_TRANSFORM_XML equ MAKE_HRESULT(1, FACILITY_OPC, 0x21)
OPC_E_DS_INVALID_CANONICALIZATION_METHOD equ MAKE_HRESULT(1, FACILITY_OPC, 0x22)
OPC_E_DS_INVALID_RELATIONSHIPS_SIGNING_OPTION equ MAKE_HRESULT(1, FACILITY_OPC, 0x23)
OPC_E_DS_INVALID_OPC_SIGNATURE_TIME_FORMAT equ MAKE_HRESULT(1, FACILITY_OPC, 0x24)
OPC_E_DS_PACKAGE_REFERENCE_URI_RESERVED equ MAKE_HRESULT(1, FACILITY_OPC, 0x25)
OPC_E_DS_MISSING_SIGNATURE_PROPERTIES_ELEMENT equ MAKE_HRESULT(1, FACILITY_OPC, 0x26)
OPC_E_DS_MISSING_SIGNATURE_PROPERTY_ELEMENT equ MAKE_HRESULT(1, FACILITY_OPC, 0x27)
OPC_E_DS_DUPLICATE_SIGNATURE_PROPERTY_ELEMENT equ MAKE_HRESULT(1, FACILITY_OPC, 0x28)
OPC_E_DS_MISSING_SIGNATURE_TIME_PROPERTY equ MAKE_HRESULT(1, FACILITY_OPC, 0x29)
OPC_E_DS_INVALID_SIGNATURE_XML equ MAKE_HRESULT(1, FACILITY_OPC, 0x2A)
OPC_E_DS_INVALID_SIGNATURE_COUNT equ MAKE_HRESULT(1, FACILITY_OPC, 0x2B)
OPC_E_DS_MISSING_SIGNATURE_ALGORITHM equ MAKE_HRESULT(1, FACILITY_OPC, 0x2C)
OPC_E_DS_DUPLICATE_PACKAGE_OBJECT_REFERENCES equ MAKE_HRESULT(1, FACILITY_OPC, 0x2D)
OPC_E_DS_MISSING_PACKAGE_OBJECT_REFERENCE equ MAKE_HRESULT(1, FACILITY_OPC, 0x2E)
OPC_E_DS_EXTERNAL_SIGNATURE_REFERENCE equ MAKE_HRESULT(1, FACILITY_OPC, 0x2F)
OPC_E_DS_REFERENCE_MISSING_CONTENT_TYPE equ MAKE_HRESULT(1, FACILITY_OPC, 0x30)
OPC_E_DS_MULTIPLE_RELATIONSHIP_TRANSFORMS equ MAKE_HRESULT(1, FACILITY_OPC, 0x31)
OPC_E_DS_MISSING_CANONICALIZATION_TRANSFORM equ MAKE_HRESULT(1, FACILITY_OPC, 0x32)
OPC_E_MC_UNEXPECTED_ELEMENT equ MAKE_HRESULT(1, FACILITY_OPC, 0x33)
OPC_E_MC_UNEXPECTED_REQUIRES_ATTR equ MAKE_HRESULT(1, FACILITY_OPC, 0x34)
OPC_E_MC_MISSING_REQUIRES_ATTR equ MAKE_HRESULT(1, FACILITY_OPC, 0x35)
OPC_E_MC_UNEXPECTED_ATTR equ MAKE_HRESULT(1, FACILITY_OPC, 0x36)
OPC_E_MC_INVALID_PREFIX_LIST equ MAKE_HRESULT(1, FACILITY_OPC, 0x37)
OPC_E_MC_INVALID_QNAME_LIST equ MAKE_HRESULT(1, FACILITY_OPC, 0x38)
OPC_E_MC_NESTED_ALTERNATE_CONTENT equ MAKE_HRESULT(1, FACILITY_OPC, 0x39)
OPC_E_MC_UNEXPECTED_CHOICE equ MAKE_HRESULT(1, FACILITY_OPC, 0x3A)
OPC_E_MC_MISSING_CHOICE equ MAKE_HRESULT(1, FACILITY_OPC, 0x3B)
OPC_E_MC_INVALID_ENUM_TYPE equ MAKE_HRESULT(1, FACILITY_OPC, 0x3C)
OPC_E_MC_UNKNOWN_NAMESPACE equ MAKE_HRESULT(1, FACILITY_OPC, 0x3E)
OPC_E_MC_UNKNOWN_PREFIX equ MAKE_HRESULT(1, FACILITY_OPC, 0x3F)
OPC_E_MC_INVALID_ATTRIBUTES_ON_IGNORABLE_ELEMENT equ MAKE_HRESULT(1, FACILITY_OPC, 0x40)
OPC_E_MC_INVALID_XMLNS_ATTRIBUTE equ MAKE_HRESULT(1, FACILITY_OPC, 0x41)
OPC_E_INVALID_XML_ENCODING equ MAKE_HRESULT(1, FACILITY_OPC, 0x42)
OPC_E_DS_SIGNATURE_REFERENCE_MISSING_URI equ MAKE_HRESULT(1, FACILITY_OPC, 0x43)
OPC_E_INVALID_CONTENT_TYPE equ MAKE_HRESULT(1, FACILITY_OPC, 0x44)
OPC_E_DS_SIGNATURE_PROPERTY_MISSING_TARGET equ MAKE_HRESULT(1, FACILITY_OPC, 0x45)
OPC_E_DS_SIGNATURE_METHOD_NOT_SET equ MAKE_HRESULT(1, FACILITY_OPC, 0x46)
OPC_E_DS_DEFAULT_DIGEST_METHOD_NOT_SET equ MAKE_HRESULT(1, FACILITY_OPC, 0x47)
OPC_E_NO_SUCH_RELATIONSHIP equ MAKE_HRESULT(1, FACILITY_OPC, 0x48)
OPC_E_MC_MULTIPLE_FALLBACK_ELEMENTS equ MAKE_HRESULT(1, FACILITY_OPC, 0x49)
OPC_E_MC_INCONSISTENT_PROCESS_CONTENT equ MAKE_HRESULT(1, FACILITY_OPC, 0x4A)
OPC_E_MC_INCONSISTENT_PRESERVE_ATTRIBUTES equ MAKE_HRESULT(1, FACILITY_OPC, 0x4B)
OPC_E_MC_INCONSISTENT_PRESERVE_ELEMENTS equ MAKE_HRESULT(1, FACILITY_OPC, 0x4C)
OPC_E_INVALID_RELATIONSHIP_TARGET_MODE equ MAKE_HRESULT(1, FACILITY_OPC, 0x4D)
OPC_E_COULD_NOT_RECOVER equ MAKE_HRESULT(1, FACILITY_OPC, 0x4E)
OPC_E_UNSUPPORTED_PACKAGE equ MAKE_HRESULT(1, FACILITY_OPC, 0x4F)
OPC_E_ENUM_COLLECTION_CHANGED equ MAKE_HRESULT(1, FACILITY_OPC, 0x50)
OPC_E_ENUM_CANNOT_MOVE_NEXT equ MAKE_HRESULT(1, FACILITY_OPC, 0x51)
OPC_E_ENUM_CANNOT_MOVE_PREVIOUS equ MAKE_HRESULT(1, FACILITY_OPC, 0x52)
OPC_E_ENUM_INVALID_POSITION equ MAKE_HRESULT(1, FACILITY_OPC, 0x53)
OPC_E_DS_SIGNATURE_ORIGIN_EXISTS equ MAKE_HRESULT(1, FACILITY_OPC, 0x54)
OPC_E_DS_UNSIGNED_PACKAGE equ MAKE_HRESULT(1, FACILITY_OPC, 0x55)
OPC_E_DS_MISSING_CERTIFICATE_PART equ MAKE_HRESULT(1, FACILITY_OPC, 0x56)
OPC_E_NO_SUCH_SETTINGS	equ MAKE_HRESULT(1, FACILITY_OPC, 0x57)
OPC_E_ZIP_INCORRECT_DATA_SIZE equ MAKE_HRESULT(1, FACILITY_OPC, 0x1001)
OPC_E_ZIP_CORRUPTED_ARCHIVE equ MAKE_HRESULT(1, FACILITY_OPC, 0x1002)
OPC_E_ZIP_COMPRESSION_FAILED equ MAKE_HRESULT(1, FACILITY_OPC, 0x1003)
OPC_E_ZIP_DECOMPRESSION_FAILED equ MAKE_HRESULT(1, FACILITY_OPC, 0x1004)
OPC_E_ZIP_INCONSISTENT_FILEITEM equ MAKE_HRESULT(1, FACILITY_OPC, 0x1005)
OPC_E_ZIP_INCONSISTENT_DIRECTORY equ MAKE_HRESULT(1, FACILITY_OPC, 0x1006)
OPC_E_ZIP_MISSING_DATA_DESCRIPTOR equ MAKE_HRESULT(1, FACILITY_OPC, 0x1007)
OPC_E_ZIP_UNSUPPORTEDARCHIVE equ MAKE_HRESULT(1, FACILITY_OPC, 0x1008)
OPC_E_ZIP_CENTRAL_DIRECTORY_TOO_LARGE equ MAKE_HRESULT(1, FACILITY_OPC, 0x1009)
OPC_E_ZIP_NAME_TOO_LARGE equ MAKE_HRESULT(1, FACILITY_OPC, 0x100A)
OPC_E_ZIP_DUPLICATE_NAME equ MAKE_HRESULT(1, FACILITY_OPC, 0x100B)
OPC_E_ZIP_COMMENT_TOO_LARGE equ MAKE_HRESULT(1, FACILITY_OPC, 0x100C)
OPC_E_ZIP_EXTRA_FIELDS_TOO_LARGE equ MAKE_HRESULT(1, FACILITY_OPC, 0x100D)
OPC_E_ZIP_FILE_HEADER_TOO_LARGE equ MAKE_HRESULT(1, FACILITY_OPC, 0x100E)
OPC_E_ZIP_MISSING_END_OF_CENTRAL_DIRECTORY equ MAKE_HRESULT(1, FACILITY_OPC, 0x100F)
OPC_E_ZIP_REQUIRES_64_BIT equ MAKE_HRESULT(1, FACILITY_OPC, 0x1010)

endif ;; (NTDDI GE NTDDI_WIN7)
endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if (NTDDI_VERSION GE NTDDI_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum OPC_READ_FLAGS {
    OPC_READ_DEFAULT	= 0,
    OPC_VALIDATE_ON_LOAD = 0x1,
    OPC_CACHE_ON_ACCESS = 0x2
    }

.enum OPC_WRITE_FLAGS {
    OPC_WRITE_DEFAULT	= 0,
    OPC_WRITE_FORCE_ZIP32 = 0x1
    }

endif

endif ;; (NTDDI GE NTDDI_WIN7)

if (NTDDI_VERSION GE NTDDI_WIN7)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum OPC_SIGNATURE_VALIDATION_RESULT {
    OPC_SIGNATURE_VALID = 0,
    OPC_SIGNATURE_INVALID	= -1
    }

.enum OPC_CANONICALIZATION_METHOD {
    OPC_CANONICALIZATION_NONE	= 0,
    OPC_CANONICALIZATION_C14N	= 1,
    OPC_CANONICALIZATION_C14N_WITH_COMMENTS	= 2
    }

.enum OPC_RELATIONSHIP_SELECTOR {
    OPC_RELATIONSHIP_SELECT_BY_ID	= 0,
    OPC_RELATIONSHIP_SELECT_BY_TYPE	= 1
    }

.enum OPC_RELATIONSHIPS_SIGNING_OPTION {
    OPC_RELATIONSHIP_SIGN_USING_SELECTORS	= 0,
    OPC_RELATIONSHIP_SIGN_PART	= 1
    }

.enum OPC_CERTIFICATE_EMBEDDING_OPTION {
    OPC_CERTIFICATE_IN_CERTIFICATE_PART = 0,
    OPC_CERTIFICATE_IN_SIGNATURE_PART	= 1,
    OPC_CERTIFICATE_NOT_EMBEDDED	= 2
    }

.enum OPC_SIGNATURE_TIME_FORMAT {
    OPC_SIGNATURE_TIME_FORMAT_MILLISECONDS	= 0,
    OPC_SIGNATURE_TIME_FORMAT_SECONDS	= 1,
    OPC_SIGNATURE_TIME_FORMAT_MINUTES	= 2,
    OPC_SIGNATURE_TIME_FORMAT_DAYS	= 3,
    OPC_SIGNATURE_TIME_FORMAT_MONTHS	= 4,
    OPC_SIGNATURE_TIME_FORMAT_YEARS	= 5
    }

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
endif ;; (NTDDI GE NTDDI_WIN7)

externdef LIBID_MSOPC:IID

ifndef __IOpcPackage_INTERFACE_DEFINED__
define __IOpcPackage_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcPackage, "42195949-3B79-4fc8-89C6-FC7FB979EE70")

.comdef IOpcPackage : public IUnknown

    GetPartSet		proc :ptr
    GetRelationshipSet	proc :ptr
   .ends

endif


ifndef __IOpcPart_INTERFACE_DEFINED__
define __IOpcPart_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcPart, "42195949-3B79-4fc8-89C6-FC7FB979EE71")

.comdef IOpcPart : public IUnknown

    GetRelationshipSet	proc :ptr
    GetContentStream	proc :ptr
    GetName		proc :ptr
    GetContentType	proc :ptr
    GetCompressionOptions proc :ptr
   .ends

endif


ifndef __IOpcRelationship_INTERFACE_DEFINED__
define __IOpcRelationship_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcRelationship, "42195949-3B79-4fc8-89C6-FC7FB979EE72")

.comdef IOpcRelationship : public IUnknown

    GetId		proc :ptr
    GetRelationshipType proc :ptr
    GetSourceUri	proc :ptr
    GetTargetUri	proc :ptr
    GetTargetMode	proc :ptr
   .ends

endif


ifndef __IOpcPartSet_INTERFACE_DEFINED__
define __IOpcPartSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcPartSet, "42195949-3B79-4fc8-89C6-FC7FB979EE73")

.comdef IOpcPartSet : public IUnknown

    GetPart		proc :ptr, :ptr
    CreatePart		proc :ptr, :LPCWSTR, :OPC_COMPRESSION_OPTIONS, :ptr
    DeletePart		proc :ptr
    PartExists		proc :ptr, :ptr
    GetEnumerator	proc :ptr
   .ends

endif


ifndef __IOpcRelationshipSet_INTERFACE_DEFINED__
define __IOpcRelationshipSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcRelationshipSet, "42195949-3B79-4fc8-89C6-FC7FB979EE74")

.comdef IOpcRelationshipSet : public IUnknown

    GetRelationship	proc :LPCWSTR, :ptr
    CreateRelationship	proc :LPCWSTR, :LPCWSTR, :ptr, :OPC_URI_TARGET_MODE, :ptr
    DeleteRelationship	proc :LPCWSTR
    RelationshipExists	proc :LPCWSTR, :ptr
    GetEnumerator	proc :ptr
    GetEnumeratorForType proc :LPCWSTR, :ptr
    GetRelationshipsContentStream proc :ptr
   .ends

endif


ifndef __IOpcPartEnumerator_INTERFACE_DEFINED__
define __IOpcPartEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcPartEnumerator, "42195949-3B79-4fc8-89C6-FC7FB979EE75")

.comdef IOpcPartEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcRelationshipEnumerator_INTERFACE_DEFINED__
define __IOpcRelationshipEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcRelationshipEnumerator, "42195949-3B79-4fc8-89C6-FC7FB979EE76")

.comdef IOpcRelationshipEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcSignaturePartReference_INTERFACE_DEFINED__
define __IOpcSignaturePartReference_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignaturePartReference, "e24231ca-59f4-484e-b64b-36eeda36072c")

.comdef IOpcSignaturePartReference : public IUnknown

    GetPartName		proc :ptr
    GetContentType	proc :ptr
    GetDigestMethod	proc :ptr
    GetDigestValue	proc
    GetTransformMethod	proc :ptr
   .ends

endif


ifndef __IOpcSignatureRelationshipReference_INTERFACE_DEFINED__
define __IOpcSignatureRelationshipReference_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureRelationshipReference, "57babac6-9d4a-4e50-8b86-e5d4051eae7c")

.comdef IOpcSignatureRelationshipReference : public IUnknown

    GetSourceUri	proc :ptr
    GetDigestMethod	proc :ptr
    GetDigestValue	proc
    GetTransformMethod	proc :ptr
    GetRelationshipSigningOption proc :ptr
    GetRelationshipSelectorEnumerator proc :ptr
   .ends

endif


ifndef __IOpcRelationshipSelector_INTERFACE_DEFINED__
define __IOpcRelationshipSelector_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcRelationshipSelector, "f8f26c7f-b28f-4899-84c8-5d5639ede75f")

.comdef IOpcRelationshipSelector : public IUnknown

    GetSelectorType	proc :ptr
    GetSelectionCriterion proc :ptr
   .ends

endif


ifndef __IOpcSignatureReference_INTERFACE_DEFINED__
define __IOpcSignatureReference_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureReference, "1b47005e-3011-4edc-be6f-0f65e5ab0342")

.comdef IOpcSignatureReference : public IUnknown

    GetId		proc :ptr
    GetUri		proc :ptr
    GetType		proc :ptr
    GetTransformMethod	proc :ptr
    GetDigestMethod	proc :ptr
    GetDigestValue	proc
   .ends

endif


ifndef __IOpcSignatureCustomObject_INTERFACE_DEFINED__
define __IOpcSignatureCustomObject_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureCustomObject, "5d77a19e-62c1-44e7-becd-45da5ae51a56")

.comdef IOpcSignatureCustomObject : public IUnknown

    GetXml		proc
   .ends

endif


ifndef __IOpcDigitalSignature_INTERFACE_DEFINED__
define __IOpcDigitalSignature_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcDigitalSignature, "52ab21dd-1cd0-4949-bc80-0c1232d00cb4")

.comdef IOpcDigitalSignature : public IUnknown

    GetNamespaces	proc :ptr, :ptr
    GetSignatureId	proc :ptr
    GetSignaturePartName proc :ptr
    GetSignatureMethod	proc :ptr
    GetCanonicalizationMethod proc :ptr
    GetSignatureValue	proc
    GetSignaturePartReferenceEnumerator proc :ptr
    GetSignatureRelationshipReferenceEnumerator proc :ptr
    GetSigningTime	proc :ptr
    GetTimeFormat	proc :ptr
    GetPackageObjectReference proc :ptr
    GetCertificateEnumerator proc :ptr
    GetCustomReferenceEnumerator proc :ptr
    GetCustomObjectEnumerator proc :ptr
    GetSignatureXml	proc :ptr, :ptr
   .ends

endif


ifndef __IOpcSigningOptions_INTERFACE_DEFINED__
define __IOpcSigningOptions_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSigningOptions, "50d2d6a5-7aeb-46c0-b241-43ab0e9b407e")

.comdef IOpcSigningOptions : public IUnknown

    GetSignatureId	proc :ptr
    SetSignatureId	proc :LPCWSTR
    GetSignatureMethod	proc :ptr
    SetSignatureMethod	proc :LPCWSTR
    GetDefaultDigestMethod proc :ptr
    SetDefaultDigestMethod proc :LPCWSTR
    GetCertificateEmbeddingOption proc :ptr
    SetCertificateEmbeddingOption proc :OPC_CERTIFICATE_EMBEDDING_OPTION
    GetTimeFormat	proc :ptr
    SetTimeFormat	proc :OPC_SIGNATURE_TIME_FORMAT
    GetSignaturePartReferenceSet proc :ptr
    GetSignatureRelationshipReferenceSet proc :ptr
    GetCustomObjectSet	proc :ptr
    GetCustomReferenceSet proc :ptr
    GetCertificateSet	proc :ptr
    GetSignaturePartName proc :ptr
    SetSignaturePartName proc :ptr
   .ends

endif


ifndef __IOpcDigitalSignatureManager_INTERFACE_DEFINED__
define __IOpcDigitalSignatureManager_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcDigitalSignatureManager, "d5e62a0b-696d-462f-94df-72e33cef2659")

.comdef IOpcDigitalSignatureManager : public IUnknown

    GetSignatureOriginPartName proc :ptr
    SetSignatureOriginPartName proc :ptr
    GetSignatureEnumerator proc :ptr
    RemoveSignature	proc :ptr
    CreateSigningOptions proc :ptr
    Validate		proc :ptr, :ptr, :ptr
    Sign		proc :ptr, :ptr, :ptr
    ReplaceSignatureXml proc :ptr, :ptr, :UINT32, :ptr
   .ends

endif


ifndef __IOpcSignaturePartReferenceEnumerator_INTERFACE_DEFINED__
define __IOpcSignaturePartReferenceEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignaturePartReferenceEnumerator, "80eb1561-8c77-49cf-8266-459b356ee99a")

.comdef IOpcSignaturePartReferenceEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcSignatureRelationshipReferenceEnumerator_INTERFACE_DEFINED__
define __IOpcSignatureRelationshipReferenceEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureRelationshipReferenceEnumerator, "773ba3e4-f021-48e4-aa04-9816db5d3495")

.comdef IOpcSignatureRelationshipReferenceEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcRelationshipSelectorEnumerator_INTERFACE_DEFINED__
define __IOpcRelationshipSelectorEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcRelationshipSelectorEnumerator, "5e50a181-a91b-48ac-88d2-bca3d8f8c0b1")

.comdef IOpcRelationshipSelectorEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcSignatureReferenceEnumerator_INTERFACE_DEFINED__
define __IOpcSignatureReferenceEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureReferenceEnumerator, "cfa59a45-28b1-4868-969e-fa8097fdc12a")

.comdef IOpcSignatureReferenceEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcSignatureCustomObjectEnumerator_INTERFACE_DEFINED__
define __IOpcSignatureCustomObjectEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureCustomObjectEnumerator, "5ee4fe1d-e1b0-4683-8079-7ea0fcf80b4c")

.comdef IOpcSignatureCustomObjectEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcCertificateEnumerator_INTERFACE_DEFINED__
define __IOpcCertificateEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcCertificateEnumerator, "85131937-8f24-421f-b439-59ab24d140b8")

.comdef IOpcCertificateEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcDigitalSignatureEnumerator_INTERFACE_DEFINED__
define __IOpcDigitalSignatureEnumerator_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcDigitalSignatureEnumerator, "967b6882-0ba3-4358-b9e7-b64c75063c5e")

.comdef IOpcDigitalSignatureEnumerator : public IUnknown

    MoveNext		proc :ptr
    MovePrevious	proc :ptr
    GetCurrent		proc :ptr
    Clone		proc :ptr
   .ends

endif


ifndef __IOpcSignaturePartReferenceSet_INTERFACE_DEFINED__
define __IOpcSignaturePartReferenceSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignaturePartReferenceSet, "6c9fe28c-ecd9-4b22-9d36-7fdde670fec0")

.comdef IOpcSignaturePartReferenceSet : public IUnknown

    Create		proc :ptr, :LPCWSTR, :OPC_CANONICALIZATION_METHOD, :ptr
    Delete		proc :ptr
    GetEnumerator	proc :ptr
   .ends

endif


ifndef __IOpcSignatureRelationshipReferenceSet_INTERFACE_DEFINED__
define __IOpcSignatureRelationshipReferenceSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureRelationshipReferenceSet, "9f863ca5-3631-404c-828d-807e0715069b")

.comdef IOpcSignatureRelationshipReferenceSet : public IUnknown

    Create		proc :ptr, :LPCWSTR, :OPC_RELATIONSHIPS_SIGNING_OPTION, :ptr, :OPC_CANONICALIZATION_METHOD, :ptr
    CreateRelationshipSelectorSet proc :ptr
    Delete		proc :ptr
    GetEnumerator	proc :ptr
   .ends

endif


ifndef __IOpcRelationshipSelectorSet_INTERFACE_DEFINED__
define __IOpcRelationshipSelectorSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcRelationshipSelectorSet, "6e34c269-a4d3-47c0-b5c4-87ff2b3b6136")

.comdef IOpcRelationshipSelectorSet : public IUnknown

    Create		proc :OPC_RELATIONSHIP_SELECTOR, :LPCWSTR, :ptr
    Delete		proc :ptr
    GetEnumerator	proc :ptr
   .ends

endif


ifndef __IOpcSignatureReferenceSet_INTERFACE_DEFINED__
define __IOpcSignatureReferenceSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureReferenceSet, "f3b02d31-ab12-42dd-9e2f-2b16761c3c1e")

.comdef IOpcSignatureReferenceSet : public IUnknown

    Create		proc :ptr, :LPCWSTR, :LPCWSTR, :LPCWSTR, :OPC_CANONICALIZATION_METHOD, :ptr
    Delete		proc :ptr
    GetEnumerator	proc :ptr
   .ends

endif


ifndef __IOpcSignatureCustomObjectSet_INTERFACE_DEFINED__
define __IOpcSignatureCustomObjectSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcSignatureCustomObjectSet, "8f792ac5-7947-4e11-bc3d-2659ff046ae1")

.comdef IOpcSignatureCustomObjectSet : public IUnknown

    Create		proc
    Delete		proc :ptr
    GetEnumerator	proc :ptr
   .ends

endif


ifndef __IOpcCertificateSet_INTERFACE_DEFINED__
define __IOpcCertificateSet_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcCertificateSet, "56ea4325-8e2d-4167-b1a4-e486d24c8fa7")

.comdef IOpcCertificateSet : public IUnknown

    _Add		proc :ptr
    Remove		proc :ptr
    GetEnumerator	proc :ptr
   .ends

endif


ifndef __IOpcFactory_INTERFACE_DEFINED__
define __IOpcFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IOpcFactory, "6d0b4446-cd73-4ab3-94f4-8ccdf6116154")

.comdef IOpcFactory : public IUnknown

    CreatePackageRootUri proc :ptr
    CreatePartUri	proc :LPCWSTR, :ptr
    CreatePackage	proc :ptr
    ReadPackageFromStream proc :ptr, :OPC_READ_FLAGS, :ptr
    WritePackageToStream proc :ptr, :OPC_WRITE_FLAGS, :ptr
    CreateDigitalSignatureManager proc :ptr, :ptr
   .ends

endif


DEFINE_GUIDS(CLSID_OpcFactory, "6B2D6BA0-9F3E-4f27-920B-313CC426A39E")

endif
endif
endif
endif
