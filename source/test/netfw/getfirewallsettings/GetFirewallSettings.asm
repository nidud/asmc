; GETFIREWALLSETTINGS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Change history:
; 2021-08-08 - converted from GetFirewallSettings.cpp
;
; Abstract:
;    This C++ file includes sample code for reading Windows Firewall
;    Settings per profile using the Microsoft Windows Firewall APIs.
;

include windows.inc
include stdio.inc
include netfw.inc
include tchar.inc

ifdef __PE__
.data
 IID_INetFwPolicy2  IID _IID_INetFwPolicy2
 CLSID_NetFwPolicy2 IID _CLSID_NetFwPolicy2
endif

.code

SUCCESS proto fastcall hr:int_t {
    retm<(sdword ptr ecx !>= 0)>
    }

; Instantiate INetFwPolicy2

WFCOMInitialize proc ppNetFwPolicy2:ptr ptr INetFwPolicy2

   .new hr:HRESULT = S_OK
    mov hr,CoCreateInstance(&CLSID_NetFwPolicy2, NULL, CLSCTX_INPROC_SERVER,
            &IID_INetFwPolicy2, ppNetFwPolicy2)
    .if (FAILED(hr))

        printf("CoCreateInstance for INetFwPolicy2 failed: 0x%08lx\n", hr)
    .endif
    .return hr

WFCOMInitialize endp

get_enabled proto Enabled:VARIANT_BOOL {
    lea rax,@CStr("disabled")
    .if ( ecx )
        lea rax,@CStr("enabled")
    .endif
    }

get_allowed proto action:NET_FW_ACTION {
    lea rax,@CStr("Block")
    .if ( ecx != NET_FW_ACTION_BLOCK )
        lea rax,@CStr("Allow")
    .endif
    }

Get_FirewallSettings_PerProfileType proc ProfileTypePassed:NET_FW_PROFILE_TYPE2, pNetFwPolicy2:ptr INetFwPolicy2

   .new bIsEnabled:VARIANT_BOOL = FALSE
   .new action:NET_FW_ACTION

    printf("******************************************\n")

    .if (SUCCESS(pNetFwPolicy2.get_FirewallEnabled(ProfileTypePassed, &bIsEnabled)))

        printf("Firewall is %s\n", get_enabled(bIsEnabled))
    .endif
    .if (SUCCESS(pNetFwPolicy2.get_BlockAllInboundTraffic(ProfileTypePassed, &bIsEnabled)))

        printf("Block all inbound traffic is %s\n", get_enabled(bIsEnabled))
    .endif
    .if (SUCCESS(pNetFwPolicy2.get_NotificationsDisabled(ProfileTypePassed, &bIsEnabled)))

        printf("Notifications are %s\n", get_enabled(bIsEnabled))
    .endif
    .if (SUCCESS(pNetFwPolicy2.get_UnicastResponsesToMulticastBroadcastDisabled(ProfileTypePassed, &bIsEnabled)))

        printf("UnicastResponsesToMulticastBroadcast is %s\n", get_enabled(bIsEnabled))
    .endif
    .if (SUCCESS(pNetFwPolicy2.get_DefaultInboundAction(ProfileTypePassed, &action)))

        printf("Default inbound action is %s\n", get_allowed(action))
    .endif
    .if (SUCCESS(pNetFwPolicy2.get_DefaultOutboundAction(ProfileTypePassed, &action)))

        printf("Default outbound action is %s\n", get_allowed(action))
    .endif
    printf("\n")
    ret

Get_FirewallSettings_PerProfileType endp

main proc

   .new hrComInit:HRESULT = S_OK
   .new hr:HRESULT = S_OK
   .new pNetFwPolicy2:ptr INetFwPolicy2 = NULL

    ; Initialize COM.

    mov hrComInit,CoInitializeEx(
                    0,
                    COINIT_APARTMENTTHREADED
                    )

    ; Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
    ; initialized with a different mode. Since we don't care what the mode is,
    ; we'll just use the existing mode.

    .if (hrComInit != RPC_E_CHANGED_MODE)

        .if (FAILED(hrComInit))

            printf("CoInitializeEx failed: 0x%08lx\n", hrComInit)
            jmp Cleanup
        .endif
    .endif

    ; Retrieve INetFwPolicy2

    mov hr,WFCOMInitialize(&pNetFwPolicy2)
    .if (FAILED(hr))

        jmp Cleanup
    .endif

    printf("Settings for the firewall domain profile:\n")
    Get_FirewallSettings_PerProfileType(NET_FW_PROFILE2_DOMAIN, pNetFwPolicy2)

    printf("Settings for the firewall private profile:\n")
    Get_FirewallSettings_PerProfileType(NET_FW_PROFILE2_PRIVATE, pNetFwPolicy2)

    printf("Settings for the firewall public profile:\n")
    Get_FirewallSettings_PerProfileType(NET_FW_PROFILE2_PUBLIC, pNetFwPolicy2)

Cleanup:

    ; Release INetFwPolicy2

    .if (pNetFwPolicy2 != NULL)

        pNetFwPolicy2.Release()
    .endif

    ; Uninitialize COM.

    .if (SUCCESS(hrComInit))

        CoUninitialize()
    .endif
    .return 0

main endp

    end _tstart

