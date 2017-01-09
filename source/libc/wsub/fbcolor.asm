include consx.inc
include io.inc
include ini.inc
include string.inc
include stdlib.inc
include wsub.inc

strtolx proto :LPSTR

	.code

fbcolor PROC USES edx ecx fp:PTR S_FBLK
	mov	edx,fp

	test	[edx].S_FBLK.fb_flag,_A_SUBDIR
	jnz	default_color

	lea	ecx,[edx].S_FBLK.fb_name
	.if	strext( ecx )
		lea	ecx,[eax+1]
	.endif
	.if	inientry( "FileColor", ecx )
		strtolx( eax )
		cmp	eax,15
		ja	default_color
		shl	eax,4
		cmp	al,at_background[B_Panel]
		je	default_color
		shr	eax,4
		jmp	done
	.endif

default_color:
	mov	eax,[edx].S_FBLK.fb_flag
	.switch
	  .case eax & _FB_SELECTED : mov al,at_foreground[F_Panel]  : .endc
	  .case eax & _FB_UPDIR	   : mov al,7			    : .endc
	  .case eax & _FB_ROOTDIR
	  .case eax & _A_SYSTEM	   : mov al,at_foreground[F_System] : .endc
	  .case eax & _A_HIDDEN	   : mov al,at_foreground[F_Hidden] : .endc
	  .case eax & _A_SUBDIR	   : mov al,at_foreground[F_Subdir] : .endc
	  .default
		mov al,at_foreground[F_Files]
	.endsw
done:
	or	al,at_background[B_Panel]
	movzx	eax,al
	ret
fbcolor ENDP

	END
