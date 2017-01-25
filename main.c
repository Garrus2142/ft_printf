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
#include <fcntl.h>

int	main()
{
	int ret1, ret2;
	long long n1, n2;
	char	*str;
	int	fd;
	setlocale(LC_ALL, "");
	/*long long a = 18446744073709551615U;
	  unsigned long long b = a;
	//unsigned long long c = b;
	printf("%llu\n", b);*/
	//char	*str;
	//size_t	size = SIZE_MAX;
	str = NULL;
	//fd = open("coucou.txt", O_WRONLY | O_CREAT);
	ret1 = ft_printf("% h");
	//close(fd);
	ret2 = printf("% h");

	printf("Return:\n\tft_printf: %d\n\tprintf: %d\n", ret1, ret2);
	
	//printf("Str: %s\n", str);
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
