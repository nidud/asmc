include direct.inc
include process.inc

PUBLIC	cp_space
PUBLIC	cp_stdmask
PUBLIC	cp_datefrm
PUBLIC	cp_dotdot
PUBLIC	cp_timefrm

    .data
    cp_timefrm	db "%2u:%02u",0
    cp_dotdot	db "..",0
    cp_datefrm	db "%2u.%02u.%02u",0
    cp_stdmask	SBYTE '*.*',0
    cp_space	db ' ',0

    END
