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

#include "ft_traceroute.h"

#ifdef BONUS_H

static uint8_t	check_valid(char *arg, size_t len, int min, int max)
{
	if (ft_isnumeric(arg) == 0)
		traceroute_exit(42, "invalid argument: '%s'", arg);
	if (ft_strlen(arg) > len || ft_atoi(arg) < min || ft_atoi(arg) > max)
		traceroute_exit(42, "argument '%s' not in range: %d - %d\n", arg,
		min, max);
	return (1);
}

static int		get_arg_opt(char *arg, const char *opt_str[],
								const int count, t_tracert_data *param)
{
	if (arg == NULL)
		traceroute_exit(42, "option requires an argument -- '%s'\n",
			opt_str[count]);
	if (ft_strequ(opt_str[count], "-f") == 1 && check_valid(arg, 3, 1, 255))
		param->ttl = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-q") == 1 && check_valid(arg, 3, 1, 255))
		param->nqueries = ft_atoi(arg);
	if (ft_strequ(opt_str[count], "-m") == 1 && check_valid(arg, 3, 1, 255))
		param->max_ttl = ft_atoi(arg);
	return (2);
}

static int		get_one_opt(char **av, int i, t_tracert_data *runtime)
{
	int			count;
	const char	*opt_str[] = {"-h", "-n", "-f", "-q", "-m" };

	count = 0;
	while (count < 5)
	{
		if (ft_strequ(av[i], opt_str[count]) == 1)
		{
			if (count < 2)
			{
				runtime->options |= (1 << count);
				if (runtime->options & OPT_HELP)
					print_help(42);
				return (1);
			}
			else
				return (get_arg_opt(av[i + 1], opt_str, count, runtime));
		}
		count++;
	}
	traceroute_exit(42, "invalid option -- '%s'\n", av[i]);
	return (0);
}

#else

static int		get_one_opt(char **av, int i, t_tracert_data *runtime)
{
	int			count;
	const char	*opt_str[] = {"-h"};

	count = 0;
	while (count < 1)
	{
		if (ft_strequ(av[i], opt_str[count]) == 1)
		{
			runtime->options |= (1 << count);
			if (runtime->options & OPT_HELP)
				print_help(42);
			return (1);
		}
		count++;
	}
	traceroute_exit(42, "invalid option -- '%s'\n", av[i]);
	return (0);
}

#endif

void			parse_options(t_tracert_data *rt, char **av)
{
	int			i;

	++av;
	i = 0;
	set_defaults(rt);
	while (av[i] != NULL)
	{
		if (av[i][0] == '-')
			i += get_one_opt(av, i, rt);
		else
		{
			if (rt->target_str == NULL)
				rt->target_str = ft_strdup(av[i]);
			else if (rt->totalsize == 0)
				get_msgsize(rt, av[i]);
			else
				traceroute_exit(42, "invalid option -- '%s'\n", av[i]);
			++i;
		}
	}
	if (rt->totalsize == 0)
		rt->totalsize = DEFAULT_TOTALSIZE;
	rt->datasize = (rt->totalsize - MINIMAL_TOTALSIZE);
}
