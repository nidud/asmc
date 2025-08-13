; DIFFTIME.ASM--
;
; https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/difftime-difftime32-difftime64?view=msvc-170
;
; This program calculates the amount of time
; needed to do a floating-point multiply 100 million times.
;

include stdio.inc
include stdlib.inc
include time.inc
include float.inc

.code

RangedRand proc range_min:float, range_max:float

   ; Generate random numbers in the half-closed interval
   ; [range_min, range_max). In other words,
   ; range_min <= random number < range_max

   rand()
   cvtsi2sd xmm0,rax
   divsd    xmm0,@CatStr(%(RAND_MAX + 1), <.0>)
   cvtss2sd xmm1,range_min
   cvtss2sd xmm2,range_max
   subsd    xmm2,xmm1
   mulsd    xmm0,xmm2
   addsd    xmm0,xmm1
   ret

RangedRand endp


main proc

   .new start:time_t
   .new finish:time_t
   .new result:double
   .new elapsed_time:double

    ; Seed the random-number generator with the current time so that
    ; the numbers will be different every time we run.

    srand( time( NULL ) )

   .new arNums[3]:double = {
        RangedRand(1.0, FLT_MAX),
        RangedRand(1.0, FLT_MAX),
        RangedRand(1.0, FLT_MAX)
        }

    printf(
        "Using floating point numbers %0.5e %0.5e %0.5e\n"
        "Multiplying 2 numbers 100 million times...\n", arNums[0*8], arNums[1*8], arNums[2*8] )

    time( &start )
    .for( ecx= 3, ebx = 0 : ebx < 100000000 : ebx++ )

      xor   edx,edx
      mov   eax,ebx
      div   ecx
      movsd xmm0,arNums[rdx*8]
      xor   edx,edx
      mov   eax,ebx
      inc   eax
      div   ecx
      mulsd xmm0,arNums[rdx*8]
      movsd result,xmm0
    .endf
    time( &finish )
    movsd elapsed_time,difftime( finish, start )
    printf( "\nProgram takes %6.0f seconds.\n", elapsed_time )
    xor eax,eax
    ret

main endp

    end
