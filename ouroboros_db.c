/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



/*====================------------------------------------====================*/
/*===----                      file control                            ----===*/
/*====================------------------------------------====================*/
static void  o___FILES___________o () { return; }

char
DB__open                (char a_mode, int *a_projs, int *a_units, int *a_scrps, int *a_conds, int *a_steps)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_mode      [LEN_TERSE] = "";
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_FILE   yLOG_point   ("my.f_db"   , my.f_db);
   --rce;  if (my.f_db != NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set mode)-----------------------*/
   DEBUG_FILE   yLOG_char    ("a_mode"    , a_mode);
   --rce;  switch (a_mode) {
   case 'r' :
      strlcpy (x_mode, "rb", LEN_TERSE);
      break;
   case 'w' :
      strlcpy (x_mode, "wb", LEN_TERSE);
      break;
   default  :
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_FILE   yLOG_info    ("x_mode"    , x_mode);
   /*---(open)---------------------------*/
   DEBUG_FILE   yLOG_info    ("my.n_db"   , my.n_db);
   my.f_db = fopen (my.n_db, x_mode);
   DEBUG_FILE   yLOG_point   ("my.f_db"   , my.f_db);
   --rce;  if (my.f_db == NULL) {
      DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(project count)------------------*/
   switch (a_mode) {
   case 'r' :
      rc = fread  (&n, sizeof (int), 1, my.f_db);
      --rce;  if (rc < 1)  {
         DB__close ();
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_FILE   yLOG_value   ("a_projs"   , n);
      if (a_projs != NULL)  *a_projs = n;
      rc = fread  (&n, sizeof (int), 1, my.f_db);
      --rce;  if (rc < 1)  {
         DB__close ();
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_FILE   yLOG_value   ("a_units"   , n);
      if (a_units != NULL)  *a_units = n;
      rc = fread  (&n, sizeof (int), 1, my.f_db);
      --rce;  if (rc < 1)  {
         DB__close ();
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_FILE   yLOG_value   ("a_scrps"   , n);
      if (a_scrps != NULL)  *a_scrps = n;
      rc = fread  (&n, sizeof (int), 1, my.f_db);
      --rce;  if (rc < 1)  {
         DB__close ();
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_FILE   yLOG_value   ("a_conds"   , n);
      if (a_conds != NULL)  *a_conds = n;
      rc = fread  (&n, sizeof (int), 1, my.f_db);
      --rce;  if (rc < 1)  {
         DB__close ();
         DEBUG_FILE   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_FILE   yLOG_value   ("a_steps"   , n);
      if (a_steps != NULL)  *a_steps = n;
      break;
   case 'w' :
      if (a_projs != NULL)   n = *(a_projs);
      else                   n = 0;
      DEBUG_FILE   yLOG_value   ("a_projs"   , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      if (a_units != NULL)   n = *(a_units);
      else                   n = 0;
      DEBUG_FILE   yLOG_value   ("a_units"   , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      if (a_scrps != NULL)   n = *(a_scrps);
      else                   n = 0;
      DEBUG_FILE   yLOG_value   ("a_scrps"   , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      if (a_conds != NULL)   n = *(a_conds);
      else                   n = 0;
      DEBUG_FILE   yLOG_value   ("a_conds"   , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      if (a_steps != NULL)   n = *(a_steps);
      else                   n = 0;
      DEBUG_FILE   yLOG_value   ("a_steps"   , n);
      fwrite (&n, sizeof (int), 1, my.f_db);
      break;
   }
   DEBUG_FILE   yLOG_value   ("n"         , n);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
DB__close               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_INPT   yLOG_info    ("my.n_db"   , my.n_db);
   DEBUG_INPT   yLOG_point   ("my.f_db"   , my.f_db);
   --rce;  if (my.f_db == NULL)  return rce;
   /*---(close)--------------------------*/
   DEBUG_INPT   yLOG_info    ("my.n_db"   , my.n_db);
   rc = fclose (my.f_db);
   DEBUG_OUTP   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0)  return rce; 
   /*---(ground pointer)-----------------*/
   my.f_db = NULL;
   DEBUG_INPT   yLOG_point   ("my.f_db"   , my.f_db);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

int          /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
DB_write              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tWAVE      *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_OUTP   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = DB__open ('w', &my.projs, &my.units, &my.scrps, &my.conds, &my.steps);
   DEBUG_OUTP   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("my.scrps"  , my.scrps);
   /*---(prepare)------------------------*/
   x_curr = g_head;
   /*---(walk projects)------------------*/
   while (x_curr != NULL) {
      /*---(write)-----------------------*/
      DEBUG_OUTP   yLOG_info    ("x_curr"    , x_curr->desc);
      fwrite (x_curr  , sizeof (tWAVE), 1, my.f_db);
      ++c;
      /*---(next)------------------------*/
      x_curr = x_curr->s_next;
   }
   /*---(close)--------------------------*/
   rc = DB__close ();
   DEBUG_OUTP   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(trouble)------------------------*/
   DEBUG_INPT   yLOG_value   ("my.scrps"  , my.scrps);
   DEBUG_INPT   yLOG_value   ("c"         , c);
   --rce;  if (my.scrps != c) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP   yLOG_exit    (__FUNCTION__);
   return c;
}

int          /*===[[ write binary file ]]=================[ ------ [ ------ ]=*/
DB_read               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   int         i           =    0;
   tWAVE      *x_wave      = NULL;
   int         c           =    0;
   tWAVE      *x_next      = NULL;
   tWAVE      *x_prev      = NULL;
   int         x_scrps     =    0;
   int         x_conds     =    0;
   int         x_steps     =    0;
   /*---(header)-------------------------*/
   DEBUG_INPT   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = DB__open ('r', &my.projs, &my.units, &x_scrps, &x_conds, &x_steps);
   DEBUG_OUTP   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_OUTP   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_INPT   yLOG_value   ("my.scrps"  , my.scrps);
   /*---(walk projects)------------------*/
   for (i = 0; i < x_scrps; ++i) {
      /*---(allocate)-----------------------*/
      rc = WAVE_force (&x_wave);
      DEBUG_INPT   yLOG_point   ("alloc"     , x_wave);
      --rce;  if (x_wave == NULL) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      x_next = x_wave->s_next;
      x_prev = x_wave->s_prev;
      /*---(read)---------------------------*/
      rc = fread  (x_wave, sizeof (tWAVE), 1, my.f_db);
      DEBUG_INPT   yLOG_value   ("fread"     , rc);
      if (rc < 1) {
         DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      DEBUG_INPT   yLOG_info    ("desc"      , x_wave->desc);
      /*---(fix pointers)-------------------*/
      x_wave->s_next = x_next;
      x_wave->s_prev = x_prev;
      /*---(totals)-------------------------*/
      my.conds += x_wave->cond;
      my.steps += x_wave->test;
      if (x_wave->ready == 'y')  ++my.ready;
      my.pass  += x_wave->pass;
      my.fail  += x_wave->fail;
      my.badd  += x_wave->badd;
      my.othr  += x_wave->othr;
      /*---(counter)------------------------*/
      ++c;
      /*---(done)---------------------------*/
   }
   /*---(close)--------------------------*/
   rc = DB__close ();
   DEBUG_INPT   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(trouble)------------------------*/
   DEBUG_INPT   yLOG_value   ("my.scrps"  , my.scrps);
   DEBUG_INPT   yLOG_value   ("c"         , c);
   --rce;  if (my.scrps != c) {
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_INPT   yLOG_exit    (__FUNCTION__);
   return c;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*            /*--> unit test accessor ------------------------------*/
DB__unit                (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_cur       = NULL;
   /*---(prepare)------------------------*/
   strlcpy  (my.unit_answer, "DB               : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "stats"         )  == 0) {
      snprintf (my.unit_answer, LEN_RECD, "DB stats         : %5dp, %5du, %5ds, %5dc, %5ds    %5dr, %5dp, %5df, %5db, %5do",
            my.projs, my.units, my.scrps, my.conds, my.steps, my.ready, my.pass, my.fail, my.badd, my.othr);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}



