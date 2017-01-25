/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:20:33 by thugo             #+#    #+#             */
/*   Updated: 2017/01/25 19:02:03 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static void	process_n(t_parsing *p, va_list *ap)
{
	if (p->lmod == LMOD_H)
		*(va_arg(*ap, short *)) = (short)buffer_getinfo();
	else if (p->lmod == LMOD_HH)
		*(va_arg(*ap, char *)) = (char)buffer_getinfo();
	else if (p->lmod == LMOD_L)
		*(va_arg(*ap, long *)) = (long)buffer_getinfo();
	else if (p->lmod == LMOD_LL)
		*(va_arg(*ap, long long *)) = (long long)buffer_getinfo();
	else if (p->lmod == LMOD_J)
		*(va_arg(*ap, intmax_t *)) = (intmax_t)buffer_getinfo();
	else if (p->lmod == LMOD_Z)
		*(va_arg(*ap, size_t *)) = (size_t)buffer_getinfo();
	else
		*(va_arg(*ap, int *)) = (int)buffer_getinfo();
}

static void	process_y(t_parsing *p, va_list *ap)
{
	char	*buffer;

	buffer = buffer_get();
	if (p->conv_spec == 'y')
		*(va_arg(*ap, char **)) = buffer;
	else
		write(va_arg(*ap, int), buffer, buffer_getinfo());
	if (p->attr & ATTR_HASHTAG)
	{
		buffer_clear();
		buffer_init();
	}
}

void		convert_extra(t_parsing *p, va_list *ap, size_t *nbytes)
{
	if (p->conv_spec == 'n')
		process_n(p, ap);
	else if (p->conv_spec == 'y' || p->conv_spec == 'Y')
		process_y(p, ap);
	*nbytes = 0;
}
