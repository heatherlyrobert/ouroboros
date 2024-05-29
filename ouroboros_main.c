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
   /*> rc = PROG_dispatch ();                                                         <*/
   DEBUG_PROG   yLOG_value   ("driver"    , rc);
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   /*---(normal)-------------------------*/
   GRAPH_add_node  ("yENV_solo");
   n = GRAPH_by_name ("yUNIT");
   if (n >= 0) {
      ystrlcat (g_nodes [n].n_deps, "yENV_solo,", LEN_RECD);
      ystrlcat (g_nodes [n].n_miss, "yENV_solo,", LEN_RECD);
   }
   GRAPH_deps_add  ("yENV_solo"  , ",zenodotus,");
   GRAPH_deps_add  ("ySTR_solo"  , ",zenodotus,");
   GRAPH_deps_add  ("yLOG_solo"  , ",zenodotus,");
   GRAPH_deps_add  ("yURG_solo"  , ",zenodotus,");
   GRAPH_deps_add  ("yUNIT_solo" , ",zenodotus,");
   GRAPH_deps_add  ("yCOLOR_solo", ",zenodotus,");
   GRAPH_deps_add  ("yDLST_solo" , ",zenodotus,");
   GRAPH_edge_virt  ("yENV_solo"  , GRAPH_by_name ("yUNIT"));
   INCL_list ();
   GRAPH_dump_nodes ();
   GRAPH_dump_edges ();
   GRAPH_solve      ('-');
   GRAPH_deps_solve ();
   GRAPH_dump_seq   ();
   GRAPH_focus_all  ();
   /*> GRAPH_focus_on   ("yVAR");                                                     <*/
   DRAW_main        ('b', YASCII_DEFAULT, YASCII_MAX);
   /*> rc = PROG_driver ();                                                           <*/
   /*---(complete)-----------------------*/
   PROG_shutdown ();
   DEBUG_PROG   yLOG_value    ("shutdown"  , rc);
   return rc;
}



/*===============================[[ end code ]]===============================*/
