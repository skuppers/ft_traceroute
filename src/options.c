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
		(ft_atoi(oarg) > 0) ? rt->first_ttl = (uint32_t)ft_atoi(oarg) : invalid_opt(oarg, "f");
}

void		parse_options(t_tracert_data *rt, int ac, char **av)
{
	int32_t	option;

	
	av = ft_getopt_order_arguments(ac, av, OPT_CHARSET);
	while ((option = ft_getopt(ac, av, OPT_CHARSET)) != -1)
	{
		if (option == 'h' || option == 'U' || option == 'T')
			handle_standalone_options(rt, option);
		else if (option == 'f')
			handle_custom_options(rt, option, g_optarg);
		else
			print_usage(42);
	}
	if (g_optind != -1)
		rt->target_str = ft_strdup(av[g_optind]);
	if (av[g_optind + 1] != NULL)
		rt->datasize = ft_atoi(av[g_optind + 1]);

	for (int i = 0; av[i] != NULL; i++)
		ft_strdel(&av[i]);
	free(av);
	
}
