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

int	free_mmr(pthread_t **baby, t_philo **philos, int error)
{
	if (philos && *philos)
	{
		free (*philos);
		*philos = NULL;
	}
	if (baby && *baby)
	{
		free (*baby);
		*baby = NULL;
	}
	return (printf("Error malloc\n") * 0 + error);
}

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

void	giving_birth(t_agora *agora)
{
	int	i;

	i = 0;
	pthread_mutex_lock(agora->start);
	while (i < agora->n_phils)
	{
		agora->baby[i].n_philo = i;
		agora->baby[i].lst_eat = agora->min_meals;
		agora->baby[i].dead = agora->ttdie;
		if (i == 0)
			agora->baby[i].right = &agora->baby[n_phils - 1].left;
		else
			agora->baby[i].right = &agora->baby[i - 1].left;
		pthread_mutex_init(agora->baby[i].right, NULL);
		pthread_mutex_init(&agora->baby[i].left, NULL);
		pthread_mutex_init(&agora->baby[i].died, NULL);
		agora->baby[i].agora = agora;
		i++;
	}
}

int	building_agora(t_agora *agora)
{
	int i;

	i = 0;
	while (i < n_phils)
	{
		if (pthread_create(agora->philos[i], NULL, routine, agora->baby[i]) != 0)
			return (printf("Error creating babies\n") * 0 + -1);
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
	agora->philos = malloc(sizeof(t_philo) * agora->n_phils);
	if (!agora->baby || !agora->philos)
		return(free_mmr(&agora->baby, &agora->philos, -1));
	giving_birth(agora);
	if (building_agora(agora) == -1)
		return (free_mmr(&agora->baby, &agora->philos, -1));
	return (0);
}
