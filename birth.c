/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   birth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 14:51:58 by gabsanch          #+#    #+#             */
/*   Updated: 2024/03/31 18:12:30 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strisvalid(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{	
		if (i == 1 && ft_strlen(argv[i]) > 3)
			return (-1);
		if (i > 1 && ft_strlen(argv[i]) > 4)
			return (-1);
		i++;
	}
	return (0);
}

int	pregnancy(char **argv, t_agora *agora)
{
	if (ft_strisvalid(argv) == -1)
		return (-1);
	agora->n_phils = ft_atoi(argv[1]);
	agora->ttdie = ft_atoi(argv[2]);
	agora->tteat = ft_atoi(argv[3]);
	agora->ttsleep =  ft_atoi(argv[4]);
	if (argv[5])
		agora->min_meals = ft_atoi(argv[5]);
	if (agora->n_phils == 0 || agora->n_phils > 200 || !agora->ttdie
		|| !agora->tteat || !agora->ttsleep
		|| (argv[5] && !agora->min_meals))
		return (-1);
	pthread_mutex_init(&agora->print, NULL);
	pthread_mutex_init(&agora->start, NULL);
	pthread_mutex_init(&agora->end, NULL);
	pthread_mutex_init(&agora->end_ph, NULL);
	agora->baby = malloc(sizeof(pthread_t) * agora->n_phils);
	return (0);
}
