
	.386
	.MODEL flat

DATADIR struct
dwAdr	dd ?
dwSize	dd ?
DATADIR ends

	.CODE

;--- all methods must work and result in eax reading index 2 instead of 0
;	mov eax,DATADIR[2*sizeof DATADIR]
	mov eax,[ebp].DATADIR[2*sizeof DATADIR].dwSize
	mov eax,[ebp].DATADIR[2*DATADIR].dwSize
	mov eax,[ebp][2*sizeof DATADIR].DATADIR.dwSize
	mov eax,[ebp].DATADIR.dwSize[2*sizeof DATADIR]
	mov eax,[ebp+2*sizeof DATADIR].DATADIR.dwSize

	END


