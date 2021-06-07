LIB = libasm.a
LIB_BONUS = libasm_bonus.a
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
	FLAGS = -g
endif

################################################################################

$(LIB): $(OBJ)
	ar -rcs $@ $^ 

$(LIB_BONUS) : $(OBJ) $(OBJ_BONUS)
	ar -rcs $@ $^ 

$(OBJDIR)/%.o: $(SRCDIR)/%.s
	mkdir -p $(@D)
	nasm -fmacho64 $(FLAGS) $< -o $@

$(OBJDIR)/$(TESTDIR)/%.o: $(TESTDIR)/%.c
	mkdir -p $(@D)
	gcc -I $(INCDIR) -I $(TESTDIR) -MMD $< $(FLAGS) -c -o $@

$(TESTBIN): $(LIB_BONUS) $(OBJ_TEST)
	gcc -lasm_bonus -L . $(OBJ_TEST) -o $(TESTBIN)

################################################################################

DEP = $(wildcard $(OBJDIR)/$(TESTDIR)/*.d)

-include $(DEP)

################################################################################

.PHONY: all clean fclean re bonus test

.DEFAULT_GOAL: all

all: $(LIB)

bonus: $(LIB_BONUS)

test: all bonus $(TESTBIN)
	./$(TESTBIN)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(LIB) $(LIB_BONUS) $(TESTBIN)

re: fclean all

