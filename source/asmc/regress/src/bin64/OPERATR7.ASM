
;--- v2.11: TYPE had a problem if type coercion was active and a
;--- unary operator was used.

ifndef __ASMC64__
    .x64
    .model flat
endif

	.CODE
start:

	dw TYPEOF QWORD PTR offset start
	dw TYPEOF QWORD PTR LOW32 start
	dw TYPEOF QWORD PTR LOWWORD start
	dw TYPEOF QWORD PTR LOWBYTE start

END
