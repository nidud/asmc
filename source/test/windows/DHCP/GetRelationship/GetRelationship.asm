;;
;; https://github.com/microsoft/Windows-classic-samples
;;
;; Assumptions:
;;    1) There exists a relationship with the name "test"
;;

include windows.inc
include stdio.inc
include dhcpsapi.inc
include tchar.inc

    .code

    ;; This routine frees LPDHCP_FAILOVER_RELATIONSHIP and its internal elements.

    assume rbx:LPDHCP_FAILOVER_RELATIONSHIP

FreeRelationshipMemory proc uses rbx pFailRel:LPDHCP_FAILOVER_RELATIONSHIP

    mov rbx,pFailRel

    .if rbx

        ;; Frees relationship name

        .if ([rbx].RelationshipName)

            DhcpRpcFreeMemory([rbx].RelationshipName)
        .endif

        ;; Frees shared secret

        .if ( [rbx].SharedSecret )

            DhcpRpcFreeMemory([rbx].SharedSecret)
        .endif

        ;;Frees Primary server's name

        .if ([rbx].PrimaryServerName)

            DhcpRpcFreeMemory([rbx].PrimaryServerName)
        .endif

        ;; Frees Secondary server's name

        .if ([rbx].SecondaryServerName)

            DhcpRpcFreeMemory([rbx].SecondaryServerName)
        .endif

        ;; Frees pScopes

        .if ([rbx].pScopes)

            ;; Frees  individual elements of pScopes

            mov rdx,[rbx].pScopes
            .if([rdx].DHCP_IP_ARRAY.Elements)

                DhcpRpcFreeMemory([rdx].DHCP_IP_ARRAY.Elements)
            .endif
             DhcpRpcFreeMemory([rbx].pScopes)
        .endif

        ;; Frees the relationship
        DhcpRpcFreeMemory(rbx)
        mov pFailRel,NULL

    .endif
    ret

FreeRelationshipMemory endp

wmain proc

    .new pRelationShip:LPDHCP_FAILOVER_RELATIONSHIP = NULL  ;; Failover relationship
    .new pwszServer:LPWSTR           = NULL                 ;; Server IP Address
    .new pwszRelationshipName:LPWSTR = "test"               ;; Relationship name to be fetched
    .new dwError:DWORD               = ERROR_SUCCESS        ;; Variable to hold error code

     mov dwError,DhcpV4FailoverGetRelationship(
        pwszServer,           ;; Server IP Address, if NULL, reflects the current server (where the program is executed)
        pwszRelationshipName, ;; Relationship name
        &pRelationShip        ;; Failover relationship
        )

    .if ( dwError != ERROR_SUCCESS)

        wprintf("DhcpV4FailoverGetRelationship failed with Error = %d\n", dwError)
    .endif

    FreeRelationshipMemory(pRelationShip)
    .return 0

wmain endp

    end _tstart
