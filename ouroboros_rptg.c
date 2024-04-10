/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



#define    MAX_GREEK    24
#define    MAX_SPREAD   240
char       g_spread   [MAX_SPREAD];
int        g_places   [MAX_GREEK];
static int        s_none     =  0;
static char       s_out      [LEN_RECD]  = "";



char
RPTG_clear              (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_SPREAD; ++i)  g_spread [i] = 0;
   s_none = 0;
   return 0;
}

char
RPTG_spread             (uchar a_wave, uchar a_stage)
{
   char       *p           = NULL;
   int         a           =    0;
   int         b           =    0;
   if (a_wave == '-') {
      ++s_none;
      return 0;
   }
   p = strchr (YSTR_GREEK, a_wave);
   a = (p - YSTR_GREEK) * 10;
   ++(g_spread [a]);
   b = a + (a_stage - '0');
   ++(g_spread [b]);
   /*> printf ("%3dw, %3ds, %3d, %-10p, %3da, %3db\n", a_wave, a_stage, a_stage - '0', p, a, b);   <*/
   return 0;
}

char*
RPTG_spread_disp        (void)
{
   char        t           [LEN_LABEL];
   int         i           =    0;
   int         a           =    0;
   ystrlcpy (s_out, "", LEN_RECD);
   a = s_none;
   if      (a <= 0)   sprintf (t, "£>·");
   else if (a <= 9)   sprintf (t, "£>%1d", a);
   else               sprintf (t, "£>Ï");
   ystrlcat (s_out, t, LEN_RECD);
   for (i = 0; i < 60; ++i) {
      if (i % 10 == 0) {
         sprintf (t, " %c>", YSTR_GREEK [i / 10]);
         ystrlcat (s_out, t, LEN_RECD);
      }
      a = g_spread [i];
      if      (a <= 0)   sprintf (t, "·");
      else if (a <= 9)   sprintf (t, "%1d", a);
      else               sprintf (t, "Ï");
      ystrlcat (s_out, t, LEN_RECD);
   }
   return s_out;
}

char
RPTG_heading             (void)
{
   char        rc          =    0;
   int         i           = 0;
   tWAVE      *x_cur       = NULL;
   char       *p           = NULL;
   int         a           =    0;
   printf ("project----------- unit-test-------------- scrp--w-s - ");
   for (i = 0; i < MAX_GREEK; ++i) {
      if (g_spread [i * 10] > 0) {
         printf (" ----%c----", YSTR_GREEK [i]);
         g_places [i] = a;
         a += 10;
      } else {
         g_places [i] = 0;
      }
   }
   printf ("\n");
   printf ("\n");
   return 0;
}

char*
RPTG_line                (tWAVE *a_prv, tWAVE *a_cur, char *a_spec)
{
   char        x_proj      =  '-';
   char        x_unit      =  '-';
   char        t           [LEN_HUND]  = "";
   char       *p           = NULL;
   int         n           =    0;
   int         i           =    0;
   /*---(default)------------------------*/
   ystrlcpy (s_out, "", LEN_RECD);
   /*---(defense)------------------------*/
   if (a_cur == NULL)   return s_out;
   /*---(flags)--------------------------*/
   if      (a_prv == NULL)                               x_proj = x_unit = 'y';
   /*> else if (strcmp (a_prv->w_phint, a_cur->w_phint) != 0)  x_proj = x_unit = 'y';   <* 
    *> else if (strcmp (a_prv->w_uhint, a_cur->w_uhint) != 0)  x_unit = 'y';            <*/
   /*---(spacing)------------------------*/
   if (strchr (a_spec, '¦') != NULL) {
      if (x_unit == 'y')  printf ("\n");
   }
   /*---(project)------------------------*/
   if (strchr (a_spec, 'p') != NULL) {
      if (x_proj == 'y')
         ;
         /*> sprintf (t, "%-2.2s %-15.15s ", a_cur->w_phint, a_cur->w_proj);          <*/
      else
         sprintf (t, "·· %-15.15s ", a_cur->w_proj);
      ystrlcat (s_out  , t, LEN_RECD);
   }
   /*---(project)------------------------*/
   if (strchr (a_spec, 'u') != NULL) {
      if (x_unit == 'y')
         ;
         /*> sprintf (t, "%-2.2s %-20.20s ", a_cur->w_uhint, a_cur->w_unit);          <*/
      else
         sprintf (t, "·· %-20.20s ", a_cur->w_unit);
      ystrlcat (s_out  , t, LEN_RECD);
   }
   /*---(script)-------------------------*/
   if (strchr (a_spec, 's') != NULL) {
      ;
      /*> sprintf (t, "%-2.2s %2d ", a_cur->w_shint, a_cur->w_scrp);                  <*/
      ystrlcat (s_out  , t, LEN_RECD);
   }
   /*---(timing)-------------------------*/
   if (strchr (a_spec, 't') != NULL) {
      sprintf (t, "%c %c ", a_cur->w_wave, a_cur->w_stage);
      ystrlcat (s_out  , t, LEN_RECD);
   }
   /*---(description)--------------------*/
   if (strchr (a_spec, 'd') != NULL) {
      sprintf (t, "%-75.75s ", a_cur->w_desc);
      ystrlcat (s_out  , t, LEN_RECD);
   }
   /*---(wave/stage)---------------------*/
   if (strchr (a_spec, 'w') != NULL) {
      p = strchr (YSTR_GREEK, a_cur->w_wave);
      if (a_cur->w_wave == '-') {
         ystrlcat (s_out, " Ï", LEN_RECD);
         n = -1;
      } else {
         ystrlcat (s_out, " ·", LEN_RECD);
         n = p - YSTR_GREEK;
      }
      for (i = 0; i < MAX_GREEK; ++i) {
         if (g_spread [i * 10] == 0)   continue;
         sprintf (t, "  Ö·······Õ", LEN_RECD);
         if (n == i)  t [a_cur->w_stage - '0' + 1] = 'Ï';
         ystrlcat (s_out, t, LEN_RECD);
      }
   }
   /*---(trim)---------------------------*/
   ystrltrim (s_out, ySTR_BOTH, LEN_RECD);
   /*---(complete)-----------------------*/
   return s_out;
}


char
RPTG_lines               (void)
{
   char        rc          =    0;
   int         i           = 0;
   int         c           =    0;
   tWAVE      *x_prv       = NULL;
   tWAVE      *x_cur       = NULL;
   char       *p           = NULL;
   int         a           =    0;
   /*> printf ("count %d\n", my.scrps);                                               <*/
   rc = PROJ_by_cursor (&x_cur, '[');
   while (rc >= 0 && x_cur != NULL) {
      /*> if (x_prv != NULL && strcmp (x_prv->w_unit, x_cur->w_unit) != 0)  printf ("\n");                          <* 
       *> ++c;                                                                                                      <* 
       *> if (x_prv == NULL || strcmp (x_prv->w_phint, x_cur->w_phint) != 0)  printf ("%-2.2s ", x_cur->w_phint);   <* 
       *> else                                                              printf ("·· ");                         <*/
      /*> printf ("%-15.15s ", x_cur->w_proj);                                                                      <* 
       *> if (x_prv == NULL || strcmp (x_prv->w_uhint, x_cur->w_uhint) != 0)  printf ("%-2.2s ", x_cur->w_uhint);   <* 
       *> else                                                              printf ("·· ");                         <* 
       *> printf ("%-20.20s ", x_cur->w_unit);                                                                      <* 
       *> printf ("%-2.2s %2d %c %c ", x_cur->w_shint, x_cur->w_scrp, x_cur->w_wave, x_cur->w_stage);               <*/
      if (x_cur->w_wave == '-') {
         printf ("Ï\n");
      } else {
         printf ("  ");
         p = strchr (YSTR_GREEK, x_cur->w_wave);
         a = g_places [p - YSTR_GREEK] + (x_cur->w_stage - '0');
         for (i = 0; i < a; ++i)  printf (" ");
         printf ("Ï\n");
      }
      /*> printf ("%-2.2s ", x_cur->w_phint);                                         <*/
      printf ("%-15.15s ", x_cur->w_proj);
      /*> printf ("%-2.2s ", x_cur->w_uhint);                                         <*/
      printf ("%-20.20s ", x_cur->w_unit);
      /*> printf ("%-2.2s %2d %c %c ", x_cur->w_shint, x_cur->w_scrp, x_cur->w_wave, x_cur->w_stage);   <*/
      printf (" %-75.75s", x_cur->w_desc);
      printf (" %-40.40s", x_cur->sort);
      printf ("\n");
      x_prv = x_cur;
      rc = PROJ_by_cursor (&x_cur, '>');
   }
   printf ("\n");
   return 0;
}

char
RPTG_dump               (void)
{
   char        rc          =    0;
   tWAVE      *x_prv       = NULL;
   tWAVE      *x_cur       = NULL;
   int         c           =    0;
   rc = PROJ_by_cursor (&x_cur, '[');
   while (rc >= 0 && x_cur != NULL) {
      if (x_prv != NULL && strcmp (x_prv->w_unit, x_cur->w_unit) != 0)  printf ("\n");
      ++c;
      printf ("%-4d ", c);
      /*> printf ("%-2.2s ", x_cur->w_phint);                                         <*/
      printf ("%-15.15s ", x_cur->w_proj);
      /*> printf ("%-2.2s ", x_cur->w_uhint);                                         <*/
      printf ("%-20.20s ", x_cur->w_unit);
      /*> printf ("%-2.2s %2d %c %c ", x_cur->w_shint, x_cur->w_scrp, x_cur->w_wave, x_cur->w_stage);   <*/
      printf (" %-75.75s", x_cur->w_desc);
      printf (" %-40.40s", x_cur->sort);
      printf ("\n");
      x_prv = x_cur;
      rc = PROJ_by_cursor (&x_cur, '>');
   }
   printf ("\ntotal %3d vs %3d counter\n", c, my.scrps);
   return 0;
}





