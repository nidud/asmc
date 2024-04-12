
;--- operators SIZE, TYPEOF
;--- for 64-bit NEAR/FAR

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

TN  typedef near
TF  typedef far

	.code

	dw TN, SIZE TN, typeof TN
	dw TF, SIZE TF, typeof TF

v1	label near
v2	label far

	dw SIZE v1, typeof v1
	dw SIZE v2, typeof v2

p1	proc

local l1[2]:TN
local l2[2]:TF

	dw sizeof   l1
	dw lengthof l1
	dw SIZE	    l1
	dw LENGTH   l1
	dw typeof   l1

	dw sizeof   l2
	dw lengthof l2
	dw SIZE	    l2
	dw LENGTH   l2
	dw typeof   l2

p1	endp

	END
