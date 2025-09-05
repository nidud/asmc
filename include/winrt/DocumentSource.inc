ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __documentsource_h__
define __documentsource_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include Inspectable.inc
include DocumentTarget.inc

if (NTDDI_VERSION GE NTDDI_WIN8)

define JOB_PAGE_APPLICATION_DEFINED (-1)

ifndef __IPrintPreviewPageCollection_INTERFACE_DEFINED__
define __IPrintPreviewPageCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IPrintPreviewPageCollection, "0b31cc62-d7ec-4747-9d6e-f2537d870f2b")

.comdef IPrintPreviewPageCollection : public IUnknown

    Paginate            proc :UINT32, :ptr
    MakePage            proc :UINT32, :FLOAT, :FLOAT
   .ends

endif

ifndef __IPrintDocumentPageSource_INTERFACE_DEFINED__
define __IPrintDocumentPageSource_INTERFACE_DEFINED__
DEFINE_IIDX(IPrintDocumentPageSource, "a96bb1db-172e-4667-82b5-ad97a252318f")

.comdef IPrintDocumentPageSource : public IUnknown

    GetPreviewPageCollection proc :ptr, :ptr
    MakeDocument        proc :ptr, :ptr
   .ends

endif

ifndef __PrintDocumentSource_LIBRARY_DEFINED__
define __PrintDocumentSource_LIBRARY_DEFINED__
externdef LIBID_PrintDocumentSource:IID
endif

endif
endif
