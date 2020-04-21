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
# include <bits/endian.h>
# include "libft.h"

/* Based on RFC 791 */
struct						s_ipv4_hdr
{
# if __BYTE_ORDER == __LITTLE_ENDIAN

	unsigned char			ip_header_length:4;
	unsigned char			ip_version:4;
# elif __BYTE_ORDER == __BIG_ENDIAN

	unsigned char			ip_version:4;
	unsigned char			ip_header_length:4;
# else
#  error "Please fix <bits/endian.h>"
# endif

	unsigned char			ip_tos;
	unsigned short			ip_len;
	unsigned short			ip_id;
	unsigned short			ip_frag_offset;
	unsigned char			ip_ttl;
	unsigned char			ip_type;
	unsigned short			ip_checksum;
	struct in_addr			ip_src;
	struct in_addr			ip_dst;
};

struct						s_icmp_hdr
{
	uint8_t					icmp_type;
	uint8_t					icmp_code;
	uint16_t				icmp_checksum;
	uint16_t				icmp_identifier;
	uint16_t				icmp_sequence;
};

/* Based on RFC 793 */
struct						s_tcpheader
{
	uint16_t				tcphsrcport;
	uint16_t				tcp_destport;
	uint32_t				tcp_seqnum;
	uint32_t				tcp_acknum;
	uint16_t				tcp_offset:4;
	uint16_t				tcp_reserved:6;
	uint16_t				tcp_urg:1;
	uint16_t				tcp_ack:1;
	uint16_t				tcp_psh:1;
	uint16_t				tcp_rst:1;
	uint16_t				tcp_syn:1;
	uint16_t				tcp_fin:1;
	uint16_t				tcp_window;
	uint16_t				tcp_checksum;
	uint16_t				tcp_urgptr;
};

struct						s_udp_hdr
{
    uint16_t				uh_sport;
    uint16_t				uh_dport;
    uint16_t				uh_ulen;
    uint16_t				uh_sum;
};

#endif
