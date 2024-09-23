ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif

ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eapplicationmodel2Eappointments2Eappointmentsprovider_h__
define __windows2Eapplicationmodel2Eappointments2Eappointmentsprovider_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.Appointments.inc

include windows.foundation.collections.inc

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAppointmentsProviderLaunchActionVerbsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAppointmentsProviderLaunchActionVerbsStatics_INTERFACE_DEFINED__

.namespace Windows
.namespace ApplicationModel
.namespace Appointments
.namespace AppointmentsProvider

DEFINE_IIDX(IAppointmentsProviderLaunchActionVerbsStatics, "36DBBA28-9E2E-49C6-8EF7-3AB7A5DCC8B8")

.comdef IAppointmentsProviderLaunchActionVerbsStatics : public IInspectable

    get_AddAppointment proc :ptr HSTRING
    get_ReplaceAppointment proc :ptr HSTRING
    get_RemoveAppointment proc :ptr HSTRING
    get_ShowTimeFrame proc :ptr HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAddAppointmentOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAddAppointmentOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IAddAppointmentOperation, "EC4A9AF3-620D-4C69-ADD7-9794E918081F")

.comdef IAddAppointmentOperation : public IInspectable

    get_AppointmentInformation proc :ptr ptr
    get_SourcePackageFamilyName proc :ptr HSTRING
    ReportCompleted proc :ptr HSTRING
    ReportCanceled proc
    ReportError proc :ptr HSTRING
    DismissUI proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIReplaceAppointmentOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIReplaceAppointmentOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IReplaceAppointmentOperation, "F4903D9B-9E61-4DE2-A732-2687C07D1DE8")

.comdef IReplaceAppointmentOperation : public IInspectable

    get_AppointmentId proc :ptr HSTRING
    get_AppointmentInformation proc :ptr ptr
    get_InstanceStartDate proc :ptr ptr
    get_SourcePackageFamilyName proc :ptr HSTRING
    ReportCompleted proc :ptr HSTRING
    ReportCanceled proc
    ReportError proc :HSTRING
    DismissUI proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIRemoveAppointmentOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIRemoveAppointmentOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IRemoveAppointmentOperation, "08B66ABA-FE33-46CD-A50C-A8FFB3260537")

.comdef IRemoveAppointmentOperation : public IInspectable

    get_AppointmentId proc :ptr HSTRING
    get_InstanceStartDate proc :ptr ptr
    get_SourcePackageFamilyName proc :ptr HSTRING
    ReportCompleted proc
    ReportCanceled proc
    ReportError proc :HSTRING
    DismissUI proc
   .ends

endif

.endn
.endn
.endn
.endn

define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentsProvider_AppointmentsProviderLaunchActionVerbs <L"Windows.ApplicationModel.Appointments.AppointmentsProvider.AppointmentsProviderLaunchActionVerbs">
define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentsProvider_AddAppointmentOperation < L"Windows.ApplicationModel.Appointments.AppointmentsProvider.AddAppointmentOperation">
define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentsProvider_ReplaceAppointmentOperation <L"Windows.ApplicationModel.Appointments.AppointmentsProvider.ReplaceAppointmentOperation">
define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentsProvider_RemoveAppointmentOperation <L"Windows.ApplicationModel.Appointments.AppointmentsProvider.RemoveAppointmentOperation">

HSTRING_UserSize	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif
