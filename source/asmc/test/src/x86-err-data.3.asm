
;--- missing error "initializer magnitude too large for specified size

	.386

XXX struct
wOfs dw ?
XXX ends

_TEXT segment use32 dword public 'CODE'

lbl1:
	ret

v2	dw offset lbl1
v1	XXX <offset lbl1>

_TEXT ends

	.386

    end
