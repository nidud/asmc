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

ifndef __windows2Eapplicationmodel2Einfrastructure2Einitfactory_h__
define __windows2Eapplicationmodel2Einfrastructure2Einitfactory_h__

include oaidl.inc
include inspectable.inc
include activation.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.Core.inc
include Windows.UI.Core.CoreWindowFactory.inc

.namespace Windows
.namespace ApplicationModel
.namespace Infrastructure

ifndef ____x_ABI_CWindows_CApplicationModel_CInfrastructure_CISetWindowWithWindowFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CInfrastructure_CISetWindowWithWindowFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Infrastructure_ISetWindowWithWindowFactory <L"Windows.ApplicationModel.Infrastructure.ISetWindowWithWindowFactory">
DEFINE_IIDX(ISetWindowWithWindowFactory,"5AF48779-F000-493C-99F1-982FBBF305E0")

.comdef ISetWindowWithWindowFactory : public IInspectable

    SetWindow           proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

endif
