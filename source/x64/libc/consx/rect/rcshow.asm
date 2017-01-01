include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rcshow	PROC USES rsi rdi rbx rect, flag, wp:PVOID

	mov	esi,ecx
	mov	edi,edx
	mov	rbx,r8

	mov	eax,edx
	and	eax,_D_DOPEN or _D_ONSCR
	jz	toend

	and	eax,_D_ONSCR
	jnz	done

	rcxchg( ecx, r8 )
	jz	toend

	test	edi,_D_SHADE
	jz	done
	rcsetshade( esi, rbx )
done:
	xor	eax,eax
	inc	eax
toend:
	ret
rcshow	ENDP

	END
