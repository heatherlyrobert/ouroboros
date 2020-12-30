/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



char
TEST_result             (tWAVE *a_cur)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_urun      [LEN_RECD]  = "";
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD]  = "";
   int         l           =    0;
   char       *p           = NULL;
   char       *q           = "=";
   char       *r           = NULL;
   /*---(prepare)------------------------*/
   sprintf (x_urun, "%s/%s.urun", a_cur->path, a_cur->unit);
   strncpy (x_recd, "", LEN_RECD);
   /*---(open file)----------------------*/
   f = fopen (x_urun, "rt");
   --rce;  if (f == NULL)              return rce;
   /*---(read records)-------------------*/
   fgets (x_recd, LEN_RECD, f);
   --rce;  if (feof (f))  return rce;
   fgets (x_recd, LEN_RECD, f);
   --rce;  if (feof (f))  return rce;
   /*---(clean record)-------------------*/
   l = strlen (x_recd);
   if (l > 0 && x_recd [l - 1] == '\n')  x_recd [--l] = '\0';
   /*---(close file)---------------------*/
   fclose (f);
   /*---(cond)---------------------------*/
   p = strtok_r (x_recd, q, &r);
   --rce;  if (p == NULL)  return rce;
   /*---(cond)---------------------------*/
   p = strtok_r (NULL  , q, &r);
   --rce;  if (p == NULL)  return rce;
   p [5] = '\0';
   a_cur->cond = atoi (p);
   /*---(test)---------------------------*/
   p = strtok_r (NULL  , q, &r);
   --rce;  if (p == NULL)  return rce;
   p [5] = '\0';
   a_cur->test = atoi (p);
   /*---(pass)---------------------------*/
   p = strtok_r (NULL  , q, &r);
   --rce;  if (p == NULL)  return rce;
   p [5] = '\0';
   a_cur->pass = atoi (p);
   /*---(fail)---------------------------*/
   p = strtok_r (NULL  , q, &r);
   --rce;  if (p == NULL)  return rce;
   p [5] = '\0';
   a_cur->fail = atoi (p);
   /*---(badd)---------------------------*/
   p = strtok_r (NULL  , q, &r);
   --rce;  if (p == NULL)  return rce;
   p [5] = '\0';
   a_cur->badd = atoi (p);
   /*---(othr)---------------------------*/
   p = strtok_r (NULL  , q, &r);
   --rce;  if (p == NULL)  return rce;
   p [5] = '\0';
   a_cur->othr = atoi (p);
   /*---(result)-------------------------*/
   if      (a_cur->fail >  0)   a_cur->resu = YUNIT_FAIL;
   else if (a_cur->badd >  0)   a_cur->resu = YUNIT_WARN;
   else                         a_cur->resu = YUNIT_SUCC;
   /*---(complete)-----------------------*/
   return 0;
}

char
TEST_run                (tWAVE *a_cur)
{
   char        rc          =    0;
   char        x_cmd       [LEN_RECD]  = "";
   char        x_urun      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   sprintf (x_cmd, "%s/%s_unit %02d --test", a_cur->path, a_cur->unit, a_cur->scrp);
   DEBUG_DATA   yLOG_info    ("x_cmd"     , x_cmd);
   rc = system  (x_cmd);
   DEBUG_DATA   yLOG_value   ("rc"        , rc);
   if      (rc == -1  )   a_cur->resu = YUNIT_NORUN;
   else if (rc ==  127)   a_cur->resu = YUNIT_NORUN;
   else if (rc <   0  )   a_cur->resu = YUNIT_FAIL;
   else {
      DEBUG_DATA   yLOG_note    ("run result checker");
      TEST_result (a_cur);
   }
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*            /*--> unit test accessor ------------------------------*/
TEST__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tWAVE      *x_cur       = NULL;
   /*---(prepare)------------------------*/
   strlcpy  (my.unit_answer, "TEST             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if      (strcmp (a_question, "urun"          )  == 0) {
      WAVE_by_index (&x_cur, n);
      if (x_cur == NULL) {
         snprintf (my.unit_answer, LEN_RECD, "TEST urun   (%2d) : -     -c,     -t,     -p,     -f,     -w,     -b,     -v", n);
      } else {
         snprintf (my.unit_answer, LEN_RECD, "TEST urun   (%2d) : %-2d %4dc, %5dt, %5dp, %5df, %5db, %5dv",
               n, x_cur->resu, x_cur->cond, x_cur->test,
               x_cur->pass, x_cur->fail, x_cur->badd, x_cur->othr);
      }
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}
