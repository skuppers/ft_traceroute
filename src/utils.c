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

//TODO: Do error handling w/ return values
void			increase_ttl(t_tracert_data *runtime, t_socketlst *socks)
{
	runtime->ttl++;
	if (setsockopt(socks->socket_send, IPPROTO_IP, IP_TTL, &runtime->ttl,
		sizeof(uint8_t)) < 0)
	{
		traceroute_fatal("setsockopt", "unknown");
    }
}

float		plot_timer(t_timer *timer)
{
	double	send;
	double	recv;

	send = 0;
	recv = 0;
	send = ((double)timer->send.tv_sec)
		+ ((double)(0.000001f * (double)timer->send.tv_usec));
	recv = ((double)timer->recv.tv_sec)
		+ ((double)(0.000001f * (double)timer->recv.tv_usec));
	return ((float)(recv - send) * 1000.0f);
}

//TODO: change char *src_addr to struct sockaddr_in for simplicity's sake
char					*reverse_target(char *src_addr)
{
	struct sockaddr_in	sa;
	char				hostname[256];

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	inet_pton(AF_INET, src_addr, &sa.sin_addr);
	
	if (getnameinfo((struct sockaddr*)&sa, sizeof(sa),
			hostname, sizeof(hostname),
			NULL, 0, NI_NAMEREQD))
		return (NULL);
	return (ft_strdup(hostname));
}