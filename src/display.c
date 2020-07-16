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

void			print_traceroute(t_tracert_data *runtime, t_loopdata *ld)
{
	dprintf(2, "ft_traceroute to %s (%s), %d hops max, %d byte packets\n",
			runtime->target_str, runtime->target_ipv4,
			runtime->max_ttl, runtime->totalsize);
	ld->request_nb = 1;
	ld->reached_target = 0;
}

#ifdef BONUS_H

static void		print_reverse(t_tracert_data *runtime,
						struct sockaddr_in *raddr)
{
	char	fqdn[256];

	ft_bzero(fqdn, 256);
	if (!(runtime->options & OPT_NOMAPPING))
	{
		reverse_target(raddr, fqdn);
		dprintf(2, " %s (%s) ", (ft_strlen(fqdn) == 0)
			? runtime->current_responder : fqdn,
			runtime->current_responder);
	}
	else
		dprintf(2, " %s ", runtime->current_responder);
}

#else

static void		print_reverse(t_tracert_data *runtime,
							struct sockaddr_in *raddr)
{
	(void)raddr;
	dprintf(2, " %s ", runtime->current_responder);
}

#endif

void			print_stats(t_tracert_data *runtime, struct sockaddr_in *raddr,
	t_timer *tm)
{
	char	fqdn[256];

	ft_bzero(fqdn, 256);
	if (runtime->current_responder == NULL)
	{
		runtime->current_responder = ft_strdup(inet_ntoa(raddr->sin_addr));
		print_reverse(runtime, raddr);
	}
	else if (ft_strequ(runtime->current_responder,
					inet_ntoa(raddr->sin_addr)) == 0)
	{
		ft_strdel(&runtime->current_responder);
		runtime->current_responder = ft_strdup(inet_ntoa(raddr->sin_addr));
		print_reverse(runtime, raddr);
	}
	dprintf(2, " %.3f ms ", plot_timer(tm));
}
