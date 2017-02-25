; CMSYSTEMINFO.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include alloc.inc
include crtl.inc
include string.inc
include stdlib.inc
include winbase.inc

ifdef _WIN95

externdef kernel32_dll:BYTE
endif
externdef IDD_DZSystemInfo:DWORD

	.data
	idleh	dd 0
	count	dd 0
	format	db "%17s",0;"%13I64d",0

	.code

UpdateMemoryStatus PROC PRIVATE USES esi edi ebx dialog
ifdef _WIN95
	local	M:MEMORYSTATUS
endif
	local	MS:MEMORYSTATUSEX
	local	value[32]:BYTE

	lea	edi,MS
	mov	ecx,sizeof( MEMORYSTATUSEX )
	xor	eax,eax
	rep	stosb
	mov	MS.dwLength,sizeof( MEMORYSTATUSEX )

ifdef _WIN95
	.if GetModuleHandle( addr kernel32_dll )
		.if GetProcAddress( eax, "GlobalMemoryStatusEx" )
			lea	ecx,MS
			push	ecx
			call	eax
		.else
			GlobalMemoryStatus( addr M )

			mov	eax,M.dwMemoryLoad
			mov	MS.dwMemoryLoad,eax
			mov	eax,M.dwTotalPhys
			mov	DWORD PTR MS.ullTotalPhys,eax
			mov	eax,M.dwAvailPhys
			mov	DWORD PTR MS.ullAvailPhys,eax
			mov	eax,M.dwTotalPageFile
			mov	DWORD PTR MS.ullTotalPageFile,eax
			mov	eax,M.dwAvailPageFile
			mov	DWORD PTR MS.ullAvailPageFile,eax
			mov	eax,M.dwTotalVirtual
			mov	DWORD PTR MS.ullTotalVirtual,eax
			mov	eax,M.dwAvailVirtual
			mov	DWORD PTR MS.ullAvailVirtual,eax
		.endif
	.endif
else
	GlobalMemoryStatusEx( addr MS ) ; min WinXP
endif
	mov	esi,dialog
	mov	ebx,[esi].S_DOBJ.dl_rect
	add	ebx,00000912h
	movzx	edi,bh
	movzx	ebx,bl
	scputf( ebx, edi, 0, 0, "%d%%  ", MS.dwMemoryLoad )
	add	edi,4
	sub	ebx,15
	mkbstring( addr value, MS.ullTotalPhys )
	scputf( ebx, edi, 0, 0, addr format, addr value )
	inc	edi
	mov	eax,DWORD PTR MS.ullTotalPhys
	mov	edx,DWORD PTR MS.ullTotalPhys[4]
	sub	eax,DWORD PTR MS.ullAvailPhys
	sbb	edx,DWORD PTR MS.ullAvailPhys[4]
	mkbstring( addr value, edx::eax )
	scputf( ebx, edi, 0, 0, addr format, addr value )
	sub	edi,1
	add	ebx,18
	mkbstring( addr value, MS.ullTotalPageFile )
	scputf( ebx, edi, 0, 0, addr format, addr value )
	inc	edi
	mov	eax,DWORD PTR MS.ullTotalPageFile
	mov	edx,DWORD PTR MS.ullTotalPageFile[4]
	sub	eax,DWORD PTR MS.ullAvailPageFile
	sbb	edx,DWORD PTR MS.ullAvailPageFile[4]
	mkbstring( addr value, edx::eax )
	scputf( ebx, edi, 0, 0, addr format, addr value )
	ret
UpdateMemoryStatus ENDP

sysinfoidle PROC PRIVATE
	.if	count == 156
		UpdateMemoryStatus( tdialog )
		mov	count,0
	.endif
	inc	count
	call	idleh
	ret
sysinfoidle ENDP

cmsysteminfo PROC USES esi edi ebx

	local	CPU[80]:BYTE

	mov	edi,sselevel
	call	GetSSELevel
	mov	sselevel,edi
	mov	ebx,eax
	xor	edi,edi
	mov	count,edi

	.if rsopen( IDD_DZSystemInfo )

		mov	esi,eax
		mov	edx,[esi].S_DOBJ.dl_wp
		mov	cl,'x'
		mov	eax,ebx

		.if eax & SSE_AVXOS
			mov [edx+906],cl
		.endif
		.if eax & SSE_AVX2
			mov [edx+982],cl
		.endif
		.if eax & SSE_AVX
			mov [edx+856],cl
		.endif
		.if eax & SSE_SSE42
			mov [edx+730],cl
		.endif
		.if eax & SSE_SSE41
			mov [edx+604],cl
		.endif
		.if eax & SSE_SSSE3
			mov [edx+960],cl
		.endif
		.if eax & SSE_SSE3
			mov [edx+834],cl
		.endif
		.if eax & SSE_SSE2
			mov [edx+708],cl
		.endif
		.if eax & SSE_SSE
			mov [edx+582],cl
		.endif

		dlshow( esi )

		.if ebx

			.686
			.xmm

			push	esi
			lea	edi,CPU
			xor	esi,esi
			.repeat
				lea	eax,[esi+80000002h]
				cpuid
				mov	[edi],eax
				mov	[edi+4],ebx
				mov	[edi+8],ecx
				mov	[edi+12],edx
				add	edi,16
				inc	esi
			.until esi == 3

			lea	eax,CPU
			.while BYTE PTR [eax] == ' '
				inc eax
			.endw
			pop	esi
			mov	ebx,[esi].S_DOBJ.dl_rect
			mov	cl,bh
			add	bl,4
			add	cl,2
			scputs( ebx, ecx, 0, 0, eax )
		.endif
		UpdateMemoryStatus( esi )
		__coreleft()
		mov	edi,ecx
		sub	ecx,eax
		mov	ebx,ecx
		xor	eax,eax
		mkbstring( addr CPU, eax::edi )
		mov	ecx,[esi].S_DOBJ.dl_rect
		mov	dl,ch
		add	cl,39
		add	dl,13
		scputf( ecx, edx, 0, 0, "%15s", addr CPU )
		xor	eax,eax
		mkbstring( addr CPU, eax::ebx )
		mov	ecx,[esi].S_DOBJ.dl_rect
		mov	dl,ch
		add	cl,39
		add	dl,14
		scputf( ecx, edx, 0, 0, "%15s", addr CPU )
		mov	eax,tdidle
		mov	tdidle,sysinfoidle
		mov	idleh,eax
		dlmodal( esi )
		mov	ecx,idleh
		mov	tdidle,ecx
	.endif
	ret
cmsysteminfo ENDP

	END
