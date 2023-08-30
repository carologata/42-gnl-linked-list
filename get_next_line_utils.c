#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*r;
	size_t			size_t_max;
	size_t			i;
	unsigned char	*str;
	size_t			total_size;

	total_size = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	size_t_max = -1;
	if (size != 0 && (nmemb >= size_t_max / size))
		return (NULL);
	r = malloc(nmemb * size);
	if (r == NULL)
		return (NULL);
	str = (unsigned char *)r;
	i = 0;
	while (i < total_size)
	{
		str[i] = 0;
		i++;
	}
	return (r);
}

t_list	*ft_lstnew(char *str)
{
	t_list	*new_node;

	new_node = malloc(1 * sizeof(t_list));
	if (new_node == NULL)
	{
		return (NULL);
	}
	new_node->str = str;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current != NULL)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*current;
	t_list	*aux;

	if (lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		aux = current->next;
		free(current->str);
        current->str = NULL;
        current->next = NULL;
		free(current);
		current = aux;
	}
	*lst = NULL;
}