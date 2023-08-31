#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct c_list
{
	char			*str;
	struct c_list	*next;
}					t_list;

void				*ft_calloc(size_t nmemb, size_t size);
t_list				*ft_lstnew(char *str);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst);
int					get_line_length(t_list *next_line);
char				*separate_line(t_list *next_line);
void				update_next_line(t_list **ptr);
int					ft_find_newline(t_list *next_line);
char				*get_next_line(int fd);

#endif