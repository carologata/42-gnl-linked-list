#include "get_next_line.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	u;

	str = (char *)s;
	u = (unsigned char)c;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == u)
		{
			return (&str[i + 1]);
		}
		i++;
	}
	if (str[i] == c)
		return (&str[i]);
	return (0);
}

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

int get_line_length(t_list *next_line)
{
	int i;
	int count;
	t_list *cursor;

	cursor = next_line;

	count = 0;
	while(cursor != NULL)
	{
		i = 0;
		while(cursor->str[i] != '\n' && cursor->str[i] != '\0')
		{
			i++;
			count++;
		}
		cursor = cursor->next;
	}
	return (count);
}

char *get_line(t_list *next_line)
{
    t_list *cursor;
	char *line;
	int line_length;
	int i;
	int j;

	cursor = next_line;
	line_length = get_line_length(next_line);
	line = ft_calloc((line_length + 1), 1);
	if(line == NULL)
		return (NULL);
	
	j = 0;
	while(cursor != NULL)
	{
		i = 0;
		while(cursor->str[i] != '\n' && cursor->str[i] != '\0')
			line[j++] = cursor->str[i--];
		if(cursor->str[i] == '\n')
			line[j] = '\n';
		cursor = cursor->next;
	}

	return (line);    
}

void update_next_line(t_list **ptr)
{
	t_list *last;
	t_list *new_node;
	char *rest_line;
	int rest_len;

	last = ft_lstlast(*ptr);

	while(last->str[i] != '\n' && last->str[i] != '\0')
		last[i++];
	if(last->str[i] == '\0')
	{

	}
	i++;
	rest_len = 0;
	while(last->str[i] != '\0')
	{
	}	rest_len++;
		
	rest_line = malloc(rest_len);
	while(last->str[i] != '\0')

	new_node = ft_lstnew(rest_line);

}

void get_next_line(fd)
{
    char *buffer;
    char *line;
    static t_list *next_line;
    t_list *new_buff_node;
    int bytes_read;

    while(!ft_strchr(buffer, '\n') && bytes_read > 0)
    {
        buffer = ft_calloc(BUFFER_SIZE, 1);
        
        bytes_read = read(fd, buffer, BUFFER_SIZE);

        buffer[bytes_read] = '\0';
        
        new_buff_node = ft_lstnew(buffer);
        
        if(next_line == NULL)
            next_line = ft_lstnew(buffer);
        else
            ft_lstadd_back(&next_line, new_buff_node);
    }

    line = get_line(next_line);
	update_next_line(&next_line);    
}

#include <stdio.h>
#include <fcntl.h>
int main(void)
{
    int i;
    int fd;
    char *res;

    i = 0;  

    fd = open("teste.txt", O_RDWR);

    get_next_line(fd);

    // while(i < 8)
    // {
    //     res = get_next_line(fd);
    //     printf("%d: %s", i, res);
    //     free(res);
    //     i++;
    // }
}