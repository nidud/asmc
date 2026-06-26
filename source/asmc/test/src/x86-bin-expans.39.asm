
@dummy macro xx
	db xx
endm

_DATA segment
	@dummy <"aaa!">
	@dummy <"aaa!!">
	@dummy <"aaa!!!">
_DATA ends
end

