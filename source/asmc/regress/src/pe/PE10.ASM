
;--- the alias triggers import by number.
;--- the name must contain a dot, followed by a number.
;--- what's before the dot is ignored; since aliases must be unique,
;--- it's important if one wants to import by number from multiple dlls.

	.386
	.model flat,stdcall
	option casemap:none
	option proc:private
	option dotname

	option dllimport:<kernel32.dll>
VxDCall1    proto stdcall :dword
VxDCall2    proto stdcall :dword, :dword
ExitProcess proto stdcall :dword
	option dllimport:none

	alias <kernel32.1> = <VxDCall1>
	alias <kernel32.2> = <VxDCall2>

	.code

start:

	invoke VxDCall1, 0
	invoke VxDCall2, 1, 2
	invoke ExitProcess, eax

	end start

