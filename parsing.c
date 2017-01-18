/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:59:50 by thugo             #+#    #+#             */
/*   Updated: 2017/01/17 17:48:46 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // REMOVE
#include <stdlib.h>
#include <stdarg.h>
#include "ft_printf.h"
#include "libft.h"

static int	parse_attr(const char *format, t_parsing *parsing)
{
	char	*res;
	int		i;
	int		u;

	ft_bzero((void *)&(parsing->attr), 6);
	i = 0;
	u = 0;
	while (format[i] && (res = ft_strchr("#0-+ ", format[i])))
	{
		if (ft_strchr(parsing->attr, format[i]) == NULL)
			parsing->attr[u++] = *res;
		i++;
	}
	return (i);
}

int			parse_field(const char *format, t_parsing *parsing, va_list *ap)
{
	int	i;

	parsing->field_width = 0;
	i = 0;
	if (format[i] == '*')
	{
		parsing->field_width = va_arg(*ap, int);
		i++;
	}
	else
	{
		if (ft_isdigit(format[i]))
		{
			parsing->field_width = ft_atoi(format);
			i = 1;
			while (ft_isdigit(format[i]))
				i++;
		}
	}
	return (i);
}

/*int			parse_lenmodif(const char *format, t_parsing *parsing)
{
	
}*/

int			parse_format(const char *format, t_parsing *parsing, va_list *ap)
{
	int	i;

	i = 0;
	i += parse_attr(format, parsing);
	i += parse_field(format + i, parsing, ap);
	printf("Next char: %c\n", format[i]);
	return (i);
}
