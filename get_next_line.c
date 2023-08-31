#include "get_next_line.h"

int	get_line_length(t_list *cursor)
{
	int	i;
	int	count;

	count = 0;
	while (cursor != NULL)
	{
		i = 0;
		while (cursor->str[i] != '\0')
		{
			if (cursor->str[i] == '\n')
				return (count);
			i++;
			count++;
		}
		cursor = cursor->next;
	}
	return (count);
}

char	*separate_line(t_list *cursor)
{
	char	*line;
	int		line_length;
	int		i;
	int		j;

	line_length = get_line_length(cursor);
	line = ft_calloc((line_length + 2), 1);
	if (line == NULL)
		return (NULL);
	j = 0;
	while (cursor != NULL)
	{
		i = 0;
		while (cursor->str[i] != '\n' && cursor->str[i] != '\0')
			line[j++] = cursor->str[i++];
		if (cursor->str[i] == '\n')
		{
			line[j] = '\n';
			return (line);
		}
		cursor = cursor->next;
	}
	return (line);
}

void	update_next_line(t_list **ptr)
{
	t_list	*last;
	t_list	*new_node;
	char	*rest_line;
	int		rest_len;
	int		i;
	int		start;

	last = ft_lstlast(*ptr);
	i = 0;
	while (last->str[i] != '\n' && last->str[i] != '\0')
		i++;
	if (last->str[i] == '\0')
	{
		ft_lstclear(ptr);
		*ptr = NULL;
		return ;
	}
	i++;
	if (last->str[i] == '\0')
	{
		ft_lstclear(ptr);
		*ptr = NULL;
		return ;
	}
	start = i;
	rest_len = 0;
	while (last->str[i] != '\0')
		rest_len = i++;
	rest_line = ft_calloc((rest_len + 1), 1);
	i = 0;
	while (last->str[start] != '\0')
	{
		rest_line[i] = last->str[start++];
		i++;
	}
	new_node = ft_lstnew(rest_line);
	ft_lstclear(ptr);
	*ptr = new_node;
}

int	ft_find_newline(t_list *next_line)
{
	t_list	*cursor;
	int		i;

	cursor = next_line;
	while (cursor != NULL)
	{
		i = 0;
		while (cursor->str[i] != '\n' && cursor->str[i] != '\0')
			i++;
		if (cursor->str[i] == '\n')
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

void	read_and_check_newline(int fd, t_list **ptr_next_line,
		char **ptr_buffer, int bytes_read)
{
	t_list	*new_buff_node;

	new_buff_node = NULL;
	while (!ft_find_newline(*ptr_next_line) && bytes_read > 0)
	{
		*ptr_buffer = ft_calloc((BUFFER_SIZE + 1), 1);
		bytes_read = read(fd, *ptr_buffer, BUFFER_SIZE);
		if ((!*ptr_next_line && !*ptr_buffer[0] && !bytes_read)
			|| bytes_read < 0)
		{
			free(*ptr_buffer);
			*ptr_next_line = NULL;
			break ;
		}
		if (bytes_read == 0)
		{
			free(*ptr_buffer);
			break ;
		}
		if (*ptr_next_line == NULL)
			*ptr_next_line = ft_lstnew(*ptr_buffer);
		else
		{
			new_buff_node = ft_lstnew(*ptr_buffer);
			ft_lstadd_back(ptr_next_line, new_buff_node);
			new_buff_node = NULL;
		}
	}
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line;
	static t_list	*next_line;
	int				bytes_read;

	bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_and_check_newline(fd, &next_line, &buffer, bytes_read);
	if(next_line == NULL)
		return (NULL);
	line = separate_line(next_line);
	update_next_line(&next_line);
	return (line);
}

/* #include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int i;
	int fd;
	char *res;

	i = 0;

	fd = open("teste.txt", O_RDWR);
	//1
	res = get_next_line(fd);
	printf("1: %s", res);
	free(res);
	//2
	res = get_next_line(fd);
	printf("1: %s", res);
	free(res);

	close(fd);
	fd = open("teste.txt", O_RDWR);
	//1
	res = get_next_line(fd);
	printf("1: %s", res);
	free(res);
	//2
	res = get_next_line(fd);
	printf("2: %s", res);
	free(res);
	//3
	res = get_next_line(fd);
	printf("3: %s", res);
	free(res);
	//4
	res = get_next_line(fd);
	printf("4: %s", res);
	free(res);
	//5
	res = get_next_line(fd);
	printf("5: %s", res);
	free(res);
	//6
	res = get_next_line(fd);
	printf("6: %s", res);
	free(res);
} */