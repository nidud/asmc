;;
;; https://docs.microsoft.com/en-us/cpp/intrinsics/interlockeddecrement-intrinsic-functions
;; compiler_intrinsics_interlocked.cpp
;; compile with: /Oi
;;

_CRT_RAND_S equ <>

include stdlib.inc
include limits.inc
include stdio.inc
include process.inc
include windows.inc
include directxmath.inc
include tchar.inc

;; To declare an interlocked function for use as an intrinsic,
;; include intrin.h and put the function in a #pragma intrinsic
;; statement.
include intrin.inc

.data
;; Data to protect with the interlocked functions.
pdata LONG 1

.code
SimpleThread proto pParam:ptr

THREAD_COUNT equ 6

main proc uses rsi rdi rbx

  local threads[THREAD_COUNT]:HANDLE
  local ThreadId[THREAD_COUNT]:int_t
  local param[THREAD_COUNT]:int_t

    .for (ebx = 0: ebx < THREAD_COUNT: ebx++)

        lea rax,[rbx+1]
        lea rdi,ThreadId[rbx*4]
        lea r9,param[rbx*4]
        mov [rdi],eax
        mov [r9],eax

        CreateThread(NULL, NULL, &SimpleThread, r9, NORMAL_PRIORITY_CLASS, rdi)
        mov threads[rbx*HANDLE],rax
        .break .if !rax ;; error creating threads
    .endf

    WaitForMultipleObjects(ebx, &threads, 1, INFINITE)
    ret

main endp

;; Code for our simple thread
SimpleThread proc pParam:ptr

  local threadNum:int_t
  local randomValue:uint_t
  local time:uint_t

    mov threadNum,[rcx]

    .if rand_s(&randomValue)

        _mm_cvtsi64_sd(xmm0, randomValue)
        _mm_cvtsi64_sd(xmm1, UINT_MAX * 500)
        _mm_div_sd()
        _mm_cvtsd_si64()

        mov time,eax

        .while (pdata < 100)

            .if (pdata < 100)

                _InterlockedIncrement(&pdata)
                printf("Thread %d: %d\n", threadNum, pdata)
            .endif

            Sleep(time) ;; wait up to half of a second
        .endw
    .endif
    printf("Thread %d complete: %d\n", threadNum, pdata)
    ret

SimpleThread endp

    end _tstart
