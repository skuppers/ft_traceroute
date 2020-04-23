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
# include <errno.h>

void			increase_portnb(t_tracert_data *runtime)
{
	runtime->send_port++;
	runtime->target_addr.sin_port = htons(runtime->send_port);
}

uint8_t			send_udppacket(t_tracert_data *runtime, t_socketlst *socks, t_timer *tm)
{
	int16_t		sent_bytes;
	char		data_buffer[1500];

	ft_memset(&data_buffer, 0x42, 1500);
	sent_bytes = sendto(socks->socket_send,
					data_buffer, runtime->datasize, 0,
					(struct sockaddr*)&runtime->target_addr,
					sizeof(struct sockaddr));
	if (sent_bytes <= 0)
	{
		printf(" -S_Err!- ");
		perror(strerror(errno));
		return (1);
	}
	gettimeofday(&tm->send, NULL);
	return (0);
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

void	print_stats(t_tracert_data *runtime, struct sockaddr_in *raddr, t_timer *tm)
{
	if (runtime->current_responder == NULL)
	{
		runtime->current_responder = inet_ntoa(raddr->sin_addr);
		printf(" %s (%s) ", reverse_target(runtime->current_responder), runtime->current_responder);
	}
	else if (!ft_strequ(runtime->current_responder, inet_ntoa(raddr->sin_addr)))
	{
		runtime->current_responder = inet_ntoa(raddr->sin_addr);
		printf(" %s (%s) ", reverse_target(runtime->current_responder), runtime->current_responder);
	}
	printf(" %.3f ms ", plot_timer(tm));
}

uint8_t			receive_packet(t_tracert_data *runtime, t_socketlst *socks, t_timer *tm)
{
	char				recv_buffer[1500];
	int32_t				read_bytes;
	socklen_t			sock_len;
	struct sockaddr_in	recv_addr;
	
	ft_bzero(&recv_buffer, 1500);
	sock_len = sizeof(struct sockaddr);
	if ((read_bytes = recvfrom(socks->socket_recv, recv_buffer, sizeof(recv_buffer),
						MSG_DONTWAIT, (struct sockaddr*)&recv_addr,
						&sock_len)) <= 0)
		traceroute_fatal("recvrom()", "No  data has been read or an error happened\n");
	else
	{
		gettimeofday(&tm->recv, NULL);
		print_stats(runtime, &recv_addr, tm);
//		printf("Received %d bytes datagram from %s\n", read_bytes, inet_ntoa(recv_addr.sin_addr));
	
		if (ft_strequ(inet_ntoa(recv_addr.sin_addr), runtime->target_ipv4))
			return (42);
	}
	return (0);
}

uint8_t			receive_routine(t_tracert_data *runtime, t_socketlst *socks, t_timer *tm)
{
	int				reached_target;
	fd_set			recv_set;
	struct timeval	tv;
	

	FD_ZERO (&recv_set);
	FD_SET (socks->socket_recv, &recv_set);
	tv.tv_sec = 2;
	tv.tv_usec = 0;

	if (select(FD_SETSIZE, &recv_set, NULL, NULL, &tv) < 0)
	{
		traceroute_fatal("select", "select failed bruh"); //TODO: do decent error handling
		exit (EXIT_FAILURE);
 	}
	if (FD_ISSET(socks->socket_recv, &recv_set))
		return (receive_packet(runtime, socks, tm));
	else
	{
		// Timeout
		printf(" * ");
	}
	return (0);
}

void			increase_ttl(t_tracert_data *runtime, t_socketlst *socks)
{
	runtime->ttl++;
	if (setsockopt(socks->socket_send, IPPROTO_IP, IP_TTL, &runtime->ttl,
		sizeof(uint8_t)) < 0)
	{
		traceroute_fatal("setsockopt", "unkniown");
	}
}

int32_t			ft_traceroute(t_tracert_data *runtime)
{
	t_socketlst			sockets;
	int					packetcount = 0;
	t_timer				pktimer;
	int					reached_target;
	int					request_nb = 0;

	// Set up sockets
	if (create_sockets(runtime, &sockets) != 0)
		return (-1);

//	printf("Selected interface: %s | addr: %s\n", runtime->interface_name, runtime->interface_ipv4);

	reached_target = 0;
	while (reached_target == 0) // No signals, target not reached & max ttl not reached
	{
		increase_ttl(runtime, &sockets);
		printf(" %d ", request_nb);
		packetcount = 0;
		runtime->current_responder = NULL;
		while (packetcount < 3)
		{
			send_udppacket(runtime, &sockets, &pktimer);
			reached_target = receive_routine(runtime, &sockets, &pktimer);
			increase_portnb(runtime);
			++packetcount;
		}
		printf("\n");
		++request_nb;
	}

//	ft_lstdel(&packetlist, NULL);
//	freeaddrinfo(runtime->dst_sockaddr);
//	ft_strdel(&runtime->interface_name);
//	ft_strdel(&runtime->interface_ipv4);
	ft_strdel(&runtime->target_str);
	ft_strdel(&runtime->target_ipv4);
	return (0);
}