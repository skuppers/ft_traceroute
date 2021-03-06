/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	print_usage(uint8_t ext)
{
	dprintf(2, "\nUsage:\t./ft_traceroute [options] host [packet_len]\n");
	if (ext != 0)
		exit(ext);
}

#ifdef BONUS_H

void	print_help(uint8_t ext)
{
	dprintf(2, "Options: \n");
	dprintf(2, "  -h\t\tShows this page.\n");
	dprintf(2, "  -n\t\tDo not resolve dns.\n");
	dprintf(2, "  -f <number>\tSpecify TTL to start with.\n");
	dprintf(2, "  -q <number>\tSet the number of probes.\n");
	dprintf(2, "  -m <number>\tSpecify max amount of hops.\n");
	print_usage(ext);
}

#else

void	print_help(uint8_t ext)
{
	dprintf(2, "Options: \n");
	dprintf(2, "  -h\t\tShows this page.\n");
	print_usage(ext);
}

#endif

void	traceroute_fatal(const char *failed_here, const char *errbuff)
{
	dprintf(STDERR_FILENO, "Fatal error in %s: %s\n", failed_here, errbuff);
}
