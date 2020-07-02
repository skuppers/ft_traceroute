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
	printf("\nUsage:\n\t./ft_traceroute [options] host [packet_len]\n");
	if (ext != 0)
		exit(ext);
}

void	print_help(uint8_t ext)
{
	printf("Options: \n");
	printf("  -h\t\tShows this page.\n");
	printf("  -n\t\tDo not resolve dns.\n");
	printf("  -f <number>\tSpecify TTL to start with.\n");
	printf("  -q <number>\tSet the number of probes.\n");
	printf("  -m <number>\tSpecify max amount of hops.\n");
	print_usage(ext);
}

void	traceroute_fatal(const char *failed_here, const char *errbuff)
{
	dprintf(STDERR_FILENO, "Fatal error in %s: %s\n", failed_here, errbuff);
}
