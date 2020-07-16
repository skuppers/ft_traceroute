/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void		set_defaults(t_tracert_data *rt)
{
	rt->send_port = DEFAULT_STARTPORT;
	rt->ttl = 1;
	rt->nqueries = 3;
	rt->max_ttl = 30;
	rt->totalsize = 0;
	rt->target_str = NULL;
}

void		traceroute_exit(int exitcode, const char *message, ...)
{
	va_list			args;

	dprintf(STDERR_FILENO, "ft_traceroute: ");
	va_start(args, message);
	vdprintf(STDERR_FILENO, message, args);
	va_end(args);
	exit(exitcode);
}

void		get_msgsize(t_tracert_data *rt, char *av)
{
	if (ft_strlen(av) > 5 || ft_isnumeric(av) == 0)
		traceroute_exit(42, "invalid size -- '%s'\n", av);
	else if (ft_atoi(av) < 0 || ft_atoi(av) > 1500)
		traceroute_exit(42, "invalid size -- '%s'\n", av);
	else
	{
		rt->totalsize = ft_atoi(av);
		if (rt->totalsize < MINIMAL_TOTALSIZE)
			rt->totalsize = MINIMAL_TOTALSIZE;
	}
}
