#
# UTD CS3377 Homework 6
# Alec Borman
# amb161530@utdallas.edu
#

CXX = g++
CXXFLAGS = -Wall -g -std=c++0x -Wno-write-strings
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 


#
# PROJECTNAME is a descriptive name used for the backup target
# This should not contain spaces or special characters

EXECFILE = homework6_Alec_Borman

OBJS = homework6.o


all: $(EXECFILE)

clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

