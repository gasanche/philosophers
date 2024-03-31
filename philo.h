/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:41:48 by gabsanch          #+#    #+#             */
/*   Updated: 2024/03/31 18:51:19 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_agora
{
	int	n_phils;
	int	threads;
	int	ttdie;
	int	tteat;
	int	ttsleep;
	int	min_meals;
	pthread_t	*baby;
	struct s_philo	*philos;
	pthread_mutex_t	print;
	pthread_mutex_t	start;
	pthread_mutex_t	end;
	pthread_mutex_t	end_ph;
}	t_agora;

typedef struct s_philo
{
	int	n_philo;
	int	lst_eat;
	int	dead;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
	pthread_mutex_t	died;
	struct s_agora	*agora;
}	t_philo;

int	check_argv(t_philos *philos, char **argv);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int pregnancy(char **argv, t_philos *philos);

#endif
