#ifndef LIBASM_H

# define LIBASM_H

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(const char *s1, const char *s2);
ssize_t	ft_write(int fildes, const char *buf, size_t nbyte);
ssize_t	ft_read(int fildes, void *buf, size_t nbyte);
char	*ft_strdup(const char *s);

// Bonus

typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;

int		ft_atoi_base(char const *str, char const *base);
void	ft_list_push_front(t_list **begin_list, void *data);
size_t	ft_list_size(t_list *begin_list);
void	ft_list_remove_if(t_list **begin_list, void *data_ref,
					int (*cmp)(void *, void *), void (*free_fct)(void *));
void	ft_list_sort(t_list **begin_list,int (*cmp)());

#endif
