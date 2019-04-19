
;--- operators .SIZE, TYPEOF
;--- for 16-bit NEAR/FAR

	.286
	.model small

TN  typedef near
TF  typedef far

	.code

	dw near, .size near, typeof near
	dw far,	 .size far,  typeof far

	dw TN, .size TN, typeof TN
	dw TF, .size TF, typeof TF

v1	label near
v2	label far

	dw .size v1, typeof v1
	dw .size v2, typeof v2

p1	proc

local l1[2]:TN
local l2[2]:TF

	dw sizeof   l1
	dw lengthof l1
	dw .size    l1
	dw .length  l1
	dw typeof   l1

	dw sizeof   l2
	dw lengthof l2
	dw .size    l2
	dw .length  l2
	dw typeof   l2

p1	endp

	END
