/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 22:05:30 by thugo             #+#    #+#             */
/*   Updated: 2017/01/19 05:31:05 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"
#include <stdio.h> //REMOVE REMOVE

static long long	get_ll_arg(t_parsing *p, va_list *ap)
{
	if (p->lmod == LMOD_H)
		return (va_arg(*ap, int));
		//return (va_arg(*ap, int) & UCHAR_MAX);
	else if (p->lmod == LMOD_HH)
		return (va_arg(*ap, int));
		//return (va_arg(*ap, int) & USHRT_MAX);
	else if (p->lmod == LMOD_L)
		return (va_arg(*ap, long));
		//return (va_arg(*ap, long) & ULONG_MAX);
	else if (p->lmod == LMOD_LL)
		return (va_arg(*ap, long long));
	else if (p->lmod == LMOD_J)
		return (va_arg(*ap, intmax_t));
	else if (p->lmod == LMOD_Z)
		return (va_arg(*ap, size_t));
	else
		return (va_arg(*ap, int));
		//return (va_arg(*ap, int) & UINT_MAX);
}

static void convert2_diouxb(t_parsing *p, char *base, long long arg, char **str)
{
	char	*prec;
	int		len;

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
	if (p->conv_spec == 'd' || p->conv_spec == 'D' || p->conv_spec == 'i')
		*str = ft_llitoa_base(arg, base);
	else
		*str = ft_lluitoa_base(arg, base);
	size_t i = 0;
	while (i < sizeof(arg) * 8)
	{
		printf("%lld", (arg >> (((sizeof(arg) * 8) - 1) - i)) & 0x1);
		i++;
		if (i % 4 == 0)
			printf(" ");
	}
	printf("\n");
	
	if (p->precision - (len = ft_strlen(*str)) > 0)
	{
		len = ft_strlen(*str);
		if ((prec = ft_strnew(p->precision - len)) == NULL)
			exit(0);
		ft_memset(prec, '0', (size_t)p->precision - len);
		*str = ft_strfjoin(prec, 1, *str, 1);
	}
}

static char	*convert_diouxb(t_parsing *p, va_list *ap, size_t *nchars)
{
	long long	arg;
	char		base[17];
	char		*str;

	arg = get_ll_arg(p, ap);
	convert2_diouxb(p, base, arg, &str);
	*nchars = ft_strlen(str);
	return (str);
}

void		convert(t_parsing *p, va_list *ap)
{
	char	*str;
	size_t	nchars;

	str = NULL;
	if (ft_strchr("dDioOuUxXb", p->conv_spec))
		str = convert_diouxb(p, ap, &nchars);
	if (str != NULL) // TEMP CONDITION
	{
		buffer_add(str, nchars, nchars);
		free(str);
	}
}
