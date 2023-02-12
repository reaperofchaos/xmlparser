# change application name here (executable output name)
TARGET=XMLParser
TESTTARGET=Test_XMLParser
LIBTARGET=libxmlparser.so
ARCHIVELIBTARGET=libxmlparser.a
# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall -Wextra -Werror
#src directory
SRCDIR=src
#object directoy
CPPVERSION=-std=c++17
LIBFLAGS=-fPIC
OBJDIR=obj
#Libraries
GTEST = /usr/local/lib/libgtest.a
LIBRARYPATH=-L/Users/jacobconner/Desktop/typescriptParser/libs
TOKENIZER=-ltokenizer
XMLPARSER=-lxmlparser
#Folder with header files
INCLUDES=-I include
#target directory

CCFLAGS=$(DEBUG) ${CPPVERSION} $(OPT) $(WARN) -pipe ${INCLUDES}

# linker
LD=g++
LDFLAGS=-lstdc++

OBJS=$(OBJDIR)/main.o\
$(OBJDIR)/Writer.o \

all: $(OBJS)
	$(LD) ${LIBRARYPATH} -o $(TARGET) $(OBJS)  $(LDFLAGS) ${XMLPARSER} ${TOKENIZER} 

$(OBJDIR)/Writer.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Writer.cpp -o $(OBJDIR)/Writer.o

$(OBJDIR)/main.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

clean:
	rm -rf $(OBJDIR)/*.o $(TARGET) $(LIBTARGET) $(ARCHIVELIBTARGET)