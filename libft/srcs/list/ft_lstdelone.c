/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:06:45 by cempassi          #+#    #+#             */
/*   Updated: 2019/07/03 22:30:32 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "ft_malloc.h"
#include <stdio.h>

void	ft_lstdelone(t_list **alst, void (*del)(void *))
{
	if (!alst || !*alst)
		return ;
	if (del)
		del((*alst)->data);
	if ((*alst)->data)
	{
		printf("Freeing meta\n");
		ft_memdel(&(*alst)->data);
	}
	printf("Freeing t_list\n");
	free(*alst);
	*alst = NULL;
}
