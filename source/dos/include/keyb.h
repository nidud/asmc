#ifndef __INC_KEYB
#define __INC_KEYB
#if !defined(__INC_DEFS)
 #include <defs.h>
#endif

#ifdef __cplusplus
 extern "C" {
#endif

#define ALTTAB		0xA500
#define ALTESC		0x0100
#define ALTENTER	0x1C00

#define F11		0x8500
#define F12		0x8600
#define CTRLUP		0x8D00
#define CTRLDN		0x9100
#define CTRLINS		0x9200
#define CTRLDEL		0x9300
#define CTRLTAB		0x9400

#define ESC		0x011B
#define BKSP		0x0E08
#define TAB		0x0F09
#define ENTER		0x1C0D
#define SPACE		0x3920
#define HOME		0x4700
#define UP		0x4800
#define PGUP		0x4900
#define LEFT		0x4B00
#define RIGHT		0x4D00
#define END		0x4F00
#define DOWN		0x5000
#define PGDN		0x5100
#define INS		0x5200
#define DEL		0x5300

#define KPSTAR		0x372A
#define KPPLUS		0x4E2B
#define KPMIN		0x4A2D
#define KPENTER		0xE00D

#define F1		0x3B00
#define F2		0x3C00
#define F3		0x3D00
#define F4		0x3e00
#define F5		0x3f00
#define F6		0x4000
#define F7		0x4100
#define F8		0x4200
#define F9		0x4300
#define F10		0x4400

#define SHIFTF1		0x5400
#define SHIFTF2		0x5500
#define SHIFTF3		0x5600
#define SHIFTF4		0x5700
#define SHIFTF9		0x5C00
#define SHIFTF10	0x5D00

#define CTRLF1		0x5E00
#define CTRLF2		0x5F00
#define CTRLF3		0x6000
#define CTRLF4		0x6100
#define CTRLF5		0x6200
#define CTRLF6		0x6300
#define CTRLF7		0x6400
#define CTRLF8		0x6500
#define CTRLF9		0x6600
#define CTRLF10		0x6700

#define CTRLEND		0x7500
#define CTRLHOME	0x7700
#define CTRLEND		0x7500
#define CTRLPGUP	0x8400
#define CTRLPGDN	0x7600
#define CTRLLEFT	0x7300
#define CTRLRIGHT	0x7400
#define CTRLENTER	0x1C0A

#define ALTF1		0x6800
#define ALTF2		0x6900
#define ALTF3		0x6A00
#define ALTF4		0x6B00
#define ALTF5		0x6C00
#define ALTF6		0x6D00
#define ALTF7		0x6E00
#define ALTF8		0x6F00
#define ALTF9		0x7000
#define ALTF10		0x7100

#define ALT0		0x8100
#define ALT1		0x7800
#define ALT2		0x7900
#define ALT3		0x7A00
#define ALT4		0x7B00
#define ALT5		0x7C00
#define ALT6		0x7D00
#define ALT7		0x7E00
#define ALT8		0x7F00
#define ALT9		0x8000

#define ALTX		0x2D00

#define CTRL0		0x0BFF
#define CTRL1		0x02FF
#define CTRL2		0x0300
#define CTRL3		0x04FF
#define CTRL4		0x05FF
#define CTRL5		0x06FF
#define CTRL6		0x071E
#define CTRL7		0x08FF
#define CTRL8		0x091B
#define CTRL9		0x0A1D

#define CTRLA		0x1E01
#define CTRLB		0x3002
#define CTRLC		0x2E03
#define CTRLD		0x2004
#define CTRLE		0x1205
#define CTRLF		0x2106
#define CTRLG		0x2207
#define CTRLH		0x2308
#define CTRLI		0x1709
#define CTRLJ		0x240A
#define CTRLK		0x250B
#define CTRLL		0x260C
#define CTRLM		0x320D
#define CTRLN		0x310E
#define CTRLO		0x180F
#define CTRLP		0x1910
#define CTRLQ		0x1011
#define CTRLR		0x1312
#define CTRLS		0x1F13
#define CTRLT		0x1414
#define CTRLU		0x1615
#define CTRLV		0x2F16
#define CTRLW		0x1117
#define CTRLX		0x2D18
#define CTRLY		0x1519
#define CTRLZ		0x2C1A

#define ALT		0x0008
#define CTRL		0x0004
#define SHIFTLEFT	0x0002
#define SHIFTRIGHT	0x0001

struct __keyshift {
	unsigned ShiftRight	: 1;
	unsigned ShiftLeft	: 1;
	unsigned Ctrl		: 1;
	unsigned Alt		: 1;
	unsigned ScrollState	: 1;
	unsigned NumState	: 1;
	unsigned CapsState	: 1;
	unsigned InsertState	: 1;
	unsigned CtrlLeft	: 1;
	unsigned AltLeft	: 1;
	unsigned filler		: 1;
	unsigned CtrlNumKey	: 1;
	unsigned ScrollKey	: 1;
	unsigned NumKey		: 1;
	unsigned CapsKey	: 1;
	unsigned InsertKey	: 1;
};

int _CType getkey(void);
int _CType getesc(void);
int _CType keystroke(void);
int _CType getshift(void);

extern struct __keyshift *keyshift;

#ifdef __f__

extern	BYTE key_char;
extern	BYTE key_scan;
extern	BYTE key_code;
extern	BYTE keystate;

#define SHIFT_RIGHT		0x0001
#define SHIFT_LEFT		0x0002
#define SHIFT_CTRL		0x0004
#define SHIFT_ALT		0x0008
#define SHIFT_SCROLL		0x0010
#define SHIFT_NUMLOCK		0x0020
#define SHIFT_CAPSLOCK		0x0040
#define SHIFT_INSERTSTATE	0x0080
#define SHIFT_CTRLLEFT		0x0100
#define SHIFT_ALTLEFT		0x0200
#define SHIFT_ENHANCED		0x0400
#define SHIFT_CONTROLEKEY	0x0800
#define SHIFT_SCROLLKEY		0x1000
#define SHIFT_NUMLOCKKEY	0x2000
#define SHIFT_CAPSLOCKKEY	0x4000
#define SHIFT_INSERTKEY		0x8000
#define KEY_SHIFT		(SHIFT_RIGHT | SHIFT_LEFT)

#endif

#ifdef __cplusplus
 }
#endif
#endif

