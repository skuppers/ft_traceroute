/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:13:23 by skuppers          #+#    #+#             */
/*   Updated: 2020/02/15 17:47:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"
/*
char        *forge_payload(t_tracert_data *rt)
{
    char		*msg;
	uint32_t	i;

    if (rt->datasize == 0)
		rt->datasize = 26;
    msg = ft_strnew(rt->datasize);
	i = 0;
	while (i < rt->datasize)
		msg[i++] = 0x42;
	msg[i] = '\0';
    return (msg);
}

void	forge_udp_header(t_tracert_data *runtime, struct s_udp_hdr *hdr)
{
	ft_bzero(hdr, sizeof(struct s_udp_hdr));
	hdr->uh_sport = htons(42420);
	hdr->uh_dport = htons(runtime->send_port);
	hdr->uh_ulen = htons(sizeof(struct s_udp_hdr) + runtime->datasize);
}

    udppacket->ip.ip_version = 4;
    udppacket->ip.ip_header_length = sizeof(udppacket->ip) >> 2;
    udppacket->ip.ip_dst = ((struct sockaddr_in*)runtime->sockad->ai_addr)->sin_addr;
    udppacket->ip.ip_type = IPPROTO_UDP;
	udppacket->ip.ip_ttl = 5;
	hdrsz = sizeof(udppacket->ip) + sizeof(udppacket->udp);
	udppacket->ip.ip_len = htons((hdrsz + ft_strlen(udppacket->payload)));
}

void	udp_checksum(t_tracert_data *runtime, struct s_udp_hdr *hdr)
{
	struct s_pseudo_hdr		psh;

	inet_pton(AF_INET, runtime->target_ipv4, psh.source_address);
	psh.dest_address = sin.sin_addr.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_UDP;
	psh.udp_length = htons(sizeof(struct udphdr) + strlen(data) );
}

t_list      *forge_packetlist(t_tracert_data *runtime)
{
//    t_upacket   udppacket;
 //   t_list      *packets;
	t_list		*packet;

	char				*payload;
	struct s_udp_hdr	udp_hdr;


	payload = forge_payload(runtime);
	forge_udp_header(runtime, &udp_hdr);
	udp_checksum(runtime, &udp_hdr);

	packet = ft_lstnew(&udppacket, sizeof(t_upacket));


		printf("\nCrafted a %u bytes ipv4 packet\n", ntohs(((struct s_ipv4_hdr *)&udppacket)->ip_len));
		printf(" ----------------- \n");
		printf("hdr->hdr_len:\t%u\n", ((struct s_ipv4_hdr *)&udppacket)->ip_header_length);
		printf("hdr->version:\t%u\n", ((struct s_ipv4_hdr *)&udppacket)->ip_version);
		printf("hdr->tos    :\t%u\n", ((struct s_ipv4_hdr *)&udppacket)->ip_tos);
		printf("hdr->len    :\t%u\n", ntohs(((struct s_ipv4_hdr *)&udppacket)->ip_len));
		printf("hdr->id      :\t%u\n", ntohs(((struct s_ipv4_hdr *)&udppacket)->ip_id));
		printf("hdr->ttl     :\t%u\n", ((struct s_ipv4_hdr *)&udppacket)->ip_ttl);
		printf("hdr->type    :\t%u\n", ((struct s_ipv4_hdr *)&udppacket)->ip_type);
		printf("hdr->checksum:\t%x\n", ((struct s_ipv4_hdr *)&udppacket)->ip_checksum);
		char *src = ft_strnew(16);
		inet_ntop(AF_INET, &((struct s_ipv4_hdr *)&udppacket)->ip_src, src, 16);
		printf("hdr->src	 :\t%s\n", src);
		char *dst = ft_strnew(16);
		inet_ntop(AF_INET, &((struct s_ipv4_hdr *)&udppacket)->ip_dst, dst, 16);
		printf("hdr->dst	 :\t%s\n", dst);
		printf(" ----------------- \n\n");



	ft_lstadd(&packets, packet);


	((t_upacket *)packet->data)->udp.uh_sum
		= checksum( &((t_upacket *)packet->data)->udp,
		sizeof(struct s_udp_hdr) + 42);

    return (NULL);
}
*/