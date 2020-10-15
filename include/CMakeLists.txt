#
# Create the "configure.hpp" file
# 
# include/configure.hpp.in --> build/include/configure.hpp
#
#configure_file(
#	"${MY_PROJECT_INCDIR}/configure.hpp.in"
#	"${MY_INSTALL_INCDIR}/configure.hpp"
#)

#
# build/include/configure.hpp --> include/configure.hpp       
#
#INSTALL(FILES "${MY_INSTALL_SRCDIR}/configure.hpp"
#        DESTINATION "${MY_INSTALL_INCDIR}")     

#
# Copy all header files to the installation folder
#
install(DIRECTORY ${MY_PROJECT_INCDIR} DESTINATION ${MY_INSTALL_PREFIX})