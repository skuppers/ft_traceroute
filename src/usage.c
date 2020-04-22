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

# include "ft_traceroute.h"

void    print_usage(uint8_t ext)
{
	printf(" --- Usage Text --- \n");
	if (ext != 0)
		exit(ext);
}

void    print_help(uint8_t ext)
{
	printf(" --- Help text ---\n");
	print_usage(ext);
}

void	traceroute_fatal(const char *failed_here, const char *errbuff)
{
	printf("Fatal error in %s: %s\n", failed_here, errbuff);
}
