ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __windows2Egraphics2Eprinting2Eworkflow2Enative_h__
define __windows2Egraphics2Eprinting2Eworkflow2Enative_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include PrinterExtension.inc
include xpsobjectmodel_1.inc

ifndef __IPrintWorkflowXpsReceiver_INTERFACE_DEFINED__
define __IPrintWorkflowXpsReceiver_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintWorkflowXpsReceiver, "04097374-77B8-47F6-8167-AAE29D4CF84B")

.comdef IPrintWorkflowXpsReceiver : public IUnknown
    SetDocumentSequencePrintTicket proc :ptr
    SetDocumentSequenceUri proc :PCWSTR
    AddDocumentData     proc :UINT32, :ptr, :PCWSTR
    AddPage             proc :UINT32, :UINT32, :ptr, :PCWSTR
    Close               proc
   .ends

endif

ifndef __IPrintWorkflowObjectModelSourceFileContentNative_INTERFACE_DEFINED__
define __IPrintWorkflowObjectModelSourceFileContentNative_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintWorkflowObjectModelSourceFileContentNative, "68C9E477-993E-4052-8AC6-454EFF58DB9D")

.comdef IPrintWorkflowObjectModelSourceFileContentNative : public IUnknown
    StartXpsOMGeneration proc :ptr
    get_ObjectFactory   proc :ptr
   .ends

endif

ifndef __IPrintWorkflowXpsObjectModelTargetPackageNative_INTERFACE_DEFINED__
define __IPrintWorkflowXpsObjectModelTargetPackageNative_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintWorkflowXpsObjectModelTargetPackageNative, "7D96BC74-9B54-4CA1-AD3A-979C3D44DDAC")

.comdef IPrintWorkflowXpsObjectModelTargetPackageNative : public IUnknown
    get_DocumentPackageTarget proc :ptr
   .ends

endif

ifndef __IPrintWorkflowConfigurationNative_INTERFACE_DEFINED__
define __IPrintWorkflowConfigurationNative_INTERFACE_DEFINED__

DEFINE_IIDX(IPrintWorkflowConfigurationNative, "C056BE0A-9EE2-450A-9823-964F0006F2BB")

.comdef IPrintWorkflowConfigurationNative : public IUnknown
    get_PrinterQueue    proc :ptr
    get_DriverProperties proc :ptr
    get_UserProperties  proc :ptr
   .ends

endif

endif
