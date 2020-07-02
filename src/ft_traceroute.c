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

uint			traceroute_condition(t_tracert_data *runtime, t_loopdata *ld)
{
	if (ld->reached_target != 0)
		return (0);
	if (ld->request_nb > runtime->max_ttl)
		return (0);
	return (1);
}

void			print_request_nb(t_tracert_data *runtime)
{
	if (runtime->ttl < 10)
		printf(" %d ", runtime->ttl);
	else
		printf("%d ", runtime->ttl);
}

int32_t			ft_traceroute(t_tracert_data *runtime)
{
	t_loopdata			ld;
	t_timer				pktimer;
	t_socketlst			sockets;

	if (create_sockets(&sockets) != 0)
		return (-1);
	print_traceroute(runtime);
	ld.request_nb = 1;
	ld.reached_target = 0;
	while (traceroute_condition(runtime, &ld) == 1)
	{
		increase_ttl(runtime, &sockets);
		print_request_nb(runtime);
		ld.packetcount = 0;
		runtime->current_responder = NULL;
		while (ld.packetcount < runtime->nqueries)
		{
			if (send_udppacket(runtime, &sockets, &pktimer) != 0)
				break ;
			ld.reached_target = receive_routine(runtime, &sockets, &pktimer);
			increase_portnb(runtime);
			++ld.packetcount;
		}
		printf("\n");
		ft_strdel(&runtime->current_responder);
		++ld.request_nb;
		++runtime->ttl;
	}
	ft_strdel(&runtime->target_str);
	ft_strdel(&runtime->target_ipv4);
	freeaddrinfo(runtime->result);
	return (0);
}
