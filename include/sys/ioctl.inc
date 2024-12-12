; IOCTL.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __IOCTL_INC
define __IOCTL_INC

include libc.inc

define TCGETS           0x5401
define TCSETS           0x5402
define TCSETSW          0x5403
define TCSETSF          0x5404
define TCGETA           0x5405
define TCSETA           0x5406
define TCSETAW          0x5407
define TCSETAF          0x5408
define TCSBRK           0x5409
define TCXONC           0x540A
define TCFLSH           0x540B
define TIOCEXCL         0x540C
define TIOCNXCL         0x540D
define TIOCSCTTY        0x540E
define TIOCGPGRP        0x540F
define TIOCSPGRP        0x5410
define TIOCOUTQ         0x5411
define TIOCSTI          0x5412
define TIOCGWINSZ       0x5413
define TIOCSWINSZ       0x5414
define TIOCMGET         0x5415
define TIOCMBIS         0x5416
define TIOCMBIC         0x5417
define TIOCMSET         0x5418
define TIOCGSOFTCAR     0x5419
define TIOCSSOFTCAR     0x541A
define FIONREAD         0x541B
define TIOCLINUX        0x541C
define TIOCCONS         0x541D
define TIOCGSERIAL      0x541E
define TIOCSSERIAL      0x541F
define TIOCPKT          0x5420
define FIONBIO          0x5421
define TIOCNOTTY        0x5422
define TIOCSETD         0x5423
define TIOCGETD         0x5424
define TCSBRKP          0x5425
define TIOCSBRK         0x5427
define TIOCCBRK         0x5428
define TIOCGSID         0x5429
define TIOCGRS485       0x542E
define TIOCSRS485       0x542F
define TCGETX           0x5432
define TCSETX           0x5433
define TCSETXF          0x5434
define TCSETXW          0x5435

define FIONCLEX         0x5450
define FIOCLEX          0x5451
define FIOASYNC         0x5452
define TIOCSERCONFIG    0x5453
define TIOCSERGWILD     0x5454
define TIOCSERSWILD     0x5455
define TIOCGLCKTRMIOS   0x5456
define TIOCSLCKTRMIOS   0x5457
define TIOCSERGSTRUCT   0x5458
define TIOCSERGETLSR    0x5459
define TIOCSERGETMULTI  0x545A
define TIOCSERSETMULTI  0x545B

define TIOCMIWAIT       0x545C
define TIOCGICOUNT      0x545D

ioctl proto __cdecl :int_t, :int_t, :ptr

endif
