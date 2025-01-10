; MDHTM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include stdlib.inc
include string.inc
include malloc.inc
include direct.inc
ifdef __UNIX__
define HHC <"chmcmd">
else
include winbase.inc
define HHC <"hhc.exe">
endif
include process.inc
include tchar.inc

.template md

    next string_t ?
    link string_t ?
    name string_t ?
    file string_t ?
   .ends
    pmd typedef ptr md

   .data
    files   pmd 0
    count   int_t 0
    utf_8   db \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 00
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 10
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 20
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 30
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 40
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 50
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 60
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 70
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 80
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; 90
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; A0
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ; B0
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, ; C0
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, ; D0
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, ; E0
        3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0  ; F0

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
ifdef __UNIX__
    .elseif ( word ptr [rcx] == '/.' )
else
    .elseif ( word ptr [rcx] == '\.' )
endif
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
        mov [rcx].md.link,rbx
    .endif
    .if ( strrchr( [rbx].md.name, '/' ) == NULL )
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


strfcat proc uses rsi rdi rbx buffer:string_t, path:string_t, file:string_t

    ldr rsi,path
    ldr rbx,file
    ldr rdx,buffer

    xor eax,eax
    mov ecx,-1

    .if ( rsi )

        mov   rdi,rsi ; overwrite buffer
        repne scasb
        mov   rdi,rdx
        not   ecx
        rep   movsb
    .else
        mov   rdi,rdx ; length of buffer
        repne scasb
    .endif
    sub rdi,1

    .if ( rdi != rdx ) ; add slash if missing

        movzx eax,byte ptr [rdi-1]
ifdef __UNIX__
        .if ( eax != '/' )
            mov eax,'/'
else
        .if ( !( eax == '\' || eax == '/' ) )
            mov eax,'\'
endif
           stosb
        .endif
    .endif

    mov rsi,rbx ; add file name
    .repeat
       lodsb
       stosb
    .until !eax
    .return(rdx)

strfcat endp


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
   .new table:int_t = 0
   .new img:int_t = 0
   .new t:string_t
   .new q:string_t
   .new r[64]:char_t
   .new name:string_t
   .new css[64]:char_t

    ldr rbx,pm

    mov name,[rbx].md.name
    .if ( fopen([rbx].md.name, "wt") == NULL )

        perror([rbx].md.name)
        exit(1)
    .endif
    mov fp,rax

    .if ( strchr([rbx].md.file, 10) == NULL )
        erexit( [rbx].md.name, "Missing \\n" )
    .endif
    .if ( byte ptr [rax-1] == 13 )
        dec rax
    .endif
    mov rcx,rax
    sub rcx,[rbx].md.file
    mov r[rcx],0
    memcpy(&r, [rbx].md.file, ecx)

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
    mov rbx,[rbx].md.name
    mov css,0
    .while strchr(rbx, '/')
        lea rbx,[rax+1]
        strcat(&css, "../")
    .endw
    strcat(&css, "style.css")

    .for ( rbx = t : byte ptr [rbx] == '#' : rbx++ )
    .endf
    .if ( byte ptr [rbx] == ' ' )
        inc rbx
    .endif
    fprintf(fp,
        "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n"
        "<html><head><title>%s</title></head>\n"
        "<link href=\"%s\" rel=\"stylesheet\" type=\"text/css\">\n"
        "<body>\n%s\n", rbx, &css, &r)

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
        .case '<'
            .ifd !memcmp(rbx, "<table", 6)
                mov table,1
            .elseifd !memcmp(rbx, "</table>", 8)
                mov table,0
            .endif
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


        .if ( table || pre )

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
            .case '!'
               .endc .if ( byte ptr [rbx-2] == '\' )
               .endc .if ( byte ptr [rbx] != '[' )
                mov al,[rbx]
                inc rbx
                inc img
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
                .if ( img )
                    mov rbx,rax
                    mov img,0
                    fprintf(fp, "<img alt=\"%s\" src=\"%s\">", t, rcx)
                    mov ecx,1
                   .endc
                .endif
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
                .if ( i == 0 )
                    .ifd !strchr(rbx, '_')

                        mov ecx,eax
                        mov eax,'_'
                       .endc
                    .endif
                .endif
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

                lea     rcx,utf_8
                movzx   ecx,byte ptr [rcx+rax]
                inc     ecx

                .if ( ecx == 1 )

                    fprintf(fp, "%c", eax)

                .elseif ( ecx == 2 )

                    and     eax,0x1F
                    shl     eax,6
                    movzx   edx,byte ptr [rbx]
                    and     edx,0x3F
                    or      eax,edx
                    inc     rbx

                    fprintf(fp, "&#x%04X;", eax)

                .elseif ( ecx == 3 )

                    and     eax,0x0F
                    shl     eax,12
                    movzx   ecx,byte ptr [rbx]
                    and     ecx,0x3F
                    shl     ecx,6
                    or      eax,ecx
                    movzx   edx,byte ptr [rbx+1]
                    and     edx,0x3F
                    or      eax,edx
                    add     rbx,2

                    fprintf(fp, "&#x%04X;", eax)
                .endif
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
            .if ( byte ptr [rax-1] == 13 )
                mov byte ptr [rax-1],0
            .endif
            inc rax
        .endif
        mov q,rax
    .endw
    fprintf(fp, "</body></html>\n" )
    fclose(fp)
    ret

makehtm endp


makecss proc opt_css:int_t

    .new fp:LPFILE

    .if ( opt_css )
        .if !_access("style.css", 0)
            .return
        .endif
    .endif
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
        "td { vertical-align: top; text-align: left; padding: 0px 10px 0px 10px; }\n"
        "pre { width: 96%%; padding: 4px 10px; font-size: 100%%; }\n"
        "code { width: 96%%; padding: 4px 10px; }\n" )
    fclose(fp)
    ret

makecss endp


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


makehhp proc uses rbx name:string_t

    .new fp:LPFILE
    .new title[128]:char_t
    .new file[_MAX_PATH]:char_t

    .if ( !getindex() )

        printf("error : Missing title for: %s\n", name)
        exit(1)
    .endif

    .for ( rbx = [rax].md.file, ecx = 0 : ecx < 128 : ecx++ )

        mov al,[rbx+rcx]
        .break .if ( al <= 13 )
        mov title[rcx],al
    .endf
    mov title[rcx],0

    strcat(strcpy(&file, name), ".hhp")

    .if ( fopen(&file, "wt") == NULL )

        perror(&file)
        exit(1)
    .endif
    mov fp,rax

    fprintf(fp,
        "[OPTIONS]\n"
        "Title=%s\n"
        "Compiled file=%s.chm\n"
        "Contents file=%s.hhc\n"
        "Index file=%s.hhk\n"
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
        "default=\"%s\",\"%s.hhc\",\"%s.hhk\",\"index.htm\",\"index.htm\",,,,,0x2020,,0x60300e,,,,,,,,0\n"
        "\n"
        "[FILES]\n"
        "style.css\n", &title, name, name, name, &title, name, name )

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


unlinkmd proc p:pmd

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

unlinkmd endp


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


makehhc proc uses rsi rdi rbx name:string_t

    .new file[_MAX_PATH]:char_t
    .new fp:LPFILE
    .new title:string_t
    .new ul:int_t
    .new pm:pmd
    .new pt:pmd = files

    strcat(strcpy(&file, name), ".hhc")

    .if ( fopen(&file, "wt") == NULL )

        perror(&file)
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
            mov title,rax
        .endif

        fprintf(fp,
           " <LI> <OBJECT type=\"text/sitemap\">\n"
           " <param name=\"Name\" value=\"%s\">\n"
           " <param name=\"Local\" value=\"%s\">\n"
           " </OBJECT>\n", title, [rbx].md.name)

       unlinkmd(rbx)

       .while getindex()

            mov rbx,rax
            mov pm,rax

            fprintf(fp, " <UL>\n" )

            .if ( strchr( [rbx].md.file, '#' ) )

                add rax,2
                mov title,rax
            .endif

            fprintf(fp,
               "  <LI> <OBJECT type=\"text/sitemap\">\n"
               "   <param name=\"Name\" value=\"%s\">\n"
               "   <param name=\"Local\" value=\"%s\">\n"
               "   </OBJECT>\n", title, [rbx].md.name)


            mov ul,0
            .while getsubdir(pm)

                mov rbx,rax

                .if ( ul == 0 )

                    fprintf(fp, "  <UL>\n" )
                    inc ul
                .endif
                .if ( strchr( [rbx].md.file, '#' ) )

                    add rax,2
                    mov title,rax
                .endif

                fprintf(fp,
                   "   <LI> <OBJECT type=\"text/sitemap\">\n"
                   "    <param name=\"Name\" value=\"%s\">\n"
                   "    <param name=\"Local\" value=\"%s\">\n"
                   "    </OBJECT>\n", title, [rbx].md.name)

                unlinkmd(rbx)
            .endw
            .if ( ul )
                fprintf(fp, "  </UL>\n" )
            .endif
            unlinkmd(pm)
            fprintf(fp, " </UL>\n" )
       .endw
    .endif
    fprintf(fp,
        "</UL>\n"
        "</BODY></HTML>\n" )
    fclose(fp)
    mov files,pt
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


makehhk proc uses rsi rdi rbx name:string_t

    .new fp:LPFILE
    .new file[_MAX_PATH]:char_t
    .new hhk:int_t = 0
    .new pm[MAXHHK]:pmd

    strcat(strcpy(&file, name), ".hhk")

    .if ( fopen(&file, "wt") == NULL )

        perror(&file)
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

            mov rdx,pm[rbx*pmd]
            fprintf(fp,
                "<LI> <OBJECT type=\"text/sitemap\">\n"
                " <param name=\"Name\" value=\"%s\">\n"
                " <param name=\"Local\" value=\"%s\">\n"
                " </OBJECT>\n", [rdx].md.file, [rdx].md.name)
        .endf
    .endif
    fprintf(fp,
        "</UL>\n"
        "</BODY></HTML>\n" )
    fclose(fp)
    ret

makehhk endp


exit_usage proc

    printf(
        "Usage: MDCHM [options] <name>\n"
        "\n"
        "-clean -- delete files on exit\n"
        "-css   -- keep the style.css file: no overwrite or delete on exit\n"
        "\n"
        "<name> is the base name used for <name>.chm, .hhk, .hhc, and .hhp files\n"
        "\n"
        "MDCHM scans the current directory and sub-directories for .md files\n"
        "and converts them to .htm files, readme.md to index.htm\n"
        "\n"
        "The main Title used in the .hhp file is taken from the first line of\n"
        "the first readme.md file. The main structure of a menu-file is:\n"
        "<description>\n"
        "\n"
        "# <title>\n"
        "\n"
        "The structure of an index-file is:\n"
        "<description>\n"
        "\n"
        "## <index>\n"
        "\n"
        )
    exit(0)

exit_usage endp


main proc uses rbx argc:int_t, argv:array_t

    .new hhc[_MAX_PATH]:char_t
    .new hhp[_MAX_PATH]:char_t
    .new buffer[_MAX_PATH]:char_t
    .new path:string_t = &buffer
    .new name:string_t = NULL
    .new opt_clean:int_t = 0
    .new opt_css:int_t = 0

    .for ( ebx = 1 : ebx < argc : ebx++ )

        mov rdx,argv
        mov rcx,[rdx+rbx*size_t]
        mov al,[rcx]
        .if ( al == '-' || al == '/' )
            mov eax,[rcx+1]
            .if ( eax == 'ssc' )
                inc opt_css
            .elseif ( eax == 'aelc' )
                inc opt_clean
            .else
                exit_usage()
            .endif
        .else
            mov name,rcx
        .endif
    .endf
    .if ( name == NULL )
        exit_usage()
    .endif

    readfiles(".")

    .if ( count )

        makecss(opt_css)
        makehhp(name)
        .for ( rbx = files : rbx : rbx = [rbx].md.next )
            makehtm(rbx)
        .endf
        makehhc(name)
        makehhk(name)

        strcpy(&hhc, HHC)
        strcat(strcpy(&hhp, name), ".hhp")
        .ifd ( _searchenv_s( HHC, "PATH", path, _MAX_PATH ) != 0 )
            mov path,&hhc
        .endif
        .if ( _spawnl( P_WAIT, path, path, &hhp, NULL ) == -1 )
            perror(path)
           .return( 1 )
        .endif
        .if ( opt_clean )
            remove(&hhp)
            remove(strcat(strcpy(&hhp, name), ".hhc"))
            remove(strcat(strcpy(&hhp, name), ".hhk"))
            .if ( !opt_css )
                remove("style.css")
            .endif
            .for ( rbx = files : rbx : rbx = [rbx].md.link )
                remove([rbx].md.name)
            .endf
        .endif
    .endif
    .return( 0 )

main endp

    end _tstart
