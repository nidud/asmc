; DOSERRLI.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include errno.inc

	PUBLIC	dos_errlist

	PUBLIC	CP_DOSER04
	PUBLIC	CP_DOSER20
if 0
	PUBLIC	CP_DOSER00
	PUBLIC	CP_DOSER01
	PUBLIC	CP_DOSER02
	PUBLIC	CP_DOSER03
	PUBLIC	CP_DOSER04
	PUBLIC	CP_DOSER05
	PUBLIC	CP_DOSER06
	PUBLIC	CP_DOSER07
	PUBLIC	CP_DOSER08
	PUBLIC	CP_DOSER09
	PUBLIC	CP_DOSER10
	PUBLIC	CP_DOSER11
	PUBLIC	CP_DOSER12
	PUBLIC	CP_DOSER13
	PUBLIC	CP_DOSER14
	PUBLIC	CP_DOSER15
	PUBLIC	CP_DOSER16
	PUBLIC	CP_DOSER17
	PUBLIC	CP_DOSER18
	PUBLIC	CP_DOSER19
endif

	.data

CP_DOSER00	db	"Write-protection violation attempted",0
CP_DOSER01	db	"Unknown unit for driver",0
CP_DOSER02	db	"Drive not ready",0
CP_DOSER03	db	"Unknown command given to driver",0
CP_DOSER04	db	"Data error (bad CRC)",0
CP_DOSER05	db	"Bad device driver request structure length",0
CP_DOSER06	db	"Seek error",0
CP_DOSER07	db	"Unknown media type",0
CP_DOSER08	db	"Sector not found",0
CP_DOSER09	db	"Printer out of paper..",0
CP_DOSER10	db	"Write fault",0
CP_DOSER11	db	"Read fault",0
CP_DOSER12	db	"General failure",0
CP_DOSER13	db	"Sharing violation",0
CP_DOSER14	db	"Lock violation",0
CP_DOSER15	db	"Invalid disk change",0
CP_DOSER16	db	"FCB unavailable",0
CP_DOSER17	db	"Sharing buffer overflow",0
CP_DOSER18	db	"Code page mismatch",0
CP_DOSER19	db	"Out of input",0
CP_DOSER20	db	"Insufficient disk space",0

dos_errlist label DWORD
	dd	CP_DOSER00
	dd	CP_DOSER01
	dd	CP_DOSER02
	dd	CP_DOSER03
	dd	CP_DOSER04
	dd	CP_DOSER05
	dd	CP_DOSER06
	dd	CP_DOSER07
	dd	CP_DOSER08
	dd	CP_DOSER09
	dd	CP_DOSER10
	dd	CP_DOSER11
	dd	CP_DOSER12
	dd	CP_DOSER13
	dd	CP_DOSER14
	dd	CP_DOSER15
	dd	CP_DOSER16
	dd	CP_DOSER17
	dd	CP_DOSER18
	dd	CP_DOSER19
	dd	CP_DOSER20

	END
