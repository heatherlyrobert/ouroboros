/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"

char
YJOBS_callback          (cchar a_req, cchar *a_data)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   DEBUG_PROG    yLOG_char    ("a_req"     , a_req);
   DEBUG_PROG    yLOG_info    ("a_data"    , a_data);
   switch (a_req) {
   case YJOBS_READ     :
      DEBUG_PROG    yLOG_note    ("READ -- central database read");
      rc = WAVE_pull_central (FILE_CENTRAL);
      break;
   case YJOBS_WRITE    :
      DEBUG_PROG    yLOG_note    ("WRITE -- central database write");
      rc = TDB_write ( FILE_CENTRAL);
      break;
   case YJOBS_STATS    :
      break;
   case YJOBS_PULL     :
      DEBUG_PROG    yLOG_note    ("PULL -- read a local project");
      rc = WAVE_inventory (a_data);
      break;
   case YJOBS_CLEAR    :
      DEBUG_PROG    yLOG_note    ("CLEAR -- purge all content data");
      break;
   case YJOBS_REPORT   :
      DEBUG_PROG    yLOG_note    ("REPORT -- central data reporting");
      INCL_list ();
      /*> GRAPH_dump_nodes ();                                                        <*/
      /*> GRAPH_dump_edges ();                                                        <*/
      /*> GRAPH_solve      ('-');                                                     <*/
      /*> GRAPH_dump_seq   ();                                                        <*/
      break;
   }
   /*---(trouble)------------------------*/
   if (rc < 0) {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return 0;
}

char
PROG_dispatch           (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG    yLOG_enter   (__FUNCTION__);
   /*---(title)--------------------------*/
   IF_VERBOSE   yURG_msg ('>', "%s", P_ONELINE);
   /*---(route action)-------------------*/
   DEBUG_PROG    yLOG_char    ("run_mode"  , my.run_mode);
   --rce;  switch (my.run_mode) {
      /*---(basic)-----------------------*/
   case ACT_STATS       :
      break;
      /*---(incomming)-------------------*/
   case CASE_VERIFY     :
      break;
   case CASE_REGISTER   :
      break;
   case CASE_UPDATE     :
      break;
   case CASE_INSTALL    :
      break;
      /*---(outgoing)--------------------*/
   case CASE_WITHDRAW   :
      break;
   case CASE_CLEAR      :
      break;
   case CASE_REMOVE     :
      break;
      /*---(central)---------------------*/
   case CASE_REPORT     :
      DEBUG_PROG    yLOG_note    ("reporting");
      break;
   case CASE_AUDIT      :
      break;
      /*---(execute)---------------------*/
   case CASE_GATHER     :
      break;
   case CASE_NORMAL     :
   case CASE_STRICT     :
      break;
      /*---(trouble)---------------------*/
   default              :
      rc = rce;
      break;
   }
   /*---(cut-off)------------------------*/
   yURG_all_mute ();
   /*---(complete)-----------------------*/
   DEBUG_PROG    yLOG_exit    (__FUNCTION__);
   return rc;
}
