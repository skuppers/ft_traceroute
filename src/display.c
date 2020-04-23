/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void			print_stats(t_tracert_data *runtime, struct sockaddr_in *raddr, t_timer *tm)
{
	char	fqdn[256];

	ft_bzero(fqdn, 256);
	if (runtime->current_responder == NULL)
	{
		runtime->current_responder = ft_strdup(inet_ntoa(raddr->sin_addr));
		reverse_target(raddr, fqdn);
		printf(" %s (%s) ", fqdn, runtime->current_responder);
	}
	else if (ft_strequ(runtime->current_responder, inet_ntoa(raddr->sin_addr)) == 0)
	{
		ft_strdel(&runtime->current_responder);
		runtime->current_responder = ft_strdup(inet_ntoa(raddr->sin_addr));
		reverse_target(raddr, fqdn);
		printf(" %s (%s) ", fqdn, runtime->current_responder);
	}
	printf(" %.3f ms ", plot_timer(tm));
}