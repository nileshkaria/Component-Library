##############################################################################
#
#    Makefile created from example : 
#    www.cs.duke.edu/courses/spring04/cps108/resources/makefiles/sample.html
# 
##############################################################################

##############################################################################
# Application-specific variables
# EXEC is the name of the executable file
# SRC_FILES is a list of all source code files that must be 
# to create the executable
##############################################################################
EXEC      = graphutils
LIB_FILE  = libgraph.a
SRC_FILES = src/bfs.cpp \
	src/bipartite.cpp \
	src/connected_components.cpp \
	src/dfs.cpp \
	src/digraph.cpp \
	src/directed_edge.cpp \
	src/edge.cpp \
	src/edge_weighted_digraph.cpp \
	src/edge_weighted_graph.cpp \
	src/graph.cpp \
	src/minimum_spanning_tree.cpp \
	src/strong_connected_components.cpp \
	src/topological_sort.cpp


##############################################################################
SRC_DIR = ./src
LIB_DIR = 
INCLUDE_DIR = ./include

##############################################################################
# Compiler specifications
##############################################################################
CXX = g++
CC = $(CXX)

# What flags should be passed to the compiler
DEBUG_LEVEL     = -g
EXTRA_CCFLAGS   = -Wall -std=c++11
CXXFLAGS        = $(DEBUG_LEVEL) $(EXTRA_CCFLAGS)
CCFLAGS         = $(CXXFLAGS)

# What flags should be passed to the C pre-processor
#   In other words, where should we look for files to include - note,
#   you should never need to include compiler specific directories here
#   because each compiler already knows where to look for its system
#   files (unless you want to override the defaults)

CPPFLAGS        = -I. \
                  -I$(INCLUDE_DIR) -I../dynamic_connectivity/include

# What flags should be passed to the linker
#   In other words, where should we look for libraries to link with - note,
#   you should never need to include compiler specific directories here
#   because each compiler already knows where to look for its system files.

LDFLAGS         = -L. \
                  -L$(SRC_DIR) \
                  -L../dynamic_connectivity \
                  #-R $(LIB_DIR):$(SRC_DIR)

# What libraries should be linked with.
# For example, -lm links with libm.so, the math library.
# If you make a library of your own, say, libscandir.a, you have to link it
# in by adding -lscandir here.
LDLIBS          = 

# All source files have associated object files.
# This line sets `OFILES' to have the same value as `SRC_FILES' but
# with all the .cpp's changed into .o's.
O_FILES         = $(SRC_FILES:%.cpp=%.o)

###########################################################################
# Additional rules make should know about in order to compile our files
###########################################################################
# all is the default rule
all: $(EXEC) 


# exec depends on the object files
# It is made automagically using the LDFLAGS and LOADLIBES variables.
# The .o files are made automagically using the CXXFLAGS variable.
# Static lib is created at the end
$(EXEC): $(O_FILES)
	ar rcs $(LIB_FILE) $(SRC_DIR)/*.o
# to use `makedepend', the target is `depend'
depend:
	makedepend -- $(CXXFLAGS) -- -Y $(SRC_FILES)

# clean up after you're done
clean:
	$(RM) $(O_FILES) core *.rpo *.o $(LIB_FILE)

realclean: clean
	$(RM) $(EXEC)