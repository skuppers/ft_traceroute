/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_traceroute.h"

static void			invalid_opt(char *optarg, char *option)
{
	if (optarg == NULL)
		printf("ft_traceroute: option requires an argument -- '%s'\n", option);
	else
		printf("ft_traceroute: invalid argument: %s\n", optarg);
	exit(-1);
}

static void		handle_standalone_options(t_tracert_data *rt, char opt)
{
	if (opt == 'h')
		print_help(1);
	else if (opt == 'I')
		rt->options |= OPT_ICMP_ONLY;
	else if (opt == 'T')
		rt->options |= OPT_TCP_ONLY;
}

static void		handle_custom_options(t_tracert_data *rt, char opt, char *oarg)
{
	if (opt == 'f')
		(ft_atoi(oarg) >= 0) ? rt->ttl = (uint32_t)ft_atoi(oarg) : invalid_opt(oarg, "f");
	else if (opt == 'N')
		(ft_atoi(oarg) >= 0) ? rt->nqueries = (uint32_t)ft_atoi(oarg) : invalid_opt(oarg, "N");
	else if (opt == 'm')
		(ft_atoi(oarg) >= 0) ? rt->max_ttl = (uint32_t)ft_atoi(oarg) : invalid_opt(oarg, "m");
}

void		set_defaults(t_tracert_data *rt)
{
	rt->send_port = DEFAULT_STARTPORT;
	rt->ttl = 1;
	rt->nqueries = 3;
	rt->max_ttl = 30;
}	

void		get_dest_and_pktsz(t_tracert_data *rt, char **av)
{
	if (g_optind != -1)
		rt->target_str = ft_strdup(av[g_optind]);
	if (av[g_optind + 1] != NULL)
		rt->totalsize = ft_atoi(av[g_optind + 1]);
	else
		rt->totalsize = DEFAULT_TOTALSIZE;
	if (rt->totalsize < MINIMAL_TOTALSIZE)
		rt->totalsize = MINIMAL_TOTALSIZE;
	rt->datasize = (rt->totalsize - MINIMAL_TOTALSIZE);
}

void		parse_options(t_tracert_data *rt, int ac, char **av)
{
	int32_t	option;

	set_defaults(rt);
	av = ft_getopt_order_arguments(ac, av, OPT_CHARSET);
	while ((option = ft_getopt(ac, av, OPT_CHARSET)) != -1)
	{
		if (option == 'h' || option == 'U' || option == 'T')
			handle_standalone_options(rt, option);
		else if (option == 'f' || option == 'N' || option == 'm')
			handle_custom_options(rt, option, g_optarg);
		else
			print_usage(42);
	}
	get_dest_and_pktsz(rt, av);
	ft_freetab(&av);
}
