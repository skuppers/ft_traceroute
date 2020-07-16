/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void			increase_portnb(t_tracert_data *runtime)
{
	runtime->send_port++;
	runtime->target_addr.sin_port = htons(runtime->send_port);
}

void			increase_ttl(t_tracert_data *runtime, t_socketlst *socks)
{
	if (setsockopt(socks->socket_send, IPPROTO_IP, IP_TTL, &runtime->ttl,
			sizeof(uint8_t)) < 0)
		traceroute_fatal("increase_ttl", "unknown");
	++runtime->ttl;
}

float			plot_timer(t_timer *timer)
{
	double		send;
	double		recv;

	send = ((double)timer->send.tv_sec)
		+ ((double)(0.000001f * (double)timer->send.tv_usec));
	recv = ((double)timer->recv.tv_sec)
		+ ((double)(0.000001f * (double)timer->recv.tv_usec));
	return ((float)(recv - send) * 1000.0f);
}

#ifdef BONUS_H

void			reverse_target(struct sockaddr_in *raddr, char *buffer)
{
	if (getnameinfo((struct sockaddr *)raddr, sizeof(struct sockaddr),
			buffer, 256, NULL, 0, 0))
		ft_bzero(buffer, 256);
}

#endif
