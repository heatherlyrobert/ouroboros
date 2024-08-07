#================================[[ beg-code ]]================================#



#===(manditory)============================================#
# basename of executable, header, and all code files
NAME_BASE  = ouroboros
# additional standard and outside libraries
LIB_STD    = 
# all heatherly libraries used, debug versions whenever available
LIB_MINE   = -lySTR_debug -lySORT_debug -lyPARSE_debug -lyUNIT_debug -lyJOBS_debug -lyENV_debug -lyASCII_debug
# all heatherly libraries used only in unit tests
LIB_MYUNIT = 
# directory for production code, no trailing slash
INST_DIR   = /usr/local/bin



#===(optional)=============================================#
# extra include directories required
INC_MINE   = 
# utilities generated, separate from main program
NAME_UTIL  = 
# libraries only for the utilities
LIB_UTIL   = 



#===(post-processing)======================================#
# create a rule for...

#install_prep       :

#remove_prep        :



#===(master template)======================================#
include /usr/local/sbin/zeno_make



#===(post-processing)======================================#
# create a rule for...

#install_post       :

#remove_post        :



#================================[[ end-code ]]================================#
