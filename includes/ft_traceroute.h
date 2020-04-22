/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACROUTE_H
# define FT_TRACROUTE_H

# include <signal.h>
# include <stdlib.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/cdefs.h>
# include <unistd.h>
# include <getopt.h>
# include <stdio.h>
# include <time.h>
# include <netdb.h>
# include <sys/uio.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <sys/time.h>
# include <ifaddrs.h>
# include <sys/ioctl.h>
# include <net/if.h>
# include "datatypes.h"
# include "libft.h"

# define OPT_CHARSET "f:hIT"
# define OPT_ICMP_ONLY	0x01
# define OPT_TCP_ONLY	0x02

# define DEFAULT_DATASIZE 42

typedef struct			s_tracert_data
{
	uint8_t				options;
	char				*target_str;
	char				*target_ipv4;
	uint32_t			datasize;
	uint16_t			first_ttl;

	struct sockaddr_in		*sin;
	
}						t_tracert_data;

void					print_usage(uint8_t ext);
void					print_help(uint8_t ext);
void					traceroute_fatal(const char *failed_here, const char *errbuff);
void					parse_options(t_tracert_data *rt, int ac, char **av);
int8_t					resolve_target(t_tracert_data *runtime);

int32_t					ft_traceroute(t_tracert_data *runtime);

#endif
