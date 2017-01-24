/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thugo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 18:44:43 by thugo             #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <locale.h>

int	main()
{
	int ret1, ret2;
	setlocale(LC_ALL, "");
	/*long long a = 18446744073709551615U;
	  unsigned long long b = a;
	//unsigned long long c = b;
	printf("%llu\n", b);*/
	//char	*str;
	//size_t	size = SIZE_MAX;

	ret1 = ft_printf("{%03c}\n", 0);
	ret2 = printf("{%03c}\n", 0);

	printf("Return:\n\tft_printf: %d\n\tprintf: %d\n", ret1, ret2);

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
