ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __xpsobjectmodel_1_h__
define __xpsobjectmodel_1_h__

include oaidl.inc
include ocidl.inc
include XpsObjectModel.inc
include winapifamily.inc

if (NTDDI_VERSION ge NTDDI_WIN8)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum XPS_DOCUMENT_TYPE {
	XPS_DOCUMENT_TYPE_UNSPECIFIED	= 1,
	XPS_DOCUMENT_TYPE_XPS	= ( XPS_DOCUMENT_TYPE_UNSPECIFIED + 1 ) ,
	XPS_DOCUMENT_TYPE_OPENXPS	= ( XPS_DOCUMENT_TYPE_XPS + 1 )
    }

ifndef __IXpsOMObjectFactory1_INTERFACE_DEFINED__
define __IXpsOMObjectFactory1_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMObjectFactory1, "0a91b617-d612-4181-bf7c-be5824e9cc8f")

.comdef IXpsOMObjectFactory1 : public IXpsOMObjectFactory
    GetDocumentTypeFromFile proc :LPCWSTR, :ptr
    GetDocumentTypeFromStream proc :ptr, :ptr
    ConvertHDPhotoToJpegXR proc :ptr
    ConvertJpegXRToHDPhoto proc :ptr
    CreatePackageWriterOnFile1 proc :LPCWSTR, :LPSECURITY_ATTRIBUTES, :DWORD, :BOOL, :XPS_INTERLEAVING, :ptr, :ptr, :ptr, :ptr, :ptr, :XPS_DOCUMENT_TYPE, :ptr
    CreatePackageWriterOnStream1 proc :ptr, :BOOL, :XPS_INTERLEAVING, :ptr, :ptr, :ptr, :ptr, :ptr, :XPS_DOCUMENT_TYPE, :ptr
    CreatePackage1	proc :ptr
    CreatePackageFromStream1 proc :ptr, :BOOL, :ptr
    CreatePackageFromFile1 proc :LPCWSTR, :BOOL, :ptr
    CreatePage1		proc :ptr, :LPCWSTR, :ptr, :ptr
    CreatePageFromStream1 proc :ptr, :ptr, :ptr, :BOOL, :ptr
    CreateRemoteDictionaryResourceFromStream1 proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IXpsOMPackage1_INTERFACE_DEFINED__
define __IXpsOMPackage1_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPackage1, "95a9435e-12bb-461b-8e7f-c6adb04cd96a")

.comdef IXpsOMPackage1 : public IXpsOMPackage
    GetDocumentType	proc :ptr
    WriteToFile1	proc :LPCWSTR, :LPSECURITY_ATTRIBUTES, :DWORD, :BOOL, :XPS_DOCUMENT_TYPE
    WriteToStream1	proc :ptr, :BOOL, :XPS_DOCUMENT_TYPE
   .ends

endif

ifndef __IXpsOMPage1_INTERFACE_DEFINED__
define __IXpsOMPage1_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMPage1, "305b60ef-6892-4dda-9cbb-3aa65974508a")

.comdef IXpsOMPage1 : public IXpsOMPage
    GetDocumentType	proc :ptr
    Write1		proc :ptr, :BOOL, :XPS_DOCUMENT_TYPE
   .ends

endif

ifndef __IXpsDocumentPackageTarget_INTERFACE_DEFINED__
define __IXpsDocumentPackageTarget_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsDocumentPackageTarget, "3b0b6d38-53ad-41da-b212-d37637a6714e")

.comdef IXpsDocumentPackageTarget : public IUnknown
    GetXpsOMPackageWriter proc :ptr, :ptr, :ptr
    GetXpsOMFactory	proc :ptr
    GetXpsType		proc :ptr
   .ends

endif

ifndef __IXpsOMRemoteDictionaryResource1_INTERFACE_DEFINED__
define __IXpsOMRemoteDictionaryResource1_INTERFACE_DEFINED__

DEFINE_IIDX(IXpsOMRemoteDictionaryResource1, "BF8FC1D4-9D46-4141-BA5F-94BB9250D041")

.comdef IXpsOMRemoteDictionaryResource1 : public IXpsOMRemoteDictionaryResource
    GetDocumentType	proc :ptr
    Write1		proc :ptr, :XPS_DOCUMENT_TYPE
   .ends

endif

define XPS_E_INVALID_NUMBER_OF_POINTS_IN_CURVE_SEGMENTS	    MAKE_HRESULT(1, FACILITY_XPS, 0x600)
define XPS_E_ABSOLUTE_REFERENCE				    MAKE_HRESULT(1, FACILITY_XPS, 0x601)
define XPS_E_INVALID_NUMBER_OF_COLOR_CHANNELS		    MAKE_HRESULT(1, FACILITY_XPS, 0x602)
endif

endif

endif
