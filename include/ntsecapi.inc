include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifdef DEFINE_GUID

if not defined(INITGUID) or not defined(Audit_System_SecurityStateChange_defined)
DEFINE_GUID( Audit_System_SecurityStateChange, 0x0cce9210, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_System_SecurityStateChange_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_System_SecuritySubsystemExtension_defined)
DEFINE_GUID( Audit_System_SecuritySubsystemExtension, 0x0cce9211, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_System_SecuritySubsystemExtension_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_System_Integrity_defined)
DEFINE_GUID( Audit_System_Integrity, 0x0cce9212, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_System_Integrity_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_System_IPSecDriverEvents_defined)
DEFINE_GUID( Audit_System_IPSecDriverEvents, 0x0cce9213, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_System_IPSecDriverEvents_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_System_Others_defined)
DEFINE_GUID( Audit_System_Others, 0x0cce9214, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_System_Others_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_Logon_defined)
DEFINE_GUID( Audit_Logon_Logon, 0x0cce9215, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_Logon_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_Logoff_defined)
DEFINE_GUID( Audit_Logon_Logoff, 0x0cce9216, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_Logoff_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_AccountLockout_defined)
DEFINE_GUID( Audit_Logon_AccountLockout, 0x0cce9217, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_AccountLockout_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_IPSecMainMode_defined)
DEFINE_GUID( Audit_Logon_IPSecMainMode, 0x0cce9218, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_IPSecMainMode_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_IPSecQuickMode_defined)
DEFINE_GUID( Audit_Logon_IPSecQuickMode, 0x0cce9219, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_IPSecQuickMode_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_IPSecUserMode_defined)
DEFINE_GUID( Audit_Logon_IPSecUserMode, 0x0cce921a, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_IPSecUserMode_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_SpecialLogon_defined)
DEFINE_GUID( Audit_Logon_SpecialLogon, 0x0cce921b, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_SpecialLogon_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_Others_defined)
DEFINE_GUID( Audit_Logon_Others, 0x0cce921c, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_Others_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_FileSystem_defined)
DEFINE_GUID( Audit_ObjectAccess_FileSystem, 0x0cce921d, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_FileSystem_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_Registry_defined)
DEFINE_GUID( Audit_ObjectAccess_Registry, 0x0cce921e, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_Registry_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_Kernel_defined)
DEFINE_GUID( Audit_ObjectAccess_Kernel, 0x0cce921f, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_Kernel_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_Sam_defined)
DEFINE_GUID( Audit_ObjectAccess_Sam, 0x0cce9220, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_Sam_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_CertificationServices_defined)
DEFINE_GUID( Audit_ObjectAccess_CertificationServices, 0x0cce9221, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_CertificationServices_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_ApplicationGenerated_defined)
DEFINE_GUID( Audit_ObjectAccess_ApplicationGenerated, 0x0cce9222, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_ApplicationGenerated_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_Handle_defined)
DEFINE_GUID( Audit_ObjectAccess_Handle, 0x0cce9223, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_Handle_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_Share_defined)
DEFINE_GUID( Audit_ObjectAccess_Share, 0x0cce9224, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_Share_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_FirewallPacketDrops_defined)
DEFINE_GUID( Audit_ObjectAccess_FirewallPacketDrops, 0x0cce9225, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_FirewallPacketDrops_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_FirewallConnection_defined)
DEFINE_GUID( Audit_ObjectAccess_FirewallConnection, 0x0cce9226, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_FirewallConnection_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_Other_defined)
DEFINE_GUID( Audit_ObjectAccess_Other, 0x0cce9227, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_Other_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PrivilegeUse_Sensitive_defined)
DEFINE_GUID( Audit_PrivilegeUse_Sensitive, 0x0cce9228, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PrivilegeUse_Sensitive_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PrivilegeUse_NonSensitive_defined)
DEFINE_GUID( Audit_PrivilegeUse_NonSensitive, 0x0cce9229, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PrivilegeUse_NonSensitive_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PrivilegeUse_Others_defined)
DEFINE_GUID( Audit_PrivilegeUse_Others, 0x0cce922a, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PrivilegeUse_Others_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DetailedTracking_ProcessCreation_defined)
DEFINE_GUID( Audit_DetailedTracking_ProcessCreation, 0x0cce922b, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DetailedTracking_ProcessCreation_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DetailedTracking_ProcessTermination_defined)
DEFINE_GUID( Audit_DetailedTracking_ProcessTermination, 0x0cce922c, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DetailedTracking_ProcessTermination_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DetailedTracking_DpapiActivity_defined)
DEFINE_GUID( Audit_DetailedTracking_DpapiActivity, 0x0cce922d, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DetailedTracking_DpapiActivity_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DetailedTracking_RpcCall_defined)
DEFINE_GUID( Audit_DetailedTracking_RpcCall, 0x0cce922e, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DetailedTracking_RpcCall_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PolicyChange_AuditPolicy_defined)
DEFINE_GUID( Audit_PolicyChange_AuditPolicy, 0x0cce922f, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PolicyChange_AuditPolicy_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PolicyChange_AuthenticationPolicy_defined)
DEFINE_GUID( Audit_PolicyChange_AuthenticationPolicy, 0x0cce9230, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PolicyChange_AuthenticationPolicy_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PolicyChange_AuthorizationPolicy_defined)
DEFINE_GUID( Audit_PolicyChange_AuthorizationPolicy, 0x0cce9231, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PolicyChange_AuthorizationPolicy_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PolicyChange_MpsscvRulePolicy_defined)
DEFINE_GUID( Audit_PolicyChange_MpsscvRulePolicy, 0x0cce9232, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PolicyChange_MpsscvRulePolicy_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PolicyChange_WfpIPSecPolicy_defined)
DEFINE_GUID( Audit_PolicyChange_WfpIPSecPolicy, 0x0cce9233, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PolicyChange_WfpIPSecPolicy_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PolicyChange_Others_defined)
DEFINE_GUID( Audit_PolicyChange_Others, 0x0cce9234, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PolicyChange_Others_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountManagement_UserAccount_defined)
DEFINE_GUID( Audit_AccountManagement_UserAccount, 0x0cce9235, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountManagement_UserAccount_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountManagement_ComputerAccount_defined)
DEFINE_GUID( Audit_AccountManagement_ComputerAccount, 0x0cce9236, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountManagement_ComputerAccount_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountManagement_SecurityGroup_defined)
DEFINE_GUID( Audit_AccountManagement_SecurityGroup, 0x0cce9237, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountManagement_SecurityGroup_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountManagement_DistributionGroup_defined)
DEFINE_GUID( Audit_AccountManagement_DistributionGroup, 0x0cce9238, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountManagement_DistributionGroup_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountManagement_ApplicationGroup_defined)
DEFINE_GUID( Audit_AccountManagement_ApplicationGroup, 0x0cce9239, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountManagement_ApplicationGroup_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountManagement_Others_defined)
DEFINE_GUID( Audit_AccountManagement_Others, 0x0cce923a, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountManagement_Others_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DSAccess_DSAccess_defined)
DEFINE_GUID( Audit_DSAccess_DSAccess, 0x0cce923b, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DSAccess_DSAccess_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DsAccess_AdAuditChanges_defined)
DEFINE_GUID( Audit_DsAccess_AdAuditChanges, 0x0cce923c, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DsAccess_AdAuditChanges_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Ds_Replication_defined)
DEFINE_GUID( Audit_Ds_Replication, 0x0cce923d, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Ds_Replication_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Ds_DetailedReplication_defined)
DEFINE_GUID( Audit_Ds_DetailedReplication, 0x0cce923e, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Ds_DetailedReplication_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountLogon_CredentialValidation_defined)
DEFINE_GUID( Audit_AccountLogon_CredentialValidation, 0x0cce923f, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountLogon_CredentialValidation_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountLogon_Kerberos_defined)
DEFINE_GUID( Audit_AccountLogon_Kerberos, 0x0cce9240, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountLogon_Kerberos_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountLogon_Others_defined)
DEFINE_GUID( Audit_AccountLogon_Others, 0x0cce9241, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountLogon_Others_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountLogon_KerbCredentialValidation_defined)
DEFINE_GUID( Audit_AccountLogon_KerbCredentialValidation, 0x0cce9242, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountLogon_KerbCredentialValidation_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_NPS_defined)
DEFINE_GUID( Audit_Logon_NPS, 0x0cce9243, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_NPS_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_DetailedFileShare_defined)
DEFINE_GUID( Audit_ObjectAccess_DetailedFileShare, 0x0cce9244, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_DetailedFileShare_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_RemovableStorage_defined)
DEFINE_GUID( Audit_ObjectAccess_RemovableStorage, 0x0cce9245, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_RemovableStorage_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_CbacStaging_defined)
DEFINE_GUID( Audit_ObjectAccess_CbacStaging, 0x0cce9246, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_CbacStaging_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_Claims_defined)
DEFINE_GUID( Audit_Logon_Claims, 0x0cce9247, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_Claims_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DetailedTracking_PnpActivity_defined)
DEFINE_GUID( Audit_DetailedTracking_PnpActivity, 0x0cce9248, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DetailedTracking_PnpActivity_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_Groups_defined)
DEFINE_GUID( Audit_Logon_Groups, 0x0cce9249, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_Groups_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DetailedTracking_TokenRightAdjusted_defined)
DEFINE_GUID( Audit_DetailedTracking_TokenRightAdjusted, 0x0cce924a, 0x69ae, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DetailedTracking_TokenRightAdjusted_defined
endif
endif

endif

ifdef DEFINE_GUID

if not defined(INITGUID) or not defined(Audit_System_defined)
DEFINE_GUID( Audit_System, 0x69979848, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_System_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_Logon_defined)
DEFINE_GUID( Audit_Logon, 0x69979849, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_Logon_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_ObjectAccess_defined)
DEFINE_GUID( Audit_ObjectAccess, 0x6997984a, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_ObjectAccess_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PrivilegeUse_defined)
DEFINE_GUID( Audit_PrivilegeUse, 0x6997984b, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PrivilegeUse_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DetailedTracking_defined)
DEFINE_GUID( Audit_DetailedTracking, 0x6997984c, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DetailedTracking_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_PolicyChange_defined)
DEFINE_GUID( Audit_PolicyChange, 0x6997984d, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_PolicyChange_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountManagement_defined)
DEFINE_GUID( Audit_AccountManagement, 0x6997984e, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountManagement_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_DirectoryServiceAccess_defined)
DEFINE_GUID( Audit_DirectoryServiceAccess, 0x6997984f, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_DirectoryServiceAccess_defined
endif
endif

if not defined(INITGUID) or not defined(Audit_AccountLogon_defined)
DEFINE_GUID( Audit_AccountLogon, 0x69979850, 0x797a, 0x11d9, 0xbe, 0xd3, 0x50, 0x50, 0x54, 0x50, 0x30, 0x30 )
ifdef INITGUID
define Audit_AccountLogon_defined
endif
endif

endif

ifndef _NTSECAPI_
define _NTSECAPI_

ifndef _NTDEF_
PNTSTATUS               typedef ptr NTSTATUS
endif

include lsalookup.inc

ifndef _NTLSA_IFS_
PLSA_OPERATIONAL_MODE   typedef ptr LSA_OPERATIONAL_MODE
endif

define LSA_MODE_PASSWORD_PROTECTED     (0x00000001)
define LSA_MODE_INDIVIDUAL_ACCOUNTS    (0x00000002)
define LSA_MODE_MANDATORY_ACCESS       (0x00000004)
define LSA_MODE_LOG_FULL               (0x00000008)

ifndef _NTLSA_IFS_

.enum SECURITY_LOGON_TYPE {
    UndefinedLogonType = 0,
    Interactive = 2,
    Network,
    Batch,
    Service,
    Proxy,
    Unlock,
    NetworkCleartext,
    NewCredentials,
if (_WIN32_WINNT ge 0x0501)
    RemoteInteractive,
    CachedInteractive,
endif
if (_WIN32_WINNT ge 0x0502)
    CachedRemoteInteractive,
    CachedUnlock
endif
    }

endif

ifndef _NTLSA_IFS_

ifndef _NTLSA_AUDIT_
define _NTLSA_AUDIT_

.enum SE_ADT_PARAMETER_TYPE {
    SeAdtParmTypeNone = 0,
    SeAdtParmTypeString,
    SeAdtParmTypeFileSpec,
    SeAdtParmTypeUlong,
    SeAdtParmTypeSid,
    SeAdtParmTypeLogonId,
    SeAdtParmTypeNoLogonId,
    SeAdtParmTypeAccessMask,
    SeAdtParmTypePrivs,
    SeAdtParmTypeObjectTypes,
    SeAdtParmTypeHexUlong,
    SeAdtParmTypePtr,
    SeAdtParmTypeTime,
    SeAdtParmTypeGuid,
    SeAdtParmTypeLuid,
    SeAdtParmTypeHexInt64,
    SeAdtParmTypeStringList,
    SeAdtParmTypeSidList,
    SeAdtParmTypeDuration,
    SeAdtParmTypeUserAccountControl,
    SeAdtParmTypeNoUac,
    SeAdtParmTypeMessage,
    SeAdtParmTypeDateTime,
    SeAdtParmTypeSockAddr,
    SeAdtParmTypeSD,
    SeAdtParmTypeLogonHours,
    SeAdtParmTypeLogonIdNoSid,
    SeAdtParmTypeUlongNoConv,
    SeAdtParmTypeSockAddrNoPort,
    SeAdtParmTypeAccessReason,
    SeAdtParmTypeStagingReason,
    SeAdtParmTypeResourceAttribute,
    SeAdtParmTypeClaims,
    SeAdtParmTypeLogonIdAsSid,
    SeAdtParmTypeMultiSzString,
    SeAdtParmTypeLogonIdEx,
    }

ifndef GUID_DEFINED
include guiddef.inc
endif

SE_ADT_OBJECT_TYPE      struct
ObjectType              GUID <>
Flags                   USHORT ?
define SE_ADT_OBJECT_ONLY 0x1
Level                   USHORT ?
AccessMask              ACCESS_MASK ?
SE_ADT_OBJECT_TYPE      ends
PSE_ADT_OBJECT_TYPE     typedef ptr SE_ADT_OBJECT_TYPE

SE_ADT_PARAMETER_ARRAY_ENTRY struct
Type                    SE_ADT_PARAMETER_TYPE ?
Length                  ULONG ?
Data                    ULONG_PTR 2 dup(?)
Address                 PVOID ?
SE_ADT_PARAMETER_ARRAY_ENTRY ends
PSE_ADT_PARAMETER_ARRAY_ENTRY typedef ptr SE_ADT_PARAMETER_ARRAY_ENTRY

SE_ADT_ACCESS_REASON    struct
AccessMask              ACCESS_MASK ?
AccessReasons           ULONG 32 dup(?)
ObjectTypeIndex         ULONG ?
AccessGranted           ULONG ?
SecurityDescriptor      PSECURITY_DESCRIPTOR ?
SE_ADT_ACCESS_REASON    ends
PSE_ADT_ACCESS_REASON   typedef ptr SE_ADT_ACCESS_REASON

SE_ADT_CLAIMS           struct
Length                  ULONG ?
Claims                  PCLAIMS_BLOB ?
SE_ADT_CLAIMS           ends
PSE_ADT_CLAIMS          typedef ptr SE_ADT_CLAIMS

define SE_MAX_AUDIT_PARAMETERS 32
define SE_MAX_GENERIC_AUDIT_PARAMETERS 28

SE_ADT_PARAMETER_ARRAY  struct
CategoryId              ULONG ?
AuditId                 ULONG ?
ParameterCount          ULONG ?
Length                  ULONG ?
FlatSubCategoryId       USHORT ?
Type                    USHORT ?
Flags                   ULONG ?
Parameters              SE_ADT_PARAMETER_ARRAY_ENTRY SE_MAX_AUDIT_PARAMETERS dup(<>)
SE_ADT_PARAMETER_ARRAY  ends
PSE_ADT_PARAMETER_ARRAY typedef ptr SE_ADT_PARAMETER_ARRAY

SE_ADT_PARAMETER_ARRAY_EX struct
CategoryId              ULONG ?
AuditId                 ULONG ?
Version                 ULONG ?
ParameterCount          ULONG ?
Length                  ULONG ?
FlatSubCategoryId       USHORT ?
Type                    USHORT ?
Flags                   ULONG ?
Parameters              SE_ADT_PARAMETER_ARRAY_ENTRY SE_MAX_AUDIT_PARAMETERS dup(<>)
SE_ADT_PARAMETER_ARRAY_EX ends
PSE_ADT_PARAMETER_ARRAY_EX typedef ptr SE_ADT_PARAMETER_ARRAY_EX

define SE_ADT_PARAMETERS_SELF_RELATIVE     0x00000001
define SE_ADT_PARAMETERS_SEND_TO_LSA       0x00000002
define SE_ADT_PARAMETER_EXTENSIBLE_AUDIT   0x00000004
define SE_ADT_PARAMETER_GENERIC_AUDIT      0x00000008
define SE_ADT_PARAMETER_WRITE_SYNCHRONOUS  0x00000010

LSAP_SE_ADT_PARAMETER_ARRAY_TRUE_SIZE macro AuditParameters
  exitm<( sizeof(SE_ADT_PARAMETER_ARRAY) - sizeof(SE_ADT_PARAMETER_ARRAY_ENTRY) * (SE_MAX_AUDIT_PARAMETERS - AuditParameters.ParameterCount) )>
  endm

endif

endif

.enum POLICY_AUDIT_EVENT_TYPE {
    AuditCategorySystem = 0,
    AuditCategoryLogon,
    AuditCategoryObjectAccess,
    AuditCategoryPrivilegeUse,
    AuditCategoryDetailedTracking,
    AuditCategoryPolicyChange,
    AuditCategoryAccountManagement,
    AuditCategoryDirectoryServiceAccess,
    AuditCategoryAccountLogon
    }
PPOLICY_AUDIT_EVENT_TYPE typedef ptr POLICY_AUDIT_EVENT_TYPE

define POLICY_AUDIT_EVENT_UNCHANGED       (0x00000000)
define POLICY_AUDIT_EVENT_SUCCESS         (0x00000001)
define POLICY_AUDIT_EVENT_FAILURE         (0x00000002)
define POLICY_AUDIT_EVENT_NONE            (0x00000004)
define POLICY_AUDIT_EVENT_MASK (POLICY_AUDIT_EVENT_SUCCESS or POLICY_AUDIT_EVENT_FAILURE or POLICY_AUDIT_EVENT_UNCHANGED or POLICY_AUDIT_EVENT_NONE)

LSA_SUCCESS macro Error
  exitm<((Error) !>= 0)>
  endm

ifndef _NTLSA_IFS_

LsaRegisterLogonProcess proto WINAPI :PLSA_STRING, :PHANDLE, :PLSA_OPERATIONAL_MODE
LsaLogonUser proto WINAPI :HANDLE, :PLSA_STRING, :SECURITY_LOGON_TYPE, :ULONG, :PVOID, :ULONG, :PTOKEN_GROUPS, :PTOKEN_SOURCE, :ptr, :PULONG, :PLUID, :PHANDLE, :PQUOTA_LIMITS, :PNTSTATUS
LsaLookupAuthenticationPackage proto WINAPI :HANDLE, :PLSA_STRING, :PULONG
LsaFreeReturnBuffer proto WINAPI :PVOID
LsaCallAuthenticationPackage proto WINAPI :HANDLE, :ULONG, :PVOID, :ULONG, :ptr, :PULONG, :PNTSTATUS
LsaDeregisterLogonProcess proto WINAPI :HANDLE
LsaConnectUntrusted proto WINAPI :PHANDLE
LsaInsertProtectedProcessAddress proto WINAPI :PVOID, :ULONG
LsaRemoveProtectedProcessAddress proto WINAPI :PVOID, :ULONG

endif

define POLICY_VIEW_LOCAL_INFORMATION              0x00000001
define POLICY_VIEW_AUDIT_INFORMATION              0x00000002
define POLICY_GET_PRIVATE_INFORMATION             0x00000004
define POLICY_TRUST_ADMIN                         0x00000008
define POLICY_CREATE_ACCOUNT                      0x00000010
define POLICY_CREATE_SECRET                       0x00000020
define POLICY_CREATE_PRIVILEGE                    0x00000040
define POLICY_SET_DEFAULT_QUOTA_LIMITS            0x00000080
define POLICY_SET_AUDIT_REQUIREMENTS              0x00000100
define POLICY_AUDIT_LOG_ADMIN                     0x00000200
define POLICY_SERVER_ADMIN                        0x00000400
define POLICY_LOOKUP_NAMES                        0x00000800
define POLICY_NOTIFICATION                        0x00001000

define POLICY_ALL_ACCESS     (STANDARD_RIGHTS_REQUIRED or POLICY_VIEW_LOCAL_INFORMATION or POLICY_VIEW_AUDIT_INFORMATION or POLICY_GET_PRIVATE_INFORMATION or POLICY_TRUST_ADMIN or POLICY_CREATE_ACCOUNT or POLICY_CREATE_SECRET or POLICY_CREATE_PRIVILEGE or POLICY_SET_DEFAULT_QUOTA_LIMITS or POLICY_SET_AUDIT_REQUIREMENTS or POLICY_AUDIT_LOG_ADMIN or POLICY_SERVER_ADMIN or POLICY_LOOKUP_NAMES)
define POLICY_READ           (STANDARD_RIGHTS_READ or POLICY_VIEW_AUDIT_INFORMATION or POLICY_GET_PRIVATE_INFORMATION)
define POLICY_WRITE          (STANDARD_RIGHTS_WRITE or POLICY_TRUST_ADMIN or POLICY_CREATE_ACCOUNT or POLICY_CREATE_SECRET or POLICY_CREATE_PRIVILEGE or POLICY_SET_DEFAULT_QUOTA_LIMITS or POLICY_SET_AUDIT_REQUIREMENTS or POLICY_AUDIT_LOG_ADMIN or POLICY_SERVER_ADMIN)
define POLICY_EXECUTE        (STANDARD_RIGHTS_EXECUTE or POLICY_VIEW_LOCAL_INFORMATION or POLICY_LOOKUP_NAMES)

LSA_TRANSLATED_SID      struct
Use                     SID_NAME_USE ?
RelativeId              ULONG ?
DomainIndex             LONG ?
LSA_TRANSLATED_SID      ends
PLSA_TRANSLATED_SID     typedef ptr LSA_TRANSLATED_SID

.enum POLICY_LSA_SERVER_ROLE {
    PolicyServerRoleBackup = 2,
    PolicyServerRolePrimary
    }

if (_WIN32_WINNT lt 0x0502)
.enum POLICY_SERVER_ENABLE_STATE {
    PolicyServerEnabled = 2,
    PolicyServerDisabled
    }
endif

PPOLICY_AUDIT_EVENT_OPTIONS typedef ptr POLICY_AUDIT_EVENT_OPTIONS

.enum POLICY_INFORMATION_CLASS {
    PolicyAuditLogInformation = 1,
    PolicyAuditEventsInformation,
    PolicyPrimaryDomainInformation,
    PolicyPdAccountInformation,
    PolicyAccountDomainInformation,
    PolicyLsaServerRoleInformation,
    PolicyReplicaSourceInformation,
    PolicyDefaultQuotaInformation,
    PolicyModificationInformation,
    PolicyAuditFullSetInformation,
    PolicyAuditFullQueryInformation,
    PolicyDnsDomainInformation,
    PolicyDnsDomainInformationInt,
    PolicyLocalAccountDomainInformation,
    PolicyMachineAccountInformation,
    PolicyLastEntry
    }

POLICY_AUDIT_LOG_INFO   struct
AuditLogPercentFull     ULONG ?
MaximumLogSize          ULONG ?
AuditRetentionPeriod    LARGE_INTEGER <>
AuditLogFullShutdownInProgress BOOLEAN ?
TimeToShutdown          LARGE_INTEGER <>
NextAuditRecordId       ULONG ?
POLICY_AUDIT_LOG_INFO   ends
PPOLICY_AUDIT_LOG_INFO  typedef ptr POLICY_AUDIT_LOG_INFO

POLICY_AUDIT_EVENTS_INFO struct
AuditingMode            BOOLEAN ?
EventAuditingOptions    PPOLICY_AUDIT_EVENT_OPTIONS ?
MaximumAuditEventCount  ULONG ?
POLICY_AUDIT_EVENTS_INFO ends
PPOLICY_AUDIT_EVENTS_INFO typedef ptr POLICY_AUDIT_EVENTS_INFO

POLICY_AUDIT_SUBCATEGORIES_INFO struct
MaximumSubCategoryCount ULONG ?
EventAuditingOptions    PPOLICY_AUDIT_EVENT_OPTIONS ?
POLICY_AUDIT_SUBCATEGORIES_INFO ends
PPOLICY_AUDIT_SUBCATEGORIES_INFO typedef ptr POLICY_AUDIT_SUBCATEGORIES_INFO

POLICY_AUDIT_CATEGORIES_INFO struct
MaximumCategoryCount    ULONG ?
SubCategoriesInfo       PPOLICY_AUDIT_SUBCATEGORIES_INFO ?
POLICY_AUDIT_CATEGORIES_INFO ends
PPOLICY_AUDIT_CATEGORIES_INFO typedef ptr POLICY_AUDIT_CATEGORIES_INFO

define PER_USER_POLICY_UNCHANGED               (0x00)
define PER_USER_AUDIT_SUCCESS_INCLUDE          (0x01)
define PER_USER_AUDIT_SUCCESS_EXCLUDE          (0x02)
define PER_USER_AUDIT_FAILURE_INCLUDE          (0x04)
define PER_USER_AUDIT_FAILURE_EXCLUDE          (0x08)
define PER_USER_AUDIT_NONE                     (0x10)

define VALID_PER_USER_AUDIT_POLICY_FLAG (PER_USER_AUDIT_SUCCESS_INCLUDE or PER_USER_AUDIT_SUCCESS_EXCLUDE or PER_USER_AUDIT_FAILURE_INCLUDE or PER_USER_AUDIT_FAILURE_EXCLUDE or PER_USER_AUDIT_NONE)

POLICY_PRIMARY_DOMAIN_INFO struct
Name                    LSA_UNICODE_STRING <>
Sid                     PSID ?
POLICY_PRIMARY_DOMAIN_INFO ends
PPOLICY_PRIMARY_DOMAIN_INFO typedef ptr POLICY_PRIMARY_DOMAIN_INFO

POLICY_PD_ACCOUNT_INFO  struct
Name                    LSA_UNICODE_STRING <>
POLICY_PD_ACCOUNT_INFO  ends
PPOLICY_PD_ACCOUNT_INFO typedef ptr POLICY_PD_ACCOUNT_INFO

POLICY_LSA_SERVER_ROLE_INFO struct
LsaServerRole           POLICY_LSA_SERVER_ROLE ?
POLICY_LSA_SERVER_ROLE_INFO ends
PPOLICY_LSA_SERVER_ROLE_INFO typedef ptr POLICY_LSA_SERVER_ROLE_INFO

POLICY_REPLICA_SOURCE_INFO struct
ReplicaSource           LSA_UNICODE_STRING <>
ReplicaAccountName      LSA_UNICODE_STRING <>
POLICY_REPLICA_SOURCE_INFO ends
PPOLICY_REPLICA_SOURCE_INFO typedef ptr POLICY_REPLICA_SOURCE_INFO

POLICY_DEFAULT_QUOTA_INFO struct
QuotaLimits             QUOTA_LIMITS <>
POLICY_DEFAULT_QUOTA_INFO ends
PPOLICY_DEFAULT_QUOTA_INFO typedef ptr POLICY_DEFAULT_QUOTA_INFO

POLICY_MODIFICATION_INFO struct
ModifiedId              LARGE_INTEGER <>
DatabaseCreationTime    LARGE_INTEGER <>
POLICY_MODIFICATION_INFO ends
PPOLICY_MODIFICATION_INFO typedef ptr POLICY_MODIFICATION_INFO

POLICY_AUDIT_FULL_SET_INFO struct
ShutDownOnFull          BOOLEAN ?
POLICY_AUDIT_FULL_SET_INFO ends
PPOLICY_AUDIT_FULL_SET_INFO typedef ptr POLICY_AUDIT_FULL_SET_INFO

POLICY_AUDIT_FULL_QUERY_INFO struct
ShutDownOnFull          BOOLEAN ?
LogIsFull               BOOLEAN ?
POLICY_AUDIT_FULL_QUERY_INFO ends
PPOLICY_AUDIT_FULL_QUERY_INFO typedef ptr POLICY_AUDIT_FULL_QUERY_INFO

.enum POLICY_DOMAIN_INFORMATION_CLASS {
if (_WIN32_WINNT le 0x0500)
    PolicyDomainQualityOfServiceInformation = 1,
endif
    PolicyDomainEfsInformation = 2,
    PolicyDomainKerberosTicketInformation
    }

if (_WIN32_WINNT lt 0x0502)

define POLICY_QOS_SCHANNEL_REQUIRED            0x00000001
define POLICY_QOS_OUTBOUND_INTEGRITY           0x00000002
define POLICY_QOS_OUTBOUND_CONFIDENTIALITY     0x00000004
define POLICY_QOS_INBOUND_INTEGRITY            0x00000008
define POLICY_QOS_INBOUND_CONFIDENTIALITY      0x00000010
define POLICY_QOS_ALLOW_LOCAL_ROOT_CERT_STORE  0x00000020
define POLICY_QOS_RAS_SERVER_ALLOWED           0x00000040
define POLICY_QOS_DHCP_SERVER_ALLOWED          0x00000080

endif

if (_WIN32_WINNT eq 0x0500)
POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO struct
QualityOfService        ULONG ?
POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO ends
PPOLICY_DOMAIN_QUALITY_OF_SERVICE_INFO typedef ptr POLICY_DOMAIN_QUALITY_OF_SERVICE_INFO
endif

POLICY_DOMAIN_EFS_INFO  struct
InfoLength              ULONG ?
EfsBlob                 PUCHAR ?
POLICY_DOMAIN_EFS_INFO  ends
PPOLICY_DOMAIN_EFS_INFO typedef ptr POLICY_DOMAIN_EFS_INFO

define POLICY_KERBEROS_VALIDATE_CLIENT 0x00000080

POLICY_DOMAIN_KERBEROS_TICKET_INFO struct
AuthenticationOptions   ULONG ?
MaxServiceTicketAge     LARGE_INTEGER <>
MaxTicketAge            LARGE_INTEGER <>
MaxRenewAge             LARGE_INTEGER <>
MaxClockSkew            LARGE_INTEGER <>
Reserved                LARGE_INTEGER <>
POLICY_DOMAIN_KERBEROS_TICKET_INFO ends
PPOLICY_DOMAIN_KERBEROS_TICKET_INFO typedef ptr POLICY_DOMAIN_KERBEROS_TICKET_INFO

POLICY_MACHINE_ACCT_INFO struct
Rid                     ULONG ?
Sid                     PSID ?
POLICY_MACHINE_ACCT_INFO ends
PPOLICY_MACHINE_ACCT_INFO typedef ptr POLICY_MACHINE_ACCT_INFO

.enum POLICY_NOTIFICATION_INFORMATION_CLASS {
    PolicyNotifyAuditEventsInformation = 1,
    PolicyNotifyAccountDomainInformation,
    PolicyNotifyServerRoleInformation,
    PolicyNotifyDnsDomainInformation,
    PolicyNotifyDomainEfsInformation,
    PolicyNotifyDomainKerberosTicketInformation,
    PolicyNotifyMachineAccountPasswordInformation,
    PolicyNotifyGlobalSaclInformation,
    PolicyNotifyMax
    }

PLSA_HANDLE             typedef ptr LSA_HANDLE

.enum TRUSTED_INFORMATION_CLASS {
    TrustedDomainNameInformation = 1,
    TrustedControllersInformation,
    TrustedPosixOffsetInformation,
    TrustedPasswordInformation,
    TrustedDomainInformationBasic,
    TrustedDomainInformationEx,
    TrustedDomainAuthInformation,
    TrustedDomainFullInformation,
    TrustedDomainAuthInformationInternal,
    TrustedDomainFullInformationInternal,
    TrustedDomainInformationEx2Internal,
    TrustedDomainFullInformation2Internal,
    TrustedDomainSupportedEncryptionTypes,
    }

TRUSTED_DOMAIN_NAME_INFO struct
Name                    LSA_UNICODE_STRING <>
TRUSTED_DOMAIN_NAME_INFO ends
PTRUSTED_DOMAIN_NAME_INFO typedef ptr TRUSTED_DOMAIN_NAME_INFO

TRUSTED_CONTROLLERS_INFO struct
Entries                 ULONG ?
Names                   PLSA_UNICODE_STRING ?
TRUSTED_CONTROLLERS_INFO ends
PTRUSTED_CONTROLLERS_INFO typedef ptr TRUSTED_CONTROLLERS_INFO

TRUSTED_POSIX_OFFSET_INFO struct
Offs                    ULONG ?
TRUSTED_POSIX_OFFSET_INFO ends
PTRUSTED_POSIX_OFFSET_INFO typedef ptr TRUSTED_POSIX_OFFSET_INFO

TRUSTED_PASSWORD_INFO   struct
Password                LSA_UNICODE_STRING <>
OldPassword             LSA_UNICODE_STRING <>
TRUSTED_PASSWORD_INFO   ends
PTRUSTED_PASSWORD_INFO  typedef ptr TRUSTED_PASSWORD_INFO

TRUSTED_DOMAIN_INFORMATION_BASIC typedef LSA_TRUST_INFORMATION
PTRUSTED_DOMAIN_INFORMATION_BASIC typedef PLSA_TRUST_INFORMATION

define TRUST_DIRECTION_DISABLED        0x00000000
define TRUST_DIRECTION_INBOUND         0x00000001
define TRUST_DIRECTION_OUTBOUND        0x00000002
define TRUST_DIRECTION_BIDIRECTIONAL   (TRUST_DIRECTION_INBOUND or TRUST_DIRECTION_OUTBOUND)

define TRUST_TYPE_DOWNLEVEL            0x00000001
define TRUST_TYPE_UPLEVEL              0x00000002
define TRUST_TYPE_MIT                  0x00000003

if (_WIN32_WINNT lt 0x0502)
define TRUST_TYPE_DCE                  0x00000004
endif

define TRUST_ATTRIBUTE_NON_TRANSITIVE                0x00000001
define TRUST_ATTRIBUTE_UPLEVEL_ONLY                  0x00000002
if (_WIN32_WINNT eq 0x0500)
define TRUST_ATTRIBUTE_TREE_PARENT     0x00400000
define TRUST_ATTRIBUTE_TREE_ROOT       0x00800000
define TRUST_ATTRIBUTES_VALID  0xFF02FFFF
endif

if (_WIN32_WINNT lt 0x0502)
define TRUST_ATTRIBUTE_FILTER_SIDS        0x00000004
else
define TRUST_ATTRIBUTE_QUARANTINED_DOMAIN            0x00000004
endif

if (_WIN32_WINNT ge 0x0501)
define TRUST_ATTRIBUTE_FOREST_TRANSITIVE             0x00000008
if (_WIN32_WINNT ge 0x0502)
define TRUST_ATTRIBUTE_CROSS_ORGANIZATION            0x00000010
define TRUST_ATTRIBUTE_WITHIN_FOREST                 0x00000020
define TRUST_ATTRIBUTE_TREAT_AS_EXTERNAL             0x00000040
if (_WIN32_WINNT ge 0x0600)
define TRUST_ATTRIBUTE_TRUST_USES_RC4_ENCRYPTION     0x00000080
define TRUST_ATTRIBUTE_TRUST_USES_AES_KEYS           0x00000100
endif
if (_WIN32_WINNT ge 0x0602)
define TRUST_ATTRIBUTE_CROSS_ORGANIZATION_NO_TGT_DELEGATION 0x00000200
define TRUST_ATTRIBUTE_PIM_TRUST                     0x00000400
endif
if (_WIN32_WINNT ge 0x0603)
define TRUST_ATTRIBUTE_CROSS_ORGANIZATION_ENABLE_TGT_DELEGATION 0x00000800
endif
else
endif
define TRUST_ATTRIBUTES_VALID          0xFF03FFFF
endif
define TRUST_ATTRIBUTES_USER           0xFF000000

TRUSTED_DOMAIN_INFORMATION_EX struct
Name                    LSA_UNICODE_STRING <>
FlatName                LSA_UNICODE_STRING <>
Sid                     PSID ?
TrustDirection          ULONG ?
TrustType               ULONG ?
TrustAttributes         ULONG ?
TRUSTED_DOMAIN_INFORMATION_EX ends
PTRUSTED_DOMAIN_INFORMATION_EX typedef ptr TRUSTED_DOMAIN_INFORMATION_EX

TRUSTED_DOMAIN_INFORMATION_EX2 struct
Name                    LSA_UNICODE_STRING <>
FlatName                LSA_UNICODE_STRING <>
Sid                     PSID ?
TrustDirection          ULONG ?
TrustType               ULONG ?
TrustAttributes         ULONG ?
ForestTrustLength       ULONG ?
ForestTrustInfo         PUCHAR ?
TRUSTED_DOMAIN_INFORMATION_EX2 ends
PTRUSTED_DOMAIN_INFORMATION_EX2 typedef ptr TRUSTED_DOMAIN_INFORMATION_EX2

define TRUST_AUTH_TYPE_NONE    0
define TRUST_AUTH_TYPE_NT4OWF  1
define TRUST_AUTH_TYPE_CLEAR   2
define TRUST_AUTH_TYPE_VERSION 3

LSA_AUTH_INFORMATION    struct
LastUpdateTime          LARGE_INTEGER <>
AuthType                ULONG ?
AuthInfoLength          ULONG ?
AuthInfo                PUCHAR ?
LSA_AUTH_INFORMATION    ends
PLSA_AUTH_INFORMATION   typedef ptr LSA_AUTH_INFORMATION

TRUSTED_DOMAIN_AUTH_INFORMATION struct
IncomingAuthInfos       ULONG ?
IncomingAuthenticationInformation PLSA_AUTH_INFORMATION ?
IncomingPreviousAuthenticationInformation PLSA_AUTH_INFORMATION ?
OutgoingAuthInfos       ULONG ?
OutgoingAuthenticationInformation PLSA_AUTH_INFORMATION ?
OutgoingPreviousAuthenticationInformation PLSA_AUTH_INFORMATION ?
TRUSTED_DOMAIN_AUTH_INFORMATION ends
PTRUSTED_DOMAIN_AUTH_INFORMATION typedef ptr TRUSTED_DOMAIN_AUTH_INFORMATION

TRUSTED_DOMAIN_FULL_INFORMATION struct
Information             TRUSTED_DOMAIN_INFORMATION_EX <>
PosixOffset             TRUSTED_POSIX_OFFSET_INFO <>
AuthInformation         TRUSTED_DOMAIN_AUTH_INFORMATION <>
TRUSTED_DOMAIN_FULL_INFORMATION ends
PTRUSTED_DOMAIN_FULL_INFORMATION typedef ptr TRUSTED_DOMAIN_FULL_INFORMATION

TRUSTED_DOMAIN_FULL_INFORMATION2 struct
Information             TRUSTED_DOMAIN_INFORMATION_EX2 <>
PosixOffset             TRUSTED_POSIX_OFFSET_INFO <>
AuthInformation         TRUSTED_DOMAIN_AUTH_INFORMATION <>
TRUSTED_DOMAIN_FULL_INFORMATION2 ends
PTRUSTED_DOMAIN_FULL_INFORMATION2 typedef ptr TRUSTED_DOMAIN_FULL_INFORMATION2

TRUSTED_DOMAIN_SUPPORTED_ENCRYPTION_TYPES struct
SupportedEncryptionTypes ULONG ?
TRUSTED_DOMAIN_SUPPORTED_ENCRYPTION_TYPES ends
PTRUSTED_DOMAIN_SUPPORTED_ENCRYPTION_TYPES typedef ptr TRUSTED_DOMAIN_SUPPORTED_ENCRYPTION_TYPES

.enum LSA_FOREST_TRUST_RECORD_TYPE {
    ForestTrustTopLevelName,
    ForestTrustTopLevelNameEx,
    ForestTrustDomainInfo,
    ForestTrustRecordTypeLast = ForestTrustDomainInfo
    }

if (_WIN32_WINNT lt 0x0502)
define LSA_FOREST_TRUST_RECORD_TYPE_UNRECOGNIZED 0x80000000
endif

define LSA_FTRECORD_DISABLED_REASONS            ( 0x0000FFFF )

define LSA_TLN_DISABLED_NEW                     ( 0x00000001 )
define LSA_TLN_DISABLED_ADMIN                   ( 0x00000002 )
define LSA_TLN_DISABLED_CONFLICT                ( 0x00000004 )
define LSA_SID_DISABLED_ADMIN                   ( 0x00000001 )
define LSA_SID_DISABLED_CONFLICT                ( 0x00000002 )
define LSA_NB_DISABLED_ADMIN                    ( 0x00000004 )
define LSA_NB_DISABLED_CONFLICT                 ( 0x00000008 )

LSA_FOREST_TRUST_DOMAIN_INFO struct
ifdef MIDL_PASS
Sid                     PISID ?
else
Sid                     PSID ?
endif
DnsName                 LSA_UNICODE_STRING <>
NetbiosName             LSA_UNICODE_STRING <>
LSA_FOREST_TRUST_DOMAIN_INFO ends
PLSA_FOREST_TRUST_DOMAIN_INFO typedef ptr LSA_FOREST_TRUST_DOMAIN_INFO

if (_WIN32_WINNT ge 0x0502)
define MAX_FOREST_TRUST_BINARY_DATA_SIZE ( 128 * 1024 )
endif

LSA_FOREST_TRUST_BINARY_DATA struct
Length                  ULONG ?
Buffer                  PUCHAR ?
LSA_FOREST_TRUST_BINARY_DATA ends
PLSA_FOREST_TRUST_BINARY_DATA typedef ptr LSA_FOREST_TRUST_BINARY_DATA

LSA_FOREST_TRUST_RECORD struct
Flags                   ULONG ?
ForestTrustType         LSA_FOREST_TRUST_RECORD_TYPE ?
Time                    LARGE_INTEGER <>
TopLevelName            LSA_UNICODE_STRING <>
DomainInfo              LSA_FOREST_TRUST_DOMAIN_INFO <>
Data                    LSA_FOREST_TRUST_BINARY_DATA <>
LSA_FOREST_TRUST_RECORD ends
ForestTrustData         typedef LSA_FOREST_TRUST_RECORD

if (_WIN32_WINNT ge 0x0502)
define MAX_RECORDS_IN_FOREST_TRUST_INFO 4000
endif

LSA_FOREST_TRUST_INFORMATION struct
RecordCount             ULONG ?
Entries                 ptr PLSA_FOREST_TRUST_RECORD ?
LSA_FOREST_TRUST_INFORMATION ends
PLSA_FOREST_TRUST_INFORMATION typedef ptr LSA_FOREST_TRUST_INFORMATION

.enum LSA_FOREST_TRUST_COLLISION_RECORD_TYPE {
    CollisionTdo,
    CollisionXref,
    CollisionOther
    }

LSA_FOREST_TRUST_COLLISION_RECORD struct
Index                   ULONG ?
Type                    LSA_FOREST_TRUST_COLLISION_RECORD_TYPE ?
Flags                   ULONG ?
Name                    LSA_UNICODE_STRING <>
LSA_FOREST_TRUST_COLLISION_RECORD ends
PLSA_FOREST_TRUST_COLLISION_RECORD typedef ptr LSA_FOREST_TRUST_COLLISION_RECORD

LSA_FOREST_TRUST_COLLISION_INFORMATION struct
RecordCount             ULONG ?
Entries                 PLSA_FOREST_TRUST_COLLISION_RECORD ?
LSA_FOREST_TRUST_COLLISION_INFORMATION ends
PLSA_FOREST_TRUST_COLLISION_INFORMATION typedef ptr LSA_FOREST_TRUST_COLLISION_INFORMATION

PLSA_ENUMERATION_HANDLE typedef ptr LSA_ENUMERATION_HANDLE

LSA_ENUMERATION_INFORMATION struct
Sid                     PSID ?
LSA_ENUMERATION_INFORMATION ends
PLSA_ENUMERATION_INFORMATION typedef ptr LSA_ENUMERATION_INFORMATION

LsaFreeMemory proto WINAPI :PVOID
LsaClose proto WINAPI :LSA_HANDLE

if (_WIN32_WINNT ge 0x0600)

LSA_LAST_INTER_LOGON_INFO struct
LastSuccessfulLogon     LARGE_INTEGER <>
LastFailedLogon         LARGE_INTEGER <>
FailedAttemptCountSinceLastSuccessfulLogon ULONG ?
LSA_LAST_INTER_LOGON_INFO ends
PLSA_LAST_INTER_LOGON_INFO typedef ptr LSA_LAST_INTER_LOGON_INFO

endif

if (_WIN32_WINNT ge 0x0501)
SECURITY_LOGON_SESSION_DATA struct
Size                    ULONG ?
LogonId                 LUID <>
UserName                LSA_UNICODE_STRING <>
LogonDomain             LSA_UNICODE_STRING <>
AuthenticationPackage   LSA_UNICODE_STRING <>
LogonType               ULONG ?
Session                 ULONG ?
Sid                     PSID ?
LogonTime               LARGE_INTEGER <>
LogonServer             LSA_UNICODE_STRING <>
DnsDomainName           LSA_UNICODE_STRING <>
Upn                     LSA_UNICODE_STRING <>
if (_WIN32_WINNT ge 0x0600)
UserFlags               ULONG ?
LastLogonInfo           LSA_LAST_INTER_LOGON_INFO <>
LogonScript             LSA_UNICODE_STRING <>
ProfilePath             LSA_UNICODE_STRING <>
HomeDirectory           LSA_UNICODE_STRING <>
HomeDirectoryDrive      LSA_UNICODE_STRING <>
LogoffTime              LARGE_INTEGER <>
KickOffTime             LARGE_INTEGER <>
PasswordLastSet         LARGE_INTEGER <>
PasswordCanChange       LARGE_INTEGER <>
PasswordMustChange      LARGE_INTEGER <>
endif
SECURITY_LOGON_SESSION_DATA ends
PSECURITY_LOGON_SESSION_DATA typedef ptr SECURITY_LOGON_SESSION_DATA

LsaEnumerateLogonSessions proto WINAPI :PULONG, :ptr
LsaGetLogonSessionData proto WINAPI :PLUID, :ptr

endif
LsaOpenPolicy proto WINAPI :PLSA_UNICODE_STRING, :PLSA_OBJECT_ATTRIBUTES, :ACCESS_MASK, :PLSA_HANDLE

define MAXIMUM_CAPES_PER_CAP 0x7F
define CENTRAL_ACCESS_POLICY_OWNER_RIGHTS_PRESENT_FLAG         0x00000001
define CENTRAL_ACCESS_POLICY_STAGED_OWNER_RIGHTS_PRESENT_FLAG  0x00000100
STAGING_FLAG macro Effective
  exitm<((Effective and 0xF) shl 8)>
  endm

define CENTRAL_ACCESS_POLICY_STAGED_FLAG                       0x00010000
define CENTRAL_ACCESS_POLICY_VALID_FLAG_MASK ( CENTRAL_ACCESS_POLICY_OWNER_RIGHTS_PRESENT_FLAG or CENTRAL_ACCESS_POLICY_STAGED_OWNER_RIGHTS_PRESENT_FLAG or CENTRAL_ACCESS_POLICY_STAGED_FLAG )
define LSASETCAPS_RELOAD_FLAG                      0x00000001
define LSASETCAPS_VALID_FLAG_MASK ( LSASETCAPS_RELOAD_FLAG )

CENTRAL_ACCESS_POLICY_ENTRY struct
Name                    LSA_UNICODE_STRING <>
Description             LSA_UNICODE_STRING <>
ChangeId                LSA_UNICODE_STRING <>
LengthAppliesTo         ULONG ?
AppliesTo               PUCHAR ?
LengthSD                ULONG ?
SD                      PSECURITY_DESCRIPTOR ?
LengthStagedSD          ULONG ?
StagedSD                PSECURITY_DESCRIPTOR ?
Flags                   ULONG ?
CENTRAL_ACCESS_POLICY_ENTRY ends
PCENTRAL_ACCESS_POLICY_ENTRY typedef ptr CENTRAL_ACCESS_POLICY_ENTRY
PCCENTRAL_ACCESS_POLICY_ENTRY typedef ptr CENTRAL_ACCESS_POLICY_ENTRY

CENTRAL_ACCESS_POLICY   struct
CAPID                   PSID ?
Name                    LSA_UNICODE_STRING <>
Description             LSA_UNICODE_STRING <>
ChangeId                LSA_UNICODE_STRING <>
Flags                   ULONG ?
CAPECount               ULONG ?
CAPEs                   ptr PCENTRAL_ACCESS_POLICY_ENTRY ?
CENTRAL_ACCESS_POLICY   ends
PCENTRAL_ACCESS_POLICY  typedef ptr CENTRAL_ACCESS_POLICY
PCCENTRAL_ACCESS_POLICY typedef ptr CENTRAL_ACCESS_POLICY

LsaSetCAPs proto WINAPI :PLSA_UNICODE_STRING, :ULONG, :ULONG
LsaGetAppliedCAPIDs proto WINAPI :PLSA_UNICODE_STRING, :ptr ptr, :PULONG
LsaQueryCAPs proto WINAPI :ptr, :ULONG, :ptr, :PULONG
LsaQueryInformationPolicy proto WINAPI :LSA_HANDLE, :POLICY_INFORMATION_CLASS, :ptr
LsaSetInformationPolicy proto WINAPI :LSA_HANDLE, :POLICY_INFORMATION_CLASS, :PVOID
LsaQueryDomainInformationPolicy proto WINAPI :LSA_HANDLE, :POLICY_DOMAIN_INFORMATION_CLASS, :ptr
LsaSetDomainInformationPolicy proto WINAPI :LSA_HANDLE, :POLICY_DOMAIN_INFORMATION_CLASS, :PVOID
LsaRegisterPolicyChangeNotification proto WINAPI :POLICY_NOTIFICATION_INFORMATION_CLASS, :HANDLE
LsaUnregisterPolicyChangeNotification proto WINAPI :POLICY_NOTIFICATION_INFORMATION_CLASS, :HANDLE
LsaEnumerateTrustedDomains proto WINAPI :LSA_HANDLE, :PLSA_ENUMERATION_HANDLE, :ptr, :ULONG, :PULONG
LsaLookupNames proto WINAPI :LSA_HANDLE, :ULONG, :PLSA_UNICODE_STRING, :ptr, :ptr

if (_WIN32_WINNT ge 0x0501)
LsaLookupNames2 proto WINAPI :LSA_HANDLE, :ULONG, :ULONG, :PLSA_UNICODE_STRING, :ptr, :ptr
endif

LsaLookupSids proto WINAPI :LSA_HANDLE, :ULONG, :ptr, :ptr, :ptr
LsaLookupSids2 proto WINAPI :LSA_HANDLE, :ULONG, :ULONG, :ptr, :ptr, :ptr

define SE_INTERACTIVE_LOGON_NAME           <"SeInteractiveLogonRight">
define SE_NETWORK_LOGON_NAME               <"SeNetworkLogonRight">
define SE_BATCH_LOGON_NAME                 <"SeBatchLogonRight">
define SE_SERVICE_LOGON_NAME               <"SeServiceLogonRight">
define SE_DENY_INTERACTIVE_LOGON_NAME      <"SeDenyInteractiveLogonRight">
define SE_DENY_NETWORK_LOGON_NAME          <"SeDenyNetworkLogonRight">
define SE_DENY_BATCH_LOGON_NAME            <"SeDenyBatchLogonRight">
define SE_DENY_SERVICE_LOGON_NAME          <"SeDenyServiceLogonRight">
if (_WIN32_WINNT ge 0x0501)
define SE_REMOTE_INTERACTIVE_LOGON_NAME    <"SeRemoteInteractiveLogonRight">
define SE_DENY_REMOTE_INTERACTIVE_LOGON_NAME <"SeDenyRemoteInteractiveLogonRight">
endif

LsaEnumerateAccountsWithUserRight proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :ptr, :PULONG
LsaEnumerateAccountRights proto WINAPI :LSA_HANDLE, :PSID, :ptr, :PULONG
LsaAddAccountRights proto WINAPI :LSA_HANDLE, :PSID, :PLSA_UNICODE_STRING, :ULONG
LsaRemoveAccountRights proto WINAPI :LSA_HANDLE, :PSID, :BOOLEAN, :PLSA_UNICODE_STRING, :ULONG
LsaOpenTrustedDomainByName proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :ACCESS_MASK, :PLSA_HANDLE
LsaQueryTrustedDomainInfo proto WINAPI :LSA_HANDLE, :PSID, :TRUSTED_INFORMATION_CLASS, :ptr
LsaSetTrustedDomainInformation proto WINAPI :LSA_HANDLE, :PSID, :TRUSTED_INFORMATION_CLASS, :PVOID
LsaDeleteTrustedDomain proto WINAPI :LSA_HANDLE, :PSID
LsaQueryTrustedDomainInfoByName proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :TRUSTED_INFORMATION_CLASS, :ptr
LsaSetTrustedDomainInfoByName proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :TRUSTED_INFORMATION_CLASS, :PVOID
LsaEnumerateTrustedDomainsEx proto WINAPI :LSA_HANDLE, :PLSA_ENUMERATION_HANDLE, :ptr, :ULONG, :PULONG
LsaCreateTrustedDomainEx proto WINAPI :LSA_HANDLE, :PTRUSTED_DOMAIN_INFORMATION_EX, :PTRUSTED_DOMAIN_AUTH_INFORMATION, :ACCESS_MASK, :PLSA_HANDLE

if (_WIN32_WINNT ge 0x0501)
LsaQueryForestTrustInformation proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :ptr
LsaSetForestTrustInformation proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :PLSA_FOREST_TRUST_INFORMATION, :BOOLEAN, :ptr

ifdef TESTING_MATCHING_ROUTINE
LsaForestTrustFindMatch proto WINAPI :LSA_HANDLE, :ULONG, :PLSA_UNICODE_STRING, :ptr
endif
endif

LsaStorePrivateData proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :PLSA_UNICODE_STRING
LsaRetrievePrivateData proto WINAPI :LSA_HANDLE, :PLSA_UNICODE_STRING, :ptr
LsaNtStatusToWinError proto WINAPI :NTSTATUS

ifndef _NTLSA_IFS_
define _NTLSA_IFS_
endif

.enum NEGOTIATE_MESSAGES {
    NegEnumPackagePrefixes = 0,
    NegGetCallerName = 1,
    NegTransferCredentials = 2,
    NegMsgReserved1 = 3,
    NegCallPackageMax
    }

define NEGOTIATE_MAX_PREFIX    32

NEGOTIATE_PACKAGE_PREFIX struct
PackageId               ULONG_PTR ?
PackageDataA            PVOID ?
PackageDataW            PVOID ?
PrefixLen               ULONG_PTR ?
Prefix                  UCHAR NEGOTIATE_MAX_PREFIX dup(?)
NEGOTIATE_PACKAGE_PREFIX ends
PNEGOTIATE_PACKAGE_PREFIX typedef ptr NEGOTIATE_PACKAGE_PREFIX

NEGOTIATE_PACKAGE_PREFIXES struct
MessageType             ULONG ?
PrefixCount             ULONG ?
Offs                    ULONG ?
if(_WIN32_WINNT ge 0x0502)
Pad                     ULONG ?
endif
NEGOTIATE_PACKAGE_PREFIXES ends
PNEGOTIATE_PACKAGE_PREFIXES typedef ptr NEGOTIATE_PACKAGE_PREFIXES

NEGOTIATE_CALLER_NAME_REQUEST struct
MessageType             ULONG ?
LogonId                 LUID <>
NEGOTIATE_CALLER_NAME_REQUEST ends
PNEGOTIATE_CALLER_NAME_REQUEST typedef ptr NEGOTIATE_CALLER_NAME_REQUEST

NEGOTIATE_CALLER_NAME_RESPONSE struct
MessageType             ULONG ?
CallerName              PWSTR ?
NEGOTIATE_CALLER_NAME_RESPONSE ends
PNEGOTIATE_CALLER_NAME_RESPONSE typedef ptr _NEGOTIATE_CALLER_NAME_RESPONSE

ifndef _NTDEF_
PUNICODE_STRING         typedef ptr ;UNICODE_STRING
PSTRING                 typedef ptr ;STRING
endif

ifndef _DOMAIN_PASSWORD_INFORMATION_DEFINED
define _DOMAIN_PASSWORD_INFORMATION_DEFINED
DOMAIN_PASSWORD_INFORMATION struct
MinPasswordLength       USHORT ?
PasswordHistoryLength   USHORT ?
PasswordProperties      ULONG ?
MaxPasswordAge          LARGE_INTEGER <>
MinPasswordAge          LARGE_INTEGER <>
DOMAIN_PASSWORD_INFORMATION ends
PDOMAIN_PASSWORD_INFORMATION typedef ptr DOMAIN_PASSWORD_INFORMATION
endif

if (_WIN32_WINNT ge 0x0501)

define DOMAIN_PASSWORD_COMPLEX             0x00000001
define DOMAIN_PASSWORD_NO_ANON_CHANGE      0x00000002
define DOMAIN_PASSWORD_NO_CLEAR_CHANGE     0x00000004
define DOMAIN_LOCKOUT_ADMINS               0x00000008
define DOMAIN_PASSWORD_STORE_CLEARTEXT     0x00000010
define DOMAIN_REFUSE_PASSWORD_CHANGE       0x00000020
if(_WIN32_WINNT ge 0x0502)
define DOMAIN_NO_LM_OWF_CHANGE             0x00000040
endif
endif

ifndef _PASSWORD_NOTIFICATION_DEFINED
define _PASSWORD_NOTIFICATION_DEFINED
CALLBACK(PSAM_PASSWORD_NOTIFICATION_ROUTINE, :PUNICODE_STRING, :ULONG, :PUNICODE_STRING)

define SAM_PASSWORD_CHANGE_NOTIFY_ROUTINE  <"PasswordChangeNotify">

CALLBACK(PSAM_INIT_NOTIFICATION_ROUTINE)

define SAM_INIT_NOTIFICATION_ROUTINE  <"InitializeChangeNotify">
define SAM_PASSWORD_FILTER_ROUTINE  <"PasswordFilter">

CALLBACK(PSAM_PASSWORD_FILTER_ROUTINE, :PUNICODE_STRING, :PUNICODE_STRING, :PUNICODE_STRING, :BOOLEAN)

endif

define MSV1_0_PACKAGE_NAME     <"MICROSOFT_AUTHENTICATION_PACKAGE_V1_0">
define MSV1_0_PACKAGE_NAMEW    <L"MICROSOFT_AUTHENTICATION_PACKAGE_V1_0">
define MSV1_0_PACKAGE_NAMEW_LENGTH sizeof(MSV1_0_PACKAGE_NAMEW) - sizeof(WCHAR)

;define MSV1_0_SUBAUTHENTICATION_KEY <"SYSTEM\\CurrentControlSet\\Control\\Lsa\\MSV1_0">
define MSV1_0_SUBAUTHENTICATION_VALUE <"Auth">

.enum MSV1_0_LOGON_SUBMIT_TYPE {
    MsV1_0InteractiveLogon = 2,
    MsV1_0Lm20Logon,
    MsV1_0NetworkLogon,
    MsV1_0SubAuthLogon,
    MsV1_0WorkstationUnlockLogon = 7,
    MsV1_0S4ULogon = 12,
    MsV1_0VirtualLogon = 82,
    MsV1_0NoElevationLogon = 83,
    MsV1_0LuidLogon = 84,
    }

.enum MSV1_0_PROFILE_BUFFER_TYPE {
    MsV1_0InteractiveProfile = 2,
    MsV1_0Lm20LogonProfile,
    MsV1_0SmartCardProfile
    }

MSV1_0_INTERACTIVE_LOGON struct
MessageType             MSV1_0_LOGON_SUBMIT_TYPE ?
LogonDomainName         UNICODE_STRING <>
UserName                UNICODE_STRING <>
Password                UNICODE_STRING <>
MSV1_0_INTERACTIVE_LOGON ends
PMSV1_0_INTERACTIVE_LOGON typedef ptr MSV1_0_INTERACTIVE_LOGON

MSV1_0_INTERACTIVE_PROFILE struct
MessageType             MSV1_0_PROFILE_BUFFER_TYPE ?
LogonCount              USHORT ?
BadPasswordCount        USHORT ?
LogonTime               LARGE_INTEGER <>
LogoffTime              LARGE_INTEGER <>
KickOffTime             LARGE_INTEGER <>
PasswordLastSet         LARGE_INTEGER <>
PasswordCanChange       LARGE_INTEGER <>
PasswordMustChange      LARGE_INTEGER <>
LogonScript             UNICODE_STRING <>
HomeDirectory           UNICODE_STRING <>
FullName                UNICODE_STRING <>
ProfilePath             UNICODE_STRING <>
HomeDirectoryDrive      UNICODE_STRING <>
LogonServer             UNICODE_STRING <>
UserFlags               ULONG ?
MSV1_0_INTERACTIVE_PROFILE ends
PMSV1_0_INTERACTIVE_PROFILE typedef ptr MSV1_0_INTERACTIVE_PROFILE

define MSV1_0_CHALLENGE_LENGTH 8
define MSV1_0_USER_SESSION_KEY_LENGTH 16
define MSV1_0_LANMAN_SESSION_KEY_LENGTH 8

define MSV1_0_CLEARTEXT_PASSWORD_ALLOWED    0x02
define MSV1_0_UPDATE_LOGON_STATISTICS       0x04
define MSV1_0_RETURN_USER_PARAMETERS        0x08
define MSV1_0_DONT_TRY_GUEST_ACCOUNT        0x10
define MSV1_0_ALLOW_SERVER_TRUST_ACCOUNT    0x20
define MSV1_0_RETURN_PASSWORD_EXPIRY        0x40
define MSV1_0_USE_CLIENT_CHALLENGE          0x80
define MSV1_0_TRY_GUEST_ACCOUNT_ONLY        0x100
define MSV1_0_RETURN_PROFILE_PATH           0x200
define MSV1_0_TRY_SPECIFIED_DOMAIN_ONLY     0x400
define MSV1_0_ALLOW_WORKSTATION_TRUST_ACCOUNT 0x800
define MSV1_0_DISABLE_PERSONAL_FALLBACK     0x00001000
define MSV1_0_ALLOW_FORCE_GUEST             0x00002000
if (_WIN32_WINNT ge 0x0502)
define MSV1_0_CLEARTEXT_PASSWORD_SUPPLIED   0x00004000
define MSV1_0_USE_DOMAIN_FOR_ROUTING_ONLY   0x00008000
endif
define MSV1_0_SUBAUTHENTICATION_DLL_EX      0x00100000
define MSV1_0_ALLOW_MSVCHAPV2               0x00010000

if (_WIN32_WINNT ge 0x0600)

define MSV1_0_S4U2SELF                      0x00020000
define MSV1_0_CHECK_LOGONHOURS_FOR_S4U      0x00040000
endif

if (_WIN32_WINNT ge 0x0602)
define MSV1_0_INTERNET_DOMAIN               0x00080000
endif

define MSV1_0_SUBAUTHENTICATION_DLL         0xFF000000
define MSV1_0_SUBAUTHENTICATION_DLL_SHIFT   24
define MSV1_0_MNS_LOGON                     0x01000000

define MSV1_0_SUBAUTHENTICATION_DLL_RAS     2
define MSV1_0_SUBAUTHENTICATION_DLL_IIS     132

MSV1_0_LM20_LOGON       struct
MessageType             MSV1_0_LOGON_SUBMIT_TYPE ?
LogonDomainName         UNICODE_STRING <>
UserName                UNICODE_STRING <>
Workstation             UNICODE_STRING <>
ChallengeToClient       UCHAR MSV1_0_CHALLENGE_LENGTH dup(?)
CaseSensitiveChallengeResponse STRING <>
CaseInsensitiveChallengeResponse STRING <>
ParameterControl        ULONG ?
MSV1_0_LM20_LOGON       ends
PMSV1_0_LM20_LOGON      typedef ptr MSV1_0_LM20_LOGON

MSV1_0_SUBAUTH_LOGON    struct
MessageType             MSV1_0_LOGON_SUBMIT_TYPE ?
LogonDomainName         UNICODE_STRING <>
UserName                UNICODE_STRING <>
Workstation             UNICODE_STRING <>
ChallengeToClient       UCHAR MSV1_0_CHALLENGE_LENGTH dup(?)
AuthenticationInfo1     STRING <>
AuthenticationInfo2     STRING <>
ParameterControl        ULONG ?
SubAuthPackageId        ULONG ?
MSV1_0_SUBAUTH_LOGON    ends
PMSV1_0_SUBAUTH_LOGON   typedef ptr MSV1_0_SUBAUTH_LOGON

if (_WIN32_WINNT ge 0x0600)

define MSV1_0_S4U_LOGON_FLAG_CHECK_LOGONHOURS 0x2

MSV1_0_S4U_LOGON        struct
MessageType             MSV1_0_LOGON_SUBMIT_TYPE ?
Flags                   ULONG ?
UserPrincipalName       UNICODE_STRING <>
DomainName              UNICODE_STRING <>
MSV1_0_S4U_LOGON        ends
PMSV1_0_S4U_LOGON       typedef ptr MSV1_0_S4U_LOGON

endif

define LOGON_GUEST                 0x01
define LOGON_NOENCRYPTION          0x02
define LOGON_CACHED_ACCOUNT        0x04
define LOGON_USED_LM_PASSWORD      0x08
define LOGON_EXTRA_SIDS            0x20
define LOGON_SUBAUTH_SESSION_KEY   0x40
define LOGON_SERVER_TRUST_ACCOUNT  0x80
define LOGON_NTLMV2_ENABLED        0x100
define LOGON_RESOURCE_GROUPS       0x200
define LOGON_PROFILE_PATH_RETURNED 0x400
define LOGON_NT_V2                 0x800
define LOGON_LM_V2                 0x1000
define LOGON_NTLM_V2               0x2000

if (_WIN32_WINNT ge 0x0600)

define LOGON_OPTIMIZED             0x4000
define LOGON_WINLOGON              0x8000
define LOGON_PKINIT               0x10000
define LOGON_NO_OPTIMIZED         0x20000

endif

if (_WIN32_WINNT ge 0x0602)

define LOGON_NO_ELEVATION         0x40000
define LOGON_MANAGED_SERVICE      0x80000

endif

define MSV1_0_SUBAUTHENTICATION_FLAGS 0xFF000000
define LOGON_GRACE_LOGON              0x01000000

MSV1_0_LM20_LOGON_PROFILE struct
MessageType             MSV1_0_PROFILE_BUFFER_TYPE ?
KickOffTime             LARGE_INTEGER <>
LogoffTime              LARGE_INTEGER <>
UserFlags               ULONG ?
UserSessionKey          UCHAR MSV1_0_USER_SESSION_KEY_LENGTH dup(?)
LogonDomainName         UNICODE_STRING <>
LanmanSessionKey        UCHAR MSV1_0_LANMAN_SESSION_KEY_LENGTH dup(?)
LogonServer             UNICODE_STRING <>
UserParameters          UNICODE_STRING <>
MSV1_0_LM20_LOGON_PROFILE ends
PMSV1_0_LM20_LOGON_PROFILE typedef ptr MSV1_0_LM20_LOGON_PROFILE

define MSV1_0_OWF_PASSWORD_LENGTH 16
define MSV1_0_SHA_PASSWORD_LENGTH 20
define MSV1_0_CREDENTIAL_KEY_LENGTH 20

define MSV1_0_CRED_LM_PRESENT      0x0001
define MSV1_0_CRED_NT_PRESENT      0x0002
define MSV1_0_CRED_REMOVED         0x0004
define MSV1_0_CRED_CREDKEY_PRESENT 0x0008
define MSV1_0_CRED_SHA_PRESENT     0x0010

define MSV1_0_CRED_VERSION             0
define MSV1_0_CRED_VERSION_V2          2
define MSV1_0_CRED_VERSION_V3          4
define MSV1_0_CRED_VERSION_IUM         0xffff0001
define MSV1_0_CRED_VERSION_REMOTE      0xffff0002
define MSV1_0_CRED_VERSION_ARSO        0xffff0003
define MSV1_0_CRED_VERSION_RESERVED_1  0xfffffffe
define MSV1_0_CRED_VERSION_INVALID     0xffffffff

.enum MSV1_0_CREDENTIAL_KEY_TYPE {
    InvalidCredKey,
    DeprecatedIUMCredKey,
    DomainUserCredKey,
    LocalUserCredKey,
    ExternallySuppliedCredKey
    }

MSV1_0_CREDENTIAL_KEY   struct
Data                    UCHAR MSV1_0_CREDENTIAL_KEY_LENGTH dup(?)
MSV1_0_CREDENTIAL_KEY   ends
PMSV1_0_CREDENTIAL_KEY  typedef ptr MSV1_0_CREDENTIAL_KEY

MSV1_0_SUPPLEMENTAL_CREDENTIAL struct
Version                 ULONG ?
Flags                   ULONG ?
LmPassword              UCHAR MSV1_0_OWF_PASSWORD_LENGTH dup(?)
NtPassword              UCHAR MSV1_0_OWF_PASSWORD_LENGTH dup(?)
MSV1_0_SUPPLEMENTAL_CREDENTIAL ends
PMSV1_0_SUPPLEMENTAL_CREDENTIAL typedef ptr MSV1_0_SUPPLEMENTAL_CREDENTIAL

MSV1_0_SUPPLEMENTAL_CREDENTIAL_V2 struct
Version                 ULONG ?
Flags                   ULONG ?
NtPassword              UCHAR MSV1_0_OWF_PASSWORD_LENGTH dup(?)
CredentialKey           MSV1_0_CREDENTIAL_KEY <>
MSV1_0_SUPPLEMENTAL_CREDENTIAL_V2 ends
PMSV1_0_SUPPLEMENTAL_CREDENTIAL_V2 typedef ptr MSV1_0_SUPPLEMENTAL_CREDENTIAL_V2

MSV1_0_SUPPLEMENTAL_CREDENTIAL_V3 struct
Version                 ULONG ?
Flags                   ULONG ?
CredentialKeyType       MSV1_0_CREDENTIAL_KEY_TYPE ?
NtPassword              UCHAR MSV1_0_OWF_PASSWORD_LENGTH dup(?)
CredentialKey           MSV1_0_CREDENTIAL_KEY <>
ShaPassword             UCHAR MSV1_0_SHA_PASSWORD_LENGTH dup(?)
MSV1_0_SUPPLEMENTAL_CREDENTIAL_V3 ends
PMSV1_0_SUPPLEMENTAL_CREDENTIAL_V3 typedef ptr MSV1_0_SUPPLEMENTAL_CREDENTIAL_V3

MSV1_0_IUM_SUPPLEMENTAL_CREDENTIAL struct
Version                 ULONG ?
EncryptedCredsSize      ULONG ?
EncryptedCreds          UCHAR ANYSIZE_ARRAY dup(?)
MSV1_0_IUM_SUPPLEMENTAL_CREDENTIAL ends
PMSV1_0_IUM_SUPPLEMENTAL_CREDENTIAL typedef ptr MSV1_0_IUM_SUPPLEMENTAL_CREDENTIAL

MSV1_0_IUM_SUPPLEMENTAL_CREDENTIAL_SIZE macro Creds
  exitm<(FIELD_OFFSET(MSV1_0_IUM_SUPPLEMENTAL_CREDENTIAL, EncryptedCreds) + (Creds).EncryptedCredsSize)>
  endm

MSV1_0_REMOTE_SUPPLEMENTAL_CREDENTIAL struct 1
Version                 ULONG ?
Flags                   ULONG ?
CredentialKey           MSV1_0_CREDENTIAL_KEY <>
CredentialKeyType       MSV1_0_CREDENTIAL_KEY_TYPE ?
EncryptedCredsSize      ULONG ?
EncryptedCreds          UCHAR ANYSIZE_ARRAY dup(?)
MSV1_0_REMOTE_SUPPLEMENTAL_CREDENTIAL ends
PMSV1_0_REMOTE_SUPPLEMENTAL_CREDENTIAL typedef ptr MSV1_0_REMOTE_SUPPLEMENTAL_CREDENTIAL

define MSV1_0_NTLM3_RESPONSE_LENGTH 16
define MSV1_0_NTLM3_OWF_LENGTH 16

if (_WIN32_WINNT eq 0x0500)
define MSV1_0_MAX_NTLM3_LIFE 1800
else
define MSV1_0_MAX_NTLM3_LIFE 129600
endif
define MSV1_0_MAX_AVL_SIZE 64000

if (_WIN32_WINNT ge 0x0501)

define MSV1_0_AV_FLAG_FORCE_GUEST                  0x00000001
if (_WIN32_WINNT ge 0x0600)
define MSV1_0_AV_FLAG_MIC_HANDSHAKE_MESSAGES       0x00000002
if (_WIN32_WINNT ge 0x0601)
define MSV1_0_AV_FLAG_UNVERIFIED_TARGET            0x00000004

endif
endif
endif

MSV1_0_NTLM3_RESPONSE   struct
Response                UCHAR MSV1_0_NTLM3_RESPONSE_LENGTH dup(?)
RespType                UCHAR ?
HiRespType              UCHAR ?
Flags                   USHORT ?
MsgWord                 ULONG ?
TimeStamp               ULONGLONG ?
ChallengeFromClient     UCHAR MSV1_0_CHALLENGE_LENGTH dup(?)
AvPairsOff              ULONG ?
Buffer                  UCHAR 1 dup(?)
MSV1_0_NTLM3_RESPONSE   ends
PMSV1_0_NTLM3_RESPONSE  typedef ptr MSV1_0_NTLM3_RESPONSE

define MSV1_0_NTLM3_INPUT_LENGTH (sizeof(MSV1_0_NTLM3_RESPONSE) - MSV1_0_NTLM3_RESPONSE_LENGTH)
if(_WIN32_WINNT ge 0x0502)
define MSV1_0_NTLM3_MIN_NT_RESPONSE_LENGTH RTL_SIZEOF_THROUGH_FIELD(MSV1_0_NTLM3_RESPONSE, AvPairsOff)
endif

.enum MSV1_0_AVID {
    MsvAvEOL,
    MsvAvNbComputerName,
    MsvAvNbDomainName,
    MsvAvDnsComputerName,
    MsvAvDnsDomainName,
if (_WIN32_WINNT ge 0x0501)
    MsvAvDnsTreeName,
    MsvAvFlags,
if (_WIN32_WINNT ge 0x0600)
    MsvAvTimestamp,
    MsvAvRestrictions,
    MsvAvTargetName,
    MsvAvChannelBindings,
endif
endif
}

MSV1_0_AV_PAIR          struct
AvId                    USHORT ?
AvLen                   USHORT ?
MSV1_0_AV_PAIR          ends
PMSV1_0_AV_PAIR         typedef ptr MSV1_0_AV_PAIR

.enum MSV1_0_PROTOCOL_MESSAGE_TYPE {
    MsV1_0Lm20ChallengeRequest = 0,
    MsV1_0Lm20GetChallengeResponse,
    MsV1_0EnumerateUsers,
    MsV1_0GetUserInfo,
    MsV1_0ReLogonUsers,
    MsV1_0ChangePassword,
    MsV1_0ChangeCachedPassword,
    MsV1_0GenericPassthrough,
    MsV1_0CacheLogon,
    MsV1_0SubAuth,
    MsV1_0DeriveCredential,
    MsV1_0CacheLookup,
if (_WIN32_WINNT ge 0x0501)
    MsV1_0SetProcessOption,
endif
if (_WIN32_WINNT ge 0x0600)
    MsV1_0ConfigLocalAliases,
    MsV1_0ClearCachedCredentials,
endif
if (_WIN32_WINNT ge 0x0601)
    MsV1_0LookupToken,
endif
if (_WIN32_WINNT ge 0x0602)
    MsV1_0ValidateAuth,
    MsV1_0CacheLookupEx,
    MsV1_0GetCredentialKey,
    MsV1_0SetThreadOption,
endif
if (_WIN32_WINNT ge 0x0604)
    MsV1_0DecryptDpapiMasterKey,
    MsV1_0GetStrongCredentialKey,
endif
if (_WIN32_WINNT ge 0x0A00)
    MsV1_0TransferCred,
    MsV1_0ProvisionTbal,
    MsV1_0DeleteTbalSecrets,
endif
}

MSV1_0_CHANGEPASSWORD_REQUEST struct
MessageType             MSV1_0_PROTOCOL_MESSAGE_TYPE ?
DomainName              UNICODE_STRING <>
AccountName             UNICODE_STRING <>
OldPassword             UNICODE_STRING <>
NewPassword             UNICODE_STRING <>
Impersonating           BOOLEAN ?
MSV1_0_CHANGEPASSWORD_REQUEST ends
PMSV1_0_CHANGEPASSWORD_REQUEST typedef ptr MSV1_0_CHANGEPASSWORD_REQUEST

MSV1_0_CHANGEPASSWORD_RESPONSE struct
MessageType             MSV1_0_PROTOCOL_MESSAGE_TYPE ?
PasswordInfoValid       BOOLEAN ?
DomainPasswordInfo      DOMAIN_PASSWORD_INFORMATION <>
MSV1_0_CHANGEPASSWORD_RESPONSE ends
PMSV1_0_CHANGEPASSWORD_RESPONSE typedef ptr MSV1_0_CHANGEPASSWORD_RESPONSE

if(_WIN32_WINNT ge 0x0502)

MSV1_0_PASSTHROUGH_REQUEST struct
MessageType             MSV1_0_PROTOCOL_MESSAGE_TYPE ?
DomainName              UNICODE_STRING <>
PackageName             UNICODE_STRING <>
DataLength              ULONG ?
LogonData               PUCHAR ?
Pad                     ULONG ?
MSV1_0_PASSTHROUGH_REQUEST ends
PMSV1_0_PASSTHROUGH_REQUEST typedef ptr MSV1_0_PASSTHROUGH_REQUEST

MSV1_0_PASSTHROUGH_RESPONSE struct
MessageType             MSV1_0_PROTOCOL_MESSAGE_TYPE ?
Pad                     ULONG ?
DataLength              ULONG ?
ValidationData          PUCHAR ?
MSV1_0_PASSTHROUGH_RESPONSE ends
PMSV1_0_PASSTHROUGH_RESPONSE typedef ptr MSV1_0_PASSTHROUGH_RESPONSE
endif

MSV1_0_SUBAUTH_REQUEST  struct
MessageType             MSV1_0_PROTOCOL_MESSAGE_TYPE ?
SubAuthPackageId        ULONG ?
SubAuthInfoLength       ULONG ?
SubAuthSubmitBuffer     PUCHAR ?
MSV1_0_SUBAUTH_REQUEST  ends
PMSV1_0_SUBAUTH_REQUEST typedef ptr MSV1_0_SUBAUTH_REQUEST

MSV1_0_SUBAUTH_RESPONSE struct
MessageType             MSV1_0_PROTOCOL_MESSAGE_TYPE ?
SubAuthInfoLength       ULONG ?
SubAuthReturnBuffer     PUCHAR ?
MSV1_0_SUBAUTH_RESPONSE ends
PMSV1_0_SUBAUTH_RESPONSE typedef ptr MSV1_0_SUBAUTH_RESPONSE

if(_WIN32_WINNT ge 0x0501)
define RtlGenRandom                    <SystemFunction036>
endif
if(_WIN32_WINNT ge 0x0500)
define RtlEncryptMemory                <SystemFunction040>
define RtlDecryptMemory                <SystemFunction041>
endif

if(_WIN32_WINNT ge 0x0501)
RtlGenRandom proto WINAPI :PVOID, :ULONG
endif

define RTL_ENCRYPT_MEMORY_SIZE             8
define RTL_ENCRYPT_OPTION_CROSS_PROCESS    0x01
define RTL_ENCRYPT_OPTION_SAME_LOGON       0x02
define RTL_ENCRYPT_OPTION_FOR_SYSTEM       0x04

RtlEncryptMemory proto WINAPI :PVOID, :ULONG, :ULONG
RtlDecryptMemory proto WINAPI :PVOID, :ULONG, :ULONG

define KERBEROS_VERSION    5
define KERBEROS_REVISION   6

define KERB_ETYPE_NULL             0
define KERB_ETYPE_DES_CBC_CRC      1
define KERB_ETYPE_DES_CBC_MD4      2
define KERB_ETYPE_DES_CBC_MD5      3
define KERB_ETYPE_AES128_CTS_HMAC_SHA1_96    17
define KERB_ETYPE_AES256_CTS_HMAC_SHA1_96    18

define KERB_ETYPE_RC4_MD4          -128
define KERB_ETYPE_RC4_PLAIN2       -129
define KERB_ETYPE_RC4_LM           -130
define KERB_ETYPE_RC4_SHA          -131
define KERB_ETYPE_DES_PLAIN        -132
define KERB_ETYPE_RC4_HMAC_OLD     -133
define KERB_ETYPE_RC4_PLAIN_OLD    -134
define KERB_ETYPE_RC4_HMAC_OLD_EXP -135
define KERB_ETYPE_RC4_PLAIN_OLD_EXP -136
define KERB_ETYPE_RC4_PLAIN        -140
define KERB_ETYPE_RC4_PLAIN_EXP    -141

define KERB_ETYPE_AES128_CTS_HMAC_SHA1_96_PLAIN    -148
define KERB_ETYPE_AES256_CTS_HMAC_SHA1_96_PLAIN    -149

define KERB_ETYPE_DSA_SHA1_CMS                             9
define KERB_ETYPE_RSA_MD5_CMS                              10
define KERB_ETYPE_RSA_SHA1_CMS                             11
define KERB_ETYPE_RC2_CBC_ENV                              12
define KERB_ETYPE_RSA_ENV                                  13
define KERB_ETYPE_RSA_ES_OEAP_ENV                          14
define KERB_ETYPE_DES_EDE3_CBC_ENV                         15

define KERB_ETYPE_DSA_SIGN                                8
define KERB_ETYPE_RSA_PRIV                                9
define KERB_ETYPE_RSA_PUB                                 10
define KERB_ETYPE_RSA_PUB_MD5                             11
define KERB_ETYPE_RSA_PUB_SHA1                            12
define KERB_ETYPE_PKCS7_PUB                               13

if(_WIN32_WINNT ge 0x0502)

define KERB_ETYPE_DES3_CBC_MD5                             5
define KERB_ETYPE_DES3_CBC_SHA1                            7
define KERB_ETYPE_DES3_CBC_SHA1_KD                        16
endif

define KERB_ETYPE_DES_CBC_MD5_NT                          20
define KERB_ETYPE_RC4_HMAC_NT                             23
define KERB_ETYPE_RC4_HMAC_NT_EXP                         24

define KERB_CHECKSUM_NONE  0
define KERB_CHECKSUM_CRC32         1
define KERB_CHECKSUM_MD4           2
define KERB_CHECKSUM_KRB_DES_MAC   4
if (_WIN32_WINNT ge 0x0501)
define KERB_CHECKSUM_KRB_DES_MAC_K 5
endif
define KERB_CHECKSUM_MD5           7
define KERB_CHECKSUM_MD5_DES       8

define KERB_CHECKSUM_SHA1_NEW      14
define KERB_CHECKSUM_HMAC_SHA1_96_AES128  15
define KERB_CHECKSUM_HMAC_SHA1_96_AES256  16

define KERB_CHECKSUM_LM            -130
define KERB_CHECKSUM_SHA1          -131
define KERB_CHECKSUM_REAL_CRC32    -132
define KERB_CHECKSUM_DES_MAC       -133
define KERB_CHECKSUM_DES_MAC_MD5   -134
define KERB_CHECKSUM_MD25          -135
define KERB_CHECKSUM_RC4_MD5       -136
define KERB_CHECKSUM_MD5_HMAC      -137
define KERB_CHECKSUM_HMAC_MD5      -138

define KERB_CHECKSUM_HMAC_SHA1_96_AES128_Ki -150
define KERB_CHECKSUM_HMAC_SHA1_96_AES256_Ki -151

define AUTH_REQ_ALLOW_FORWARDABLE      0x00000001
define AUTH_REQ_ALLOW_PROXIABLE        0x00000002
define AUTH_REQ_ALLOW_POSTDATE         0x00000004
define AUTH_REQ_ALLOW_RENEWABLE        0x00000008
define AUTH_REQ_ALLOW_NOADDRESS        0x00000010
define AUTH_REQ_ALLOW_ENC_TKT_IN_SKEY  0x00000020
define AUTH_REQ_ALLOW_VALIDATE         0x00000040
define AUTH_REQ_VALIDATE_CLIENT        0x00000080
define AUTH_REQ_OK_AS_DELEGATE         0x00000100
define AUTH_REQ_PREAUTH_REQUIRED       0x00000200
define AUTH_REQ_TRANSITIVE_TRUST       0x00000400
if(_WIN32_WINNT ge 0x0502)
define AUTH_REQ_ALLOW_S4U_DELEGATE     0x00000800
endif

define AUTH_REQ_PER_USER_FLAGS         (AUTH_REQ_ALLOW_FORWARDABLE or AUTH_REQ_ALLOW_PROXIABLE or AUTH_REQ_ALLOW_POSTDATE or AUTH_REQ_ALLOW_RENEWABLE or AUTH_REQ_ALLOW_VALIDATE )

define KERB_TICKET_FLAGS_reserved          0x80000000
define KERB_TICKET_FLAGS_forwardable       0x40000000
define KERB_TICKET_FLAGS_forwarded         0x20000000
define KERB_TICKET_FLAGS_proxiable         0x10000000
define KERB_TICKET_FLAGS_proxy             0x08000000
define KERB_TICKET_FLAGS_may_postdate      0x04000000
define KERB_TICKET_FLAGS_postdated         0x02000000
define KERB_TICKET_FLAGS_invalid           0x01000000
define KERB_TICKET_FLAGS_renewable         0x00800000
define KERB_TICKET_FLAGS_initial           0x00400000
define KERB_TICKET_FLAGS_pre_authent       0x00200000
define KERB_TICKET_FLAGS_hw_authent        0x00100000
define KERB_TICKET_FLAGS_ok_as_delegate    0x00040000
define KERB_TICKET_FLAGS_name_canonicalize 0x00010000
if (_WIN32_WINNT eq 0x0501)
define KERB_TICKET_FLAGS_cname_in_pa_data  0x00040000
endif
define KERB_TICKET_FLAGS_enc_pa_rep        0x00010000
define KERB_TICKET_FLAGS_reserved1         0x00000001

if (_WIN32_WINNT ge 0x0501)

define KRB_NT_UNKNOWN   0
define KRB_NT_PRINCIPAL 1
define KRB_NT_PRINCIPAL_AND_ID -131
define KRB_NT_SRV_INST  2
define KRB_NT_SRV_INST_AND_ID -132
define KRB_NT_SRV_HST   3
define KRB_NT_SRV_XHST  4
define KRB_NT_UID       5
define KRB_NT_ENTERPRISE_PRINCIPAL 10
define KRB_NT_WELLKNOWN 11
define KRB_NT_ENT_PRINCIPAL_AND_ID -130

define KRB_NT_MS_PRINCIPAL         -128
define KRB_NT_MS_PRINCIPAL_AND_ID  -129
define KRB_NT_MS_BRANCH_ID         -133

KERB_IS_MS_PRINCIPAL macro _x_
  exitm<(((_x_) le KRB_NT_MS_PRINCIPAL) or ((_x_) ge KRB_NT_ENTERPRISE_PRINCIPAL))>
  endm
endif

if (_WIN32_WINNT ge 0x0600)
define KRB_NT_X500_PRINCIPAL 6
endif

define KRB_WELLKNOWN_STRING <L"WELLKNOWN">
define KRB_ANONYMOUS_STRING <L"ANONYMOUS">

ifndef MICROSOFT_KERBEROS_NAME_A

define MICROSOFT_KERBEROS_NAME_A   <"Kerberos">
define MICROSOFT_KERBEROS_NAME_W   <L"Kerberos">
ifdef WIN32_CHICAGO
define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_A
else
define MICROSOFT_KERBEROS_NAME MICROSOFT_KERBEROS_NAME_W
endif
endif

define KERB_WRAP_NO_ENCRYPT 0x80000001

.enum KERB_LOGON_SUBMIT_TYPE {
    KerbInteractiveLogon = 2,
    KerbSmartCardLogon = 6,
    KerbWorkstationUnlockLogon = 7,
    KerbSmartCardUnlockLogon = 8,
    KerbProxyLogon = 9,
    KerbTicketLogon = 10,
    KerbTicketUnlockLogon = 11,
    KerbS4ULogon = 12,
if (_WIN32_WINNT ge 0x0600)
    KerbCertificateLogon = 13,
    KerbCertificateS4ULogon = 14,
    KerbCertificateUnlockLogon = 15,
endif
if (_WIN32_WINNT ge 0x0602)
    KerbNoElevationLogon = 83,
    KerbLuidLogon = 84,
endif
}

KERB_INTERACTIVE_LOGON  struct
MessageType             KERB_LOGON_SUBMIT_TYPE ?
LogonDomainName         UNICODE_STRING <>
UserName                UNICODE_STRING <>
Password                UNICODE_STRING <>
KERB_INTERACTIVE_LOGON  ends
PKERB_INTERACTIVE_LOGON typedef ptr KERB_INTERACTIVE_LOGON

KERB_INTERACTIVE_UNLOCK_LOGON struct
Logon                   KERB_INTERACTIVE_LOGON <>
LogonId                 LUID <>
KERB_INTERACTIVE_UNLOCK_LOGON ends
PKERB_INTERACTIVE_UNLOCK_LOGON typedef ptr KERB_INTERACTIVE_UNLOCK_LOGON

KERB_SMART_CARD_LOGON   struct
MessageType             KERB_LOGON_SUBMIT_TYPE ?
Pin                     UNICODE_STRING <>
CspDataLength           ULONG ?
CspData                 PUCHAR ?
KERB_SMART_CARD_LOGON   ends
PKERB_SMART_CARD_LOGON  typedef ptr KERB_SMART_CARD_LOGON

KERB_SMART_CARD_UNLOCK_LOGON struct
Logon                   KERB_SMART_CARD_LOGON <>
LogonId                 LUID <>
KERB_SMART_CARD_UNLOCK_LOGON ends
PKERB_SMART_CARD_UNLOCK_LOGON typedef ptr KERB_SMART_CARD_UNLOCK_LOGON

if (_WIN32_WINNT ge 0x0600)

define KERB_CERTIFICATE_LOGON_FLAG_CHECK_DUPLICATES            0x1
define KERB_CERTIFICATE_LOGON_FLAG_USE_CERTIFICATE_INFO        0x2

KERB_CERTIFICATE_LOGON  struct
MessageType             KERB_LOGON_SUBMIT_TYPE ?
DomainName              UNICODE_STRING <>
UserName                UNICODE_STRING <>
Pin                     UNICODE_STRING <>
Flags                   ULONG ?
CspDataLength           ULONG ?
CspData                 PUCHAR ?
KERB_CERTIFICATE_LOGON  ends
PKERB_CERTIFICATE_LOGON typedef ptr KERB_CERTIFICATE_LOGON

KERB_CERTIFICATE_UNLOCK_LOGON struct
Logon                   KERB_CERTIFICATE_LOGON <>
LogonId                 LUID <>
KERB_CERTIFICATE_UNLOCK_LOGON ends
PKERB_CERTIFICATE_UNLOCK_LOGON typedef ptr KERB_CERTIFICATE_UNLOCK_LOGON

define KERB_CERTIFICATE_S4U_LOGON_FLAG_CHECK_DUPLICATES 0x1
define KERB_CERTIFICATE_S4U_LOGON_FLAG_CHECK_LOGONHOURS 0x2
define KERB_CERTIFICATE_S4U_LOGON_FLAG_FAIL_IF_NT_AUTH_POLICY_REQUIRED 0x4
define KERB_CERTIFICATE_S4U_LOGON_FLAG_IDENTIFY         0x8

KERB_CERTIFICATE_S4U_LOGON struct
MessageType             KERB_LOGON_SUBMIT_TYPE ?
Flags                   ULONG ?
UserPrincipalName       UNICODE_STRING <>
DomainName              UNICODE_STRING <>
CertificateLength       ULONG ?
Certificate             PUCHAR ?
KERB_CERTIFICATE_S4U_LOGON ends
PKERB_CERTIFICATE_S4U_LOGON typedef ptr KERB_CERTIFICATE_S4U_LOGON

endif

KERB_TICKET_LOGON       struct
MessageType             KERB_LOGON_SUBMIT_TYPE ?
Flags                   ULONG ?
ServiceTicketLength     ULONG ?
TicketGrantingTicketLength ULONG ?
ServiceTicket           PUCHAR ?
TicketGrantingTicket    PUCHAR ?
KERB_TICKET_LOGON       ends
PKERB_TICKET_LOGON      typedef ptr KERB_TICKET_LOGON

define KERB_LOGON_FLAG_ALLOW_EXPIRED_TICKET 0x1
define KERB_LOGON_FLAG_REDIRECTED           0x2

KERB_TICKET_UNLOCK_LOGON struct
Logon                   KERB_TICKET_LOGON <>
LogonId                 LUID <>
KERB_TICKET_UNLOCK_LOGON ends
PKERB_TICKET_UNLOCK_LOGON typedef ptr KERB_TICKET_UNLOCK_LOGON

if (_WIN32_WINNT ge 0x0600)

define KERB_S4U_LOGON_FLAG_CHECK_LOGONHOURS 0x2
define KERB_S4U_LOGON_FLAG_IDENTIFY         0x8

endif

KERB_S4U_LOGON          struct
MessageType             KERB_LOGON_SUBMIT_TYPE ?
Flags                   ULONG ?
ClientUpn               UNICODE_STRING <>
ClientRealm             UNICODE_STRING <>
KERB_S4U_LOGON          ends
PKERB_S4U_LOGON         typedef ptr KERB_S4U_LOGON

.enum KERB_PROFILE_BUFFER_TYPE {
    KerbInteractiveProfile = 2,
    KerbSmartCardProfile = 4,
    KerbTicketProfile = 6
    }

KERB_INTERACTIVE_PROFILE struct
MessageType             KERB_PROFILE_BUFFER_TYPE ?
LogonCount              USHORT ?
BadPasswordCount        USHORT ?
LogonTime               LARGE_INTEGER <>
LogoffTime              LARGE_INTEGER <>
KickOffTime             LARGE_INTEGER <>
PasswordLastSet         LARGE_INTEGER <>
PasswordCanChange       LARGE_INTEGER <>
PasswordMustChange      LARGE_INTEGER <>
LogonScript             UNICODE_STRING <>
HomeDirectory           UNICODE_STRING <>
FullName                UNICODE_STRING <>
ProfilePath             UNICODE_STRING <>
HomeDirectoryDrive      UNICODE_STRING <>
LogonServer             UNICODE_STRING <>
UserFlags               ULONG ?
KERB_INTERACTIVE_PROFILE ends
PKERB_INTERACTIVE_PROFILE typedef ptr KERB_INTERACTIVE_PROFILE

KERB_SMART_CARD_PROFILE struct
Profile                 KERB_INTERACTIVE_PROFILE <>
CertificateSize         ULONG ?
CertificateData         PUCHAR ?
KERB_SMART_CARD_PROFILE ends
PKERB_SMART_CARD_PROFILE typedef ptr KERB_SMART_CARD_PROFILE

KERB_CRYPTO_KEY         struct
KeyType                 LONG ?
Length                  ULONG ?
Value                   PUCHAR ?
KERB_CRYPTO_KEY         ends
PKERB_CRYPTO_KEY        typedef ptr KERB_CRYPTO_KEY

KERB_CRYPTO_KEY32       struct
KeyType                 LONG ?
Length                  ULONG ?
Offs                    ULONG ?
KERB_CRYPTO_KEY32       ends
PKERB_CRYPTO_KEY32      typedef ptr KERB_CRYPTO_KEY32

KERB_TICKET_PROFILE     struct
Profile                 KERB_INTERACTIVE_PROFILE <>
SessionKey              KERB_CRYPTO_KEY <>
KERB_TICKET_PROFILE     ends
PKERB_TICKET_PROFILE    typedef ptr KERB_TICKET_PROFILE

.enum KERB_PROTOCOL_MESSAGE_TYPE {
    KerbDebugRequestMessage = 0,
    KerbQueryTicketCacheMessage,
    KerbChangeMachinePasswordMessage,
    KerbVerifyPacMessage,
    KerbRetrieveTicketMessage,
    KerbUpdateAddressesMessage,
    KerbPurgeTicketCacheMessage,
    KerbChangePasswordMessage,
    KerbRetrieveEncodedTicketMessage,
    KerbDecryptDataMessage,
    KerbAddBindingCacheEntryMessage,
    KerbSetPasswordMessage,
    KerbSetPasswordExMessage,
if (_WIN32_WINNT eq 0x0500)
    KerbAddExtraCredentialsMessage = 17
endif
if (_WIN32_WINNT ge 0x0501)
    KerbVerifyCredentialsMessage,
    KerbQueryTicketCacheExMessage,
    KerbPurgeTicketCacheExMessage,
endif
if (_WIN32_WINNT ge 0x0502)
    KerbRefreshSmartcardCredentialsMessage,
    KerbAddExtraCredentialsMessage,
    KerbQuerySupplementalCredentialsMessage,
endif
if (_WIN32_WINNT ge 0x0600)
    KerbTransferCredentialsMessage,
    KerbQueryTicketCacheEx2Message,
    KerbSubmitTicketMessage,
    KerbAddExtraCredentialsExMessage,
endif
if (_WIN32_WINNT ge 0x0602)
    KerbQueryKdcProxyCacheMessage,
    KerbPurgeKdcProxyCacheMessage,
    KerbQueryTicketCacheEx3Message,
    KerbCleanupMachinePkinitCredsMessage,
    KerbAddBindingCacheEntryExMessage,
    KerbQueryBindingCacheMessage,
    KerbPurgeBindingCacheMessage,
    KerbPinKdcMessage,
    KerbUnpinAllKdcsMessage,
    KerbQueryDomainExtendedPoliciesMessage,
    KerbQueryS4U2ProxyCacheMessage,
endif
if (_WIN32_WINNT ge 0x0A00)
    KerbRetrieveKeyTabMessage,
endif
}

KERB_QUERY_TKT_CACHE_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
KERB_QUERY_TKT_CACHE_REQUEST ends
PKERB_QUERY_TKT_CACHE_REQUEST typedef ptr KERB_QUERY_TKT_CACHE_REQUEST

KERB_TICKET_CACHE_INFO  struct
ServerName              UNICODE_STRING <>
RealmName               UNICODE_STRING <>
StartTime               LARGE_INTEGER <>
EndTime                 LARGE_INTEGER <>
RenewTime               LARGE_INTEGER <>
EncryptionType          LONG ?
TicketFlags             ULONG ?
KERB_TICKET_CACHE_INFO  ends
PKERB_TICKET_CACHE_INFO typedef ptr KERB_TICKET_CACHE_INFO

if (_WIN32_WINNT ge 0x0501)
KERB_TICKET_CACHE_INFO_EX struct
ClientName              UNICODE_STRING <>
ClientRealm             UNICODE_STRING <>
ServerName              UNICODE_STRING <>
ServerRealm             UNICODE_STRING <>
StartTime               LARGE_INTEGER <>
EndTime                 LARGE_INTEGER <>
RenewTime               LARGE_INTEGER <>
EncryptionType          LONG ?
TicketFlags             ULONG ?
KERB_TICKET_CACHE_INFO_EX ends
PKERB_TICKET_CACHE_INFO_EX typedef ptr KERB_TICKET_CACHE_INFO_EX
endif

KERB_TICKET_CACHE_INFO_EX2 struct
ClientName              UNICODE_STRING <>
ClientRealm             UNICODE_STRING <>
ServerName              UNICODE_STRING <>
ServerRealm             UNICODE_STRING <>
StartTime               LARGE_INTEGER <>
EndTime                 LARGE_INTEGER <>
RenewTime               LARGE_INTEGER <>
EncryptionType          LONG ?
TicketFlags             ULONG ?
SessionKeyType          ULONG ?
BranchId                ULONG ?
KERB_TICKET_CACHE_INFO_EX2 ends
PKERB_TICKET_CACHE_INFO_EX2 typedef ptr KERB_TICKET_CACHE_INFO_EX2

if (_WIN32_WINNT ge 0x0602)
KERB_TICKET_CACHE_INFO_EX3 struct
ClientName              UNICODE_STRING ?
ClientRealm             UNICODE_STRING ?
ServerName              UNICODE_STRING ?
ServerRealm             UNICODE_STRING ?
StartTime               LARGE_INTEGER <>
EndTime                 LARGE_INTEGER <>
RenewTime               LARGE_INTEGER <>
EncryptionType          LONG ?
TicketFlags             ULONG ?
SessionKeyType          ULONG ?
BranchId                ULONG ?
CacheFlags              ULONG ?
KdcCalled               UNICODE_STRING ?
KERB_TICKET_CACHE_INFO_EX3 ends
PKERB_TICKET_CACHE_INFO_EX3 typedef ptr KERB_TICKET_CACHE_INFO_EX3
endif

KERB_QUERY_TKT_CACHE_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfTickets          ULONG ?
Tickets                 KERB_TICKET_CACHE_INFO ANYSIZE_ARRAY dup(<>)
KERB_QUERY_TKT_CACHE_RESPONSE ends
PKERB_QUERY_TKT_CACHE_RESPONSE typedef ptr KERB_QUERY_TKT_CACHE_RESPONSE

if (_WIN32_WINNT ge 0x0502)
KERB_QUERY_TKT_CACHE_EX_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfTickets          ULONG ?
Tickets                 KERB_TICKET_CACHE_INFO_EX ANYSIZE_ARRAY dup(<>)
KERB_QUERY_TKT_CACHE_EX_RESPONSE ends
PKERB_QUERY_TKT_CACHE_EX_RESPONSE typedef ptr KERB_QUERY_TKT_CACHE_EX_RESPONSE
endif

KERB_QUERY_TKT_CACHE_EX2_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfTickets          ULONG ?
Tickets                 KERB_TICKET_CACHE_INFO_EX2 ANYSIZE_ARRAY dup(<>)
KERB_QUERY_TKT_CACHE_EX2_RESPONSE ends
PKERB_QUERY_TKT_CACHE_EX2_RESPONSE typedef ptr KERB_QUERY_TKT_CACHE_EX2_RESPONSE

if (_WIN32_WINNT ge 0x0602)
KERB_QUERY_TKT_CACHE_EX3_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfTickets          ULONG ?
Tickets                 KERB_TICKET_CACHE_INFO_EX3 ANYSIZE_ARRAY dup(?)
KERB_QUERY_TKT_CACHE_EX3_RESPONSE ends
PKERB_QUERY_TKT_CACHE_EX3_RESPONSE typedef ptr KERB_QUERY_TKT_CACHE_EX3_RESPONSE
endif

ifndef __SECHANDLE_DEFINED__
define __SECHANDLE_DEFINED__
SecHandle               struct
dwLower                 ULONG_PTR ?
dwUpper                 ULONG_PTR ?
SecHandle               ends
PSecHandle              typedef ptr SecHandle
endif

if (_WIN32_WINNT ge 0x0501)
define KERB_USE_DEFAULT_TICKET_FLAGS       0x0

define KERB_RETRIEVE_TICKET_DEFAULT           0x0
endif
define KERB_RETRIEVE_TICKET_DONT_USE_CACHE    0x1
define KERB_RETRIEVE_TICKET_USE_CACHE_ONLY    0x2
define KERB_RETRIEVE_TICKET_USE_CREDHANDLE    0x4
if (_WIN32_WINNT ge 0x0501)
define KERB_RETRIEVE_TICKET_AS_KERB_CRED      0x8
define KERB_RETRIEVE_TICKET_WITH_SEC_CRED    0x10
endif
if (_WIN32_WINNT ge 0x0600)
define KERB_RETRIEVE_TICKET_CACHE_TICKET     0x20
endif

if (_WIN32_WINNT ge 0x0601)
define KERB_RETRIEVE_TICKET_MAX_LIFETIME     0x40
endif

if (_WIN32_WINNT ge 0x0501)
define KERB_ETYPE_DEFAULT 0x0

KERB_AUTH_DATA          struct
Type                    ULONG ?
Length                  ULONG ?
Data                    PUCHAR ?
KERB_AUTH_DATA          ends
PKERB_AUTH_DATA         typedef ptr KERB_AUTH_DATA

KERB_NET_ADDRESS        struct
Family                  ULONG ?
Length                  ULONG ?
Address                 PCHAR ?
KERB_NET_ADDRESS        ends
PKERB_NET_ADDRESS       typedef ptr KERB_NET_ADDRESS

KERB_NET_ADDRESSES      struct
Number                  ULONG ?
Addresses               KERB_NET_ADDRESS ANYSIZE_ARRAY dup(<>)
KERB_NET_ADDRESSES      ends
PKERB_NET_ADDRESSES     typedef ptr KERB_NET_ADDRESSES
endif

KERB_EXTERNAL_NAME      struct
NameType                sword ?
NameCount               USHORT ?
Names                   UNICODE_STRING ANYSIZE_ARRAY dup(<>)
KERB_EXTERNAL_NAME      ends
PKERB_EXTERNAL_NAME     typedef ptr KERB_EXTERNAL_NAME

KERB_EXTERNAL_TICKET    struct
ServiceName             PKERB_EXTERNAL_NAME ?
TargetName              PKERB_EXTERNAL_NAME ?
ClientName              PKERB_EXTERNAL_NAME ?
DomainName              UNICODE_STRING <>
TargetDomainName        UNICODE_STRING <>
AltTargetDomainName     UNICODE_STRING <>
SessionKey              KERB_CRYPTO_KEY <>
TicketFlags             ULONG ?
Flags                   ULONG ?
KeyExpirationTime       LARGE_INTEGER <>
StartTime               LARGE_INTEGER <>
EndTime                 LARGE_INTEGER <>
RenewUntil              LARGE_INTEGER <>
TimeSkew                LARGE_INTEGER <>
EncodedTicketSize       ULONG ?
EncodedTicket           PUCHAR ?
KERB_EXTERNAL_TICKET    ends
PKERB_EXTERNAL_TICKET   typedef ptr KERB_EXTERNAL_TICKET

KERB_RETRIEVE_TKT_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
TargetName              UNICODE_STRING <>
TicketFlags             ULONG ?
CacheOptions            ULONG ?
EncryptionType          LONG ?
CredentialsHandle       SecHandle <>
KERB_RETRIEVE_TKT_REQUEST ends
PKERB_RETRIEVE_TKT_REQUEST typedef ptr KERB_RETRIEVE_TKT_REQUEST

KERB_RETRIEVE_TKT_RESPONSE struct
Ticket                  KERB_EXTERNAL_TICKET <>
KERB_RETRIEVE_TKT_RESPONSE ends
PKERB_RETRIEVE_TKT_RESPONSE typedef ptr KERB_RETRIEVE_TKT_RESPONSE

KERB_PURGE_TKT_CACHE_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
ServerName              UNICODE_STRING <>
RealmName               UNICODE_STRING <>
KERB_PURGE_TKT_CACHE_REQUEST ends
PKERB_PURGE_TKT_CACHE_REQUEST typedef ptr KERB_PURGE_TKT_CACHE_REQUEST

if (_WIN32_WINNT ge 0x0501)

define KERB_PURGE_ALL_TICKETS 1

KERB_PURGE_TKT_CACHE_EX_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
Flags                   ULONG ?
TicketTemplate          KERB_TICKET_CACHE_INFO_EX <>
KERB_PURGE_TKT_CACHE_EX_REQUEST ends
PKERB_PURGE_TKT_CACHE_EX_REQUEST typedef ptr KERB_PURGE_TKT_CACHE_EX_REQUEST
endif

KERB_SUBMIT_TKT_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
Flags                   ULONG ?
Key                     KERB_CRYPTO_KEY32 <>
KerbCredSize            ULONG ?
KerbCredOffset          ULONG ?
KERB_SUBMIT_TKT_REQUEST ends
PKERB_SUBMIT_TKT_REQUEST typedef ptr KERB_SUBMIT_TKT_REQUEST

if (_WIN32_WINNT ge 0x0602)

KERB_QUERY_KDC_PROXY_CACHE_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
Flags                   ULONG ?
LogonId                 LUID <>
KERB_QUERY_KDC_PROXY_CACHE_REQUEST ends
PKERB_QUERY_KDC_PROXY_CACHE_REQUEST typedef ptr KERB_QUERY_KDC_PROXY_CACHE_REQUEST

KDC_PROXY_CACHE_ENTRY_DATA struct
SinceLastUsed           ULONG64 ?
DomainName              UNICODE_STRING ?
ProxyServerName         UNICODE_STRING ?
ProxyServerVdir         UNICODE_STRING ?
ProxyServerPort         USHORT ?
LogonId                 LUID <>
CredUserName            UNICODE_STRING ?
CredDomainName          UNICODE_STRING ?
GlobalCache             BOOLEAN ?
KDC_PROXY_CACHE_ENTRY_DATA ends
PKDC_PROXY_CACHE_ENTRY_DATA typedef ptr KDC_PROXY_CACHE_ENTRY_DATA

KERB_QUERY_KDC_PROXY_CACHE_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfEntries          ULONG ?
Entries                 PKDC_PROXY_CACHE_ENTRY_DATA ?
KERB_QUERY_KDC_PROXY_CACHE_RESPONSE ends
PKERB_QUERY_KDC_PROXY_CACHE_RESPONSE typedef ptr KERB_QUERY_KDC_PROXY_CACHE_RESPONSE

KERB_PURGE_KDC_PROXY_CACHE_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
Flags                   ULONG ?
LogonId                 LUID <>
KERB_PURGE_KDC_PROXY_CACHE_REQUEST ends
PKERB_PURGE_KDC_PROXY_CACHE_REQUEST typedef ptr KERB_PURGE_KDC_PROXY_CACHE_REQUEST

KERB_PURGE_KDC_PROXY_CACHE_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfPurged           ULONG ?
KERB_PURGE_KDC_PROXY_CACHE_RESPONSE ends
PKERB_PURGE_KDC_PROXY_CACHE_RESPONSE typedef ptr KERB_PURGE_KDC_PROXY_CACHE_RESPONSE

define KERB_S4U2PROXY_CACHE_ENTRY_INFO_FLAG_NEGATIVE 0x1

KERB_S4U2PROXY_CACHE_ENTRY_INFO struct
ServerName              UNICODE_STRING ?
Flags                   ULONG ?
LastStatus              NTSTATUS ?
Expiry                  LARGE_INTEGER <>
KERB_S4U2PROXY_CACHE_ENTRY_INFO ends
PKERB_S4U2PROXY_CACHE_ENTRY_INFO typedef ptr KERB_S4U2PROXY_CACHE_ENTRY_INFO

define KERB_S4U2PROXY_CRED_FLAG_NEGATIVE 0x1

KERB_S4U2PROXY_CRED     struct
UserName                UNICODE_STRING ?
DomainName              UNICODE_STRING ?
Flags                   ULONG ?
LastStatus              NTSTATUS ?
Expiry                  LARGE_INTEGER <>
CountOfEntries          ULONG ?
Entries                 PKERB_S4U2PROXY_CACHE_ENTRY_INFO ?
KERB_S4U2PROXY_CRED     ends
PKERB_S4U2PROXY_CRED    typedef ptr KERB_S4U2PROXY_CRED

KERB_QUERY_S4U2PROXY_CACHE_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
Flags                   ULONG ?
LogonId                 LUID <>
KERB_QUERY_S4U2PROXY_CACHE_REQUEST ends
PKERB_QUERY_S4U2PROXY_CACHE_REQUEST typedef ptr KERB_QUERY_S4U2PROXY_CACHE_REQUEST

KERB_QUERY_S4U2PROXY_CACHE_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfCreds            ULONG ?
Creds                   PKERB_S4U2PROXY_CRED ?
KERB_QUERY_S4U2PROXY_CACHE_RESPONSE ends
PKERB_QUERY_S4U2PROXY_CACHE_RESPONSE typedef ptr KERB_QUERY_S4U2PROXY_CACHE_RESPONSE

endif

if (_WIN32_WINNT ge 0x0A00)

KERB_RETRIEVE_KEY_TAB_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
Flags                   ULONG ?
UserName                UNICODE_STRING ?
DomainName              UNICODE_STRING ?
Password                UNICODE_STRING ?
KERB_RETRIEVE_KEY_TAB_REQUEST ends
PKERB_RETRIEVE_KEY_TAB_REQUEST typedef ptr KERB_RETRIEVE_KEY_TAB_REQUEST

KERB_RETRIEVE_KEY_TAB_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
KeyTabLength            ULONG ?
KeyTab                  PUCHAR ?
KERB_RETRIEVE_KEY_TAB_RESPONSE ends
PKERB_RETRIEVE_KEY_TAB_RESPONSE typedef ptr KERB_RETRIEVE_KEY_TAB_RESPONSE

endif

KERB_CHANGEPASSWORD_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
DomainName              UNICODE_STRING <>
AccountName             UNICODE_STRING <>
OldPassword             UNICODE_STRING <>
NewPassword             UNICODE_STRING <>
Impersonating           BOOLEAN ?
KERB_CHANGEPASSWORD_REQUEST ends
PKERB_CHANGEPASSWORD_REQUEST typedef ptr KERB_CHANGEPASSWORD_REQUEST

KERB_SETPASSWORD_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
CredentialsHandle       SecHandle <>
Flags                   ULONG ?
DomainName              UNICODE_STRING <>
AccountName             UNICODE_STRING <>
Password                UNICODE_STRING <>
KERB_SETPASSWORD_REQUEST ends
PKERB_SETPASSWORD_REQUEST typedef ptr KERB_SETPASSWORD_REQUEST

KERB_SETPASSWORD_EX_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
CredentialsHandle       SecHandle <>
Flags                   ULONG ?
AccountRealm            UNICODE_STRING <>
AccountName             UNICODE_STRING <>
Password                UNICODE_STRING <>
ClientRealm             UNICODE_STRING <>
ClientName              UNICODE_STRING <>
Impersonating           BOOLEAN ?
KdcAddress              UNICODE_STRING <>
KdcAddressType          ULONG ?
KERB_SETPASSWORD_EX_REQUEST ends
PKERB_SETPASSWORD_EX_REQUEST typedef ptr KERB_SETPASSWORD_EX_REQUEST

define DS_UNKNOWN_ADDRESS_TYPE         0
define KERB_SETPASS_USE_LOGONID        1
define KERB_SETPASS_USE_CREDHANDLE     2

KERB_DECRYPT_REQUEST    struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
Flags                   ULONG ?
CryptoType              LONG ?
KeyUsage                LONG ?
Key                     KERB_CRYPTO_KEY <>
EncryptedDataSize       ULONG ?
InitialVectorSize       ULONG ?
InitialVector           PUCHAR ?
EncryptedData           PUCHAR ?
KERB_DECRYPT_REQUEST    ends
PKERB_DECRYPT_REQUEST   typedef ptr KERB_DECRYPT_REQUEST

define KERB_DECRYPT_FLAG_DEFAULT_KEY   0x00000001

KERB_DECRYPT_RESPONSE   struct
DecryptedData           UCHAR ANYSIZE_ARRAY dup(?)
KERB_DECRYPT_RESPONSE   ends
PKERB_DECRYPT_RESPONSE  typedef ptr KERB_DECRYPT_RESPONSE

KERB_ADD_BINDING_CACHE_ENTRY_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
RealmName               UNICODE_STRING <>
KdcAddress              UNICODE_STRING <>
AddressType             ULONG ?
KERB_ADD_BINDING_CACHE_ENTRY_REQUEST ends
PKERB_ADD_BINDING_CACHE_ENTRY_REQUEST typedef ptr KERB_ADD_BINDING_CACHE_ENTRY_REQUEST

if (_WIN32_WINNT ge 0x0502)
KERB_REFRESH_SCCRED_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CredentialBlob          UNICODE_STRING <>
LogonId                 LUID <>
Flags                   ULONG ?
KERB_REFRESH_SCCRED_REQUEST ends
PKERB_REFRESH_SCCRED_REQUEST typedef ptr KERB_REFRESH_SCCRED_REQUEST

define KERB_REFRESH_SCCRED_RELEASE             0x0
define KERB_REFRESH_SCCRED_GETTGT              0x1
endif

if (_WIN32_WINNT ne 0x0501)

KERB_ADD_CREDENTIALS_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
UserName                UNICODE_STRING <>
DomainName              UNICODE_STRING <>
Password                UNICODE_STRING <>
LogonId                 LUID <>
Flags                   ULONG ?
KERB_ADD_CREDENTIALS_REQUEST ends
PKERB_ADD_CREDENTIALS_REQUEST typedef ptr KERB_ADD_CREDENTIALS_REQUEST

define KERB_REQUEST_ADD_CREDENTIAL     1
define KERB_REQUEST_REPLACE_CREDENTIAL 2
define KERB_REQUEST_REMOVE_CREDENTIAL  4
endif

if (_WIN32_WINNT ge 0x0600)

KERB_ADD_CREDENTIALS_REQUEST_EX struct
Credentials             KERB_ADD_CREDENTIALS_REQUEST <>
PrincipalNameCount      ULONG ?
PrincipalNames          UNICODE_STRING ANYSIZE_ARRAY dup(<>)
KERB_ADD_CREDENTIALS_REQUEST_EX ends
PKERB_ADD_CREDENTIALS_REQUEST_EX typedef ptr KERB_ADD_CREDENTIALS_REQUEST_EX

endif

KERB_TRANSFER_CRED_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
OriginLogonId           LUID <>
DestinationLogonId      LUID <>
Flags                   ULONG ?
KERB_TRANSFER_CRED_REQUEST ends
PKERB_TRANSFER_CRED_REQUEST typedef ptr KERB_TRANSFER_CRED_REQUEST

define KERB_TRANSFER_CRED_WITH_TICKETS        0x1
define KERB_TRANSFER_CRED_CLEANUP_CREDENTIALS 0x2

if (_WIN32_WINNT ge 0x0602)

KERB_CLEANUP_MACHINE_PKINIT_CREDS_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
LogonId                 LUID <>
KERB_CLEANUP_MACHINE_PKINIT_CREDS_REQUEST ends
PKERB_CLEANUP_MACHINE_PKINIT_CREDS_REQUEST typedef ptr KERB_CLEANUP_MACHINE_PKINIT_CREDS_REQUEST

endif

if (_WIN32_WINNT ge 0x0602)

KERB_BINDING_CACHE_ENTRY_DATA struct
DiscoveryTime           ULONG64 ?
RealmName               UNICODE_STRING ?
KdcAddress              UNICODE_STRING ?
AddressType             ULONG ?
Flags                   ULONG ?
DcFlags                 ULONG ?
CacheFlags              ULONG ?
KdcName                 UNICODE_STRING ?
KERB_BINDING_CACHE_ENTRY_DATA ends
PKERB_BINDING_CACHE_ENTRY_DATA typedef ptr KERB_BINDING_CACHE_ENTRY_DATA

KERB_QUERY_BINDING_CACHE_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
CountOfEntries          ULONG ?
Entries                 PKERB_BINDING_CACHE_ENTRY_DATA ?
KERB_QUERY_BINDING_CACHE_RESPONSE ends
PKERB_QUERY_BINDING_CACHE_RESPONSE typedef ptr KERB_QUERY_BINDING_CACHE_RESPONSE

KERB_ADD_BINDING_CACHE_ENTRY_EX_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
RealmName               UNICODE_STRING ?
KdcAddress              UNICODE_STRING ?
AddressType             ULONG ?
DcFlags                 ULONG ?
KERB_ADD_BINDING_CACHE_ENTRY_EX_REQUEST ends
PKERB_ADD_BINDING_CACHE_ENTRY_EX_REQUEST typedef ptr KERB_ADD_BINDING_CACHE_ENTRY_EX_REQUEST

KERB_QUERY_BINDING_CACHE_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
KERB_QUERY_BINDING_CACHE_REQUEST ends
PKERB_QUERY_BINDING_CACHE_REQUEST typedef ptr KERB_QUERY_BINDING_CACHE_REQUEST

KERB_PURGE_BINDING_CACHE_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
KERB_PURGE_BINDING_CACHE_REQUEST ends
PKERB_PURGE_BINDING_CACHE_REQUEST typedef ptr KERB_PURGE_BINDING_CACHE_REQUEST

KERB_QUERY_DOMAIN_EXTENDED_POLICIES_REQUEST struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
Flags                   ULONG ?
DomainName              UNICODE_STRING ?
KERB_QUERY_DOMAIN_EXTENDED_POLICIES_REQUEST ends
PKERB_QUERY_DOMAIN_EXTENDED_POLICIES_REQUEST typedef ptr KERB_QUERY_DOMAIN_EXTENDED_POLICIES_REQUEST

define KERB_QUERY_DOMAIN_EXTENDED_POLICIES_RESPONSE_FLAG_DAC_DISABLED  0x1

KERB_QUERY_DOMAIN_EXTENDED_POLICIES_RESPONSE struct
MessageType             KERB_PROTOCOL_MESSAGE_TYPE ?
Flags                   ULONG ?
ExtendedPolicies        ULONG ?
DsFlags                 ULONG ?
KERB_QUERY_DOMAIN_EXTENDED_POLICIES_RESPONSE ends
PKERB_QUERY_DOMAIN_EXTENDED_POLICIES_RESPONSE typedef ptr KERB_QUERY_DOMAIN_EXTENDED_POLICIES_RESPONSE

endif

if (_WIN32_WINNT ge 0x0602)

.enum KERB_CERTIFICATE_INFO_TYPE {
    CertHashInfo = 1,
    }

KERB_CERTIFICATE_HASHINFO struct
StoreNameLength         USHORT ?
HashLength              USHORT ?
KERB_CERTIFICATE_HASHINFO ends
PKERB_CERTIFICATE_HASHINFO typedef ptr KERB_CERTIFICATE_HASHINFO

KERB_CERTIFICATE_INFO   struct
CertInfoSize            ULONG ?
InfoType                ULONG ?
KERB_CERTIFICATE_INFO   ends
PKERB_CERTIFICATE_INFO  typedef ptr KERB_CERTIFICATE_INFO

endif

POLICY_AUDIT_SID_ARRAY  struct
UsersCount              ULONG ?
UserSidArray            ptr PSID ?
POLICY_AUDIT_SID_ARRAY  ends
PPOLICY_AUDIT_SID_ARRAY typedef ptr POLICY_AUDIT_SID_ARRAY

AUDIT_POLICY_INFORMATION struct
AuditSubCategoryGuid    GUID <>
AuditingInformation     ULONG ?
AuditCategoryGuid       GUID <>
AUDIT_POLICY_INFORMATION ends
PAUDIT_POLICY_INFORMATION typedef ptr AUDIT_POLICY_INFORMATION
PCAUDIT_POLICY_INFORMATION  typedef PAUDIT_POLICY_INFORMATION
LPCAUDIT_POLICY_INFORMATION typedef PAUDIT_POLICY_INFORMATION

define AUDIT_SET_SYSTEM_POLICY                 (0x0001)
define AUDIT_QUERY_SYSTEM_POLICY               (0x0002)
define AUDIT_SET_USER_POLICY                   (0x0004)
define AUDIT_QUERY_USER_POLICY                 (0x0008)
define AUDIT_ENUMERATE_USERS                   (0x0010)
define AUDIT_SET_MISC_POLICY                   (0x0020)
define AUDIT_QUERY_MISC_POLICY                 (0x0040)

define AUDIT_GENERIC_ALL            (STANDARD_RIGHTS_REQUIRED or AUDIT_SET_SYSTEM_POLICY or AUDIT_QUERY_SYSTEM_POLICY or AUDIT_SET_USER_POLICY or AUDIT_QUERY_USER_POLICY or AUDIT_ENUMERATE_USERS or AUDIT_SET_MISC_POLICY or AUDIT_QUERY_MISC_POLICY)
define AUDIT_GENERIC_READ           (STANDARD_RIGHTS_READ or AUDIT_QUERY_SYSTEM_POLICY or AUDIT_QUERY_USER_POLICY or AUDIT_ENUMERATE_USERS or AUDIT_QUERY_MISC_POLICY)
define AUDIT_GENERIC_WRITE          (STANDARD_RIGHTS_WRITE or AUDIT_SET_USER_POLICY or AUDIT_SET_MISC_POLICY or AUDIT_SET_SYSTEM_POLICY)
define AUDIT_GENERIC_EXECUTE        (STANDARD_RIGHTS_EXECUTE)

AuditSetSystemPolicy proto WINAPI :PCAUDIT_POLICY_INFORMATION, :ULONG
AuditSetPerUserPolicy proto WINAPI :PSID, :PCAUDIT_POLICY_INFORMATION, :ULONG
AuditQuerySystemPolicy proto WINAPI :ptr, :ULONG, :ptr
AuditQueryPerUserPolicy proto WINAPI :PSID, :ptr, :ULONG, :ptr
AuditEnumeratePerUserPolicy proto WINAPI :ptr
AuditComputeEffectivePolicyBySid proto WINAPI :PSID, :ptr, :ULONG, :ptr
AuditComputeEffectivePolicyByToken proto WINAPI :HANDLE, :ptr, :ULONG, :ptr
AuditEnumerateCategories proto WINAPI :ptr ptr, :PULONG
AuditEnumerateSubCategories proto WINAPI :ptr, :BOOLEAN, :ptr ptr, :PULONG
AuditLookupCategoryNameW proto WINAPI :ptr, :ptr
AuditLookupCategoryNameA proto WINAPI :ptr, :ptr

ifdef _UNICODE
define AuditLookupCategoryName  <AuditLookupCategoryNameW>
else
define AuditLookupCategoryName  <AuditLookupCategoryNameA>
endif

AuditLookupSubCategoryNameW proto WINAPI :ptr, :ptr
AuditLookupSubCategoryNameA proto WINAPI :ptr, :ptr

ifdef _UNICODE
define AuditLookupSubCategoryName  <AuditLookupSubCategoryNameW>
else
define AuditLookupSubCategoryName  <AuditLookupSubCategoryNameA>
endif

AuditLookupCategoryIdFromCategoryGuid proto WINAPI :ptr, :PPOLICY_AUDIT_EVENT_TYPE
AuditLookupCategoryGuidFromCategoryId proto WINAPI :POLICY_AUDIT_EVENT_TYPE, :ptr
AuditSetSecurity proto WINAPI :SECURITY_INFORMATION, :PSECURITY_DESCRIPTOR
AuditQuerySecurity proto WINAPI :SECURITY_INFORMATION, :ptr
AuditSetGlobalSaclW proto WINAPI :PCWSTR, :PACL
AuditSetGlobalSaclA proto WINAPI :PCSTR, :PACL

ifdef _UNICODE
define AuditSetGlobalSacl <AuditSetGlobalSaclW>
else
define AuditSetGlobalSacl <AuditSetGlobalSaclA>
endif

AuditQueryGlobalSaclW proto WINAPI :PCWSTR, :ptr
AuditQueryGlobalSaclA proto WINAPI :PCSTR, :ptr

ifdef _UNICODE
define AuditQueryGlobalSacl <AuditQueryGlobalSaclW>
else
define AuditQueryGlobalSacl <AuditQueryGlobalSaclA>
endif

AuditFree proto WINAPI :PVOID

if (_WIN32_WINNT ge 0x0601)

define PKU2U_PACKAGE_NAME_A          <"pku2u">
define PKU2U_PACKAGE_NAME            <L"pku2u">
define PKU2U_PACKAGE_NAME_W          PKU2U_PACKAGE_NAME

endif

if (_WIN32_WINNT ge 0x0601)

PKU2U_CERT_BLOB         struct
CertOffset              ULONG ?
CertLength              USHORT ?
PKU2U_CERT_BLOB         ends
PPKU2U_CERT_BLOB        typedef ptr PKU2U_CERT_BLOB

define PKU2U_CREDUI_CONTEXT_VERSION  0x4154414454524543

PKU2U_CREDUI_CONTEXT    struct
Version                 ULONG64 ?
cbHeaderLength          USHORT ?
cbStructureLength       ULONG ?
CertArrayCount          USHORT ?
CertArrayOffset         ULONG ?
PKU2U_CREDUI_CONTEXT    ends
PPKU2U_CREDUI_CONTEXT   typedef ptr PKU2U_CREDUI_CONTEXT

.enum PKU2U_LOGON_SUBMIT_TYPE {
    Pku2uCertificateS4ULogon = 14,
    }

PKU2U_CERTIFICATE_S4U_LOGON struct
MessageType             PKU2U_LOGON_SUBMIT_TYPE ?
Flags                   ULONG ?
UserPrincipalName       UNICODE_STRING <>
DomainName              UNICODE_STRING <>
CertificateLength       ULONG ?
Certificate             PUCHAR ?
PKU2U_CERTIFICATE_S4U_LOGON ends
PPKU2U_CERTIFICATE_S4U_LOGON typedef ptr PKU2U_CERTIFICATE_S4U_LOGON

endif

endif

endif

