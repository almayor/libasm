#include "test.h"

static void	free_list(t_list *head) {
	t_list *next;

	while (head) {
		next = head->next;
		free(head);
		head = next;
	}
}

static t_list	*create_list(char **data) {
	t_list	*head = NULL;
	t_list	*node1 = NULL, *node2;

	while (*data) {
		if (!(node2 = malloc(sizeof(t_list)))) {
			printf(YELLOW "\n\nSYSCALL ERROR\n" RESET);
			exit(errno);
		}

		if (node1)
			node1->next = node2;
		else
			head = node2;

		node2->data = *data;
		node1 = node2;
		++data;
	}
	node1->next = NULL;
	return head;
}

static int		compare_list(t_list *head, char **data) {
	while (*data) {
		if (!head || strcmp(head->data, *data))
			return 1;
		++data;
		head = head->next;
	}
	return 0;
}

static void		print_list(const t_list *head) {
	while (head) {
		printf("%s -> ", head->data);
		head = head->next;
	}
	printf("(null)\n");
}

void 			test_list_size(void) {
	t_list	*list;

	printf("\n* ft_list_size:\t\t");

	list = create_list((char *[]){"HELLO", "World", "egghead", "CoCOnUTT", NULL});
	test(ft_list_size(list) == 4);
	free_list(list);

	test(ft_list_size(NULL) == 0);

	list = create_list((char *[]){"Cheesecake!!!", NULL});
	test(ft_list_size(list) == 1);
	free_list(list);
}

void 			test_list_push_front(void) {
	t_list	*list;

	printf("\n* ft_list_push_front:\t");

	list = create_list((char *[]){"HELLO", "World", "egghead", "CoCOnUTT", NULL});
	ft_list_push_front(&list, "♡( ◡‿◡ )");
	test(compare_list(list, (char *[]){ "♡( ◡‿◡ )", "HELLO", "World", "egghead", "CoCOnUTT", NULL}) == 0);
	free_list(list);

	list = NULL;
	ft_list_push_front(&list, "♡( ◡‿◡ )");
	test(compare_list(list, (char *[]){"♡( ◡‿◡ )", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"＼(￣▽￣)／", "😇", "😅", NULL});
	ft_list_push_front(&list, "♡( ◡‿◡ )");
	test(compare_list(list, (char *[]){"♡( ◡‿◡ )", "＼(￣▽￣)／", "😇", "😅", NULL}) == 0);
	free_list(list);
}

static void		remove_data(void *data) {
};

static int		compare_data(void *s1, void *s2) {
	return strcmp(s1, s2);
}

void			test_list_remove_if(void) {
	t_list	*list;

	printf("\n* ft_list_remove_if:\t");

	list = create_list((char *[]){"HELLO", "World", "egghead", "egghead", "CoCOnUTT", NULL});
	ft_list_remove_if(&list, "egghead", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"HELLO", "World", "CoCOnUTT", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"HELLO", "World", "egghead", "egghead", "CoCOnUTT", NULL});
	ft_list_remove_if(&list, "HELLO", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"World", "egghead", "egghead", "CoCOnUTT", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"HELLO", "World", "egghead", "HELLO", "egghead", "CoCOnUTT", NULL});
	ft_list_remove_if(&list, "HELLO", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"World", "egghead", "egghead", "CoCOnUTT", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"HELLO", "World", "egghead", "BLABLA", "egghead", "CoCOnUTT", NULL});
	ft_list_remove_if(&list, "`-`-`-`", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"HELLO", "World", "egghead", "BLABLA", "egghead", "CoCOnUTT", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"egghead", "HELLO", "World", "egghead", "egghead", "CoCOnUTT", "DEV-OPS", "egghead", NULL});
	ft_list_remove_if(&list, "egghead", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"HELLO", "World", "CoCOnUTT", "DEV-OPS", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"licentious", NULL});
	ft_list_remove_if(&list, "egghead", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"licentious", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"licentious", NULL});
	ft_list_remove_if(&list, "licentious", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"licentious", "screpe", NULL});
	ft_list_remove_if(&list, "screpe", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"licentious", NULL}) == 0);
	free_list(list);

	list = create_list((char *[]){"licentious", "screpe", NULL});
	ft_list_remove_if(&list, "licentious", &compare_data, &remove_data);
	test(compare_list(list, (char *[]){"screpe", NULL}) == 0);
	free_list(list);
}

