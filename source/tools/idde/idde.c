/* DZRC.C--
 * Copyright (c) 2016 GNU General Public License www.gnu.org/licenses
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Change history:
 * 2009-09-09 - new startup code, added new switches
 * 2007-03-15 - fixed comandline args
 * 1995-10-22 - created
 */

#include <io.h>
#include <direct.h>
#include <time.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <conio.h>

#define __IDDE__        206

#define MAX_X           127
#define MAX_Y           127
#define MAX_ROW         128
#define MAX_COL         128

#define MAXOBJECT       128
#define MAXWINDOW       (MAX_COL*MAX_ROW)
#define MAXALLOCSIZE    (16+(MAXWINDOW*2)+(MAXOBJECT*16))
#define MAXNAMELEN      32

#define MAXATTRIB       (8+16+16)

#define NAMEOFFSET      25
#define TOBJ_DELETED    0xFFFF

#define MIN(a,b)        (((a) < (b)) ? (a) : (b))
#define MAX(a,b)        (((a) > (b)) ? (a) : (b))
#define MKW(hb,lb)      ((DWORD)(((BYTE)hb<<16)|((BYTE)lb)))

#define _D_STDDLG       (W_MOVEABLE|W_SHADE|W_UNICODE)

#define D_MENUS         0x0001 /* menus color (gray), no title */
#define D_STDLG         0x0002
#define D_STERR         0x0004

#define MKAT(b,f)       (at_background[b] | at_foreground[f])

#define at_Menus        MKAT(BG_MENU,    FG_MENU)
#define at_Dialog       MKAT(BG_DIALOG,  FG_DIALOG)
#define at_Desktop      MKAT(BG_DESKTOP, FG_DESKTOP)
#define at_MenusKey     MKAT(BG_MENU,    FG_MENUKEY)
#define at_DialogKey    MKAT(BG_DIALOG,  FG_DIALOGKEY)
#define at_Panel        MKAT(BG_PANEL,   FG_PANEL)
#define at_Error        MKAT(BG_ERROR,   FG_DESKTOP)
#define at_Title        MKAT(BG_TITLE,   FG_TITLE)
#define at_TitleKey     MKAT(BG_TITLE,   FG_TITLEKEY)

typedef struct {
    RIDD        dialog;
    ROBJ        object[MAXOBJECT];
    CHAR_INFO   wz[MAXWINDOW + 8];
  } CRES;

typedef struct {
    int     x;
    int     y;
    int     at;
    int     ch;
 }  MSXY;

typedef struct {
    TRECT   rc;
    int     key;
  } stinfo;

extern PIDD IDD_RCDesktop;
extern PIDD IDD_RCExternEvent;
extern PIDD IDD_RCQuickMenu;
extern PIDD IDD_RCExit;
extern PIDD IDD_RCChild;
extern PIDD IDD_RCSave;
extern PIDD IDD_RCHelp;
extern PIDD IDD_RCDOBJ;
extern PIDD IDD_RCBackground;
extern PIDD IDD_RCColor;
extern PIDD IDD_RCForeground;
extern PIDD IDD_RCAddFrame;
extern PIDD IDD_RCTOBJ;
extern PIDD IDD_RCOpenFile;

static DOBJ *DLG_RCEDIT = NULL;

#define O_type(o)       (o->flags & O_TYPEMASK)
#define isOpen()        (dialog.flags & W_ISOPEN)
#define isVisible()     (dialog.flags & W_VISIBLE)
#define isDeleted(o)    (o->flags == TOBJ_DELETED)

int option_new = 0;
int fexist_src = 0;

int endmain = 0;
int tclrascii = U_MIDDLE_DOT;
int console = 0;
int dlcolor = 0;
int dltype = D_STDLG;

CRES Resource;
CHAR_INFO winbuf[MAXWINDOW + 80 + 50 + 32];
TOBJ object[MAXOBJECT];
DOBJ dialog = {
    W_MOVEABLE | W_SHADE | W_RESAT | W_UNICODE,
    0,
    0,
    { 10,7,10,60 },
    NULL,
    object
};

int  fsaved_src = 0;
char dialogname[128];
char identifier[128];
char objectname[MAXOBJECT][128];

stinfo st_line[] = {
    { { 1,24, 7, 1}, KEY_F1 },
    { {10,24, 6, 1}, KEY_F2 },
    { {18,24, 7, 1}, KEY_F3 },
    { {27,24, 7, 1}, KEY_F4 },
    { {36,24,12, 1}, KEY_F5 },
    { {50,24, 9, 1}, KEY_F6 },
    { {62,24, 7, 1}, KEY_F7 },
    { {71,24, 7, 1}, KEY_ESC },
};

/* IO */

FILE *fp_src;
FILE *fp_tmp;

char ext_idd[] = ".idd";
char ext_tmp[] = ".tmp";
char ext_bak[] = ".bak";
char *default_ext = ext_idd;

char filename_txt[_MAX_PATH];
char filename_src[_MAX_PATH];
char filename_out[_MAX_PATH];
char filename_tmp[_MAX_PATH];
char filename_bak[_MAX_PATH];

void rc_initscreen(void);

int lwarning(char *msg)
{
    _errmsg("*Warning*", "%s %s %s\n", filename_src, msg);
    return 0;
}

int lerror(char *msg)
{
    _errmsg("**Error**", "%s %s %s\n", filename_src, msg);
    return 0;
}

int IOInitSourceFile(char *name)
{
    char tmp[_MAX_PATH];

    fexist_src = 0;
    strcpy(tmp, name);
    if (_access(tmp, 0) == 0)
        fexist_src = 1;
    strcpy(filename_src, tmp);
    return 1;
}

int IOInitFiles(char *name)
{
    char *p;

    if (IOInitSourceFile(name) == 0)
        return 0;

    strcpy(filename_out, filename_src);
    p = strrchr( filename_out, '.' );
    if ( p == NULL )
        strcat( filename_out, ext_idd );
    else
        strcpy(p, ext_idd);

    strcpy(filename_tmp, filename_out);
    strcpy(filename_bak, filename_out);
    strcpy(strrchr(filename_tmp, '.'), ext_tmp);
    strcpy(strrchr(filename_bak, '.'), ext_bak);
    return 1;
}

FILE *IOOpenSource(char *mode)
{
    fp_src = fopen(filename_src, mode);
    if (fp_src == NULL) {
        _eropen(filename_src);
    }
    return fp_src;
}

FILE *IOOpenTemp(void)
{
    if (filename_tmp[0] == 0)
        return NULL;
    fp_tmp = fopen(filename_tmp, "w");
    if (fp_tmp == NULL) {
        _eropen(filename_tmp);
    }
    return fp_tmp;
}

int IOCloseFiles(void)
{
    if (fp_tmp)
        fclose(fp_tmp);
    if (fp_src)
        fclose(fp_src);
    fp_src = NULL;
    fp_tmp = NULL;
    return 0;
}

int IORename(void)
{
    IOCloseFiles();
    remove(filename_bak);
    rename(filename_out, filename_bak);
    rename(filename_tmp, filename_out);
    return 1;
}

int IORemoveTemp(void)
{
    IOCloseFiles();
    remove(filename_tmp);
    return 0;
}

/* Decompress Resource */

int event_child(void)
{
    switch (rsmodal(IDD_RCChild)) {
    case 4: return _C_REOPEN; /* Rewrite dialog and continue*/
    case 3: return _C_ESCAPE; /* Close dialog and return 0  */
    case 2: return _C_RETURN; /* Close dialog and return 1  */
    case 1: return _C_NORMAL; /* Continue dialog        */
    }
    return 0;
}

int UnzipResource(int count)
{
    int q;
    char *p;

    if (count < 8 || count == sizeof(CRES) ||
        Resource.dialog.rc.x > MAX_X ||
        Resource.dialog.rc.y > MAX_Y ||
        Resource.dialog.rc.row > MAX_ROW ||
        Resource.dialog.rc.col > MAX_COL ||
        Resource.dialog.count > MAXOBJECT) {

        _errmsg("UnzipResource","%04X,%d,%d,{ %d,%d,%d,%d }",
            Resource.dialog.flags,
            Resource.dialog.count,
            Resource.dialog.index,
            Resource.dialog.rc.x,
            Resource.dialog.rc.y,
            Resource.dialog.rc.col,
            Resource.dialog.rc.row);
        return 0;
    }
    p = (char *)&Resource;
    p += 8 + (Resource.dialog.count * 8);
    _rcunzip(Resource.dialog.rc, winbuf, p, Resource.dialog.flags);

    /* Copy resource to dialog */
    memcpy(&dialog, &Resource.dialog, 8);
    dialog.flags = (Resource.dialog.flags & W_RESBITS);
    dialog.object = object;
    dialog.wp = rcopen(dialog.rc, dialog.flags, 0, 0, NULL, NULL);
    if (dialog.wp == NULL)
        return 0;
    memcpy(dialog.wp, &winbuf, (dialog.rc.row * dialog.rc.col) * 4);
    dialog.flags |= W_ISOPEN;
    wcstrcpy(dialogname, dialog.wp, dialog.rc.col);
    if (dialog.count) {
        for (q = 0; q < dialog.count; q++) {
            memcpy(&object[q], &Resource.object[q], 8);
            wcstrcpy((char*)object[q].data, _rcbprc(dialog.rc, object[q].rc, dialog.wp), object[q].rc.col);
            if (object[q].flags & O_CHILD)
                object[q].tproc = event_child;
        }
    }
    return 1;
}

/* Read IDD file */

int bin_read(char *name)
{
    int count;
    char *p;

    if (IOOpenSource("rb") == NULL)
        return 0;
    count = osread(fp_src->_file, &Resource, sizeof(CRES));
    IOCloseFiles();
    dialogname[0] = 0;
    if (UnzipResource(count) == 0)
        return lerror("UnzipResource(<name>)");
    strcpy(identifier, (const char *)strfn(name));
    if ((p = strrchr(identifier, '.')) != NULL)
        *p = 0;
    if (*dialogname == 0)
        strcpy(dialogname, identifier);
    return 1;
}

int IOReadIDD(char *name)
{
    int result;

    result = bin_read(name);

    if (result) {
        if (dialogname[0] == 0)
            strcpy(dialogname, name);
        if (identifier[0] == 0)
            strcpy(identifier, name);
    }
    fsaved_src = result;
    return result;
}

/* Write file */

int IOOnCreate(FILE *fp)
{
    char file[_MAX_PATH];
    SYSTEMTIME t;

    GetLocalTime(&t);
    strcpy(file, strfn(filename_out));
    _strupr(file);
    return 1;
}

int IOCreateSource(void)
{
    if (IOOpenSource("w+") == NULL)
        return IORemoveTemp();
    IOOnCreate(fp_src);
    fclose(fp_src);
    return 1;
}

int IOOpenFiles(void)
{
    if (IOOpenTemp() == NULL)
        return 0;
    fp_src = fopen(filename_src, "r");
    if (fp_src == NULL) {
        if (IOCreateSource() == 0)
            return 0;
        if (IOOpenSource("r") == NULL)
            return IORemoveTemp();
    }
    if (_access(filename_out, 0) == 0)
        return 2;
    IOOnCreate(fp_tmp);
    return 1;
}

/* Write IDD file */

int bin_save(char *name)
{
    TOBJ *o;
    int df,flag;
    int count,q;
    int wc_count;

    if (IOOpenTemp() == NULL)
        return 0;
    flag = dialog.flags;
    if (isVisible())
        dlhide(&dialog);
    df = dialog.flags;
    dialog.flags = W_MYBUF | (flag & W_RESBITS);
    count = 1 + dialog.count;

    wc_count = _rczip(dialog.rc, &Resource.wz, dialog.wp, flag);

    memcpy(&Resource.dialog, &dialog, 8);
    if (count > 1) {
        o = &object[0];
        for (q = 0; q < count - 1; q++, o++)
            memcpy(&Resource.object[q], o, 8);
    }
    oswrite(fp_tmp->_file, &Resource, (count * 8));
    oswrite(fp_tmp->_file, &Resource.wz, wc_count);
    if (flag & W_VISIBLE) {
        dialog.flags = (WORD)df;
        dlshow(&dialog);
    } else {
        dialog.flags = (WORD)flag;
    }
    name++;
    return IORename();
}

int RCCompressDialog(void)
{
    TOBJ *o;
    int flag;
    int count,q;
    int wc_count;

    flag = dialog.flags;
    if (isVisible())
        dlhide(&dialog);
    dialog.flags = W_MYBUF | (flag & W_RESBITS);
    count = 1 + dialog.count;
    wc_count = _rczip(dialog.rc, &Resource.wz, dialog.wp, flag);

    memcpy(&Resource.dialog, &dialog, 8);
    if (count > 1) {
        o = &object[0];
        for (q = 0; q < count - 1; q++, o++)
            memcpy(&Resource.object[q], o, 8);
    }
    if (flag & W_VISIBLE)
        dlshow(&dialog);
    dialog.flags = (WORD)flag;
    return wc_count;
}

int IORCSave(void)
{
    int result;

    result = bin_save(identifier);
    fsaved_src = result;
    return result;
}

/* Edit */

#define STLCOUNT    (sizeof(st_line) / sizeof(stinfo))

CHAR_INFO apbuf[MAX_COL];

void apushstl(char *cp)
{
    if (dialog.rc.y + dialog.rc.row < _console->rc.row )
        wcpushst(apbuf, cp);
}

void apopstl(void)
{
    if (dialog.rc.y + dialog.rc.row < _console->rc.row )
        wcpopst(apbuf);
}

void rc_initscreen(void)
{
    int q;

    for (q = 0; q < 16; q++) {
        _scputa(1 + q, 1, 1, q | (q << 4));
    }

    _scputa(0,  4, 1, at_Desktop);
    _scputa(0,  5, 1, at_Panel);
    _scputa(0,  6, 1, at_Menus);
    _scputa(0,  7, 1, at_Dialog);
    _scputa(0,  8, 1, at_Error);
    _scputa(0,  9, 1, at_Title);
    _scputa(0, 10, 1, at_MenusKey);
    _scputa(0, 11, 1, at_DialogKey);
    _scputa(0, 12, 1, at_TitleKey);
}

void rcputidd(char *n)
{
    if (dialog.rc.y) {
        _scputc(15, 0, 41, ' ');
        if (n == filename_src)
            _scpath(17, 0, 39, n);
        else
            _scputf(15, 0, ": IDD_%s", n);
    }
}

int rcupdate(void)
{
    static int  _mousex = 0;
    static int  _mousey = 0;
    static int  _ocount = 0;
    static int  _oindex = 0;
    static int  _dsaved = 0;

    if (_console->focus == 0)
        return 0;

    if (fsaved_src != _dsaved) {
        _dsaved = rcxyrow(dialog.rc, 2, 23);
        if (_dsaved)
            _dsaved = dlhide(&dialog);
        if (fsaved_src)
            _scputc(1, 0, 1, ' ');
        else
            _scputc(1, 0, 1, '*');
        if (_dsaved)
            dlshow(&dialog);
        _dsaved = fsaved_src;
    }
    if (dialog.rc.y == 0 && dialog.rc.x + dialog.rc.col > 50)
        return 0;
    /* [00:00] [00:00] [00:00] */
    if (_oindex != dialog.index) {
        _oindex = dialog.index;
        _scputf(58, 0, "%02d", _oindex);
    }
    if (_ocount != dialog.count) {
        _ocount = dialog.count;
        _scputf(61, 0, "%02d", _ocount);
    }
    if (_mousex != mousex()) {
        _mousex = mousex();
        _scputf(74, 0, "%02d", _mousex);
        if (_mousex > dialog.rc.x
         && _mousex < dialog.rc.x + dialog.rc.col)
            _scputf(66, 0, "%02d", _mousex - dialog.rc.x);
         else
            _scputf(66, 0, "00");
    }
    if (_mousey != mousey()) {
        _mousey = mousey();
        _scputf(77, 0, "%02d", _mousey);
        if (_mousey > dialog.rc.y
         && _mousey < dialog.rc.y + dialog.rc.row)
            _scputf(69, 0, "%02d", _mousey - dialog.rc.y);
         else
            _scputf(69, 0, "00");
    }
    return 0;
}

int event_handler(void)
{
    switch (rsmodal(IDD_RCExternEvent)) {
    case 1: return KEY_UP;
    case 2: return KEY_ESC;
    case 3: return KEY_RETURN;
    case 4: return KEY_DOWN;
    }
    return 0;
}

enum {
    OBJ_PBUTT,
    OBJ_RBUTT,
    OBJ_CHBOX,
    OBJ_XCELL,
    OBJ_TEDIT,
    OBJ_MENUS,
    OBJ_TBUTT,
    OBJ_USERTYPE,

    OBJ_FLAGA,
    OBJ_RADIO,
    OBJ_FLAGB,
    OBJ_LLIST,
    OBJ_FLAGC,
    OBJ_NOFOCUS,
    OBJ_DEXIT,
    OBJ_FLAGD,
    OBJ_CHILD,
    OBJ_FLAGE,
    OBJ_WNDPROC,
    OBJ_PARENT,
    OBJ_STATE,

    OBJ_RCX,
    OBJ_RCY,
    OBJ_RCCOL,
    OBJ_RCROW,
    OBJ_ASCII,
    OBJ_BCOUNT,
    OBJ_INDEX,
    OBJ_NAME,
    OBJ_OK,
    OBJ_COPY,
    OBJ_DELETE,
    OBJ_CANCEL,
    OBJ_OBJCOUNT
};

DOBJ *tobj_dp;

int cmdeditobj_help(void)
{
    switch (tobj_dp->index) {
    case OBJ_PBUTT:
        _stdmsg("Object type","Push Button");
        break;
    case OBJ_RBUTT:
        _stdmsg("Object type","Radio Button (*)");
        break;
    case OBJ_CHBOX:
        _stdmsg("Object type","Check Box [x]");
        break;
    case OBJ_XCELL:
        _stdmsg("Object type","Text Cell");
        break;
    case OBJ_TEDIT:
        _stdmsg("Object type","Text Edit item");
        break;
    case OBJ_MENUS:
        _stdmsg("Object type","Menu item");
        break;
    case OBJ_TBUTT:
        _stdmsg("Object type","Text Button");
        break;
    case OBJ_USERTYPE:
        _stdmsg("Object type","User defined type");
        break;
    case OBJ_FLAGA:
        _stdmsg("Object flag","User defined flag");
        break;
    case OBJ_RADIO:
        _stdmsg("Object flag","Radio Button On/Off");
        break;
    case OBJ_FLAGB:
        _stdmsg("Object flag","User defined flag\nUses by Check Box [x]");
        break;
    case OBJ_LLIST:
        _stdmsg("Object flag","Linked List item");
        break;
    case OBJ_FLAGC:
        _stdmsg("Object flag","User defined flag\nTEDIT: Text Selected on activation");
        break;
    case OBJ_NOFOCUS:
        _stdmsg("Object flag","No Focus item");
        break;
    case OBJ_DEXIT:
        _stdmsg("Object flag","Exits dialog and returns item->retval");
        break;
    case OBJ_FLAGD:
        _stdmsg("Object flag","User defined flag");
        break;
    case OBJ_CHILD:
        _stdmsg("Object flag","Item is a child\nThis flag is always set");
        break;
    case OBJ_FLAGE:
        _stdmsg("Object flag","User defined flag");
        break;
    case OBJ_WNDPROC:
        _stdmsg("Object flag","Item have local event handler");
        break;
    case OBJ_PARENT:
        _stdmsg("Object flag","tproc() executed on activation");
        break;
    case OBJ_STATE:
        _stdmsg("Object flag","Object State On/Off");
        break;

    case OBJ_RCX:
    case OBJ_RCY:
    case OBJ_RCCOL:
    case OBJ_RCROW:
        _stdmsg("Object RECT","offset from DOBJ.dl_rect");
        break;
    case OBJ_ASCII:
        _stdmsg("Object short-key","Upper Activation Char");
        break;
    case OBJ_BCOUNT:
        _stdmsg("Object count","Memory to allocate for .to_data on init");
        break;
    case OBJ_INDEX:
        _stdmsg("Dialog index","Write new index and hit enter\n\nthen hit Esc");
        break;
    case OBJ_NAME:
        _stdmsg("Name","Object name (if used)");
        break;
    case OBJ_OK:
        _stdmsg("Ok","Save/Exit");
    case OBJ_COPY:
        _stdmsg("Copy","Copy Object");
        break;
    case OBJ_DELETE:
        _stdmsg("Delete","Delete Object");
        break;
    default:
        _stdmsg("TOBJ","Unused");
        break;
    }
    return 0;
}

void object_default(int q)
{
    object[q].rc.x   = 4;
    object[q].rc.y   = 2;
    object[q].rc.col = 8;
    object[q].rc.row = 1;
    object[q].count  = 0;
    object[q].syskey = 0;
    object[q].flags  = 0xFFFF;
    object[q].data   = objectname[q];
    object[q].tproc  = event_handler;
    objectname[q][0] = 0;
}

void objxchg(TOBJ *a, TOBJ *b)
{
    void *p = a->data;

    a->data = b->data;
    b->data = p;
    memxchg(a->data, b->data, 128);
    memxchg(a, b, sizeof(TOBJ));
}

int tobj_moveup(void)
{
    int id;

    if ((id = dialog.index) == 0)
        return 0;
    objxchg(&dialog.object[id], &dialog.object[id - 1]);
    dialog.index--;
    return 1;
}

int tobj_movedown(void)
{
    int id;

    if ((id = dialog.index) == dialog.count - 1)
        return 0;
    objxchg(&dialog.object[id], &dialog.object[id + 1]);
    dialog.index++;
    return 1;
}

void init_rectdlg(TOBJ *o, TRECT rc)
{
    sprintf(o[0].data, "%d", rc.x);
    sprintf(o[1].data, "%d", rc.y);
    sprintf(o[2].data, "%d", rc.col);
    sprintf(o[3].data, "%d", rc.row);
}

void save_rectdlg(TRECT *rc, TOBJ *o)
{
    rc->x   = atoi(o[0].data);
    rc->y   = atoi(o[1].data);
    rc->col = atoi(o[2].data);
    rc->row = atoi(o[3].data);
}

void init_objectdlg(TOBJ *o, TOBJ *src)
{
    int q;
    char *p;

    tosetbitflag(o + 8, O_FLAGBITS, O_CHECK, src->flags >> O_TYPEBITS);
    q = (src->flags & O_TYPEMASK);
    o[q].flags |= O_RADIO;
    q = src->count;
    q <<= 4;
    sprintf(o[OBJ_BCOUNT].data, "%d", q);
    p = (char*)o[OBJ_ASCII].data;
    p[0] = src->syskey;
    p[1] = 0;
    init_rectdlg(&o[OBJ_RCX], src->rc);
}

int tdgetrdid(DOBJ *d)
{
    int x,s;
    TOBJ *o;

    o = d->object;
    for (x = 0; x < d->count; x++) {
        if ((o[x].flags & O_TYPEMASK) == O_RBUTT)
            break;
    }
    s = x;
    for (; x < d->count; x++) {
        if (o[x].flags & O_RADIO)
            return x - s;
    }
    return 0;
}

void save_objectdlg(TOBJ *o, TOBJ *src)
{
    int q,x;
    char *p;

    src->flags = (WORD)(togetbitflag(o + 8, O_FLAGBITS, O_CHECK) << O_TYPEBITS);
    src->flags |= tdgetrdid(tobj_dp);
    save_rectdlg(&src->rc, &o[OBJ_RCX]);
    p = (char*)o[OBJ_ASCII].data;
    src->syskey = *p;
    p = (char*)o[OBJ_BCOUNT].data;
    if ((q = atoi(p)) != 0) {
        x = (q & 16-1);
        q >>= 4;
        if (x != 0)
            q++;
    }
    src->count = q;
}

int update_object(TOBJ *o)
{
    int     at;
    int     att;
    PCHAR_INFO sw;
    char *  cp;
    TRECT   rc;

    at = _scgeta(dialog.rc.x, dialog.rc.y + 1);
    dlhide(&dialog);
    rc = o->rc;
    cp = (char*)o->data;
    sw = _rcbprc(dialog.rc, rc, dialog.wp);
    att = sw->Attributes;
    fsaved_src = 0;
    switch (O_type(o)) {
    case O_PBUTT:
        wcputw(sw, rc.col + 1, MKW(at, ' '));
        wcputw(sw + dialog.rc.col + 1, rc.col, MKW(at, ' '));
        wcpbutt(sw, dialog.rc.col, rc.col, cp);
        break;
    case O_RBUTT:
        wcputw(sw, rc.col, MKW(at, ' '));
        if (cp != NULL)
            wcputs(sw, 0, 0, cp);
        break;
    case O_CHBOX:
        wcputw(sw, rc.col, MKW(at, ' '));
        if (cp != NULL)
            wcputs(sw, 0, 0, cp);
        break;
    case O_TEDIT:
        wcputw(sw, rc.col, MKW(att, tclrascii));
        break;
    case O_MENUS:
    case O_XCELL:
        if (cp != NULL && *cp) {
            wcputw(sw, rc.col, MKW(att, ' '));
            wcputs(sw + 1, 0, 0, cp);
        }
        break;
    case O_USERTYPE:
        if (cp != NULL && *cp) {
            wcputw(sw, rc.col, MKW(att, ' '));
            wcputs(sw, 0, 0, cp);
        }
        break;
    default:
        fsaved_src = 1;
        break;
    }
    dlshow(&dialog);
    return 0;
}

int event_index(void)
{
    int id;

    id = atoi(tobj_dp->object[OBJ_INDEX].data);
    if (id < dialog.index) {
        while (id < dialog.index) {
            if (tobj_moveup() == 0)
                break;
        }
        if (id < dialog.index)
            _errmsg("TObject", "Index out of range: %d", id);
    } else if (id > dialog.index) {
        while (id > dialog.index) {
            if (tobj_movedown() == 0)
                break;
        }
        if (id > dialog.index)
            _errmsg("TObject", "Index out of range: %d", id);
    }
    sprintf(tobj_dp->object[OBJ_INDEX].data, "%d", dialog.index);
    return _C_REOPEN;
}

int cmddelete(int id)
{
    int a,q;
    TRECT rc;
    TOBJ *o;

    o = object;
    a = _scgeta(dialog.rc.x, dialog.rc.y + 1);
    rc = _rcaddrc(dialog.rc, o[id].rc);
    for (q = 0; q < rc.row; q++)
        _scputw(rc.x, rc.y + q, rc.col, a << 16 | ' ');
    if ((o[id].flags & O_USERTYPE) == O_PBUTT) {
        _scputc(rc.x + rc.col, rc.y, 1, ' ');
        _scputc(rc.x, rc.y + 1, rc.col + 2, ' ');
    }
    o[id].flags = TOBJ_DELETED;
    for (q = id + 1; q < dialog.count; q++) {
        if (o[q].flags != TOBJ_DELETED)
            objxchg(&o[q - 1], &o[q]);
    }
    if (dialog.count)
        dialog.count--;
    if (dialog.index >= dialog.count)
        dialog.index--;
    fsaved_src = 0;
    return 1;
}

int getobjid(void)
{
    int id;

    if (++dialog.count >= MAXOBJECT) {
        dialog.count--;
        return -1;
    }
    for (id = 0; id < MAXOBJECT; id++) {
        if (object[id].flags == TOBJ_DELETED)
            break;
    }
    if (id >= MAXOBJECT)
        return -1;
    return id;
}

int cmdeditobj(int id)
{
    TOBJ *o;
    TOBJ *q;
    int result;
    DPROC old_thelp;

    if (isOpen() == 0 || (tobj_dp = rsopen(IDD_RCTOBJ)) == NULL)
        return 0;
    old_thelp = _inithelp(cmdeditobj_help);
    dialog.index = id;
    o = tobj_dp->object;
    o[OBJ_INDEX].tproc = event_index;
    o[OBJ_PBUTT].data = "TObject";
    q = &object[id];
    strcpy(o[OBJ_NAME].data, object[id].data);
    sprintf(o[OBJ_INDEX].data, "%d", dialog.index);
    init_objectdlg(o, q);
    dlinit(tobj_dp);
    dlshow(tobj_dp);
    result = rsevent(IDD_RCTOBJ, tobj_dp);
    _inithelp(old_thelp);

    if (result == 0) {
        dlclose(tobj_dp);
        return 0;
    }
    if (result == OBJ_DELETE + 1) {
        dlclose(tobj_dp);
        cmddelete(dialog.index);
        return -1;
    }
    if (result == OBJ_COPY + 1) {
        if ((result = getobjid()) == -1) {
            dlclose(tobj_dp);
            return 0;
        }
        dialog.index = result;
        strcpy(object[result].data, o[OBJ_NAME].data);
        save_objectdlg(o, &object[result]);
        dlclose(tobj_dp);
        update_object(&object[result]);
        return cmdeditobj(result);
    }
    q = &object[dialog.index];
    strcpy(q->data, o[OBJ_NAME].data);
    save_objectdlg(o, q);
    dlclose(tobj_dp);
    update_object(q);
    return 1;
}

enum {  ID_ADDCANCEL,
        ID_ADDPBUTT,
        ID_ADDRBUTT,
        ID_ADDCHBOX,
        ID_ADDTEDIT,
        ID_ADDXCELL,
        ID_ADDMENUS };

int cmdaddobj(void)
{
    int id;
    int flag;
    int result;

    flag = _O_PBUTT;
    if ((id = getobjid()) == -1)
        return 0;
    object_default(id);
    object[id].flags = flag;
    result = cmdeditobj(id);
    if (result == 0) {
        object[id].flags = TOBJ_DELETED;
        dialog.count--;
    }
    return result;
}

void dialog_default(void)
{
    int q;

    dlcolor       = _D_CLEAR|_D_COLOR;
    dialog.flags  = _D_STDDLG;
    dialog.rc.x   = 10;
    dialog.rc.y   = 7;
    dialog.rc.row = 10;
    dialog.rc.col = 60;
    dialog.count  = 0;
    dialog.index  = 0;
    dialog.object = object;
    for (q = 0; q < MAXOBJECT; q++)
        object_default(q);
}

int opendlg(void)
{
    int color;
    TRECT rc;

    if (dialog.flags & W_ISOPEN)
        return dlshow(&dialog);
    switch(dltype & (D_STERR|D_MENUS|D_STDLG)) {
        case D_STERR: color = at_Error; break;
        case D_MENUS: color = at_Menus; break;
        case D_STDLG: color = at_Dialog; break;
        default:
            color = at_Desktop;
            break;
    }
    if (dltype & D_MENUS) {
        if ((dialog.wp = rcopen(
            dialog.rc,
            dialog.flags,
            dlcolor,
            color,
            NULL,
            dialog.wp)) == NULL) {
            return 0;
        }
        rc = dialog.rc;
        rc.x = 0;
        rc.y = 1;
        rc.row--;
        _rcframe(dialog.rc, rc, dialog.wp, BOX_SINGLE, 0);
    } else {
        if ((dialog.wp = rcopen(
            dialog.rc,
            dialog.flags,
            dlcolor,
            color,
            dialogname,
            dialog.wp)) == NULL) {
            return 0;
        }
    }
    dialog.flags |= W_ISOPEN;
    dlshow(&dialog);
    return 1;
}

int closedlg(void)
{
    int result;

    result = dlclose(&dialog);
    dialog_default();
    fsaved_src = 0;
    option_new = 1;
    return result;
}

int moveobj(TRECT *rp, void *wp, int flag)
{
    int end;
    TRECT rc;

    rc = *rp;
    end  = 0;
    while (end == 0) {
        _gotoxy(rc.x, rc.y);
/*
        if (mousep() == 1) {
            rcmsmove(&rc, wp, flag);
            break;
        } else switch (getkey()) {
*/
        switch (tgetevent()) {
        case MOUSECMD:
            if (mousep() == 1) {
                rcmsmove(&rc, wp, flag);
                end = 1;
            }
            break;
        case KEY_UP:
            rcmove(&rc, wp, flag, rc.x, rc.y - 1);
            break;
        case KEY_DOWN:
            rcmove(&rc, wp, flag, rc.x, rc.y + 1);
            break;
        case KEY_LEFT:
            rcmove(&rc, wp, flag, rc.x - 1, rc.y);
            break;
        case KEY_RIGHT:
            rcmove(&rc, wp, flag, rc.x + 1, rc.y);
            break;
        case KEY_RETURN:
            end = 1;
            break;
        case KEY_ESC:
            end = KEY_ESC;
            break;
        }
    }
    if (end == KEY_ESC)
        return 0;
    *rp = rc;
    return 1;
}

/*
 * Get char/attrib/RECT from screen using mouse
 */

char cp_msstart   [] = "Click on start point..";
char cp_msend     [] = "Click on end point..";
char cp_msinvalid [] = "Ivalid point...";

int msinvalid(void)
{
    apushstl(cp_msinvalid);
    while (mousep())
        ;
    apopstl();
    return 0;
}

#define delay Sleep

int getxy(int *sx, int *sy, char *msg)
{
    int x = *sx,
        y = *sy,
        end = 0;

    apushstl(msg);
    delay(10);
    while (mousep());

    while (end == 0) {
        _gotoxy(x, y);
        switch (tgetevent()) {
        case KEY_UP:
            if (y == 0)
                break;
            y--;
            break;
        case KEY_LEFT:
            if (x == 0)
                break;
            x--;
            break;
        case KEY_RIGHT: x++; break;
        case KEY_DOWN:  y++; break;
        case MOUSECMD:
            x = mousex();
            y = mousey();
        case KEY_RETURN:
            end = 1;
            break;
        case KEY_ESC:
            end = KEY_ESC;
            break;
        }
    }
    *sx = x;
    *sy = y;
    apopstl();
    _gotoxy(x, y);
    while (mousep());
    return (end != KEY_ESC);
}

int msgetevent(char *msg)
{
    int event;

    apushstl(msg);
    while (mousep());
    event = tgetevent();
    apopstl();
    if (event != MOUSECMD)
        return 0;
    return 1;
}

int msgetrc(TRECT dl, TRECT *rp)
{
    TRECT rc;
    int x,y;

    x = dl.x;
    y = dl.y;
    if (getxy(&x, &y, cp_msstart) == 0)
        return 0;
    rc = dl;
    if (rcxyrow(rc, x, y) == 0)
        return msinvalid();
    rc.x = x;
    rc.y = y;
    if (getxy(&x, &y, cp_msend) == 0)
        return msinvalid();
    if (y == rc.y && x == rc.x)
        return msinvalid();
    if (y < rc.y) {
        rc.row = rc.y - y + 1;
        rc.y = y;
    } else {
        rc.row = y - rc.y + 1;
    }
    if (x < rc.x) {
        rc.col = rc.x - x + 1;
        rc.x = x;
    } else {
        rc.col = x - rc.x + 1;
    }
    if (_rcinside(dl, rc) != 0)
        return msinvalid();
    *rp = rc;
    return 1;
}

int msget(MSXY *ms, char *cp)
{
    int x,y;

    if (msgetevent(cp) == 0)
        return msinvalid();
    x = mousex();
    y = mousey();
    ms->x = x;
    ms->y = y;
    ms->at = _scgeta(x, y);
    ms->ch = _scgetc(x, y);
    return 1;
}

/*
 * IDD_SaveIDD - Save dialog to file
 */
enum {
    ID_Identifier,
    ID_Filename,
    ID_Save,
    ID_Cancel
};

int cmdsave(void)
{
    DOBJ *p;
    int result;

    if (fsaved_src)
        return 0;
    if ((dialog.flags & W_ISOPEN) == 0)
        return 0;
    if ((p = rsopen(IDD_RCSave)) == NULL)
        return 0;

    strcpy(p->object[ID_Identifier].data, identifier);
    strcpy(p->object[ID_Filename].data, filename_out);
    dlinit(p);
    if (rsevent(IDD_RCSave, p) == 0) {
        dlclose(p);
        return 0;
    }

    strcpy(identifier, p->object[ID_Identifier].data);

    result = IOInitFiles(p->object[ID_Filename].data);
    dlclose(p);
    rcputidd(identifier);
    if (result) {
        fsaved_src = IORCSave();
        return fsaved_src;
    }
    return 0;
}

/*
 * IDD_Color - Edit color setup
 */
int cmdcolor(void)
{
/*  editattrib(); */
    return 1;
}

int cmdtext(void)
{
    int  x,y;
    TRECT rc;
    CHAR_INFO sc[80];
    char cb[80];

    apushstl(cp_msstart);
    while (mousep());
    x = tgetevent();
    apopstl();
    if (x != MOUSECMD)
        return 0;
    rc = dialog.rc;
    x = mousex();
    y = mousey();
    if (rcxyrow(rc, x, y) == 0)
        return 0;
    while (mousep());
    rc.col -= (x - rc.x);
    rc.x = x;
    rc.y = y;
    rc.row = 1;
    cb[0] = 0;
    _rcread(rc, sc);
    if (dledit(cb, rc, 80, 0) != KEY_RETURN) {
        _rcwrite(rc, sc);
        return 0;
    }
    _rcwrite(rc, sc);
    scputs(rc.x, rc.y, 0, 80, cb);
    fsaved_src = 0;
    return 1;
}

int cmdresize(void)
{
    TRECT rc;
    CHAR_INFO a,b,c,h,v;
    PCHAR_INFO wp;
    int ex,x;
    int ey,y;
    int z,q,flag;

    fsaved_src = 0;
    flag = dialog.flags;
    while (mousep() == 1) {
        x = mousex();
        y = mousey();
        rc = dialog.rc;
        ex = rc.x + rc.col - 1;
        ey = rc.y + rc.row - 1;
        if (x != ex || y != ey) {
            if (x < rc.x + 10 || y < rc.y + 2) {
                mousewait(x, y, 1);
                continue;
            }
            if (x != ex)
                rc.col = x - rc.x + 1;
            if (y != ey)
                rc.row = y - rc.y + 1;
            wp = (CHAR_INFO *)rcopen(rc, dialog.flags & (W_SHADE|W_UNICODE), 0, 0, 0, 0);
            z = 0;
            if (x < ex || y < ey) {
                dlhide(&dialog);
                v = dialog.wp[dialog.rc.col];
                a = dialog.wp[dialog.rc.col-1];
                b = dialog.wp[dialog.rc.col*(dialog.rc.row-1)];
                h = dialog.wp[dialog.rc.col*(dialog.rc.row-1)+1];
                c = dialog.wp[dialog.rc.col*(dialog.rc.row-1)+dialog.rc.col-1];
            } else {
                if (x > ex)
                    z = x - ex;
                else if (y > ey)
                    z = y - ey;
                v = wp[rc.col];
                a = wp[dialog.rc.col-1];
                b = wp[rc.col*(dialog.rc.row-1)];
                h = wp[rc.col*(dialog.rc.row-1)+1];
                c = wp[rc.col*(dialog.rc.row-1)+dialog.rc.col-1];
            }
            dlclose(&dialog);
            wp[rc.col-1] = a;
            wcmemset(&wp[1], wp[1], rc.col-2);
            wp[rc.col*(rc.row-1)] = b;
            wp[rc.col*rc.row-1] = c;
            wcmemset(&wp[(rc.row-1)*rc.col+1], h, rc.col-2);
            b.Char.UnicodeChar = ' ';
            for (q = 1; q < rc.row-1; q++) {
                wp[rc.col*q] = v;
                wp[rc.col*q+rc.col-1] = v;
                if (z) {
                    wcmemset(&wp[rc.col*q+rc.col-1-z], b, z);
                }
            }
            if (y > ey) {
                wcmemset(&wp[rc.col*(rc.row-2)+1], b, rc.col-2);
            }
            wcenter(wp, rc.col, dialogname);
            dialog.rc = rc;
            dialog.wp = wp;
            dialog.flags |= W_ISOPEN;
            dlshow(&dialog);
        }
        mousewait(x, y, 1);
    }
    dialog.flags = flag;
    return 0;
}

int cmdmoveobj(int i)
{
    int flag;
    int result;
    TRECT rc;
    PCHAR_INFO wp;

    fsaved_src = 0;
    apushstl("Use Mouse or [Left/Right/Up/Down] to move object..");
    flag = W_MOVEABLE|W_UNICODE;
    rc = _rcaddrc(dialog.rc, object[i].rc);
    if ((object[i].flags & O_USERTYPE) == O_PBUTT) {
        rc.row++;
        rc.col++;
    }
    wp = rcopen(rc, flag, _D_CLEAR|_D_COLOR, _scgeta(dialog.rc.x, dialog.rc.y + 1), 0, 0);
    flag |= (W_ISOPEN|W_VISIBLE);
    result = moveobj(&rc, wp, flag);
    apopstl();
    if (result == 0 ||
        rc.x < dialog.rc.x ||
        rc.y < dialog.rc.y ||
        rc.x + rc.col > dialog.rc.x + dialog.rc.col ||
        rc.y + rc.row > dialog.rc.y + dialog.rc.row) {
        _rcxchg(rc, wp);
        rc.x = object[i].rc.x + dialog.rc.x;
        rc.y = object[i].rc.y + dialog.rc.y;
        rcclose(rc, W_ISOPEN|W_VISIBLE, wp);
        return 0;
    }
    object[i].rc.x = rc.x - dialog.rc.x;
    object[i].rc.y = rc.y - dialog.rc.y;
    rcclose(rc, W_ISOPEN, wp);
    return 1;
}

int cmdmovetext(void)
{
    int flag;
    int result;
    TRECT rc;
    PCHAR_INFO wp;

    fsaved_src = 0;
    if (msgetrc(dialog.rc, &rc) == 0)
        return msinvalid();

    flag = W_MOVEABLE|W_UNICODE;
    wp = rcopen(rc, flag, _D_CLEAR|_D_COLOR, _scgeta(dialog.rc.x, dialog.rc.y + 1), 0, 0);
    flag |= (W_ISOPEN|W_VISIBLE);
    apushstl("Mouseclick on first line, or [Left/Right/Up/Down] to move object..");
    while (mousep() == 1);
    result = moveobj(&rc, wp, flag);
    apopstl();
    rcclose(rc, W_ISOPEN, wp);
    return result;
}

int cmdframe(void)
{
    TRECT rc;
    int type;

    if ((type = rsmodal(IDD_RCAddFrame)) == 0)
        return msinvalid();
    if (msgetrc(dialog.rc, &rc) == 0)
        return msinvalid();
    dlhide(&dialog);
    type--;
    rc.y -= dialog.rc.y;
    rc.x -= dialog.rc.x;
    _rcframe(dialog.rc, rc, dialog.wp, type, 0);
    dlshow(&dialog);
    fsaved_src = 0;
    return 1;
}

int cmdclearat(void)
{
    int b,f;

    if (isOpen() == 0)
        return 0;
    if (isVisible() == 0)
        dlshow(&dialog);

    apushstl("Select background color of attrib..");
    if ((b = rsmodal(IDD_RCBackground)) == 0)
        return 0;
    b = (b - 1) << 4;
    apushstl("Select foreground color of attrib..");
    if ((f = rsmodal(IDD_RCForeground)) == 0)
        return 0;
    apopstl();
    b |= (f - 1);
    dlhide(&dialog);
    wcputa(dialog.wp, dialog.rc.col * dialog.rc.row, b);
    dlshow(&dialog);
    fsaved_src = 0;
    return 1;
}

int cmdclearfg(void)
{
    int x,y,a,n;
    MSXY ms;

    if (isOpen() == 0)
        return 0;
    if (isVisible() == 0)
        dlshow(&dialog);
    if (msget(&ms, "Click on foreground color to change..") == 0)
        return 0;
    a = (ms.at & 0x0F);
    if (msget(&ms, "Click to get new foreground color to set..") == 0)
        return 0;
    n = (ms.at & 0x0F);
    dlhide(&dialog);
    for (x = 0; x < dialog.rc.col * dialog.rc.row; x++) {
        y = dialog.wp[x].Attributes;
        if ((y & 0x0F) == a) {
            dialog.wp[x].Attributes &= 0xF0;
            dialog.wp[x].Attributes |= n;
        }
    }
    dlshow(&dialog);
    fsaved_src = 0;
    return 1;
}

int cmdfground(void)
{
    int x,y;
    int color;
    TRECT rc;

    x = rsmodal(IDD_RCForeground);
    if (x == 0)
        return 0;
    rc = dialog.rc;
    color = x - 1;
    apushstl("Click to set foreground..");
    while (mousep());
    while ( 1 ) {
        if (tgetevent() != MOUSECMD)
            break;
        x = mousex();
        y = mousey();
        if (mousep() == 1 && rcxyrow(rc, x, y)) {
            _scputfg(x, y, 1, color);
        } else if (mousep() == 2) {
            color = _scgeta(x, y);
        }
        mousewait(x, y, 1);
    }
    apopstl();
    fsaved_src = 0;
    return 1;
}

int cmdclearbg(void)
{
    int x,a,n;
    MSXY ms;

    if (isOpen() == 0)
        return 0;
    if (isVisible() == 0)
        dlshow(&dialog);
    if (msget(&ms, "Click on color to change..") == 0)
        return 0;
    if (rcxyrow(dialog.rc, ms.x, ms.y) == 0)
        return 0;
    a = (ms.at & 0xF0);
    if (msget(&ms, "Click to get new color to set..") == 0)
        return 0;
    n = (ms.at & 0xF0);
    dlhide(&dialog);
    for (x = 0; x < dialog.rc.col * dialog.rc.row; x++) {
        if ((dialog.wp[x].Attributes & 0xF0) == a) {
            dialog.wp[x].Attributes &= 0x0F;
            dialog.wp[x].Attributes |= n;
        }
    }
    dlshow(&dialog);
    fsaved_src = 0;
    return 1;
}

int cmdbground(void)
{
    int x,y;
    int color;
    TRECT rc;

    x = rsmodal(IDD_RCBackground);
    if (x == 0)
        return 0;
    rc = dialog.rc;
    color = (x - 1);
    apushstl("Left-Click to set/Right-Click to get background..");
    while ( 1 ) {
        if (tgetevent() != MOUSECMD)
            break;
        x = mousex();
        y = mousey();
        if (mousep() == 1 && rcxyrow(rc, x, y)) {
            _scputbg(x, y, 1, color);
        } else if (mousep() == 2) {
            color = (_scgeta(x, y) >> 4);
        }
        mousewait(x, y, 1);
    }
    apopstl();
    fsaved_src = 0;
    return 1;
}

int cmdascii(void)
{
    int ch;
    int q;
    int x,y;
    TRECT rc;

    apushstl("Left-Click to set/Right-Click to get ascii..");
    while (mousep());
    q = tgetevent();
    if (q != MOUSECMD) {
        apopstl();
        return 0;
    }
    x = mousex();
    y = mousey();
    ch = _scgetc(x, y);
    rc = dialog.rc;
    while ( 1 ) {
        if (tgetevent() != MOUSECMD)
            break;
        x = mousex();
        y = mousey();
        if (mousep() == 1 && rcxyrow(rc, x, y)) {
            _scputc(x, y, 1, ch);
        } else if (mousep() == 2) {
            ch = _scgetc(x, y);
        }
        mousewait(x, y, 1);
    }
    apopstl();
    fsaved_src = 0;
    return 1;
}

int cmdcenter(void)
{
    int x = 40 - (dialog.rc.col / 2);
    int y = 12 - (dialog.rc.row / 2);

    dlhide(&dialog);
    dialog.rc.x = x;
    dialog.rc.y = y;
    dlshow(&dialog);
    fsaved_src = 0;

    return 1;
}

int cmdtitle(void)
{
    int result;

    if ((result = _tgetline("Dialogname title", dialogname, 32, 128)) != 0) {
        if (dialog.flags & W_ISOPEN) {
            TRECT rc = dialog.rc;
            result = dlhide(&dialog);
            if (dialog.wp[0].Char.UnicodeChar == ' ')
                wctitle(dialog.wp, rc.col, dialogname);
            else
                wcenter(dialog.wp, rc.col, dialogname);
            if (result)
                dlshow(&dialog);
        }
    }
    return _C_NORMAL;
}

enum {
    ID_DOPEN,
    ID_ONSCR,
    ID_DMOVE,
    ID_SHADE,
    ID_MYBUF,
    ID_RCNEW,
    ID_RESAT,
    ID_DHELP,
    ID_CLEAR,
    ID_BACKG,
    ID_FOREG,
    ID_STDLG,
    ID_STERR,
    ID_MENUS,
    ID_MUSER,
    ID_KLINE,
    ID_NAME,
    ID_COUNT,
    ID_INDEX,
    ID_RCX,
    ID_RCY,
    ID_RCCOL,
    ID_RCROW,
    ID_SETAT,
    ID_SETBG,
    ID_SETFG,
    ID_TITLE,
    ID_OK,
    ID_DCANCEL
};

int cmdeditdlg_help(void)
{
    switch (tdialog->index) {
    case ID_DOPEN:
        _stdmsg("DOPEN","dialog is open - runtime value");
        break;
    case ID_ONSCR:
        _stdmsg("ONSCR","dialog is on screen - runtime value");
        break;
    case ID_DMOVE:
        _stdmsg("DMOVE","dialog is movable");
        break;
    case ID_SHADE:
        _stdmsg("SHADE","dialog have shade");
        break;
    case ID_MYBUF:
        _stdmsg("MYBUF","dialog is static - don't delete");
        break;
    case ID_RCNEW:
        _stdmsg("RCNEW","delete dialog on exit if set - runtime value");
        break;
    case ID_RESAT:
        _stdmsg("RESAT","Color is table-index (Setup(F7))");
        break;
    case ID_DHELP:
        _stdmsg("DHELP","Call *thelp on F1 if set");
        break;
    case ID_CLEAR:
    case ID_BACKG:
    case ID_FOREG:
        _stdmsg("CLEAR/BACKG/FOREG","runtime values");
        break;
    case ID_STDLG:
        _stdmsg("STDLG","Standard dialog - use title line");
        break;
    case ID_STERR:
        _stdmsg("STERR","Standard dialog - Red background");
        break;
    case ID_MENUS:
        _stdmsg("MENUS","..");
        break;
    case ID_MUSER:
        _stdmsg("MUSER","..");
        break;
    case ID_KLINE:
        _stdmsg("KLINE","Key Bar or Status Line\nB_Menus | F_KeyBar");
        break;
    case ID_NAME:
        _stdmsg("NAME","Dialog Name");
        break;
    case ID_COUNT:
        _stdmsg("COUNT","Object count");
        break;
    case ID_INDEX:
        _stdmsg("INDEX","Dialog index");
        break;
    case ID_RCX:
    case ID_RCY:
    case ID_RCCOL:
    case ID_RCROW:
        _stdmsg("TRECT","Dialog TRECT");
        break;
    case ID_SETAT:
        _stdmsg("Clear","Clear Dialog with new color");
        break;
    case ID_SETBG:
        _stdmsg("Set","Change background color");
        break;
    case ID_SETFG:
        _stdmsg("Set","Change foreground color");
        break;
    case ID_TITLE:
        _stdmsg("Title","Change Dialog Title");
        break;
    case ID_OK:
    case ID_DCANCEL:
    default:
        _stdmsg("Dialog","no help on this item...");
        break;
    }
    return 0;
}

int cmdeditdlg(void)
{
    TOBJ *o;
    DOBJ *d;
    int result;
    int (*old_thelp)(void);

    if ((d = rsopen(IDD_RCDOBJ)) == NULL)
        return 0;
    old_thelp = _inithelp(cmdeditdlg_help);
    o = d->object;
    strcpy(o[ID_NAME].data, identifier);
    tosetbitflag(o, 16, O_CHECK, dialog.flags);
    sprintf(o[ID_COUNT].data, "%d", dialog.count);
    sprintf(o[ID_INDEX].data, "%d", dialog.index);
    init_rectdlg(&o[ID_RCX], dialog.rc);
    dlinit(d);
    result = rsevent(IDD_RCDOBJ, d);
    _inithelp(old_thelp);
    if (result == 0) {
        dlclose(d);
        return 0;
    }
    strcpy(identifier, o[ID_NAME].data);
    dialog.flags  = (WORD)togetbitflag(o, 16, O_CHECK);
    save_rectdlg(&dialog.rc, &o[ID_RCX]);
    dialog.index = atoi(o[ID_INDEX].data);
    dlclose(d);
    rcputidd(identifier);
    if (dialog.index >= dialog.count)
        dialog.index = 0;
    switch (result - 1) {
    case ID_SETAT: cmdclearat(); break;
    case ID_SETBG: cmdclearbg(); break;
    case ID_SETFG: cmdclearfg(); break;
    case ID_TITLE: cmdtitle();
    default:
        break;
    }
    fsaved_src = 0;
    return 1;
}

/*
 * Create a new Dialog
 */
int cmdnewdlg(void)
{
    cmdsave();
    closedlg();
    fsaved_src = 0;
    option_new = 1;
    strcpy(identifier, "Dialogname");
    strcpy(dialogname, identifier);
    if (cmdeditdlg() == 0)
        return 0;
    opendlg();
    return 1;
}

int cmdhelp(void)
{
    return rsmodal(IDD_RCHelp);
}

int cmdexit(void)
{
    if (rsmodal(IDD_RCExit))
        endmain = 1;
    return endmain;
}


int cmdmenu(void)
{
    int x;
    DOBJ *p;

    if ((dialog.flags & W_VISIBLE) == 0)
        return 0;
    if (mousep() == 2) {
        IDD_RCQuickMenu->rc.x = mousex();
        IDD_RCQuickMenu->rc.y = mousey();
    }
    if ((p = rsopen(IDD_RCQuickMenu)) == NULL)
        return 0;
    dlshow(p);
    while (mousep());
    switch (dlmodal(p)) {
    case 9: return cmdmovetext();
    case 8: dlinit(&dialog);
        return dlevent(&dialog);
    case 7: return cmdcenter();
    case 6: return cmdbground();
    case 5: return cmdfground();
    case 4: return cmdframe();
    case 3: return cmdascii();
    case 2: return cmdtext();
    case 1: return cmdaddobj();
    default:
        return 0;
    }
}

int mousevent(void)
{
    TRECT rc;
    int  x,y,q;

    x = mousex();
    y = mousey();
    if (y == 24) {
        if (isVisible() && dialog.rc.y + dialog.rc.row >= y) {
        } else {
            for (q = 0; q < STLCOUNT; q++) {
                if (rcxyrow(st_line[q].rc, x, y)) {
                    mousewait(x, y, 1);
                    return st_line[q].key;
                }
            }
            mousewait(x, y, 1);
            return 0;
        }
    }
    if (isVisible() == 0)
        return 0;
    if (rcxyrow(dialog.rc, x, y) == 1) {
        dlmove(&dialog);
        fsaved_src = 0;
        return 0;
    }
    if (y == dialog.rc.y + dialog.rc.row - 1
        && x == dialog.rc.x + dialog.rc.col - 1) {
        cmdresize();
        return 0;
    }
    for (q = 0; q < dialog.count; q++) {
        rc = _rcaddrc(dialog.rc, object[q].rc);
        if (object[q].flags != TOBJ_DELETED) {
            if (rcxyrow(rc, x, y) == 1) {
                if (mousep() == 1)
                    cmdmoveobj(q);
                else
                    cmdeditobj(q);
                return 1;
            }
        }
    }
    if (mousep() == 2)
        cmdmenu();
    return 0;
}

#define CLEARSTATE  0x03FF

enum {  ID_LISTU,
        ID_LISTD = 11,
        ID_OPEND,
        ID_CANCEL,
        ID_OPENF,
        ID_MOUSEU,
        ID_MOUSED
};

#define OCOUNT  ID_OPEND

LOBJ list;

int open_initlist(void)
{
    int x;

    for (x = 0; x < OCOUNT; x++)
        tdialog->object[x].data = object[list.index + x].data;
    dlinit(tdialog);
    return 1;
}

int open_event_openfile(void)
{
    int x;
    char *p;
    TOBJ *o;

    list.index = 0;
    list.count = 0;
    list.dcount = OCOUNT;
    memset(objectname, 0, sizeof(objectname));

    if (IOInitFiles(filename_src) == 0 || fexist_src == 0)
        return lwarning("File not found");

    if (identifier[0] == 0) {
        strcpy(identifier, strfn(filename_src));
        if ((p = strrchr(identifier, '.')) != NULL)
            *p = 0;
    }
    strncpy(object[list.count++].data, identifier, 32);

    list.numcel = MIN(list.count, OCOUNT);
    o = tdialog->object;
    for (x = 0; x < list.numcel; x++)
        o[x].flags &= ~O_STATE;
    for (; x < OCOUNT; x++)
        o[x].flags |= O_STATE;
    open_initlist();
    if (list.count == 0)
        _stdmsg("No object", "There is no dialogs saved in\n%s", filename_src);
    return list.count;
}

int ll_eventopen(void)
{
    if (list.celoff >= list.dcount) {
        _stdmsg("TDialog", "No item selected\n");
        return _C_NORMAL;
    }
    return _C_RETURN;
}

DOBJ *open_initdlg(void)
{
    TOBJ *o;
    DOBJ *d;

    if ((d = rsopen(IDD_RCOpenFile)) == NULL)
        return NULL;
    list.numcel = 0;
    list.dcount = OCOUNT;
    list.celoff = OCOUNT;
    list.lproc  = open_initlist;
    o = d->object;
    o[ID_OPEND].tproc  = ll_eventopen;
    o[ID_OPENF].tproc  = open_event_openfile;
    o[ID_OPENF].data  = filename_src;
    o[ID_OPENF].count = (_MAX_PATH >> 4);
    return d;
}

int cmdopen(void)
{
    DOBJ *d;
    int result;
    char idd[128];

    cmdsave();
    closedlg();
    tclrascii = U_MIDDLE_DOT;
    rcputidd(filename_src);
    if ((d = open_initdlg()) == NULL)
        return 0;
    tdialog = d;
    result = open_event_openfile();
    if (result > 1)
        result = dllevent(d, &list);
    else if (result == 1)
        list.celoff = 0;
    dlclose(d);
    if (result == 0 || list.celoff >= OCOUNT)
        return 0;
    strncpy(idd, object[list.index + list.celoff].data, 128);
    dialogname[0] = 0;
    identifier[0] = 0;
    if (IOReadIDD(idd) == 0)
        return 0;
    dlshow(&dialog);
    rcputidd(identifier);
    return 1;
}


int cmuserscreen(void)
{
    dlhide(DLG_RCEDIT);
    tgetevent();
    dlshow(DLG_RCEDIT);
    return 1;
}

int rc_event(int event)
{
    int result;

    switch ( event ) {
    case KEY_F1: return cmdhelp();
    case KEY_F2: return cmdsave();
    case KEY_F3: return cmdopen();
    case KEY_F5: return cmdmenu();
    case KEY_F6: return cmdeditdlg();
    case KEY_F7: return cmdcolor();
    case (KEY_CTRL | KEY_F2):
        return cmdnewdlg();
    case (KEY_CTRL | 'B'):
    case (KEY_ALT | KEY_F5):
        return cmuserscreen();
    case KEY_ESC:
        return cmdexit();
    case ( KEY_ALT | 'x' ):
        endmain = 1;
        return event;
    }
    if (isVisible() == 0)
        return 0;
    if ( event == (KEY_CTRL | KEY_F8) )
        cmdmovetext();
    if (dialog.count == 0)
        return 0;

    switch (event) {
    case KEY_UP:
        if (dialog.index)
            dialog.index--;
        else if (dialog.count > 1)
            dialog.index = dialog.count - 1;
        break;
    case KEY_TAB:
    case KEY_DOWN:
        if (dialog.index == dialog.count - 1)
            dialog.index = 0;
        else if (dialog.count > 1)
            dialog.index++;
        break;
    case KEY_RETURN:
        cmdeditobj(dialog.index);
        break;
    case KEY_F8:
        cmdmoveobj(dialog.index);
        break;
    case KEY_F9:  cmdtext();    break;
    case KEY_F10: cmdcenter();  break;
    case KEY_F11: cmdfground(); break;
    case KEY_F12: cmdbground(); break;
    case (KEY_CTRL | KEY_F4):
        cmdascii();
        break;
    case (KEY_CTRL | KEY_F5):
        cmdframe();
        break;
    case (KEY_CTRL | KEY_F6):
        dlinit(&dialog);
        dlevent(&dialog);
        break;
    }
    return 0;
}

int modal(void)
{
    CURSOR cu;
    TRECT rc;
    int result;

    cu.type    = 32;
    cu.visible = 1;

    while (endmain == 0) {
        if (isVisible() && dialog.count) {
            rc = _rcaddrc(dialog.rc, object[dialog.index].rc);
            cu.x = rc.x;
            cu.y = rc.y;
            _setcursor(&cu);
        } else {
            _cursoroff();
        }
        result = tgetevent();
        if (result == MOUSECMD)
            result = mousevent();
        if (rc_event(result) == ( KEY_ALT | 'x' ) )
            break;
    }
    closedlg();
    return 0;
}

int rcedit(char *dname)
{
    int result;
    CURSOR cursor;
    CHAR_INFO ci;

    console |= ( CON_UTIME | CON_SLEEP );
    if (option_new == 1) {
        if (dname == NULL) {
            if ( _tgetline("Resource filename", filename_src, 30, 256) == 0)
                return 0;
        } else {
            strcpy(filename_src, dname);
        }
    }
    if (IOInitFiles(filename_src) == 0)
        return 0;

    _getcursor(&cursor);
    _cursoroff();

    if ((DLG_RCEDIT = rsopen(IDD_RCDesktop)) == NULL)
        return 0;
    dlshow(DLG_RCEDIT);
    rc_initscreen();
    _scpath(17, 0, 39, filename_src);
    _initupdate(rcupdate);
    if (option_new == 1) {
        cmdnewdlg();
    } else {
        if (isOpen() == 0) {
            if (cmdopen() == 0)
                closedlg();
        } else if (isVisible() == 0) {
            dlshow(&dialog);
        }
    }
    result = modal();
    dlclose(DLG_RCEDIT);
    _setcursor(&cursor);
    DLG_RCEDIT = NULL;
    return (result != 0);
}

void print_copyright(void)
{
    printf("Binary Resource Edit Version %d.%d.%d.%d\n",
        __IDDE__ / 100, __IDDE__ % 100,
        __LIBC__ / 100, __LIBC__ % 100 );
}

int main(int argc, char *argv[])
{
    filename_src[0] = 0;

    if ( argc == 2 ) {

        if ( argv[1][0] == '?' || argv[1][0] == '-' || argv[1][0] == '/' ) {

            print_copyright();
            printf("Usage: IDDE [source]\n");
            return 0;
        }
        strcpy(filename_src, argv[1]);
    }
    print_copyright();
    dialog_default();

    if (filename_src[0]) {
        if (IOInitSourceFile(filename_src) == 0)
            return 1;
        return rcedit(filename_src);
    }
    option_new = 1;
    return rcedit("NewDialog");
}
