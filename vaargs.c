/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vaargs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 00:26:45 by thugo             #+#    #+#             */
/*   Updated: 2017/01/20 00:27:22 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long			get_ll_arg(t_parsing *p, va_list *ap)
{
	if (p->lmod == LMOD_H)
		return ((short)va_arg(*ap, int));
	else if (p->lmod == LMOD_HH)
		return ((char)va_arg(*ap, int));
	else if (p->lmod == LMOD_L)
		return (va_arg(*ap, long));
	else if (p->lmod == LMOD_LL)
		return (va_arg(*ap, long long));
	else if (p->lmod == LMOD_J)
		return (va_arg(*ap, intmax_t));
	else if (p->lmod == LMOD_Z)
		return (va_arg(*ap, size_t));
	else
		return (va_arg(*ap, int));
}

unsigned long long	get_llu_arg(t_parsing *p, va_list *ap)
{
	if (p->lmod == LMOD_H)
		return ((unsigned short)va_arg(*ap, unsigned int));
	else if (p->lmod == LMOD_HH)
		return ((unsigned char)va_arg(*ap, unsigned int));
	else if (p->lmod == LMOD_L)
		return (va_arg(*ap, unsigned long));
	else if (p->lmod == LMOD_LL)
		return (va_arg(*ap, unsigned long long));
	else if (p->lmod == LMOD_J)
		return (va_arg(*ap, intmax_t));
	else if (p->lmod == LMOD_Z)
		return (va_arg(*ap, size_t));
	else
		return (va_arg(*ap, unsigned int));
}
