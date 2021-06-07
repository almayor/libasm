LIB = libasm.a

SRCDIR = src
OBJDIR = obj
INCDIR = include
TESTDIR = test
TESTBIN = runtests

SRC = $(wildcard $(SRCDIR)/*.s)
OBJ = $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%.o, $(SRC))

$(LIB): $(OBJ)
	ar -rcs $@ $^ 

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	mkdir -p $(OBJDIR)
	nasm -fmacho64 $< -o $@

$(TESTBIN): $(LIB) $(wildcard $(TESTDIR)/*.c)
	gcc -I $(INCDIR) -lasm -L . $(TESTDIR)/* -o $(TESTBIN)

.PHONY: all clean fclean re bonus test

.DEFAULT: all

all: $(LIB)

test: all $(TESTBIN)
	./$(TESTBIN)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIB) $(TESTBIN)

re: fclean all

