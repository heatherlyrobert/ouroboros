/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"


int
main               (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----------+-*/
   char        rc          = 0;
   /*---(initialize)---------------------*/
   if (rc >= 0)  rc = PROG_startup (a_argc, a_argv);
   if (rc >= 0)  rc = PROG_final   ();
   if (rc <  0)  {
      PROG_shutdown ();
      return rc;
   }
   /*---(normal)-------------------------*/
   rc = PROG_driver ();
   /*---(complete)-----------------------*/
   PROG_shutdown ();
   return rc;
}



/*===============================[[ end code ]]===============================*/
