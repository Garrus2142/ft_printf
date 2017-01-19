/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:44:43 by thugo             #+#    #+#             */
/*   Updated: 2017/01/19 05:23:53 by thugo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>

int	main()
{
	/*long long a = 18446744073709551615U;
	unsigned long long b = a;
	//unsigned long long c = b;
	printf("%llu\n", b);*/
	char	*str;
	size_t	size;
	
	ft_printf("%d", -1);
	
	/*buffer_init();
	buffer_add("salut", 5, 5);
	buffer_add(" ca va?", 7, 7);
	str = buffer_get();
	buffer_getinfo(&size, NULL);
	write(1, str, size);
	buffer_clear();
	free(str);*/
	return (0);
}
