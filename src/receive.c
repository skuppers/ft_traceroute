/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static uint8_t	is_localhost(t_tracert_data *runtime, char *recv)
{
	if (ft_strequ(runtime->target_ipv4, "0.0.0.0")
		&& ft_strequ(recv, "127.0.0.1"))
		return (42);
	return (0);
}

uint8_t			receive_packet(t_tracert_data *runtime, t_socketlst *socks,
					t_timer *tm)
{
	char				recv_buffer[1500];
	socklen_t			sock_len;
	struct sockaddr_in	recv_addr;

	ft_memset(&recv_addr, 0, sizeof(struct sockaddr_in));
	ft_bzero(&recv_buffer, 1500);
	sock_len = sizeof(struct sockaddr);
	if (recvfrom(socks->socket_recv, recv_buffer,
						sizeof(recv_buffer), MSG_DONTWAIT,
						(struct sockaddr*)&recv_addr, &sock_len) <= 0)
		traceroute_fatal("recvrom()", "No  data has been read"
						" or an error happened\n");
	else
	{
		gettimeofday(&tm->recv, NULL);
		print_stats(runtime, &recv_addr, tm);
		if (ft_strequ(inet_ntoa(recv_addr.sin_addr), runtime->target_ipv4)
			|| is_localhost(runtime, inet_ntoa(recv_addr.sin_addr)))
			return (42);
	}
	return (0);
}

uint8_t			receive_routine(t_tracert_data *runtime, t_socketlst *socks,
					t_timer *tm)
{
	fd_set			recv_set;
	struct timeval	tv;

	FD_ZERO(&recv_set);
	FD_SET(socks->socket_recv, &recv_set);
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (select(FD_SETSIZE, &recv_set, NULL, NULL, &tv) < 0)
	{
		traceroute_fatal("select", "select failed.");
		exit(EXIT_FAILURE);
	}
	if (FD_ISSET(socks->socket_recv, &recv_set))
		return (receive_packet(runtime, socks, tm));
	else
		dprintf(2, " * ");
	return (0);
}
