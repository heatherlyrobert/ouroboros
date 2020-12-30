/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



char       *g_greek     = "טיךכלםמןנסעףפץצקרשתûü‎‏ÿ";

#define    MAX_GREEK    24
#define    MAX_SPREAD   240
char       g_spread   [MAX_SPREAD];
int        g_places   [MAX_GREEK];



char
RPTG_clear              (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_SPREAD; ++i)  g_spread [i] = 0;
   return 0;
}

char
RPTG_spread             (char a_wave, char a_stage)
{
   char       *p           = NULL;
   int         a           =    0;
   p = strchr (g_greek, a_wave);
   a = (p - g_greek) * 10;
   ++(g_spread [a]);
   a += a_stage;
   ++(g_spread [a]);
   return 0;
}

char
RPTG_heading             (void)
{
   char        rc          =    0;
   int         i           = 0;
   tWAVE      *x_cur       = NULL;
   char       *p           = NULL;
   int         a           =    0;
   printf ("---file------------- ## w s   ");
   for (i = 0; i < MAX_GREEK; ++i) {
      if (g_spread [i * 10] > 0) {
         printf (" ----%c----", g_greek [i]);
         g_places [i] = a;
         a += 10;
      } else {
         g_places [i] = 0;
      }
   }
   printf ("\n");
}

char
RPTG_lines               (void)
{
   char        rc          =    0;
   int         i           = 0;
   int         c           =    0;
   tWAVE      *x_cur       = NULL;
   char       *p           = NULL;
   int         a           =    0;
   rc = WAVE_by_cursor (&x_cur, '[');
   while (rc >= 0 && x_cur != NULL) {
      if (c % 5 == 0)  printf ("\n");
      ++c;
      printf ("%-20.20s %2d %c %d   ", x_cur->unit, x_cur->scrp, x_cur->wave, x_cur->stage);
      p = strchr (g_greek, x_cur->wave);
      a = g_places [p - g_greek] + x_cur->stage;
      for (i = 0; i < a; ++i)  printf (" ");
      printf ("Ï\n");
      rc = WAVE_by_cursor (&x_cur, '>');
   }
   return 0;
}


