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
   DEBUG_DATA   yLOG_value   ("prep tsae" , rc);
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
   int         i           =    0;
   /*> for (i = 0; i < MAX_NODE; ++i)   NODE__wipe (i);                               <* 
    *> g_nnode = 0;                                                                   <* 
    *> g_ready = 0;                                                                   <*/
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
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       node handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___NODES___________o () { return; }

int
NODE_by_name            (char a_name [LEN_TITLE])
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (a_name == NULL)            return rce;
   --rce;  if (strcmp (a_name, "") == 0)  return rce;
   for (i = 0; i < g_nnode; ++i) {
      if (strcmp (g_nodes [i].n_name, a_name) != 0)  continue;
      return i;
   }
   return --rce;
}

char
NODE_add                (char a_name [LEN_TITLE])
{
   char        rce         =  -10;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("a_name"    , a_name);
   --rce;  if (strcmp (a_name, "") == 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(filter)-------------------------*/
   /*> if (strcmp (a_name, "yVIHUB_solo") == 0) {                                     <* 
    *>    DEBUG_PROG  yLOG_note    ("always ignore yVIHUB_solo");                     <* 
    *>    DEBUG_DATA  yLOG_exit    (__FUNCTION__);                                    <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   n = GRAPH_by_name (a_name);
   DEBUG_PROG   yLOG_value   ("n"         , n);
   if (n < 0) {
      DEBUG_PROG  yLOG_note    ("can't find, add new node");
      ystrlcpy (g_nodes [g_nnode].n_name, a_name, LEN_TITLE);
      n = g_nnode;
      DEBUG_PROG   yLOG_value   ("n"         , n);
      g_nodes [n].n_self = n;
      ++g_nnode;
      DEBUG_PROG   yLOG_value   ("g_nnode"   , g_nnode);
   }
   /*> if (strcmp (a_name, "zenodotus") != 0) {                                       <* 
    *>    DEBUG_PROG   yLOG_note    ("create a link back to zenodotus");              <* 
    *>    INCL_add_by_name ("zenodotus", n);                                          <* 
    *>    GRAPH_edge_add   ("zenodotus", n);                                          <* 
    *> }                                                                              <*/
   /*---(defense)------------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return n;
}

/*> char                                                                                                               <* 
 *> GRAPH_cum_deps          (void)                                                                                     <* 
 *> {                                                                                                                  <* 
 *>    int         i           =    0;                                                                                 <* 
 *>    char        x_lvl       =    0;                                                                                 <* 
 *>    int         c           =    0;                                                                                 <* 
 *>    tEDGE      *x_pred      = NULL;                                                                                 <* 
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

char*
NODE_line               (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        s           [LEN_DESC]  = "";
   char        t           [LEN_HUND]  = "";
   char        u           [LEN_HUND]  = "";
   /*---(empty)--------------------------*/
   if (n < 0 || n >= g_nnode) {
      snprintf (my.unit_answer, LEN_RECD, "GRAPH node  (%2d) : ·                    · ·  · ·                    ·                     · ·    · ·                    ·                      ´ åæ", n);
      return my.unit_answer;
   }
   /*---(prepare)------------------------*/
   /*> if (g_nodes [n].n_cpred > 0)  sprintf (t, "%2d %-20.20s %-20.20s %2d %c", g_nodes [n].n_cpred, ((g_nodes [n].n_cpred)->e_beg)->n_name, ((g_nodes [n].n_tpred)->e_beg)->n_name, g_nodes [n].n_filled, g_nodes [n].n_ready);   <* 
    *> else                         strcpy  (t, " · ·                    ·                     · ·");                                                                                                                               <* 
    *> if (g_nodes [n].n_csucc > 0)  sprintf (u, "%2d %-20.20s %-20.20s", g_nodes [n].n_csucc, ((g_nodes [n].n_hsucc)->e_end)->n_name, ((g_nodes [n].n_tsucc)->e_end)->n_name);                                                     <* 
    *> else                         strcpy  (u, " · ·                    ·                     ·");                                                                                                                                 <* 
    *> if      (g_nodes [n].n_level <  0)  strcpy (s, "-");                                                                                                                                                                         <* 
    *> else if (g_nodes [n].n_level >  9)  strcpy (s, "Ï");                                                                                                                                                                         <* 
    *> else                                sprintf (s, "%c", g_nodes [n].n_level + '0');                                                                                                                                            <*/
   /*---(concatenate)--------------------*/
   snprintf (my.unit_answer, LEN_RECD, "GRAPH node  (%2d) : %-20.20s %c %-1.1s %-49.49s   %-44.44s   ´ å%sæ", n, g_nodes [n].n_name, g_nodes [n].n_focus, s, t, u, g_nodes [n].n_deps);
   /*---(complete)-----------------------*/
   return my.unit_answer;
}

char
NODE_dump               (void)
{
   int         i           =    0;
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   DEBUG_PROG   yLOG_value   ("g_nnode"   , g_nnode);
   for (i = 0; i <  g_nnode; ++i) {
      DEBUG_PROG   yLOG_complex ("node"      , "%3d  %-25.25s   %3dp   %3ds", i, g_nodes [i].n_name, g_nodes [i].n_cpred, g_nodes [i].n_csucc);
      printf ("%s\n", GRAPH_node_line (i));
   }
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}
