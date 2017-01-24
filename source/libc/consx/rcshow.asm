include consx.inc

	.code

rcshow	PROC rect, flag, wp:PVOID
	mov	eax,flag
	and	eax,_D_DOPEN or _D_ONSCR
	jz	toend
	and	eax,_D_ONSCR
	jnz	done
	rcxchg( rect, wp )
	jz	toend
	test	BYTE PTR flag,_D_SHADE
	jz	done
	rcsetshade( rect, wp )
done:
	xor	eax,eax
	inc	eax
toend:
	ret
rcshow	ENDP

	END
