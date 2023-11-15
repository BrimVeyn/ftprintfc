/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dupnfree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:14:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/15 16:12:11 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

char *ft_dupnfree(const char *src)
{
    if (!src)
	{
		free((void *) src);
        return NULL; 
	}
    size_t len = ft_strlen(src);
    char *ptr = malloc((len + 1) * sizeof(char));
    if (ptr == NULL)
		return NULL;
    ft_memcpy(ptr, src, len + 1); 

	// printf("|%s|", src);
    free((void *)src);
    return ptr;
}
