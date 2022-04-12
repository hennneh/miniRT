#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;

	if (lst == NULL)
		return (NULL);
	dest = ft_lstnew(f(lst->content));
	if (dest == NULL)
		return (NULL);
	if (lst->next != NULL)
	{
		dest->next = ft_lstmap(lst->next, f, del);
		if (dest->next == NULL)
		{
			del(dest->content);
			free(dest);
			return (NULL);
		}
	}
	else
		dest->next = NULL;
	return (dest);
}
