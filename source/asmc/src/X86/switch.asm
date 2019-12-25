include string.inc
include stdio.inc
include stdlib.inc
include malloc.inc
include limits.inc

include asmc.inc
include token.inc
include hllext.inc

    .code

    option proc: private
    assume esi:  hll_t

.pragma warning(disable: 6004)

LQAddLabelIdBuffer proc fastcall id, buffer

    AddLineQueueX( "%s%s", GetLabelStr( id, buffer ), LABELQUAL )
    ret

LQAddLabelIdBuffer endp


LQAddLabelId proc id

  local buffer[32]:sbyte

    LQAddLabelIdBuffer(id, &buffer)
    ret

LQAddLabelId endp


LQJumpLabel proc x, id

  local buffer[32]:sbyte

    AddLineQueueX("%r %s", x, GetLabelStr(id, &buffer))
    ret

LQJumpLabel endp


LQJumpLabel64 proc x, base, id

  local buffer[32]:sbyte

    AddLineQueueX("%r %s-%s", x, base, GetLabelStr(id, &buffer))
    ret

LQJumpLabel64 endp


RenderCase proc uses esi edi ebx hll:hll_t, case:hll_t, buffer:string_t

    mov esi,hll
    mov ebx,case
    mov edi,buffer
    mov edx,[ebx].hll_item.condlines

    .if !edx

        LQJumpLabel( T_JMP, [ebx].hll_item.labels[LSTART*4] )

    .elseif strchr(edx, '.') && BYTE PTR [eax+1] == '.'

        mov BYTE PTR [eax],0
        add eax,2
        push    eax
        AddLineQueueX( "cmp %s,%s", [esi].condlines, edx )
        mov edi,GetHllLabel()
        LQJumpLabel( T_JB, edi )
        pop eax
        AddLineQueueX( "cmp %s,%s", [esi].condlines, eax )
        LQJumpLabel( T_JBE, [ebx].hll_item.labels[LSTART*4] )
        LQAddLabelId(edi)

    .else

        AddLineQueueX( "cmp %s,%s", [esi].condlines, edx )
        LQJumpLabel( T_JE, [ebx].hll_item.labels[LSTART*4] )

    .endif
    ret

RenderCase endp

RenderCCMP proc uses esi edi ebx hll:hll_t, buffer:string_t

    mov esi,hll
    mov edi,buffer
    AddLineQueueX( "%s%s", edi, LABELQUAL )
    mov ebx,[esi].caselist
    .while  ebx

        RenderCase( esi, ebx, edi )
        mov ebx,[ebx].hll_item.caselist
    .endw
    ret

RenderCCMP endp

GetLowCount proc hll:hll_t, min, dist

    mov ecx,min
    add ecx,dist
    mov edx,hll
    xor eax,eax
    mov edx,[edx].hll_item.caselist

    .while edx
        .ifs [edx].hll_item.flags & HLLF_TABLE && ecx >= [edx].hll_item.labels

            add eax,1
        .endif
        mov edx,[edx].hll_item.caselist
    .endw
    ret

GetLowCount endp

GetHighCount proc hll:hll_t, max, dist

    mov ecx,max
    sub ecx,dist
    mov edx,hll
    xor eax,eax
    mov edx,[edx].hll_item.caselist

    .while edx
        .ifs [edx].hll_item.flags & HLLF_TABLE && ecx <= [edx].hll_item.labels

            add eax,1
        .endif
        mov edx,[edx].hll_item.caselist
    .endw
    ret

GetHighCount endp

SetLowCount proc uses esi hll:hll_t, count, min, dist

    mov ecx,min
    mov edx,count
    add ecx,dist
    xor eax,eax
    mov esi,hll
    mov esi,[esi].caselist

    .while  esi
        .ifs [esi].flags & HLLF_TABLE && ecx < [esi].labels

            and [esi].flags,NOT HLLF_TABLE
            dec DWORD PTR [edx]
            add eax,1
        .endif
        mov esi,[esi].caselist
    .endw
    mov edx,[edx]
    ret

SetLowCount endp

SetHighCount proc uses esi hll:hll_t, count, max, dist

    mov ecx,max
    mov edx,count
    sub ecx,dist
    xor eax,eax
    mov esi,hll
    mov esi,[esi].caselist

    .while esi

        .ifs [esi].flags & HLLF_TABLE && ecx > [esi].labels

            and [esi].flags,NOT HLLF_TABLE
            dec DWORD PTR [edx]
            add eax,1
        .endif
        mov esi,[esi].caselist
    .endw
    mov edx,[edx]
    ret

SetHighCount endp

GetCaseVal proc fastcall private hll, val

    mov eax,[ecx].hll_item.caselist
    .while eax

        .if [eax].hll_item.flags & HLLF_TABLE && \
            [eax].hll_item.labels == edx

            .break
        .endif
        mov ecx,eax
        mov eax,[eax].hll_item.caselist
    .endw
    ret

GetCaseVal endp

RemoveVal proc fastcall private hll, val

    .if GetCaseVal()

        and [eax].hll_item.flags,NOT HLLF_TABLE
        mov eax,1
    .endif
    ret

RemoveVal endp

GetCaseValue proc uses esi edi ebx hll, tokenarray, dcount, scount

  local i, opnd:expr

    xor edi,edi ; dynamic count
    xor ebx,ebx ; static count

    mov esi,hll
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

            mov eax,DWORD PTR opnd.value64
            mov edx,DWORD PTR opnd.value64[4]
            .if opnd.kind == EXPR_ADDR

                mov ecx,opnd.sym
                add eax,[ecx].asym._offset
                xor edx,edx
            .endif
            mov [esi].labels[LTEST*4],eax
            mov [esi].labels[LEXIT*4],edx
            inc ebx
        .elseif [esi].condlines

            inc edi
        .endif
        mov esi,[esi].caselist
    .endw

    Tokenize( ModuleInfo.currsource, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax

    mov eax,dcount
    mov [eax],edi
    mov eax,scount
    mov [eax],ebx
    ;
    ; error A3022 : .CASE redefinition : %s(%d) : %s(%d)
    ;
    .if ebx && Parse_Pass != PASS_1

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

GetMaxCaseValue proc uses esi edi ebx hll, min, max, min_table, max_table

    mov esi,hll
    xor edi,edi
    mov eax,80000000h
    mov edx,7FFFFFFFh
    mov esi,[esi].caselist

    .while esi

        .if [esi].flags & HLLF_TABLE

            inc edi
            mov ecx,[esi].labels
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

    assume esi:tok_t

IsCaseColon proc uses esi edi ebx tokenarray:tok_t

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

    assume  ebx: tok_t

RenderMultiCase proc uses esi edi ebx hll:hll_t, i:ptr SDWORD, buffer:ptr char_t,
        tokenarray:tok_t

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

            mov edx,[ebx].tokpos
            mov BYTE PTR [edx],0
            strcpy( buffer, [esi].tokpos )
            lea esi,[ebx+16]
            mov BYTE PTR [edx],','

            inc result
            AddLineQueueX( ".case %s", buffer )
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

        AddLineQueueX( ".case %s", [esi].tokpos )

        mov ebx,tokenarray
        xor eax,eax
        .while [ebx].token != T_FINAL

            add eax,1
            add ebx,16
        .endw
        mov ebx,i
        mov [ebx],eax

        mov esi,hll
        assume esi:hll_t

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

CompareMaxMin proc reg, max, min, around
    AddLineQueueX( "cmp %s,%d", reg, min )
    AddLineQueueX( "jl %s", around )
    AddLineQueueX( "cmp %s,%d", reg, max )
    AddLineQueueX( "jg %s", around )
    ret
CompareMaxMin endp

;
; Move .SWITCH <arg> to [R|E]AX
;
GetSwitchArg proc uses ebx reg, flags, arg

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
ifndef __ASMC64__
        mov ecx,ModuleInfo.curr_cpu
        and ecx,P_CPU_MASK
        .if ecx >= P_386
endif
            .if eax & HLLF_ARGMEM

                AddLineQueueX( "movsx %r,BYTE PTR %s", edx, ebx )
            .else
                AddLineQueueX( "movsx %r,%s", edx, ebx )
            .endif
ifndef __ASMC64__
        .else
            .if _stricmp( "al", ebx )

                AddLineQueueX( "mov al,%s", ebx )
            .endif
            AddLineQueue ( "cbw" )
        .endif
endif
    .elseif eax & HLLF_ARG16
        ;
        ; WORD value
        ;
ifndef __ASMC64__
        .if ModuleInfo.Ofssize == USE16

            .if eax & HLLF_ARGMEM

                AddLineQueueX( "mov %r,WORD PTR %s", edx, ebx )
            .elseif _stricmp( ebx, &buffer )

                AddLineQueueX( "mov %r,%s", edx, ebx )
            .endif
        .elseif eax & HLLF_ARGMEM
else
        .if eax & HLLF_ARGMEM
endif
            AddLineQueueX( "%r %r,WORD PTR %s", T_MOVSX, edx, ebx )
        .else
            AddLineQueueX( "%r %r,%s", T_MOVSX, edx, ebx )
        .endif

    .elseif eax & HLLF_ARG32
        ;
        ; DWORD value
        ;
ifndef __ASMC64__
        .if ModuleInfo.Ofssize == USE32
            .if eax & HLLF_ARGMEM
                AddLineQueueX( "mov %r,%r PTR %s", edx, T_DWORD, ebx )
            .elseif _stricmp( ebx, &buffer )
                AddLineQueueX( "mov %r,%s", edx, ebx )
            .endif
        .elseif eax & HLLF_ARGMEM
else
        .if eax & HLLF_ARGMEM
endif
            AddLineQueueX( "%r %r,%r PTR %s", T_MOVSXD, edx, T_DWORD, ebx )
        .else
            AddLineQueueX( "%r %r,%s", T_MOVSXD, edx, ebx )
        .endif
    .else
        ;
        ; QWORD value
        ;
        AddLineQueueX( "mov %r,%r PTR %s", edx, T_QWORD, ebx )
    .endif
    ret

GetSwitchArg endp

    assume ebx:hll_t

RenderSwitch proc uses esi edi ebx hll:hll_t, tokenarray:tok_t,
    buffer:string_t,  ; *switch.labels[LSTART]
    l_exit:string_t   ; *switch.labels[LEXIT]

  local r_dw:       DWORD,  ; dw/dd
        r_db:       DWORD,  ; "DB"/"DW"
        r_size:     DWORD,  ; 2/4/8
        dynamic:    DWORD,  ; number of dynmaic cases
        default:    DWORD,  ; hll_item * if exist
        static:     DWORD,  ; number of static const values
        tables:     DWORD,  ; number of tables
        lcount:     DWORD,  ; number of labels in table
        icount:     DWORD,  ; number of index to labels in table
        tcases:     DWORD,  ; number of cases in table
        ncases:     DWORD,  ; number of cases not in table
        min_table:  DWORD,
        max_table:  DWORD,
        min[2]:     SDWORD, ; minimum const value
        max[2]:     SDWORD, ; maximum const value
        dist:       SDWORD, ; max - min
        l_start[16]:char_t,  ; current start label
        l_jtab[16]: char_t,  ; jump table address
        labelx[16]: char_t,  ; label symbol
        use_index:  BYTE

    mov esi,hll
    mov edi,buffer
    xor eax,eax
    mov tables,eax
    mov ncases,eax
    mov default,eax

    ; get static case-count

    GetCaseValue( esi, tokenarray, &dynamic, &static )

    .if ( eax && [esi].flags & HLLF_NOTEST )

        ; create a small table

        add eax,MIN_JTABLE
    .endif

    .if ModuleInfo.xflag & OPT_NOTABLE || eax < MIN_JTABLE
        ;
        ; Time NOTABLE/TABLE
        ;
        ; .case *   3   4       7       8       9       10      16      60
        ; NOTABLE 1401  2130    5521    5081    7681    9481    18218   158245
        ; TABLE   1521  3361    4402    6521    7201    7881    9844    68795
        ; elseif  1402  4269    5787    7096    8481    10601   22923   212888
        ;
        RenderCCMP( esi, edi )
        jmp toend
    .endif

ifndef __ASMC64__
    mov ecx,2
    mov eax,T_DW
    .if ModuleInfo.Ofssize != USE16
        mov ecx,4
        mov eax,T_DD
    .endif
    mov r_dw,eax
    mov r_size,ecx
else
    mov r_dw,T_DD
    mov r_size,4
endif
    strcpy( &l_start, edi )

    ; flip exit to default if exist

    .if [esi].flags & HLLF_ELSEOCCURED

        .for eax = esi, ebx = [esi].caselist: ebx: eax = ebx, ebx = [ebx].caselist

            .if [ebx].flags & HLLF_DEFAULT

                mov [eax].hll_item.caselist,0
                mov default,ebx
                GetLabelStr( [ebx].labels[LSTART*4], l_exit )
                .break
            .endif
        .endf
    .endif

    .if ( ModuleInfo.casealign && !( [esi].flags & HLLF_JTDATA ) )

        mov cl,ModuleInfo.casealign
        mov eax,1
        shl eax,cl
        AddLineQueueX( "ALIGN %d", eax )

    .elseif ( [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE )

        .if ( ModuleInfo.Ofssize == USE64 && !( [esi].flags & HLLF_JTDATA ) )

            AddLineQueueX( "ALIGN 8" )
        .endif
    .endif
    AddLineQueueX( "%s%s", &l_start, LABELQUAL )

    .if dynamic

        .for eax = esi, ebx = [esi].caselist: ebx: eax = ebx, ebx = [ebx].caselist

            .if !( [ebx].flags & HLLF_NUM )

                mov ecx,[ebx].caselist
                mov [eax].hll_item.caselist,ecx
                RenderCase( esi, ebx, edi )
            .endif
        .endf
    .endif

    .while [esi].condlines

        GetMaxCaseValue( esi, &min, &max, &min_table, &max_table )

        mov dist,eax
        mov tcases,ecx
        mov ncases,0

        .break .if ecx < min_table

        .for ebx = ecx:,
             ebx >= min_table,
             max > edx,
             eax > max_table: ebx = tcases

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
        .if eax < dist && ModuleInfo.Ofssize == USE64

            inc use_index
        .endif

        ; Create the jump table lable

        .if [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE

            strcpy( &l_jtab, &l_start )
            AddLineQueueX( "MIN%s equ %d", eax, min )
        .else
            lea ecx,l_jtab
            GetLabelStr( GetHllLabel(), ecx )
        .endif

        mov edi,l_exit
        .if ncases
            lea ecx,l_start
            mov edi,GetLabelStr( GetHllLabel(), ecx )
        .endif
        mov ebx,[esi].condlines
        .if !( [esi].flags & HLLF_NOTEST )
            CompareMaxMin(ebx, max, min, edi)
        .endif

        mov edx,min
        mov eax,[esi].flags
        mov cl,ModuleInfo.Ofssize

        .if ( [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE )

            .if ( [esi].flags & HLLF_JTDATA )

                AddLineQueueX( ".data" )
                AddLineQueueX( "ALIGN 4" )
                AddLineQueueX( "DT%s label dword", &l_jtab )

            .elseif cl == USE64

                mov r_dw,T_DQ
                mov r_size,8
            .endif

        .else

ifndef __ASMC64__
            .if cl == USE16

                .if !( ModuleInfo.xflag & OPT_REGAX )
                    AddLineQueue("push ax")
                .endif
                .if [esi].flags & HLLF_ARGREG
                    .if ModuleInfo.xflag & OPT_REGAX
                        .if _stricmp("ax", ebx)
                            AddLineQueueX( "mov ax,%s", ebx )
                        .endif
                        AddLineQueue("xchg ax,bx")
                    .else
                        AddLineQueue("push bx")
                        AddLineQueue("push ax")
                        .if _stricmp("bx", ebx)
                            AddLineQueueX("mov bx,%s", ebx)
                        .endif
                    .endif
                .else
                    .if !( ModuleInfo.xflag & OPT_REGAX )
                        AddLineQueue( "push bx" )
                    .endif
                    GetSwitchArg(T_AX, [esi].flags, ebx)
                    .if ModuleInfo.xflag & OPT_REGAX
                        AddLineQueue("xchg ax,bx")
                    .else
                        AddLineQueue("mov bx,ax")
                    .endif
                .endif
                .if min
                    AddLineQueueX("sub bx,%d", min)
                .endif
                AddLineQueue("add bx,bx")
                .if ModuleInfo.xflag & OPT_REGAX
                    AddLineQueueX("mov bx,cs:[bx+%s]", &l_jtab)
                    AddLineQueue ("xchg ax,bx")
                    AddLineQueue ("jmp ax")
                .else
                    AddLineQueueX("mov ax,cs:[bx+%s]", &l_jtab)
                    AddLineQueue ("mov bx,sp")
                    AddLineQueue ("mov ss:[bx+4],ax")
                    AddLineQueue ("pop ax")
                    AddLineQueue ("pop bx")
                    AddLineQueue ("retn")
                .endif

            .elseif cl == USE32

                .if !( eax & HLLF_ARGREG )

                    GetSwitchArg(T_EAX, [esi].flags, ebx)
                    .if use_index
                        .if dist < 256
                            AddLineQueueX("movzx eax,BYTE PTR [eax+IT%s-(%d)]", &l_jtab, min)
                        .else
                            AddLineQueueX("movzx eax,WORD PTR [eax*2+IT%s-(%d*2)]", &l_jtab, min)
                        .endif
                        .if ModuleInfo.xflag & OPT_REGAX
                            AddLineQueueX("jmp [eax*4+%s]", &l_jtab)
                        .else
                            AddLineQueueX("mov eax,[eax*4+%s]", &l_jtab)
                        .endif
                    .elseif ModuleInfo.xflag & OPT_REGAX
                        AddLineQueueX("jmp [eax*4+%s-(%d*4)]", &l_jtab, min)
                    .else
                        AddLineQueueX("mov eax,[eax*4+%s-(%d*4)]", &l_jtab, min)
                    .endif
                    .if !( ModuleInfo.xflag & OPT_REGAX )
                        AddLineQueue("xchg eax,[esp]")
                        AddLineQueue("retn")
                    .endif
                .else
                    .if use_index
                        .if !( ModuleInfo.xflag & OPT_REGAX )
                            AddLineQueueX("push %s", ebx)
                        .endif
                        .if dist < 256
                            AddLineQueueX("movzx %s,BYTE PTR [%s+IT%s-(%d)]", ebx, ebx, &l_jtab, min)
                        .else
                            AddLineQueueX("movzx %s,WORD PTR [%s*2+IT%s-(%d*2)]", ebx, ebx, &l_jtab, min)
                        .endif
                        .if ModuleInfo.xflag & OPT_REGAX
                            AddLineQueueX("jmp [%s*4+%s]", ebx, &l_jtab)
                        .else
                            AddLineQueueX("mov %s,[%s*4+%s]", ebx, ebx, &l_jtab)
                            AddLineQueueX("xchg %s,[esp]", ebx)
                            AddLineQueue ("retn")
                        .endif
                    .else
                        AddLineQueueX("jmp [%s*4+%s-(%d*4)]", ebx, &l_jtab, min)
                    .endif
                .endif

            .elseif ( edx <= ( UINT_MAX / 8 ) ) && !use_index && [esi].flags & HLLF_ARGREG && \
                ModuleInfo.xflag & OPT_REGAX
else
            .if ( edx <= ( UINT_MAX / 8 ) ) && !use_index && [esi].flags & HLLF_ARGREG && \
                ModuleInfo.xflag & OPT_REGAX
endif

                .if !_memicmp( ebx, "r11", 3 )

                    asmerr( 2008, "register r11 overwritten by .SWITCH" )
                .endif
                AddLineQueueX( "lea r11,%s", l_exit )
                AddLineQueue ( "push rax" )
                AddLineQueueX( "mov eax,[%s*4+r11-(%d*4)+(%s-%s)]", ebx, min, &l_jtab, l_exit )
                AddLineQueue ( "sub r11,rax" )
                AddLineQueue ( "pop rax" )
                AddLineQueue ( "jmp r11" )

            .else

                .if ( ModuleInfo.xflag & OPT_REGAX )

                    AddLineQueue( "push rax" )

                    .if !( [esi].flags & HLLF_ARGREG )

                        GetSwitchArg( T_RAX, [esi].flags, ebx )
                    .else
                        mov eax,[ebx]
                        or  eax,0x202020
                        and eax,0xFFFFFF
                        .if !( eax == 'xar' || eax == 'xae' )
                            AddLineQueueX("mov rax,%s", ebx)
                        .endif
                    .endif
                    AddLineQueueX( "lea r11,%s", l_exit )
                    .if use_index
                        .if dist < 256
                            AddLineQueueX( "movzx eax,BYTE PTR [r11+rax-(%d)+(IT%s-%s)]", min, &l_jtab, l_exit )
                        .else
                            AddLineQueueX( "movzx eax,WORD PTR [r11+rax*2-(%d*2)+(IT%s-%s)]", min, &l_jtab, l_exit )
                        .endif
                        AddLineQueueX( "mov eax,[r11+rax*4+(%s-%s)]", &l_jtab, l_exit )
                    .else
                        mov eax,min
                        .if ( eax < ( UINT_MAX / 8 ) )
                            AddLineQueueX( "mov eax,[r11+rax*4-(%d*4)+(%s-%s)]", min, &l_jtab, l_exit )
                        .else
                            AddLineQueueX( "sub r11,%d", eax )
                            AddLineQueueX( "mov eax,[r11+rax*4+(%s-%s)]", &l_jtab, l_exit )
                        .endif
                    .endif
                    AddLineQueue( "sub r11,rax" )
                    AddLineQueue( "pop rax" )
                    AddLineQueue( "jmp r11" )

                .else

                    .if !( [esi].flags & HLLF_ARGREG )
                        GetSwitchArg( T_RAX, [esi].flags, ebx )
                    .else
                        AddLineQueue("push rax")
                        .if _memicmp(ebx, "rax", 3)
                            AddLineQueueX("mov rax,%s", ebx)
                        .endif
                    .endif
                    AddLineQueue ( "push rdx" )
                    AddLineQueueX( "lea rdx,%s", l_exit )
                    .if use_index
                        .if dist < 256
                            AddLineQueueX( "movzx eax,BYTE PTR [rdx+rax-(%d)+(IT%s-%s)]", min, &l_jtab, l_exit )
                        .else
                            AddLineQueueX( "movzx eax,WORD PTR [rdx+rax*2-(%d*2)+(IT%s-%s)]", min, &l_jtab, l_exit )
                        .endif
                        AddLineQueueX( "mov eax,[rdx+rax*4+(%s-%s)]", &l_jtab, l_exit )
                    .else
                        mov eax,min
                        .if ( eax < ( UINT_MAX / 8 ) )
                            AddLineQueueX( "mov eax,[rdx+rax*4-(%d*4)+(%s-%s)]", min, &l_jtab, l_exit )
                        .else
                            AddLineQueueX( "sub rax,%d", eax )
                            AddLineQueueX( "mov eax,[rdx+rax*4+(%s-%s)]", &l_jtab, l_exit )
                        .endif
                    .endif
                    AddLineQueue( "sub rdx,rax" )
                    AddLineQueue( "mov rax,[rsp+8]" )
                    AddLineQueue( "mov [rsp+8],rdx" )
                    AddLineQueue( "pop rdx" )
                    AddLineQueue( "retn" )
                .endif
            .endif
            ;
            ; Create the jump table
            ;
            AddLineQueueX( "ALIGN %d", r_size )
            AddLineQueueX( "%s%s", &l_jtab, LABELQUAL )

        .endif

        .if use_index

            push edi

            .for ebx = -1, ; offset
                 edi = -1, ; table index
                 esi = [esi].caselist: esi: esi = [esi].caselist

                .if [esi].flags & HLLF_TABLE

                    .break .if !SymFind(GetLabelStr([esi].labels[LSTART*4], &labelx))

                    .if ebx != [eax].asym._offset

                        mov ebx,[eax].asym._offset
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

            .for esi = hll, ebx = -1,
                 esi = [esi].caselist: esi: esi = [esi].caselist

                .if [esi].flags & HLLF_TABLE && ebx != [esi].next

ifndef __ASMC64__
                    .if ModuleInfo.Ofssize == USE64
endif
                        AddLineQueueX(" dd %s-%s ; .case %s", l_exit,
                            GetLabelStr([esi].labels[LSTART*4], &labelx), [esi].condlines)
ifndef __ASMC64__
                    .else
                        AddLineQueueX(" %r %s ; .case %s", r_dw,
                            GetLabelStr([esi].labels[LSTART*4], &labelx), [esi].condlines)
                    .endif
endif
                    mov ebx,[esi].next
                .endif
            .endf

            mov esi,hll
ifndef __ASMC64__
            .if ModuleInfo.Ofssize == USE64
endif
                AddLineQueueX( " %r 0 ; .default", r_dw )
ifndef __ASMC64__
            .else
                AddLineQueueX( " %r %s ; .default", r_dw, l_exit )
            .endif
endif
            mov eax,max
            sub eax,min
            inc eax
            mov icount,eax
            mov ebx,T_DB
            .if eax > 256

ifndef __ASMC64__
                .if ModuleInfo.Ofssize == USE16

                    asmerr(2022, 1, 2)
                    jmp toend
                .endif
endif
                mov ebx,T_DW
            .endif
            mov r_db,ebx
            AddLineQueueX( "IT%s LABEL BYTE", &l_jtab )

            .for ebx = 0: ebx < icount: ebx++
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
                    AddLineQueueX( " %r %d", r_db, [eax].hll_item.next )

                .else
                    ;
                    ; else make a jump to exit or default label
                    ;
                    AddLineQueueX( " %r %d", r_db, lcount )
                .endif
            .endf
            AddLineQueueX( "ALIGN %d", r_size )
        .else
            .for ebx = 0: ebx < dist: ebx++
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
ifndef __ASMC64__
                    .if ModuleInfo.Ofssize == USE64
endif
                        LQJumpLabel64( r_dw, l_exit, ecx )
ifndef __ASMC64__
                    .else

                        LQJumpLabel( r_dw, ecx )
                    .endif
endif
                .else
                    ;
                    ; else make a jump to exit or default label
                    ;
ifndef __ASMC64__
                    .if ModuleInfo.Ofssize == USE64
endif
                        AddLineQueueX( "%r 0", r_dw )
ifndef __ASMC64__
                    .else
                        AddLineQueueX( "%r %s", r_dw, l_exit )
                    .endif
endif
                .endif
            .endf
        .endif

        .if ( [esi].flags & HLLF_JTDATA )

            AddLineQueue( ".code" )
        .endif

        .if ncases
            ;
            ; Create the new start label
            ;
            AddLineQueueX( "%s%s", &l_start, LABELQUAL )

            .for ebx = [esi].caselist: ebx: ebx = [ebx].caselist

                or [ebx].flags,HLLF_TABLE
            .endf
        .endif
    .endw

    .for ebx = [esi].caselist: ebx: ebx = [ebx].caselist

        RenderCase( esi, ebx, buffer )
    .endf

    .if default && [esi].caselist

        AddLineQueueX( "jmp %s", l_exit )
    .endif
toend:
    ret
RenderSwitch endp

    assume  esi: hll_t

RenderJTable proc uses esi edi ebx hll:hll_t

  local l_exit[16]:sbyte, l_jtab[16]:sbyte  ; jump table address

    mov esi,hll
    lea edi,l_jtab

    .if [esi].labels[LEXIT*4] == 0
        mov [esi].labels[LEXIT*4],GetHllLabel()
    .endif
    .if [esi].labels[LSTARTSW*4] == 0
        mov [esi].labels[LSTARTSW*4],GetHllLabel()
    .endif

    LQAddLabelId( [esi].labels[LSTARTSW*4] )
    GetLabelStr( [esi].labels[LSTART*4], edi )
    GetLabelStr( [esi].labels[LEXIT*4], &l_exit )

    mov ebx,[esi].condlines
ifndef __ASMC64__
    mov cl,ModuleInfo.Ofssize

    .if cl == USE16

        .if ModuleInfo.xflag & OPT_REGAX
            .if _stricmp( "ax", ebx )
                AddLineQueueX( "mov ax,%s", ebx )
            .endif
            AddLineQueue ( "xchg ax,bx" )
            AddLineQueue ( "add bx,bx" )
            AddLineQueueX( "mov bx,cs:[bx+%s]", edi )
            AddLineQueue ( "xchg ax,bx" )
            AddLineQueue ( "jmp ax" )
        .else
            AddLineQueue( "push ax" )
            AddLineQueue( "push bx" )
            AddLineQueue( "push ax" )
            .if _stricmp( "bx", ebx )
                AddLineQueueX( "mov bx,%s", ebx )
            .endif
            AddLineQueue ( "add bx,bx" )
            AddLineQueueX( "mov ax,cs:[bx+%s]", edi )
            AddLineQueue ( "mov bx,sp" )
            AddLineQueue ( "mov ss:[bx+4],ax" )
            AddLineQueue ( "pop ax" )
            AddLineQueue ( "pop bx" )
            AddLineQueue ( "retn" )
        .endif

    .elseif cl == USE32

        .if ( [esi].flags & HLLF_JTDATA )
            AddLineQueueX( "jmp [%s*4+DT%s-(MIN%s*4)]", ebx, edi, edi )
        .else
            AddLineQueueX( "jmp [%s*4+%s-(MIN%s*4)]", ebx, edi, edi )
        .endif

    .elseif ModuleInfo.xflag & OPT_REGAX
else
    .if ModuleInfo.xflag & OPT_REGAX
endif
        .ifd !_memicmp( ebx, "r11", 3 )

            asmerr( 2008, "register r11 overwritten by .SWITCH" )
        .endif
        .if ( [esi].flags & HLLF_ARG3264 )
            mov byte ptr [ebx],'r'
        .endif
        AddLineQueueX( "lea r11,%s", &l_exit )
        AddLineQueueX( "sub r11,[%s*8+r11-(MIN%s*8)+(%s-%s)]", ebx, edi, edi, &l_exit )
        AddLineQueue ( "jmp r11" )
        .if ( [esi].flags & HLLF_ARG3264 )
            mov byte ptr [ebx],'e'
        .endif
    .else
        AddLineQueue( "push rax" )
        AddLineQueue( "push rdx" )
        .if _memicmp( ebx, "rax", 3 )
            AddLineQueueX( "mov rax,%s", ebx )
        .endif
        AddLineQueueX( "lea rdx,%s", &l_exit )
        AddLineQueueX( "mov eax,[rdx+rax*4-(MIN%s*4)+(%s-%s)]", edi, edi, &l_exit )
        AddLineQueue ( "sub rdx,rax" )
        AddLineQueue ( "mov rax,[rsp+8]" )
        AddLineQueue ( "mov [rsp+8],rdx" )
        AddLineQueue ( "pop rdx" )
        AddLineQueue ( "retn" )
    .endif
    ret

RenderJTable endp

    assume  ebx: tok_t

SwitchStart proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local rc:int_t, cmd:uint_t, buffer[MAX_LINE_LEN]:char_t
  local opnd:expr

    mov rc,NOT_ERROR
    mov ebx,tokenarray
    lea edi,buffer

    mov eax,i
    shl eax,4
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

    mov edx,i ; v2.27.38: .SWITCH [NOTEST] [C|PASCAL] ...
    shl edx,4 ; v2.30.07: .SWITCH [JMP] [C|PASCAL] ...
    mov eax,HLLF_WHILE

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
        add edx,16

    .elseif [ebx+edx].tokval == T_PASCAL

        inc i
        add edx,16
        or eax,HLLF_PASCAL

    .elseif ModuleInfo.xflag & OPT_PASCAL

        or eax,HLLF_PASCAL
    .endif

    mov [esi].flags,eax

    .if [ebx+edx].token != T_FINAL

        .return .if ExpandHllProc(edi, i, ebx) == ERROR

        .if BYTE PTR [edi]

            QueueTestLines(edi)
            or [esi].flags,HLLF_ARGREG
ifndef __ASMC64__
            .if ModuleInfo.Ofssize == USE16
                or [esi].flags,HLLF_ARG16
            .elseif ModuleInfo.Ofssize == USE32
                or [esi].flags,HLLF_ARG32
            .else
endif
                or [esi].flags,HLLF_ARG64
ifndef __ASMC64__
            .endif
endif
        .else

            mov ecx,i
            shl ecx,4
            mov eax,[ebx+ecx].tokval

            .switch eax
              .case T_AX .. T_DI
                or  [esi].flags,HLLF_ARG16
ifndef __ASMC64__
                .if ModuleInfo.Ofssize == USE16
                    or [esi].flags,HLLF_ARGREG
                    .if [esi].flags & HLLF_NOTEST
                        or [esi].flags,HLLF_JTABLE
                    .endif
                .endif
endif
              .case T_AL .. T_BH
                .endc

              .case T_EAX .. T_EDI
                or  [esi].flags,HLLF_ARG32
ifndef __ASMC64__
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
ifndef __ASMC64__
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

                .if eax != ERROR
                    mov eax,8
ifndef __ASMC64__
                    .if ModuleInfo.Ofssize == USE16
                        mov eax,2
                    .elseif ModuleInfo.Ofssize == USE32
                        mov eax,4
                    .endif
endif
                    .if ( opnd.kind == EXPR_ADDR && (opnd.flags & E_INDIRECT) && opnd.mbr )
                        mov ecx,opnd.mbr
                        mov eax,[ecx].asym.total_size
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
        .endif

        mov edx,i
        shl edx,4
        strlen(strcpy(edi, [ebx+edx].asm_tok.tokpos))
        inc eax
        push eax
        LclAlloc(eax)
        pop ecx
        mov [esi].condlines,eax
        memcpy(eax, edi, ecx)
    .endif

    mov eax,i
    shl eax,4
    .if ![esi].flags && ([ebx+eax].asm_tok.token != T_FINAL && rc == NOT_ERROR)

        mov rc,asmerr(2008, [ebx+eax].asm_tok.tokpos)
    .endif

    .if esi == ModuleInfo.HllFree
        mov eax,[esi].next
        mov ModuleInfo.HllFree,eax
    .endif
    mov eax,ModuleInfo.HllStack
    mov [esi].next,eax
    mov ModuleInfo.HllStack,esi
    mov eax,rc
    ret

SwitchStart endp

SwitchEnd proc uses esi edi ebx i:int_t, tokenarray:tok_t

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
                LQJumpLabel(T_JMP, [esi].labels[LEXIT*4])
            .endif
        .endif

        mov ebx,[esi].caselist
        assume ebx:hll_t

        mov cl,ModuleInfo.casealign
        .if cl
            mov eax,1
            shl eax,cl
            AddLineQueueX("ALIGN %d", eax)
        .endif

        .if ( ![esi].condlines )

            AddLineQueueX("%s%s", edi, LABELQUAL)

            .while ebx

                .if ![ebx].condlines

                    LQJumpLabel(T_JMP, [ebx].labels[LSTART*4])
                .elseif [ebx].flags & HLLF_EXPRESSION
                    mov i,1
                    or  [ebx].flags,HLLF_WHILE
                    ExpandHllExpression(ebx, &i, tokenarray, LSTART, 1, edi)
                .else
                    QueueTestLines([ebx].condlines)
                .endif
                mov ebx,[ebx].caselist
            .endw
        .else
            RenderSwitch(esi, tokenarray, edi, &l_exit)
        .endif

        assume ebx:tok_t
    .until 1

    mov eax,[esi].labels[LEXIT*4]
    .if eax
        LQAddLabelId(eax)
    .endif
    mov eax,rc
    ret

SwitchEnd endp

SwitchExit proc uses esi edi ebx i, tokenarray:tok_t

  local rc:     int_t,
        cmd:    int_t,
        buff    [16]:char_t,
        buffer  [MAX_LINE_LEN]:char_t,
        gotosw: int_t,
        hll:    hll_t,
        name:   string_t

    mov esi,ModuleInfo.HllStack
    mov hll,esi

    .return asmerr(1011) .if !esi

    ExpandCStrings(tokenarray)

    lea edi,buffer
    mov rc,NOT_ERROR
    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    mov eax,[ebx].tokval
    mov cmd,eax
    xor ecx,ecx     ; exit level 0,1,2,3

    .switch eax

      .case T_DOT_DEFAULT
        .return asmerr(2142) .if ( [esi].flags & HLLF_ELSEOCCURED )
        .return asmerr(2008, [ebx].tokpos) .if ( [ebx+16].token != T_FINAL )

        or [esi].flags,HLLF_ELSEOCCURED

      .case T_DOT_CASE

        .while esi && [esi].cmd != HLL_SWITCH

            mov esi,[esi].next
        .endw

        .return asmerr(1010, [ebx].string_ptr) .if [esi].cmd != HLL_SWITCH

        .if [esi].labels[LSTART*4] == 0

            ;; First case..

            mov [esi].labels[LSTART*4],GetHllLabel()

            .if [esi].flags & HLLF_NOTEST && [esi].flags & HLLF_JTABLE
                RenderJTable(esi)
            .else
                LQJumpLabel(T_JMP, eax)
            .endif

        .elseif [esi].flags & HLLF_PASCAL

                .if [esi].labels[LEXIT*4] == 0
                    mov [esi].labels[LEXIT*4],GetHllLabel()
                .endif
                mov eax,esi
                .while [eax].hll_item.caselist
                    mov eax,[eax].hll_item.caselist
                .endw
                .if ( eax != esi && !( [eax].hll_item.flags & HLLF_ENDCOCCUR ) )
                    LQJumpLabel( T_JMP, [esi].labels[LEXIT*4] )
                .endif

        .elseif Parse_Pass == PASS_1
                ;
                ; error A7007: .CASE without .ENDC: assumed fall through
                ;
                mov eax,esi
                .while [eax].hll_item.caselist
                    mov eax,[eax].hll_item.caselist
                .endw
if 1
                .if ( eax != esi && !( [eax].hll_item.flags & HLLF_ENDCOCCUR ) )
                    asmerr( 7007 )
                .endif
endif
        .endif

        ; .case <case_a> a

        mov name,0
        .if ( [ebx+16].token == T_STRING && [ebx+32].token == T_ID && [ebx+48].token == T_STRING )

            mov name,[ebx+32].string_ptr
            add ebx,48
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
        mov ecx,GetHllLabel()

        push ecx
        LQAddLabelId(ecx)
        .if name
            AddLineQueueX("%s:", name )
        .endif
        LclAlloc(hll_item)
        pop ecx

        mov edx,esi
        mov esi,eax
        mov eax,[edx].hll_item.condlines
        mov [esi].labels[LSTART*4],ecx
        .while [edx].hll_item.caselist

            mov edx,[edx].hll_item.caselist
        .endw
        mov [edx].hll_item.caselist,esi

        inc i   ; skip past the .case token
        add ebx,16

        push eax ;
        push ebx ; handle .case <expression> : ...
        push esi ;

        .for ( esi = 0 : IsCaseColon(ebx) : ebx += 16, esi = [ebx].tokpos )

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

                        .if [ebx+16].token == T_FINAL

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
                    .if [ebx+16].token == T_FINAL

                        or [esi].flags,HLLF_NUM
                        .break
                    .endif
                    .endc

                  .case T_STYPE ; BYTE, WORD, ...
                    .break .if [ebx+16].tokval == T_PTR
                    .gotosw(T_STRING)

                  .case T_FLOAT ; 1..3 ?
                    .break  .if [ebx+16].token == T_DOT
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

            .return asmerr(2008, [ebx-16].tokpos) .if ( [ebx].token == T_FINAL )

            .if !eax

                mov ebx,i
                EvaluateHllExpression( esi, &i, tokenarray, LSTART, 1, edi )
                mov i,ebx
                mov rc,eax
                .endc .if eax == ERROR

            .else

                mov eax,ModuleInfo.token_count
                shl eax,4
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
                        .if !strcmp(edi, [esi].condlines)

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

                    AddLineQueueX("mov %s,%s", [esi].condlines, edi)

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

SwitchDirective proc uses esi edi ebx i:int_t, tokenarray:tok_t

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
    mov eax,ebx
    ret

SwitchDirective endp

    END
