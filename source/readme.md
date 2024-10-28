# The Asmc Source Directory

A few general notes about the source code in this sub-directory.

At first glance it may appear that the source is exclusively written for 64-bit but that's not necessarily so. The General Purpose Registers (GPR) used throughout is defined as follows (an idea taken from one of the Masm header files included in Visual Studio).

```
ifndef _WIN64
define rax <eax>
define rdx <edx>
define rbx <ebx>
define rcx <ecx>
define rdi <edi>
define rsi <esi>
define rbp <ebp>
define rsp <esp>
endif
```
This means there's some discipline with regards to register usage throughout the source. Another aspect of this approach is that all pointers will be 64-bit registers, which in turn improves readability of the code.

In addition to this a large portion of the source code which depends on LIBC (local or external) may also work in Linux. This require some additional discipline and [Asmc](asmc/) falls into this category (and also [libc](libc/) itself).

In Linux GNU make is used, so to distinguish between the simple make utility supplied here a symbol always defined by GNU make (YACC in this case) is used in the make files. Another common command used in make files is [pause](tools/pause/pause.asm), so if you plan on playing with the samples in Linux it may be a good idea to install that first.
