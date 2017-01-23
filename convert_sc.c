/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_sc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:40:13 by thugo             #+#    #+#             */
/*   Updated: 2017/01/23 20:39:28 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h> //REMOVE

static void	*process_c(t_parsing *p, va_list *ap, size_t *nbytes,
		size_t *nchars)
{
	void	*c;

	if (p->conv_spec == 'c' && p->lmod != 'l')
	{
		if ((c = (char *)malloc(sizeof(char))) == NULL)
			exit(EXIT_FAILURE);
		*(char *)c = (char)va_arg(*ap, int);
		*nbytes = sizeof(char);
	}
	else
	{
		// Renvoyer un tableau de char avec la fonction ft_to_utf8 pour ne pas envoyer les octets non utilise
		if ((c = (wchar_t *)malloc(sizeof(wchar_t))) == NULL)
			exit(EXIT_FAILURE);
		*(wchar_t *)c = (wchar_t)ft_to_utf8((int)va_arg(*ap, wchar_t));
		*nbytes = sizeof(wchar_t);
	}
	*nchars = 1;
	return (c);
}

void		convert_sc(t_parsing *p, va_list *ap)
{
	void		*str;
	size_t		nbytes;
	size_t		nchars;

	if (p->conv_spec == 'c' || p->conv_spec == 'C')
		str = process_c(p, ap, &nbytes, &nchars);
	//else
	//	str = process_s(p, ap, &nbytes, &nchars);
	printf("Char: %c, size: %zu, nchars: %zu\n", *(wchar_t *)str, nbytes, nchars);
	buffer_add(str, nbytes, nchars);
	free(str);
}
