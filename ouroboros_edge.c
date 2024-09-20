/*===============================[[ beg-code ]]===============================*/
#include    "ouroboros.h"



tEDGE   g_edges   [MAX_EDGE];
int     g_nedge     =  0;
char    g_maxlvl    =  0;




/*====================------------------------------------====================*/
/*===----                     create and destroy                       ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
EDGE__wipe              (tEDGE *a_dst)
{
   /*---(link)--------------*/
   a_dst->e_source     = NULL;
   a_dst->e_target     = NULL;
   /*---(working)-----------*/
   a_dst->e_filled     = '-';
   a_dst->e_type       = '-';
   a_dst->e_used       = '-';
   /*---(predecessors)------*/
   a_dst->e_pprev      = NULL;
   a_dst->e_pnext      = NULL;
   /*---(successors)--------*/
   a_dst->e_sprev      = NULL;
   a_dst->e_snext      = NULL;
   /*---(sorting)-----------*/
   a_dst->e_unique [0] = '\0';
   a_dst->e_ysort      = NULL;
   /*---(done)--------------*/
   return 0;
}

char
EDGE__new               (tNODE *a_source, tNODE *a_target, char a_force, tEDGE **r_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_unique    [LEN_DESC]  = "";
   tEDGE      *x_new       = NULL;
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
   DEBUG_DATA   yLOG_point   ("a_source"  , a_source);
   --rce;  if (a_source == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->n_name"  , a_source->n_name);
   DEBUG_DATA   yLOG_point   ("a_target"  , a_target);
   --rce;  if (a_target == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_DATA   yLOG_info    ("->n_name"  , a_target->n_name);
   /*---(make key)-----------------------*/
   snprintf (x_unique, LEN_DESC, "%-20.20s Ö %s", a_source->n_name, a_target->n_name);
   /*---(check for duplicate)------------*/
   rc = ySORT_by_name (B_EDGE, x_unique, &x_new);
   DEBUG_DATA   yLOG_point   ("x_exist"   , x_new);
   --rce;  if (x_new != NULL) {
      if (r_new != NULL)  *r_new = x_new;
      DEBUG_DATA   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL) {
      ++x_tries;
      x_new = (tEDGE *)  malloc (sizeof (tEDGE));
      if (x_tries > 3)   break;
   }
   DEBUG_DATA   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_DATA   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(wipe)---------------------------*/
   EDGE__wipe (x_new);
   /*---(populate base)------------------*/
   x_new->e_source = a_source;
   x_new->e_target = a_target;
   ystrlcpy (x_new->e_unique, x_unique, LEN_DESC);
   /*---(hook tsae)----------------------*/
   rc = ySORT_hook (B_EDGE, x_new, x_new->e_unique, &(x_new->e_ysort));
   DEBUG_DATA   yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ySORT_prepare (B_EDGE);
   DEBUG_DATA   yLOG_value   ("prep edges", rc);
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
EDGE__free              (tEDGE **r_old)
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
   rc = ySORT_unhook (&((*r_old)->e_ysort));
   DEBUG_DATA   yLOG_value   ("wave"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_DATA   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   rc = ySORT_prepare (B_EDGE);
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
EDGE_purge              (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tEDGE      *x_edge      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_enter   (__FUNCTION__);
   /*---(walk entries)-------------------*/
   rc = ySORT_by_cursor (B_EDGE, YDLST_HEAD, &x_edge);
   DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_edge);
   while (rc >= 0 && x_edge != NULL) {
      /*> rc = EDGE_remove (x_edge->n_name);                                          <*/
      if (rc < 0)  break;
      rc = ySORT_by_cursor (B_EDGE, YDLST_HEAD, &x_edge);
      DEBUG_CONF  yLOG_complex ("entry"     , "%4d, %p", rc, x_edge);
   }
   /*---(complete)-----------------------*/
   DEBUG_DATA   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
EDGE_init               (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = ySORT_btree (B_EDGE, "edges");
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
EDGE_wrap               (void)
{
   EDGE_purge ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       edge handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___EDGES___________o () { return; }











char
EDGE_add                (char a_type, char a_beg [LEN_TITLE], int a_end)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                 <* 
    *> char        rce         =  -10;                                                          <* 
    *> int         x_beg       =    0;                                                          <* 
    *> tEDGE      *x_pred      = NULL;                                                          <* 
    *> /+---(header)-------------------------+/                                                 <* 
    *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                <* 
    *> /+---(defense)------------------------+/                                                 <* 
    *> DEBUG_PROG   yLOG_point   ("a_beg"     , a_beg);                                         <* 
    *> --rce;  if (a_beg == NULL) {                                                             <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_PROG   yLOG_info    ("a_beg"     , a_beg);                                         <* 
    *> --rce;  if (strcmp (a_beg, "") == 0) {                                                   <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_PROG   yLOG_value   ("a_end"     , a_end);                                         <* 
    *> --rce;  if (a_end < 0) {                                                                 <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_PROG   yLOG_value   ("g_nnode"   , g_nnode);                                       <* 
    *> --rce;  if (a_end >= g_nnode) {                                                          <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_PROG   yLOG_info    ("name"      , g_nodes [a_end].n_name);                        <* 
    *> /+---(check for duplicate)------------+/                                                 <* 
    *> x_pred = g_nodes [a_end].n_hpred;                                                        <* 
    *> while (x_pred != NULL) {                                                                 <* 
    *>    if (strcmp (x_pred->e_beg->n_name, a_beg) == 0) {                                     <* 
    *>       DEBUG_PROG   yLOG_note    ("found pre-existing, duplicate edge");                  <* 
    *>       DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                          <* 
    *>       return 1;                                                                          <* 
    *>    }                                                                                     <* 
    *>    x_pred = x_pred->e_pnext;                                                             <* 
    *> }                                                                                        <* 
    *> DEBUG_PROG   yLOG_note    ("not duplicate");                                             <* 
    *> /+---(beg-point on edge)--------------+/                                                 <* 
    *> x_beg = GRAPH_add_node (a_beg);                                                          <* 
    *> DEBUG_PROG   yLOG_value   ("x_beg"     , x_beg);                                         <* 
    *> --rce;  if (x_beg < 0) {                                                                 <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> --rce;  if (x_beg == a_end) {                                                            <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> /+---(set type)-----------------------+/                                                 <* 
    *> g_edges [g_nedge].e_type = a_type;                                                       <* 
    *> /+---(beg-point on edge)--------------+/                                                 <* 
    *> g_edges [g_nedge].e_nbeg = x_beg;                                                        <* 
    *> g_edges [g_nedge].e_beg  = &(g_nodes [x_beg]);                                           <* 
    *> /+---(beg-point on node)--------------+/                                                 <* 
    *> if (g_nodes [x_beg].n_hsucc == NULL) { /+ first +/                                       <* 
    *>    DEBUG_PROG   yLOG_note    ("first successor");                                        <* 
    *>    g_nodes [x_beg].n_hsucc = &(g_edges [g_nedge]);                                       <* 
    *> } else {  /+                          append +/                                          <* 
    *>    DEBUG_PROG   yLOG_note    ("append successor");                                       <* 
    *>    (g_nodes [x_beg].n_tsucc)->e_snext = &(g_edges [g_nedge]);                            <* 
    *> }                                                                                        <* 
    *> g_nodes [x_beg].n_tsucc = &(g_edges [g_nedge]);                                          <* 
    *> ++(g_nodes [x_beg].n_csucc);                                                             <* 
    *> /+---(end-point on edge)--------------+/                                                 <* 
    *> g_edges [g_nedge].e_nend = a_end;                                                        <* 
    *> g_edges [g_nedge].e_end  = &(g_nodes [a_end]);                                           <* 
    *> /+---(end-point on node)--------------+/                                                 <* 
    *> if (g_nodes [a_end].n_hpred == NULL) { /+ first +/                                       <* 
    *>    DEBUG_PROG   yLOG_note    ("first predecessor");                                      <* 
    *>    g_nodes [a_end].n_hpred = &(g_edges [g_nedge]);                                       <* 
    *> } else {  /+                          append +/                                          <* 
    *>    DEBUG_PROG   yLOG_note    ("append predecessor");                                     <* 
    *>    (g_nodes [a_end].n_tpred)->e_pnext = &(g_edges [g_nedge]);                            <* 
    *> }                                                                                        <* 
    *> g_nodes [a_end].n_tpred = &(g_edges [g_nedge]);                                          <* 
    *> ++(g_nodes [a_end].n_cpred);                                                             <* 
    *> /+---(counter)------------------------+/                                                 <* 
    *> ++g_nedge;                                                                               <* 
    *> DEBUG_PROG   yLOG_value   ("g_nedge"   , g_nedge);                                       <* 
    *> /+---(check for solo)-----------------+/                                                 <* 
    *> /+> DEBUG_PROG   yLOG_info    ("b_name"    , g_nodes [x_beg].n_name);              <+/   <* 
    *> /+> DEBUG_PROG   yLOG_info    ("e_name"    , g_nodes [a_end].n_name);              <+/   <* 
    *> /+> if (strcmp (g_nodes [x_beg].n_name, "zenodotus") == 0) {                       <*    <* 
    *>  *>    if (strstr (g_nodes [a_end].n_name, "_solo") != NULL) {                     <*    <* 
    *>  *>       DEBUG_PROG   yLOG_note    ("call to add tie to _solo");                  <*    <* 
    *>  *>       INCL_add_by_name ("zenodotus", a_end);                                   <*    <* 
    *>  *>    }                                                                           <*    <* 
    *>  *> }                                                                              <+/   <* 
    *> /+---(complete)-----------------------+/                                                 <* 
    *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                <* 
    *> return 0;                                                                                <*/
}

char EDGE_real         (char a_beg [LEN_TITLE], int a_end) { return EDGE_add ('r', a_beg, a_end); }
char EDGE_virt         (char a_beg [LEN_TITLE], int a_end) { return EDGE_add ('v', a_beg, a_end); }

char
EDGE_dump               (void)
{
   /*> int         i           =    0;                                                                                                                                        <* 
    *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                                                                                                              <* 
    *> DEBUG_PROG   yLOG_value   ("g_nedge"   , g_nedge);                                                                                                                     <* 
    *> for (i = 0; i <  g_nedge; ++i) {                                                                                                                                       <* 
    *>    printf ("%3d  %3d %-25.25s  %3d %-25.25s¦", i, g_edges [i].e_nbeg, g_nodes [g_edges [i].e_nbeg].n_name, g_edges [i].e_nend, g_nodes [g_edges [i].e_nend].n_name);   <* 
    *> }                                                                                                                                                                      <* 
    *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                                                                                                              <* 
    *> return 0;                                                                                                                                                              <*/
}
