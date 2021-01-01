/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"




/*
 *  0) read in master.unit entries for stage/wave
 *
 *  1) take in all *.wave files
 *  2) execute as requested
 *  3) report out
 *
 *
 *
 *
 */


tWAVE     *g_head   = NULL;
tWAVE     *g_tail   = NULL;
int        g_curr   = 0;



#define      OURU_WAVE     0
#define      OURU_STAGE    1
#define      OURU_UNIT     2
#define      OURU_SCRP     3
#define      OURU_DESC     4



static   char        s_recd      [LEN_RECD]  = "";
static   char        s_wave      =  '-';
static   char        s_stage     =    0;
static   char        s_unit      [LEN_DESC]  = "";
static   char        s_scrp      =    0;
static   char        s_desc      [LEN_HUND]  = "";



/*====================------------------------------------====================*/
/*===----                        simple support                        ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
WAVE__wipe              (tWAVE *a_dst, char a_new)
{
   if (a_dst == NULL)  return -1;
   DEBUG_DATA   yLOG_snote   ("wipe");
   /*---(basic)----------------*/
   a_dst->wave     =  '-';
   a_dst->stage    =    0;
   a_dst->path [0] = '\0';
   a_dst->unit [0] = '\0';
   a_dst->scrp     =    0;
   a_dst->desc [0] = '\0';
   a_dst->key  [0] = '\0';
   /*---(statistics)-----------*/
   a_dst->cond     =    0;
   a_dst->test     =    0;
   /*---(results)--------------*/
   a_dst->ready    =  '-';
   a_dst->resu     =    0;
   a_dst->pass     =    0;
   a_dst->fail     =    0;
   a_dst->badd     =    0;
   a_dst->othr     =    0;
   /*---(links)----------------*/
   a_dst->s_next   = NULL;
   a_dst->s_prev   = NULL;
   /*---(done)-----------------*/
   return 1;
}

char
WAVE__verify            (char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc, char *a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tWAVE      *x_old       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_schar   (a_stage);
   --rce;  if (strchr (LTRS_GREEK, a_wave) == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_sint    (a_stage);
   --rce;  if (a_stage < 1 || a_stage > 9) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_unit);
   --rce;  if (a_unit == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_sint    (a_scrp);
   --rce;  if (a_scrp < 1 || a_scrp > 99) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (a_desc);
   --rce;  if (a_desc == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for existing)-------------*/
   sprintf (a_key, "%c.%d.%s.%d", a_wave, a_stage, a_unit, a_scrp);
   WAVE_by_name (&x_old, a_key);
   DEBUG_DATA   yLOG_spoint  (x_old);
   --rce;  if (x_old != NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
WAVE__hook              (tWAVE *a_new)
{
   /*---(into linked list)---------------*/
   DEBUG_DATA   yLOG_point   ("head"      , g_head);
   DEBUG_DATA   yLOG_point   ("tail"      , g_tail);
   if (g_head  == NULL) {
      DEBUG_DATA   yLOG_note    ("first");
      g_head  = g_tail  = a_new;
   } else {
      DEBUG_DATA   yLOG_note    ("append");
      a_new->s_prev   = g_tail;
      g_tail->s_next  = a_new;
      g_tail          = a_new;
   }
   /*---(update counter)-----------------*/
   ++my.scrps;
   /*---(complete)-----------------------*/
   return 0;
}

char
WAVE__populate          (tWAVE *a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc, char *a_key)
{
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   /*---(populate)-----------------------*/
   a_new->wave  = a_wave;
   a_new->stage = a_stage;
   strlcpy (a_new->path, my.path, LEN_PATH);
   strlcpy (a_new->unit, a_unit , LEN_TITLE);
   a_new->scrp  = a_scrp;
   strlcpy (a_new->desc, a_desc , LEN_DESC);
   strlcpy (a_new->key , a_key  , LEN_HUND);
   RPTG_spread (a_wave, a_stage);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
WAVE__unhook            (tWAVE *a_old)
{
   /*---(out of linked list)-------------*/
   DEBUG_DATA   yLOG_spoint  (g_head);
   DEBUG_DATA   yLOG_spoint  (g_tail);
   DEBUG_DATA   yLOG_note    ("unlink");
   if (a_old->s_next != NULL)  a_old->s_next->s_prev = a_old->s_prev;
   else                        g_tail                = a_old->s_prev;
   if (a_old->s_prev != NULL)  a_old->s_prev->s_next = a_old->s_next;
   else                        g_head                = a_old->s_next;
   /*---(update counter)-----------------*/
   --my.scrps;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       memory allccation                      ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
WAVE__new               (tWAVE **a_new, char a_force)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWAVE      *x_new       = NULL;
   int         x_tries     =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(default return)-----------------*/
   DEBUG_DATA   yLOG_spoint  (a_new);
   --rce;  if (a_new != NULL)  {
      if (*a_new != NULL && a_force != 'y') {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      *a_new = NULL;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tWAVE *)  malloc (sizeof (tWAVE));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_sint    (x_tries);
   DEBUG_DATA   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   WAVE__wipe (x_new, 'y');
   /*---(into linked list)---------------*/
   rc = WAVE__hook (x_new);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save return)--------------------*/
   if (a_new != NULL)  *a_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char WAVE_new      (tWAVE **a_new) { return WAVE__new (a_new, '-'); }
char WAVE_force    (tWAVE **a_new) { return WAVE__new (a_new, 'y'); }

char
WAVE_populate           (tWAVE *a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_key       [LEN_HUND]  = "";
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   rc = WAVE__verify (a_wave, a_stage, a_unit, a_scrp, a_desc, x_key);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   rc = WAVE__populate (a_new, a_wave, a_stage, a_unit, a_scrp, a_desc, x_key);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
WAVE_results            (tWAVE *x_wave, uchar a_resu, int a_cond, int a_test, int a_pass, int a_fail, int a_badd, int a_othr)
{
   x_wave->resu = a_resu;
   x_wave->cond = a_cond;
   x_wave->test = a_test;
   x_wave->pass = a_pass;
   x_wave->fail = a_fail;
   x_wave->badd = a_badd;
   x_wave->othr = a_othr;
   return 0;
}

char
WAVE_free               (tWAVE **a_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_old);
   --rce;  if (a_old == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_spoint  (*a_old);
   --rce;  if (*a_old == NULL) {
      DEBUG_DATA   yLOG_snote   ("never set");
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(out of linked list)-------------*/
   rc = WAVE__unhook (*a_old);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and return)---------------*/
   WAVE__wipe (*a_old, '-');
   free (*a_old);
   *a_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;

}

char
WAVE_purge              (void)
{
   tWAVE      *x_cur       = NULL;
   tWAVE      *x_next      = NULL;
   x_cur = g_head;
   while (x_cur != NULL) {
      x_next = x_cur->s_next;
      WAVE_free (&x_cur);
      x_cur = x_next;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     searching and finding                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char
WAVE_by_index            (tWAVE **a_cur, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_cur);
   --rce;  if (a_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   *a_cur = NULL;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_sint    (n);
   --rce;  if (n < 0 || n >= my.scrps) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   x_cur = g_head;
   while (x_cur != NULL) {
      if (n == c) {
         DEBUG_DATA   yLOG_snote   ("FOUND");
         *a_cur = x_cur;
         DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      x_cur = x_cur->s_next;
      ++c;
   }
   /*---(no match)-----------------------*/
   DEBUG_DATA   yLOG_snote   ("no match");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char
WAVE_by_cursor           (tWAVE **a_cur, char a_move)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(set current)--------------------*/
   DEBUG_DATA   yLOG_spoint  (a_cur);
   if (a_cur != NULL)   x_cur = *a_cur;
   if (x_cur == NULL)   x_cur = g_head;
   /*---(check start)--------------------*/
   DEBUG_DATA   yLOG_spoint  (x_cur);
   --rce;  if (x_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(move)---------------------------*/
   DEBUG_DATA   yLOG_schar   (a_move);
   --rce;  switch (a_move) {
   case '[' :   x_cur = g_head;               break;
   case '<' :   x_cur = x_cur->s_prev;        break;
   case '.' :   x_cur = x_cur;                break;
   case '>' :   x_cur = x_cur->s_next;        break;
   case ']' :   x_cur = g_tail;               break;
   default  :
                DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
                return rce;
   }
   /*---(check end)----------------------*/
   DEBUG_DATA   yLOG_spoint  (x_cur);
   --rce;  if (x_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   *a_cur = x_cur;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
WAVE_by_name             (tWAVE **a_cur, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_spoint  (a_cur);
   --rce;  if (a_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   *a_cur = NULL;
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_snote   (a_name);
   /*---(walk)---------------------------*/
   x_cur = g_head;
   while (x_cur != NULL) {
      if (x_cur->key != NULL && strcmp (a_name, x_cur->key) == 0) {
         DEBUG_DATA   yLOG_snote   ("FOUND");
         *a_cur = x_cur;
         DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      x_cur = x_cur->s_next;
      ++c;
   }
   /*---(no match)-----------------------*/
   DEBUG_DATA   yLOG_snote   ("no match");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}



/*====================------------------------------------====================*/
/*===----                       data import                            ----===*/
/*====================------------------------------------====================*/
static void  o___IMPORT__________o () { return; }

char
WAVE_parse              (char *a_recd, char a_call)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   int         i           =    0;
   char       *p           = NULL;
   char       *q           = "";
   char       *r           = NULL;
   char        t           [LEN_RECD]  = "";
   tWAVE      *x_wave      = NULL;
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   s_wave  = '-';
   s_stage =  0;
   strlcpy (s_unit , "", LEN_DESC);
   s_scrp  =  0;
   strlcpy (s_desc , "", LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_recd"    , a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_info    ("a_recd"    , a_recd);
   c = strldcnt (a_recd, '', LEN_RECD);
   DEBUG_ENVI   yLOG_value   ("c"         , c);
   --rce;  if (c < 4) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (t, a_recd, LEN_RECD);
   p = strtok_r (t, q, &r);
   c = 0;
   /*---(walk fields)--------------------*/
   --rce;  for (i = 0; i < 5; ++i) {
      DEBUG_INPT   yLOG_point   ("p"         , p);
      if (p == NULL) {
         DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      strltrim (p, ySTR_BOTH, LEN_RECD);
      DEBUG_INPT   yLOG_info    ("p"         , p);
      /*---(handle fields)---------------*/
      switch (i) {
      case OURU_WAVE  :
         s_wave  = p [0];
         DEBUG_INPT   yLOG_char    ("s_wave"    , s_wave);
         break;
      case OURU_STAGE :
         s_stage = atoi (p);
         DEBUG_INPT   yLOG_char    ("s_stage"   , s_stage);
         break;
      case OURU_UNIT  :
         strlcpy (s_unit, p, LEN_DESC);
         DEBUG_INPT   yLOG_info    ("s_unit"    , s_unit);
         break;
      case OURU_SCRP  :
         s_scrp  = atoi (p);
         DEBUG_INPT   yLOG_char    ("s_scrp"    , s_scrp);
         break;
      case OURU_DESC  :
         strlcpy (s_desc, p, LEN_HUND);
         DEBUG_INPT   yLOG_info    ("s_desc"    , s_desc);
         break;
      }
      /*---(next record)-----------------*/
      p = strtok_r (NULL  , q, &r);
      ++c;
   } 
   /*---(call new)-----------------------*/
   DEBUG_ENVI   yLOG_value   ("c"         , c);
   DEBUG_ENVI   yLOG_char    ("a_call"    , a_call);
   if (a_call == 'y') {
      WAVE_new      (&x_wave);
      WAVE_populate (x_wave, s_wave, s_stage, s_unit, s_scrp, s_desc);
   }
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_read               (char *a_name, char a_call)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   FILE       *f           = NULL;
   int         l           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_info    ("a_name"    , a_name);
   /*---(open to read)-------------------*/
   f = fopen (a_name, "rt");
   DEBUG_ENVI   yLOG_point   ("f"         , f);
   --rce;  if (f == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk entries)-------------------*/
   --rce; while (1) {
      fgets (s_recd, LEN_RECD, f);
      if (feof (f))  {
         DEBUG_ENVI   yLOG_note    ("end-of-file");
         break;
      }
      if (s_recd [0] == '#' )  continue;
      if (s_recd [0] == '\0')  continue;
      /*---(trim newline)----------------*/
      l = strlen (s_recd);
      if (l <= 0)              continue;
      s_recd [--l] = '\0';
      /*---(call parse)------------------*/
      ++c;
      if (a_call == 'y')  WAVE_parse (s_recd, a_call);
   }
   /*---(close reading)------------------*/
   rc = fclose (f);
   --rce;  if (rc != 0) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update globals)-----------------*/
   ++my.units;
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_inventory          (char *a_path, char a_call)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   DIR        *x_dir       = NULL;          /* directory pointer              */
   tDIRENT    *x_entry     = NULL;          /* directory entry                */
   char        x_name      [LEN_PATH]  = "";
   /*---(header)-------------------------*/
   DEBUG_ENVI   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_ENVI   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_ENVI   yLOG_info    ("a_path"    , a_path);
   /*---(open directory)-----------------*/
   x_dir = opendir (a_path);
   DEBUG_ENVI   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (my.path, a_path, LEN_PATH);
   RPTG_clear ();
   my.wave_min = 'è';
   my.wave_max = 'è';
   /*---(walk entries)-------------------*/
   --rce; while (1) {
      /*---(read)------------------------*/
      x_entry = readdir (x_dir);
      DEBUG_ENVI   yLOG_point   ("X_ENTRY"   , x_entry);
      if (x_entry == NULL)                            break;
      /*---(filter)----------------------*/
      if (x_entry->d_name   == NULL)                  continue;
      DEBUG_ENVI   yLOG_info    ("d_name"    , x_entry->d_name);
      if (strcmp (x_entry->d_name, "."    ) == 0)     continue;
      if (strcmp (x_entry->d_name, ".."   ) == 0)     continue;
      if (strstr (x_entry->d_name, ".wave") == NULL)  continue;
      /*---(process)---------------------*/
      ++c;
      sprintf (x_name, "%s/%s", a_path, x_entry->d_name);
      /*> printf ("%s\n", x_name);                                                    <*/
      if (a_call == 'y')  WAVE_read (x_name, a_call);
      /*---(done)------------------------*/
   }
   /*---(close)--------------------------*/
   closedir (x_dir);
   /*---(sort)---------------------------*/
   WAVE_gnome ();
   /*> rc = ySORT_troll (YSORT_NONE, YSORT_ASCEND, &(a_parent->c_head), &(a_parent->c_tail));   <*/
   /*---(update globals)-----------------*/
   ++my.projs;
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_here               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   int         x_len       =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(get the home)-------------------*/
   p = getcwd (my.path, LEN_HUND);
   DEBUG_DATA   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*> printf ("%s\n", my.path);                                                       <*/
   DEBUG_DATA   yLOG_snote   (my.path);
   x_len = strlen (my.path);
   DEBUG_DATA   yLOG_sint    (x_len);
   /*---(run inventory)------------------*/
   c = WAVE_inventory (my.path, 'y');
   /*---(complete)-----------------------*/
   DEBUG_ENVI   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                          sorting                             ----===*/
/*====================------------------------------------====================*/
static void  o___SORT____________o () { return; }

static  s_swaps      = 0;
static  s_comps      = 0;
static  s_teles      = 0;

char
WAVE_swap               (tWAVE *a_one, tWAVE *a_two)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   /*---(beginning)----------------------*/
   DEBUG_SORT   yLOG_senter  (__FUNCTION__);
   DEBUG_SORT   yLOG_spoint  (a_one);
   --rce;  if (a_one == NULL) {
      DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_SORT   yLOG_spoint  (a_two);
   --rce;  if (a_two == NULL) {
      DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_one == a_two) {
      DEBUG_SORT   yLOG_snote   ("same, no action");
      DEBUG_SORT   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(cut two from list)--------------*/
   DEBUG_SORT   yLOG_snote   ("unlink");
   if (a_two->s_next != NULL)   a_two->s_next->s_prev = a_two->s_prev;
   else                         g_tail                = a_two->s_prev;
   if (a_two->s_prev != NULL)   a_two->s_prev->s_next = a_two->s_next;
   else                         g_head                = a_two->s_next;
   /*---(insert before one)--------------*/
   DEBUG_SORT   yLOG_snote   ("insert");
   if (a_one->s_prev != NULL)   a_one->s_prev->s_next = a_two;
   else                         g_head                = a_two;
   a_two->s_prev = a_one->s_prev;
   a_two->s_next = a_one;
   a_one->s_prev = a_two;
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
WAVE_gnome              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         n           =   -1;
   int         x_match     =    0;
   char        x_flag      =  '-';
   tWAVE      *p           = NULL;          /* main index                     */
   tWAVE      *t           = NULL;          /* teleport point                 */
   tWAVE      *o           = NULL;          /* origin point                   */
   char        x_swap      =  '-';
   /*---(header)-------------------------*/
   DEBUG_SORT   yLOG_enter   (__FUNCTION__);
   /*---(check list)---------------------*/
   DEBUG_SORT   yLOG_point   ("head"      , g_head);
   --rce;  if (g_head == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   DEBUG_SORT   yLOG_point   ("->next"    , g_head->s_next);
   --rce;  if (g_head->s_next == NULL) {
      DEBUG_SORT   yLOG_exitr   (__FUNCTION__, rce);
      return 0;
   }
   /*---(prepare)------------------------*/
   s_swaps = 0;
   s_comps = 0;
   s_teles = 0;
   o   = g_head->s_next;
   if (o != NULL) {
      p = o->s_prev;
      t = o->s_next;
   }
   /*---(do the gnome walk)--------------*/
   while (o != NULL) {
      /*---(beginning)-------------------*/
      if (p == NULL) {
         DEBUG_SORT   yLOG_note    ("bounce off beginning");
         if (x_swap == 'y') {
            ++s_swaps;
            WAVE_swap (g_head, o);
            x_swap = '-';
         }
         ++s_teles;
         o = t;
         if (o != NULL) {
            p = o->s_prev;
            t = o->s_next;
         }
         continue;
      }
      /*---(compare)---------------------*/
      ++s_comps;
      x_match = strcmp (p->key, o->key);
      x_flag  = (x_match <= 0) ? 'y' : '#';
      DEBUG_SORT   yLOG_complex ("compare"   , "%-20.20s v %-20.20s   %c %4d   %4d %4d %4d", p->key, o->key, x_flag, x_match, s_comps, s_teles, s_swaps);
      if (x_match <= 0) {
         if (x_swap == 'y') {
            ++s_swaps;
            WAVE_swap (p->s_next, o);
            x_swap = '-';
         }
         ++s_teles;
         o = t;
         if (o != NULL) {
            p = o->s_prev;
            t = o->s_next;
         }
         continue;
      }
      /*---(swap)------------------------*/
      x_swap = 'y';
      p = p->s_prev;
      /*---(next)------------------------*/
   }
   DEBUG_SORT   yLOG_value   ("size"       , my.scrps);
   DEBUG_SORT   yLOG_value   ("compares"   , s_comps);
   DEBUG_SORT   yLOG_value   ("teleports"  , s_teles);
   DEBUG_SORT   yLOG_value   ("swaps"      , s_swaps);
   /*---(complete)-----------------------*/
   DEBUG_SORT   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*            /*--> unit test accessor ------------------------------*/
WAVE__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        s           [LEN_DESC]  = " -[]";
   char        t           [LEN_HUND]  = " -[]";
   tWAVE      *x_cur       = NULL;
   /*---(prepare)------------------------*/
   strlcpy  (my.unit_answer, "WAVE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "parse"         )  == 0) {
      sprintf (s, "%2d[%.20s]", strlen (s_unit), s_unit);
      sprintf (t, "%2d[%.40s]", strlen (s_desc), s_desc);
      snprintf (my.unit_answer, LEN_RECD, "WAVE parse       : %c  %d  %-24.24s  %2d  %s",
            s_wave, s_stage, s, s_scrp, t);
   }
   else if (strcmp (a_question, "entry"         )  == 0) {
      WAVE_by_index (&x_cur, n);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "WAVE entry  (%2d) : -  -   -[]                       -   -[]", n);
      } else {
         if (x_cur->unit != NULL)  sprintf (s, "%2d[%.20s]", strlen (x_cur->unit), x_cur->unit);
         if (x_cur->desc != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->desc), x_cur->desc);
         snprintf (my.unit_answer, LEN_RECD, "WAVE entry  (%2d) : %c  %d  %-24.24s  %2d  %s",
               n, x_cur->wave, x_cur->stage, s, x_cur->scrp, t);
      }
   }
   else if (strcmp (a_question, "key"           )  == 0) {
      WAVE_by_index (&x_cur, n);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "WAVE key    (%2d) :  -[]", n);
      } else {
         snprintf (my.unit_answer, LEN_RECD, "WAVE key    (%2d) : %2d[%s]",
               n, strlen (x_cur->key), x_cur->key);
      }
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



