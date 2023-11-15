/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:34:06 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/15 12:46:04 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdupchar(int c)
{
	char	*s;
	s = (char *) malloc(sizeof(char) * 2);
	s[0] = c;
	s[1] = 0;
	return s;
}
