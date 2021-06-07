#ifndef TEST_H

# define TEST_H

#define GREEN	"\e[0;32m"
#define YELLOW	"\e[0;33m"
#define	RED		"\e[0;31m"
#define RESET	"\e[0m"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "libasm.h"

static inline void	test(int passed) {
	if (passed) {
		printf(GREEN "v " RESET);
	} else {
		printf(RED "x\n\nFAILED\n" RESET);
		exit(1);
	}
}

// base

void	test_read(void);
void	test_strcmp(void);
void	test_strcpy(void);
void	test_strdup(void);
void	test_strlen(void);
void	test_write(void);

// bonus

void test_list_size(void);
void test_list_push_front(void);
void test_list_remove_if(void);

#endif
