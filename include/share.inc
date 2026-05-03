.pragma list(push, 0)

define SH_DENYRW	0x10 ; deny read/write mode
define SH_DENYWR	0x20 ; deny write mode
define SH_DENYRD	0x30 ; deny read mode
define SH_DENYNO	0x40 ; deny none mode
define SH_SECURE	0x80 ; secure mode

.pragma list(pop)
