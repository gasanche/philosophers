/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:41:12 by gabsanch          #+#    #+#             */
/*   Updated: 2024/04/09 17:23:34 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str [i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return (nb * sign);
}

int	check_argv(t_agora *agora, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while(argv[++i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				return (-1);
			j++;
		}
	}
	if (pregnancy(argv, agora) == -1)
		return (-1);
	return (0);
}
/*
#include <stdio.h>
int	main ()
{
	char str[] = "adgv";

	printf("Atoi devuelve: %i\n", ft_atoi(str));
	return 0;
}*/
