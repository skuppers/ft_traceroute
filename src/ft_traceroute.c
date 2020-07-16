/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

uint8_t			traceroute_condition(t_tracert_data *runtime, t_loopdata *ld)
{
	if (ld->reached_target != 0)
		return (0);
	if (ld->request_nb > runtime->max_ttl)
		return (0);
	return (1);
}

void			print_request_nb(t_tracert_data *runtime, t_loopdata *ld)
{
	if (runtime->ttl < 10)
		dprintf(2, " %d ", runtime->ttl);
	else
		dprintf(2, "%d ", runtime->ttl);
	++ld->request_nb;
	ld->packetcount = 0;
}

static void		free_tracert_data(t_tracert_data *runtime)
{
	ft_strdel(&runtime->target_str);
	ft_strdel(&runtime->target_ipv4);
	freeaddrinfo(runtime->result);
}

int32_t			ft_traceroute(t_tracert_data *runtime)
{
	t_loopdata			ld;
	t_timer				pktimer;
	t_socketlst			sockets;

	if (create_sockets(&sockets) != 0)
		return (-1);
	print_traceroute(runtime, &ld);
	while (traceroute_condition(runtime, &ld) == 1)
	{
		print_request_nb(runtime, &ld);
		increase_ttl(runtime, &sockets);
		runtime->current_responder = NULL;
		while (ld.packetcount < runtime->nqueries)
		{
			if (send_udppacket(runtime, &sockets, &pktimer) != 0)
				break ;
			ld.reached_target += receive_routine(runtime, &sockets, &pktimer);
			increase_portnb(runtime);
			++ld.packetcount;
		}
		dprintf(2, "\n");
		ft_strdel(&runtime->current_responder);
	}
	free_tracert_data(runtime);
	return (0);
}
