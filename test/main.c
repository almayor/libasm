#include "test.h"

int		main(void) {
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();

	printf("\n\n" GREEN "PASSED\n\n" RESET);

	test_list_size();
	test_list_push_front();
	test_list_remove_if();
	test_list_sort();

	printf("\n\n" GREEN "PASSED\n\n" RESET);
}
