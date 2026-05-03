ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eapplicationmodel2Eappointments2Eappointmentsprovider_h__
define __windows2Eapplicationmodel2Eappointments2Eappointmentsprovider_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.ApplicationModel.Appointments.inc

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAppointmentsProviderLaunchActionVerbsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAppointmentsProviderLaunchActionVerbsStatics_INTERFACE_DEFINED__

.namespace Windows
.namespace ApplicationModel
.namespace Appointments
.namespace AppointmentsProvider

DEFINE_IIDX(IAppointmentsProviderLaunchActionVerbsStatics, "36DBBA28-9E2E-49C6-8EF7-3AB7A5DCC8B8")

.comdef IAppointmentsProviderLaunchActionVerbsStatics : public IInspectable

    get_AddAppointment proc :ptr
    get_ReplaceAppointment proc :ptr
    get_RemoveAppointment proc :ptr
    get_ShowTimeFrame proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAddAppointmentOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIAddAppointmentOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IAddAppointmentOperation, "EC4A9AF3-620D-4C69-ADD7-9794E918081F")

.comdef IAddAppointmentOperation : public IInspectable

    get_AppointmentInformation proc :ptr
    get_SourcePackageFamilyName proc :ptr
    ReportCompleted proc :ptr
    ReportCanceled proc
    ReportError proc :ptr
    DismissUI proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIReplaceAppointmentOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIReplaceAppointmentOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IReplaceAppointmentOperation, "F4903D9B-9E61-4DE2-A732-2687C07D1DE8")

.comdef IReplaceAppointmentOperation : public IInspectable

    get_AppointmentId proc :ptr
    get_AppointmentInformation proc :ptr
    get_InstanceStartDate proc :ptr
    get_SourcePackageFamilyName proc :ptr
    ReportCompleted proc :ptr
    ReportCanceled proc
    ReportError proc :HSTRING
    DismissUI proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIRemoveAppointmentOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CAppointmentsProvider_CIRemoveAppointmentOperation_INTERFACE_DEFINED__

DEFINE_IIDX(IRemoveAppointmentOperation, "08B66ABA-FE33-46CD-A50C-A8FFB3260537")

.comdef IRemoveAppointmentOperation : public IInspectable

    get_AppointmentId proc :ptr
    get_InstanceStartDate proc :ptr
    get_SourcePackageFamilyName proc :ptr
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

endif
