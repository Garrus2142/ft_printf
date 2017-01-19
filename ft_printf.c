/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:44:29 by thugo             #+#    #+#             */
/*   Updated: 2017/01/19 05:04:06 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // REMOVE
#include <unistd.h>
#include "ft_printf.h"

static void	process_format(const char *format, va_list *ap)
{
	t_parsing	parsing;
	int			i;

	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			parse_format(format + i + 1, &parsing, ap);
			convert(&parsing, ap);
			//printf("Attribute: %d Field width: %d Precision: %d Lmod: %d Conv: %c\n", parsing.attr, parsing.field_width, parsing.precision, parsing.lmod, parsing.conv_spec);
			//printf("format: %s\n", format + i);
		}
		//else
			// Ajoute dans le buffer tant qu'il n'y a pas de %
	}
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
	return (nchars);
}
