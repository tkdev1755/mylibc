# Nom de l'exécutable par défaut
TARGET = tp

# Nom de l'exécutable pour l'option -linux
LINUX_TARGET = tpL

CMD_TARGET = tpc

#Nom de l'executable du parser de questions
PARSER_TARGET = qPrs

# Compilateur et options
CC = gcc
CFLAGS = -g -Wall
LDFLAGS =
#Fichiers parser de questions
QPARSER_SRC = questionsParser.c
QPARSER_OBJ = $(QPARSER_SRC:.c=.o)

# Fichiers sources
SRCS = main.c mini_lib.c mini_memory.c mini_io.c mini_string.c

# Fichier Commande systèmes
CMD_SRC = terminalTest.c systemCommands.c mini_lib.c mini_memory.c mini_io.c mini_string.c
CMD_OBJ = $(CMD_SRC:.c=.o)


# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Règle par défaut : compilation de l'exécutable
all: $(TARGET)

# Compilation de l'exécutable par défaut
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Option spéciale -linux : compilation de l'exécutable pour Linux
linux: CFLAGS += -DLINUX
linux: $(LINUX_TARGET)

$(LINUX_TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(LINUX_TARGET) $(OBJS) $(LDFLAGS)

$(CMD_TARGET) : $(CMD_OBJ)
	$(CC) $(CFLAGS) -o $(CMD_TARGET) $(CMD_OBJ) $(LDFLAGS)
qPrs: $(QPARSER_OBJ)
	$(CC) $(CFLAGS) $(QPARSER_OBJ) -o qprs

# Règle pour nettoyer les fichiers objets et exécutables
clean:
	rm -f $(OBJS) $(TARGET) $(LINUX_TARGET)

cleanAll:
	rm -f $(QPARSER_OBJ) qParser $(OBJS) $(TARGET) $(LINUX_TARGET)

# Règle pour forcer la recompilation
.PHONY: all clean linux