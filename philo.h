/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:41:48 by gabsanch          #+#    #+#             */
/*   Updated: 2024/04/09 17:00:42 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_agora
{
	int	n_phils;
	int	threads;
	int	ttdie;
	int	tteat;
	int	ttsleep;
	int	min_meals;
	int	ended;
	pthread_t	*baby;
	struct timeval	start;
	struct s_philo	*philo;
	pthread_mutex_t	print;
	pthread_mutex_t	m_start;
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

/*check_argv*/
int	check_argv(t_agora *agora, char **argv);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);

/*birth*/
int pregnancy(char **argv, t_agora *agora);
int	building_agora(t_agora *agora);
void	giving_birth(t_agora *agora);
int	ft_strisvalid(char **argv);
int	ft_strlen(char *s);
int	free_mmr(pthread_t **baby, t_philo **philos, int error);

/*routine*/
void *routine(void *philo_arg);
void    sargent(t_agora *agora);
long int    time_passed(struct timeval start);
int food_supervisor(t_agora *agora);
void sleeping(int ttsleep, t_agora *agora);
void eat(t_philo *philo);
void    food_left(t_philo *philo);

/*utils*/
void    dead(t_agora *agora);
void    print_status(t_philo *philo, char *str, int status);

#endif
