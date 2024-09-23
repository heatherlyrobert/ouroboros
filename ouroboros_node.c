/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



tNODE   g_nodes   [MAX_NODE];
int     g_nnode     =  0;
int     g_ready     =  0;



/*====================------------------------------------====================*/
/*===----                     create and destroy                       ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
NODE__wipe              (tNODE *a_dst)
{
   /*---(data)--------------*/
   a_dst->n_name [0]   = '\0';
   a_dst->n_deps [0]   = '\0';
   a_dst->n_cumd [0]   = '\0';
   a_dst->n_miss [0]   = '\0';
   a_dst->n_focus      = '-';
   /*---(working)-----------*/
   a_dst->n_self       = -1;
   a_dst->n_level      = -1;
   a_dst->n_row        = -1;
   a_dst->n_block      = '-';
   /*---(predecessors)------*/
   a_dst->n_cpred      = 0;
   a_dst->n_hpred      = NULL;
   a_dst->n_tpred      = NULL;
   a_dst->n_filled     = 0;
   a_dst->n_ready      = '-';
   /*---(successors)--------*/
   a_dst->n_csucc      = 0;
   a_dst->n_hsucc      = NULL;
   a_dst->n_tsucc      = NULL;
   /*---(sorting)-----------*/
   a_dst->n_ysort      = NULL;
   /*---(done)--------------*/
   return 0;
}

char
NODE__new               (char a_name [LEN_LABEL], char a_force, tNODE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_new       = NULL;
   int         x_tries     =    0;
   char        x_verb      =  '·';
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(default return)-----------------*/
   DEBUG_DATA   yLOG_point   ("r_new"     , r_new);
   --rce;  if (r_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*r_new"    , *r_new);
   DEBUG_DATA   yLOG_char    ("a_force"   , a_force);
   if (a_force == 'y' && *r_new != NULL) {
      *r_new = NULL;
      DEBUG_DATA   yLOG_note    ("force mode grounds existing pointer");
   }
   --rce;  if (*r_new != NULL)  {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("a_name"    , a_name);
   l = strlen (a_name);
   DEBUG_DATA   yLOG_value   ("l"         , l);
   --rce;  if (l > LEN_LABEL - 1) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for duplicate)------------*/
   rc = ySORT_by_name (B_NODE, a_name, &x_new);
   DEBUG_DATA   yLOG_point   ("x_exist"   , x_new);
   --rce;  if (x_new != NULL) {
      if (r_new != NULL)  *r_new = x_new;
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tNODE *)  malloc (sizeof (tNODE));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   NODE__wipe (x_new);
   /*---(populate base)------------------*/
   ystrlcpy (x_new->n_name, a_name, LEN_LABEL);
   /*---(hook tsae)----------------------*/
   rc = ySORT_hook (B_NODE, x_new, x_new->n_name, &(x_new->n_ysort));
   DEBUG_DATA   yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySORT_prepare (B_NODE);
   DEBUG_DATA   yLOG_value   ("prep nodes", rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save return)--------------------*/
   if (r_new != NULL)  *r_new = x_new;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
NODE__free              (tNODE **r_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_DATA   yLOG_enter   (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_DATA   yLOG_point   ("r_old"     , r_old);
   --rce;  if (r_old == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_point   ("*r_old"    , *r_old);
   --rce;  if (*r_old == NULL) {
      DEBUG_DATA   yLOG_note    ("never set");
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(unhook)-------------------------*/
   rc = ySORT_unhook (&((*r_old)->n_ysort));
   DEBUG_DATA   yLOG_value   ("wave"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = ySORT_prepare (B_NODE);
   DEBUG_DATA   yLOG_value   ("prepare"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear and free)-----------------*/
   free (*r_old);
   /*---(ground the pointer)-------------*/
   *r_old = NULL;
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
NODE_purge              (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_NODE, YDLST_HEAD, &x_node);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_node);
   while (rc >= 0 && x_node != NULL) {
      rc = NODE_remove (x_node->n_name, NULL);
      if (rc < 0)  break;
      rc = ySORT_by_cursor (B_NODE, YDLST_HEAD, &x_node);
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_node);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
NODE_init               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ySORT_btree (B_NODE, "nodes");
   DEBUG_PROG   yLOG_value   ("btree"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
NODE_wrap               (void)
{
   NODE_purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       node handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___NODES___________o () { return; }

char
NODE_add                (char a_name [LEN_LABEL], tNODE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(filter)-------------------------*/
   rc = NODE__new (a_name, '-', &x_node);
   --rce;  if (rc < 0 || x_node == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   if (r_new != NULL)  *r_new = x_node;
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
NODE_remove             (char a_name [LEN_LABEL], tNODE **r_old)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(filter)-------------------------*/
   rc = NODE__new (a_name, '-', &x_node);
   DEBUG_PROG   yLOG_value   ("new"       , rc);
   DEBUG_PROG   yLOG_point   ("x_node"    , x_node);
   --rce;  if (rc < 0 || x_node == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check use)----------------------*/
   DEBUG_PROG   yLOG_value   ("n_cpred"   , x_node->n_cpred);
   --rce;  if (x_node->n_cpred > 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_value   ("n_csucc"   , x_node->n_csucc);
   --rce;  if (x_node->n_csucc > 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(free)---------------------------*/
   rc = NODE__free (&x_node);
   DEBUG_PROG   yLOG_value   ("free"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   if (r_old != NULL)  *r_old = NULL;
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                                               <* 
 *> GRAPH_cum_deps          (void)                                                                                     <* 
 *> {                                                                                                                  <* 
 *>    int         i           =    0;                                                                                 <* 
 *>    char        x_lvl       =    0;                                                                                 <* 
 *>    int         c           =    0;                                                                                 <* 
 *>    tEDGE_OLD  *x_pred      = NULL;                                                                                 <* 
 *>    char        x_cumd      [LEN_RECD]  = "";                                                                       <* 
 *>    for (x_lvl = 0; x_lvl < MAX_LEVEL; ++x_lvl) {                                                                   <* 
 *>       for (i = 0; i <  g_nnode; ++i) {                                                                             <* 
 *>          if (g_nodes [i].n_level != x_lvl)  continue;                                                              <* 
 *>          printf ("%3d  %3d  %-25.25s   %3dp  ", i, g_nodes [i].n_level, g_nodes [i].n_name, g_nodes [i].n_cpred);   <* 
 *>          if (g_nodes [i].n_cpred > 0)  {                                                                            <* 
 *>             x_pred = g_nodes [i].n_hpred;                                                                          <* 
 *>             while (x_pred != NULL) {                                                                               <* 
 *>                printf (" %-15.15s", (x_pred->e_beg)->n_name);                                                      <* 
 *>                x_pred = x_pred->e_pnext;                                                                           <* 
 *>             }                                                                                                      <* 
 *>          }                                                                                                         <* 
 *>          printf ("\n");                                                                                            <* 
 *>          ++c;                                                                                                      <* 
 *>       }                                                                                                            <* 
 *>       printf ("\n");                                                                                               <* 
 *>       if (c == g_nnode)  break;                                                                                    <* 
 *>    }                                                                                                               <* 
 *>    return 0;                                                                                                       <* 
 *> }                                                                                                                  <*/



/*====================------------------------------------====================*/
/*===----                     searching and finding                    ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

int  NODE_count     (void)                                    { return  ySORT_count     (B_NODE); }
char NODE_by_name   (char a_name [LEN_LABEL], tNODE **r_cur)  { return  ySORT_by_name   (B_NODE, a_name, r_cur); }
int  NODE_by_index  (int  n                 , tNODE **r_cur)  { return  ySORT_by_index  (B_NODE, n     , r_cur); }
char NODE_by_cursor (char a_dir             , tNODE **r_cur)  { return  ySORT_by_cursor (B_NODE, a_dir , r_cur); }



/*====================------------------------------------====================*/
/*===----                        report/dumping                        ----===*/
/*====================------------------------------------====================*/
static void  o___REPORT__________o () { return; }

char*
NODE_line               (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tNODE      *x_node      = NULL;
   char        x_preds     [LEN_HUND]  = "";
   char        x_succs     [LEN_HUND]  = "";
   char        x_level     [LEN_DESC]  = "";
   /*---(find node)----------------------*/
   rc = NODE_by_index (n, &x_node);
   if (rc < 0 || x_node == NULL) {
      snprintf (my.unit_answer, LEN_RECD, "NODE full   (%2d) : ·                    · ·  · ·                    ·                     · ·    · ·                    ·                      ´ åæ", n);
      return my.unit_answer;
   }
   /*---(predessors)---------------------*/
   if (x_node->n_cpred > 0)        sprintf (x_preds, "%2d %-20.20s %-20.20s %2d %c", x_node->n_cpred, ((x_node->n_hpred)->e_source)->n_name, ((x_node->n_tpred)->e_source)->n_name, x_node->n_filled, x_node->n_ready);
   else                            strcpy  (x_preds, " · ·                    ·                     · ·");
   /*> if (x_node->n_cpred > 0)        sprintf (x_preds, "%2d %-20.20s %-20.20s %2d %c", x_node->n_cpred, ((x_node->n_hpred)->e_target)->n_name, ((x_node->n_tpred)->e_target)->n_name, x_node->n_filled, x_node->n_ready);   <* 
    *> else                            strcpy  (x_preds, " · ·                    ·                     · ·");                                                                                                                <*/
   /*---(successors)---------------------*/
   if (x_node->n_csucc > 0)        sprintf (x_succs, "%2d %-20.20s %-20.20s", x_node->n_csucc, ((x_node->n_hsucc)->e_target)->n_name, ((x_node->n_tsucc)->e_target)->n_name);
   else                            strcpy  (x_succs, " · ·                    ·                     ·");
   /*> if (x_node->n_csucc > 0)        sprintf (x_succs, "%2d %-20.20s %-20.20s", x_node->n_csucc, ((x_node->n_hsucc)->e_source)->n_name, ((x_node->n_tsucc)->e_source)->n_name);   <* 
    *> else                            strcpy  (x_succs, " · ·                    ·                     ·");                                                                        <*/
   /*---(level)--------------------------*/
   if      (x_node->n_level <  0)  strcpy  (x_level, "-");
   else if (x_node->n_level >  9)  strcpy  (x_level, "Ï");
   else                            sprintf (x_level, "%c", x_node->n_level + '0');
   /*---(concatenate)--------------------*/
   snprintf (my.unit_answer, LEN_RECD, "NODE full   (%2d) : %-20.20s %c %-1.1s %-49.49s   %-44.44s   ´ å%sæ", n, x_node->n_name, x_node->n_focus, x_level, x_preds, x_succs, x_node->n_deps);
   /*---(complete)-----------------------*/
   return my.unit_answer;
}

char
NODE_dump               (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         i           =    0;
   tNODE      *x_node      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_NODE, YDLST_HEAD, &x_node);
   while (rc >= 0 && x_node != NULL) {
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %4d, %p", rc, i, x_node);
      printf ("%s\n", GRAPH_node_line (i++));
      rc = ySORT_by_cursor (B_NODE, YDLST_NEXT, &x_node);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*
NODE__unit              (char *a_question, int n)
{ 
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        s           [LEN_DESC]  = "";
   char        t           [LEN_HUND]  = "";
   char        u           [LEN_HUND]  = "";
   tNODE      *x_cur       = NULL;
   char        i           =    0;
   char        x_focus     =    0;
   /*---(prepare)------------------------*/
   ystrlcpy  (my.unit_answer, "NODE             : question not understood", LEN_RECD);
   /*---(crontab name)-------------------*/
   if (strcmp (a_question, "full"          )  == 0) {
      NODE_by_index (n, &x_cur);
      ystrlcpy (my.unit_answer, NODE_line (n), LEN_RECD);
   }
   /*---(complete)-----------------------*/
   return my.unit_answer;
}





