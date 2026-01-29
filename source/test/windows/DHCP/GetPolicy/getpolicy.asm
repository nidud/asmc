;;
;; https://github.com/microsoft/Windows-classic-samples
;;
;; Assumptions:
;;    1) There exists a scope 10.0.0.0
;;    2) There exists a policy with the name "testPolicy" on scope 10.0.0.0

include stdio.inc
include windows.inc
include dhcpsapi.inc
include tchar.inc

    .code

;; This routine frees  LPDHCP_POLICY and its internal elements.

    assume rbx:LPDHCP_POLICY

FreeDhcpPolicyMemory proc uses rsi rdi rbx pDhcpPolicy:LPDHCP_POLICY

    mov rbx,pDhcpPolicy
    .if rbx

        ;; Frees the policy name

        .if ( [rbx].PolicyName )

            DhcpRpcFreeMemory( [rbx].PolicyName )
        .endif

        ;; Frees the policy description

        .if ( [rbx].Description )

            DhcpRpcFreeMemory( [rbx].Description )
        .endif

        ;; Frees the policy condition

        .if ( [rbx].Conditions )

            mov rsi,[rbx].Conditions
            .for ( edi = 0: edi < [rsi].DHCP_POL_COND_ARRAY.NumElements: edi++ )

                ;; Frees the vendorName holder in condition's elements, if it exists

                imul ecx,edi,DHCP_POL_COND
                add  rcx,[rsi].DHCP_POL_COND_ARRAY.Elements
                .if( [rcx].DHCP_POL_COND.VendorName )

                    DhcpRpcFreeMemory( [rcx].DHCP_POL_COND.VendorName )
                .endif

                ;; Frees the "bytes" used for storing condition values

                imul ecx,edi,DHCP_POL_COND
                add  rcx,[rsi].DHCP_POL_COND_ARRAY.Elements
                .if ( [rcx].DHCP_POL_COND.Value )

                    DhcpRpcFreeMemory( [rcx].DHCP_POL_COND.Value )
                .endif
            .endf
            DhcpRpcFreeMemory( [rbx].Conditions )
        .endif

        ;; Frees the policy expression

        .if ( [rbx].Expressions )

            ;; Frees the expression elements, if they exist

            mov rsi,[rbx].Expressions
            .if ( [rsi].DHCP_POL_EXPR_ARRAY.NumElements && [rsi].DHCP_POL_EXPR_ARRAY.Elements )

                DhcpRpcFreeMemory( [rsi].DHCP_POL_EXPR_ARRAY.Elements )
            .endif
            DhcpRpcFreeMemory( [rbx].Expressions )
        .endif

        ;; Frees the policy ranges

        .if ( [rbx].Ranges )

            ;; Frees the individual range elements

            mov rsi,[rbx].Ranges
            .if ( [rsi].DHCP_IP_RANGE_ARRAY.Elements )

                DhcpRpcFreeMemory( [rsi].DHCP_IP_RANGE_ARRAY.Elements )
            .endif
            DhcpRpcFreeMemory( [rbx].Ranges )
        .endif

        ;; Finally frees the policy structure

        DhcpRpcFreeMemory( rbx )
        mov pDhcpPolicy,NULL

    .endif
    ret

FreeDhcpPolicyMemory endp

wmain proc

  .new pPolicy:LPDHCP_POLICY = NULL             ;; Policy structure, this will hold the policies obtained from DhcpV4GetPolicy
  .new pwszServer:LPWSTR     = NULL             ;; NULL signifies current server
  .new dwScope:DWORD         = 0xa000000        ;; (10.0.0.0) Subnet address
  .new dwError:DWORD         = ERROR_SUCCESS    ;; Variable to hold the error code
  .new pwszName:LPWSTR       = "testPolicy"     ;; Name of the policy

    mov dwError,DhcpV4GetPolicy(
        pwszServer,     ;; Server IP Address, NULL signifies the current server (where the program is executed)
        0,              ;; fGlobalPolicy, TRUE means a global policy, for a global policy SubnetAddress is 0.
        dwScope,        ;; Subnet address, if it is a global policy, its value is 0
        pwszName,       ;; Name of the policy
        &pPolicy        ;; Policy structure obtained from the server
        )

    .if (dwError != ERROR_SUCCESS)

        ;; DhcpV4GetPolicy returned error.
        wprintf( "DhcpV4GetPolicy failed with error %d\n", dwError )
        .return 0
    .endif

    FreeDhcpPolicyMemory( pPolicy )
    .return 0

wmain endp

    end _tstart
