/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:44:29 by thugo             #+#    #+#             */
/*   Updated: 2017/01/17 17:47:09 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_parsing	parsing;
	int			i;

	va_start(ap, format);
	i = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			i += parse_format(format + i + 1, &parsing, &ap);
			printf("Attribute: \"%s\" Field width: %d\n", parsing.attr, parsing.field_width);
			//printf("format: %s\n", format + i);
		}
		//else
			// Ajoute dans le buffer tant qu'il n'y a pas de %
	}
	va_end(ap);
	return (0);
}
