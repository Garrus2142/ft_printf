/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:43:19 by thugo             #+#    #+#             */
/*   Updated: 2017/01/17 17:48:29 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>

typedef struct		s_parsing
{
	char	attr[6];
	int		field_width;
	int		precision;
	char	len_modifier;
	char	conv_spec;
}					t_parsing;

int					ft_printf(const char *format, ...);
int					parse_format(const char *format, t_parsing *parsing, 
						va_list *ap);

#endif
