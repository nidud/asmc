ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __documenttarget_h__
define __documenttarget_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif

if (NTDDI_VERSION GE NTDDI_WIN7)

ifndef __IPrintDocumentPackageTarget_INTERFACE_DEFINED__
define __IPrintDocumentPackageTarget_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintDocumentPackageTarget, "1b8efec4-3019-4c27-964e-367202156906")

.comdef IPrintDocumentPackageTarget : public IUnknown

    GetPackageTargetTypes proc :ptr, :ptr
    GetPackageTarget	proc :REFGUID, :REFIID, :ptr
    Cancel		proc
   .ends

endif

.enum PrintDocumentPackageCompletion {
    PrintDocumentPackageCompletion_InProgress,
    PrintDocumentPackageCompletion_Completed,
    PrintDocumentPackageCompletion_Canceled,
    PrintDocumentPackageCompletion_Failed
    }

PrintDocumentPackageStatus STRUC
JobId			UINT32 ?
CurrentDocument		INT32 ?
CurrentPage		INT32 ?
CurrentPageTotal	INT32 ?
Completion		PrintDocumentPackageCompletion ?
PackageStatus		HRESULT ?
PrintDocumentPackageStatus ENDS


ifndef __IPrintDocumentPackageStatusEvent_INTERFACE_DEFINED__
define __IPrintDocumentPackageStatusEvent_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintDocumentPackageStatusEvent, "ed90c8ad-5c34-4d05-a1ec-0e8a9b3ad7af")

.comdef IPrintDocumentPackageStatusEvent : public IDispatch

    PackageStatusUpdated proc :ptr
   .ends

endif

ifndef __IPrintDocumentPackageTargetFactory_INTERFACE_DEFINED__
define __IPrintDocumentPackageTargetFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintDocumentPackageTargetFactory, "d2959bf7-b31b-4a3d-9600-712eb1335ba4")

.comdef IPrintDocumentPackageTargetFactory : public IUnknown

    CreateDocumentPackageTargetForPrintJob proc :LPCWSTR, :LPCWSTR, :ptr, :ptr, :ptr
   .ends

endif

ifndef __PrintDocumentTargetLib_LIBRARY_DEFINED__
define __PrintDocumentTargetLib_LIBRARY_DEFINED__

externdef LIBID_PrintDocumentTargetLib:IID

DEFINE_GUIDS(CLSID_PrintDocumentPackageTarget, "4842669e-9947-46ea-8ba2-d8cce432c2ca")
DEFINE_GUIDS(CLSID_PrintDocumentPackageTargetFactory, "348ef17d-6c81-4982-92b4-ee188a43867a")
endif

DEFINE_GUID(ID_DOCUMENTPACKAGETARGET_MSXPS,   0x9cae40a8, 0xded1, 0x41c9, 0xa9, 0xfd, 0xd7, 0x35, 0xef, 0x33, 0xae, 0xda);
DEFINE_GUID(ID_DOCUMENTPACKAGETARGET_OPENXPS, 0x0056bb72, 0x8c9c, 0x4612, 0xbd, 0x0f, 0x93, 0x01, 0x2a, 0x87, 0x09, 0x9d);

endif

if (NTDDI_VERSION GE NTDDI_WINBLUE)
DEFINE_GUID(ID_DOCUMENTPACKAGETARGET_OPENXPS_WITH_3D, 0x63dbd720, 0x8b14, 0x4577, 0xb0, 0x74, 0x7b, 0xb1, 0x1b, 0x59, 0x6d, 0x28);
endif

endif
