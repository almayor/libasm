#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "libasm.h"

#define GREEN	"\e[0;32m"
#define YELLOW	"\e[0;33m"
#define	RED		"\e[0;31m"
#define RESET	"\e[0m"

inline static void	test(int passed) {
	if (passed) {
		printf(GREEN "v " RESET);
	} else {
		printf(RED "x\n\nFAILED\n" RESET);
		exit(1);
	}
}

static void			test_strlen(void) {
	printf("\n* ft_strlen:\t");

	test(strlen("") == ft_strlen(""));
	test(strlen("he\12llo") == ft_strlen("he\12llo"));
	test(strlen("HOW ARE YOU BABY") == ft_strlen("HOW ARE YOU BABY"));
	test(strlen("DANCE DANCE I WANNA DANCE") == ft_strlen("DANCE DANCE I WANNA DANCE"));
}

static void			test_strcpy(void) {
	char	buf[1024];

	printf("\n* ft_strcpy:\t");

	ft_strcpy("", buf);
	test(strcmp(buf, "") == 0);
	ft_strcpy("how \4are you?\5", buf);
	test(strcmp(buf, "how \4are you?\5") == 0);
	ft_strcpy("I AM TH*RSTY", buf);
	test(strcmp(buf, "I AM TH*RSTY") == 0);
	ft_strcpy("LET IT GO LET IT GOOOO", buf);
	test(strcmp(buf, "LET IT GO LET IT GOOOO") == 0);
}

static void			test_strcmp(void) {
	printf("\n* ft_strcmp:\t");

	test(ft_strcmp("", "") == 0);
	test(ft_strcmp("ABC", "AB") > 0);
	test(ft_strcmp("ABC", "ABC") == 0);
	test(ft_strcmp("AB", "ABC") < 0);
	test(ft_strcmp("HOW DO YOU DO?", "HOW DO YOU DO") > 0);
	test(ft_strcmp("this is lowercase", "this is lowercase") == 0);
}

static void			test_write(void) {
	char	buf[1024];
	int		fds[2];
	int		rc;

	printf("\n* ft_write:\t");

	if (pipe(fds)) {
		printf(YELLOW "\n\nSYSCALL ERROR\n" RESET);
		exit(errno);
	}

	rc = ft_write(fds[1], "Much WOW So COOL", strlen("Much WOW So COOL"));
	buf[read(fds[0], buf, strlen("Much WOW So COOL"))] = 0;
	test(rc == strlen("Much WOW So COOL") && errno == 0 && strcmp(buf, "Much WOW So COOL") == 0);

	rc = ft_write(fds[1], "", strlen(""));
	buf[read(fds[0], buf, strlen(""))] = 0;
	test(rc == strlen("") && errno == 0 && strcmp(buf, "") == 0);

	rc = ft_write(fds[1], "A\23", strlen("A\23"));
	buf[read(fds[0], buf, strlen("A\23"))] = 0;
	test(rc == strlen("A\23") && errno == 0 && strcmp(buf, "A\23") == 0);

	rc = ft_write(-1, "i love cream cheese", strlen("i love cream cheese"));
	test(rc == -1 && errno == EBADF);
	errno = 0;

	close(fds[0]);
	close(fds[1]);
}

static void			test_read(void) {
	char	buf[1024];
	int		fds[2];
	int		rc;

	printf("\n* ft_read:\t");

	if (pipe(fds)) {
		printf(YELLOW "\n\nSYSCALL ERROR\n" RESET);
		exit(errno);
	}

	write(fds[1], "Much WOW So COOL", strlen("Much WOW So COOL"));
	rc = ft_read(fds[0], buf, strlen("Much WOW So COOL"));
	buf[rc] = 0;
	test(rc == strlen("Much WOW So COOL") && errno == 0 && strcmp(buf, "Much WOW So COOL") == 0);

	write(fds[1], "", strlen(""));
	rc = ft_read(fds[0], buf, strlen(""));
	buf[rc] = 0;
	test(rc == strlen("") && errno == 0 && strcmp(buf, "") == 0);

	write(fds[1], "A", strlen("A"));
	rc = ft_read(fds[0], buf, strlen("A"));
	buf[rc] = 0;
	test(rc == strlen("A") && errno == 0 && strcmp(buf, "A") == 0);

	strcpy(buf, "untouched message");
	rc = ft_read(-1, buf, 0);
	test(rc == -1 && errno == EBADF && strcmp(buf, "untouched message") == 0);
	errno = 0;

	strcpy(buf, "untouched message");
	rc = ft_read(-1, buf, 10);
	test(rc == -1 && errno == EBADF && strcmp(buf, "untouched message") == 0);
	errno = 0;

	close(fds[0]);
	close(fds[1]);
}

static void			test_strdup(void) {
	int 	rc;
	char	*dup;

	printf("\n* ft_strdup:\t");

	dup = ft_strdup("ginger men are everywhere!");
	test(strcmp(dup, "ginger men are everywhere!") == 0 && errno == 0);
	free(dup);

	dup = ft_strdup("");
	test(strcmp(dup, "") == 0 && errno == 0);
	free(dup);

	dup = ft_strdup("Lord John Grey is a true gentleman!");
	test(strcmp(dup, "Lord John Grey is a true gentleman!") == 0 && errno == 0);
	free(dup);
}

int		main(void) {
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();

	printf("\n\n" GREEN "PASSED\n" RESET);
}
