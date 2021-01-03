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


tWAVE     *p_head   = NULL;
tWAVE     *p_tail   = NULL;

tWAVE     *s_head   = NULL;
tWAVE     *s_tail   = NULL;




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
   a_dst->proj [0] = '\0';
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
   a_dst->p_next   = NULL;
   a_dst->p_prev   = NULL;
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
   sprintf (a_key , "%c.%1d.%-20.20s.%02d", a_wave, a_stage, a_unit, a_scrp);
   WAVE_by_sortkey (&x_old, a_key);
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
WAVE__populate          (tWAVE *a_new, char a_wave, char a_stage, char *a_unit, char a_scrp, char *a_desc, char *a_key)
{
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   /*---(populate)-----------------------*/
   a_new->wave  = a_wave;
   a_new->stage = a_stage;
   strlcpy (a_new->path, my.path, LEN_PATH);
   strlcpy (a_new->proj, my.proj, LEN_LABEL);
   strlcpy (a_new->unit, a_unit , LEN_TITLE);
   a_new->scrp  = a_scrp;
   strlcpy (a_new->desc, a_desc , LEN_DESC);
   /*---(sorting)------------------------*/
   sprintf (a_new->sort, "%-15.15s.%-20.20s.%02d", my.proj, a_unit, a_scrp);
   strlcpy (a_new->key , a_key  , LEN_HUND);
   /*---(reporting)----------------------*/
   RPTG_spread (a_wave, a_stage);
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
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
   rc = WAVE__shook (NULL, x_new);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   rc = WAVE__phook (NULL, x_new);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(update counter)-----------------*/
   ++my.scrps;
   /*---(save return)--------------------*/
   if (a_new != NULL)  *a_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 1;
}

char WAVE_new      (tWAVE **a_new) { return WAVE__new (a_new, '-'); }
char WAVE_force    (tWAVE **a_new) { return WAVE__new (a_new, 'y'); }

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
   rc = WAVE__sunhook (*a_old);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   rc = WAVE__punhook (*a_old);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(update counter)-----------------*/
   --my.scrps;
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
   x_cur = s_head;
   while (x_cur != NULL) {
      x_next = x_cur->s_next;
      WAVE_free (&x_cur);
      x_cur = x_next;
   }
   return 0;
}

char
WAVE_purge_by_unit      (char *a_unit)
{
   tWAVE      *x_cur       = NULL;
   tWAVE      *x_next      = NULL;
   int         c           =    0;
   char        x_unit      [LEN_TITLE] = "";
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   strlcpy (x_unit, a_unit, LEN_TITLE);
   DEBUG_DATA   yLOG_complex ("x_unit"    , "%2d[%s]", strlen (x_unit), x_unit);
   x_cur = s_head;
   while (x_cur != NULL) {
      x_next = x_cur->s_next;
      DEBUG_DATA   yLOG_complex ("current"   , "%-10p, %-10p, %2d[%s], %s", x_cur, x_next, strlen (x_cur->unit), x_cur->unit, x_cur->desc);
      if (strcmp (x_unit, x_cur->unit) == 0) {
         WAVE_free (&x_cur);
         ++c;
      }
      x_cur = x_next;
   }
   if (c > 0)  --my.units;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}

char
WAVE_purge_by_path      (char *a_path)
{
   tWAVE      *x_cur       = NULL;
   tWAVE      *x_next      = NULL;
   int         c           =    0;
   char        x_path      [LEN_PATH] = "";
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   strlcpy (x_path, a_path, LEN_PATH);
   DEBUG_DATA   yLOG_info    ("x_path"    , x_path);
   x_cur = s_head;
   while (x_cur != NULL) {
      x_next = x_cur->s_next;
      if (strcmp (x_path, x_cur->path) == 0) {
         c += WAVE_purge_by_unit (x_cur->unit);
         x_cur = x_next = s_head;
      }
      x_cur = x_next;
   }
   if (c > 0)  --my.projs;
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                    hooking and unhooking                     ----===*/
/*====================------------------------------------====================*/
static void  o___HOOKING_________o () { return; }

char
WAVE__shook             (tWAVE *a_ref, tWAVE *a_cur)
{
   /*---(into wave list)-----------------*/
   /*> DEBUG_DATA   yLOG_point   ("head"      , s_head);                              <*/
   /*> DEBUG_DATA   yLOG_point   ("tail"      , s_tail);                              <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   /*---(append normally)---------------*/
   if (a_ref == NULL) {
      if (s_head  == NULL) {
         /*> DEBUG_DATA   yLOG_note    ("first");                                     <*/
         s_head  = s_tail  = a_cur;
      } else {
         /*> DEBUG_DATA   yLOG_note    ("append");                                    <*/
         a_cur->s_prev   = s_tail;
         s_tail->s_next  = a_cur;
         s_tail          = a_cur;
      }
   }
   /*---(insert before ref)--------------*/
   else {
      if (a_ref->s_prev != NULL)   a_ref->s_prev->s_next = a_cur;
      else                         s_head                = a_cur;
      a_cur->s_prev   = a_ref->s_prev;
      a_cur->s_next   = a_ref;
      a_ref->s_prev   = a_cur;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
WAVE__phook             (tWAVE *a_ref, tWAVE *a_cur)
{
   /*---(into project list)--------------*/
   /*> DEBUG_DATA   yLOG_point   ("head"      , p_head);                              <*/
   /*> DEBUG_DATA   yLOG_point   ("tail"      , p_tail);                              <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   /*---(append normally)---------------*/
   if (a_ref == NULL) {
      if (p_head  == NULL) {
         /*> DEBUG_DATA   yLOG_note    ("first");                                     <*/
         p_head  = p_tail  = a_cur;
      } else {
         /*> DEBUG_DATA   yLOG_note    ("append");                                    <*/
         a_cur->p_prev   = p_tail;
         p_tail->p_next  = a_cur;
         p_tail          = a_cur;
      }
   }
   /*---(insert before ref)--------------*/
   else {
      if (a_ref->p_prev != NULL)   a_ref->p_prev->p_next = a_cur;
      else                         p_head                = a_cur;
      a_cur->p_prev   = a_ref->p_prev;
      a_cur->p_next   = a_ref;
      a_ref->p_prev   = a_cur;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
WAVE__sunhook            (tWAVE *a_cur)
{
   /*---(out of linked list)-------------*/
   /*> DEBUG_DATA   yLOG_spoint  (s_head);                                            <*/
   /*> DEBUG_DATA   yLOG_spoint  (s_tail);                                            <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   if (a_cur->s_next != NULL)  a_cur->s_next->s_prev = a_cur->s_prev;
   else                        s_tail                = a_cur->s_prev;
   if (a_cur->s_prev != NULL)  a_cur->s_prev->s_next = a_cur->s_next;
   else                        s_head                = a_cur->s_next;
   /*---(complete)-----------------------*/
   return 0;
}

char
WAVE__punhook            (tWAVE *a_cur)
{
   /*---(out of linked list)-------------*/
   /*> DEBUG_DATA   yLOG_spoint  (p_head);                                            <*/
   /*> DEBUG_DATA   yLOG_spoint  (p_tail);                                            <*/
   /*> DEBUG_DATA   yLOG_snote   (__FUNCTION__);                                      <*/
   if (a_cur->p_next != NULL)  a_cur->p_next->p_prev = a_cur->p_prev;
   else                        p_tail                = a_cur->p_prev;
   if (a_cur->p_prev != NULL)  a_cur->p_prev->p_next = a_cur->p_next;
   else                        p_head                = a_cur->p_next;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      data maintainence                       ----===*/
/*====================------------------------------------====================*/
static void  o___DATA____________o () { return; }

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



/*====================------------------------------------====================*/
/*===----                     searching and finding                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

#define     IF_SCRP   (a_type == 's') ? 

char
WAVE__by_index           (char a_type, tWAVE **a_cur, int n)
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
   x_cur = IF_SCRP  s_head : p_head;
   while (x_cur != NULL) {
      if (n == c) {
         DEBUG_DATA   yLOG_snote   ("FOUND");
         *a_cur = x_cur;
         DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      x_cur = IF_SCRP x_cur->s_next : x_cur->p_next;
      ++c;
   }
   /*---(no match)-----------------------*/
   DEBUG_DATA   yLOG_snote   ("no match");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char WAVE_by_index  (tWAVE **a_cur, int n)  { return  WAVE__by_index ('s', a_cur, n); }
char PROJ_by_index  (tWAVE **a_cur, int n)  { return  WAVE__by_index ('p', a_cur, n); }

char
WAVE__by_cursor          (char a_type, tWAVE **a_cur, char a_move)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_DATA   yLOG_spoint  (a_cur);
   --rce;  if (a_cur == NULL) {
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_cur = *a_cur;
   DEBUG_DATA   yLOG_spoint  (x_cur);
   --rce;  if (x_cur == NULL) {
      /*---(non-bounce)------------------*/
      if (strchr ("Ö´Õ", a_move) != NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      /*---(bounce types)----------------*/
      x_cur = IF_SCRP  s_head : p_head;
      DEBUG_DATA   yLOG_spoint  (x_cur);
      if (x_cur == NULL) {
         DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(move)---------------------------*/
   DEBUG_DATA   yLOG_schar   (a_move);
   --rce;  switch (a_move) {
   case '[' : case 'º' :   /* head         */
      x_cur = IF_SCRP  s_head : p_head;
      break;
   case '<' : case 'Ö' :   /* previous     */
      x_cur = IF_SCRP  x_cur->s_prev : x_cur->p_prev;
      break;
   case '.' : case '´' :   /* current      */
      x_cur = x_cur;
      break;
   case '>' : case 'Õ' :   /* next         */
      x_cur = IF_SCRP  x_cur->s_next : x_cur->p_next;
      break;
   case ']' : case '»' :   /* tail         */
      x_cur = IF_SCRP  s_tail : p_tail;
      break;
   default  :
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check end)----------------------*/
   DEBUG_DATA   yLOG_spoint  (x_cur);
   --rce;  if (x_cur == NULL) {
      /*---(non-bounce)------------------*/
      if (strchr ("ºÖ´Õ»", a_move) != NULL) {
         *a_cur = x_cur;
      }
      /*---(all types)-------------------*/
      DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   *a_cur = x_cur;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char WAVE_by_cursor (tWAVE **a_cur, char a_move)  { return  WAVE__by_cursor ('s', a_cur, a_move); }
char PROJ_by_cursor (tWAVE **a_cur, char a_move)  { return  WAVE__by_cursor ('p', a_cur, a_move); }

char
WAVE__by_sortkey         (char a_type, tWAVE **a_cur, char *a_name)
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
   x_cur = IF_SCRP s_head : p_head;
   while (x_cur != NULL) {
      if (x_cur->key != NULL && x_cur->sort != NULL) {
         if (strcmp (a_name, IF_SCRP x_cur->key : x_cur->sort) == 0) {
            DEBUG_DATA   yLOG_snote   ("FOUND");
            *a_cur = x_cur;
            DEBUG_DATA   yLOG_sexit   (__FUNCTION__);
            return 0;
         }
      }
      x_cur = IF_SCRP x_cur->s_next : x_cur->p_next;
      ++c;
   }
   /*---(no match)-----------------------*/
   DEBUG_DATA   yLOG_snote   ("no match");
   --rce;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char WAVE_by_sortkey (tWAVE **a_cur, char *a_sortkey)  { return  WAVE__by_sortkey ('s', a_cur, a_sortkey); }
char PROJ_by_sortkey (tWAVE **a_cur, char *a_sortkey)  { return  WAVE__by_sortkey ('p', a_cur, a_sortkey); }



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
   strlcpy (my.path, a_path, LEN_PATH);
   DEBUG_ENVI   yLOG_info    ("a_path"    , a_path);
   /*---(get the home)-------------------*/
   rc = strlproj (my.path, my.proj);
   DEBUG_DATA   yLOG_value   ("strlhere"  , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("my.path"   , my.path);
   DEBUG_DATA   yLOG_info    ("my.proj"   , my.proj);
   /*---(open directory)-----------------*/
   x_dir = opendir (a_path);
   DEBUG_ENVI   yLOG_point   ("x_dir"     , x_dir);
   --rce;  if (x_dir == NULL) {
      DEBUG_ENVI   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
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
   /*> WAVE_gnome ();                                                                 <*/
   /*> rc = ySORT_troll (YSORT_NONE, YSORT_ASCEND, &(a_parent->c_head), &(a_parent->c_tail));   <*/
   WAVE_gnome ();
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
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(get the home)-------------------*/
   rc = strlhome (my.path);
   DEBUG_DATA   yLOG_value   ("strlhere"  , rc);
   --rce;  if (rc < 0)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("my.path"   , my.path);
   /*---(clear existing)-----------------*/
   WAVE_purge_by_path (my.path);
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

char
WAVE_schecker            (tWAVE *a_ref, tWAVE *a_cur, uchar a_order)
{
   if (a_ref == NULL)  return 0;
   if (a_cur == NULL)  return 0;
   return strcmp (a_ref->key, a_cur->key);
}

char
WAVE_pchecker            (tWAVE *a_ref, tWAVE *a_cur, uchar a_order)
{
   if (a_ref == NULL)  return 0;
   if (a_cur == NULL)  return 0;
   return strcmp (a_ref->sort, a_cur->sort);
}

char
WAVE_gnome              (void)
{
   ySORT_simple (YSORT_ASCEND, WAVE_by_cursor, WAVE_schecker, WAVE__shook, WAVE__sunhook);
   ySORT_simple (YSORT_ASCEND, PROJ_by_cursor, WAVE_pchecker, WAVE__phook, WAVE__punhook);
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
   char        u           [LEN_HUND]  = " -[]";
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
   else if (strcmp (a_question, "project"       )  == 0) {
      PROJ_by_index (&x_cur, n);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "PROJ entry  (%2d) : -  -   -[]                       -   -[]", n);
      } else {
         if (x_cur->unit != NULL)  sprintf (s, "%2d[%.20s]", strlen (x_cur->unit), x_cur->unit);
         if (x_cur->desc != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->desc), x_cur->desc);
         snprintf (my.unit_answer, LEN_RECD, "PROJ entry  (%2d) : %c  %d  %-24.24s  %2d  %s",
               n, x_cur->wave, x_cur->stage, s, x_cur->scrp, t);
      }
   }
   else if (strcmp (a_question, "sortkey"       )  == 0) {
      WAVE_by_index (&x_cur, n);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "WAVE sortkey(%2d) :  -[]                                 -[]", n);
      } else {
         if (x_cur->key  != NULL)  sprintf (s, "%2d[%.30s]", strlen (x_cur->key ), x_cur->key );
         if (x_cur->sort != NULL)  sprintf (t, "%2d[%.40s]", strlen (x_cur->sort), x_cur->sort);
         snprintf (my.unit_answer, LEN_RECD, "WAVE sortkey(%2d) : %-34.34s  %s",
               n, s, t);
      }
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



