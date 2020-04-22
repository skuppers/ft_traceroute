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

static void				extract_ipaddr(const struct sockaddr *sa, char *ip,
						uint32_t maxlen)
{
	if (sa->sa_family == AF_INET)
		inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr), ip,
			maxlen);
	else if (sa->sa_family == AF_INET6)
		inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr), ip,
			maxlen);
	else
	{
		traceroute_fatal("extract_ipaddr()", "Unknown AF");
		exit(42);
	}
}

static uint8_t		retrieve_interfaces(struct ifaddrs **interfaces)
{
	if (getifaddrs(interfaces) == -1)
	{
		traceroute_fatal("getifaddrs", "could not retreive interfaces");
		return (1);
	}
	return (0);
}

uint8_t				select_dflt_interface(t_tracert_data *runtime)
{
	struct ifaddrs	*itf_ptr;
	struct ifaddrs	*interfaces;

	if (retrieve_interfaces(&interfaces))
		return (-1);

	itf_ptr = interfaces;
	while (itf_ptr != NULL)
	{
		if (itf_ptr->ifa_addr == NULL || ft_strequ(itf_ptr->ifa_name, "lo"))
		{
			itf_ptr = itf_ptr->ifa_next;
			continue;
		}
		if (itf_ptr->ifa_addr->sa_family == AF_INET)
		{
			runtime->interface_name = ft_strdup(itf_ptr->ifa_name);
			runtime->interface_ipv4 = ft_strnew(INET_ADDRSTRLEN);
			extract_ipaddr(itf_ptr->ifa_addr, runtime->interface_ipv4, INET_ADDRSTRLEN);
			freeifaddrs(interfaces);
			return (0);
		}
		itf_ptr = itf_ptr->ifa_next;
	}
	freeifaddrs(interfaces);
	printf("ft_traceroute: Network is unreachable.\n");
	return (-1);
}
