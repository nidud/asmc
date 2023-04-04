ifndef _TERMIOS_H
define _TERMIOS_H

define	IGNBRK		0x0001
define	BRKINT		0x0002
define	IGNPAR		0x0004
define	PARMRK		0x0008
define	INPCK		0x0010
define	ISTRIP		0x0020
define	INLCR		0x0040
define	IGNCR		0x0080
define	ICRNL		0x0100
define	IUCLC		0x0200
define	IXON		0x0400
define	IXANY		0x0800
define	IXOFF		0x1000
define	IMAXBEL		0x2000

define	OPOST		0x0001
define	ONLCR		0x0004
define	OCRNL		0x0008
define	ONOCR		0x0010
define	ONLRET		0x0020

define	NLDLY		0x0100
define	NL0		0x0000
define	NL1		0x0100
define	TABDLY		0x1800
define	TAB0		0x0000
define	TAB1		0x0800
define	TAB2		0x1000
define	TAB3		0x1800
define	CRDLY		0x0600
define	_CR0		0x0000
define	_CR1		0x0200
define	_CR2		0x0400
define	_CR3		0x0600
define	FFDLY		0x8000
define	FF0		0x0000
define	FF1		0x8000
define	BSDLY		0x2000
define	BS0		0x0000
define	BS1		0x2000
define	VTDLY		0x4000
define	VT0		0x0000
define	VT1		0x4000

define	OLCUC		0x0002
define	OFILL		0x0040
define	OFDEL		0x0080

define	CSIZE		0x0030
define	CS5		0x0000
define	CS6		0x0010
define	CS7		0x0020
define	CS8		0x0030
define	CSTOPB		0x0040
define	CREAD		0x0080
define	PARENB		0x0100
define	PARODD		0x0200
define	HUPCL		0x0400
define	CLOCAL		0x0800

define	CRTSCTS		0x80000000

; .c_lflag

define	ISIG		0x0001
define	ICANON		0x0002
define	XCASE		0x0004
define	_ECHO		0x0008
define	ECHOE		0x0010
define	ECHOK		0x0020
define	ECHONL		0x0040
define	NOFLSH		0x0080
define	TOSTOP		0x0100
define	ECHOCTL		0x0200
define	ECHOPRT		0x0400
define	ECHOKE		0x0800
define	FLUSHO		0x1000
define	IEXTEN		0x8000
define	EXTPROC		0x10000

define	VINTR		0
define	VQUIT		1
define	VERASE		2
define	VKILL		3
define	VEOF		4
define	VTIME		5
define	VMIN		6
define	VSTART		8
define	VSTOP		9
define	VSUSP		10
define	VEOL		11
define	VREPRINT	12
define	VDISCARD	13
define	VWERASE		14
define	VLNEXT		15
define	VEOL2		16

define	NCCS		32

define	B0		0
define	B50		50
define	B75		75
define	B110		110
define	B134		134
define	B150		150
define	B200		200
define	B300		300
define	B600		600
define	B1200		1200
define	B1800		1800
define	B2400		2400
define	B4800		4800
define	B9600		9600
define	B7200		7200
define	B14400		14400
define	B19200		19200
define	B28800		28800
define	B38400		38400

define	EXTA		14
define	EXTB		15

define	B57600		57600
define	B76800		76800
define	B115200		115200
define	B230400		230400
define	B460800		460800
define	B500000		500000
define	B576000		576000
define	B921600		921600
define	B1000000	1000000
define	B1152000	1152000
define	B1500000	1500000
define	B2000000	2000000
define	B2500000	2500000
define	B3000000	3000000
define	B3500000	3500000
define	B4000000	4000000

define	TCSANOW		0
define	TCSADRAIN	1
define	TCSAFLUSH	2

define	TCIFLUSH	0
define	TCOFLUSH	1
define	TCIOFLUSH	2

define	TCOOFF		0
define	TCOON		1
define	TCIOFF		2
define	TCION		3

; ioctl commands 'T'

define TCGETS		0x5401
define TCSETS		0x5402
define TCSETSW		0x5403
define TCSETSF		0x5404
define TCGETA		0x5405
define TCSETA		0x5406
define TCSETAW		0x5407
define TCSETAF		0x5408
define TCSBRK		0x5409
define TCXONC		0x540A
define TCFLSH		0x540B
define TIOCEXCL		0x540C
define TIOCNXCL		0x540D
define TIOCSCTTY	0x540E
define TIOCGPGRP	0x540F
define TIOCSPGRP	0x5410
define TIOCOUTQ		0x5411
define TIOCSTI		0x5412
define TIOCGWINSZ	0x5413
define TIOCSWINSZ	0x5414
define TIOCMGET		0x5415
define TIOCMBIS		0x5416
define TIOCMBIC		0x5417
define TIOCMSET		0x5418
define TIOCGSOFTCAR	0x5419
define TIOCSSOFTCAR	0x541A
define FIONREAD		0x541B
define TIOCLINUX	0x541C
define TIOCCONS		0x541D
define TIOCGSERIAL	0x541E
define TIOCSSERIAL	0x541F
define TIOCPKT		0x5420
define FIONBIO		0x5421
define TIOCNOTTY	0x5422
define TIOCSETD		0x5423
define TIOCGETD		0x5424
define TCSBRKP		0x5425
define TIOCSBRK		0x5427
define TIOCCBRK		0x5428
define TIOCGSID		0x5429
define TIOCGRS485	0x542E
define TIOCSRS485	0x542F
define TCGETX		0x5432
define TCSETX		0x5433
define TCSETXF		0x5434
define TCSETXW		0x5435

define FIONCLEX		0x5450
define FIOCLEX		0x5451
define FIOASYNC		0x5452
define TIOCSERCONFIG	0x5453
define TIOCSERGWILD	0x5454
define TIOCSERSWILD	0x5455
define TIOCGLCKTRMIOS	0x5456
define TIOCSLCKTRMIOS	0x5457
define TIOCSERGSTRUCT	0x5458
define TIOCSERGETLSR	0x5459
define TIOCSERGETMULTI	0x545A
define TIOCSERSETMULTI	0x545B

define TIOCMIWAIT	0x545C
define TIOCGICOUNT	0x545D

tcflag_t	typedef dword
cc_t		typedef byte
speed_t		typedef sdword

termios		struct 4
c_iflag		tcflag_t ?
c_oflag		tcflag_t ?
c_cflag		tcflag_t ?
c_lflag		tcflag_t ?
c_line		cc_t ?
c_cc		cc_t NCCS dup(?)
c_ispeed	speed_t ?
c_ospeed	speed_t ?
termios		ends

cfgetospeed	proto __cdecl :ptr termios
cfgetispeed	proto __cdecl :ptr termios
cfsetospeed	proto __cdecl :ptr termios, :speed_t
cfsetispeed	proto __cdecl :ptr termios, :speed_t
cfsetspeed	proto __cdecl :ptr termios, :speed_t

tcgetattr	proto __cdecl :int_t, :ptr termios
tcsetattr	proto __cdecl :int_t, :int_t, :ptr termios

cfmakeraw	proto __cdecl :ptr termios
tcsendbreak	proto __cdecl :int_t, :int_t
tcdrain		proto __cdecl :int_t
tcflush		proto __cdecl :int_t, :int_t
tcflow		proto __cdecl :int_t, :int_t
tcgetsid	proto __cdecl :int_t

endif
