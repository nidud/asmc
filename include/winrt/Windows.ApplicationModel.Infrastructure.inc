ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eapplicationmodel2Einfrastructure2Einitfactory_h__
define __windows2Eapplicationmodel2Einfrastructure2Einitfactory_h__
ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include activation.inc
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
