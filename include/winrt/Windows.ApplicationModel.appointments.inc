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

ifndef __windows2Eapplicationmodel2Eappointments_h__
define __windows2Eapplicationmodel2Eappointments_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.UI.Popups.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee, "57e35198-1b41-54da-adaf-50ef1e93fded")

.comdef __FIIterator_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :UINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee, "fb9718a9-f059-52b0-a904-1a65e4281e40")

.comdef __FIIterable_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee, "ba2f633a-5182-5eda-8e2e-a66e55b320ce")

.comdef __FIVectorView_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee, "70f4b32e-f91e-55bb-9a92-0246da734bb0")

.comdef __FIVector_1_Windows__CApplicationModel__CAppointments__CAppointmentInvitee : public IInspectable

     GetAt		proc :SINT, :ptr
     get_Size		proc :ptr
     GetView		proc :ptr
     IndexOf		proc :ptr, :ptr, :ptr
     SetAt		proc :SINT, :ptr
     InsertAt		proc :SINT, :ptr
     RemoveAt		proc :SINT
     Append		proc :ptr
     RemoveAtEnd	proc
     Clear		proc
     GetMany		proc :SINT, :SINT, :ptr, :ptr
     ReplaceAll		proc :SINT, :ptr
    .ends

endif

.namespace Windows
.namespace ApplicationModel
.namespace Appointments

.enum AppointmentSensitivity {
    AppointmentSensitivity_Public,
    AppointmentSensitivity_Private
    }

.enum AppointmentBusyStatus {
    AppointmentBusyStatus_Busy,
    AppointmentBusyStatus_Tentative,
    AppointmentBusyStatus_Free,
    AppointmentBusyStatus_OutOfOffice,
    AppointmentBusyStatus_WorkingElsewhere
    }

.enum AppointmentParticipantResponse {
    AppointmentParticipantResponse_None,
    AppointmentParticipantResponse_Tentative,
    AppointmentParticipantResponse_Accepted,
    AppointmentParticipantResponse_Declined,
    AppointmentParticipantResponse_Unknown
    }

.enum AppointmentParticipantRole {
    AppointmentParticipantRole_RequiredAttendee,
    AppointmentParticipantRole_OptionalAttendee,
    AppointmentParticipantRole_Resource
    }

.enum AppointmentRecurrenceUnit {
    AppointmentRecurrenceUnit_Daily,
    AppointmentRecurrenceUnit_Weekly,
    AppointmentRecurrenceUnit_Monthly,
    AppointmentRecurrenceUnit_MonthlyOnDay,
    AppointmentRecurrenceUnit_Yearly,
    AppointmentRecurrenceUnit_YearlyOnDay
    }

.enum AppointmentDaysOfWeek {
    AppointmentDaysOfWeek_None		= 0,
    AppointmentDaysOfWeek_Sunday	= 0x1,
    AppointmentDaysOfWeek_Monday	= 0x2,
    AppointmentDaysOfWeek_Tuesday	= 0x4,
    AppointmentDaysOfWeek_Wednesday	= 0x8,
    AppointmentDaysOfWeek_Thursday	= 0x10,
    AppointmentDaysOfWeek_Friday	= 0x20,
    AppointmentDaysOfWeek_Saturday	= 0x40
    }

.enum AppointmentWeekOfMonth {
    AppointmentWeekOfMonth_First,
    AppointmentWeekOfMonth_Second,
    AppointmentWeekOfMonth_Third,
    AppointmentWeekOfMonth_Fourth,
    AppointmentWeekOfMonth_Last
    }

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Appointments_IAppointmentManagerStatics <L"Windows.ApplicationModel.Appointments.IAppointmentManagerStatics">

DEFINE_IIDX(IAppointmentManagerStatics, "3A30FA01-5C40-499D-B33F-A43050F74FC4")

.comdef IAppointmentManagerStatics : public IInspectable

    ShowAddAppointmentAsync proc :ptr, :LONG, :ptr
    ShowAddAppointmentWithPlacementAsync proc :ptr, :ptr, :ptr, :ptr
    ShowReplaceAppointmentAsync proc :HSTRING, :ptr, :ptr, :ptr
    ShowReplaceAppointmentWithPlacementAsync proc :HSTRING, :ptr, :ptr, :ptr, :ptr
    ShowReplaceAppointmentWithPlacementAndDateAsync proc :HSTRING, :ptr, :ptr, :ptr, :ptr
    ShowRemoveAppointmentAsync proc :HSTRING, :ptr,	 :ptr
    ShowRemoveAppointmentWithPlacementAsync proc :HSTRING, :ptr, :ptr, :ptr
    ShowRemoveAppointmentWithPlacementAndDateAsync proc :HSTRING, :ptr, :ptr, :ptr, :ptr
    ShowTimeFrameAsync proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentParticipant_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentParticipant_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Appointments_IAppointmentParticipant <L"Windows.ApplicationModel.Appointments.IAppointmentParticipant">

DEFINE_IIDX(IAppointmentParticipant, "615E2902-9718-467B-83FB-B293A19121DE")

.comdef IAppointmentParticipant : public IInspectable

    get_DisplayName	proc :ptr
    put_DisplayName	proc :HSTRING
    get_Address		proc :ptr
    put_Address		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentInvitee_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentInvitee_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Appointments_IAppointmentInvitee <L"Windows.ApplicationModel.Appointments.IAppointmentInvitee">

DEFINE_IIDX(IAppointmentInvitee, "13BF0796-9842-495B-B0E7-EF8F79C0701D")

.comdef IAppointmentInvitee : public IInspectable

    get_Role		proc :ptr
    put_Role		proc :LONG
    get_Response	proc :ptr
    put_Response	proc :LONG
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentRecurrence_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointmentRecurrence_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Appointments_IAppointmentRecurrence <L"Windows.ApplicationModel.Appointments.IAppointmentRecurrence">

DEFINE_IIDX(IAppointmentRecurrence, "D87B3E83-15A6-487B-B959-0C361E60E954")

.comdef IAppointmentRecurrence : public IInspectable

    get_Unit		proc :ptr
    put_Unit		proc :LONG
    get_Occurrences	proc :ptr
    put_Occurrences	proc :ptr
    get_Until		proc :ptr
    put_Until		proc :ptr
    get_Interval	proc :ptr
    put_Interval	proc :UINT32
    get_DaysOfWeek	proc :ptr
    put_DaysOfWeek	proc :ptr
    get_WeekOfMonth	proc :ptr
    put_WeekOfMonth	proc :ptr
    get_Month		proc :ptr
    put_Month		proc :UINT32
    get_Day		proc :ptr
    put_Day		proc :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CAppointments_CIAppointment_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Appointments_IAppointment <L"Windows.ApplicationModel.Appointments.IAppointment">

DEFINE_IIDX(IAppointment, "DD002F2F-2BDD-4076-90A3-22C275312965")

.comdef IAppointment : public IInspectable

    get_StartTime	proc :ptr
    put_StartTime	proc :LONG
    get_Duration	proc :ptr
    put_Duration	proc :LONG
    get_Location	proc :ptr
    put_Location	proc :HSTRING
    get_Subject		proc :ptr
    put_Subject		proc :HSTRING
    get_Details		proc :ptr
    put_Details		proc :HSTRING
    get_Reminder	proc :ptr
    put_Reminder	proc :ptr
    get_Organizer	proc :ptr
    put_Organizer	proc :ptr
    get_Invitees	proc :ptr
    get_Recurrence	proc :ptr
    put_Recurrence	proc :ptr
    get_BusyStatus	proc :ptr
    put_BusyStatus	proc :LONG
    get_AllDay		proc :BOOL
    put_AllDay		proc :BOOL
    get_Sensitivity	proc :ptr
    put_Sensitivity	proc :LONG
    get_Uri		proc :ptr
    put_Uri		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_ApplicationModel_Appointments_Appointment_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Appointments_Appointment_DEFINED
define RuntimeClass_Windows_ApplicationModel_Appointments_Appointment <L"Windows.ApplicationModel.Appointments.Appointment">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentOrganizer_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentOrganizer_DEFINED
define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentOrganizer <L"Windows.ApplicationModel.Appointments.AppointmentOrganizer">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentInvitee_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentInvitee_DEFINED
define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentInvitee <L"Windows.ApplicationModel.Appointments.AppointmentInvitee">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentRecurrence_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentRecurrence_DEFINED
define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentRecurrence <L"Windows.ApplicationModel.Appointments.AppointmentRecurrence">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentManager_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Appointments_AppointmentManager_DEFINED
define RuntimeClass_Windows_ApplicationModel_Appointments_AppointmentManager <L"Windows.ApplicationModel.Appointments.AppointmentManager">
endif

HSTRING_UserSize	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif
