;
; From the Win7 SDK -- netshare.c
;
; Test case for Lan Manager API headers (lm.inc) and
; mixed Unicode/ASCII output using printf("char %ls", ptr wchar_t)
;
; Additional format:
;
; '%C' -- ISO wide character
; '%S' -- ISO wide character string
;
include windows.inc
include lm.inc
include stdio.inc

RTN_OK      equ 0
RTN_USAGE   equ 1
RTN_ERROR   equ 13

;;
;; Note: UNICODE entry point and argv.  This way, we don't need to bother
;; with converting commandline args to Unicode
;;
.code

wmain proc argc:SINT, argv:ptr wchar_t

    local DirectoryToShare:LPWSTR
    local Sharename:LPWSTR
    local Username:LPWSTR
    local Server:LPWSTR

    local pSid:PSID
    local cbSid:DWORD

    local RefDomain[DNLEN + 1]:WCHAR
    local cchDomain:DWORD
    local peUse:SID_NAME_USE

    local sd:SECURITY_DESCRIPTOR
    local pDacl:PACL
    local dwAclSize:DWORD

    local si502:SHARE_INFO_502
    local nas:NET_API_STATUS

    local bSuccess:BOOL ;; assume this function fails
    local psidTemp:PSID

    mov bSuccess,FALSE
    mov pDacl,NULL
    mov cchDomain,DNLEN + 1
    mov pSid,NULL

    mov rsi,argv

    .repeat

        .if argc < 4

            mov rbx,[rsi]
            printf("Usage: %ls <directory> <sharename> <user/group> [\\\\Server]\n", rbx)
            printf(" directory is fullpath of directory to share\n")
            printf(" sharename is name of share on server\n")
            printf(" user/group is an WinNT user/groupname (REDMOND\\sfield, Administrators, etc)\n")
            printf(" optional Server is the name of the computer to create the share on\n")
            printf("\nExample: %ls c:\\public public Everyone\n", rbx)
            printf("c:\\public shared as public granting Everyone full access\n")
            printf("\nExample: %ls c:\\private cool$ REDMOND\\sfield \\\\WINBASE\n", rbx)
            printf("c:\\private on \\\\WINBASE shared as cool$ (hidden) granting REDMOND\\sfield access\n")
            mov eax,RTN_USAGE
            .break
        .endif

        ;;
        ;; since the commandline was Unicode, just provide pointers to
        ;; the relevant items
        ;;

        mov rax,[rsi+1*size_t]
        mov DirectoryToShare,rax
        mov rax,[rsi+2*size_t]
        mov Sharename,rax
        mov rax,[rsi+3*size_t]
        mov Username,rax

        .if argc > 4
            mov rax,[rsi+4*size_t]
            mov Server,rax
        .else
            mov Server,NULL ;; local machine
        .endif

        ;;
        ;; initial allocation attempt for Sid
        ;;
        SID_SIZE equ 96
        mov cbSid,SID_SIZE

        mov pSid,HeapAlloc(GetProcessHeap(), 0, cbSid)
        .if (pSid == NULL)
            printf("HeapAlloc error!\n");
            mov eax,RTN_ERROR
            .break
        .endif

        .repeat
            ;;
            ;; get the Sid associated with the supplied user/group name
            ;; force Unicode API since we always pass Unicode string
            ;;
            .if !LookupAccountNameW(
                NULL,       ;; default lookup logic
                Username,   ;; user/group of interest from commandline
                pSid,       ;; Sid buffer
                &cbSid,     ;; size of Sid
                &RefDomain, ;; Domain account found on (unused)
                &cchDomain, ;; size of domain in chars
                &peUse
                )

                ;;
                ;; if the buffer wasn't large enough, try again
                ;;

                .if GetLastError() == ERROR_INSUFFICIENT_BUFFER

                    mov psidTemp,HeapReAlloc(GetProcessHeap(), 0, pSid, cbSid)

                    .if (psidTemp == NULL)
                        printf("HeapReAlloc error!\n")
                        .break
                    .else
                        mov rax,psidTemp
                        mov pSid,rax
                    .endif

                    mov cchDomain,DNLEN + 1

                    .if !LookupAccountNameW(
                        NULL,       ;; default lookup logic
                        Username,   ;; user/group of interest from commandline
                        pSid,       ;; Sid buffer
                        &cbSid,     ;; size of Sid
                        &RefDomain, ;; Domain account found on (unused)
                        &cchDomain, ;; size of domain in chars
                        &peUse
                        )
                        printf("LookupAccountName error! (rc=%lu)\n", GetLastError());
                        .break
                    .endif
                .else
                    printf("LookupAccountName error! (rc=%lu)\n", GetLastError())
                    .break
                .endif
            .endif

            ;;
            ;; compute size of new acl
            ;;
            GetLengthSid(pSid)
            add rax,sizeof(ACL) + 1 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) )
            mov dwAclSize,eax

            ;;
            ;; allocate storage for Acl
            ;;

            mov pDacl,HeapAlloc(GetProcessHeap(), 0, dwAclSize)
            .break .if pDacl == NULL
            .break .if !InitializeAcl(pDacl, dwAclSize, ACL_REVISION)

            ;;
            ;; grant GENERIC_ALL (Full Control) access
            ;;

            .break .if !AddAccessAllowedAce(pDacl, ACL_REVISION, GENERIC_ALL, pSid)
            .break .if !InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)

            .if !SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE)
                fprintf(stderr, "SetSecurityDescriptorDacl error! (rc=%lu)\n", GetLastError())
                .break
            .endif

            ;;
            ;; setup share info structure
            ;;

            mov rax,Sharename

            mov si502.shi502_netname,rax
            mov si502.shi502_type,STYPE_DISKTREE
            mov si502.shi502_remark,NULL
            mov si502.shi502_permissions,0
            mov si502.shi502_max_uses,SHI_USES_UNLIMITED
            mov si502.shi502_current_uses,0
            mov rax,DirectoryToShare
            mov si502.shi502_path,rax
            mov si502.shi502_passwd,NULL
            mov si502.shi502_reserved,0
            lea rax,sd
            mov si502.shi502_security_descriptor,rax

            mov nas,NetShareAdd(
                Server,         ;; share is on local machine
                502,            ;; info-level
                &si502,         ;; info-buffer
                NULL            ;; don't bother with parm
                )

            .if (nas != NO_ERROR)
                printf("NetShareAdd error! (rc=%lu)\n", nas)
                .break
            .endif

            mov bSuccess,TRUE ;; indicate success
        .until 1

        ;;
        ;; free allocated resources
        ;;
        .if (pDacl != NULL)
            HeapFree(GetProcessHeap(), 0, pDacl)
        .endif

        .if (pSid != NULL)
            HeapFree(GetProcessHeap(), 0, pSid)
        .endif

        mov eax,RTN_OK
        .break .if bSuccess
        mov eax,RTN_ERROR
    .until 1
    ret

wmain endp

    end
