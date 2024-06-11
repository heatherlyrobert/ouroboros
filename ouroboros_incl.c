/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



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
   /*---(ansi c)-------------------------*/
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
   /*---(ansi c updates)-----------------, 0*/
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
   /*---(posix c standard)---------------, 0*/
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

   /*---(heatherly core)-----------------*/
   /* core, nearly every program uses these libraries */
   { 'c', "zenodotus"                , 0, '-', '-', 'v', 'é', '-' },
   { 'c', "yLOG"                     , 0, 'y', 'y', 'y', 'é', '-' },
   { 'c', "yURG"                     , 0, 'y', 'y', 'y', 'é', '-' },
   { 'c', "yVAR"                     , 0, '-', '-', 'y', 'é', '-' },
   { 'c', "ySTR"                     , 0, 'y', 'y', 'y', 'é', '-' },
   { 'c', "yENV"                     , 0, '-', '-', 'y', 'é', '-' },

   /*---(heatherly vikeys)---------------*/
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

   /*---(heatherly vikeys)---------------*/
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

   /*---(heatherly other)----------------*/
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

   /*---(heatherly solo)-----------------*/
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
   { 's', "yVIHUB_solo"              , 0, 'y', 'y', '-', '-', '-' },

   /*---(heatherly unit testing)---------*/
   { 'u', "yUNIT_solo"               , 0, '-', '-', 'y', '-', 'y' },
   { 'u', "yUNIT"                    , 0, '-', '-', 'y', '-', '-' },
   { 'u', "koios"                    , 0, '-', '-', 'v', '-', '-' },

   /*---(heatherly DEPRECATED)-----------*/
   /* just taking in for definitions in header file */
   { 'X', "yVIKEYS"                  , 0, '-', '-', '-', '-', '-' },
   { 'X', "yXINIT"                   , 0, '-', '-', '-', '-', '-' },

   /*---(alien)--------------------------*/
   /* just taking in for definitions in header file */
   { '!', "png"                      , 0, '-', '-', '-', '-', '-' },
   { '!', "jpeglib"                  , 0, '-', '-', '-', '-', '-' },
   { '!', "openssl/sha"              , 0, '-', '-', '-', '-', '-' },
   { '!', "ft2build"                 , 0, '-', '-', '-', '-', '-' },

   /*---(end)----------------------------*/
   {  0 , "end-of-list"              , 0, '-', '-', '-' },
};
int  g_nincl   = 0;
int  g_handled = 0;



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
INCL_clear              (void)
{
   int         i           =    0;
   g_nincl   = 0;
   g_handled = 0;
   for (i = 0; i < MAX_INCL; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      g_incls [i].i_count = 0;
      ++g_nincl;
   }
   INCL_list_clear ();
   return 0;
}

char
INCL_zenodotus          (void)
{
   int         i           =    0;
   int         n           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_value   ("g_nincl"   , g_nincl);
   for (i = 0; i < g_nincl; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      DEBUG_PROG   yLOG_complex ("looking"   , "%3d %-20.20s %c", i, g_incls [i].i_name, g_incls [i].i_zenodotus);
      if (g_incls [i].i_zenodotus != 'y')  continue;
      /*> n = GRAPH_by_name (g_incls [i].i_name);                                     <* 
       *> DEBUG_PROG   yLOG_value   ("n"         , n);                                <* 
       *> INCL_add_by_name ("zenodotus", n);                                          <*/
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
INCL_list_clear         (void)
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
INCL_list_add           (char a_cat, char a_header [LEN_TITLE])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_list      = NULL;
   char        t           [LEN_HUND]  = "";

   return 1;

   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
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
   /*---(pick list)----------------------*/
   DEBUG_PROG   yLOG_char    ("a_cat"     , a_cat);
   --rce;  switch (a_cat) {
   case DEPSOLO  :  x_list = my.depsolo;    break;
   case DEPUNIT  :  x_list = my.depunit;    break;
   case DEPANSI  :  x_list = my.depansi;    break;
   case DEPPOSIX :  x_list = my.depposix;   break;
   case DEPCORE  :  x_list = my.depcore;    break;
   case DEPVIKEY :  x_list = my.depvikey;   break;
   case DEPGRAPH :  x_list = my.depgraph;   break;
   case DEPOTHER :  x_list = my.depother;   break;
   case DEPALIEN :  x_list = my.depalien;   break;
   case DEPINPT  :  x_list = my.depinpt;    break;
   case DEPOUTP  :  x_list = my.depoutp;    break;
   case DEPFILE  :  x_list = my.depfile;    break;
   case DEPWTF   :  x_list = my.depwtf;     break;
   default       :
                    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
                    return rce;
   }
   DEBUG_PROG   yLOG_info    ("x_list"    , x_list);
   /*---(prepare)------------------------*/
   sprintf (t, ",%s,", a_header);
   DEBUG_PROG   yLOG_info    ("t"         , t);
   /*---(check individual)---------------*/
   --rce;  if (strstr (x_list, t) != NULL) {
      DEBUG_PROG   yLOG_note    ("already in specific list");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 2;
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
   switch (a_cat) {
   case 'I' : ystrlcat (my.depall, "×", LEN_RECD);   break;
   case 'O' : ystrlcat (my.depall, "Ö", LEN_RECD);   break;
   case 'F' : ystrlcat (my.depall, "Ï", LEN_RECD);   break;
   }
   ystrlcat (my.depall, t + 1, LEN_RECD);
   /*---(full total)---------------------*/
   ++g_handled;
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 1;
}

int
INCL_by_name            (char a_header [LEN_TITLE], char *r_block)
{
   char        rce         =  -10;
   int         i           =    0;
   if (r_block  != NULL)  *r_block = '·';
   --rce;  if (a_header == NULL)       return rce;
   --rce;  if (a_header [0] == '\0')   return rce;
   for (i = 0; i < MAX_INCL; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      if (strcmp (g_incls [i].i_name, a_header) != 0)  continue;
      if (r_block != NULL)  *r_block = g_incls [i].i_block;
      return i;
   }
   return rce;
}

char
DEPS__add               (char a_source [LEN_TITLE], char a_target [LEN_LABEL], char a_force)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *x_list      = NULL;
   int         x_beg       =   -1;
   int         x_end       =   -1;
   char        t           [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL || a_source [0] == '\0') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_source"  , a_source);
   DEBUG_PROG   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL || a_target [0] == '\0') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_target"  , a_target);
   --rce;  if (strcmp (a_source, a_target) == 0) {
      DEBUG_PROG   yLOG_note    ("circular dependency requested");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find beg-point)-----------------*/
   x_beg = INCL_by_name (a_source, NULL);
   DEBUG_PROG   yLOG_value   ("x_beg"     , x_beg);
   --rce;  if (x_beg < 0) {
      DEBUG_PROG   yLOG_note    ("a_source not found, but must record");
   }
   /*---(find end-point)-----------------*/
   x_end = GRAPH_by_name (a_target);
   DEBUG_PROG   yLOG_value   ("x_end"     , x_end);
   --rce;  if (x_end < 0) {
      if (a_force != 'y') {
         DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_end = GRAPH_add_node (a_target);
   }
   /*---(prepare)------------------------*/
   sprintf (t, ",%s,", a_source);
   DEBUG_PROG   yLOG_info    ("t"         , t);
   x_list = g_nodes [x_end].n_deps;
   DEBUG_PROG   yLOG_info    ("x_list"    , x_list);
   /*---(check)--------------------------*/
   --rce;  if (strstr (x_list, t) != NULL) {
      DEBUG_PROG   yLOG_note    ("already in list, just a duplicate");
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 2;
   }
   /*---(append)-------------------------*/
   switch (x_list [0]) {
   case '\0' :
   case '´'  :
      ystrlcpy (x_list   , ",", LEN_RECD);
      break;
   }
   ystrlcat (x_list, t + 1, LEN_RECD);
   /*---(not-standard)-------------------*/
   if (x_beg < 0) {
      DEBUG_PROG   yLOG_note    ("not found, so add to WTF");
      rc = INCL_list_add (DEPWTF, a_source);
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return 3;
   }
   /*---(add)----------------------------*/
   rc = INCL_list_add (g_incls [x_beg].i_cat, g_incls [x_beg].i_name);
   DEBUG_PROG   yLOG_value   ("list"      , rc);
   if (rc == 1) {
      DEBUG_PROG   yLOG_note    ("add to include counts");
      ++(g_incls [x_beg].i_count);
      DEBUG_PROG   yLOG_char    ("i_draw"    , g_incls [x_beg].i_draw);
      if (g_incls [x_beg].i_draw == 'y') {
         DEBUG_PROG   yLOG_note    ("add real graph edge");
         rc = GRAPH_edge_real (a_source, x_end);
         DEBUG_PROG   yLOG_value   ("edge"      , rc);
      } else if (g_incls [x_beg].i_draw == 'v') {
         DEBUG_PROG   yLOG_note    ("add virtual/koios graph edge");
         rc = GRAPH_edge_virt (a_source, x_end);
         DEBUG_PROG   yLOG_value   ("edge"      , rc);
      }
   }
   /*---(check for solo/uver)------------*/
   DEBUG_PROG   yLOG_char    ("i_zeno"    , g_incls [x_beg].i_zenodotus);
   if (g_incls [x_beg].i_zenodotus == 'y') {
      if (g_incls [x_beg].i_draw == 'y') {
         rc = DEPS_add ("zenodotus", a_source);
         DEBUG_PROG   yLOG_value   ("solo/uver" , rc);
         x_beg = GRAPH_by_name (a_source);
         DEBUG_PROG   yLOG_value   ("x_beg"     , x_beg);
         rc = GRAPH_edge_virt ("zenodotus", x_beg);
         DEBUG_PROG   yLOG_value   ("edge"      , rc);
         DEBUG_PROG   yLOG_exit    (__FUNCTION__);
         return rc;
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 1;
}

char DEPS_add         (char a_source [LEN_TITLE], char a_target [LEN_LABEL]) { return DEPS__add (a_source, a_target, '-'); }
char DEPS_force       (char a_source [LEN_TITLE], char a_target [LEN_LABEL]) { return DEPS__add (a_source, a_target, 'y'); }



/*====================------------------------------------====================*/
/*===----                     inclusion finding                        ----===*/
/*====================------------------------------------====================*/
static void  o___FIND____________o () { return; }

int
INCL_add_by_name        (char a_beg [LEN_TITLE], int a_end)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_beg"     , a_beg);
   --rce;  if (a_beg     == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_beg"     , a_beg);
   --rce;  if (a_beg [0] == '\0') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("a_end"     , a_end);
   --rce;  if (a_end < 0) {
      DEBUG_PROG   yLOG_note    ("negative a_end, better be unit testing");
   }
   /*---(find)---------------------------*/
   n  = INCL_by_name (a_beg, NULL);
   DEBUG_PROG   yLOG_value   ("by_name"   , n);
   /*---(not-standard)-------------------*/
   --rce;  if (n < 0) {
      DEBUG_PROG   yLOG_note    ("not found, so add to WTF");
      rc = INCL_list_add (DEPWTF, a_beg);
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add)----------------------------*/
   rc = INCL_list_add (g_incls [n].i_cat, g_incls [n].i_name);
   DEBUG_PROG   yLOG_value   ("list"      , rc);
   if (rc == 1) {
      DEBUG_PROG   yLOG_note    ("add to include counts");
      ++(g_incls [n].i_count);
      DEBUG_PROG   yLOG_char    ("i_draw"    , g_incls [n].i_draw);
      if (g_incls [n].i_draw == 'y') {
         DEBUG_PROG   yLOG_note    ("add real graph edge");
         rc = GRAPH_edge_real (a_beg, a_end);
         DEBUG_PROG   yLOG_value   ("edge"      , rc);
      } else if (g_incls [n].i_draw == 'v') {
         DEBUG_PROG   yLOG_note    ("add virtual/koios graph edge");
         rc = GRAPH_edge_virt (a_beg, a_end);
         DEBUG_PROG   yLOG_value   ("edge"      , rc);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return n;
}

char
INCL_add_by_group       (int a_end, char a_type)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_type     == 0)                  return rce;
   --rce;  if (strchr ("OC", a_type) == NULL)    return rce;
   for (i = 0; i < MAX_INCL; ++i) {
      if (g_incls [i].i_cat == 0)   break;
      switch (a_type) {
      case 'O' :
         /*> if (g_incls [i].i_opengl == 'y')  INCL_add_by_name (g_incls [i].i_name, a_end);   <*/
         if (g_incls [i].i_opengl == 'y')  DEPS_add (g_incls [i].i_name, g_nodes [a_end].n_name);
         break;
      case 'C' :
         /*> if (g_incls [i].i_curses == 'y')  INCL_add_by_name (g_incls [i].i_name, a_end);   <*/
         if (g_incls [i].i_curses == 'y')  DEPS_add (g_incls [i].i_name, g_nodes [a_end].n_name);
         break;
      }
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      wild gathering                          ----===*/
/*====================------------------------------------====================*/
static void  o___GATHER__________o () { return; }

char
INCL_gather_detail      (char a_header [LEN_TITLE], int a_end)
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
   DEBUG_DATA   yLOG_point   ("a_header"  , a_header);
   --rce; if (a_header == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_header"  , a_header);
   /*---(filter)-------------------------*/
   strcpy (t, a_header);
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
      INCL_add_by_group (a_end, 'O');
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 2;
   } else if (strcmp (t, "make_curses") == 0) {
      DEBUG_DATA   yLOG_note    ("found meta-curses header");
      INCL_add_by_group (a_end, 'C');
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(filter)-------------------------*/
   if (strcmp (t, "yVIHUB_solo") == 0) {
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(add to list)--------------------*/
   /*> n = INCL_add_by_name (t, a_end);                                               <*/
   DEPS_add (t, g_nodes [a_end].n_name);
   /*> DEBUG_DATA   yLOG_complex ("FOUND"     , "%-20.20s  %3d", t, n);               <*/
   if (n < 0) {
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*> DEBUG_DATA   yLOG_info    ("found"     , g_incls [n].i_name);                  <*/
   /*---(check for solos)----------------*/
   /*> DEBUG_DATA   yLOG_char    ("zenodotus" , g_incls [n].i_zenodotus);             <*/
   /*> if (g_incls [n].i_zenodotus == 'y') {                                                    <* 
    *>    DEBUG_PROG   yLOG_note    ("add a graph edge from zenodotus to _solo/_uver");         <* 
    *>    n  = GRAPH_by_name (t);                                                               <* 
    *>    DEBUG_PROG   yLOG_value   ("new node"  , n);                                          <* 
    *>    n = INCL_add_by_name ("zenodotus", a_end);                                            <* 
    *>    /+> rc = GRAPH_edge_virt ("zenodotus", n);                                      <+/   <* 
    *>    DEBUG_PROG   yLOG_value   ("edge"      , rc);                                         <* 
    *> }                                                                                        <*/
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 1;
}

char
INCL_gather             (char a_recd [LEN_RECD], int a_end)
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
            if      (strcmp (p + l - 7, "_solo.h") == 0)  rc = INCL_gather_detail (p, a_end);
            else if (strcmp (p + l - 7, "_uver.h") == 0)  rc = INCL_gather_detail (p, a_end);
            else {
               DEBUG_DATA  yLOG_note    ("ignore local headers except _solo and _uver");
               DEBUG_DATA  yLOG_exit    (__FUNCTION__);
               return 0;
            }
         } else {
            rc = INCL_gather_detail (p, a_end);
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
    *>    INCL_add_by_name ("zenodotus", GRAPH_by_name (a_proj));                     <* 
    *> }                                                                              <*/
   /*> if (strcmp (a_proj, "yUNIT") == 0) {                                           <* 
    *>    GRAPH_add_node  ("yENV_solo");                                              <* 
    *>    INCL_add_by_name ("yENV_solo", GRAPH_by_name (a_proj));                     <* 
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
    *  call GRAPH_deps_merge on all previous nodes
    *  call GRAPH_deps_missing  (these are the only drawn lines on box diagram)
    *  call GRAPH_deps_merge on current node also
    */
   /*---(complete)-----------------------*/
   return 0;
}

/*> char                                                                              <* 
 *> INCL_solos              (char a_proj [LEN_TITLE])                                 <* 
 *> {                                                                                 <* 
 *>    char        n           =   -1;                                                <* 
 *> }                                                                                 <*/

char
INCL_handler            (int n, uchar a_verb [LEN_TERSE])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        x_proj      [LEN_LABEL] = "";
   char        x_depall    [LEN_RECD]  = "";
   char       *p           = NULL;
   char       *q           = ",";
   char       *r           = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CONF  yLOG_point   ("a_verb"     , a_verb);
   --rce;  if (a_verb == NULL) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);
   rc = yPARSE_ready (&c);
   DEBUG_CONF  yLOG_value   ("rc"         , rc);
   DEBUG_CONF  yLOG_value   ("c"          , c);
   /*---(read project)-------------------*/
   --rce; if (strncmp (a_verb, "WAVE", 4) != 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(read unit test)-----------------*/
   rc = yPARSE_scanf (a_verb, "LR"  , x_proj, x_depall);
   /*---(trouble)------------------------*/
   DEBUG_CONF  yLOG_value   ("scanf"      , rc);
   if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check project)------------------*/
   DEBUG_CONF  yLOG_info    ("x_proj"     , x_proj);
   n = GRAPH_by_name (x_proj);
   if (n < 0)  n = GRAPH_add_node (x_proj);
   DEBUG_CONF  yLOG_value   ("n"          , n);
   if (n < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for empty)----------------*/
   if (strcmp (x_depall, "´") == 0) {
      DEBUG_PROG  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(handle)-------------------------*/
   c = 0;
   p = strtok_r (x_depall, q, &r);
   while (p != NULL) {
      /*> rc = INCL_add_by_name (p, n);                                               <*/
      rc = DEPS_add (p, x_proj);
      ++c;
      p = strtok_r (NULL, q, &r);
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_exit    (__FUNCTION__);
   return c;
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
         if (g_incls [i].i_cat == 0)   break;
         if (g_incls [i].i_count <= 0) continue;
         ++x_count;
         x_total += g_incls [i].i_count;
      }
      snprintf (my.unit_answer, LEN_RECD, "INCL count       : %4d count, %4d total, %4d handled", x_count, x_total, g_handled);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



