
;--- v2.11: TYPE had a problem if type coercion was active and a
;--- unary operator was used.

	.x64
	.model flat

	.CODE
start:

	dw TYPEOF QWORD PTR offset start
	dw TYPEOF QWORD PTR low32 start
	dw TYPEOF QWORD PTR lowword start
	dw TYPEOF QWORD PTR .low start

END
