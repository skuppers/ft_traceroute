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

static void			prepare_hints(struct addrinfo *hints)
{
	ft_memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = 0;
	hints->ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
}

static uint8_t		getsocketresult(t_tracert_data *runtime,
							struct addrinfo **results)
{
	struct addrinfo	hints;

	prepare_hints(&hints);
	if ((getaddrinfo(runtime->target_str, NULL, &hints, results)) != 0)
	{
		dprintf(2, "ft_traceroute: %s: Temporary failure in name resolution\n",
				runtime->target_str);
		ft_strdel(&runtime->target_str);
		return (1);
	}
	return (0);
}

void				store_target_strings(t_tracert_data *runtime)
{
	char			*buffer;

	buffer = inet_ntoa(runtime->target_addr.sin_addr);
	runtime->target_ipv4 = ft_strdup(buffer);
}

int8_t				resolve_target(t_tracert_data *runtime)
{
	struct addrinfo	*result;

	result = NULL;
	if (getsocketresult(runtime, &result))
		return (-1);
	runtime->result = result;
	runtime->target_addr = *((struct sockaddr_in*)result->ai_addr);
	runtime->target_addr.sin_family = AF_INET;
	runtime->target_addr.sin_port = htons(runtime->send_port);
	ft_memset(&(runtime->target_addr.sin_zero), '\0', 8);
	store_target_strings(runtime);
	return (0);
}
