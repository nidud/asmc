;
; This sample shows how to compute SHA 256 hash of a message(s) using CNG.
;

include windows.inc
include winternl.inc
include ntstatus.inc
include winerror.inc
include stdio.inc
include bcrypt.inc
include sal.inc
include tchar.inc

.data
 Message byte \
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,

.code

ReportError proc dwErrCode:DWORD

    wprintf( L"Error: 0x%08x (%d)\n", dwErrCode, dwErrCode )
    ret

ReportError endp

wmain proc \
    argc: int_t,
    argv: ptr LPWSTR

    .new Status:NTSTATUS

    .new AlgHandle:BCRYPT_ALG_HANDLE = NULL
    .new HashHandle:BCRYPT_HASH_HANDLE = NULL

    .new Hash:PBYTE = NULL
    .new HashLength:DWORD = 0
    .new ResultLength:DWORD = 0

    ;
    ; Open an algorithm handle
    ; This sample passes BCRYPT_HASH_REUSABLE_FLAG with
    ; BCryptAlgorithmProvider(...) to load a provider which supports reusable hash
    ;

    mov Status,BCryptOpenAlgorithmProvider(
            &AlgHandle,                 ; Alg Handle pointer
            BCRYPT_SHA256_ALGORITHM,    ; Cryptographic Algorithm name (null terminated unicode string)
            NULL,                       ; Provider name; if null, the default provider is loaded
            BCRYPT_HASH_REUSABLE_FLAG)  ; Flags; Loads a provider which supports reusable hash

    .if ( !NT_SUCCESS(Status) )

        ReportError(Status)
        jmp cleanup
    .endif

    ;
    ; Obtain the length of the hash
    ;

    mov Status,BCryptGetProperty(
            AlgHandle,                  ; Handle to a CNG object
            BCRYPT_HASH_LENGTH,         ; Property name (null terminated unicode string)
            &HashLength,                ; Address of the output buffer which recieves the property value
            sizeof(HashLength),         ; Size of the buffer in bytes
            &ResultLength,              ; Number of bytes that were copied into the buffer
            0)                          ; Flags

    .if ( !NT_SUCCESS(Status) )

        ReportError(Status)
        jmp cleanup
    .endif

    ;
    ; Allocate the hash buffer on the heap
    ;

    mov Hash,HeapAlloc(GetProcessHeap(), 0, HashLength)
    .if ( Hash == NULL )

        mov Status,STATUS_NO_MEMORY
        ReportError(Status)
        jmp cleanup
    .endif

    ;
    ; Create a hash handle
    ;

    mov Status,BCryptCreateHash(
            AlgHandle,                  ; Handle to an algorithm provider
            &HashHandle,                ; A pointer to a hash handle - can be a hash or hmac object
            NULL,                       ; Pointer to the buffer that recieves the hash/hmac object
            0,                          ; Size of the buffer in bytes
            NULL,                       ; A pointer to a key to use for the hash or MAC
            0,                          ; Size of the key in bytes
            0)                          ; Flags

    .if ( !NT_SUCCESS(Status) )

        ReportError(Status)
        jmp cleanup
    .endif

    ;
    ; Hash the message(s)
    ; More than one message can be hashed by calling BCryptHashData
    ;

    mov Status,BCryptHashData(
            HashHandle,                 ; Handle to the hash or MAC object
            &Message,                   ; A pointer to a buffer that contains the data to hash
            sizeof(Message),            ; Size of the buffer in bytes
            0)                          ; Flags

    .if ( !NT_SUCCESS(Status) )

        ReportError(Status)
        jmp cleanup
    .endif

    ;
    ; Obtain the hash of the message(s) into the hash buffer
    ;

    mov Status,BCryptFinishHash(
            HashHandle,                 ; Handle to the hash or MAC object
            Hash,                       ; A pointer to a buffer that receives the hash or MAC value
            HashLength,                 ; Size of the buffer in bytes
            0)                          ; Flags

    .if( !NT_SUCCESS(Status) )

        ReportError(Status)
        jmp cleanup
    .endif

    mov Status,STATUS_SUCCESS

cleanup:

    .if ( Hash != NULL )

        HeapFree(GetProcessHeap(), 0, Hash)
    .endif

    .if ( HashHandle != NULL )

         BCryptDestroyHash(HashHandle)  ; Handle to hash/MAC object which needs to be destroyed
    .endif

    .if ( AlgHandle != NULL )

        BCryptCloseAlgorithmProvider(
            AlgHandle,                  ; Handle to the algorithm provider which needs to be closed
            0)                          ; Flags
    .endif

    .return Status

wmain endp

    end _tstart
