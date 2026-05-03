ifndef KERNELSPECS_H
define KERNELSPECS_H

include DriverSpecs.inc

DISPATCH_LEVEL  equ 2
APC_LEVEL       equ 1
PASSIVE_LEVEL   equ 0

if defined(_X86_)
HIGH_LEVEL equ 31
endif
if defined(_AMD64_)
HIGH_LEVEL equ 15
endif
if defined(_ARM_)
HIGH_LEVEL equ 15
endif
if defined(_IA64_)
HIGH_LEVEL equ 15
endif

ifdef _PREFAST_
endif

endif
