/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interfaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static uint8_t		retrieve_interfaces(struct ifaddrs **interfaces)
{
	if (getifaddrs(interfaces) == -1)
	{
		traceroute_fatal("getifaddrs", "could not retreive interfaces");
		return (1);
	}
	return (0);
}

// TODO: Handle
uint8_t				select_dflt_interface(t_tracert_data *runtime)
{
	(void)runtime;
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
			freeifaddrs(interfaces);
			return (0);
		}
		itf_ptr = itf_ptr->ifa_next;
	}
	freeifaddrs(interfaces);
	printf("ft_traceroute: Network is unreachable.\n");
	return (-1);
}
