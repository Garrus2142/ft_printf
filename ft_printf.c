/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:44:29 by thugo             #+#    #+#             */
/*   Updated: 2017/01/24 20:54:26 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // REMOVE
#include <unistd.h>
#include "ft_printf.h"

static char	*process_field_width(t_parsing *p, char *str, size_t *nbytes)
{
	long long	num_space;
	char		*spaces;
	char		*new;

	num_space = (long long)p->field_width - (long long)*nbytes;
	if (num_space <= 0)
		return (str);
	if ((spaces = (char *)malloc(sizeof(char) * num_space)) == NULL)
		exit(EXIT_FAILURE);
	ft_memset(spaces, ' ', num_space);
	if (p->attr & ATTR_MINUS)
	{
		if ((new = (char *)ft_memjoin(str, *nbytes, spaces, num_space)) == NULL)
			exit(EXIT_FAILURE);
		*nbytes += num_space;
	}
	else
	{
		if ((new = (char *)ft_memjoin(spaces, num_space, str, *nbytes)) == NULL)
			exit(EXIT_FAILURE);
		*nbytes += num_space;
	}
	free(spaces);
	free(str);
	return (new);
}

static void	process_conv(t_parsing *p, va_list *ap)
{
	size_t	nbytes;
	char	*str;

	str = NULL;
	if (ft_strchr("dDioOuUxXbp", p->conv_spec))
		str = convert_dioux(p, ap, &nbytes);
	else if (ft_strchr("cCsS%", p->conv_spec))
		str = convert_sc(p, ap, &nbytes);
	else
	{
		if ((str = (char *)malloc(sizeof(char))) == NULL)
			exit(EXIT_FAILURE);
		str[0] = p->conv_spec;
		nbytes = 1;
	}
	if (p->field_width > 0 && (p->attr & ATTR_ZERO) == 0)
		str = process_field_width(p, str, &nbytes);
	buffer_add(str, nbytes);
	free(str);
}

static void	process_format(const char *format, va_list *ap)
{
	t_parsing	p;
	int			i;
	int			s_start;

	i = -1;
	s_start = -1;
	while (format[++i] != '\0')
	{
		if (format[i] == '%')
		{
			if (s_start > -1)
				buffer_add(format + s_start, i - s_start);
			s_start = -1;
			if (format[i + 1] == '\0')
				break;
			i += parse_format(format + i + 1, &p, ap);
			//printf("Attribute: %d Field width: %d Precision: %d Lmod: %d Conv: %d\n", p.attr, p.field_width, p.precision, p.lmod, p.conv_spec);
			process_conv(&p, ap);
		}
		else if (s_start == -1)
			s_start = i;
	}
	if (s_start > -1)
		buffer_add(format + s_start, (size_t)i - s_start);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	size_t		nbytes;
	char		*str;

	buffer_init();
	va_start(ap, format);
	process_format(format, &ap);
	va_end(ap);
	nbytes = buffer_getinfo();
	str = buffer_get();
	buffer_clear();
	if (nbytes > 0)
		write(1, str, nbytes);
	free(str);
	return (nbytes);
}
