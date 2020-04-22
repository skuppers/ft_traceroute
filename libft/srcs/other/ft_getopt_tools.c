/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:15:30 by skuppers          #+#    #+#             */
/*   Updated: 2020/04/17 20:16:01 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_getopt.h"
#include "list.h"
#include "memory.h"

int8_t		option_needs_argument(char *opt, char *charset)
{
	char	*target;

	if (opt[0] != '-')
		return (-2);
	else
		opt++;
	target = ft_strchr(charset, *opt);
	if (target != NULL)
	{
		if (target + 1 == '\0')
			return (0);
		else if (*(target + 1) == ':')
			if (*(opt + 1) == '\0')
				return (1);
	}
	return (-1);
}

void	ft_lstiter_elem_ctx(t_list *lst, void *context, void (*f)(void *data, void *ctx))
{
	if (lst)
	{
		f(lst, context);
		ft_lstiter_elem_ctx(lst->next, context, f);
	}
}

void	merge_option_arguments(void *data, void *context)
{
	t_list	*current;
	t_list	*next;
	char	*tmp;

	current = (t_list *)data;
	if (option_needs_argument(current->data, context) == 1)
	{
		next = current->next;
		tmp = ft_strjoin(current->data, next->data);
		ft_strdel((char **)&(current->data));
		current->data = tmp;
		current->data_size = ft_strlen(current->data);
		ft_lstdelnext(current, NULL);
	}
}

t_list	*arrange_options(int ac, char **av, char *charset)
{
	t_list	*options;

	options = ft_getargslst(ac, av);
	ft_lstrev(&options);
	ft_lstiter_elem_ctx(options, charset, merge_option_arguments);
	return (options);
}

int	is_option_or_not(void *opt1, void *opt2)
{
	if (ft_strbeginswith((char *)opt1, "-")
		&& ft_strbeginswith((char *)opt2, "-"))
		return (0);
	else
	{
		if (ft_strbeginswith((char *)opt1, "-"))
			return (-1);
		return (1);
	}
}

int is_option_or_argument(void *opt1, void *opt2)
{
	if (ft_strlen((char *)opt1) > ft_strlen((char *)opt2))
		return (1);
	else
		return (-1);
}

char	*ft_strdup2(void *s)
{
	char	*dst;
	char	*s1;

	s1 = (char *)s;
	if (!s1)
		return (NULL);
	if (!(dst = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1)))
		return (NULL);
	return (ft_strcpy(dst, s1));
}


char	**ft_getopt_order_arguments(int ac, char **av, char *charset)
{
	char	**sorted_avs;
	t_list	*options;

	options = arrange_options(ac, av, charset);
	ft_mergesort(&options, is_option_or_argument);
	ft_mergesort(&options, is_option_or_not);
	sorted_avs = ft_lsttotab(options, ft_strdup2);
	ft_lstdel(&options, NULL);
	return (sorted_avs);
}