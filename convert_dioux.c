/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 22:05:30 by thugo             #+#    #+#             */
/*   Updated: 2017/01/20 01:52:22 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"

static void	process_dioux_hash(t_parsing *p, char **str, size_t *nchars)
{
	char	*join;

	if ((p->conv_spec == 'o' || p->conv_spec == 'O') &&
			(*nchars == 0 || *str[*nchars - 1] != '0'))
	{
		if ((join = ft_strnew(1)) == NULL)
			exit(0);
		join[0] = '0';
		*str = ft_strfjoin(join, 1, *str, 1);
		*nchars += 1;
	}
	else if ((p->conv_spec == 'x' || p->conv_spec == 'X') &&
			*nchars > 0 && *str[*nchars - 1] != '0')
	{
		if ((join = ft_strnew(2)) == NULL)
			exit(0);
		ft_strcpy(join, p->conv_spec == 'X' ? "0X" : "0x");
		*str = ft_strfjoin(join, 1, *str, 1);
		*nchars += 1;
	}
}

static void	process_dioux(t_parsing *p, char **str, size_t *nchars)
{
	char	*join;

	*nchars = ft_strlen(*str);
	if (*nchars == 1 && p->precision == 0 && *str[0] == '0')
		*str[--(*nchars)] = '\0';
	else if (p->precision > 0 && (int)(p->precision - *nchars) > 0)
	{
		if ((join = ft_strnew((int)(p->precision - *nchars))) == NULL)
			exit(0);
		ft_memset(join, '0', (int)(p->precision - *nchars));
		*str = ft_strfjoin(join, 1, *str, 1);
		*nchars += (int)(p->precision - *nchars);
	}
	if (p->attr & ATTR_HASHTAG)
		process_dioux_hash(p, str, nchars);
}

void		convert_dioux(t_parsing *p, va_list *ap)
{
	size_t			nchars;
	char			base[17];
	char			*str;

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
		str = ft_llitoa_base(get_ll_arg(p, ap), base);
	else
		str = ft_lluitoa_base(get_llu_arg(p, ap), base);
	if (str == NULL)
		exit(0);
	process_dioux(p, &str, &nchars);
	buffer_add(str, nchars, nchars);
	free(str);
}
