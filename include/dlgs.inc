ifndef _DLGSH_INCLUDED_
_DLGSH_INCLUDED_ equ <>

ctlFirst		equ 0x0400
ctlLast			equ 0x04ff

psh1			equ 0x0400
psh2			equ 0x0401
psh3			equ 0x0402
psh4			equ 0x0403
psh5			equ 0x0404
psh6			equ 0x0405
psh7			equ 0x0406
psh8			equ 0x0407
psh9			equ 0x0408
psh10			equ 0x0409
psh11			equ 0x040a
psh12			equ 0x040b
psh13			equ 0x040c
psh14			equ 0x040d
psh15			equ 0x040e
pshHelp			equ psh15
psh16			equ 0x040f

chx1			equ 0x0410
chx2			equ 0x0411
chx3			equ 0x0412
chx4			equ 0x0413
chx5			equ 0x0414
chx6			equ 0x0415
chx7			equ 0x0416
chx8			equ 0x0417
chx9			equ 0x0418
chx10			equ 0x0419
chx11			equ 0x041a
chx12			equ 0x041b
chx13			equ 0x041c
chx14			equ 0x041d
chx15			equ 0x041e
chx16			equ 0x041f

rad1			equ 0x0420
rad2			equ 0x0421
rad3			equ 0x0422
rad4			equ 0x0423
rad5			equ 0x0424
rad6			equ 0x0425
rad7			equ 0x0426
rad8			equ 0x0427
rad9			equ 0x0428
rad10			equ 0x0429
rad11			equ 0x042a
rad12			equ 0x042b
rad13			equ 0x042c
rad14			equ 0x042d
rad15			equ 0x042e
rad16			equ 0x042f

grp1			equ 0x0430
grp2			equ 0x0431
grp3			equ 0x0432
grp4			equ 0x0433
frm1			equ 0x0434
frm2			equ 0x0435
frm3			equ 0x0436
frm4			equ 0x0437
rct1			equ 0x0438
rct2			equ 0x0439
rct3			equ 0x043a
rct4			equ 0x043b
ico1			equ 0x043c
ico2			equ 0x043d
ico3			equ 0x043e
ico4			equ 0x043f

stc1			equ 0x0440
stc2			equ 0x0441
stc3			equ 0x0442
stc4			equ 0x0443
stc5			equ 0x0444
stc6			equ 0x0445
stc7			equ 0x0446
stc8			equ 0x0447
stc9			equ 0x0448
stc10			equ 0x0449
stc11			equ 0x044a
stc12			equ 0x044b
stc13			equ 0x044c
stc14			equ 0x044d
stc15			equ 0x044e
stc16			equ 0x044f
stc17			equ 0x0450
stc18			equ 0x0451
stc19			equ 0x0452
stc20			equ 0x0453
stc21			equ 0x0454
stc22			equ 0x0455
stc23			equ 0x0456
stc24			equ 0x0457
stc25			equ 0x0458
stc26			equ 0x0459
stc27			equ 0x045a
stc28			equ 0x045b
stc29			equ 0x045c
stc30			equ 0x045d
stc31			equ 0x045e
stc32			equ 0x045f

lst1			equ 0x0460
lst2			equ 0x0461
lst3			equ 0x0462
lst4			equ 0x0463
lst5			equ 0x0464
lst6			equ 0x0465
lst7			equ 0x0466
lst8			equ 0x0467
lst9			equ 0x0468
lst10			equ 0x0469
lst11			equ 0x046a
lst12			equ 0x046b
lst13			equ 0x046c
lst14			equ 0x046d
lst15			equ 0x046e
lst16			equ 0x046f

cmb1			equ 0x0470
cmb2			equ 0x0471
cmb3			equ 0x0472
cmb4			equ 0x0473
cmb5			equ 0x0474
cmb6			equ 0x0475
cmb7			equ 0x0476
cmb8			equ 0x0477
cmb9			equ 0x0478
cmb10			equ 0x0479
cmb11			equ 0x047a
cmb12			equ 0x047b
cmb13			equ 0x047c
cmb14			equ 0x047d
cmb15			equ 0x047e
cmb16			equ 0x047f

edt1			equ 0x0480
edt2			equ 0x0481
edt3			equ 0x0482
edt4			equ 0x0483
edt5			equ 0x0484
edt6			equ 0x0485
edt7			equ 0x0486
edt8			equ 0x0487
edt9			equ 0x0488
edt10			equ 0x0489
edt11			equ 0x048a
edt12			equ 0x048b
edt13			equ 0x048c
edt14			equ 0x048d
edt15			equ 0x048e
edt16			equ 0x048f

scr1			equ 0x0490
scr2			equ 0x0491
scr3			equ 0x0492
scr4			equ 0x0493
scr5			equ 0x0494
scr6			equ 0x0495
scr7			equ 0x0496
scr8			equ 0x0497

FILEOPENORD		equ 1536
MULTIFILEOPENORD	equ 1537
PRINTDLGORD		equ 1538
PRNSETUPDLGORD		equ 1539
FINDDLGORD		equ 1540
REPLACEDLGORD		equ 1541
FONTDLGORD		equ 1542
FORMATDLGORD31		equ 1543
FORMATDLGORD30		equ 1544
RUNDLGORD		equ 1545

if (WINVER GE 0x400)
PAGESETUPDLGORD		equ 1546
NEWFILEOPENORD		equ 1547
NEWOBJECTOPENORD	equ 1548
endif

CRGB			STRUC
bRed			db ?
bGreen			db ?
bBlue			db ?
bExtra			db ?
CRGB			ENDS

endif
