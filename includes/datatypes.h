/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
# define DATATYPES_H

# include <bits/endian.h>
# include <unistd.h>
# include <netdb.h>

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
	struct in_addr			ip_src;     /* typedef uint32_t in_addr_t; */
	struct in_addr			ip_dst;     /* typedef uint32_t in_addr_t; */
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
struct						s_tcp_hdr
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

struct			s_pseudo_hdr
{
	u_int32_t	source_address;
	u_int32_t	dest_address;
	u_int8_t	placeholder;
	u_int8_t	protocol;
	u_int16_t	udp_length;
};

typedef struct				s_upacket
{
	struct s_ipv4_hdr		ip;
	struct s_udp_hdr		udp;
	char					payload[42];
} __attribute__ ((packed))	t_upacket;

typedef struct				s_ipacket
{
	struct s_ipv4_hdr		ip;
	struct s_icmp_hdr		icmp;
	char					*payload;
} __attribute__ ((packed))	t_ipacket;

typedef struct				s_tpacket
{
	struct s_ipv4_hdr		ip;
	struct s_tcp_hdr		tcp;
	char					*payload;
} __attribute__ ((packed))	t_tpacket;

#endif
