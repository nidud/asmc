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

ifndef __windows2Emanagement2Ecore_h__
define __windows2Emanagement2Ecore_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc

.namespace Windows
.namespace Management
.namespace Core

ifndef ____x_ABI_CWindows_CManagement_CCore_CIApplicationDataManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CManagement_CCore_CIApplicationDataManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Management_Core_IApplicationDataManagerStatics <L"Windows.Management.Core.IApplicationDataManagerStatics">
DEFINE_IIDX(IApplicationDataManagerStatics, "1E1862E3-698E-49A1-9752-DEE94925B9B3")

.comdef IApplicationDataManagerStatics : public IInspectable

    CreateForPackageFamily proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CManagement_CCore_CIApplicationDataManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CManagement_CCore_CIApplicationDataManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Management_Core_IApplicationDataManager <L"Windows.Management.Core.IApplicationDataManager">
DEFINE_IIDX(IApplicationDataManager, "74D10432-2E99-4000-9A3A-64307E858129")

.comdef IApplicationDataManager : public IInspectable

   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Management_Core_ApplicationDataManager_DEFINED
define RUNTIMECLASS_Windows_Management_Core_ApplicationDataManager_DEFINED
define RuntimeClass_Windows_Management_Core_ApplicationDataManager <L"Windows.Management.Core.ApplicationDataManager">
endif

endif
