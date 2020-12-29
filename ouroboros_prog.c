/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



tGLOBALS    my;



/*====================------------------------------------====================*/
/*===----                        identipy functions                    ----===*/
/*====================------------------------------------====================*/
static void  o___IDENTITY________o () { return; }


char*      /* ---- : return library versioning information -------------------*/
PROG_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __CBANG__  > 0
   strncpy (t, "[cbang      ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (my.version, LEN_FULL, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return my.version;
}



/*====================------------------------------------====================*/
/*===----                        startup functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___STARTUP_________o () { return; }

char         /*--> shutdown program ----------------------[ ------ [ ------ ]-*/
PROG__init          (void)
{
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(files)--------------------------*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char               /* PURPOSE : process the command line arguments            */
PROG__args          (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char       *a           = NULL;
   int         x_total     =    0;
   int         x_args      =    0;
   /*---(begin)--------------------------*/
   DEBUG_TOPS  yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   for (i = 1; i < a_argc; ++i) {
      a = a_argv[i];
      ++x_total;
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      ++x_args;
      /*> if      (strncmp (a, "--create"     , 10) == 0)    my.run_type = G_RUN_CREATE;                                                                                    <* 
       *> else if (strncmp (a, "--compile"    , 10) == 0)    my.run_type = G_RUN_CREATE;                                                                                    <* 
       *> else if (strncmp (a, "--debug"      , 10) == 0)    my.run_type = G_RUN_DEBUG;                                                                                     <* 
       *> else if (strncmp (a, "--convert"    , 10) == 0)    my.run_type = G_RUN_UPDATE;                                                                                    <* 
       *> else if (strncmp (a, "--update"     , 10) == 0)  { my.run_type = G_RUN_UPDATE;  my.replace = G_RUN_REPLACE; }                                                     <* 
       *> else if (strncmp (a, "-"            ,  1) == 0)  { printf ("FATAL, arg <<%s>> not understood\n", a); DEBUG_TOPS  yLOG_exitr  (__FUNCTION__, rce); return rce; }   <* 
       *> else {                                                                                                                                                            <* 
       *>    rc = PROG_file (a);                                                                                                                                            <* 
       *>    if (rc < 0) {                                                                                                                                                  <* 
       *>       DEBUG_TOPS  yLOG_exitr  (__FUNCTION__, rce);                                                                                                                <* 
       *>    }                                                                                                                                                              <* 
       *> }                                                                                                                                                                 <*/
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*---(complete)-----------------------*/
   DEBUG_TOPS  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG__begin         (void)
{
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(file names)---------------------*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_startup       (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(normal sequence)----------------*/
   if (rc >= 0)  rc = yURG_logger  (a_argc, a_argv);
   if (rc >= 0)  rc = PROG__init   ();
   if (rc >= 0)  rc = yURG_urgs    (a_argc, a_argv);
   if (rc >= 0)  rc = PROG__args   (a_argc, a_argv);
   if (rc >= 0)  rc = PROG__begin  ();
   /*---(complete)-----------------------*/
   return rc;
}

char
PROG_final         (void)
{
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(file names)---------------------*/
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        wrapup functions                      ----===*/
/*====================------------------------------------====================*/
static void  o___WRAPUP__________o () { return; }

char                /* PURPOSE : shutdown program and free memory ------------*/
PROG__end           (void)
{
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_shutdown      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_TOPS   yLOG_enter   (__FUNCTION__);
   /*---(normal sequence)----------------*/
   if (rc >= 0)  rc = PROG__end  ();
   /*---(complete)-----------------------*/
   DEBUG_TOPS   yLOG_exit    (__FUNCTION__);
   yLOGS_end     ();
   return rc;
}



/*====================------------------------------------====================*/
/*===----                          unit testing                        ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char       /*----: set up programgents/debugging -----------------------------*/
PROG__unit_quiet   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_argc      =    1;
   char       *x_argv [1]  = { "ouroboros" };
   /*---(run)----------------------------*/
   rc = PROG_startup (x_argc, x_argv);
   /*---(complete)-----------------------*/
   return rc;
}

char       /*----: set up programgents/debugging -----------------------------*/
PROG__unit_loud    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_argc      = 2;
   char       *x_argv [2]  = { "ouroboros_unit", "@@kitchen" };
   /*---(run)----------------------------*/
   rc = PROG_startup (x_argc, x_argv);
   /*---(complete)-----------------------*/
   return rc;
}

char       /*----: set up program urgents/debugging --------------------------*/
PROG__unit_end     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(run)----------------------------*/
   rc = PROG_shutdown  ();
   /*---(complete)-----------------------*/
   return rc;
}





