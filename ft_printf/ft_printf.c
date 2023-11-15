/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:12:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/11/15 17:16:29 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

static	int	is_in(const char *fmt, const char *charset)
{
	size_t	i;
	i = 0;
	while (charset[i])
	{
		if (fmt[0] == charset[i])
			return (1);
		i++;
	}
	return (0);
}	

static size_t	flag_count(const char *fmt)
{
	char const	*charset = "cspdiuxX%";
	size_t	i;

	i = 0;
	// printf("%c", fmt[i]);
	while (!is_in(&fmt[i], charset))
		i++;
	return (i);
}


t_flag_triglist initialise_triglist(t_flag_triglist triglist)
{
	triglist.dash = 0;
	triglist.zero = 0;
	triglist.dot = 0;
	triglist.hash = 0;
	triglist.blank = 0;
	triglist.plus = 0;
	triglist.num_one = 0;
	triglist.num_two = 0;
	triglist.type = '0';

	return (triglist);
}

t_flag_triglist parse_flags(const char *fmt, size_t flag_num, t_flag_triglist triglist)
{
	size_t	i;
	size_t numsize;

	i = 0;
	numsize = 0;
	while (i < flag_num)
	{
		if (fmt[i] != '0')
			triglist.num_one = ft_parse_num(&fmt[i], &numsize);
		i += numsize;
		if (fmt[i] == '#')
			triglist.hash = 1;
		if (fmt[i] == '0')
		{
			triglist.zero = 1;
			triglist.num_one = ft_parse_num(&fmt[++i], &numsize);
			i += numsize;
		}
		if (fmt[i] == '+')
		{
			triglist.plus = 1;
			if (fmt[i + 1] != '0')
				triglist.num_one = ft_parse_num(&fmt[++i], &numsize);
			i += numsize;
		}
		if (fmt[i] == '-')
		{
			triglist.dash = 1;
			triglist.num_one = ft_parse_num(&fmt[++i], &numsize);
			i += numsize;
		}
		if (fmt[i] == '.')
		{
			triglist.dot = 1;
			triglist.num_two = ft_parse_num(&fmt[++i], &numsize);
			i += numsize - 1;
		}
		if (fmt[i] == ' ')
			triglist.blank = 1;
		i++;
		// printf("PL %d", triglist.num_one);
	}
	return (triglist);
}

char	*ft_cjoin(const char *fstr, int c, int n, int p)
{
	char	*tmp;
	char	*result;

	if (n < 0)
		return ((char *) fstr);
	tmp = (char *) malloc(sizeof(char) * n + 1);
	if (!tmp)
		return (NULL);
	tmp = ft_memset(tmp, c, n);
	tmp[n] = '\0';
	if (p == 0)
		result = ft_strjoin(tmp, fstr);
	if (p == 1)
		result = ft_strjoin(fstr, tmp);
	free(tmp);
	free((void *) fstr);
	return (result);
}

int	ft_isdorx(char *fstr)
{
	size_t	i;
	size_t	j; 
	int	flag;
	char base[] = "0123456789abcdefABCDEF";

	i = 0;
	while(fstr[i])
	{
		j = 0;
		flag = 0;
		while(base[j])
		{
			if (fstr[i] == base[j])
			{
				flag = 1;
				break;
			}
			j++;
		}
		if (flag == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*exec_flag_part_two(char *newstr, t_flag_triglist a)
{
	if (a.zero && a.dot == 1 && a.num_one != 0 && a.num_two == 0 && newstr[0] == '0') 
		newstr = ft_cjoin(ft_memset(newstr, ' ', 1), ' ', a.num_one - ft_strlen(newstr), 0);
	else if (a.zero && a.num_two == 0 && newstr[0] != '-') 
		newstr = ft_cjoin(newstr, '0', a.num_one - ft_strlen(newstr), 0);
	else if (a.zero && a.num_two == 0 && newstr[0] == '-')
		newstr = ft_memset(ft_cjoin(ft_memset(newstr, '0', 1), '0', a.num_one - ft_strlen(newstr), 0), '-', 1);
	if (a.hash && a.zero && (a.type == 'x' || a.type == 'X'))
		newstr = ft_memset(ft_memset(&newstr[0], '0', 1) + 1, 'x', 1);
	else if ((a.type == 'x' || a.type == 'X') && a.hash && !(ft_strlen(newstr) == 1 && newstr[0] == '0'))
		newstr = ft_strjoinfree("0x", newstr);
	if (a.plus && a.zero && a.dot == 0)
		newstr = ft_memset(newstr, '+', 1);
	if (a.plus && a.zero && a.dot)
		newstr = ft_cjoin(newstr, '+', 1, 0);
	if (a.plus && a.num_one == 0 && newstr[0] != '-')
		newstr = ft_strjoinfree("+", newstr);
	if (a.plus && a.num_one)
		newstr = ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr), 0);
	else if (a.dash == 0 && a.num_one)
		newstr = ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr), 0);
	if (a.blank && (a.zero || a.dot) && newstr[0] != '-' && a.type != 's')
			newstr = ft_cjoin(newstr, ' ', 1, 0);
	if(a.type == 'X')
		return (ft_strupp(newstr));
	return (newstr);
}

char	*execute_flag(const char *fstr, t_flag_triglist a)
{
	char	*newstr; 
	int		offset;
	int const base_len = (int) ft_strlen(fstr);
	const char *base_str = ft_strdup(fstr);

	newstr = (char *) fstr;
	offset = 2 * (a.type == 'x' || a.type == 'X');
	if (a.dot && base_str[0] ==  '0' && !a.zero)
		ft_memset(newstr, 0, 1);
	if (a.blank && a.zero == 0 && a.dot == 0 && newstr[0] != '-' && a.type != 's')
			newstr = ft_cjoin(newstr, ' ', 1, 0);
	if(a.type == 's' && a.dot)
		newstr =  ft_substrfree(newstr, 0, a.num_two);
	else if (a.num_two && newstr[0] == '-')
		newstr = ft_cjoin(ft_cjoin(ft_memset(newstr, '0', (base_len - 1 < a.num_two)), '0', a.num_two - base_len, 0), '-', (base_len - 1 < a.num_two), 0);
	else if (a.num_two)
		newstr = ft_cjoin(newstr, '0', a.num_two - ft_strlen(newstr), 0);
	if (a.dash && (a.zero || a.hash))
		newstr = ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr) - offset, 1);
	else if (a.dot && ((a.dash && base_str[0] == '0' && !a.num_two && !a.num_one) || (a.num_two < 6 && base_str[0] == '(' && a.type == 's')))
	{
		free(newstr);
		newstr = ft_strdup("");
	}
	else if (a.dash)
		newstr = ft_memset(ft_cjoin(newstr, ' ', a.num_one - ft_strlen(newstr), 1), ' ', (base_str[0] == '0' && a.dot && a.num_one >= a.num_two));
	free((void *)base_str);
	return(exec_flag_part_two(newstr, a));
}


char	*parse_format(const char	*fmt, va_list *args, t_flag_triglist *triglist)
{
	char	c;

	if (*fmt == 'd' || *fmt == 'i')
		return (ft_dupnfree(ft_itoa(va_arg(*args, int))));
	else if (*fmt == 's')
	{
		triglist->type = 's';
		return(ft_strdupm(va_arg(*args, char *)));
	}
	else if (*fmt == 'c')
	{
		c = (char) va_arg(*args, int);
		if (c == 0)
		{
			return (ft_strdupchar(-45));
		}
		return (ft_strdupchar(c));
	}
	else if (*fmt == 'u')
		return (ft_dupnfree(ft_uitoa(va_arg(*args, unsigned int))));
	else if (*fmt == 'x')
	{
		triglist->type = 'x';
		return (ft_dupnfree(ft_uitoahex(va_arg(*args, unsigned int))));
	}
	else if (*fmt == 'X')
	{
		triglist->type = 'X';
		return (ft_dupnfree(ft_strupp(ft_uitoahex(va_arg(*args, unsigned int)))));
	}
	else if (*fmt == '%')
		return (ft_strdup("%"));
	else if (*fmt == 'p')
		return (ft_llitoahex(va_arg(*args, unsigned long long int)));
	return (ft_strdup(""));
}

int	execute_and_print_c(char *newstr, t_flag_triglist a)
{
	size_t	i;

	i = 0;
	// printf("|%d, %d|", a.dash, a.num_one);
	if (a.dash && a.num_one)
	{
		newstr = ft_cjoin(newstr, ' ', a.num_one * (a.num_one > 1) , 0);	
	}
	else if (a.num_one && !a.dash)
	{
		newstr = ft_cjoin(newstr, ' ', (a.num_one - 1) * (a.num_one > 1), 1);
	}
	while (newstr[i++] != 0)
	{
		if (newstr[i] != -45)
		{
			write(1, &newstr[i], 1);
		}
		else
		{
			write(1, "\0", 1);
		}
	}
	free(newstr);
	return(i);
}


int	ft_printf(const char *fmt, ...)
{
	va_list args;
	size_t	i;
	size_t	flag_num;
	t_flag_triglist arg_triglist;
	char	*fstr;
	int		len;
	int		flag;

	va_start(args, fmt);
	i = 0;
	len = 0;
	flag = 0;
	while(fmt[i])
	{
		if (fmt[i] == '%')
		{
			flag_num = flag_count(&fmt[++i]);
			if (flag_num == 0)
			{
				fstr = parse_format(&fmt[i], &args, &arg_triglist);
				len += ft_strlen(fstr);
				if (ft_strlen(fstr) >= 1 && fstr[0] != -45)
				{
					ft_putstr_fd(fstr, 1);
					free(fstr);
				}
				else
					execute_and_print_c(fstr, arg_triglist);
			}
			else
			{
				arg_triglist = initialise_triglist(arg_triglist);
				arg_triglist = parse_flags(&fmt[i], flag_num, arg_triglist);
				i += flag_num;
				fstr = parse_format(&fmt[i], &args, &arg_triglist);
				flag = (-1 * (fstr[0] == -45)) * (-1 * (flag == 0));
				if (flag == 1)
				{
					// len += 1;
					len += execute_and_print_c(fstr, arg_triglist) - 1;	
				}
				if (flag == 0)
				{
					fstr = execute_flag(fstr, arg_triglist);
					ft_putstr_fd(fstr, 1);
					len+= ft_strlen(fstr);
					free(fstr);
				}

			}
		}
		else
		{
			ft_putchar_fd(fmt[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}
//
// #include <limits.h>
//
// int	main(void)
// {
// 	ft_printf("C = %-1c %-2c %-3c |\n", '2', '1', 0);
// 	printf("R = %-1c %-2c %-3c |\n", '2', '1', 0);
// 	ft_printf("C = %-50c now you see|\n", '\0');
// 	printf("R = %-50c now you see|\n", '\0');
// 	// printf("%-10.d", 0);
// 	// ft_printf("%-10.d", 0);
// 	// ft_printf("%-2c|%-3c|%-4c|*\n", 0, 'a', 0);
// 	// printf("%-2c|%-3c|%-4c|*\n", 0, 'a', 0);
// 	// ft_printf("%-.X", 0);
// 	// ft_printf("%10c|\n", 0);
// 	// printf("%10c|\n", 0);
// 	// ft_printf("%50s", 0);
// 	// ft_printf("%s", 0);
// 	// printf(" %-15d |\n", -1);
// 	// ft_printf(" %-15d |\n", -1);
// 	// printf(" %01u |\n", 0);
// 	// ft_printf(" %01u |\n", 0);
// 	// printf("%30.6d\n", 12);
// 	// ft_printf("%30.6d\n", 12);
// 	// printf("%30.6s\n", "ceciestunestring");
// 	// ft_printf("%30.6s\n", "ceciestunestring");
// 	// printf("%-30.6s\n", "ceciestunestring");
// 	// ft_printf("%-30.6s\n", "ceciestunestring");
// 	// printf("%+030.6d|\n", 12);
// 	// ft_printf("%+030.6d|\n", 12);
// 	// printf("%+030d|\n", 12);
// 	// ft_printf("%+030d|\n", 12);
// 	// printf("%-30d|\n", 12);
// 	// ft_printf("%-30d|\n", 12);
// 	// printf("%30d|\n", 12);
// 	// ft_printf("%30d|\n", 12);
// 	// printf("%#10x|\n", 2566);
// 	// ft_printf("%#10x|\n", 2566);
// 	// printf("%#010x|\n", 2566);
// 	// ft_printf("%#010x|\n", 2566);
// 	// printf("%#-10x|\n", 2566);
// 	// ft_printf("%#-10x|\n", 2566);
// 	// printf("%#.10x|\n", 2566);
// 	// ft_printf("%#.10x|\n", 2566);
// 	// printf("%#20.10x|\n", 2566);
// 	// ft_printf("%#20.10x|\n", 2566);
// 	// printf("%#-20.10x|\n", 2566);
// 	// ft_printf("%#-20.10x|\n", 2566);
// 	// printf("%#x|\n", 10);
// 	// ft_printf("%#x|\n", 10);
// 	// printf("%-4x|\n", 9);
// 	// ft_printf("%-4x|\n", 9);
// 	//
// 	// printf("%#10X|\n", 2566);
// 	// ft_printf("%#10X|\n", 2566);
// 	// printf("%#010X|\n", 2566);
// 	// ft_printf("%#010X|\n", 2566);
// 	// printf("%#-10X|\n", 2566);
// 	// ft_printf("%#-10X|\n", 2566);
// 	// printf("%#.10X|\n", 2566);
// 	// ft_printf("%#.10X|\n", 2566);
// 	// printf("%#20.10X|\n", 2566);
// 	// ft_printf("%#20.10X|\n", 2566);
// 	// printf("%#-20.10X|\n", 2566);
// 	// ft_printf("%#-20.10X|\n", 2566);
// 	// printf("% d|\n", 2256);
// 	// ft_printf("% d|\n", 2256);
// 	// printf("% 10.10d|\n", 2256);
// 	// ft_printf("% 10.10d|\n", 2256);
// 	// printf("% -4d|\n", 20);
// 	// ft_printf("% -4d|\n", 20);
// 	// printf("% 4d|\n", 20);
// 	// ft_printf("% 4d|\n", 20);
// 	// printf(" %5d |\n", -1);
// 	// ft_printf(" %5d |\n", -1);
// 	// printf(" %#x |\n", 0);
// 	// ft_printf(" %#x |\n", 0);
// 	// printf("%011d\n", 1111111);
// 	// ft_printf("%011d\n", 1111111);
// 	// printf("%011d\n", -1111111);
// 	// ft_printf("%011d\n", -1111111);
// 	// printf("%.11d\n", -1111111);
// 	// ft_printf("%.11d\n", -1111111);
// 	// printf("%-9d %-10d %-11d %-12d %-13d %-14d %-15d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
// 	// ft_printf("%-9d %-10d %-11d %-12d %-13d %-14d %-15d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
// 	
//
// 	// printf("p %p\n", (void *) 43);
// 	// ft_printf("p %p\n", (void *) 43);
// 	// printf("%x\n", (unsigned int) 4294967295);
// 	// printf("%x", (unsigned int) 2147483647);
// 	// printf("%%c  = %c \n", 'c');
// 	// printf("%%s  = %s \n", "str");
// 	// printf("%%p  = %p \n", (void *) 1278);
// 	// printf("%%d  = %d \n", 1278);
// 	// printf("%%i  = %i \n", 1278);
// 	// printf("%%u  = %u \n", 1278);
// 	// printf("%%x  = %x \n", 1278);
// 	// printf("%%X  = %X \n", 1278);
// 	// printf("%%   = %% \n");
// 	// printf("%%#x = %#x \n", 1278);
// 	// printf("%%#X = %#X \n", 1278);
// 	// printf("%%-#10x  = %-#10x|\n", 546);
// 	// printf("%%x      = %x|\n", 546);
// 	//
// 	// printf("\n%%#68.x    = %#68.x|\n", 456);
// 	// printf("%%#68x     = %#68x|\n", 456); //Cas particulier
// 	// printf("%%#.68x    = %#.68x|\n", 456);
// 	// printf("%%#.68x    = %.68d|\n", 456);
// 	// printf("%%#-68x    = %#-68x|\n", 456);
// 	//
// 	//
// 	//
// 	// printf("%%#68x  = %#68x|\n", 456);
// 	// printf("%%#068x  = %#068x|\n", 456);
// 	// printf("%%.68x   = %.68x|\n", 456);
// 	// printf("%%#10x   = %#10x|\n", 546);
// 	// printf("%%#010x  = %#010x|\n", 546);
// }
