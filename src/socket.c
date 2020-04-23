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

static int8_t		set_socket_options(t_tracert_data *runtime, t_socketlst *sl)
{
	(void)runtime;
	int on;

	on = 1;
	if (setsockopt(sl->socket_send, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) < 0)
		return (-1);
	return (0);
}

int32_t				create_sockets(t_tracert_data *runtime, t_socketlst *sl)
{
	// sudo or root
	sl->socket_send = socket(PF_INET, SOCK_DGRAM, 0);
	sl->socket_recv = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);

	if (sl->socket_send < 0 || sl->socket_recv < 0)
	{
		traceroute_fatal("create_socket()","Error creating sockets");
		return (-1);
	}

	//select_dflt_interface(runtime);
	

	if (set_socket_options(runtime, sl) != 0)
	{
		traceroute_fatal("set_socket_options()", "Error configuring sockets");
		return (-1);
	}

	//bind_sockets(runtime, sl);

	return (0);
}

int32_t				bind_sockets(t_tracert_data *runtime, t_socketlst *sockets)
{
	(void)runtime;
	struct sockaddr_in myaddr;
	
	myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(0);
    memset(&(myaddr.sin_zero), '\0', 8);

    if (bind(sockets->socket_send, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
        perror("bind");
        exit(1);
    }
//	ft_memcpy(&runtime->trace_addr, &myaddr, sizeof(struct sockaddr));
	return (0);
}