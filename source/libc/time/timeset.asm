include time.inc

		.data

PST		db "PST",0
PDT		db "PDT",0
_timezone	dd 8*3600
_daylight	dd 1
_tzname		PVOID PST
		PVOID PDT
__dnames	db "SunMonTueWedThuFriSat",0
__mnames	db "JanFebMarAprMayJunJulAugSepOctNovDec",0

		END
