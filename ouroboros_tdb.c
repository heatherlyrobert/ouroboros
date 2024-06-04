/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



static int   G_nproj;
static int   G_nunit, G_nscrp, G_ncond, G_nstep, G_est, G_npass, G_nfail, G_nbadd, G_nvoid, G_nmiss, G_act, G_PASS, G_FAIL, G_WARN, G_NONE;
static int   P_nunit, P_nscrp, P_ncond, P_nstep, P_est, P_npass, P_nfail, P_nbadd, P_nvoid, P_nmiss, P_act, P_PASS, P_FAIL, P_WARN, P_NONE;
static int   U_nunit, U_nscrp, U_ncond, U_nstep, U_est, U_npass, U_nfail, U_nbadd, U_nvoid, U_nmiss, U_act, U_PASS, U_FAIL, U_WARN, U_NONE;


char
TDB_total_proj         (tWAVE *a_proj)
{
   a_proj->w_nunit  = P_nunit;
   a_proj->w_nscrp  = P_nscrp;
   a_proj->w_ncond  = P_ncond;
   a_proj->w_nstep  = P_nstep;
   a_proj->w_expect = P_est;
   a_proj->w_npass  = P_npass;
   a_proj->w_nfail  = P_nfail;
   a_proj->w_nbadd  = P_nbadd;
   a_proj->w_nvoid  = P_nvoid;
   a_proj->w_nmiss  = P_nmiss;
   a_proj->w_actual = P_act;
   a_proj->w_pass   = P_PASS;
   a_proj->w_fail   = P_FAIL;
   a_proj->w_warn   = P_WARN;
   a_proj->w_none   = P_NONE;
   return 0;
}

char
TDB_total_unit         (tWAVE *a_unit)
{
   a_unit->w_nunit  = U_nunit;
   a_unit->w_nscrp  = U_nscrp;
   a_unit->w_ncond  = U_ncond;
   a_unit->w_nstep  = U_nstep;
   a_unit->w_expect = U_est;
   a_unit->w_npass  = U_npass;
   a_unit->w_nfail  = U_nfail;
   a_unit->w_nbadd  = U_nbadd;
   a_unit->w_nvoid  = U_nvoid;
   a_unit->w_nmiss  = U_nmiss;
   a_unit->w_actual = U_act;
   a_unit->w_pass   = U_PASS;
   a_unit->w_fail   = U_FAIL;
   a_unit->w_warn   = U_WARN;
   a_unit->w_none   = U_NONE;
   return 0;
}

char
TDB_totalize            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   tWAVE      *x_proj      = NULL;
   tWAVE      *x_unit      = NULL;
   tWAVE      *x_wave      = NULL;
   int         x_none      =    0;
   /*---(prepare)------------------------*/
   G_nproj = 0;
   G_nunit = G_nscrp = G_ncond = G_nstep = G_npass = G_est = G_nfail = G_nbadd = G_nvoid = G_nmiss = G_act = G_PASS = G_FAIL = G_WARN = G_NONE = 0;
   P_nunit = P_nscrp = P_ncond = P_nstep = P_npass = P_est = P_nfail = P_nbadd = P_nvoid = P_nmiss = P_act = P_PASS = P_FAIL = P_WARN = P_NONE = 0;
   U_nunit = U_nscrp = U_ncond = U_nstep = U_npass = U_est = U_nfail = U_nbadd = U_nvoid = U_nmiss = U_act = U_PASS = U_FAIL = U_WARN = U_NONE = 0;
   /*---(walk database)------------------*/
   rc = WAVE_by_cursor (YDLST_HEAD, &x_wave);
   while (rc >= 0) {
      /*---(project)---------------------*/
      switch (x_wave->w_verb) {
      case ENTRY_PROG :
         ++G_nproj;
         if (x_unit != NULL)   TDB_total_unit (x_unit);
         if (x_proj != NULL)   TDB_total_proj (x_proj);
         x_proj = x_wave;
         x_unit = NULL;
         P_nunit = P_nscrp = P_ncond = P_nstep = P_npass = P_est = P_nfail = P_nbadd = P_nvoid = P_nmiss = P_act = P_PASS = P_FAIL = P_WARN = P_NONE = 0;
         U_nunit = U_nscrp = U_ncond = U_nstep = U_npass = U_est = U_nfail = U_nbadd = U_nvoid = U_nmiss = U_act = U_PASS = U_FAIL = U_WARN = U_NONE = 0;
         break;
         /*---(unit)------------------------*/
      case ENTRY_UNIT :
         if (x_unit != NULL)   TDB_total_unit (x_unit);
         x_unit = x_wave;
         G_nunit  += 1;       P_nunit  += 1;
         U_nunit = U_nscrp = U_ncond = U_nstep = U_npass = U_est = U_nfail = U_nbadd = U_nvoid = U_nmiss = U_act = U_PASS = U_FAIL = U_WARN = U_NONE = 0;
         break;
         /*---(wave)------------------------*/
      case ENTRY_WAVE :
         G_nscrp  += 1;                P_nscrp  += 1;                U_nscrp  += 1; 
         G_ncond  += x_wave->w_ncond;  P_ncond  += x_wave->w_ncond;  U_ncond  += x_wave->w_ncond; 
         G_nstep  += x_wave->w_nstep;  P_nstep  += x_wave->w_nstep;  U_nstep  += x_wave->w_nstep; 
         G_est    += x_wave->w_expect; P_est    += x_wave->w_expect; U_est    += x_wave->w_expect;
         G_npass  += x_wave->w_npass;  P_npass  += x_wave->w_npass;  U_npass  += x_wave->w_npass; 
         G_nfail  += x_wave->w_nfail;  P_nfail  += x_wave->w_nfail;  U_nfail  += x_wave->w_nfail;
         G_nbadd  += x_wave->w_nbadd;  P_nbadd  += x_wave->w_nbadd;  U_nbadd  += x_wave->w_nbadd;
         G_nvoid  += x_wave->w_nvoid;  P_nvoid  += x_wave->w_nvoid;  U_nvoid  += x_wave->w_nvoid;
         G_nmiss  += x_wave->w_nmiss;  P_nmiss  += x_wave->w_nmiss;  U_nmiss  += x_wave->w_nmiss;
         G_act    += x_wave->w_actual; P_act    += x_wave->w_actual; U_act    += x_wave->w_actual;
         switch (x_wave->w_result) {
         case 'P' : G_PASS  += 1; P_PASS  += 1; U_PASS  += 1; x_wave->w_pass = 'Ï'; break;
         case 'F' : G_FAIL  += 1; P_FAIL  += 1; U_FAIL  += 1; x_wave->w_fail = 'Ï'; break;
         case '?' : G_WARN  += 1; P_WARN  += 1; U_WARN  += 1; x_wave->w_warn = 'Ï'; break;
         default  : G_NONE  += 1; P_NONE  += 1; U_NONE  += 1; x_wave->w_none = 'Ï'; break;
         }
         break;
      }
      /*---(next)------------------------*/
      rc = WAVE_by_cursor (YDLST_NEXT, &x_wave);
   }
   if (x_unit != NULL)   TDB_total_unit (x_unit);
   if (x_proj != NULL)   TDB_total_proj (x_proj);
   return 0;
}



char
TDB_write               (char a_full [LEN_PATH])
{
   char        rce         =  -10;
   char        rc          =    0;
   long        x_now       =    0;
   tTIME      *x_broke     = NULL;
   FILE       *f           = NULL;
   tWAVE      *x_wave      = NULL;
   int         c           =    0;
   char        x_heart     [LEN_HUND]  = "";
   char        x_est       [LEN_SHORT] = "";
   char        x_act       [LEN_SHORT] = "";
   /*---(defense)------------------------*/
   --rce; if (a_full == NULL)  return rce;
   /*---(open file)----------------------*/
   f = fopen (a_full, "wt");
   --rce; if (f      == NULL)  return rce;
   /*---(header)-------------------------*/
   x_now   = time (NULL);
   x_broke = localtime (&x_now);
   strftime (x_heart, LEN_TITLE, "%y.%m.%d.%H.%M.%S.%u.%W.%j", x_broke);
   fprintf (f, "#!/usr/local/bin/ouroboros\n");
   fprintf (f, "## ouroboros-aperantos (tail-eater) master unit testing sequencer\n");
   fprintf (f, "## central wave and dependency database\n");
   fprintf (f, "## version      å%sæ %s\n", P_VERNUM, P_VERTXT);
   fprintf (f, "## last updated å%sæ %ld\n", x_heart, x_now);
   TDB_totalize ();
   /*---(prepare)------------------------*/
   rc = WAVE_by_cursor (YDLST_HEAD, &x_wave);
   /*---(walk database)------------------*/
   while (rc >= 0) {
      /*---(project)---------------------*/
      switch (x_wave->w_verb) {
      case ENTRY_PROG :
         ystrldur (x_wave->w_expect, '-', x_est);
         ystrldur (x_wave->w_actual, '-', x_act);
         fprintf (f, "\n\n\n");
         fprintf (f, "##------  ---timestamp--------------  ---epoch--  ---project----------  ---unit-----------------------  sc  S  ---description--------------------------------------------------------  ---terse------------  w  s  i  #units  #scrps  #conds  #steps  est  expect  R  #pass#  #fail#  #badd#  #void#  #miss#  actual  act  -pass-  -fail-  -warn-  -none- \n");
         fprintf (f, "PROJ====  =========´=========´======  =========´  %-20.20s  ##=======´=========´=========´  ==  =  =========´=========´=========´=========´=========´=========´=========´  =========´=========´  =  =  =  %6d  %6d  %6d  %6d  %3s  %6d  =  %6d  %6d  %6d  %6d  %6d  %6d  %3s  %6d  %6d  %6d  %6d \n",
               x_wave->w_proj, x_wave->w_nunit, x_wave->w_nscrp, x_wave->w_ncond, x_wave->w_nstep, x_est, x_wave->w_expect, x_wave->w_npass, x_wave->w_nfail, x_wave->w_nbadd, x_wave->w_nvoid, x_wave->w_nmiss, x_wave->w_actual, x_act, x_wave->w_pass, x_wave->w_fail, x_wave->w_warn, x_wave->w_none);
         break;
         /*---(unit)------------------------*/
      case ENTRY_UNIT :
         ystrldur (x_wave->w_expect, '-', x_est);
         ystrldur (x_wave->w_actual, '-', x_act);
         fprintf (f, "\n");
         fprintf (f, "  UNIT··  ··························  ··········  %-20.20s  %-30.30s  ##  S  ---description--------------------------------------------------------  ---terse------------  -  -  -  %6d  %6d  %6d  %6d  %3s  %6d  -  %6d  %6d  %6d  %6d  %6d  %6d  %3s  %6d  %6d  %6d  %6d \n",
               x_wave->w_proj, x_wave->w_unit, x_wave->w_nunit, x_wave->w_nscrp, x_wave->w_ncond, x_wave->w_nstep, x_est, x_wave->w_expect, x_wave->w_npass, x_wave->w_nfail, x_wave->w_nbadd, x_wave->w_nvoid, x_wave->w_nmiss, x_wave->w_actual, x_act, x_wave->w_pass, x_wave->w_fail, x_wave->w_warn, x_wave->w_none);
         break;
         /*---(wave)------------------------*/
      case ENTRY_WAVE :
         ystrldur (x_wave->w_actual, '-', x_act);
         fprintf (f, "    WAVE  %-26.26s  %10ld  %-20.20s  %-30.30s  %02d  %c  %-70.70s  %-20.20s  %c  %c  %c  %6d  %6d  %6d  %6d  %3.3s  %6d  %c  %6d  %6d  %6d  %6d  %6d  %6d  %3s       %c       %c       %c       %c \n",
               x_wave->w_time, x_wave->w_last, x_wave->w_proj, x_wave->w_unit,
               x_wave->w_scrp, x_wave->w_source, x_wave->w_desc, x_wave->w_terse,
               x_wave->w_wave, x_wave->w_stage, x_wave->w_rating,
               x_wave->w_nunit, x_wave->w_nscrp, x_wave->w_ncond, x_wave->w_nstep,
               x_wave->w_expe, x_wave->w_expect,
               x_wave->w_result,
               x_wave->w_npass, x_wave->w_nfail, x_wave->w_nbadd, x_wave->w_nvoid, x_wave->w_nmiss,
               x_wave->w_actual, x_act,
               x_wave->w_pass, x_wave->w_fail, x_wave->w_warn, x_wave->w_none);
         break;
      }
      /*---(next)------------------------*/
      rc = WAVE_by_cursor (YDLST_NEXT, &x_wave);
   }
   /*---(footer)-------------------------*/
   ystrldur (G_est, '-', x_est);
   ystrldur (G_act, '-', x_act);
   fprintf (f, "\n\n\n");
   fprintf (f, "##------  ---timestamp--------------  ---epoch--  ---project----------  ---unit-----------------------  sc  S  ---description--------------------------------------------------------  ---terse------------  w  s  i  #units  #scrps  #conds  #steps  est  expect  R  #pass#  #fail#  #badd#  #void#  #miss#  actual  act  -pass-  -fail-  -warn-  -none- \n");
   fprintf (f, "## GRAND  =========´=========´======  =========´  %3d =====´=========´  ##=======´=========´=========´  ==  =  =========´=========´=========´=========´=========´=========´=========´  =========´=========´  =  =  =  %6d  %6d  %6d  %6d  %3s  %6d  =  %6d  %6d  %6d  %6d  %6d  %6d  %3s  %6d  %6d  %6d  %6d \n",
         G_nproj, G_nunit, G_nscrp, G_ncond, G_nstep, x_est, G_est, G_npass, G_nfail, G_nbadd, G_nvoid, G_nmiss, G_act, x_act, G_PASS, G_FAIL, G_WARN, G_NONE);
   fprintf (f, "\n\n\n");
   fprintf (f, "## end-of-data.  done, finito, completare, whimper [Ï´···\n");
   /*---(close)--------------------------*/
   rc = fclose (f);
   --rce; if (rc != 0)         return rce;
   /*---(complete)-----------------------*/
   return 0;
}
