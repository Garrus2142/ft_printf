/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 22:05:30 by thugo             #+#    #+#             */
/*   Updated: 2017/01/20 08:42:50 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"
#include <stdio.h>

static void	process_dioux_hash(t_parsing *p, char **str, size_t *nchars,
		unsigned long long arg)
{
	char	*join;

	if ((p->conv_spec == 'o' || p->conv_spec == 'O') &&
			(*nchars == 0 || (*str)[0] != '0'))
	{
		if ((join = ft_strnew(1)) == NULL)
			exit(0);
		join[0] = '0';
		*str = ft_strfjoin(join, 1, *str, 1);
		*nchars += 1;
	}
	else if ((p->conv_spec == 'x' || p->conv_spec == 'X') && arg > 0)
	{
		if ((join = ft_strnew(2)) == NULL)
			exit(0);
		ft_strcpy(join, p->conv_spec == 'X' ? "0X" : "0x");
		*str = ft_strfjoin(join, 1, *str, 1);
		*nchars += 2;
	}
}

static void	process_precision(t_parsing *p, char **str, size_t *nchars,
		unsigned long long arg)
{
	int		neg;
	char	*join;

	neg = 0;
	if (p->precision == 0 && arg == 0)
		(*str)[--(*nchars)] = '\0';
	else if (p->precision > 0 && (int)(p->precision - *nchars) +
			((*str)[0] == '-' ? 1 : 0) > 0)
	{
		if ((*str)[0] == '-')
			neg = 1;
		if ((join = ft_strnew((neg ? 1 : 0) + (int)(p->precision - *nchars)))
				== NULL)
			exit(0);
		ft_memset(join, '0', (neg ? 1 : 0) + (int)(p->precision - *nchars));
		if (neg)
		{
			(*str)[0] = '0';
			join[0] = '-';
		}
		*str = ft_strfjoin(join, 1, *str, 1);
		*nchars += (neg ? 1 : 0) + (int)(p->precision - *nchars);
	}
}

static void	process_dioux_zero(t_parsing *p, char **str, size_t *nchars,
		unsigned long long arg)
{
	if (p->field_width == 0)
		p->precision = 1;
	else
	{
		p->precision = p->field_width;
		if (p->attr & ATTR_HASHTAG && arg != 0 &&
				(p->conv_spec == 'x' || p->conv_spec == 'X'))
			p->precision -= 2;
		if ((p->attr & ATTR_SPACE || p->attr & ATTR_PLUS || (*str)[0] == '-') &&
				ft_strchr("diD", p->conv_spec))
			p->precision--;
	}
	process_precision(p, str, nchars, arg);
}

static void	process_dioux(t_parsing *p, char **str, unsigned long long arg)
{
	size_t	nchars;
	char	*join;

	nchars = ft_strlen(*str);
	process_precision(p, str, &nchars, arg);
	if (p->attr & ATTR_ZERO && p->precision == -1 && !(p->attr & ATTR_MINUS))
		process_dioux_zero(p, str, &nchars, arg);
	if (p->attr & ATTR_HASHTAG)
		process_dioux_hash(p, str, &nchars, arg);
	if ((p->attr & ATTR_SPACE || p->attr & ATTR_PLUS) && (p->conv_spec == 'd' ||
			p->conv_spec == 'i' || p->conv_spec == 'D') && (*str)[0] != '-')
	{
		if ((join = ft_strnew(1)) == NULL)
			exit(0);
		join[0] = p->attr & ATTR_PLUS ? '+' : ' ';
		*str = ft_strfjoin(join, 1, *str, 1);
		nchars += 1;
	}
	buffer_add(*str, nchars, nchars);
	free(*str);
}

void		convert_dioux(t_parsing *p, va_list *ap)
{
	char				base[17];
	char				*str;
	unsigned long long	arg;

	if (p->conv_spec == 'o' || p->conv_spec == 'O')
		ft_strcpy(base, "01234567");
	else if (p->conv_spec == 'x')
		ft_strcpy(base, "0123456789abcdef");
	else if (p->conv_spec == 'X')
		ft_strcpy(base, "0123456789ABCDEF");
	else if (p->conv_spec == 'b')
		ft_strcpy(base, "01");
	else
		ft_strcpy(base, "0123456789");
	if (p->conv_spec == 'D' || p->conv_spec == 'O' || p->conv_spec == 'U')
		p->lmod = p->lmod == LMOD_LL ? LMOD_LL : LMOD_L;
	if (p->conv_spec == 'd' || p->conv_spec == 'D' || p->conv_spec == 'i')
		str = ft_llitoa_base(get_ll_arg(p, ap, (long long *)&arg), base);
	else
		str = ft_lluitoa_base(get_llu_arg(p, ap, &arg), base);
	if (str == NULL)
		exit(0);
	process_dioux(p, &str, arg);
}
