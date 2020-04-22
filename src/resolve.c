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

static void				prepare_hints(struct addrinfo *hints)
{
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = 0;
	hints->ai_flags = AI_V4MAPPED | AI_ADDRCONFIG;
}

static uint8_t			getsocketresult(t_tracert_data *runtime, struct addrinfo **results)
{
	struct addrinfo		hints;

	prepare_hints(&hints);
	if ((getaddrinfo(runtime->target_str, NULL, &hints, results)) != 0)
	{
		printf("ft_traceroute: %s: Temporary failure in name resolution\n", runtime->target_str);
		ft_strdel(&runtime->target_str);
		return (1);
	}
	return (0);
}

int8_t		resolve_target(t_tracert_data *runtime)
{
	struct addrinfo		*result;
	struct in_addr		*iadr;
	char				buffer[INET_ADDRSTRLEN];

	result = NULL;
	if (getsocketresult(runtime, &result))
		return (-1);
	
	runtime->sin = ((struct sockaddr_in *)result->ai_addr);
	iadr = &(((struct sockaddr_in*)result->ai_addr)->sin_addr);
	ft_bzero(buffer, INET_ADDRSTRLEN);
	if (inet_ntop(AF_INET, iadr, buffer, INET_ADDRSTRLEN) == NULL)
	{
		traceroute_fatal("inet_ntop", "undefined");
		ft_strdel(&runtime->target_str);
		return (-1);
	}
	freeaddrinfo(result);
	runtime->target_ipv4 = ft_strdup(buffer);

	printf("%s resolved to %s\n", runtime->target_str, runtime->target_ipv4);

	return (0);
}   