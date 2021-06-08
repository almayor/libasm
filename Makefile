LIB = libasm.a
TESTBIN = runtests

################################################################################

SRCDIR = src
OBJDIR = obj
INCDIR = include
TESTDIR = test

################################################################################

SRC = $(wildcard $(SRCDIR)/*.s)
OBJ = $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%.o, $(SRC))

SRC_BONUS = $(wildcard $(SRCDIR)/bonus/*.s)
OBJ_BONUS = $(patsubst $(SRCDIR)/%.s, $(OBJDIR)/%.o, $(SRC_BONUS))

SRC_TEST = $(wildcard $(TESTDIR)/*.c)
OBJ_TEST = $(patsubst $(TESTDIR)/%.c, $(OBJDIR)/$(TESTDIR)/%.o, $(SRC_TEST))

################################################################################

ifeq ($(DEBUG), 1) 
	FLAGS += -g
endif

################################################################################

ifeq ($(BONUS), 1)
$(LIB): $(OBJ) $(OBJ_BONUS)
	ar -rcs $@ $^
else
$(LIB): $(OBJ)
	ar -rcs $@ $^ 
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	mkdir -p $(@D)
	nasm -fmacho64 $(FLAGS) $< -o $@

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.c
	mkdir -p $(@D)
	gcc -I $(INCDIR) -I $(TESTDIR) -MMD $< $(FLAGS) -c -o $@

$(TESTBIN): $(OBJ_TEST)
	BONUS=1 make all
	gcc -lasm -L . $(OBJ_TEST) -o $(TESTBIN)

################################################################################

DEP = $(wildcard $(OBJDIR)/$(TESTDIR)/*.d)

-include $(DEP)

################################################################################

.PHONY: all clean fclean re bonus test

.DEFAULT_GOAL: all

all: $(LIB)

bonus:
	BONUS=1 make all

test: $(TESTBIN)
	./$(TESTBIN)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIB) $(TESTBIN)

re: fclean all
