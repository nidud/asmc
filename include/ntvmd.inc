; NTVMD.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __NTVMD_INC
define __NTVMD_INC

getAF	    proto stdcall
getAH	    proto stdcall
getAL	    proto stdcall
getAX	    proto stdcall
getBH	    proto stdcall
getBL	    proto stdcall
getBP	    proto stdcall
getBX	    proto stdcall
getCF	    proto stdcall
getCH	    proto stdcall
getCL	    proto stdcall
getCS	    proto stdcall
getCX	    proto stdcall
getDF	    proto stdcall
getDH	    proto stdcall
getDI	    proto stdcall
getDL	    proto stdcall
getDS	    proto stdcall
getDX	    proto stdcall
getEAX	    proto stdcall
getEBP	    proto stdcall
getEBX	    proto stdcall
getECX	    proto stdcall
getEDI	    proto stdcall
getEDX	    proto stdcall
getEFLAGS   proto stdcall
getEIP	    proto stdcall
getES	    proto stdcall
getESI	    proto stdcall
getESP	    proto stdcall
getFS	    proto stdcall
getGS	    proto stdcall
getIF	    proto stdcall
getIP	    proto stdcall

getMSW	    proto stdcall
getOF	    proto stdcall
getPF	    proto stdcall
getSF	    proto stdcall
getSI	    proto stdcall
getSP	    proto stdcall
getSS	    proto stdcall
getZF	    proto stdcall

setAF	    proto stdcall :dword
setAH	    proto stdcall :dword
setAL	    proto stdcall :dword
setAX	    proto stdcall :dword
setBH	    proto stdcall :dword
setBL	    proto stdcall :dword
setBP	    proto stdcall :dword
setBX	    proto stdcall :dword
setCF	    proto stdcall :dword
setCH	    proto stdcall :dword
setCL	    proto stdcall :dword
setCS	    proto stdcall :dword
setCX	    proto stdcall :dword
setDF	    proto stdcall :dword
setDH	    proto stdcall :dword
setDI	    proto stdcall :dword
setDL	    proto stdcall :dword
setDS	    proto stdcall :dword
setDX	    proto stdcall :dword
setEAX	    proto stdcall :dword
setEBP	    proto stdcall :dword
setEBX	    proto stdcall :dword
setECX	    proto stdcall :dword
setEDI	    proto stdcall :dword
setEDX	    proto stdcall :dword
setEFLAGS   proto stdcall :dword
setEIP	    proto stdcall :dword
setES	    proto stdcall :dword
setESI	    proto stdcall :dword
setESP	    proto stdcall :dword
setFS	    proto stdcall :dword
setGS	    proto stdcall :dword
setIF	    proto stdcall :dword
setIP	    proto stdcall :dword

setMSW	    proto stdcall :dword
setOF	    proto stdcall :dword
setPF	    proto stdcall :dword
setSF	    proto stdcall :dword
setSI	    proto stdcall :dword
setSP	    proto stdcall :dword
setSS	    proto stdcall :dword
setZF	    proto stdcall :dword

BlockWOWIdle			proto stdcall :dword
DBGNotifyDebugged		proto stdcall :dword
DBGNotifyNewTask		proto stdcall :dword, :dword
DBGNotifyRemoteThreadAddress	proto stdcall :dword, :dword
DispatchInterrupts		proto stdcall
DpmiSetIncrementalAlloc		proto stdcall :dword
GetDOSAppName			proto stdcall :dword
GetWOWShortCutInfo		proto stdcall :dword, :dword
IsCdRomFile			proto stdcall :dword
MGetVdmPointer			proto stdcall :dword, :dword, :dword
RegisterWOWIdle			proto stdcall
ResumeTimerThread		proto stdcall
SetShadowDescriptorEntries	proto stdcall :dword, :dword
Sim32pGetVDMPointer		proto stdcall :dword, :dword
SoftPcEoi			proto stdcall :dword, :dword
SuspendTimerThread		proto stdcall

VDDAllocMem			proto stdcall :dword, :dword, :dword
VDDAllocateDosHandle		proto stdcall :dword, :dword, :dword
VDDAssociateNtHandle		proto stdcall :dword, :dword, :dword
VDDDeInstallIOHook		proto stdcall :dword, :dword, :dword
VDDDeInstallMemoryHook		proto stdcall :dword, :dword, :dword
VDDDeInstallUserHook		proto stdcall :dword
VDDExcludeMem			proto stdcall :dword, :dword, :dword
VDDFreeMem			proto stdcall :dword, :dword, :dword
VDDIncludeMem			proto stdcall :dword, :dword, :dword
VDDInstallIOHook		proto stdcall :dword, :dword, :dword, :dword
VDDInstallMemoryHook		proto stdcall :dword, :dword, :dword, :dword
VDDInstallUserHook		proto stdcall :dword, :dword, :dword, :dword, :dword
VDDQueryDMA			proto stdcall :dword, :dword, :dword
VDDReleaseDosHandle		proto stdcall :dword, :dword
VDDReleaseIrqLine		proto stdcall :dword, :dword
VDDRequestDMA			proto stdcall :dword, :dword, :dword, :dword
VDDReserveIrqLine		proto stdcall :dword, :dword
VDDRetrieveNtHandle		proto stdcall :dword, :dword, :dword, :dword
VDDSetDMA			proto stdcall :dword, :dword, :dword, :dword
VDDSimulate16			proto stdcall
VDDTerminateVDM			proto stdcall

VdmDbgAttach			proto stdcall
VdmGetParametersInfoError	proto stdcall
VdmMapFlat			proto stdcall :dword, :dword, :dword
VdmParametersInfo		proto stdcall :dword, :dword, :dword
VdmTraceEvent			proto stdcall :dword, :dword, :dword

WOWSysErrorBox			proto stdcall :dword, :dword, :dword, :dword, :dword
WaitIfIdle			proto stdcall
call_ica_hw_interrupt		proto stdcall :dword, :dword, :dword
cmdCheckTemp			proto stdcall :dword
cmdCheckTempInit		proto stdcall
cpu_createthread		proto stdcall :dword, :dword
getIntelRegistersPointer	proto stdcall

demClientErrorEx		proto stdcall :dword, :dword, :dword
demFileDelete			proto stdcall :dword
demFileFindFirst		proto stdcall :dword, :dword, :dword
demFileFindNext			proto stdcall :dword
demGetCurrentDirectoryLCDS	proto stdcall :dword, :dword
demGetFileTimeByHandle_WOW	proto stdcall :dword
demGetPhysicalDriveType		proto stdcall :dword
demIsShortPathName		proto stdcall :dword, :dword
demLFNCleanup			proto stdcall
demLFNGetCurrentDirectory	proto stdcall :dword, :dword
demSetCurrentDirectoryGetDrive	proto stdcall :dword, :dword
demSetCurrentDirectoryLCDS	proto stdcall :dword, :dword
demWOWLFNAllocateSearchHandle	proto stdcall :dword
demWOWLFNCloseSearchHandle	proto stdcall :dword
demWOWLFNEntry			proto stdcall :dword
demWOWLFNGetSearchHandle	proto stdcall :dword
demWOWLFNInit			proto stdcall :dword

CurrentMonitorTeb		proto c :vararg
Dos_Flag_Addr			proto c :vararg
ExpLdt				proto c :vararg
FlatAddress			proto c :vararg
SelectorLimit			proto c :vararg
fSeparateWow			proto c :vararg
pDeviceChain			proto c :vararg

host_CreateThread		proto stdcall :dword, :dword, :dword, :dword, :dword, :dword
host_ExitThread			proto stdcall :dword
host_com_close			proto stdcall :dword
host_direct_access_error	proto stdcall :dword
host_simulate			proto stdcall

endif
