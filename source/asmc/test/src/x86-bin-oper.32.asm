ifdef __ASMC__
option masm:on
endif

;--- operators SIZE, TYPE
;--- for 32-bit NEAR/FAR

	.386
	.model flat

TN  typedef near
TF  typedef far

	.code

	dw near, SIZE near, TYPE near
	dw far,	 SIZE far,  TYPE far

	dw TN, SIZE TN, TYPE TN
	dw TF, SIZE TF, TYPE TF

v1	label near
v2	label far

	dw SIZE v1, TYPE v1
	dw SIZE v2, TYPE v2

p1	proc

local l1[2]:TN
local l2[2]:TF

	dw sizeof   l1
	dw lengthof l1
	dw SIZE	    l1
	dw LENGTH   l1
	dw TYPE	    l1

	dw sizeof   l2
	dw lengthof l2
	dw SIZE	    l2
	dw LENGTH   l2
	dw TYPE	    l2

p1	endp

	END
