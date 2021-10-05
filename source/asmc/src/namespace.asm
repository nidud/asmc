; NAMESPACE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include parser.inc
include types.inc
include memalloc.inc

AllocName proto private :string_t, :string_t

    .code

NameSpace proc watcall name:string_t, retval:string_t

    mov ecx,ModuleInfo.NspStack
    .if ( ecx || eax != edx )
        AllocName(eax, edx)
    .endif
    ret

NameSpace endp

    assume esi:ptr nsp_item
    assume ebx:ptr asm_tok

NameSpaceDirective proc uses esi ebx i:int_t, tokenarray:token_t

    mov ebx,tokenarray
    mov esi,ModuleInfo.NspStack
    .if ( [ebx].tokval == T_DOT_ENDN )
        .if ( esi == NULL )
            .return asmerr( 1011 )
        .endif
        mov ecx,[esi].next
        .if ( ecx )
            .while ( [ecx].nsp_item.next )
                mov ecx,[ecx].nsp_item.next
                mov esi,[esi].next
            .endw
            mov [esi].next,NULL
        .else
            mov ModuleInfo.NspStack,NULL
        .endif
        .return NOT_ERROR
    .endif

    mov esi,LclAlloc( &[strlen([ebx+16].string_ptr)+nsp_item+1] )
    mov [esi].next,NULL
    mov [esi].name,&[eax+nsp_item]
    strcpy( [esi].name, [ebx+16].string_ptr )
    .if ( ModuleInfo.NspStack == NULL )
        mov ModuleInfo.NspStack,esi
    .else
        mov eax,esi
        mov esi,ModuleInfo.NspStack
        .while ( [esi].next )
            mov esi,[esi].next
        .endw
        mov [esi].next,eax
    .endif
    .return NOT_ERROR

NameSpaceDirective endp

AllocName proc private uses esi edi name:string_t, retval:string_t

   .new buffer[256]:char_t

    mov esi,ecx ; ModuleInfo.NspStack
    mov edi,edx ; retval

    .if ( !edi || edi == eax )
        lea edi,buffer
    .endif
    mov byte ptr [edi],0
    .if ( esi == NULL )
        strcpy( edi, name )
    .else
        .repeat
            strcat( edi, [esi].name )
            strcat( edi, "_" )
            mov esi,[esi].next
        .until !esi
        strcat( edi, name )
    .endif
    .if ( edi != retval )
        strcpy( LclAlloc( &[strlen( edi ) + 1] ), edi )
    .endif
    ret

AllocName endp

    end
