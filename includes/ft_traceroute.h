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
# include "libft.h"

# define IP4_HDRLEN		20
# define UDP_HDRLEN		8

# define OPT_CHARSET "N:m:f:hI"
# define OPT_ICMP_ONLY	0x01

# define DEFAULT_STARTPORT	33434
# define DEFAULT_TOTALSIZE	60
# define MINIMAL_TOTALSIZE	28
# define DEFAULT_DATASIZE	32

typedef struct			s_socketlst
{
	int32_t				socket_send;
	int32_t				socket_recv;
}						t_socketlst;

typedef struct				s_timer
{
	struct timeval			send;
	struct timeval			recv;
}							t_timer;

typedef struct			s_tracert_data
{
	uint8_t				options;
	uint32_t			totalsize;
	uint32_t			datasize;
	uint16_t			ttl;
	uint16_t			max_ttl;
	uint8_t				nqueries;

	char				*target_str;
	char				*target_ipv4;

	struct addrinfo		*result;
	struct sockaddr_in	target_addr;

	char				*current_responder;
	uint16_t			send_port;
	
}						t_tracert_data;

typedef struct			s_loopdata
{
	int					packetcount;
	int					reached_target;
	int					request_nb;
}						t_loopdata;

void					print_usage(uint8_t ext);
void					print_help(uint8_t ext);
void					traceroute_fatal(const char *failed_here, const char *errbuff);
void					parse_options(t_tracert_data *rt, int ac, char **av);

int8_t					resolve_target(t_tracert_data *runtime);
uint8_t					select_dflt_interface(t_tracert_data *runtime);

int32_t					create_sockets(t_socketlst *socketlist);
int32_t					ft_traceroute(t_tracert_data *runtime);

void					increase_portnb(t_tracert_data *runtime);
void					increase_ttl(t_tracert_data *runtime, t_socketlst *socks);
float					plot_timer(t_timer *timer);
void					reverse_target(struct sockaddr_in *raddr, char *buffer);
void					print_stats(t_tracert_data *runtime, struct sockaddr_in *raddr, t_timer *tm);
#endif
