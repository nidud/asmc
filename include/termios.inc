ifndef __TERMIOS_INC
define __TERMIOS_INC

include sys/ioctl.inc

; c_iflag

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
define	IUTF8		0x4000

; c_oflag

define	OPOST		0x0001 ; Enable implementation-defined output processing.
define	OLCUC		0x0002 ; (not POSIX) Map lowercase characters to uppercase on output.
define	ONLCR		0x0004 ; (XSI) Map NL to CR-NL on output.
define	OCRNL		0x0008 ; Map CR to NL on output.
define	ONOCR		0x0010 ; Don't output CR at column 0.
define	ONLRET		0x0020 ; Don't output CR.
define	OFILL		0x0040 ; Send fill characters for a delay, rather than using a timed delay
define	OFDEL		0x0080 ; Fill character is ASCII DEL (0177).  If unset, fill
			       ; character is ASCII NUL ('\0'). (Not implemented on Linux.)
define	NLDLY		0x0100 ; Newline delay mask.
define	NL0		0x0000
define	NL1		0x0100
define	CRDLY		0x0600 ; Carriage return delay mask.
define	_CR0		0x0000
define	_CR1		0x0200
define	_CR2		0x0400
define	_CR3		0x0600
define	TABDLY		0x1800 ; Horizontal tab delay mask.
define	TAB0		0x0000
define	TAB1		0x0800
define	TAB2		0x1000
define	TAB3		0x1800
define	BSDLY		0x2000 ; Backspace delay mask.
define	BS0		0x0000
define	BS1		0x2000
define	VTDLY		0x4000 ; Vertical tab delay mask.
define	VT0		0x0000
define	VT1		0x4000
define	FFDLY		0x8000 ; Form feed delay mask.
define	FF0		0x0000
define	FF1		0x8000

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

; ioctl.inc: commands 'T'

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
