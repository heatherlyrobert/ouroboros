/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



struct {
   char        c_cat;
   char        c_name      [LEN_LABEL];
   char        c_desc      [LEN_HUND];
} static s_cats [LEN_LABEL] = {
   { 'u', "unit"           , "unit testing tools required"                        },
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


#define   MAX_INCL   300
typedef  struct cINCL tINCL;
struct cINCL {
   char        i_cat;
   char        i_name      [LEN_TITLE];
   int         i_count;
   char        i_opengl;                /* including in make_opengl.h        */
   char        i_curses;                /* including in make_curses.h        */
   char        i_draw;                  /* include in output drawings        */
};

static tINCL s_incls [MAX_INCL] = {
   /*---(ansi c)-------------------------*/
   /* original c standard */
   { 'a', "assert"                   , 0, '-', '-', '-' },
   { 'a', "ctype"                    , 0, '-', '-', '-' },
   { 'a', "errno"                    , 0, '-', '-', '-' },
   { 'a', "float"                    , 0, '-', '-', '-' },
   { 'a', "limits"                   , 0, '-', '-', '-' },
   { 'a', "locale"                   , 0, '-', '-', '-' },
   { 'a', "malloc"                   , 0, '-', '-', '-' },
   { 'a', "math"                     , 0, '-', '-', '-' },
   { 'a', "memory"                   , 0, '-', '-', '-' },
   { 'a', "setjmp"                   , 0, '-', '-', '-' },
   { 'a', "signal"                   , 0, '-', '-', '-' },
   { 'a', "stdarg"                   , 0, '-', '-', '-' },
   { 'a', "stddef"                   , 0, '-', '-', '-' },
   { 'a', "stdio"                    , 0, '-', '-', '-' },
   { 'a', "stdlib"                   , 0, '-', '-', '-' },
   { 'a', "string"                   , 0, '-', '-', '-' },
   { 'a', "time"                     , 0, '-', '-', '-' },
   /*---(ansi c updates)-----------------, 0*/
   /* c99, c23, ... , 0*/
   { 'a', "complex"                  , 0, '-', '-', '-' },
   { 'a', "err"                      , 0, '-', '-', '-' },
   { 'a', "error"                    , 0, '-', '-', '-' },
   { 'a', "fenv"                     , 0, '-', '-', '-' },
   { 'a', "inttypes"                 , 0, '-', '-', '-' },
   { 'a', "iso646"                   , 0, '-', '-', '-' },
   { 'a', "stdalign"                 , 0, '-', '-', '-' },
   { 'a', "stdatomic"                , 0, '-', '-', '-' },
   { 'a', "stdbit"                   , 0, '-', '-', '-' },
   { 'a', "stdbool"                  , 0, '-', '-', '-' },
   { 'a', "stdchkdint"               , 0, '-', '-', '-' },
   { 'a', "stdint"                   , 0, '-', '-', '-' },
   { 'a', "stdnoreturn"              , 0, '-', '-', '-' },
   { 'a', "tmath"                    , 0, '-', '-', '-' },
   { 'a', "threads"                  , 0, '-', '-', '-' },
   { 'a', "uchar"                    , 0, '-', '-', '-' },
   { 'a', "wchar"                    , 0, '-', '-', '-' },
   { 'a', "wctype"                   , 0, '-', '-', '-' },
   /*---(posix c standard)---------------, 0*/
   /* wider POXIX related libraries (maybe harder to port) , 0*/
   { 'p', "aio"                      , 0, '-', '-', '-' },
   { 'p', "arpa/inet"                , 0, '-', '-', '-' },
   { 'p', "cpio"                     , 0, '-', '-', '-' },
   { 'p', "dirent"                   , 0, '-', '-', '-' },
   { 'p', "dlfcn"                    , 0, '-', '-', '-' },
   { 'p', "fcntl"                    , 0, '-', '-', '-' },
   { 'p', "fmtmsg"                   , 0, '-', '-', '-' },
   { 'p', "fnctrl"                   , 0, '-', '-', '-' },
   { 'p', "fnmatch"                  , 0, '-', '-', '-' },
   { 'p', "ftw"                      , 0, '-', '-', '-' },
   { 'p', "glob"                     , 0, '-', '-', '-' },
   { 'p', "grp"                      , 0, '-', '-', '-' },
   { 'p', "iconv"                    , 0, '-', '-', '-' },
   { 'p', "langinfo"                 , 0, '-', '-', '-' },
   { 'p', "libgen"                   , 0, '-', '-', '-' },
   { 'p', "linux/fs"                 , 0, '-', '-', '-' },
   { 'p', "linux/hdreg"              , 0, '-', '-', '-' },
   { 'p', "monetary"                 , 0, '-', '-', '-' },
   { 'p', "mqueue"                   , 0, '-', '-', '-' },
   { 'p', "ndbm"                     , 0, '-', '-', '-' },
   { 'p', "net/if"                   , 0, '-', '-', '-' },
   { 'p', "netdb"                    , 0, '-', '-', '-' },
   { 'p', "netinet/in"               , 0, '-', '-', '-' },
   { 'p', "netinet/tcp"              , 0, '-', '-', '-' },
   { 'p', "nl_types"                 , 0, '-', '-', '-' },
   { 'p', "poll"                     , 0, '-', '-', '-' },
   { 'p', "pthread"                  , 0, '-', '-', '-' },
   { 'p', "pwd"                      , 0, '-', '-', '-' },
   { 'p', "regex"                    , 0, '-', '-', '-' },
   { 'p', "sched"                    , 0, '-', '-', '-' },
   { 'p', "search"                   , 0, '-', '-', '-' },
   { 'p', "semaphore"                , 0, '-', '-', '-' },
   { 'p', "shadow"                   , 0, '-', '-', '-' },
   { 'p', "spawn"                    , 0, '-', '-', '-' },
   { 'p', "strings"                  , 0, '-', '-', '-' },
   { 'p', "stropts"                  , 0, '-', '-', '-' },
   { 'p', "sys/ioctl"                , 0, '-', '-', '-' },
   { 'p', "sys/ipc"                  , 0, '-', '-', '-' },
   { 'p', "sys/mman"                 , 0, '-', '-', '-' },
   { 'p', "sys/mount"                , 0, '-', '-', '-' },
   { 'p', "sys/reboot"               , 0, '-', '-', '-' },
   { 'p', "sys/resource"             , 0, '-', '-', '-' },
   { 'p', "sys/select"               , 0, '-', '-', '-' },
   { 'p', "sys/sem"                  , 0, '-', '-', '-' },
   { 'p', "sys/shm"                  , 0, '-', '-', '-' },
   { 'p', "sys/socket"               , 0, '-', '-', '-' },
   { 'p', "sys/stat"                 , 0, '-', '-', '-' },
   { 'p', "sys/stavfs"               , 0, '-', '-', '-' },
   { 'p', "sys/sysmacros"            , 0, '-', '-', '-' },
   { 'p', "sys/time"                 , 0, '-', '-', '-' },
   { 'p', "sys/times"                , 0, '-', '-', '-' },
   { 'p', "sys/types"                , 0, '-', '-', '-' },
   { 'p', "sys/uio"                  , 0, '-', '-', '-' },
   { 'p', "sys/un"                   , 0, '-', '-', '-' },
   { 'p', "sys/utsname"              , 0, '-', '-', '-' },
   { 'p', "sys/wait"                 , 0, '-', '-', '-' },
   { 'p', "syslog"                   , 0, '-', '-', '-' },
   { 'p', "termios"                  , 0, '-', '-', '-' },
   { 'p', "tgmath"                   , 0, '-', '-', '-' },
   { 'p', "trace"                    , 0, '-', '-', '-' },
   { 'p', "unistd"                   , 0, '-', '-', '-' },
   { 'p', "sys/unistd"               , 0, '-', '-', '-' },
   { 'p', "utime"                    , 0, '-', '-', '-' },
   { 'p', "utmp"                     , 0, '-', '-', '-' },
   { 'p', "utmpx"                    , 0, '-', '-', '-' },
   { 'p', "wordexp"                  , 0, '-', '-', '-' },

   /*---(heatherly core)-----------------*/
   /* core, nearly every program uses these libraries */
   { 'c', "zenodotus"                , 0, '-', '-', 'y' },
   { 'c', "yLOG"                     , 0, 'y', 'y', 'y' },
   { 'c', "yURG"                     , 0, 'y', 'y', 'y' },
   { 'c', "yVAR"                     , 0, '-', '-', 'y' },
   { 'c', "ySTR"                     , 0, 'y', 'y', 'y' },
   { 'c', "yENV"                     , 0, '-', '-', 'y' },

   /*---(heatherly vikeys)---------------*/
   /* vikeys components supporting full vi-keys environment */
   { 'v', "yMODE"                    , 0, 'y', 'y', 'y' },
   { 'v', "yKEYS"                    , 0, 'y', 'y', 'y' },
   { 'v', "yFILE"                    , 0, 'y', 'y', 'y' },
   { 'v', "yVIEW"                    , 0, 'y', 'y', 'y' },

   { 'v', "yMAP"                     , 0, 'y', 'y', 'y' },
   { 'v', "yCMD"                     , 0, 'y', 'y', 'y' },
   { 'v', "yMACRO"                   , 0, 'y', 'y', 'y' },
   { 'v', "ySRC"                     , 0, 'y', 'y', 'y' },
   { 'v', "yMARK"                    , 0, 'y', 'y', 'y' },

   { 'v', "yGOD"                     , 0, '-', '-', 'y' },
   { 'v', "yVIHUB"                   , 0, '-', '-', 'y' },

   /*---(heatherly vikeys)---------------*/
   /* graphics specific libraries */
   /* -    -------------------------  */
   { 'g', "ncurses"                  , 0, '-', 'y', '-' },
   { 'g', "tinfo"                    , 0, '-', 'y', '-' },
   { 'g', "X11"                      , 0, '-', '-', '-' },
   { 'g', "X11/X"                    , 0, 'y', '-', '-' },
   { 'g', "X11/Xlib"                 , 0, 'y', '-', '-' },
   { 'g', "X11/extensions/shape"     , 0, '-', '-', '-' },
   { 'g', "X11/Xutil"                , 0, '-', '-', '-' },
   { 'g', "X11/keysym"               , 0, '-', '-', '-' },
   { 'g', "X11/Xatom"                , 0, '-', '-', '-' },
   { 'g', "GL"                       , 0, '-', '-', '-' },
   { 'g', "GL/gl"                    , 0, 'y', '-', '-' },
   { 'g', "GL/glx"                   , 0, 'y', '-', '-' },
   { 'g', "GL/glu"                   , 0, '-', '-', '-' },
   { 'g', "yX11"                     , 0, 'y', '-', 'y' },
   { 'g', "yGLTEX"                   , 0, 'y', '-', 'y' },
   { 'g', "yCOLOR"                   , 0, 'y', '-', 'y' },
   { 'g', "yFONT"                    , 0, 'y', '-', 'y' },
   { 'g', "yVIOPENGL"                , 0, 'y', '-', 'y' },
   { 'g', "yVICURSES"                , 0, '-', 'y', 'y' },

   /*---(heatherly other)----------------*/
   /* mine, but not core, vikey, or graphics libraries */
   { 'o', "yASCII"                   , 0, '-', '-', 'y' },
   { 'o', "yCALC"                    , 0, '-', '-', 'y' },
   { 'o', "yDLST"                    , 0, '-', '-', 'y' },
   { 'o', "ySEC"                     , 0, '-', '-', 'y' },
   { 'o', "ySORT"                    , 0, '-', '-', 'y' },
   { 'o', "yPARSE"                   , 0, '-', '-', 'y' },
   { 'o', "yJOBS"                    , 0, '-', '-', 'y' },
   { 'o', "yEXEC"                    , 0, '-', '-', 'y' },
   { 'o', "yGOLEM"                   , 0, '-', '-', 'y' },
   { 'o', "yKINE"                    , 0, '-', '-', 'y' },
   { 'o', "yREGEX"                   , 0, '-', '-', 'y' },
   { 'o', "yRPN"                     , 0, '-', '-', 'y' },
   { 'o', "ySCHED"                   , 0, '-', '-', 'y' },
   { 'o', "ySHELL"                   , 0, '-', '-', 'y' },
   { 'o', "yHUBLIN"                  , 0, '-', '-', 'y' },

   /*---(heatherly solo)-----------------*/
   /* just taking in for definitions in header file */
   { 's', "yLOG_solo"                , 0, '-', '-', 'y' },
   { 's', "yLOG_uver"                , 0, '-', '-', 'y' },
   { 's', "yURG_solo"                , 0, '-', '-', 'y' },
   { 's', "ySTR_solo"                , 0, '-', '-', 'y' },
   { 's', "ySTR_uver"                , 0, '-', '-', 'y' },
   { 's', "yENV_solo"                , 0, '-', '-', 'y' },
   { 's', "yENV_uver"                , 0, '-', '-', 'y' },
   { 's', "yDLST_solo"               , 0, '-', '-', 'y' },
   { 's', "yCOLOR_solo"              , 0, '-', '-', 'y' },
   { 's', "yVIHUB_solo"              , 0, 'y', 'y', 'y' },

   /*---(heatherly unit testing)---------*/
   { 'u', "yUNIT_solo"               , 0, '-', '-', 'y' },
   { 'u', "yUNIT"                    , 0, '-', '-', 'y' },

   /*---(heatherly DEPRECATED)-----------*/
   /* just taking in for definitions in header file */
   { 'X', "yVIKEYS"                  , 0, '-', '-', '-' },
   { 'X', "yXINIT"                   , 0, '-', '-', '-' },

   /*---(alien)--------------------------*/
   /* just taking in for definitions in header file */
   { '!', "png"                      , 0, '-', '-', '-' },
   { '!', "jpeglib"                  , 0, '-', '-', '-' },
   { '!', "openssl/sha"              , 0, '-', '-', '-' },
   { '!', "ft2build"                 , 0, '-', '-', '-' },

   /*---(end)----------------------------*/
   {  0 , "end-of-list"              , 0, '-', '-', '-' },
};
static int  s_nincl   = 0;
static int  s_handled = 0;



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
INCL_clear              (void)
{
   int         i           =    0;
   s_nincl   = 0;
   s_handled = 0;
   for (i = 0; i < MAX_INCL; ++i) {
      if (s_incls [i].i_cat == 0)   break;
      s_incls [i].i_count = 0;
      ++s_nincl;
   }
   INCL_list_clear ();
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
   strcpy (my.depall  , "´");
   strcpy (my.depwtf  , "´");
   return 0;
}

char
INCL_list_add           (char a_cat, char a_header [LEN_TITLE])
{
   char        rce         =  -10;
   char       *x_list      = NULL;
   char        t           [LEN_HUND]  = "";
   /*---(defense)------------------------*/
   --rce;  if (a_header     == NULL)  return rce;
   --rce;  if (a_header [0] == '\0')  return rce;
   /*---(pick list)----------------------*/
   --rce;  switch (a_cat) {
   case 's' :  x_list = my.depsolo;    break;
   case 'u' :  x_list = my.depunit;    break;
   case 'a' :  x_list = my.depansi;    break;
   case 'p' :  x_list = my.depposix;   break;
   case 'c' :  x_list = my.depcore;    break;
   case 'v' :  x_list = my.depvikey;   break;
   case 'g' :  x_list = my.depgraph;   break;
   case 'o' :  x_list = my.depother;   break;
   case '!' :  x_list = my.depalien;   break;
   case 'I' :  x_list = my.depinpt;    break;
   case 'O' :  x_list = my.depoutp;    break;
   case 'F' :  x_list = my.depfile;    break;
   default  :  x_list = my.depwtf;     break;
   }
   /*---(prepare)------------------------*/
   sprintf (t, ",%s,", a_header);
   /*---(check individual)---------------*/
   --rce;  if (strstr (x_list, t) != NULL)     return 2;
   if (x_list [0]    == '´')  ystrlcpy (x_list   , ",", LEN_FULL);
   ystrlcat (x_list, t + 1, LEN_FULL);
   /*---(check all)----------------------*/
   --rce;  if (strstr (my.depall, t) != NULL)  return 3;
   if (my.depall [0] == '´')  ystrlcpy (my.depall, ",", LEN_RECD);
   switch (a_cat) {
   case 'I' : ystrlcat (my.depall, "×", LEN_RECD);   break;
   case 'O' : ystrlcat (my.depall, "Ö", LEN_RECD);   break;
   case 'F' : ystrlcat (my.depall, "Ï", LEN_RECD);   break;
   }
   ystrlcat (my.depall, t + 1, LEN_RECD);
   /*---(full total)---------------------*/
   ++s_handled;
   /*---(complete)-----------------------*/
   return 1;
}



/*====================------------------------------------====================*/
/*===----                     inclusion finding                        ----===*/
/*====================------------------------------------====================*/
static void  o___FIND____________o () { return; }

int
INCL_add_by_name        (int a_end, char a_header [LEN_TITLE])
{
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   --rce;  if (a_header     == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_header [0] == '\0') {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < MAX_INCL; ++i) {
      if (s_incls [i].i_cat == 0)   break;
      if (strcmp (s_incls [i].i_name, a_header) != 0)  continue;
      rc = INCL_list_add (s_incls [i].i_cat, s_incls [i].i_name);
      if (rc == 1) {
         ++(s_incls [i].i_count);
         if (a_end >= 0) {
            if (strchr (DEPVISIBLE, s_incls [i].i_cat) != NULL) {
               if (a_header [0] == 'y') {
                  rc = GRAPH_add_edge (a_header, a_end);
               }
            }
         }
      }
      DEBUG_PROG   yLOG_value   ("i"         , i);
      DEBUG_PROG   yLOG_exit    (__FUNCTION__);
      return i;
   }
   INCL_list_add ('?', a_header);
   if (a_end >= 0)   rc = GRAPH_add_edge (a_header, a_end);
   DEBUG_PROG   yLOG_exitr   (__FUNCTION__, --rce);
   return rce;
}

char
INCL_add_by_group       (int a_end, char a_type)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_type     == 0)                  return rce;
   --rce;  if (strchr ("OC", a_type) == NULL)    return rce;
   for (i = 0; i < MAX_INCL; ++i) {
      if (s_incls [i].i_cat == 0)   break;
      switch (a_type) {
      case 'O' :
         if (s_incls [i].i_opengl == 'y')  INCL_add_by_name (a_end, s_incls [i].i_name);
         break;
      case 'C' :
         if (s_incls [i].i_curses == 'y')  INCL_add_by_name (a_end, s_incls [i].i_name);
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
INCL_gather_add         (int a_end, char a_head [LEN_TITLE])
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
   DEBUG_DATA   yLOG_point   ("a_head"    , a_head);
   --rce; if (a_head == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_head"    , a_head);
   /*---(filter)-------------------------*/
   strcpy (t, a_head);
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
      return 1;
   } else if (strcmp (t, "make_curses") == 0) {
      DEBUG_DATA   yLOG_note    ("found meta-curses header");
      INCL_add_by_group (a_end, 'C');
      DEBUG_DATA  yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(add to list)--------------------*/
   n = INCL_add_by_name (a_end, t);
   DEBUG_DATA   yLOG_value   ("n"         , n);
   /*---(found)--------------------------*/
   /*> if (n >= 0) {                                                                                 <* 
    *>    DEBUG_DATA   yLOG_complex ("FOUND"     , "%-20.20s  %3d  %c", t, n, s_incls [n].i_cat);    <* 
    *>    if (strchr (DEPVISIBLE, s_incls [n].i_cat) != NULL && s_incls [n].i_name [0] == 'y')   {   <* 
    *>       GRAPH_add_edge (s_incls [n].i_name, a_end);                                             <* 
    *>    }                                                                                          <* 
    *>    DEBUG_DATA  yLOG_exit    (__FUNCTION__);                                                   <* 
    *>    return 1;                                                                                  <* 
    *> }                                                                                             <*/
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 0;
}

char
INCL_gather_in_c        (char a_proj [LEN_TITLE], cchar a_file [LEN_PATH])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *rcp         = NULL;
   char        x_temp      [LEN_LABEL] = "/tmp/ouroboros.txt";
   char        x_cmd       [LEN_RECD]  = "";
   char        x_recd      [LEN_RECD]  = "";
   FILE       *f           =    0;
   char       *p           =    0;
   char       *q           =  " ";
   char        t           [LEN_TITLE] = "";
   int         l           =    0;
   int         c           =    0;
   int         n           =    0;
   int         x_end       =    0;
   char        x_delimit   =  '>';
   /*---(header)-------------------------*/
   DEBUG_DATA  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_point   ("a_file"    , a_file);
   --rce; if (a_file == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_file"    , a_file);
   /*---(add project)--------------------*/
   x_end = GRAPH_add_node (a_proj);
   DEBUG_DATA   yLOG_value   ("x_end"     , x_end);
   /*---(prepare)------------------------*/
   sprintf (x_cmd, "grep \"^#include\" %s > %s 2> /dev/null", a_file, x_temp);
   rc = system (x_cmd);
   DEBUG_DATA   yLOG_value   ("grep"      , rc);
   --rce; if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   c = yENV_lines (x_temp);
   DEBUG_DATA   yLOG_value   ("c"         , c);
   /*---(open)---------------------------*/
   f = fopen (x_temp, "rt");
   DEBUG_DATA   yLOG_point   ("f"         , f);
   --rce; if (f == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(pull)---------------------------*/
   rcp = fgets (x_recd, LEN_RECD, f);
   DEBUG_DATA   yLOG_point   ("fgets"     , rcp);
   while (rcp != NULL) {
      if (feof (f)) {
         DEBUG_DATA   yLOG_note    ("end-of-file");
         break;
      }
      l = strlen (x_recd);
      if (l > 0 && x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
      DEBUG_DATA   yLOG_info    ("x_recd"    , x_recd);
      /*---(work out delimiters)---------*/
      p = strchr (x_recd, '<');
      if (p != NULL) {
         x_delimit = '>';
      } else  {
         p = strchr (x_recd, '"');
         x_delimit = '"';
      }
      DEBUG_DATA   yLOG_point   ("p"         , p);
      /*---(handle)----------------------*/
      if (p != NULL) {
         DEBUG_DATA   yLOG_char    ("x_delimit" , x_delimit);
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
               if      (strcmp (p + l - 7, "_solo.h") == 0)  INCL_gather_add (x_end, p);
               else if (strcmp (p + l - 7, "_uver.h") == 0)  INCL_gather_add (x_end, p);
            } else {
               INCL_gather_add (x_end, p);
            }
         }
      }
      /*---(next)------------------------*/
      rcp  = fgets (x_recd, LEN_RECD, f);
      DEBUG_DATA   yLOG_point   ("fgets"     , rcp);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   rc = fclose (f);
   DEBUG_DATA   yLOG_value   ("close"     , rc);
   --rce; if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clean-up)-----------------------*/
   yENV_rm (x_temp);
   /*---(complete)-----------------------*/
   DEBUG_DATA  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      pulling from database                   ----===*/
/*====================------------------------------------====================*/
static void  o___PULL____________o () { return; }

char
INCL_handler            (int n, uchar a_verb [LEN_TERSE], char a_exist, void *a_handler)
{
   /*> /+---(locals)-----------+-----------+-+/                                                                                                                                                                                                                                                                <* 
    *> char        rce         =  -10;                                                                                                                                                                                                                                                                         <* 
    *> int         rc          =    0;                                                                                                                                                                                                                                                                         <* 
    *> tWAVE      *x_new       = NULL;                                                                                                                                                                                                                                                                         <* 
    *> char        x_time      [LEN_TITLE] = "";                                                                                                                                                                                                                                                               <* 
    *> long        x_epoch     =    0;                                                                                                                                                                                                                                                                         <* 
    *> char        x_proj      [LEN_LABEL] = "";                                                                                                                                                                                                                                                               <* 
    *> char        x_unit      [LEN_TITLE] = "";                                                                                                                                                                                                                                                               <* 
    *> short       x_scrp      =    0;                                                                                                                                                                                                                                                                         <* 
    *> char        x_source    =  '·';                                                                                                                                                                                                                                                                         <* 
    *> char        x_wave      =  '·';                                                                                                                                                                                                                                                                         <* 
    *> char        x_stage     =  '·';                                                                                                                                                                                                                                                                         <* 
    *> char        x_rating    =  '·';                                                                                                                                                                                                                                                                         <* 
    *> char        x_desc      [LEN_LONG]  = "";                                                                                                                                                                                                                                                               <* 
    *> char        x_terse     [LEN_LABEL] = "";                                                                                                                                                                                                                                                               <* 
    *> int         x_nunit     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_nscrp     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_ncond     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_nstep     =    0;                                                                                                                                                                                                                                                                         <* 
    *> char        x_expe      [LEN_SHORT] = "";                                                                                                                                                                                                                                                               <* 
    *> int         x_expect    =    0;                                                                                                                                                                                                                                                                         <* 
    *> char        x_result    =  '-';                                                                                                                                                                                                                                                                         <* 
    *> int         x_npass     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_nfail     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_nbadd     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_nvoid     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_nmiss     =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         x_actual    =    0;                                                                                                                                                                                                                                                                         <* 
    *> int         c           =    0;                                                                                                                                                                                                                                                                         <* 
    *> /+---(header)-------------------------+/                                                                                                                                                                                                                                                                <* 
    *> DEBUG_CONF  yLOG_enter   (__FUNCTION__);                                                                                                                                                                                                                                                                <* 
    *> /+---(defense)------------------------+/                                                                                                                                                                                                                                                                <* 
    *> DEBUG_CONF  yLOG_point   ("a_verb"     , a_verb);                                                                                                                                                                                                                                                       <* 
    *> --rce;  if (a_verb == NULL) {                                                                                                                                                                                                                                                                           <* 
    *>    DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                        <* 
    *>    return rce;                                                                                                                                                                                                                                                                                          <* 
    *> }                                                                                                                                                                                                                                                                                                       <* 
    *> DEBUG_CONF  yLOG_info    ("a_verb"     , a_verb);                                                                                                                                                                                                                                                       <* 
    *> rc = yPARSE_ready (&c);                                                                                                                                                                                                                                                                                 <* 
    *> DEBUG_CONF  yLOG_value   ("rc"         , rc);                                                                                                                                                                                                                                                           <* 
    *> DEBUG_CONF  yLOG_value   ("c"          , c);                                                                                                                                                                                                                                                            <* 
    *> /+---(read details)-------------------+/                                                                                                                                                                                                                                                                <* 
    *> --rce; if (strncmp (a_verb, "PROJ", 4) == 0) {                                                                                                                                                                                                                                                          <* 
    *>    rc = yPARSE_scanf (a_verb, "--L-------------------"  , x_proj);                                                                                                                                                                                                                                      <* 
    *> }                                                                                                                                                                                                                                                                                                       <* 
    *> else if   (strncmp (a_verb, "UNIT", 4) == 0) {                                                                                                                                                                                                                                                          <* 
    *>    rc = yPARSE_scanf (a_verb, "--L3------------------"  , x_proj, x_unit);                                                                                                                                                                                                                              <* 
    *> }                                                                                                                                                                                                                                                                                                       <* 
    *> else if   (strncmp (a_verb, "WAVE", 4) == 0) {                                                                                                                                                                                                                                                          <* 
    *>    switch (c) {                                                                                                                                                                                                                                                                                         <* 
    *>    case 23 : case 28 :                                                                                                                                                                                                                                                                                  <* 
    *>       rc = yPARSE_scanf (a_verb, "3lL3s7LCCiiiiSiCiiiiii"  , x_time, &x_epoch, x_proj, x_unit, &x_scrp, x_desc, x_terse, &x_wave, &x_stage, &x_nunit, &x_nscrp, &x_ncond, &x_nstep, x_expe, &x_expect, &x_result, &x_npass, &x_nfail, &x_nbadd, &x_nvoid, &x_nmiss, &x_actual);                         <* 
    *>       break;                                                                                                                                                                                                                                                                                            <* 
    *>    case 24 : case 29 :                                                                                                                                                                                                                                                                                  <* 
    *>       rc = yPARSE_scanf (a_verb, "3lL3s7LCCCiiiiSiCiiiiii" , x_time, &x_epoch, x_proj, x_unit, &x_scrp, x_desc, x_terse, &x_wave, &x_stage, &x_rating, &x_nunit, &x_nscrp, &x_ncond, &x_nstep, x_expe, &x_expect, &x_result, &x_npass, &x_nfail, &x_nbadd, &x_nvoid, &x_nmiss, &x_actual);              <* 
    *>       break;                                                                                                                                                                                                                                                                                            <* 
    *>    case 25 : case 30 :                                                                                                                                                                                                                                                                                  <* 
    *>       rc = yPARSE_scanf (a_verb, "3lL3sC7LCCCiiiiSiCiiiiii", x_time, &x_epoch, x_proj, x_unit, &x_scrp, &x_source, x_desc, x_terse, &x_wave, &x_stage, &x_rating, &x_nunit, &x_nscrp, &x_ncond, &x_nstep, x_expe, &x_expect, &x_result, &x_npass, &x_nfail, &x_nbadd, &x_nvoid, &x_nmiss, &x_actual);   <* 
    *>       break;                                                                                                                                                                                                                                                                                            <* 
    *>    }                                                                                                                                                                                                                                                                                                    <* 
    *> }                                                                                                                                                                                                                                                                                                       <* 
    *> else {                                                                                                                                                                                                                                                                                                  <* 
    *>    DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                        <* 
    *>    return rce;                                                                                                                                                                                                                                                                                          <* 
    *> }                                                                                                                                                                                                                                                                                                       <* 
    *> DEBUG_CONF  yLOG_value   ("scanf"      , rc);                                                                                                                                                                                                                                                           <* 
    *> if (rc < 0) {                                                                                                                                                                                                                                                                                           <* 
    *>    DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                        <* 
    *>    return rce;                                                                                                                                                                                                                                                                                          <* 
    *> }                                                                                                                                                                                                                                                                                                       <* 
    *> /+---(add wave)-----------------------+/                                                                                                                                                                                                                                                                <* 
   *> DEBUG_CONF  yLOG_info    ("x_proj"     , x_proj);                                                                                                                                                                                                                                                       <* 
      *> DEBUG_CONF  yLOG_info    ("x_unit"     , x_unit);                                                                                                                                                                                                                                                       <* 
      *> DEBUG_CONF  yLOG_value   ("x_stage"    , x_stage);                                                                                                                                                                                                                                                      <* 
      *> rc = WAVE__new (x_proj, x_unit, x_scrp, s_gather, &x_new);                                                                                                                                                                                                                                              <* 
      *> DEBUG_CONF  yLOG_value   ("new"        , rc);                                                                                                                                                                                                                                                           <* 
      *> --rce;  if (rc < 0) {                                                                                                                                                                                                                                                                                   <* 
         *>    DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);                                                                                                                                                                                                                                                        <* 
            *>    return rce;                                                                                                                                                                                                                                                                                          <* 
            *> }                                                                                                                                                                                                                                                                                                       <* 
            *> /+---(note)---------------------------+/                                                                                                                                                                                                                                                                <* 
            *> if (rc == 0)  {                                                                                                                                                                                                                                                                                         <* 
               *>    DEBUG_PROG  yLOG_note    ("NEW");                                                                                                                                                                                                                                                                    <* 
                  *> } else {                                                                                                                                                                                                                                                                                                <* 
                     *>    DEBUG_PROG  yLOG_note    ("UPDATING");                                                                                                                                                                                                                                                               <* 
                        *> }                                                                                                                                                                                                                                                                                                       <* 
                        *> /+---(save)---------------------------+/                                                                                                                                                                                                                                                                <* 
                        *> x_new->w_source  = x_source;                                                                                                                                                                                                                                                                            <* 
                        *> ystrlcpy (x_new->w_time   , x_time   , LEN_TITLE);                                                                                                                                                                                                                                                      <* 
                        *> x_new->w_last    = x_epoch;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_wave    = x_wave;                                                                                                                                                                                                                                                                              <* 
                        *> x_new->w_stage   = x_stage;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_rating  = x_rating;                                                                                                                                                                                                                                                                            <* 
                        *> ystrlcpy (x_new->w_desc   , x_desc   , LEN_LONG);                                                                                                                                                                                                                                                       <* 
                        *> ystrlcpy (x_new->w_terse  , x_terse  , LEN_LABEL);                                                                                                                                                                                                                                                      <* 
                        *> x_new->w_nunit   = x_nunit;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_nscrp   = x_nscrp;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_ncond   = x_ncond;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_nstep   = x_nstep;                                                                                                                                                                                                                                                                             <* 
                        *> ystrlcpy (x_new->w_expe   , x_expe   , LEN_SHORT);                                                                                                                                                                                                                                                      <* 
                        *> ystrlunage (x_expe, &x_expect);                                                                                                                                                                                                                                                                         <* 
                        *> x_new->w_expect  = x_expect;                                                                                                                                                                                                                                                                            <* 
                        *> x_new->w_result  = x_result;                                                                                                                                                                                                                                                                            <* 
                        *> x_new->w_npass   = x_npass;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_nfail   = x_nfail;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_nbadd   = x_nbadd;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_nvoid   = x_nvoid;                                                                                                                                                                                                                                                                             <* 
                        *> x_new->w_nmiss   = x_new->w_nstep - x_new->w_npass - x_new->w_nfail - x_new->w_nbadd - x_new->w_nvoid;                                                                                                                                                                                                  <* 
                        *> x_new->w_actual  = x_actual;                                                                                                                                                                                                                                                                            <* 
                        *> /+---(update totals)------------------+/                                                                                                                                                                                                                                                                <* 
                        *> if (strncmp (x_time, "··´", 3) == 0) {                                                                                                                                                                                                                                                                  <* 
                           *>    rc = WAVE__new (x_proj, x_unit, 0, '-', NULL);                                                                                                                                                                                                                                                       <* 
                              *> }                                                                                                                                                                                                                                                                                                       <* 
                              *> /+---(update totals)------------------+/                                                                                                                                                                                                                                                                <* 
                              *> ++s_read;                                                                                                                                                                                                                                                                                               <* 
                              *> /+---(complete)-----------------------+/                                                                                                                                                                                                                                                                <* 
                              *> DEBUG_CONF  yLOG_exit    (__FUNCTION__);                                                                                                                                                                                                                                                                <* 
                              *> return 0;                                                                                                                                                                                                                                                                                               <*/
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
      if (s_incls [i].i_cat == 0)   break;
      if (s_incls [i].i_count == 0) {
         printf ("%3d  %c  %-25.25s  ···\n", i, s_incls [i].i_cat, s_incls [i].i_name);
      } else {
         printf ("%3d  %c  %-25.25s  %3d\n", i, s_incls [i].i_cat, s_incls [i].i_name, s_incls [i].i_count);
      }
   }
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
   if (strstr (a_proj, "_solo") != NULL) {
      INCL_add_by_name (GRAPH_by_name (a_proj), "zenodotus");
   }
   /*> if (strcmp (a_proj, "yUNIT") == 0) {                                           <* 
    *>    GRAPH_add_node  ("yENV_solo");                                              <* 
    *>    INCL_add_by_name (GRAPH_by_name (a_proj), "yENV_solo");                     <* 
    *> }                                                                              <*/
   /*---(show result)--------------------*/
   printf ("PROJECT     : å%sæ\n", a_proj);
   printf ("  depsolo   : %4då%sæ\n", strlen (my.depsolo ), my.depsolo );
   printf ("  depunit   : %4då%sæ\n", strlen (my.depunit ), my.depunit );
   printf ("  depansi   : %4då%sæ\n", strlen (my.depansi ), my.depansi );
   printf ("  depposix  : %4då%sæ\n", strlen (my.depposix), my.depposix);
   printf ("  depcore   : %4då%sæ\n", strlen (my.depcore ), my.depcore );
   printf ("  depvikey  : %4då%sæ\n", strlen (my.depvikey), my.depvikey);
   printf ("  depgraph  : %4då%sæ\n", strlen (my.depgraph), my.depgraph);
   printf ("  depother  : %4då%sæ\n", strlen (my.depother), my.depother);
   printf ("  depalien  : %4då%sæ\n", strlen (my.depalien), my.depalien);
   printf ("  depinpt   : %4då%sæ\n", strlen (my.depinpt ), my.depinpt );
   printf ("  depoutp   : %4då%sæ\n", strlen (my.depoutp ), my.depoutp );
   printf ("  depfile   : %4då%sæ\n", strlen (my.depfile ), my.depfile );
   printf ("  depwtf    : %4då%sæ\n", strlen (my.depwtf  ), my.depwtf  );
   printf ("  depall    : %4då%sæ\n", strlen (my.depall  ), my.depall  );
   /*---(show filen entry)---------------*/
   if (my.depall [0] == '´')  strcpy (my.depall, "");
   x_len = strlen (my.depall);
   /*> if (my.depall [x_len - 1] == ',')  my.depall [--x_len] = '\0';                 <*/
   if (x_len == 0)     printf ("  DEPEND  ´ \n");
   else                printf ("  DEPEND  %s \n", my.depall);
   /*---(add to node)--------------------*/
   GRAPH_deps_add  (a_proj, my.depall);
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
         if (s_incls [i].i_cat == 0)   break;
         if (s_incls [i].i_count <= 0) continue;
         ++x_count;
         x_total += s_incls [i].i_count;
      }
      snprintf (my.unit_answer, LEN_RECD, "INCL count       : %4d count, %4d total, %4d handled", x_count, x_total, s_handled);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



