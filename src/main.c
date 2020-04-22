/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int								main(int ac, char **av)
{
    t_tracert_data		runtime;

    if (ac < 2)
        print_usage(42);
	
	ft_bzero(&runtime, sizeof(t_tracert_data));
	parse_options(&runtime, ac, av);

	printf("Target %s datasize %d first TTL %d\n", runtime.target_str, runtime.datasize, runtime.first_ttl);

	if (runtime.target_str == NULL)
		print_usage(42);

	if (resolve_target(&runtime) < 0)
		return (-1);
	else
		return (ft_traceroute(&runtime));

	return (0);
}