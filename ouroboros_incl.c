/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



/*
 * file        : ouroboros_incl.c
 * subject     : process files with ansi-c include directives
 *
 *
 *
 */



struct {
   char        c_cat;
   char        c_name      [LEN_LABEL];
   char        c_desc      [LEN_HUND];
} static s_cats [LEN_LABEL] = {
   { 'u', "unit"           , "unit testing tools required"                       , '-' },
   { 's', "solo"           , "only requires header file for defines, etc"         },
   { 'a', "ansi"           , "original ansi c standard"                           },
   { 'p', "posix"          , "posix-system standard (mayber harder to port)"      },
   { 'c', "core"           , "heatherly core library (used almost everywhere)"    },
   { 'v', "vikeys"         , "heatherly vi-keys user-interface framework"         },
   { 'g', "graph"          , "grahics environment specific (opengl, curses, ...)" },
   { 'o', "other"          , "heatherly non-core, vikeys, or graphics related"    },
   { '!', "alien"          , "non-standard and non-heatherly external library"    },
   { 'I', "inpt"           , "files required for input or configuration"          },
   { 'O', "outp"           , "output written to reports or other temp"            },
   { 'F', "file"           , "primary databases"                                  },
   { '?', "wtf"            , "uncategorized dependency"                           },
   {  0 , "end"            , "end"                                                },
};
static s_ncat    = 0;


tINCL g_incls [MAX_INCL] = {
   /*---(ansi c)-------------------- cnt  ogl  cur  drw  blk  zen  */
   /* original c standard */
   { 'a', "assert"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "ctype"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "errno"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "float"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "limits"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "locale"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "malloc"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "math"                     , 0, '-', '-', '-', '-', '-' },
   { 'a', "memory"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "setjmp"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "signal"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdarg"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "stddef"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdio"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdlib"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "string"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "time"                     , 0, '-', '-', '-', '-', '-' },
   /*---(ansi c updates)------------ cnt  ogl  cur  drw  blk  zen  */
   /* c99, c23, ... , 0*/
   { 'a', "complex"                  , 0, '-', '-', '-', '-', '-' },
   { 'a', "err"                      , 0, '-', '-', '-', '-', '-' },
   { 'a', "error"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "fenv"                     , 0, '-', '-', '-', '-', '-' },
   { 'a', "inttypes"                 , 0, '-', '-', '-', '-', '-' },
   { 'a', "iso646"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdalign"                 , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdatomic"                , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdbit"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdbool"                  , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdchkdint"               , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdint"                   , 0, '-', '-', '-', '-', '-' },
   { 'a', "stdnoreturn"              , 0, '-', '-', '-', '-', '-' },
   { 'a', "tmath"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "threads"                  , 0, '-', '-', '-', '-', '-' },
   { 'a', "uchar"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "wchar"                    , 0, '-', '-', '-', '-', '-' },
   { 'a', "wctype"                   , 0, '-', '-', '-', '-', '-' },
   /*---(posix c standard)---------- cnt  ogl  cur  drw  blk  zen  */
   /* wider POXIX related libraries (maybe harder to port) , 0*/
   { 'p', "aio"                      , 0, '-', '-', '-', '-', '-' },
   { 'p', "arpa/inet"                , 0, '-', '-', '-', '-', '-' },
   { 'p', "cpio"                     , 0, '-', '-', '-', '-', '-' },
   { 'p', "dirent"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "dlfcn"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "fcntl"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "fmtmsg"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "fnctrl"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "fnmatch"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "ftw"                      , 0, '-', '-', '-', '-', '-' },
   { 'p', "glob"                     , 0, '-', '-', '-', '-', '-' },
   { 'p', "grp"                      , 0, '-', '-', '-', '-', '-' },
   { 'p', "iconv"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "langinfo"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "libgen"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "linux/fs"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "linux/hdreg"              , 0, '-', '-', '-', '-', '-' },
   { 'p', "monetary"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "mqueue"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "ndbm"                     , 0, '-', '-', '-', '-', '-' },
   { 'p', "net/if"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "netdb"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "netinet/in"               , 0, '-', '-', '-', '-', '-' },
   { 'p', "netinet/tcp"              , 0, '-', '-', '-', '-', '-' },
   { 'p', "nl_types"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "poll"                     , 0, '-', '-', '-', '-', '-' },
   { 'p', "pthread"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "pwd"                      , 0, '-', '-', '-', '-', '-' },
   { 'p', "regex"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "sched"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "search"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "semaphore"                , 0, '-', '-', '-', '-', '-' },
   { 'p', "shadow"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "spawn"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "strings"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "stropts"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/ioctl"                , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/ipc"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/mman"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/mount"                , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/reboot"               , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/resource"             , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/select"               , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/sem"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/shm"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/socket"               , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/stat"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/stavfs"               , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/sysmacros"            , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/time"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/times"                , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/types"                , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/uio"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/un"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/utsname"              , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/wait"                 , 0, '-', '-', '-', '-', '-' },
   { 'p', "syslog"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "termios"                  , 0, '-', '-', '-', '-', '-' },
   { 'p', "tgmath"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "trace"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "unistd"                   , 0, '-', '-', '-', '-', '-' },
   { 'p', "sys/unistd"               , 0, '-', '-', '-', '-', '-' },
   { 'p', "utime"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "utmp"                     , 0, '-', '-', '-', '-', '-' },
   { 'p', "utmpx"                    , 0, '-', '-', '-', '-', '-' },
   { 'p', "wordexp"                  , 0, '-', '-', '-', '-', '-' },

   /*---(heatherly core)------------ cnt  ogl  cur  drw  blk  zen  */
   /* core, nearly every program uses these libraries */
   { 'c', "zenodotus"                , 0, '-', '-', 'v', 'é', '-' },
   { 'c', "yLOG"                     , 0, 'y', 'y', 'y', 'é', '-' },
   { 'c', "yURG"                     , 0, 'y', 'y', 'y', 'é', '-' },
   { 'c', "yVAR"                     , 0, '-', '-', 'y', 'é', '-' },
   { 'c', "ySTR"                     , 0, 'y', 'y', 'y', 'é', '-' },
   { 'c', "yENV"                     , 0, '-', '-', 'y', 'é', '-' },

   /*---(heatherly vikeys)---------- cnt  ogl  cur  drw  blk  zen  */
   /* vikeys components supporting full vi-keys environment */
   { 'v', "yVIHUB"                   , 0, '-', '-', 'y', 'ê', '-' },
   { 'v', "yMODE"                    , 0, 'y', 'y', 'y', 'ê', '-' },
   { 'v', "yKEYS"                    , 0, 'y', 'y', 'y', 'ê', '-' },
   { 'v', "yFILE"                    , 0, 'y', 'y', 'y', 'ê', '-' },
   { 'v', "yVIEW"                    , 0, 'y', 'y', 'y', 'ê', '-' },

   { 'v', "yMAP"                     , 0, 'y', 'y', 'y', 'ê', '-' },
   { 'v', "yCMD"                     , 0, 'y', 'y', 'y', 'ê', '-' },
   { 'v', "yMACRO"                   , 0, 'y', 'y', 'y', 'ê', '-' },
   { 'v', "ySRC"                     , 0, 'y', 'y', 'y', 'ê', '-' },
   { 'v', "yMARK"                    , 0, 'y', 'y', 'y', 'ê', '-' },

   { 'v', "yGOD"                     , 0, '-', '-', 'y', '-', '-' },

   /*---(heatherly vikeys)---------- cnt  ogl  cur  drw  blk  zen  */
   /* graphics specific libraries */
   /* -    -------------------------  */
   { 'g', "ncurses"                  , 0, '-', 'y', '-', '-', '-' },
   { 'g', "tinfo"                    , 0, '-', 'y', '-', '-', '-' },
   { 'g', "X11"                      , 0, '-', '-', '-', '-', '-' },
   { 'g', "X11/X"                    , 0, 'y', '-', '-', '-', '-' },
   { 'g', "X11/Xlib"                 , 0, 'y', '-', '-', '-', '-' },
   { 'g', "X11/extensions/shape"     , 0, '-', '-', '-', '-', '-' },
   { 'g', "X11/Xutil"                , 0, '-', '-', '-', '-', '-' },
   { 'g', "X11/keysym"               , 0, '-', '-', '-', '-', '-' },
   { 'g', "X11/Xatom"                , 0, '-', '-', '-', '-', '-' },
   { 'g', "GL"                       , 0, '-', '-', '-', '-', '-' },
   { 'g', "GL/gl"                    , 0, 'y', '-', '-', '-', '-' },
   { 'g', "GL/glx"                   , 0, 'y', '-', '-', '-', '-' },
   { 'g', "GL/glu"                   , 0, '-', '-', '-', '-', '-' },
   { 'g', "yX11"                     , 0, 'y', '-', 'y', 'ë', '-' },
   { 'g', "yGLTEX"                   , 0, 'y', '-', 'y', 'ë', '-' },
   { 'g', "yCOLOR"                   , 0, 'y', '-', 'y', 'ë', '-' },
   { 'g', "yFONT"                    , 0, 'y', '-', 'y', 'ë', '-' },
   { 'g', "yVIOPENGL"                , 0, 'y', '-', 'y', '-', '-' },
   { 'g', "yVICURSES"                , 0, '-', 'y', 'y', '-', '-' },

   /*---(heatherly other)----------- cnt  ogl  cur  drw  blk  zen  */
   /* mine, but not core, vikey, or graphics libraries */
   { 'o', "yDLST"                    , 0, '-', '-', 'y', 'ì', '-' },
   { 'o', "ySORT"                    , 0, '-', '-', 'y', 'ì', '-' },
   { 'o', "yPARSE"                   , 0, '-', '-', 'y', 'ì', '-' },
   { 'o', "yJOBS"                    , 0, '-', '-', 'y', 'ì', '-' },
   { 'o', "yEXEC"                    , 0, '-', '-', 'y', 'ì', '-' },
   { 'o', "yREGEX"                   , 0, '-', '-', 'y', 'ì', '-' },
   { 'o', "ySCHED"                   , 0, '-', '-', 'y', 'ì', '-' },

   { 'o', "yRPN"                     , 0, '-', '-', 'y', 'ó', '-' },
   { 'o', "yCALC"                    , 0, '-', '-', 'y', 'ó', '-' },

   { 'o', "ySEC"                     , 0, '-', '-', 'y', '-', '-' },
   { 'o', "yASCII"                   , 0, '-', '-', 'y', '-', '-' },
   { 'o', "ySHELL"                   , 0, '-', '-', 'y', '-', '-' },
   { 'o', "yHUBLIN"                  , 0, '-', '-', 'y', '-', '-' },
   { 'o', "yGOLEM"                   , 0, '-', '-', 'y', '-', '-' },
   { 'o', "yKINE"                    , 0, '-', '-', 'y', '-', '-' },

   /*---(heatherly solo)------------ cnt  ogl  cur  drw  blk  zen  */
   /* just taking in for definitions in header file */
   { 's', "yLOG_solo"                , 0, '-', '-', '-', '-', '-' },
   { 's', "yLOG_uver"                , 0, '-', '-', 'y', 'é', 'y' },
   { 's', "yURG_solo"                , 0, '-', '-', '-', '-', '-' },
   { 's', "yURG_uver"                , 0, '-', '-', 'y', 'é', 'y' },
   { 's', "ySTR_solo"                , 0, '-', '-', 'y', 'é', 'y' },
   { 's', "ySTR_uver"                , 0, '-', '-', 'y', 'é', 'y' },
   { 's', "yENV_solo"                , 0, '-', '-', '-', '-', '-' },
   { 's', "yENV_uver"                , 0, '-', '-', 'y', 'é', 'y' },
   { 's', "yDLST_solo"               , 0, '-', '-', 'y', 'é', 'y' },
   { 's', "yCOLOR_solo"              , 0, '-', '-', 'y', 'é', 'y' },
   { 's', "yVIHUB_solo"              , 0, 'y', 'y', 'y', 'ê', 'y' },

   /*---(heatherly unit testin------ cnt  ogl  cur  drw  blk  zen  */
   { 'u', "yUNIT_solo"               , 0, '-', '-', 'y', '-', 'y' },
   { 'u', "yUNIT"                    , 0, '-', '-', 'y', '-', '-' },
   { 'u', "koios"                    , 0, '-', '-', 'v', '-', '-' },

   /*---(heatherly DEPRECATED)------ cnt  ogl  cur  drw  blk  zen  */
   /* just taking in for definitions in header file */
   { 'X', "yVIKEYS"                  , 0, '-', '-', '-', '-', '-' },
   { 'X', "yXINIT"                   , 0, '-', '-', '-', '-', '-' },

   /*---(alien)--------------------- cnt  ogl  cur  drw  blk  zen  */
   /* just taking in for definitions in header file */
   { '!', "png"                      , 0, '-', '-', '-', '-', '-' },
   { '!', "jpeglib"                  , 0, '-', '-', '-', '-', '-' },
   { '!', "openssl/sha"              , 0, '-', '-', '-', '-', '-' },
   { '!', "ft2build"                 , 0, '-', '-', '-', '-', '-' },

   /*---(end)----------------------- cnt  ogl  cur  drw  blk  zen  */
   {  0 , "end-of-list"              , 0, '-', '-', '-' },
};
static int  s_nincl   = 0;
static int  s_nseen   = 0;
static int  s_handled = 0;
static int  s_nextra  = 0;
static int  s_ndrawn  = 0;



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
INCL_purge              (void)
{
   int         i           =    0;
   s_nincl   = 0;
   s_nseen   = 0;
   s_handled = 0;
   s_nextra  = 0;
   s_ndrawn  = 0;
   for (i = 0; i < MAX_INCL; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      g_incls [i].i_count = 0;
      ++s_nincl;
   }
   INCL_clear ();
   return 0;
}

char INCL_init               (void) { return INCL_purge (); }
char INCL_wrap               (void) { return INCL_purge (); }

char
INCL_zenodotus          (void)
{
   int         i           =    0;
   int         n           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_value   ("s_nincl"   , s_nincl);
   for (i = 0; i < s_nincl; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      DEBUG_PROG   yLOG_complex ("looking"   , "%3d %-20.20s %c", i, g_incls [i].i_name, g_incls [i].i_zenodotus);
      if (g_incls [i].i_zenodotus != 'y')  continue;
      DEPS_force ("zenodotus", g_incls [i].i_name);
   }
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      link detail                             ----===*/
/*====================------------------------------------====================*/
static void  o___DETAIL__________o () { return; }

char
INCL_clear              (void)
{
   strcpy (my.depsolo , "´");
   strcpy (my.depunit , "´");
   strcpy (my.depansi , "´");
   strcpy (my.depposix, "´");
   strcpy (my.depcore , "´");
   strcpy (my.depvikey, "´");
   strcpy (my.depgraph, "´");
   strcpy (my.depother, "´");
   strcpy (my.depalien, "´");
   strcpy (my.depinpt , "´");
   strcpy (my.depoutp , "´");
   strcpy (my.depfile , "´");
   strcpy (my.depwtf  , "´");
   strcpy (my.depall  , "´");
   return 0;
}

char
INCL_add                (int n, char a_cat, char a_header [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_cat       =  '-';
   char        x_header    [LEN_TITLE] = "";
   char       *x_list      = NULL;
   char        t           [LEN_HUND]  = "";
   char        x_show      =  '-';
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(handle direct)------------------*/
   DEBUG_DATA   yLOG_value   ("n"         , n);
   --rce;  if (n < 0 || n >= s_nincl) {
      DEBUG_PROG   yLOG_note    ("direct request (no index)");
      DEBUG_PROG   yLOG_point   ("a_header"  , a_header);
      --rce;  if (a_header     == NULL) {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_PROG   yLOG_info    ("a_header"  , a_header);
      --rce;  if (a_header [0] == '\0') {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      n = INCL_by_name (a_header);
      x_cat = a_cat;
      ystrlcpy (x_header, a_header, LEN_TITLE);
   }
   /*---(handle indexed)-----------------*/
   else {
      DEBUG_PROG   yLOG_note    ("indexed request");
      x_cat = g_incls [n].i_cat;
      ystrlcpy (x_header, g_incls [n].i_name, LEN_TITLE);
   }
   DEBUG_PROG   yLOG_info    ("x_header"  , x_header);
   /*---(pick list)----------------------*/
   DEBUG_PROG   yLOG_char    ("x_cat"     , x_cat);
   /*---(standards)------------*/
   --rce;  switch (x_cat) {
   case DEPSOLO  :  x_list = my.depsolo;    break;
   case DEPUNIT  :  x_list = my.depunit;    break;
   case DEPANSI  :  x_list = my.depansi;    break;
   case DEPPOSIX :  x_list = my.depposix;   break;
   case DEPCORE  :  x_list = my.depcore;    break;
   case DEPVIKEY :  x_list = my.depvikey;   break;
   case DEPGRAPH :  x_list = my.depgraph;   break;
   case DEPOTHER :  x_list = my.depother;   break;
   case DEPALIEN :  x_list = my.depalien;   break;
   }
   /*---(extended)-------------*/
   switch (x_cat) {
   case DEPINPT  :  x_list = my.depinpt;  ++s_nextra;  break;
   case DEPOUTP  :  x_list = my.depoutp;  ++s_nextra;  break;
   case DEPFILE  :  x_list = my.depfile;  ++s_nextra;  break;
   case DEPWTF   :  x_list = my.depwtf;   ++s_nextra;  break;
   }
   /*---(missing)--------------*/
   --rce;  if (x_list == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(increment handled/seen)---------*/
   DEBUG_PROG   yLOG_info    ("x_list"    , x_list);
   ++s_nseen;
   /*---(prepare)------------------------*/
   sprintf (t, ",%s,", x_header);
   DEBUG_PROG   yLOG_info    ("t"         , t);
   /*---(check individual)---------------*/
   --rce;  if (strstr (x_list, t) != NULL) {
      DEBUG_PROG   yLOG_note    ("already in specific list");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 2;
   }
   ++s_handled;
   /*---(increment count)----------------*/
   if (n >= 0 && n <= s_nincl) {
      ++(g_incls [n].i_count);
      DEBUG_PROG   yLOG_value   ("i_count"   , g_incls [n].i_count);
   }
   if (x_list [0]    == '´')  ystrlcpy (x_list   , ",", LEN_FULL);
   ystrlcat (x_list, t + 1, LEN_FULL);
   /*---(add to all)---------------------*/
   DEBUG_PROG   yLOG_info    ("depall"    , my.depall);
   --rce;  if (strstr (my.depall, t) != NULL) {
      DEBUG_PROG   yLOG_note    ("already in ALL list");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 3;
   }
   if (my.depall [0] == '´')  ystrlcpy (my.depall, ",", LEN_RECD);
   switch (x_cat) {
   case 'I' : ystrlcat (my.depall, "×", LEN_RECD);   break;
   case 'O' : ystrlcat (my.depall, "Ö", LEN_RECD);   break;
   case 'F' : ystrlcat (my.depall, "Ï", LEN_RECD);   break;
   }
   ystrlcat (my.depall, t + 1, LEN_RECD);
   /*---(create node)--------------------*/
   x_show = g_incls [n].i_draw;
   DEBUG_PROG   yLOG_char    ("x_show"    , x_show);
   if (x_show != 0 && strchr ("yv", x_show) != NULL) {
      DEBUG_PROG   yLOG_note    ("return request to show/draw header");
      ++s_ndrawn;
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return x_show;
   }
   DEBUG_PROG   yLOG_note    ("leave header invisible");
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
INCL_add_by_group       (char a_project [LEN_LABEL], char a_group)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_value   ("a_group"   , a_group);
   --rce;  if (a_group     == 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_char    ("a_group"   , a_group);
   --rce;  if (strchr ("OC", a_group) == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < MAX_INCL; ++i) {
      DEBUG_DATA   yLOG_complex ("loop"      , "%3d, %c, %-30.30s, %c, %c", i, g_incls [i].i_cat, g_incls [i].i_name, g_incls [i].i_opengl, g_incls [i].i_curses);
      if (g_incls [i].i_cat == 0)   break;
      switch (a_group) {
      case 'O' :
         if (g_incls [i].i_opengl == 'y')  DEPS_force (g_incls [i].i_name, a_project);
         break;
      case 'C' :
         if (g_incls [i].i_curses == 'y')  DEPS_force (g_incls [i].i_name, a_project);
         break;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     inclusion finding                        ----===*/
/*====================------------------------------------====================*/
static void  o___FIND____________o () { return; }

int
INCL_by_name            (char a_header [LEN_TITLE])
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_header == NULL)       return rce;
   --rce;  if (a_header [0] == '\0')   return rce;
   for (i = 0; i < MAX_INCL; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      if (strcmp (g_incls [i].i_name, a_header) != 0)  continue;
      return i;
   }
   return rce;
}

char
INCL_data               (int n, char *r_cat, char r_name [LEN_TITLE], int *r_count, char *r_opengl, char *r_curses, char *r_draw, char *r_block, char *r_zeno)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_cat    != NULL)  *r_cat     = '-';
   if (r_name   != NULL)  ystrlcpy (r_name    , "", LEN_TITLE);
   if (r_count  != NULL)  *r_count   =   0;
   if (r_opengl != NULL)  *r_opengl  = '-';
   if (r_curses != NULL)  *r_curses  = '-';
   if (r_draw   != NULL)  *r_draw    = '-';
   if (r_block  != NULL)  *r_block   = '-';
   if (r_zeno   != NULL)  *r_zeno    = '-';
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_value   ("n"         , n);
   --rce;  if (n < 0 || n >= s_nincl) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_cat    != NULL)  *r_cat     = g_incls [n].i_cat;
   if (r_name   != NULL)  ystrlcpy (r_name    , g_incls [n].i_name, LEN_TITLE);
   if (r_count  != NULL)  *r_count   = g_incls [n].i_count;
   if (r_opengl != NULL)  *r_opengl  = g_incls [n].i_opengl;
   if (r_curses != NULL)  *r_curses  = g_incls [n].i_curses;
   if (r_draw   != NULL)  *r_draw    = g_incls [n].i_draw;
   if (r_block  != NULL)  *r_block   = g_incls [n].i_block;
   if (r_zeno   != NULL)  *r_zeno    = g_incls [n].i_zenodotus;
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      wild gathering                          ----===*/
/*====================------------------------------------====================*/
static void  o___GATHER__________o () { return; }

char
INCL_gather_detail      (char a_project [LEN_LABEL], char a_entry [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_TITLE] = "";
   char        s           [LEN_SHORT] = "";
   int         l           =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_entry"   , a_entry);
   --rce; if (a_entry == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_entry"   , a_entry);
   /*---(filter)-------------------------*/
   strcpy (t, a_entry);
   l = strlen (t);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (s, t + l - 2);
   DEBUG_DATA   yLOG_info    ("s"         , s);
   --rce;  if (strcmp (s, ".h") != 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   t [l - 2] = '\0';
   /*---(special)------------------------*/
   --rce; if (strcmp (t, "make_opengl") == 0) {
      DEBUG_DATA   yLOG_note    ("found meta-opengl header");
      INCL_add_by_group (a_project, 'O');
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 2;
   } else if (strcmp (t, "make_curses") == 0) {
      DEBUG_DATA   yLOG_note    ("found meta-curses header");
      INCL_add_by_group (a_project, 'C');
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(filter)-------------------------*/
   if (strcmp (t, "yVIHUB_solo") == 0) {
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(add to list)--------------------*/
   rc = DEPS_force (t, a_project);
   if (n < 0) {
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
INCL_gather             (char a_project [LEN_LABEL], char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           =    0;
   char        x_delimit   =  '>';
   char       *q           =  " ";
   char        l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_recd"    , a_recd);
   --rce; if (a_recd == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_recd"    , a_recd);
   /*---(work out delimiters)---------*/
   p = strchr (a_recd, '<');
   if (p != NULL) {
      x_delimit = '>';
   } else  {
      p = strchr (a_recd, '"');
      x_delimit = '"';
   }
   DEBUG_DATA   yLOG_point   ("p"         , p);
   DEBUG_DATA   yLOG_char    ("x_delimit" , x_delimit);
   /*---(handle)----------------------*/
   if (p != NULL) {
      p [0] = '\0';
      ++p;
      DEBUG_DATA   yLOG_info    ("p"         , p);
      q = strchr (p, x_delimit);
      DEBUG_DATA   yLOG_point   ("q"         , q);
      if (q != NULL) {
         q [0] = '\0';
         l = strlen (p);
         DEBUG_DATA   yLOG_info    ("p"         , p);
         if (x_delimit == '"') {
            DEBUG_DATA   yLOG_info    ("strcmp"    , p + l - 7);
            if      (strcmp (p + l - 7, "_solo.h") == 0)  rc = INCL_gather_detail (a_project, p);
            else if (strcmp (p + l - 7, "_uver.h") == 0)  rc = INCL_gather_detail (a_project, p);
            else {
               DEBUG_DATA  yLOG_note    ("ignore local headers except _solo and _uver");
               DEBUG_DATA  yLOG_exit    (__FUNCTION__);
               return 0;
            }
         } else {
            rc = INCL_gather_detail (a_project, p);
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       output/repurting                       ----===*/
/*====================------------------------------------====================*/
static void  o___REPORT__________o () { return; }

char
INCL_list               (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_INCL; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      if (g_incls [i].i_count == 0) {
         printf ("%3d  %c  %-25.25s  ···\n", i, g_incls [i].i_cat, g_incls [i].i_name);
      } else {
         printf ("%3d  %c  %-25.25s  %3d\n", i, g_incls [i].i_cat, g_incls [i].i_name, g_incls [i].i_count);
      }
   }
   return 0;
}

char
INCL_finalize           (char a_proj [LEN_LABEL], char a_full [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =    0;
   char        rc          =    0;
   int         l           =    0;
   char        x_full      [LEN_PATH]  = "";
   FILE       *f           = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_proj"    , a_proj);
   --rce; if (a_proj == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_proj"    , a_proj);
   DEBUG_DATA   yLOG_point   ("a_full"    , a_full);
   --rce; if (a_full == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_full"    , a_full);
   /*---(add to project)-----------------*/
   /*> if (my.depall [0] == '\0')  strcpy (my.depall, "´");                           <* 
    *> rc = GRAPH_deps_add  (a_proj, my.depall);                                      <* 
    *> DEBUG_DATA   yLOG_value   ("deps_add"  , rc);                                  <* 
    *> --rce; if (rc < 0) {                                                           <* 
    *>    DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(open file)----------------------*/
   l = strlen (a_full);
   if (a_full [l - 1] == '/') sprintf (x_full, "%s%s" , a_full, "ouroboros.deps");
   else                       sprintf (x_full, "%s/%s", a_full, "ouroboros.deps");
   DEBUG_DATA   yLOG_info    ("x_full"    , x_full);
   f = fopen (x_full, "wt");
   DEBUG_DATA   yLOG_point   ("f"         , f);
   --rce; if (f == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(write file)---------------------*/
   fprintf (f, "#define     P_DEPSOLO   \"%s\"\n", my.depsolo );
   fprintf (f, "#define     P_DEPUNIT   \"%s\"\n", my.depunit );
   fprintf (f, "#define     P_DEPANSI   \"%s\"\n", my.depansi );
   fprintf (f, "#define     P_DEPPOSIX  \"%s\"\n", my.depposix);
   fprintf (f, "#define     P_DEPCORE   \"%s\"\n", my.depcore );
   fprintf (f, "#define     P_DEPVIKEY  \"%s\"\n", my.depvikey);
   fprintf (f, "#define     P_DEPGRAPH  \"%s\"\n", my.depgraph);
   fprintf (f, "#define     P_DEPOTHER  \"%s\"\n", my.depother);
   fprintf (f, "#define     P_DEPALIEN  \"%s\"\n", my.depalien);
   fprintf (f, "#define     P_DEPINPT   \"%s\"\n", my.depinpt );
   fprintf (f, "#define     P_DEPOUTP   \"%s\"\n", my.depoutp );
   fprintf (f, "#define     P_DEPFILE   \"%s\"\n", my.depfile );
   fprintf (f, "#define     P_DEPWTF    \"%s\"\n", my.depwtf  );
   fprintf (f, "#define     P_DEPALL    \"%s\"\n", my.depall  );
   /*---(close file)---------------------*/
   rc = fclose (f);
   DEBUG_DATA   yLOG_value   ("fclose"    , rc);
   --rce; if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
INCL_block              (char a_proj [LEN_TITLE])
{
   char        rce         =    0;
   int         x_len       =    0;
   char        n           =   -1;
   /*---(defense)------------------------*/
   --rce;  if (a_proj == NULL)             return rce;
   /*> if (strstr (a_proj, "_solo") != NULL) {                                        <* 
    *> }                                                                              <*/
   /*> if (strcmp (a_proj, "yUNIT") == 0) {                                           <* 
    *>    GRAPH_add_node  ("yENV_solo");                                              <* 
    *> }                                                                              <*/
   /*---(show result)--------------------*/
   /*> printf ("PROJECT     : å%sæ\n", a_proj);                                       <* 
    *> printf ("  depsolo   : %4då%sæ\n", strlen (my.depsolo ), my.depsolo );         <* 
    *> printf ("  depunit   : %4då%sæ\n", strlen (my.depunit ), my.depunit );         <* 
    *> printf ("  depansi   : %4då%sæ\n", strlen (my.depansi ), my.depansi );         <* 
    *> printf ("  depposix  : %4då%sæ\n", strlen (my.depposix), my.depposix);         <* 
    *> printf ("  depcore   : %4då%sæ\n", strlen (my.depcore ), my.depcore );         <* 
    *> printf ("  depvikey  : %4då%sæ\n", strlen (my.depvikey), my.depvikey);         <* 
    *> printf ("  depgraph  : %4då%sæ\n", strlen (my.depgraph), my.depgraph);         <* 
    *> printf ("  depother  : %4då%sæ\n", strlen (my.depother), my.depother);         <* 
    *> printf ("  depalien  : %4då%sæ\n", strlen (my.depalien), my.depalien);         <* 
    *> printf ("  depinpt   : %4då%sæ\n", strlen (my.depinpt ), my.depinpt );         <* 
    *> printf ("  depoutp   : %4då%sæ\n", strlen (my.depoutp ), my.depoutp );         <* 
    *> printf ("  depfile   : %4då%sæ\n", strlen (my.depfile ), my.depfile );         <* 
    *> printf ("  depwtf    : %4då%sæ\n", strlen (my.depwtf  ), my.depwtf  );         <* 
    *> printf ("  depall    : %4då%sæ\n", strlen (my.depall  ), my.depall  );         <*/
   /*---(show filen entry)---------------*/
   if (my.depall [0] == '´')  strcpy (my.depall, "");
   x_len = strlen (my.depall);
   /*> if (my.depall [x_len - 1] == ',')  my.depall [--x_len] = '\0';                 <*/
   if (x_len == 0)     printf ("  DEPS    %-20.20s  ´ \n" , a_proj);
   else                printf ("  DEPS    %-20.20s  %s \n", a_proj, my.depall);
   /*---(add to node)--------------------*/
   /*> GRAPH_deps_add  (a_proj, my.depall);                                           <*/
   /*
    *  call DEPS_merge on all previous nodes
    *  call DEPS_missing  (these are the only drawn lines on box diagram)
    *  call DEPS_merge on current node also
    */
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*            /*--> unit test accessor ------------------------------*/
INCL__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         i           =    0;
   int         x_count     =    0;
   int         x_total     =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (my.unit_answer, "INCL             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if (strcmp (a_question, "count"         )  == 0) {
      for (i = 0; i < MAX_INCL; ++i) {
         if (g_incls [i].i_cat   == 0)   break;
         if (g_incls [i].i_count <= 0)   continue;
         ++x_count;
         x_total += g_incls [i].i_count;
      }
      snprintf (my.unit_answer, LEN_RECD, "INCL count       : %4d list   , %4d seen   , %4d handled, %4d unique , %4d total  , %4d extra  , %4d drawn", s_nincl, s_nseen, s_handled, x_count, x_total, s_nextra, s_ndrawn);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



