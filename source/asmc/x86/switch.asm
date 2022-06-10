; SWITCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include string.inc
include stdio.inc
include stdlib.inc
include malloc.inc
include limits.inc

include asmc.inc
include token.inc
include hllext.inc

    .code

    .pragma warning(disable: 6004)

     option proc: private
     assume esi:  ptr hll_item


RenderCase proc uses esi edi ebx hll:ptr hll_item, case:ptr hll_item, buffer:string_t

    mov esi,hll
    mov ebx,case
    mov edi,buffer
    mov edx,[ebx].hll_item.condlines

    .if ( edx == NULL )

        AddLineQueueX( " jmp @C%04X", [ebx].hll_item.labels[LSTART*4] )

    .elseif ( strchr(edx, '.') && BYTE PTR [eax+1] == '.' )

        mov byte ptr [eax],0
        lea edi,[eax+2]
        mov ecx,GetHllLabel()

        AddLineQueueX(
            " cmp %s, %s\n"
            " jb @C%04X\n"
            " cmp %s, %s\n"
            " jbe @C%04X\n"
            "@C%04X%s",
            [esi].condlines, [ebx].hll_item.condlines,
            ecx,
            [esi].condlines, edi,
            [ebx].hll_item.labels[LSTART*4],
            ecx, LABELQUAL )

    .else
        AddLineQueueX(
            " cmp %s, %s\n"
            " je @C%04X",
            [esi].condlines, [ebx].hll_item.condlines,
            [ebx].hll_item.labels[LSTART*4] )
    .endif
    ret

RenderCase endp


RenderCCMP proc uses esi edi ebx hll:ptr hll_item, buffer:string_t

    mov esi,hll
    mov edi,buffer
    AddLineQueueX( "%s%s", edi, LABELQUAL )
    mov ebx,[esi].caselist
    .while ebx

        RenderCase( esi, ebx, edi )
        mov ebx,[ebx].hll_item.caselist
    .endw
    ret

RenderCCMP endp


GetLowCount proc hll:ptr hll_item, min:int_t, dist:int_t

    mov ecx,min
    add ecx,dist
    mov edx,hll
    xor eax,eax
    mov edx,[edx].hll_item.caselist

    .while edx
        .ifs [edx].hll_item.flags & HLLF_TABLE && ecx >= [edx].hll_item.value
            add eax,1
        .endif
        mov edx,[edx].hll_item.caselist
    .endw
    ret

GetLowCount endp


GetHighCount proc hll:ptr hll_item, max:int_t, dist:int_t

    mov ecx,max
    sub ecx,dist
    mov edx,hll
    xor eax,eax
    mov edx,[edx].hll_item.caselist

    .while edx
        .ifs [edx].hll_item.flags & HLLF_TABLE && ecx <= [edx].hll_item.value
            add eax,1
        .endif
        mov edx,[edx].hll_item.caselist
    .endw
    ret

GetHighCount endp


SetLowCount proc uses esi hll:ptr hll_item, count:int_t, min:int_t, dist:int_t

    mov ecx,min
    mov edx,count
    add ecx,dist
    xor eax,eax
    mov esi,hll
    mov esi,[esi].caselist

    .while  esi
        .ifs [esi].flags & HLLF_TABLE && ecx < [esi].value

            and [esi].flags,NOT HLLF_TABLE
            dec DWORD PTR [edx]
            add eax,1
        .endif
        mov esi,[esi].caselist
    .endw
    mov edx,[edx]
    ret

SetLowCount endp


SetHighCount proc uses esi hll:ptr hll_item, count:int_t, max:int_t, dist:int_t

    mov ecx,max
    mov edx,count
    sub ecx,dist
    xor eax,eax
    mov esi,hll
    mov esi,[esi].caselist

    .while esi

        .ifs [esi].flags & HLLF_TABLE && ecx > [esi].value

            and [esi].flags,NOT HLLF_TABLE
            dec DWORD PTR [edx]
            add eax,1
        .endif
        mov esi,[esi].caselist
    .endw
    mov edx,[edx]
    ret

SetHighCount endp


GetCaseVal proc fastcall private hll:ptr hll_item, val:int_t

    mov eax,[ecx].hll_item.caselist
    .while eax

        .if [eax].hll_item.flags & HLLF_TABLE && \
            [eax].hll_item.value == edx

            .break
        .endif
        mov ecx,eax
        mov eax,[eax].hll_item.caselist
    .endw
    ret

GetCaseVal endp


RemoveVal proc fastcall private hll:ptr hll_item, val:int_t

    .if GetCaseVal()

        and [eax].hll_item.flags,NOT HLLF_TABLE
        mov eax,1
    .endif
    ret

RemoveVal endp


GetCaseValue proc uses esi edi ebx hll:ptr hll_item, tokenarray:ptr asm_tok, dcount:uint_t, scount:uint_t

  .new i:int_t, opnd:expr
  .new oldtok:string_t
  .new size:byte = 1

    mov edx,tokenarray
    mov oldtok,[edx].asm_tok.tokpos

    xor edi,edi ; dynamic count
    xor ebx,ebx ; static count
    mov esi,hll
    mov eax,[esi].flags
    and eax,HLLF_ARG16 or HLLF_ARG32 or HLLF_ARG64
    .if eax == HLLF_ARG16
        inc size
    .elseif eax == HLLF_ARG32
        mov size,4
    .elseif eax == HLLF_ARG64
        mov size,8
    .endif
    mov esi,[esi].caselist

    .while esi

        .if [esi].flags & HLLF_NUM

            or [esi].flags,HLLF_TABLE
            Tokenize( [esi].condlines, 0, tokenarray, TOK_DEFAULT )
            mov ModuleInfo.token_count,eax
            mov i,0
            mov ecx,eax
            EvalOperand( &i, tokenarray, ecx, &opnd, EXPF_NOERRMSG )
            .break .if eax != NOT_ERROR

            xor edx,edx
            mov eax,opnd.value
            .if size == 1
                movsx eax,al
                test eax,eax
                .ifs
                    dec edx
                .endif
            .elseif size == 2
                movsx eax,ax
                test eax,eax
                .ifs
                    dec edx
                .endif
            .elseif size == 4
                test eax,eax
                .ifs
                    dec edx
                .endif
            .else
                mov edx,opnd.hvalue
            .endif

            .if opnd.kind == EXPR_ADDR
                mov ecx,opnd.sym
                add eax,[ecx].asym.offs
                xor edx,edx
            .endif
            mov [esi].value,eax
            mov [esi].hvalue,edx
            inc ebx
        .elseif [esi].condlines
            inc edi
        .endif
        mov esi,[esi].caselist
    .endw

    Tokenize( oldtok, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax

    mov eax,dcount
    mov [eax],edi
    mov eax,scount
    mov [eax],ebx
    ;
    ; error A3022 : .CASE redefinition : %s(%d) : %s(%d)
    ;
    .if ( ebx && Parse_Pass != PASS_1 )

        mov esi,hll
        mov esi,[esi].caselist
        mov edi,[esi].caselist

        .while edi

            .if [esi].flags & HLLF_NUM

                .if GetCaseVal( esi, [esi].labels )

                    asmerr( 3022, [esi].condlines, [esi].labels,
                        [eax].hll_item.condlines, [eax].hll_item.labels )
                .endif
            .endif
            mov esi,[esi].caselist
            mov edi,[esi].caselist
        .endw
    .endif
    mov eax,ebx
    ret

GetCaseValue endp


GetMaxCaseValue proc uses esi edi ebx hll:ptr hll_item, min:int_t, max:int_t, min_table:int_t, max_table:int_t

    mov esi,hll
    xor edi,edi
    mov eax,_I32_MIN
    mov edx,_I32_MAX
    mov esi,[esi].caselist

    .while esi

        .if [esi].flags & HLLF_TABLE

            inc edi
            mov ecx,[esi].value
            .ifs eax <= ecx
                mov eax,ecx
            .endif
            .ifs edx >= ecx
                mov edx,ecx
            .endif
        .endif
        mov esi,[esi].caselist
    .endw
    .if !edi
        mov eax,edi
        mov edx,edi
    .endif

    mov ebx,max
    mov ecx,min
    mov [ebx],eax
    mov [ecx],edx
    xor esi,esi
    and eax,eax
    .ifs
        dec esi
    .endif
    mov [ebx+4],esi
    xor esi,esi
    and edx,edx
    .ifs
        dec esi
    .endif
    mov [ebx+4],esi

    mov esi,hll
    mov ecx,1
    mov eax,MIN_JTABLE
    .if ( [esi].flags & HLLF_NOTEST )

        ; v2.30 - allow small jump tables

        mov eax,1

    .elseif !( [esi].flags & HLLF_ARGREG )

        add eax,2
        add ecx,1
        .if !( [esi].flags & HLLF_ARG16 or HLLF_ARG32 or HLLF_ARG64 )

            add eax,1
            .if !( ModuleInfo.xflag & OPT_REGAX )

                add eax,10
            .endif
        .endif
    .endif
    mov esi,min_table
    mov [esi],eax
    mov esi,max_table
    mov eax,edi
    shl eax,cl
    mov [esi],eax
    mov eax,[ebx]
    sub eax,edx
    mov ecx,edi
    add eax,1
    ret

GetMaxCaseValue endp


    assume esi:ptr asm_tok

IsCaseColon proc uses esi edi ebx tokenarray:ptr asm_tok

    mov esi,tokenarray
    xor edi,edi
    xor edx,edx

    .while [esi].token != T_FINAL

        mov al,[esi].token
        mov ah,[esi-16].token
        mov ecx,[esi-16].tokval
        .switch

          .case al == T_OP_BRACKET : inc edx : .endc
          .case al == T_CL_BRACKET : dec edx : .endc
          .case al == T_COLON

            .endc .if edx
            .endc .if ah == T_REG && ecx >= T_ES && ecx <= T_ST

            mov [esi].token,T_FINAL
            mov edi,esi
            .break
        .endsw
        add esi,16
    .endw
    mov eax,edi
    ret
IsCaseColon endp


    assume  ebx: ptr asm_tok

RenderMultiCase proc uses esi edi ebx hll:ptr hll_item, i:ptr int_t, buffer:ptr char_t,
        tokenarray:ptr asm_tok

  local result, colon

    mov ebx,tokenarray
    add ebx,16
    mov eax,ebx
    mov esi,ebx
    xor edi,edi
    mov result,edi

    IsCaseColon( ebx )
    mov colon,eax

    .while 1
        ;
        ; Split .case 1,2,3 to
        ;
        ;   .case 1
        ;   .case 2
        ;   .case 3
        ;
        mov al,[ebx].token
        .switch al

          .case T_FINAL : .break

          .case T_OP_BRACKET : inc edi : .endc
          .case T_CL_BRACKET : dec edi : .endc

          .case T_COMMA
            .endc .if edi

            mov edi,[ebx].tokpos
            mov BYTE PTR [edi],0
            strcpy( buffer, [esi].tokpos )
            lea esi,[ebx+16]
            mov BYTE PTR [edi],','
            xor edi,edi

            inc result
            AddLineQueueX( " .case %s", buffer )
            mov [ebx].token,T_FINAL
        .endsw
        add ebx,16
    .endw

    mov ebx,colon
    .if ebx

        mov [ebx].token,T_COLON
    .endif

    mov eax,result
    .if eax

        AddLineQueueX( " .case %s", [esi].tokpos )

        mov ebx,tokenarray
        xor eax,eax
        .while [ebx].token != T_FINAL

            add eax,1
            add ebx,16
        .endw
        mov ebx,i
        mov [ebx],eax

        mov esi,hll
        assume esi:ptr hll_item

        .if [esi].flags & HLLF_PASCAL

            and [esi].flags,NOT HLLF_PASCAL

            .if ModuleInfo.list

                LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
            .endif
            RunLineQueue()

            or [esi].flags,HLLF_PASCAL
        .endif
        mov eax,1
    .endif
    ret

RenderMultiCase endp


CompareMaxMin proc reg:string_t, max:int_t, min:int_t, around:string_t
    AddLineQueueX(
        " cmp %s,%d\n"
        " jl  %s\n"
        " cmp %s,%d\n"
        " jg  %s", reg, min, around, reg, max, around )
    ret
CompareMaxMin endp

;
; Move .SWITCH <arg> to [R|E]AX
;
GetSwitchArg proc uses ebx reg:int_t, flags:int_t, arg:int_t

  local buffer[64]:sbyte

    .if !( ModuleInfo.xflag & OPT_REGAX )

        AddLineQueueX( "push %r", reg )
    .endif

    GetResWName( reg, &buffer )

    mov eax,flags
    mov edx,reg
    mov ebx,arg

    .if !( eax & HLLF_ARG16 or HLLF_ARG32 or HLLF_ARG64 )
        ;
        ; BYTE value
        ;
ifndef ASMC64
        mov ecx,ModuleInfo.curr_cpu
        and ecx,P_CPU_MASK
        .if ecx >= P_386
endif
            .if eax & HLLF_ARGMEM

                AddLineQueueX( " movsx %r, byte ptr %s", edx, ebx )
            .else
                AddLineQueueX( " movsx %r, %s", edx, ebx )
            .endif
ifndef ASMC64
        .else
            .if tstricmp( "al", ebx )

                AddLineQueueX( " mov al, %s", ebx )
            .endif
            AddLineQueue( " cbw" )
        .endif
endif
    .elseif eax & HLLF_ARG16
        ;
        ; WORD value
        ;
ifndef ASMC64
        .if ModuleInfo.Ofssize == USE16

            .if eax & HLLF_ARGMEM

                AddLineQueueX( " mov %r, word ptr %s", edx, ebx )
            .elseif tstricmp( ebx, &buffer )

                AddLineQueueX( " mov %r,%s", edx, ebx )
            .endif
        .elseif eax & HLLF_ARGMEM
else
        .if eax & HLLF_ARGMEM
endif
            AddLineQueueX( " movsx %r, word ptr %s", edx, ebx )
        .else
            AddLineQueueX( " movsx %r, %s", edx, ebx )
        .endif

    .elseif eax & HLLF_ARG32
        ;
        ; DWORD value
        ;
ifndef ASMC64
        .if ModuleInfo.Ofssize == USE32
            .if eax & HLLF_ARGMEM
                AddLineQueueX( " mov %r, dword ptr %s", edx, ebx )
            .elseif tstricmp( ebx, &buffer )
                AddLineQueueX( " mov %r, %s", edx, ebx )
            .endif
        .elseif eax & HLLF_ARGMEM
else
        .if eax & HLLF_ARGMEM
endif
            AddLineQueueX( " movsxd %r, dword ptr %s", edx, ebx )
        .else
            AddLineQueueX( " movsxd %r, %s", edx, ebx )
        .endif
    .else
        ;
        ; QWORD value
        ;
        AddLineQueueX( " mov %r, qword ptr %s", edx, ebx )
    .endif
    ret

GetSwitchArg endp


GetJumpDist proc table_type:int_t, reg:int_t, min:int_t, table_addr:string_t, base_addr:string_t

    mov ecx,T_MOV
    mov edx,4
    .if ( table_type == T_BYTE )
        mov edx,1
        mov ecx,T_MOVZX
    .elseif ( table_type == T_WORD )
        mov edx,2
        mov ecx,T_MOVZX
    .endif
    AddLineQueueX(" %r eax, %r ptr [r11+%r*%d-(%d*%d)+(%s-%s)]",
        ecx, table_type, reg, edx, min, edx, table_addr, base_addr )
    ret

GetJumpDist endp


    assume ebx:ptr hll_item

RenderSwitch proc uses esi edi ebx hll:ptr hll_item, tokenarray:ptr asm_tok,
    buffer:string_t, exit_addr:string_t ; *switch.labels[LEXIT]

   .new lcount:uint_t       ; number of labels in table
   .new icount:uint_t       ; number of index to labels in table
   .new l_start[16]:char_t  ; current start label
   .new l_jtab[16]:char_t   ; jump table address
   .new labelx[16]:char_t   ; case labels
   .new use_index:uchar_t
   .new table_addr:string_t = &l_jtab
   .new start_addr:string_t = &l_start

    mov esi,hll
    mov edi,buffer ; - switch.labels[LSTART]

    ; get static case count

    .new dynamic:uint_t      ; number of dynmaic cases
    .new static:uint_t       ; number of static const values

    .ifd ( GetCaseValue( esi, tokenarray, &dynamic, &static ) && [esi].flags & HLLF_NOTEST )

        ; create a small table

        add eax,MIN_JTABLE
    .endif

    .if ( ModuleInfo.xflag & OPT_NOTABLE || eax < MIN_JTABLE )
        ;
        ; Time NOTABLE/TABLE
        ;
        ; .case *   3   4       7       8       9       10      16      60
        ; NOTABLE 1401  2130    5521    5081    7681    9481    18218   158245
        ; TABLE   1521  3361    4402    6521    7201    7881    9844    68795
        ; elseif  1402  4269    5787    7096    8481    10601   22923   212888
        ;
        RenderCCMP( esi, edi )
       .return
    .endif

   .new table_type:int_t = T_DWORD
ifndef ASMC64
    .if ( ModuleInfo.Ofssize == USE16 )
        mov table_type,T_WORD
    .endif
endif

    strcpy( start_addr, edi )

    ; flip exit to default if exist

    .new case_default:ptr hll_item = NULL

    .if ( [esi].flags & HLLF_ELSEOCCURED )

        .for ( eax = esi, ebx = [esi].caselist: ebx: eax = ebx, ebx = [ebx].caselist )

            .if ( [ebx].flags & HLLF_DEFAULT )

                mov [eax].hll_item.caselist,0
                mov case_default,ebx
                GetLabelStr( [ebx].labels[LSTART*4], exit_addr )
               .break
            .endif
        .endf
    .endif

    .if ( ModuleInfo.casealign && !( [esi].flags & HLLF_JTDATA ) )

        mov cl,ModuleInfo.casealign
        mov eax,1
        shl eax,cl
        AddLineQueueX( " align %d", eax )

    .elseif ( [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE )

        .if ( ModuleInfo.Ofssize == USE64 && !( [esi].flags & HLLF_JTDATA ) )

            AddLineQueue( " align 8" )
        .endif
    .endif
    AddLineQueueX( "%s%s", start_addr, LABELQUAL )

    .if ( dynamic )

        .for ( eax = esi, ebx = [esi].caselist: ebx: eax = ebx, ebx = [ebx].caselist )

            .if !( [ebx].flags & HLLF_NUM )

                mov ecx,[ebx].caselist
                mov [eax].hll_item.caselist,ecx
                RenderCase( esi, ebx, edi )
            .endif
        .endf
    .endif

    .while ( [esi].condlines )

        .new min[2]:int_t ; minimum const value
        .new max[2]:int_t ; maximum const value
        .new min_table:uint_t
        .new max_table:uint_t
        .new dist:int_t = GetMaxCaseValue( esi, &min, &max, &min_table, &max_table )
        .new tcases:uint_t = ecx ; number of cases in table
        .new ncases:uint_t = 0   ; number of cases not in table

        .break .if ( ecx < min_table )

        .for ( ebx = ecx : ebx >= min_table && max > edx && eax > max_table : ebx = tcases )

            GetLowCount ( esi, min, max_table )
            mov ebx,eax
            GetHighCount( esi, max, max_table )

            .switch
            .case ebx < min_table
                .break .if !RemoveVal( esi, min )
                sub tcases,eax
               .endc
            .case eax < min_table
                .break .if !RemoveVal( esi, max )
                sub tcases,eax
               .endc
            .case ebx >= eax
                mov ebx,tcases
                SetLowCount( esi, &tcases, min, max_table )
               .endc
            .default
                mov ebx,tcases
                SetHighCount( esi, &tcases, max, max_table )
               .endc
            .endsw
            add ncases,eax

            GetMaxCaseValue( esi, &min, &max, &min_table, &max_table )
            mov dist,eax
           .break .if ebx == tcases
        .endf

        mov eax,tcases
        .break .if eax < min_table

        mov use_index,0
        .if ( eax < dist && ModuleInfo.Ofssize == USE64 )
            inc use_index
        .endif

        ; Create the jump table lable

        .if ( [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE )

            strcpy( table_addr, start_addr )
            AddLineQueueX( "MIN%s equ %d", eax, min )
        .else
            GetLabelStr( GetHllLabel(), table_addr )
        .endif

        mov edi,exit_addr
        .if ncases
            mov edi,GetLabelStr( GetHllLabel(), start_addr )
        .endif
        mov ebx,[esi].condlines
        .if !( [esi].flags & HLLF_NOTEST )
            CompareMaxMin(ebx, max, min, edi)
        .endif

        mov cl,ModuleInfo.Ofssize
        .if ( [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE )

            .if ( [esi].flags & HLLF_JTDATA )

                AddLineQueueX(
                    ".data\n"
                    "ALIGN 4\n"
                    "DT%s label dword", table_addr )

            .elseif cl == USE64

                mov table_type,T_QWORD
            .endif

        .else

ifndef ASMC64
            .if ( cl == USE16 )

                .if !( ModuleInfo.xflag & OPT_REGAX )
                    AddLineQueue(" push ax")
                .endif
                .if [esi].flags & HLLF_ARGREG
                    .if ModuleInfo.xflag & OPT_REGAX
                        .if tstricmp("ax", ebx)
                            AddLineQueueX( " mov ax, %s", ebx )
                        .endif
                        AddLineQueue(" xchg ax, bx")
                    .else
                        AddLineQueueX(
                            " push bx\n"
                            " push ax")
                        .if tstricmp("bx", ebx)
                            AddLineQueueX(" mov bx, %s", ebx)
                        .endif
                    .endif
                .else
                    .if !( ModuleInfo.xflag & OPT_REGAX )
                        AddLineQueue( " push bx" )
                    .endif
                    GetSwitchArg(T_AX, [esi].flags, ebx)
                    .if ModuleInfo.xflag & OPT_REGAX
                        AddLineQueue(" xchg ax, bx")
                    .else
                        AddLineQueue(" mov bx, ax")
                    .endif
                .endif
                .if min
                    AddLineQueueX(" sub bx, %d", min)
                .endif
                AddLineQueue(" add bx, bx")
                .if ModuleInfo.xflag & OPT_REGAX
                    AddLineQueueX(
                        " mov bx, cs:[bx+%s]\n"
                        " xchg ax, bx\n"
                        " jmp ax", table_addr )
                .else
                    AddLineQueueX(
                        " mov ax, cs:[bx+%s]\n"
                        " mov bx, sp\n"
                        " mov ss:[bx+4], ax\n"
                        " pop ax\n"
                        " pop bx\n"
                        " retn", table_addr )
                .endif

            .elseif ( cl == USE32 )

                .if !( [esi].flags & HLLF_ARGREG )

                    GetSwitchArg(T_EAX, [esi].flags, ebx)
                    .if ( use_index )
                        .if ( dist < 256 )
                            AddLineQueueX( " movzx eax, byte ptr [eax+IT%s-(%d)]", table_addr, min )
                        .else
                            AddLineQueueX( " movzx eax, word ptr [eax*2+IT%s-(%d*2)]", table_addr, min )
                        .endif
                        .if ( ModuleInfo.xflag & OPT_REGAX )
                            AddLineQueueX( " jmp [eax*4+%s]", table_addr )
                        .else
                            AddLineQueueX( " mov eax, [eax*4+%s]", table_addr )
                        .endif
                    .elseif ( ModuleInfo.xflag & OPT_REGAX )
                        AddLineQueueX( " jmp [eax*4+%s-(%d*4)]", table_addr, min )
                    .else
                        AddLineQueueX( " mov eax, [eax*4+%s-(%d*4)]", table_addr, min )
                    .endif
                    .if !( ModuleInfo.xflag & OPT_REGAX )
                        AddLineQueue(
                            " xchg eax, [esp]\n"
                            " retn" )
                    .endif

                .elseif ( use_index )

                    .if !( ModuleInfo.xflag & OPT_REGAX )
                        AddLineQueueX( " push %s", ebx )
                    .endif
                    .if ( dist < 256 )
                        AddLineQueueX( " movzx %s, byte ptr [%s+IT%s-(%d)]",
                            ebx, ebx, table_addr, min )
                    .else
                        AddLineQueueX( " movzx %s, word ptr [%s*2+IT%s-(%d*2)]",
                            ebx, ebx, table_addr, min )
                    .endif
                    .if ( ModuleInfo.xflag & OPT_REGAX )
                        AddLineQueueX( " jmp [%s*4+%s]", ebx, table_addr )
                    .else
                        AddLineQueueX(
                            " mov %s, [%s*4+%s]\n"
                            " xchg %s, [esp]\n"
                            " retn", ebx, ebx, table_addr, ebx )
                    .endif
                .else
                    AddLineQueueX( " jmp [%s*4+%s-(%d*4)]", ebx, table_addr, min )
                .endif

            .else
endif

           .new case_offset:uint_t = 0
            push esi
            .for ( eax = 0, esi = [esi].caselist: esi: esi = [esi].caselist )

                .if ( [esi].flags & HLLF_TABLE )

                    .if SymFind( GetLabelStr( [esi].labels[LSTART*4], &labelx ) )
                        mov case_offset,[eax].asym.offs
                    .endif
                    .break
                .endif
            .endf
            pop esi

            ;
            ; Pack jump table in pass one.
            ;
            .if ( Parse_Pass == PASS_1 && !case_default )

                add GetCurrOffset(),34
                add eax,static

            .elseif SymFind(exit_addr)

                mov eax,[rax].asym.offs
            .endif

            .if ( case_offset && eax )

                sub eax,case_offset

                .if !( eax & 0xFFFFFF00 )
                    mov table_type,T_BYTE
                .elseif !( eax & 0xFFFF0000 )
                    mov table_type,T_WORD
                .endif
            .endif

            .if ( !use_index && ( [esi].flags & ( HLLF_ARGREG or HLLF_ARG3264 ) ) && ( ModuleInfo.xflag & OPT_REGAX ) )

                mov ebx,[esi].tokval
                .if ( ebx == T_R11 || ebx == T_R11D )
                    asmerr( 2008, "register r11 overwritten by .SWITCH" )
                .endif
                AddLineQueue( " push rax" )

                .if ( [esi].flags & HLLF_ARG3264 )
                    ;
                    ; Sign-extend argument if minimum case value is < 0
                    ;
                    .ifs ( min < 0 )

                        AddLineQueueX( " movsxd rax, %r", ebx )
                        mov ebx,T_RAX
                    .else
                        mov ecx,ebx
                        lea ebx,[ebx+T_RAX-T_EAX]
                        .if ( ecx >= T_R8D )
                            lea ebx,[ecx+T_R8-T_R8D]
                        .endif
                    .endif
                .endif

                AddLineQueueX( " lea r11, %s", exit_addr )
                GetJumpDist( table_type, ebx, min, table_addr, exit_addr )
                AddLineQueueX(
                    " sub r11, rax\n"
                    " pop rax\n"
                    " jmp r11" )

            .else

                .if ( ModuleInfo.xflag & OPT_REGAX )

                    AddLineQueue( " push rax" )

                    mov ecx,ebx
                    mov ebx,[esi].tokval

                    .if !( [esi].flags & ( HLLF_ARGREG or HLLF_ARG3264 ) )

                        GetSwitchArg( T_RAX, [esi].flags, ecx )
                        mov ebx,T_RAX

                    .elseif ( [esi].flags & HLLF_ARG3264 )

                        .if ( min < 0 )

                            AddLineQueueX(" movsxd rax, %r", ebx)
                            mov ebx,T_RAX
                        .else
                            mov ecx,ebx
                            lea ebx,[ebx+T_RAX-T_EAX]
                            .if ( ecx >= T_R8D )
                                lea ebx,[ecx+T_R8-T_R8D]
                            .endif
                        .endif
                    .endif

                    AddLineQueueX( " lea r11, %s", exit_addr )
                    mov ecx,min
                    .if ( use_index )
                        .if ( dist < 256 )
                            AddLineQueueX( " movzx eax, byte ptr [r11+%r-(%d)+(IT%s-%s)]",
                                ebx, ecx, table_addr, exit_addr )
                        .else
                            AddLineQueueX( " movzx eax, word ptr [r11+%r*2-(%d*2)+(IT%s-%s)]",
                                ebx, ecx, table_addr, exit_addr )
                        .endif
                        xor ecx,ecx
                    .endif
                    GetJumpDist( table_type, ebx, ecx, table_addr, exit_addr )
                    AddLineQueue(
                        " sub r11, rax\n"
                        " pop rax\n"
                        " jmp r11" )

                .else

                    mov ecx,ebx
                    mov ebx,[esi].tokval

                    .if !( [esi].flags & ( HLLF_ARGREG or HLLF_ARG3264 ) )

                        GetSwitchArg( T_RAX, [esi].flags, ecx )
                        mov ebx,T_RAX

                    .else

                        AddLineQueue(" push rax")

                        .if ( [esi].flags & HLLF_ARG3264 )

                            .if ( min < 0 )

                                AddLineQueueX( " movsxd rax, %r", ebx )
                                mov ebx,T_RAX
                            .else
                                mov ecx,ebx
                                lea ebx,[ebx+T_RAX-T_EAX]
                                .if ( ecx >= T_R8D )
                                    lea ebx,[ecx+T_R8-T_R8D]
                                .endif
                            .endif
                        .endif
                    .endif

                    AddLineQueueX(
                        " push r11\n"
                        " lea r11, %s", exit_addr )

                    mov ecx,min
                    .if ( use_index )
                        .if ( dist < 256 )
                            AddLineQueueX( " movzx eax, byte ptr [r11+%r-(%d)+(IT%s-%s)]",
                                ebx, ecx, table_addr, exit_addr )
                        .else
                            AddLineQueueX( " movzx eax, word ptr [r11+%r*2-(%d*2)+(IT%s-%s)]",
                                ebx, ecx, table_addr, exit_addr )
                        .endif
                        xor ecx,ecx
                    .endif
                    GetJumpDist( table_type, ebx, ecx, table_addr, exit_addr )
                    AddLineQueue(
                        " sub r11, rax\n"
                        " mov rax, [rsp+8]\n"
                        " mov [rsp+8], r11\n"
                        " pop r11\n"
                        " retn" )
                .endif
            .endif
ifndef ASMC64
            .endif
endif

            ;
            ; Create the jump table
            ;
            .if ( table_type != T_BYTE )
                AddLineQueueX("ALIGN %r", table_type )
            .endif
            AddLineQueueX("%s%s", table_addr, LABELQUAL )
        .endif

        .if ( use_index )

            push edi

            .for ( ebx = -1, ; offset
                   edi = -1, ; table index
                   esi = [esi].caselist: esi: esi = [esi].caselist )

                .if ( [esi].flags & HLLF_TABLE )

                    .break .if !SymFind( GetLabelStr( [esi].labels[LSTART*4], &labelx ) )

                    .if ( ebx != [eax].asym.offs )

                        mov ebx,[eax].asym.offs
                        inc edi
                    .endif
                    ;
                    ; use case->next pointer as index...
                    ;
                    mov [esi].next,edi
                .endif
            .endf
            mov edx,esi
            inc edi
            mov lcount,edi

            pop edi

            .for ( esi = hll, ebx = -1,
                   esi = [esi].caselist: esi: esi = [esi].caselist )

                .if ( [esi].flags & HLLF_TABLE && ebx != [esi].next )

ifndef ASMC64
                    .if ( ModuleInfo.Ofssize == USE64 )
endif
                        AddLineQueueX( " %r %s-@C%04X",
                            table_type, exit_addr, [esi].labels[LSTART*4] )
ifndef ASMC64
                    .else
                        AddLineQueueX( " %r @C%04X", table_type, [esi].labels[LSTART*4] )
                    .endif
endif
                    mov ebx,[esi].next
                .endif
            .endf

            mov esi,hll
ifndef ASMC64
            .if ( ModuleInfo.Ofssize == USE64 )
endif
                AddLineQueueX( " %r 0", table_type )
ifndef ASMC64
            .else
                AddLineQueueX( " %r %s", table_type, exit_addr )
            .endif
endif
            mov eax,max
            sub eax,min
            inc eax
            mov icount,eax

            mov ecx,T_BYTE
            .ifs ( eax > 256 )

ifndef ASMC64
                .if ( ModuleInfo.Ofssize == USE16 )

                    .return( asmerr(2022, 1, 2) )
                .endif
endif
                mov ecx,T_WORD
            .endif

            .new index_type:int_t = ecx

            AddLineQueueX( "IT%s label %r", table_addr, ecx )

            .for ( ebx = 0: ebx < icount: ebx++ )
                ;
                ; loop from min value
                ;
                mov eax,min
                add eax,ebx

                .if GetCaseVal( esi, eax )
                    ;
                    ; Unlink block
                    ;
                    mov edx,[eax].hll_item.caselist
                    mov [ecx].hll_item.caselist,edx
                    ;
                    ; write block to table
                    ;
                    AddLineQueueX( " %r %d", index_type, [eax].hll_item.next )

                .else
                    ;
                    ; else make a jump to exit or default label
                    ;
                    AddLineQueueX( " %r %d", index_type, lcount )
                .endif
            .endf

            .if ( table_type != T_BYTE )
                AddLineQueueX( "ALIGN %r", table_type )
            .endif

        .else

            .for ( ebx = 0: ebx < dist: ebx++ )
                ;
                ; loop from min value
                ;
                mov eax,min
                add eax,ebx

                .if GetCaseVal( esi, eax )
                    ;
                    ; Unlink block
                    ;
                    mov edx,[eax].hll_item.caselist
                    mov [ecx].hll_item.caselist,edx
                    ;
                    ; write block to table
                    ;
                    mov ecx,[eax].hll_item.labels[LSTART*4]
ifndef ASMC64
                    .if ( ModuleInfo.Ofssize == USE64 )
endif
                        AddLineQueueX( " %r %s-@C%04X", table_type, exit_addr, ecx )
ifndef ASMC64
                    .else

                        AddLineQueueX( " %r @C%04X", table_type, ecx )
                    .endif
endif
                .else
                    ;
                    ; else make a jump to exit or default label
                    ;
ifndef ASMC64
                    .if ( ModuleInfo.Ofssize == USE64 )
endif
                        AddLineQueueX( " %r 0", table_type )
ifndef ASMC64
                    .else
                        AddLineQueueX( " %r %s", table_type, exit_addr )
                    .endif
endif
                .endif
            .endf
        .endif

        .if ( [esi].flags & HLLF_JTDATA )

            AddLineQueue( ".code" )
        .endif

        .if ( ncases )
            ;
            ; Create the new start label
            ;
            AddLineQueueX( "%s%s", start_addr, LABELQUAL )

            .for ( ebx = [esi].caselist: ebx: ebx = [ebx].caselist )

                or [ebx].flags,HLLF_TABLE
            .endf
        .endif
    .endw

    .for ( ebx = [esi].caselist: ebx: ebx = [ebx].caselist )

        RenderCase( esi, ebx, buffer )
    .endf

    .if ( case_default && [rsi].caselist )

        AddLineQueueX( " jmp %s", exit_addr )
    .endif
    ret

RenderSwitch endp


    assume  esi: ptr hll_item

RenderJTable proc uses esi edi ebx hll:ptr hll_item

  local l_exit[16]:char_t, l_jtab[16]:char_t ; jump table address
  local minsym[32]:char_t

    mov esi,hll
    lea edi,l_jtab

    .if [esi].labels[LEXIT*4] == 0
        mov [esi].labels[LEXIT*4],GetHllLabel()
    .endif
    .if [esi].labels[LSTARTSW*4] == 0
        mov [esi].labels[LSTARTSW*4],GetHllLabel()
    .endif

    AddLineQueueX( "@C%04X%s", [rsi].labels[LSTARTSW*4], LABELQUAL )

    GetLabelStr( [esi].labels[LSTART*4], edi )
    GetLabelStr( [esi].labels[LEXIT*4], &l_exit )

    mov ebx,[esi].tokval

ifndef ASMC64
    mov cl,ModuleInfo.Ofssize
    .if cl == USE16

        .if ModuleInfo.xflag & OPT_REGAX
            .if ( ebx != T_AX )
                AddLineQueueX( " mov ax, %r", ebx )
            .endif
            AddLineQueueX(
                " xchg ax, bx\n"
                " add bx, bx\n"
                " mov bx, cs:[bx+%s]\n"
                " xchg ax, bx\n"
                " jmp ax", edi )
        .else
            AddLineQueue(
                " push ax\n"
                " push bx\n"
                " push ax" )
            .if ( ebx != T_BX )
                AddLineQueueX( " mov bx, %r", ebx )
            .endif
            AddLineQueueX(
                " add bx, bx\n"
                " mov ax, cs:[bx+%s]\n"
                " mov bx, sp\n"
                " mov ss:[bx+4], ax\n"
                " pop ax\n"
                " pop bx\n"
                " retn", edi )
        .endif

    .elseif cl == USE32

        .if ( [esi].flags & HLLF_JTDATA )
            AddLineQueueX( " jmp [%r*4+DT%s-(MIN%s*4)]", ebx, edi, edi )
        .else
            AddLineQueueX( " jmp [%r*4+%s-(MIN%s*4)]", ebx, edi, edi )
        .endif

    .else
endif
        .if ( [esi].flags & HLLF_ARG3264 )
           ;
           ; Sign-extend argument if minimum case value is < 0
           ;
            tsprintf(&minsym, "MIN%s", edi )
            .if SymFind(&minsym)
                mov ecx,eax
                xor eax,eax
                .if ( [ecx].asym.value3264 < 0 )
                    inc eax
                .endif
            .endif

            mov ecx,ebx
            lea ebx,[ebx+T_RAX-T_EAX]
            .if ( ecx >= T_R8D )
                lea ebx,[ecx+T_R8-T_R8D]
            .endif
            .if ( eax )
                AddLineQueueX(" movsxd %r, %r", ebx, ecx)
            .endif
        .endif

        .if ( ModuleInfo.xflag & OPT_REGAX ) ; defualt for 64-bit

            .ifd ( ebx == T_R11 || ebx == T_R11D )
                asmerr( 2008, "register r11 overwritten by .SWITCH" )
            .endif

            AddLineQueueX(
                " lea r11, %s\n"
                " sub r11, [%r*8+r11-(MIN%s*8)+(%s-%s)]\n"
                " jmp r11", &l_exit, ebx, edi, edi, &l_exit )
        .else

            mov esi,T_RAX
            .if ( ebx == esi )
                mov esi,T_RDX
            .endif
            AddLineQueueX(
                " push %r\n"
                " lea  %r, %s\n"
                " sub  %r, [%r+%r*8-(MIN%s*8)+(%s-%s)]\n"
                " xchg %r, [rsp]\n"
                " retn", esi, esi, &l_exit, esi, esi, ebx, edi, edi, &l_exit, esi )
        .endif
ifndef ASMC64
    .endif
endif
    ret

RenderJTable endp


    assume  ebx: ptr asm_tok

SwitchStart proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local rc:int_t, cmd:uint_t, buffer[MAX_LINE_LEN]:char_t
  local opnd:expr
  local brackets:byte

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,buffer

    imul eax,i,asm_tok
    mov eax,[ebx+eax].tokval
    mov cmd,eax
    inc i

    mov esi,ModuleInfo.HllFree
    .if !esi
        mov esi,LclAlloc( hll_item )
    .endif
    ExpandCStrings(tokenarray)

    xor eax,eax
    mov [esi].labels[LSTART*4],eax  ; set by .CASE
    mov [esi].labels[LTEST*4],eax   ; set by .CASE
    mov [esi].labels[LEXIT*4],eax   ; set by .BREAK
    mov [esi].labels[LSTARTSW*4],eax; set by .GOTOSW
    mov [esi].condlines,eax
    mov [esi].caselist,eax
    mov [esi].cmd,HLL_SWITCH

    imul edx,i,asm_tok  ; v2.27.38: .SWITCH [NOTEST] [C|PASCAL] ...
                        ; v2.30.07: .SWITCH [JMP] [C|PASCAL] ...
    mov eax,HLLF_WHILE

    mov brackets,0
    .while ( [ebx+edx].token == T_OP_BRACKET )

        inc i
        inc brackets
        add edx,asm_tok
    .endw

    .if ( [ebx+edx].tokval == T_JMP )

        inc i
        or eax,HLLF_NOTEST
    .endif

    .if ( [ebx+edx].token == T_ID )

        mov ecx,[ebx+edx].string_ptr
        mov ecx,[ecx]
        or  cl,0x20
        .if ( cx == 'c' )
            mov [ebx+edx].tokval,T_CCALL
            mov [ebx+edx].token,T_RES_ID
            mov [ebx+edx].bytval,1
        .endif
    .endif

    .if [ebx+edx].tokval == T_CCALL

        inc i
        add edx,asm_tok

    .elseif [ebx+edx].tokval == T_PASCAL

        inc i
        add edx,asm_tok
        or eax,HLLF_PASCAL

    .elseif ModuleInfo.xflag & OPT_PASCAL

        or eax,HLLF_PASCAL
    .endif

    mov [esi].flags,eax

    .if [ebx+edx].token != T_FINAL

        .return .if ExpandHllProc(edi, i, ebx) == ERROR

        .if BYTE PTR [edi]

            QueueTestLines(edi)

            ; v2.33.38 -- the result may differ from inline RETM<al>

        .endif

        imul ecx,i,asm_tok
        mov eax,[ebx+ecx].tokval
        mov [esi].tokval,eax

        .switch eax
        .case T_R8W .. T_R15W
        .case T_AX .. T_DI
            or  [esi].flags,HLLF_ARG16
ifndef ASMC64
            .if ModuleInfo.Ofssize == USE16
                or [esi].flags,HLLF_ARGREG
                .if [esi].flags & HLLF_NOTEST
                    or [esi].flags,HLLF_JTABLE
                .endif
            .endif
endif
        .case T_SPL .. T_R15B
        .case T_AL .. T_BH
            .endc
        .case T_R8D .. T_R15D
        .case T_EAX .. T_EDI
            or  [esi].flags,HLLF_ARG32
ifndef ASMC64
            .if ModuleInfo.Ofssize == USE32
                or [esi].flags,HLLF_ARGREG
                .if [esi].flags & HLLF_NOTEST
                    or [esi].flags,HLLF_JTABLE
                    .if !( [esi].flags & HLLF_PASCAL )
                        or [esi].flags,HLLF_JTDATA
                    .endif
                .endif
            .endif
            .if ModuleInfo.Ofssize == USE64
endif
                or [esi].flags,HLLF_ARG3264
                .if [esi].flags & HLLF_NOTEST
                    or [esi].flags,HLLF_JTABLE or HLLF_ARGREG
                .endif
ifndef ASMC64
            .endif
endif
            .endc

        .case T_RAX .. T_R15
            or  [esi].flags,HLLF_ARG64
            .if ModuleInfo.Ofssize == USE64
                or [esi].flags,HLLF_ARGREG
                .if [esi].flags & HLLF_NOTEST
                    or [esi].flags,HLLF_JTABLE
                .endif
            .endif
            .endc

        .default
            or [esi].flags,HLLF_ARGMEM
            push i
            EvalOperand(&i, tokenarray, ModuleInfo.token_count, &opnd, EXPF_NOERRMSG)
            pop ecx
            mov i,ecx

            .if ( eax != ERROR )
                mov eax,8
ifndef ASMC64
                .if ( ModuleInfo.Ofssize == USE16 )
                    mov eax,2
                .elseif ( ModuleInfo.Ofssize == USE32 )
                    mov eax,4
                .endif
endif
                .if ( opnd.kind == EXPR_ADDR && opnd.mem_type != MT_EMPTY )
                    SizeFromMemtype( opnd.mem_type, opnd.Ofssize, opnd.type )
                .endif
                .if eax == 2
                    or [esi].flags,HLLF_ARG16
                .elseif eax == 4
                    or [esi].flags,HLLF_ARG32
                .elseif eax == 8
                    or [esi].flags,HLLF_ARG64
                .endif
            .endif
        .endsw

        imul ecx,Token_Count,asm_tok
        .while ( brackets && [ebx+ecx-asm_tok].token == T_CL_BRACKET )
            sub ecx,asm_tok
            dec brackets
        .endw
        mov ecx,[ebx+ecx].tokpos
        imul eax,i,asm_tok
        mov edi,[ebx+eax].tokpos
        .while ( ecx > edi && byte ptr [ecx-1] <= ' ' )
            dec ecx
        .endw
        sub ecx,edi
        mov ebx,ecx
        inc ecx
        LclAlloc(ecx)
        mov [esi].condlines,eax
        mov edx,esi
        mov ecx,ebx
        mov esi,edi
        mov edi,eax
        rep movsb
        mov esi,edx
        mov byte ptr [edi],0
        mov ebx,tokenarray
    .endif

    imul eax,i,asm_tok
    .if ![esi].flags && ( [ebx+eax].asm_tok.token != T_FINAL && rc == NOT_ERROR )

        mov rc,asmerr( 2008, [ebx+eax].asm_tok.tokpos )
    .endif

    .if esi == ModuleInfo.HllFree
        mov eax,[esi].next
        mov ModuleInfo.HllFree,eax
    .endif
    mov eax,ModuleInfo.HllStack
    mov [esi].next,eax
    mov ModuleInfo.HllStack,esi
   .return rc

SwitchStart endp


SwitchEnd proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local rc:int_t, cmd:int_t, buffer[MAX_LINE_LEN]:char_t,
        l_exit[16]:char_t ; exit or default label

    mov esi,ModuleInfo.HllStack
    .return asmerr(1011) .if !esi

    mov eax,[esi].next
    mov ecx,ModuleInfo.HllFree
    mov ModuleInfo.HllStack,eax
    mov [esi].next,ecx
    mov ModuleInfo.HllFree,esi
    mov rc,NOT_ERROR
    lea edi,buffer
    mov ebx,tokenarray

    mov ecx,[esi].cmd
    .return asmerr(1011) .if ecx != HLL_SWITCH

    inc i
    .repeat

        .break .if [esi].labels[LTEST*4] == 0
        .if [esi].labels[LSTART*4] == 0
            mov [esi].labels[LSTART*4],GetHllLabel()
        .endif
        .if [esi].labels[LEXIT*4] == 0
            mov [esi].labels[LEXIT*4],GetHllLabel()
        .endif

        GetLabelStr([esi].labels[LEXIT*4], &l_exit)
        GetLabelStr([esi].labels[LSTART*4], edi)

        mov eax,esi
        .while ( [eax].hll_item.caselist )
            mov eax,[eax].hll_item.caselist
        .endw
        .if ( eax != esi && !( [eax].hll_item.flags & HLLF_ENDCOCCUR ) )
            .if !( [esi].flags & HLLF_JTDATA )
                AddLineQueueX( " jmp @C%04X", [esi].labels[LEXIT*4] )
            .endif
        .endif

        mov ebx,[esi].caselist
        assume ebx:ptr hll_item

        mov cl,ModuleInfo.casealign
        .if cl
            mov eax,1
            shl eax,cl
            AddLineQueueX( "ALIGN %d", eax )
        .endif

        .if ( ![esi].condlines )

            AddLineQueueX( "%s%s", edi, LABELQUAL )

            .while ( ebx )

                .if ( ![ebx].condlines )

                    AddLineQueueX( " jmp @C%04X", [ebx].labels[LSTART*4] )
                .elseif ( [ebx].flags & HLLF_EXPRESSION )
                    mov i,1
                    or  [ebx].flags,HLLF_WHILE
                    ExpandHllExpression( ebx, &i, tokenarray, LSTART, 1, edi )
                .else
                    QueueTestLines( [ebx].condlines )
                .endif
                mov ebx,[ebx].caselist
            .endw
        .else
            RenderSwitch( esi, tokenarray, edi, &l_exit )
        .endif

        assume ebx:ptr asm_tok
    .until 1

    mov eax,[esi].labels[LEXIT*4]
    .if eax
        AddLineQueueX( "@C%04X%s", eax, LABELQUAL )
    .endif
    .return rc

SwitchEnd endp


SwitchExit proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local rc:     int_t,
        cmd:    int_t,
        buff    [16]:char_t,
        buffer  [MAX_LINE_LEN]:char_t,
        gotosw: int_t,
        hll:    ptr hll_item

    mov esi,ModuleInfo.HllStack
    mov hll,esi

    .return asmerr(1011) .if !esi

    ExpandCStrings(tokenarray)

    lea edi,buffer
    mov rc,NOT_ERROR
    imul ebx,i,asm_tok
    add ebx,tokenarray
    mov eax,[ebx].tokval
    mov cmd,eax
    xor ecx,ecx     ; exit level 0,1,2,3

    .switch eax

      .case T_DOT_DEFAULT
        .return asmerr(2142) .if ( [esi].flags & HLLF_ELSEOCCURED )
        .return asmerr(2008, [ebx].tokpos) .if ( [ebx+asm_tok].token != T_FINAL )

        or [esi].flags,HLLF_ELSEOCCURED

      .case T_DOT_CASE

        .while ( esi && [esi].cmd != HLL_SWITCH )

            mov esi,[esi].next
        .endw

        .return asmerr(1010, [ebx].string_ptr) .if [esi].cmd != HLL_SWITCH

        .if ( [esi].labels[LSTART*4] == 0 )

            ;; First case..

            mov [esi].labels[LSTART*4],GetHllLabel()

            .if ( [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE )
                RenderJTable(esi)
            .else
                AddLineQueueX( " jmp @C%04X", eax )
            .endif

        .elseif ( [esi].flags & HLLF_PASCAL )

                .if ( [esi].labels[LEXIT*4] == 0 )
                    mov [esi].labels[LEXIT*4],GetHllLabel()
                .endif
                mov eax,esi
                .while [eax].hll_item.caselist
                    mov eax,[eax].hll_item.caselist
                .endw
                .if ( eax != esi && !( [eax].hll_item.flags & HLLF_ENDCOCCUR ) )
                    AddLineQueueX( " jmp @C%04X", [esi].labels[LEXIT*4] )
                .endif
if 0
        .elseif ( Parse_Pass == PASS_1 )
                ;
                ; error A7007: .CASE without .ENDC: assumed fall through
                ;
                mov eax,esi
                .while ( [eax].hll_item.caselist )
                    mov eax,[eax].hll_item.caselist
                .endw
                .if ( eax != esi && !( [eax].hll_item.flags & HLLF_ENDCOCCUR ) )
                    asmerr( 7007 )
                .endif
endif
        .endif

        ; .case <case_a> a

        .new case_name:string_t = NULL
        .if ( [ebx+asm_tok].token == T_STRING &&
              [ebx+2*asm_tok].token == T_ID &&
              [ebx+3*asm_tok].token == T_STRING )

            mov case_name,[ebx+2*asm_tok].string_ptr
            add ebx,3*asm_tok
            add i,3
        .endif

        ; .case a, b, c, ...

        .endc .if RenderMultiCase(esi, &i, edi, ebx)

        mov cl,ModuleInfo.casealign
        .if cl

            mov eax,1
            shl eax,cl
            AddLineQueueX("ALIGN %d", eax)
        .endif

        inc [esi].labels[LTEST*4]

       .new case_label:uint_t = GetHllLabel()
        AddLineQueueX( "@C%04X%s", eax, LABELQUAL )
        .if ( case_name )
            AddLineQueueX( "%s:", case_name )
        .endif

        LclAlloc( hll_item )
        mov ecx,case_label
        mov edx,esi
        mov esi,eax
        mov eax,[edx].hll_item.condlines
        mov [esi].labels[LSTART*4],ecx
        .while [edx].hll_item.caselist

            mov edx,[edx].hll_item.caselist
        .endw
        mov [edx].hll_item.caselist,esi

        inc i   ; skip past the .case token
        add ebx,asm_tok

        push eax ;
        push ebx ; handle .case <expression> : ...
        push esi ;

        .for ( esi = 0 : IsCaseColon(ebx) : ebx += asm_tok, esi = [ebx].tokpos )

            mov ebx,eax
            .if esi
                mov eax,[ebx].tokpos
                mov BYTE PTR [eax],0
                AddLineQueue(esi)
                mov eax,[ebx].tokpos
                mov BYTE PTR [eax],':'
            .else
                sub eax,tokenarray
                shr eax,4
                mov ModuleInfo.token_count,eax
            .endif
        .endf

        .if esi
            AddLineQueue(esi)
        .endif

        pop esi
        pop ebx
        pop eax

        .if eax && cmd != T_DOT_DEFAULT

            push eax
            push ebx
            push edi
            xor  edi,edi

            .while 1
                movzx eax,[ebx].token
                ;
                ; .CASE BYTE PTR [reg+-*imm]
                ; .CASE ('A'+'L') SHR (8 - H_BITS / ... )
                ;
                .switch eax

                  .case T_CL_BRACKET
                    .if edi == 1

                        .if [ebx+asm_tok].token == T_FINAL

                            or [esi].flags,HLLF_NUM
                            .break
                        .endif
                    .endif
                    sub edi,2
                  .case T_OP_BRACKET
                    inc edi
                  .case T_PERCENT   ; %
                  .case T_INSTRUCTION   ; XOR, OR, NOT,...
                  .case '+'
                  .case '-'
                  .case '*'
                  .case '/'
                    .endc

                  .case T_NUM
                  .case T_STRING
                    .if [ebx+asm_tok].token == T_FINAL

                        or [esi].flags,HLLF_NUM
                        .break
                    .endif
                    .endc

                  .case T_STYPE ; BYTE, WORD, ...
                    .break .if [ebx+asm_tok].tokval == T_PTR
                    .gotosw(T_STRING)

                  .case T_FLOAT ; 1..3 ?
                    .break  .if [ebx+asm_tok].token == T_DOT
                    .gotosw(T_STRING)

                  .case T_UNARY_OPERATOR    ; offset x
                    .break .if [ebx].tokval != T_OFFSET
                    .gotosw(T_STRING)

                  .case T_ID
                    .if SymFind( [ebx].string_ptr )

                        .break .if [eax].asym.state != SYM_INTERNAL
                        .break .if !([eax].asym.mem_type == MT_NEAR || \
                                      [eax].asym.mem_type == MT_EMPTY)
                    .elseif Parse_Pass != PASS_1

                        .break
                    .endif
                    .gotosw(T_STRING)

                  .default
                    ; T_REG
                    ; T_OP_SQ_BRACKET
                    ; T_DIRECTIVE
                    ; T_QUESTION_MARK
                    ; T_BAD_NUM
                    ; T_DBL_COLON
                    ; T_CL_SQ_BRACKET
                    ; T_COMMA
                    ; T_COLON
                    ; T_FINAL
                    .break
                .endsw
                add ebx,16
            .endw
            pop edi
            pop ebx
            pop eax
        .endif

        .if cmd == T_DOT_DEFAULT

            or [esi].flags,HLLF_DEFAULT
        .else

            .return asmerr(2008, [ebx-asm_tok].tokpos) .if ( [ebx].token == T_FINAL )

            .if !eax

                mov ebx,i
                EvaluateHllExpression( esi, &i, tokenarray, LSTART, 1, edi )
                mov i,ebx
                mov rc,eax
                .endc .if eax == ERROR

            .else

                imul eax,ModuleInfo.token_count,asm_tok
                add eax,tokenarray
                mov eax,[eax].asm_tok.tokpos
                sub eax,[ebx].tokpos
                mov WORD PTR [edi+eax],0
                memcpy(edi, [ebx].tokpos, eax)
            .endif

            strlen(edi)
            inc eax
            push eax
            LclAlloc(eax)
            pop ecx
            mov [esi].condlines,eax
            memcpy(eax, edi, ecx)
        .endif

        mov eax,ModuleInfo.token_count
        mov i,eax
        .endc

      .case T_DOT_ENDC

        .for ( : esi, [esi].cmd != HLL_SWITCH : esi = [esi].next )

        .endf

        .for ( : esi, ecx : ecx-- )
            .for ( esi = [esi].next: esi, [esi].cmd != HLL_SWITCH: esi = [esi].next )

            .endf
        .endf
        .return asmerr(1011) .if !esi

        .if [esi].labels[LEXIT*4] == 0
            mov [esi].labels[LEXIT*4],GetHllLabel()
        .endif
        mov ecx,LEXIT
        .if cmd != T_DOT_ENDC
            mov ecx,LSTART
        .endif

        inc i
        add ebx,16
        mov gotosw,0

        .if ( ecx == LSTART && [ebx].token == T_OP_BRACKET )

            ;; .gotosw([n:]<text>)

            .if ( [ebx+16].token != T_FINAL && [ebx+32].token == T_COLON )

                add i,2
                add ebx,32
            .endif
            mov eax,[ebx+16].tokpos

            .for ( i++, ebx += 16, ecx = 1 : [ebx].token != T_FINAL : i++, ebx += 16 )

                .if ( [ebx].token == T_OP_BRACKET )
                    inc ecx
                .elseif ( [ebx].token == T_CL_BRACKET )
                    dec ecx
                    .break .ifz
                .endif
            .endf
            .endc .if ( [ebx].token != T_CL_BRACKET )

            inc i
            add ebx,16

            .repeat

                .break .if ( [ebx-32].token == T_OP_BRACKET )   ; .gotosw()
                .break .if ( [ebx-32].token == T_COLON )        ; .gotosw(n:)

                ; get size of string

                mov ecx,[ebx-16].tokpos
                sub ecx,eax
                .break .ifz

                .endc .if ecx > MAX_LINE_LEN - 32

                ; copy string

                push esi
                push ecx
                memcpy(edi, eax, ecx)
                pop ecx
                add ecx,eax
                mov byte ptr [ecx],0
                .for ( ecx-- : ecx > eax && byte ptr [ecx] <= ' ' : ecx-- )

                    mov byte ptr [ecx],0
                .endf

                ; find the string

                .for ( esi = [esi].caselist : esi : esi = [esi].caselist )
                    .if ( [esi].condlines )
                        .if !tstrcmp(edi, [esi].condlines)

                            mov ecx,[esi].labels[LSTART*4]
                            .break
                        .endif
                    .endif
                .endf
                mov eax,esi
                pop esi

                .if eax

                    mov edx,[esi].labels[LSTART*4]
                    mov [esi].labels[LSTART*4],ecx
                    mov gotosw,edx

                .elseif [esi].condlines

                    ; -- this overwrites the switch argument

                    AddLineQueueX(" mov %s, %s", [esi].condlines, edi)

                    mov eax,[esi].labels[LSTARTSW*4]
                    .if ( eax )

                        mov edx,[esi].labels[LSTART*4]
                        mov [esi].labels[LSTART*4],eax
                        mov gotosw,edx
                    .endif
                .endif

            .until 1
            mov ecx,LSTART

        .elseif ( ecx == LSTART && [esi].labels[LSTARTSW*4] )

            mov eax,[esi].labels[LSTARTSW*4]
            mov edx,[esi].labels[LSTART*4]
            mov [esi].labels[LSTART*4],eax
            mov gotosw,edx
        .endif

        HllContinueIf(esi, &i, tokenarray, ecx, hll, 1)
        .if gotosw
            mov [esi].labels[LSTART*4],gotosw
        .endif
        .endc

      .case T_DOT_GOTOSW

        .if ( [ebx+16].token == T_OP_BRACKET && [ebx+48].token == T_COLON )

            ; .gotosw(n:

            mov eax,[ebx+32].string_ptr
            mov al,[eax]

            .if ( al >= '0' && al <= '9' )

                sub al,'0'
                movzx ecx,al
            .endif
        .endif
        .gotosw(T_DOT_ENDC)
    .endsw

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    .if [ebx].token != T_FINAL && rc == NOT_ERROR

        asmerr(2008, [ebx].tokpos)
        mov rc,ERROR
    .endif
    mov eax,rc
    ret

SwitchExit endp


    option proc: public

SwitchDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

    mov ecx,i
    mov edx,tokenarray
    mov eax,ecx
    shl eax,4
    mov eax,[edx+eax].asm_tok.tokval
    xor ebx,ebx

    .switch eax
      .case T_DOT_CASE
      .case T_DOT_GOTOSW
      .case T_DOT_DEFAULT
      .case T_DOT_ENDC
        mov ebx,SwitchExit(ecx, edx)
        .endc
      .case T_DOT_ENDSW
        mov ebx,SwitchEnd(ecx, edx)
        .endc
      .case T_DOT_SWITCH
        mov ebx,SwitchStart(ecx, edx)
        .endc
    .endsw

    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    .return ebx

SwitchDirective endp

    END
