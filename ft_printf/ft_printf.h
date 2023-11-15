/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:34:33 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/14 18:26:59 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_PRINTF_H
# define	FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct s_flag_triglist
{
	int	dash;
	int	zero;
	int	dot;
	int	hash;
	int	blank;
	int	plus;
	int	num_one;
	int	num_two;
	char	type;

}t_flag_triglist;

int	ft_printf(const char *fmt, ...);
char	*ft_uitoa(unsigned int n);
char	*ft_uitoahex(unsigned int n);
char	*ft_strupp(char	*str);
char	*ft_strdupcat(char *s, char *prefix);
char	*ft_dupnfree(const char *src);
char	*ft_strdupchar(int c);
char	*ft_llitoahex(unsigned long long n);
char	*ft_strdupm(const char *src);
int		ft_parse_num(const char *fmt, size_t *numsize);
char	*ft_strjoinfree(char const *s1, char const *s2);
char	*ft_substrfree(char const *s, unsigned int start, size_t len);

#endif
