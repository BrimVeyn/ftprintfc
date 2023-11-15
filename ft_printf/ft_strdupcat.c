/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:30:40 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/10 17:23:08 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdupcat(char *s, char *prefix)
{
	char	*ns;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ns = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(prefix) + 1));
	if (ns == NULL)
		return (NULL);
	while(prefix[i])
		ns[j++] = prefix[i++];
	i = 0;
	while(s[i] != 0)
		ns[j++] = s[i++];
	ns[j] = 0;
	return (ns);
}
