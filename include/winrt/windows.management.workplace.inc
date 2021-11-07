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

ifndef __windows2Emanagement2Eworkplace_h__
define __windows2Emanagement2Eworkplace_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace Management
.namespace Workplace

ifndef ____x_ABI_CWindows_CManagement_CWorkplace_CIWorkplaceSettingsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CManagement_CWorkplace_CIWorkplaceSettingsStatics_INTERFACE_DEFINED__

.comdef IWorkplaceSettingsStatics : public IInspectable

    get_IsMicrosoftAccountOptional proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Management_Workplace_WorkplaceSettings_DEFINED
define RUNTIMECLASS_Windows_Management_Workplace_WorkplaceSettings_DEFINED
define RuntimeClass_Windows_Management_Workplace_WorkplaceSettings <L"Windows.Management.Workplace.WorkplaceSettings">
endif

endif
