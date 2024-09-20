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
/*===----                       pre-initialization                     ----===*/
/*====================------------------------------------====================*/
static void      o___PREINIT________o (void) {;}

char
PROG__header            (void)
{
   /*---(log header)---------------------*/
   DEBUG_PROG   yLOG_info     ("purpose"   , P_PURPOSE);
   DEBUG_PROG   yLOG_info     ("namesake"  , P_NAMESAKE);
   DEBUG_PROG   yLOG_info     ("heritage"  , P_HERITAGE);
   DEBUG_PROG   yLOG_info     ("imagery"   , P_IMAGERY);
   DEBUG_PROG   yLOG_info     ("ouroboros" , PROG_version      ());
   /*---(core)---------------------------*/
   DEBUG_PROG   yLOG_note     ("custom core");
   DEBUG_PROG   yLOG_info     ("yLOG"      , yLOGS_version     ());
   DEBUG_PROG   yLOG_info     ("yURG"      , yURG_version      ());
   DEBUG_PROG   yLOG_info     ("ySTR"      , ySTR_version      ());
   DEBUG_PROG   yLOG_info     ("yUNIT"     , yUNIT_version     ());
   /*---(other custom)-------------------*/
   DEBUG_PROG   yLOG_note     ("other custom");
   DEBUG_PROG   yLOG_info     ("ySORT"     , ySORT_version   ());
   DEBUG_PROG   yLOG_info     ("yPARSE"    , yPARSE_version  ());
   DEBUG_PROG   yLOG_info     ("yJOBS"     , yJOBS_version   ());
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_urgents            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(set mute)-----------------------*/
   yURG_all_mute ();
   /*---(start logger)-------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(process urgents)----------------*/
   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(show header)--------------------*/
   rc = PROG__header ();
   DEBUG_PROG   yLOG_value    ("header"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        startup functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___STARTUP_________o () { return; }

char
PROG_reset_yjobs   (void)
{
   my.run_as   = IAM_OUROBOROS;
   my.run_mode = ACT_NONE;
   strcpy (my.run_file, "");
   return 0;
}

char         /*--> shutdown program ----------------------[ ------ [ ------ ]-*/
PROG__init          (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(yJOB config)--------------------*/
   PROG_reset_yjobs ();
   DEBUG_PROG  yLOG_char    ("run_as"    , my.run_as);
   my.run_uid     = getuid ();
   my.run_start   = time (NULL);
   /*---(files)--------------------------*/
   ystrlcpy (my.n_db, "", LEN_PATH);
   my.f_db = NULL;
   my.projs = 0;
   my.units = 0;
   my.scrps = 0;
   my.conds = 0;
   my.steps = 0;
   my.ready = 0;
   my.pass  = 0;
   my.fail  = 0;
   my.badd  = 0;
   my.othr  = 0;
   NODE_init  ();
   EDGE_init  ();
   WAVE_init  ();
   GRAPH_init ();
   INCL_clear ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

#define  TWOARG  if (++i >= a_argc)  yURG_err ("FATAL, %s argument requires an additional string", a, --rc); else 

char               /* PURPOSE : process the command line arguments            */
PROG__args          (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   char       *a           = NULL;
   char       *b           = NULL;          /* next argument                  */
   int         x_total     =    0;
   int         x_args      =    0;
   /*---(begin)--------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(yjobs setup)--------------------*/
   rc = yJOBS_runas (a_argv [0], &(my.run_as), P_FOCUS, P_NICHE, P_SUBJECT, P_PURPOSE, P_NAMESAKE, P_HERITAGE, P_IMAGERY, P_REASON, P_ONELINE, P_HOMEDIR, P_BASENAME, P_FULLPATH, P_SUFFIX, P_CONTENT, P_SYSTEM, P_LANGUAGE, P_CODESIZE, "", P_AUTHOR, P_CREATED, P_VERMAJOR, P_VERMINOR, P_VERNUM, P_VERTXT, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   DEBUG_PROG  yLOG_value   ("runas"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG  yLOG_char    ("run_as"    , my.run_as);
   getcwd (my.n_home, LEN_PATH);
   ystrlcat (my.n_home, "/", LEN_PATH);
   /*---(process)------------------------*/
   /*> printf ("testing %d\n", a_argc);                                               <*/
   for (i = 1; i < a_argc; ++i) {
      /*---(arguement)-------------------*/
      a = a_argv[i];
      /*> printf ("a = [%s]\n", a);                                                   <*/
      ++x_total;
      /*---(filter urgents)--------------*/
      if (a[0] == '@')  continue;
      DEBUG_ARGS  yLOG_info    ("cli arg", a);
      ++x_args;
      /*---(potential two-arg)-----------*/
      if (i < a_argc - 1)  b = a_argv [i + 1];
      else                 b = NULL;
      /*---(yjobs standards)-------------*/
      if (strstr (" --verify --cverify --vverify --local --clocal --vlocal --registir --cregister --vregister --update --cupdate --vupdate --install --cinstall --vinstall ", a) != NULL) {
         b = my.n_home;
      }
      rc = yJOBS_argument (&i, a, b, &(my.run_as), &(my.run_mode), my.run_file);
      DEBUG_ARGS  yLOG_value   ("yJOBS"  , rc);
      /*> if (rc < 0) {                                                               <* 
       *>    DEBUG_PROG  yLOG_exitr (__FUNCTION__, rce);                              <* 
       *>    return rce;                                                              <* 
       *> }                                                                           <*/
      if (rc == 1)  continue;
      /*---(configuration)---------------*/
      if      (strcmp (a, "--db"        ) == 0)  TWOARG rc = ystrlfile  ("--db", my.n_db, a_argv [i], "db", LEN_PATH);
      /*---(major actions)---------------*/
      else if (strcmp (a, "--here"      ) == 0)  my.run_mode = RUN_HERE;
      else if (strcmp (a, "--purge"     ) == 0)  my.run_mode = RUN_PURGE;
      else if (strcmp (a, "--create"    ) == 0)  my.run_mode = RUN_CREATE;
      else if (strcmp (a, "--update"    ) == 0)  my.run_mode = RUN_UPDATE;
      else if (strcmp (a, "--remove"    ) == 0)  my.run_mode = RUN_REMOVE;
      /*---(reporting)-------------------*/
      else if (strcmp (a, "--dump"      ) == 0)  my.run_mode = RUN_DUMP;
      else if (strcmp (a, "--list"      ) == 0)  my.run_mode = RUN_LIST;
      else if (strcmp (a, "--seq"       ) == 0)  my.run_mode = RUN_SEQ;
      /*---(unknown)---------------------*/
      else                                       rc = rce;
      /*---(fall-out)--------------------*/
      if (rc < 0)  break;
      /*---(done)------------------------*/
   }
   DEBUG_ARGS  yLOG_value  ("entries"   , x_total);
   DEBUG_ARGS  yLOG_value  ("arguments" , x_args);
   if (x_args == 0) {
      DEBUG_ARGS  yLOG_note   ("no arguments identified");
   }
   /*---(finalize)-----------------------*/
   yJOBS_final (my.run_uid);
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return rc;
}

char
PROG__begin         (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(file names)---------------------*/
   if (strcmp (my.n_db, "") == 0)  ystrlcpy (my.n_db, F_DB, LEN_PATH);
   /*---(prepare)------------------------*/
   RPTG_clear ();
   my.wave_min = 'è';
   my.wave_max = 'è';
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv [])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = PROG__init   ();
   DEBUG_PROG   yLOG_value    ("init"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(arguments)----------------------*/
   rc = PROG__args   (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("args"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(begin)--------------------------*/
   rc = PROG__begin  ();
   DEBUG_PROG   yLOG_value    ("begin"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr    (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                      runtime driver                          ----===*/
/*====================------------------------------------====================*/
static void  o___RUNTIME_________o () { return; }

char
PROG_driver             (void)
{
   switch (my.run_mode) {
   case RUN_HERE   :
      /*> WAVE_here     ();                                                           <*/
      break;
   case RUN_PURGE  :
      /*> DB_write      ();                                                           <*/
      break;
   case RUN_CREATE :
      /*> WAVE_here     ();                                                           <*/
      /*> DB_write      ();                                                           <*/
      break;
   case RUN_UPDATE :
      /*> DB_read       ();                                                           <*/
      /*> WAVE_here     ();                                                           <*/
      /*> DB_write      ();                                                           <*/
      break;
   case RUN_SEQ    :
      /*> DB_read       ();                                                           <*/
      /*> RPTG_heading  ();                                                           <*/
      /*> RPTG_lines    ();                                                           <*/
      break;
   case RUN_DUMP   :
      /*> DB_read       ();                                                           <*/
      /*> RPTG_dump     ();                                                           <*/
      break;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        wrapup functions                      ----===*/
/*====================------------------------------------====================*/
static void  o___WRAPUP__________o () { return; }

char                /* PURPOSE : shutdown program and free memory ------------*/
PROG__end           (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   WAVE_wrap ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_shutdown      (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(normal sequence)----------------*/
   if (rc >= 0)  rc = PROG__end  ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
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
   rc = PROG_urgents (x_argc, x_argv);
   rc = PROG_startup (x_argc, x_argv);
   /*---(complete)-----------------------*/
   return rc;
}

char       /*----: set up programgents/debugging -----------------------------*/
PROG__unit_loud    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_argc      = 5;
   char       *x_argv [5]  = { "ouroboros_unit", "@@kitchen" , "@@yjobs" , "@@yparse", "@@yascii" };
   /*---(run)----------------------------*/
   rc = PROG_urgents (x_argc, x_argv);
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





