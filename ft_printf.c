/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:44:29 by thugo             #+#    #+#             */
/*   Updated: 2017/01/23 20:30:46 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // REMOVE
#include <unistd.h>
#include "ft_printf.h"

static void	process_format(const char *format, va_list *ap)
{
	t_parsing	p;
	int			i;
	int			s_start;

	i = -1;
	s_start = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			if (s_start > -1)
				buffer_add(format + s_start, i - s_start, i - s_start);
			s_start = -1;
			i += parse_format(format + i + 1, &p, ap);
			//printf("Attribute: %d Field width: %d Precision: %d Lmod: %d Conv: %c\n", p.attr, p.field_width, p.precision, p.lmod, p.conv_spec);
			if (ft_strchr("dDioOuUxXb", p.conv_spec))
				convert_dioux(&p, ap);
			else if (ft_strchr("cCsS", p.conv_spec))
				convert_sc(&p, ap);
		}
		else if (s_start == -1)
			s_start = i;
	}
	if (s_start > -1)
		buffer_add(format + s_start, (size_t)i - s_start, (size_t)i - s_start);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	size_t		nbytes;
	size_t		nchars;
	char		*str;

	buffer_init();
	va_start(ap, format);
	process_format(format, &ap);
	va_end(ap);
	buffer_getinfo(&nbytes, &nchars);
	str = buffer_get();
	buffer_clear();
	if (nbytes > 0)
		write(1, str, nbytes);
	free(str);
	return (nchars);
}
