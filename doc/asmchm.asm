; ASMCHM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include stdlib.inc
include string.inc
include malloc.inc
include direct.inc
ifndef __INIX__
include winbase.inc
endif
include tchar.inc

.template md

    next string_t ?
    name string_t ?
    file string_t ?
   .ends
    pmd typedef ptr md

   .data
    files   pmd 0
    count   int_t 0

   .data?
    lbuf    char_t 0x8000 dup(?)
    ltmp    char_t 0x8000 dup(?)

   .code

readfile proc uses rdi rbx path:string_t, ff:ptr _finddata_t

   .new size:int_t
   .new fp:LPFILE
   .new name[_MAX_PATH]:char_t = 0

    ldr rcx,path
    ldr rbx,ff

    .if ( word ptr [rcx] == '.' )

        inc rcx

    .elseif ( word ptr [rcx] == '\.' )

        add rcx,2
    .endif

    .for ( rdx = &name : byte ptr [rcx] : rcx++, rdx++ )

        mov al,[rcx]
        .if ( al == '\' )
            mov al,'/'
        .endif
        mov [rdx],al
    .endf
    lea rcx,name
    .if ( rdx > rcx )
        mov eax,'/'
        mov [rdx],eax
    .endif
    strcat(rcx, &[rbx]._finddata_t.name )
    strlen(rax)
    add eax,dword ptr [rbx]._finddata_t.size
    add eax,md + size_t*2
    mov size,eax
    mov rbx,malloc(eax)
    mov rdi,rax
    mov ecx,size
    xor eax,eax
    rep stosb
    lea rcx,[rbx+md]
    mov [rbx].md.name,rcx
    strcpy(rcx, &name)
    strlen(rax)
    add eax,2
    mov rcx,[rbx].md.name
    add rcx,rax
    add rcx,size_t-1
    and rcx,-size_t
    mov [rbx].md.file,rcx

    .if ( fopen(&name, "rb") == NULL )

        perror(&name)
        exit(1)
    .endif
    mov fp,rax
    fread([rbx].md.file, 1, size, fp)
    fclose(fp)

    mov rcx,files
    .if ( rcx == NULL )

        mov files,rbx
    .else
        .while( [rcx].md.next )
            mov rcx,[rcx].md.next
        .endw
        mov [rcx].md.next,rbx
    .endif
    .if ( strchr( [rbx].md.name, '/' ) == NULL )
        mov rbx,[rbx].md.name
    .else
        lea rbx,[rax+1]
    .endif
    .ifd ( strcmp(rbx, "readme.md") == 0 )
        strcpy(rbx, "index.htm")
    .elseif ( strrchr( rbx, '.' ) )
        strcpy(rax, ".htm")
    .endif
    .return( 0 )

readfile endp

readfiles proc uses rbx directory:string_t

    .new path[_MAX_PATH]:char_t
    .new ff:_finddata_t

    .ifd _findfirst(strfcat(&path, directory, "*.md"), &ff) != -1

        mov rbx,rax
        .repeat
            .if !( ff.attrib & _F_SUBDIR )

                readfile(directory, &ff)
                inc count
            .endif
        .until _findnext(rbx, &ff)
        _findclose(rbx)
    .endif

    .ifd ( _findfirst(strfcat(&path, directory, "*.*"), &ff) != -1 )

        mov rbx,rax
        .repeat

            mov eax,dword ptr ff.name
            and eax,0x00FFFFFF
            .if ( ax != '.' && eax != '..' && ff.attrib & _F_SUBDIR )

                readfiles(strfcat(&path, directory, &ff.name))
            .endif
        .until _findnext(rbx, &ff)
        _findclose(rbx)
    .endif
    ret

readfiles endp


erexit proc name:string_t, string:string_t

    printf( "error: %s(%s)\n", string, name )
    exit( 1 )
    ret

erexit endp


a_href proc uses rbx fp:LPFILE, line:string_t

   .new href[256]:char_t

    strcpy(&href, line)
    mov rbx,strrchr(rax, '/')
    .if ( rbx )
         inc rbx
    .else
        lea rbx,href
    .endif
    .ifd ( strcmp(rbx, "readme.md") == 0 )
        strcpy(rbx, "index.htm")
    .endif
    .if ( strrchr( &href, '.' ) )

        mov ecx,[rax]
        .if ( ecx == 'dm.' )
            strcpy(rax, ".htm")
        .endif
    .endif
    fprintf(fp, "<a href=\"%s\">", &href)
    ret

a_href endp


makehtm proc uses rsi rdi rbx pm:pmd

   .new fp:LPFILE
   .new ul:int_t = 0
   .new li:int_t = 0
   .new pre:int_t = 0
   .new p:int_t = 0
   .new h:int_t = 0
   .new b:int_t = 0
   .new i:int_t = 0
   .new t:string_t
   .new q:string_t
   .new name:string_t

    ldr rbx,pm

    mov name,[rbx].md.name
    .if ( fopen([rbx].md.name, "wt") == NULL )

        perror([rbx].md.name)
        exit(1)
    .endif
    mov fp,rax

    .if ( strchr([rbx].md.file, '#') == NULL )
        erexit( [rbx].md.name, "Missing #<title>" )
    .endif
    mov t,rax
    .if ( strchr(rax, 10) == NULL )
        erexit( [rbx].md.name, "Missing \\n" )
    .endif
    lea rcx,[rax+1]
    mov q,rcx
    .if ( byte ptr [rax-1] == 13 )
        dec rax
    .endif
    mov byte ptr [rax],0
    strchr([rbx].md.name, '/')
    .for ( rcx = t : byte ptr [rcx] == '#' : rcx++ )
    .endf
    .if ( byte ptr [rcx] == ' ' )
        inc rcx
    .endif
    lea rdx,@CStr("../style.css")
    .if ( !rax )
        add rdx,3
    .endif
    fprintf(fp,
        "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n"
        "<html><head><title>%s</title></head>\n"
        "<link href=\"%s\" rel=\"stylesheet\" type=\"text/css\">\n"
        "<body>\n"
        "Asmc Macro Assembler Reference\n", rcx, rdx)

    mov rbx,t

    .while 1

        movzx eax,byte ptr [rbx]
        .switch eax
        .case 0
            .if ( ul )
                fprintf(fp, "</ul>\n" )
                dec ul
            .endif
            .endc
        .case '`'
            .if ( pre )
                fprintf(fp, "</pre>\n" )
                dec pre
            .else
                fprintf(fp, "<pre>\n" )
                inc pre
                jmp continue
            .endif
            .while ( byte ptr [rbx] )
                inc rbx
            .endw
            .endc
        .case '-'
            .if ( ul == 0 )
                fprintf(fp, "<ul>\n" )
                inc ul
            .endif
            inc li
            fprintf(fp, "<li>" )
            inc rbx
           .endc
        .case '#'
            .while ( byte ptr [rbx] == al )
                inc h
                inc rbx
            .endw
            .if ( byte ptr [rbx] == ' ' )
                inc rbx
            .endif
            fprintf(fp, "<h%d>", h)
           .endc
        .default
            .if ( ul )
                fprintf(fp, "</ul>\n" )
                dec ul
            .endif
            .if ( !pre )
                fprintf(fp, "<p>" )
                inc p
            .endif
        .endsw


        .if ( pre )

            fprintf(fp, "%s\n", rbx)
            jmp continue
        .endif

        .while ( byte ptr [rbx] )

            movzx eax,byte ptr [rbx]
            inc rbx
            xor ecx,ecx

            .switch eax
            .case '\'
               .endc .if ( byte ptr [rbx-2] == '\' )
                inc ecx
               .endc
            .case '['
               .endc .if ( byte ptr [rbx-2] == '\' )
                mov t,rbx
                .for ( edx = 1 : byte ptr [rbx] : rbx++ )

                    .if ( [rbx] == al )
                        inc edx
                    .elseif ( byte ptr [rbx] == ']' )
                        dec edx
                       .break .ifz
                    .endif
                .endf
                .if ( byte ptr [rbx] != ']' || byte ptr [rbx+1] != '(' )

                    mov rbx,t
                   .endc
                .endif
                mov byte ptr [rbx],0
                add rbx,2
               .endc .if strchr(rbx, ')') == NULL
                mov byte ptr [rax],0
                mov rcx,rbx
                inc rax
                mov rbx,t
                mov t,rax
                a_href(fp, rcx)

                .while ( byte ptr [rbx] )

                    mov ecx,[rbx]
                    movzx eax,cl
                    inc rbx
                    .if ( al == '\' && byte ptr [rbx-2] != '\' )
                    .elseif ( al == '_' && byte ptr [rbx-2] != '\' )
                        .if ( i )
                            fprintf(fp, "</i>" )
                            dec i
                        .else
                            fprintf(fp, "<i>" )
                            inc i
                        .endif
                    .elseif ( al == '*' && ch == '*' )
                        .if ( b )
                            fprintf(fp, "</b>" )
                            dec b
                        .else
                            fprintf(fp, "<b>" )
                            inc b
                        .endif
                        inc rbx
                    .else
                        fprintf(fp, "%c", eax)
                    .endif
                .endw
                fprintf(fp, "</a>")
                mov rbx,t
                mov ecx,3
               .endc
            .case '_'
                .endc .if ( byte ptr [rbx-2] == '\' )
                .if ( i )
                    fprintf(fp, "</i>" )
                    dec i
                .else
                    fprintf(fp, "<i>" )
                    inc i
                .endif
                mov ecx,1
               .endc
            .case '*'
                .if ( byte ptr [rbx] == '*' )
                    .if ( b )
                        fprintf(fp, "</b>" )
                        dec b
                    .else
                        fprintf(fp, "<b>" )
                        inc b
                    .endif
                    inc rbx
                    mov ecx,2
                .endif
                .endc
            .endsw

            .if ( ecx == 0 )
                fprintf(fp, "%c", eax)
            .endif
        .endw


        .if ( b )
            fprintf(fp, "</b>")
            dec b
        .endif
        .if ( i )
            fprintf(fp, "</i>")
            dec i
        .endif
        .if ( li )
            fprintf(fp, "</li>")
            dec li
        .endif
        .if ( h )
            fprintf(fp, "</h%d>", h)
            mov h,0
        .endif
        .if ( p )
            fprintf(fp, "</p>")
            dec p
        .endif
        fprintf(fp, "\n")

continue:

        mov rbx,q
        .break .if rbx == NULL
        .if ( strchr(rbx, 10) )

            mov byte ptr [rax],0
            mov byte ptr [rax-1],0
            inc rax
        .endif
        mov q,rax
    .endw
    fprintf(fp, "</body></html>\n" )
    fclose(fp)
    ret

makehtm endp


makecss proc

    .new fp:LPFILE

    .if ( fopen("style.css", "wt") == NULL )

        perror("style.css")
        exit(1)
    .endif
    mov fp,rax
    fprintf(fp,
        "body { font-family: Verdana, Arial, Helvetica, sans-serif; font-size: 80%%; padding: 0px 0px 0px 20px; }\n"
        "h1, h2, h3, h4 { font-family: Verdana, Arial, Helvetica, sans-serif; }\n"
        "h1 { font-size: 160%%; margin-left: -20px; }\n"
        "h2 { font-size: 140%%; margin-left: -10px; }\n"
        "h3 { font-size: 130%%; margin-left: -10px; }\n"
        "h4 { font-size: 110%%; }\n"
        "a { text-decoration: none; }\n"
        "a:hover { color: #ffffff; background: #1b2466; }\n"
        "table { font-size: 90%%; }\n"
        "td { text-align: center; padding: 0px 10px 0px 10px; }\n"
        "pre { width: 96%%; padding: 4px 10px; font-size: 100%%; }\n"
        "code { width: 96%%; padding: 4px 10px; }\n" )
    fclose(fp)
    ret

makecss endp


makehhp proc uses rbx

    .new fp:LPFILE

    .if ( fopen("asmc.hhp", "wt") == NULL )

        perror("asmc.hhp")
        exit(1)
    .endif
    mov fp,rax
    fprintf(fp,
        "[OPTIONS]\n"
        "Title=Asmc Macro Assembler Reference\n"
        "Compiled file=asmc.chm\n"
        "Contents file=asmc.hhc\n"
        "Index file=asmc.hhk\n"
        "Binary TOC=Yes\n"
        "Binary Index=Yes\n"
        "Auto Index=Yes\n"
        "Compatibility=1.1 or later\n"
        "Default Window=default\n"
        "Default topic=index.htm\n"
        "Display compile progress=No\n"
        "Full-text search=Yes\n"
        "Language=0x409 English (United States)\n"
        "\n"
        "[WINDOWS]\n"
        "default=\"Asmc Macro Assembler Reference\",\"asmc.hhc\",\"asmc.hhk\",\"index.htm\",\"index.htm\",,,,,0x2020,,0x60300e,,,,,,,,0\n"
        "\n"
        "[FILES]\n"
        "style.css\n" )

    .for ( rbx = files : rbx : rbx = [rbx].md.next )

        fprintf(fp, "%s\n", [rbx].md.name )
    .endf
    fprintf(fp,
        "\n"
        "[MAP]\n"
        "[INFOTYPES]\n" )
    fclose(fp)
    ret

makehhp endp


unlink proc p:pmd

    ldr rcx,p

    mov rdx,files
    .if ( rcx == rdx )

        mov rax,[rcx].md.next
        mov files,rax
       .return
    .endif

    .for ( : rdx : rdx = [rdx].md.next )

        .if ( rcx == [rdx].md.next )

            mov rax,[rcx].md.next
            mov [rdx].md.next,rax
           .return
        .endif
    .endf
    ret

unlink endp


getindex proc uses rbx

    .for ( rbx = files : rbx : rbx = [rbx].md.next )

        .if ( strrchr( [rbx].md.name, '/' ) )
            inc rax
        .else
            mov rax,[rbx].md.name
        .endif
        .ifd ( strcmp(rax, "index.htm") == 0 )

            .return( rbx )
        .endif
    .endf
    .return( NULL )

getindex endp


getsubdir proc uses rbx p:pmd

   .new path[_MAX_PATH]:char_t
   .new size:int_t
   .new name:string_t

    ldr rcx,p

    mov name,[rcx].md.name
    .if ( strrchr( strcpy(&path, [rcx].md.name), '/' ) )
        mov byte ptr [rax+1],0
    .else
        mov path,0
    .endif
    mov size,strlen(&path)

    .for ( rbx = files : rbx : rbx = [rbx].md.next )

        .if ( size )
            memcmp(&path, [rbx].md.name, size)
        .else
            strchr( [rbx].md.name, '/' )
        .endif
        .if ( rax == NULL )
            .if ( strcmp(name, [rbx].md.name) )
                .if ( strchr( [rbx].md.file, '#' ) )
                    .if ( byte ptr [rax+1] == ' ' )
                        .return(rbx)
                    .endif
                .endif
            .endif
        .endif
    .endf
    .return( NULL )

getsubdir endp


makehhc proc uses rsi rdi rbx

    .new fp:LPFILE
    .new name:string_t
    .new ul:int_t
    .new pm:pmd

    .if ( fopen("asmc.hhc", "wt") == NULL )

        perror("asmc.hhc")
        exit(1)
    .endif
    mov fp,rax
    fprintf(fp,
        "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n"
        "<HTML><HEAD></HEAD>\n"
        "<BODY>\n"
        "<OBJECT type=\"text/site properties\">\n"
        "    <param name=\"Window Styles\" value=\"0x800025\">\n"
        "    <param name=\"ImageType\" value=\"Folder\">\n"
        "</OBJECT>\n"
        "<UL>\n" )

    .if ( getindex() )

        mov rbx,rax

        .if ( strchr( [rbx].md.file, '#' ) )

            add rax,2
            mov name,rax
        .endif

        fprintf(fp,
           " <LI> <OBJECT type=\"text/sitemap\">\n"
           " <param name=\"Name\" value=\"%s\">\n"
           " <param name=\"Local\" value=\"%s\">\n"
           " </OBJECT>\n", name, [rbx].md.name)

       unlink(rbx)

       .while getindex()

            mov rbx,rax
            mov pm,rax

            fprintf(fp, " <UL>\n" )

            .if ( strchr( [rbx].md.file, '#' ) )

                add rax,2
                mov name,rax
            .endif

            fprintf(fp,
               "  <LI> <OBJECT type=\"text/sitemap\">\n"
               "   <param name=\"Name\" value=\"%s\">\n"
               "   <param name=\"Local\" value=\"%s\">\n"
               "   </OBJECT>\n", name, [rbx].md.name)


            mov ul,0
            .while getsubdir(pm)

                mov rbx,rax

                .if ( ul == 0 )

                    fprintf(fp, "  <UL>\n" )
                    inc ul
                .endif
                .if ( strchr( [rbx].md.file, '#' ) )

                    add rax,2
                    mov name,rax
                .endif

                fprintf(fp,
                   "   <LI> <OBJECT type=\"text/sitemap\">\n"
                   "    <param name=\"Name\" value=\"%s\">\n"
                   "    <param name=\"Local\" value=\"%s\">\n"
                   "    </OBJECT>\n", name, [rbx].md.name)

                unlink(rbx)
            .endw
            .if ( ul )
                fprintf(fp, "  </UL>\n" )
            .endif
            unlink(pm)
            fprintf(fp, " </UL>\n" )
       .endw
    .endif
    fprintf(fp,
        "</UL>\n"
        "</BODY></HTML>\n" )
    fclose(fp)
    ret

makehhc endp

define MAXHHK 800

compare proc a:ptr, b:ptr

    ldr rcx,a
    ldr rdx,b

    mov rcx,[rcx]
    mov rdx,[rdx]
    _stricmp([rcx].md.file, [rdx].md.file)
    ret

compare endp


makehhk proc uses rsi rdi rbx

    .new fp:LPFILE
    .new name:string_t
    .new hhk:int_t = 0
    .new pm[MAXHHK]:pmd

    .if ( fopen("asmc.hhk", "wt") == NULL )

        perror("asmc.hhk")
        exit(1)
    .endif
    mov fp,rax
    fprintf(fp,
        "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n"
        "<HTML>\n"
        "<HEAD>\n"
        "<meta name=\"GENERATOR\" content=\"Microsoft&reg; HTML Help Workshop 4.1\">\n"
        "<!-- Sitemap 1.0 -->\n"
        "</HEAD><BODY>\n"
        "<OBJECT type=\"text/site properties\">\n"
        "    <param name=\"Auto Generated\" value=\"Yes\">\n"
        "</OBJECT>\n"
        "<UL>\n" )

    .for ( rbx = files : rbx && hhk < MAXHHK : rbx = [rbx].md.next )

        .if ( strchr( [rbx].md.file, '#' ) )

            mov ecx,[rax+1]
            .if ( cl == '#' && ch == ' ' )

                mov rcx,[rbx].md.name
                mov edx,[rcx]
                .if ( edx != 'orre' )

                    lea rcx,[rax+3]
                    mov rdx,[rbx].md.file

                    .for ( : byte ptr [rcx] : rcx++, rdx++ )

                        mov eax,[rcx]
                        .if ( al != '\' )

                            mov [rdx],al
                            .if ( al == '&' && ah != 'g' && ah != 'l' )

                                mov eax,';pma'
                                mov [rdx+1],eax
                                add rdx,4
                            .endif
                        .else
                            dec rdx
                        .endif
                    .endf
                    mov byte ptr [rdx],0

                    mov ecx,hhk
                    inc hhk
                    mov pm[rcx*size_t],rbx
                .endif
            .endif
        .endif
    .endf
    .if ( hhk )

        qsort(&pm, hhk, size_t, &compare)

        .for ( ebx = 0 : ebx < hhk : ebx++ )

            mov rcx,pm[rbx*pmd]
            fprintf(fp,
                "<LI> <OBJECT type=\"text/sitemap\">\n"
                " <param name=\"Name\" value=\"%s\">\n"
                " <param name=\"Local\" value=\"%s\">\n"
                " </OBJECT>\n", [rcx].md.file, [rcx].md.name)
        .endf
    .endif
    fprintf(fp,
        "</UL>\n"
        "</BODY></HTML>\n" )
    fclose(fp)
    ret

makehhk endp

_tmain proc uses rbx argc:int_t, argv:array_t

    readfiles(".")
    printf("file count: %d\n", count)

    .if ( count )

        makecss()
        makehhp()

        .for ( rbx = files : rbx : rbx = [rbx].md.next )

            makehtm(rbx)
        .endf
        makehhc()
        makehhk()
    .endif
    .return( 0 )

_tmain endp

    end _tstart
