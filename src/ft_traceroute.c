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

uint8_t			send_udppacket(t_tracert_data *runtime, t_socketlst *socks, t_timer *tm)
{
	int16_t		sent_bytes;
	char		data_buffer[1468];

	ft_memset(&data_buffer, 0x42, 1468);
	sent_bytes = sendto(socks->socket_send,
					data_buffer, runtime->datasize, 0,
					(struct sockaddr*)&runtime->target_addr,
					sizeof(struct sockaddr));
	if (sent_bytes < 0)
	{
		printf(" -S_Err!- ");
		return (1);
	}
	gettimeofday(&tm->send, NULL);
	return (0);
}

uint8_t			receive_packet(t_tracert_data *runtime, t_socketlst *socks, t_timer *tm)
{
	char				recv_buffer[1500];
	int32_t				read_bytes;
	socklen_t			sock_len;
	struct sockaddr_in	recv_addr;
	
	ft_memset(&recv_addr, 0, sizeof(struct sockaddr_in));
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
		if (ft_strequ(inet_ntoa(recv_addr.sin_addr), runtime->target_ipv4))
			return (42);
	}
	return (0);
}

uint8_t			receive_routine(t_tracert_data *runtime, t_socketlst *socks, t_timer *tm)
{
	fd_set			recv_set;
	struct timeval	tv;
	
	FD_ZERO (&recv_set);
	FD_SET (socks->socket_recv, &recv_set);
	tv.tv_sec = 1;
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

int32_t			ft_traceroute(t_tracert_data *runtime)
{
	int					packetcount;
	int					reached_target;
	int					request_nb;
	t_timer				pktimer;
	t_socketlst			sockets;

	// Set up sockets
	if (create_sockets(&sockets) != 0)
		return (-1);

	printf("ft_traceroute to %s (%s), 30 hops max, %d byte packets\n",
				runtime->target_str, runtime->target_ipv4, runtime->totalsize);

//	printf("Selected interface: %s | addr: %s\n", runtime->interface_name, runtime->interface_ipv4);

	request_nb = 1;
	reached_target = 0;
	while (reached_target == 0 || request_nb >= 30) // TODO: No signals, target not reached & max ttl not reached
	{
		increase_ttl(runtime, &sockets);
		printf(" %d ", runtime->ttl);
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
		ft_strdel(&runtime->current_responder);
		++request_nb;
		++runtime->ttl;
	}
	ft_strdel(&runtime->target_str);
	ft_strdel(&runtime->target_ipv4);
	freeaddrinfo(runtime->result);
	return (0);
}