/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"


int
main               (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   /*---(debugging)----------------------*/
   rc = PROG_urgents (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("urgents"   , rc);
   --rce;  if (rc <  0) { PROG_shutdown (); return rce; }
   /*---(initialization)-----------------*/
   rc = PROG_startup (a_argc, a_argv);
   DEBUG_PROG   yLOG_value    ("startup"   , rc);
   --rce;  if (rc <  0) { PROG_shutdown (); return rce; }
   /*---(dispatch)-----------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   rc = yJOBS_driver (P_ONELINE, YJOBS_callback);
   DEBUG_PROG   yLOG_value   ("driver"    , rc);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   /*---(normal)-------------------------*/
   INCL_zenodotus  ();
   INCL_list ();
   GRAPH_dump_nodes ();
   GRAPH_dump_edges ();
   DEPS_dump        ();
   /*> GRAPH_focus_all  ();                                                           <*/
   GRAPH_focus_on   ("ySTR");
   GRAPH_focus_on   ("yENV");
   GRAPH_solve      ('-');
   DEPS_gather      ();
   GRAPH_dump_seq   ();
   GRAPH_dump_all   ();
   /*> GRAPH_focus_on   ("yVAR");                                                     <*/
   DRAW_main        ('b', YASCII_DEFAULT, YASCII_MAX);
   GRAPH_dump_placement   ();
   /*> rc = PROG_driver ();                                                           <*/
   /*---(complete)-----------------------*/
   PROG_shutdown ();
   DEBUG_PROG   yLOG_value    ("shutdown"  , rc);
   return rc;
}



/*===============================[[ end code ]]===============================*/
