# change application name here (executable output name)
TARGET=XMLParser

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
OBJDIR=obj
#target directory

CCFLAGS=$(DEBUG) ${CPPVERSION} $(OPT) $(WARN) -pipe
# linker
LD=g++
LDFLAGS=$(PTHREAD) -lstdc++

OBJS=$(OBJDIR)/main.o \
$(OBJDIR)/CharType.o \
$(OBJDIR)/CharType.o \
$(OBJDIR)/CharacterReader.o \
$(OBJDIR)/Tokenizer.o \
# $(OBJDIR)/Writer.o \
# $(OBJDIR)/Printer.o \
# $(OBJDIR)/Prop.o \
# $(OBJDIR)/Node.o \


all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/Symbol.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types/Symbol.cpp -o $(OBJDIR)/Symbol.o


$(OBJDIR)/CharType.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types/CharType.cpp -o $(OBJDIR)/CharType.o

# $(OBJDIR)/Prop.o:
# 	$(CC) -c $(CCFLAGS) $(SRCDIR)/Prop.cpp -o $(OBJDIR)/Prop.o

# $(OBJDIR)/Writer.o:
# 	$(CC) -c $(CCFLAGS) $(SRCDIR)/Writer.cpp -o $(OBJDIR)/Writer.o

# $(OBJDIR)/Node.o:
# 	$(CC) -c $(CCFLAGS) $(SRCDIR)/Node.cpp -o $(OBJDIR)/Node.o

# $(OBJDIR)/Printer.o:
# 	$(CC) -c $(CCFLAGS) $(SRCDIR)/printer.cpp -o $(OBJDIR)/Printer.o

# $(OBJDIR)/Types.o:
# 	$(CC) -c $(CCFLAGS) $(SRCDIR)/Types.cpp -o $(OBJDIR)/Types.o

$(OBJDIR)/CharacterReader.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/CharacterReader.cpp -o $(OBJDIR)/CharacterReader.o

$(OBJDIR)/Tokenizer.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Tokenizer.cpp -o $(OBJDIR)/Tokenizer.o

$(OBJDIR)/main.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o
    
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)