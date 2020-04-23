/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int8_t		set_socket_options(t_socketlst *sl)
{
	int on;

	on = 1;
	if (setsockopt(sl->socket_send, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0)
		return (-1);
	return (0);
}

int32_t				create_sockets(t_socketlst *sl)
{
	sl->socket_send = socket(PF_INET, SOCK_DGRAM, 0);
	sl->socket_recv = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sl->socket_send < 0 || sl->socket_recv < 0)
	{
		traceroute_fatal("create_socket()","Error creating sockets");
		return (-1);
	}
	if (set_socket_options(sl) != 0)
	{
		traceroute_fatal("set_socket_options()", "Error configuring sockets");
		return (-1);
	}
	return (0);
}
