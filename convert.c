/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 22:05:30 by thugo             #+#    #+#             */
/*   Updated: 2017/01/19 18:45:18 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"
#include <stdio.h> //REMOVE REMOVE


void		convert(t_parsing *p, va_list *ap)
{
	char	*str;
	size_t	nchars;

	str = NULL;
	if (ft_strchr("dDioOuUxXb", p->conv_spec))
		//str = convert_diouxb(p, ap, &nchars);
	if (str != NULL) // TEMP CONDITION
	{
		buffer_add(str, nchars, nchars);
		free(str);
	}
}
