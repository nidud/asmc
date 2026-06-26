
;--- don't allow groups to contain segments with different offset sizes

cgroup  group   _work, _work2

_work   segment
	db 16
_work   ends

	.386

_work2  segment use32
	db 32
_work2  ends

	End
