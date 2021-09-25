ifndef _LMERRLOG_
define _LMERRLOG_

ERROR_LOG		STRUC
el_len			dd ?
el_reserved		dd ?
el_time			dd ?
el_error		dd ?
el_name			LPWSTR ?
el_text			LPWSTR ?
el_data			LPBYTE ?
el_data_size		dd ?
el_nstrings		dd ?
ERROR_LOG		ENDS
PERROR_LOG		typedef ptr ERROR_LOG
LPERROR_LOG		typedef ptr ERROR_LOG

REVISED_ERROR_LOG_STRUCT equ 1

ifndef _LMHLOGDEFINED_
define _LMHLOGDEFINED_

HLOG			STRUC
time			dd ?
last_flags		dd ?
_offset			dd ?
rec_offset		dd ?
HLOG			ENDS
PHLOG			typedef ptr HLOG
LPHLOG			typedef ptr HLOG

LOGFLAGS_FORWARD	equ 0
LOGFLAGS_BACKWARD	equ 0x1
LOGFLAGS_SEEK		equ 0x2

endif


;NET_API_STATUS
NetErrorLogClear proto WINAPI \
	 UncServerName: LPCWSTR,
	    BackupFile: LPCWSTR,
	      Reserved: LPBYTE


;NET_API_STATUS
NetErrorLogRead proto WINAPI \
	 UncServerName: LPCWSTR,
	     Reserved1: LPWSTR,
	ErrorLogHandle: LPHLOG,
	       _Offset: DWORD,
	     Reserved2: LPDWORD,
	     Reserved3: DWORD,
	    OffsetFlag: DWORD,
		BufPtr: ptr LPBYTE,
	   PrefMaxSize: DWORD,
	     BytesRead: LPDWORD,
	TotalAvailable: LPDWORD


;NET_API_STATUS
NetErrorLogWrite proto WINAPI \
	     Reserved1: LPBYTE,
		  Code: DWORD,
	     Component: LPCWSTR,
		Buffer: LPBYTE,
	      NumBytes: DWORD,
		MsgBuf: LPBYTE,
	      StrCount: DWORD,
	     Reserved2: LPBYTE


ERRLOG_BASE		equ 3100
NELOG_Internal_Error	equ (ERRLOG_BASE + 0)
NELOG_Resource_Shortage equ (ERRLOG_BASE + 1)
NELOG_Unable_To_Lock_Segment equ (ERRLOG_BASE + 2)
NELOG_Unable_To_Unlock_Segment equ (ERRLOG_BASE + 3)
NELOG_Uninstall_Service equ (ERRLOG_BASE + 4)
NELOG_Init_Exec_Fail	equ (ERRLOG_BASE + 5)
NELOG_Ncb_Error		equ (ERRLOG_BASE + 6)
NELOG_Net_Not_Started	equ (ERRLOG_BASE + 7)
NELOG_Ioctl_Error	equ (ERRLOG_BASE + 8)
NELOG_System_Semaphore	equ (ERRLOG_BASE + 9)
NELOG_Init_OpenCreate_Err equ (ERRLOG_BASE + 10)
NELOG_NetBios		equ (ERRLOG_BASE + 11)
NELOG_SMB_Illegal	equ (ERRLOG_BASE + 12)
NELOG_Service_Fail	equ (ERRLOG_BASE + 13)
NELOG_Entries_Lost	equ (ERRLOG_BASE + 14)

NELOG_Init_Seg_Overflow equ (ERRLOG_BASE + 20)
NELOG_Srv_No_Mem_Grow	equ (ERRLOG_BASE + 21)
NELOG_Access_File_Bad	equ (ERRLOG_BASE + 22)
NELOG_Srvnet_Not_Started equ (ERRLOG_BASE + 23)
NELOG_Init_Chardev_Err	equ (ERRLOG_BASE + 24)
NELOG_Remote_API	equ (ERRLOG_BASE + 25)
NELOG_Ncb_TooManyErr	equ (ERRLOG_BASE + 26)
NELOG_Mailslot_err	equ (ERRLOG_BASE + 27)
NELOG_ReleaseMem_Alert	equ (ERRLOG_BASE + 28)
NELOG_AT_cannot_write	equ (ERRLOG_BASE + 29)
NELOG_Cant_Make_Msg_File equ (ERRLOG_BASE + 30)
NELOG_Exec_Netservr_NoMem equ (ERRLOG_BASE + 31)
NELOG_Server_Lock_Failure equ (ERRLOG_BASE + 32)

NELOG_Msg_Shutdown	equ (ERRLOG_BASE + 40)
NELOG_Msg_Sem_Shutdown	equ (ERRLOG_BASE + 41)
NELOG_Msg_Log_Err	equ (ERRLOG_BASE + 50)

NELOG_VIO_POPUP_ERR	equ (ERRLOG_BASE + 51)
NELOG_Msg_Unexpected_SMB_Type equ (ERRLOG_BASE + 52)

NELOG_Wksta_Infoseg	equ (ERRLOG_BASE + 60)
NELOG_Wksta_Compname	equ (ERRLOG_BASE + 61)
NELOG_Wksta_BiosThreadFailure equ (ERRLOG_BASE + 62)
NELOG_Wksta_IniSeg	equ (ERRLOG_BASE + 63)
NELOG_Wksta_HostTab_Full equ (ERRLOG_BASE + 64)
NELOG_Wksta_Bad_Mailslot_SMB equ (ERRLOG_BASE + 65)
NELOG_Wksta_UASInit	equ (ERRLOG_BASE + 66)
NELOG_Wksta_SSIRelogon	equ (ERRLOG_BASE + 67)

NELOG_Build_Name	equ (ERRLOG_BASE + 70)
NELOG_Name_Expansion	equ (ERRLOG_BASE + 71)
NELOG_Message_Send	equ (ERRLOG_BASE + 72)
NELOG_Mail_Slt_Err	equ (ERRLOG_BASE + 73)
NELOG_AT_cannot_read	equ (ERRLOG_BASE + 74)
NELOG_AT_sched_err	equ (ERRLOG_BASE + 75)
NELOG_AT_schedule_file_created equ (ERRLOG_BASE + 76)
NELOG_Srvnet_NB_Open	equ (ERRLOG_BASE + 77)
NELOG_AT_Exec_Err	equ (ERRLOG_BASE + 78)

NELOG_Lazy_Write_Err	equ (ERRLOG_BASE + 80)
NELOG_HotFix		equ (ERRLOG_BASE + 81)
NELOG_HardErr_From_Server equ (ERRLOG_BASE + 82)
NELOG_LocalSecFail1	equ (ERRLOG_BASE + 83)
NELOG_LocalSecFail2	equ (ERRLOG_BASE + 84)
NELOG_LocalSecFail3	equ (ERRLOG_BASE + 85)
NELOG_LocalSecGeneralFail equ (ERRLOG_BASE + 86)

NELOG_NetWkSta_Internal_Error equ (ERRLOG_BASE + 90)
NELOG_NetWkSta_No_Resource equ (ERRLOG_BASE + 91)
NELOG_NetWkSta_SMB_Err	equ (ERRLOG_BASE + 92)
NELOG_NetWkSta_VC_Err	equ (ERRLOG_BASE + 93)
NELOG_NetWkSta_Stuck_VC_Err equ (ERRLOG_BASE + 94)
NELOG_NetWkSta_NCB_Err	equ (ERRLOG_BASE + 95)
NELOG_NetWkSta_Write_Behind_Err equ (ERRLOG_BASE + 96)
NELOG_NetWkSta_Reset_Err equ (ERRLOG_BASE + 97)
NELOG_NetWkSta_Too_Many equ (ERRLOG_BASE + 98)

NELOG_Srv_Thread_Failure equ (ERRLOG_BASE + 104)
NELOG_Srv_Close_Failure equ (ERRLOG_BASE + 105)
NELOG_ReplUserCurDir	equ (ERRLOG_BASE + 106)
NELOG_ReplCannotMasterDir equ (ERRLOG_BASE + 107)
NELOG_ReplUpdateError	equ (ERRLOG_BASE + 108)
NELOG_ReplLostMaster	equ (ERRLOG_BASE + 109)
NELOG_NetlogonAuthDCFail equ (ERRLOG_BASE + 110)
NELOG_ReplLogonFailed	equ (ERRLOG_BASE + 111)
NELOG_ReplNetErr	equ (ERRLOG_BASE + 112)
NELOG_ReplMaxFiles	equ (ERRLOG_BASE + 113)

NELOG_ReplMaxTreeDepth	equ (ERRLOG_BASE + 114)
NELOG_ReplBadMsg	equ (ERRLOG_BASE + 115)
NELOG_ReplSysErr	equ (ERRLOG_BASE + 116)
NELOG_ReplUserLoged	equ (ERRLOG_BASE + 117)
NELOG_ReplBadImport	equ (ERRLOG_BASE + 118)
NELOG_ReplBadExport	equ (ERRLOG_BASE + 119)
NELOG_ReplSignalFileErr equ (ERRLOG_BASE + 120)
NELOG_DiskFT		equ (ERRLOG_BASE+121)
NELOG_ReplAccessDenied	equ (ERRLOG_BASE + 122)
NELOG_NetlogonFailedPrimary equ (ERRLOG_BASE + 123)
NELOG_NetlogonPasswdSetFailed equ (ERRLOG_BASE + 124)
NELOG_NetlogonTrackingError equ (ERRLOG_BASE + 125)
NELOG_NetlogonSyncError equ (ERRLOG_BASE + 126)
NELOG_NetlogonRequireSignOrSealError equ (ERRLOG_BASE + 127)

NELOG_UPS_PowerOut	equ (ERRLOG_BASE + 130)
NELOG_UPS_Shutdown	equ (ERRLOG_BASE + 131)
NELOG_UPS_CmdFileError	equ (ERRLOG_BASE + 132)
NELOG_UPS_CannotOpenDriver equ (ERRLOG_BASE+133)
NELOG_UPS_PowerBack	equ (ERRLOG_BASE + 134)
NELOG_UPS_CmdFileConfig equ (ERRLOG_BASE + 135)
NELOG_UPS_CmdFileExec	equ (ERRLOG_BASE + 136)

NELOG_Missing_Parameter equ (ERRLOG_BASE + 150)
NELOG_Invalid_Config_Line equ (ERRLOG_BASE + 151)
NELOG_Invalid_Config_File equ (ERRLOG_BASE + 152)
NELOG_File_Changed	equ (ERRLOG_BASE + 153)
NELOG_Files_Dont_Fit	equ (ERRLOG_BASE + 154)
NELOG_Wrong_DLL_Version equ (ERRLOG_BASE + 155)
NELOG_Error_in_DLL	equ (ERRLOG_BASE + 156)
NELOG_System_Error	equ (ERRLOG_BASE + 157)
NELOG_FT_ErrLog_Too_Large equ (ERRLOG_BASE + 158)
NELOG_FT_Update_In_Progress equ (ERRLOG_BASE + 159)
NELOG_Joined_Domain	equ (ERRLOG_BASE + 160)
NELOG_Joined_Workgroup	equ (ERRLOG_BASE + 161)

NELOG_OEM_Code		equ (ERRLOG_BASE + 199)

ERRLOG2_BASE		equ 5700

NELOG_NetlogonSSIInitError equ (ERRLOG2_BASE + 0)
NELOG_NetlogonFailedToUpdateTrustList equ (ERRLOG2_BASE + 1)
NELOG_NetlogonFailedToAddRpcInterface equ (ERRLOG2_BASE + 2)
NELOG_NetlogonFailedToReadMailslot equ (ERRLOG2_BASE + 3)
NELOG_NetlogonFailedToRegisterSC equ (ERRLOG2_BASE + 4)
NELOG_NetlogonChangeLogCorrupt equ (ERRLOG2_BASE + 5)
NELOG_NetlogonFailedToCreateShare equ (ERRLOG2_BASE + 6)
NELOG_NetlogonDownLevelLogonFailed equ (ERRLOG2_BASE + 7)
NELOG_NetlogonDownLevelLogoffFailed equ (ERRLOG2_BASE + 8)
NELOG_NetlogonNTLogonFailed equ (ERRLOG2_BASE + 9)
NELOG_NetlogonNTLogoffFailed equ (ERRLOG2_BASE + 10)
NELOG_NetlogonPartialSyncCallSuccess equ (ERRLOG2_BASE + 11)
NELOG_NetlogonPartialSyncCallFailed equ (ERRLOG2_BASE + 12)
NELOG_NetlogonFullSyncCallSuccess equ (ERRLOG2_BASE + 13)
NELOG_NetlogonFullSyncCallFailed equ (ERRLOG2_BASE + 14)
NELOG_NetlogonPartialSyncSuccess equ (ERRLOG2_BASE + 15)

NELOG_NetlogonPartialSyncFailed equ (ERRLOG2_BASE + 16)
NELOG_NetlogonFullSyncSuccess equ (ERRLOG2_BASE + 17)

NELOG_NetlogonFullSyncFailed equ (ERRLOG2_BASE + 18)
NELOG_NetlogonAuthNoDomainController equ (ERRLOG2_BASE + 19)
NELOG_NetlogonAuthNoTrustLsaSecret equ (ERRLOG2_BASE + 20)
NELOG_NetlogonAuthNoTrustSamAccount equ (ERRLOG2_BASE + 21)
NELOG_NetlogonServerAuthFailed equ (ERRLOG2_BASE + 22)
NELOG_NetlogonServerAuthNoTrustSamAccount equ (ERRLOG2_BASE + 23)

NELOG_FailedToRegisterSC equ (ERRLOG2_BASE + 24)
NELOG_FailedToSetServiceStatus equ (ERRLOG2_BASE + 25)
NELOG_FailedToGetComputerName equ (ERRLOG2_BASE + 26)
NELOG_DriverNotLoaded	equ (ERRLOG2_BASE + 27)
NELOG_NoTranportLoaded	equ (ERRLOG2_BASE + 28)

NELOG_NetlogonFailedDomainDelta equ (ERRLOG2_BASE + 29)
NELOG_NetlogonFailedGlobalGroupDelta equ (ERRLOG2_BASE + 30)
NELOG_NetlogonFailedLocalGroupDelta equ (ERRLOG2_BASE + 31)
NELOG_NetlogonFailedUserDelta equ (ERRLOG2_BASE + 32)
NELOG_NetlogonFailedPolicyDelta equ (ERRLOG2_BASE + 33)
NELOG_NetlogonFailedTrustedDomainDelta equ (ERRLOG2_BASE + 34)
NELOG_NetlogonFailedAccountDelta equ (ERRLOG2_BASE + 35)
NELOG_NetlogonFailedSecretDelta equ (ERRLOG2_BASE + 36)
NELOG_NetlogonSystemError equ (ERRLOG2_BASE + 37)
NELOG_NetlogonDuplicateMachineAccounts equ (ERRLOG2_BASE + 38)
NELOG_NetlogonTooManyGlobalGroups equ (ERRLOG2_BASE + 39)
NELOG_NetlogonBrowserDriver equ (ERRLOG2_BASE + 40)
NELOG_NetlogonAddNameFailure equ (ERRLOG2_BASE + 41)
NELOG_RplMessages	equ (ERRLOG2_BASE + 42)
NELOG_RplXnsBoot	equ (ERRLOG2_BASE + 43)
NELOG_RplSystem		equ (ERRLOG2_BASE + 44)
NELOG_RplWkstaTimeout	equ (ERRLOG2_BASE + 45)
NELOG_RplWkstaFileOpen	equ (ERRLOG2_BASE + 46)
NELOG_RplWkstaFileRead	equ (ERRLOG2_BASE + 47)
NELOG_RplWkstaMemory	equ (ERRLOG2_BASE + 48)
NELOG_RplWkstaFileChecksum equ (ERRLOG2_BASE + 49)
NELOG_RplWkstaFileLineCount equ (ERRLOG2_BASE + 50)
NELOG_RplWkstaBbcFile	equ (ERRLOG2_BASE + 51)
NELOG_RplWkstaFileSize	equ (ERRLOG2_BASE + 52)
NELOG_RplWkstaInternal	equ (ERRLOG2_BASE + 53)
NELOG_RplWkstaWrongVersion equ (ERRLOG2_BASE + 54)
NELOG_RplWkstaNetwork	equ (ERRLOG2_BASE + 55)
NELOG_RplAdapterResource equ (ERRLOG2_BASE + 56)
NELOG_RplFileCopy	equ (ERRLOG2_BASE + 57)
NELOG_RplFileDelete	equ (ERRLOG2_BASE + 58)
NELOG_RplFilePerms	equ (ERRLOG2_BASE + 59)
NELOG_RplCheckConfigs	equ (ERRLOG2_BASE + 60)
NELOG_RplCreateProfiles equ (ERRLOG2_BASE + 61)
NELOG_RplRegistry	equ (ERRLOG2_BASE + 62)
NELOG_RplReplaceRPLDISK equ (ERRLOG2_BASE + 63)
NELOG_RplCheckSecurity	equ (ERRLOG2_BASE + 64)
NELOG_RplBackupDatabase equ (ERRLOG2_BASE + 65)
NELOG_RplInitDatabase	equ (ERRLOG2_BASE + 66)
NELOG_RplRestoreDatabaseFailure equ (ERRLOG2_BASE + 67)
NELOG_RplRestoreDatabaseSuccess equ (ERRLOG2_BASE + 68)
NELOG_RplInitRestoredDatabase equ (ERRLOG2_BASE + 69)

NELOG_NetlogonSessionTypeWrong equ (ERRLOG2_BASE + 70)
NELOG_RplUpgradeDBTo40	equ (ERRLOG2_BASE + 71)
NELOG_NetlogonLanmanBdcsNotAllowed equ (ERRLOG2_BASE + 72)
NELOG_NetlogonNoDynamicDns equ (ERRLOG2_BASE + 73)

NELOG_NetlogonDynamicDnsRegisterFailure equ (ERRLOG2_BASE + 74)
NELOG_NetlogonDynamicDnsDeregisterFailure equ (ERRLOG2_BASE + 75)
NELOG_NetlogonFailedFileCreate equ (ERRLOG2_BASE + 76)
NELOG_NetlogonGetSubnetToSite equ (ERRLOG2_BASE + 77)
NELOG_NetlogonNoSiteForClient equ (ERRLOG2_BASE + 78)
NELOG_NetlogonBadSiteName equ (ERRLOG2_BASE + 79)
NELOG_NetlogonBadSubnetName equ (ERRLOG2_BASE + 80)
NELOG_NetlogonDynamicDnsServerFailure equ (ERRLOG2_BASE + 81)
NELOG_NetlogonDynamicDnsFailure equ (ERRLOG2_BASE + 82)
NELOG_NetlogonRpcCallCancelled equ (ERRLOG2_BASE + 83)
NELOG_NetlogonDcSiteCovered equ (ERRLOG2_BASE + 84)
NELOG_NetlogonDcSiteNotCovered equ (ERRLOG2_BASE + 85)
NELOG_NetlogonGcSiteCovered equ (ERRLOG2_BASE + 86)
NELOG_NetlogonGcSiteNotCovered equ (ERRLOG2_BASE + 87)
NELOG_NetlogonFailedSpnUpdate equ (ERRLOG2_BASE + 88)
NELOG_NetlogonFailedDnsHostNameUpdate equ (ERRLOG2_BASE + 89)
NELOG_NetlogonAuthNoUplevelDomainController equ (ERRLOG2_BASE + 90)
NELOG_NetlogonAuthDomainDowngraded equ (ERRLOG2_BASE + 91)
NELOG_NetlogonNdncSiteCovered equ (ERRLOG2_BASE + 92)
NELOG_NetlogonNdncSiteNotCovered equ (ERRLOG2_BASE + 93)
NELOG_NetlogonDcOldSiteCovered equ (ERRLOG2_BASE + 94)
NELOG_NetlogonDcSiteNotCoveredAuto equ (ERRLOG2_BASE + 95)
NELOG_NetlogonGcOldSiteCovered equ (ERRLOG2_BASE + 96)
NELOG_NetlogonGcSiteNotCoveredAuto equ (ERRLOG2_BASE + 97)
NELOG_NetlogonNdncOldSiteCovered equ (ERRLOG2_BASE + 98)
NELOG_NetlogonNdncSiteNotCoveredAuto equ (ERRLOG2_BASE + 99)
NELOG_NetlogonSpnMultipleSamAccountNames equ (ERRLOG2_BASE + 100)
NELOG_NetlogonSpnCrackNamesFailure equ (ERRLOG2_BASE + 101)
NELOG_NetlogonNoAddressToSiteMapping equ (ERRLOG2_BASE + 102)
NELOG_NetlogonInvalidGenericParameterValue equ (ERRLOG2_BASE + 103)
NELOG_NetlogonInvalidDwordParameterValue equ (ERRLOG2_BASE + 104)
NELOG_NetlogonServerAuthFailedNoAccount equ (ERRLOG2_BASE + 105)
NELOG_NetlogonNoDynamicDnsManual equ (ERRLOG2_BASE + 106)
NELOG_NetlogonNoSiteForClients equ (ERRLOG2_BASE + 107)
NELOG_NetlogonDnsDeregAborted equ (ERRLOG2_BASE + 108)
NELOG_NetlogonRpcPortRequestFailure equ (ERRLOG2_BASE + 109)
NELOG_NetlogonPartialSiteMappingForClients equ (ERRLOG2_BASE + 110)
NELOG_NetlogonRemoteDynamicDnsRegisterFailure equ (ERRLOG2_BASE + 111)
NELOG_NetlogonRemoteDynamicDnsDeregisterFailure equ (ERRLOG2_BASE + 112)
NELOG_NetlogonRejectedRemoteDynamicDnsRegister equ (ERRLOG2_BASE + 113)
NELOG_NetlogonRejectedRemoteDynamicDnsDeregister equ (ERRLOG2_BASE + 114)
NELOG_NetlogonRemoteDynamicDnsUpdateRequestFailure equ (ERRLOG2_BASE + 115)

endif
