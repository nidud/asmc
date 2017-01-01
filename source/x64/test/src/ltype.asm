include ltype.inc

	.code

main	proc
	.assert islabel('A') == 'A'
	.assert islabel('a') == 'a'
	.assert islabel('0') == '0'
	.assert islabel('9') == '9'
	.assert islabel('_') == '_'
	.assert islabel('@') == '@'
	.assert islabel('$') == '$'
	.assert islabel('?') == '?'
	.assert islabel('F') == 'F'
	.assert islabel('q') == 'q'
	.assert islabel('.') == 0
	.assert islabel(' ') == 0
	xor	rax,rax
	ret
main	endp

	end
