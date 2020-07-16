/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

uint8_t			send_udppacket(t_tracert_data *runtime, t_socketlst *socks,
					t_timer *tm)
{
	int16_t		sent_bytes;
	char		data_buffer[1500];

	ft_memset(&data_buffer, 0x42, 1500);
	sent_bytes = sendto(socks->socket_send,
					data_buffer, runtime->datasize, 0,
					(struct sockaddr*)&runtime->target_addr,
					sizeof(struct sockaddr));
	if (sent_bytes < 0)
	{
		traceroute_fatal("send_udp_packet()",
			"No  data has been sent or an error happened\n");
		return (1);
	}
	gettimeofday(&tm->send, NULL);
	return (0);
}
