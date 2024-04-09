/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:20:13 by gabsanch          #+#    #+#             */
/*   Updated: 2024/04/09 16:57:52 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    food_left(t_philo *philo)
{
    if (philo->lst_eat >= philo->agora->min_meals && philo->lst_eat >= 0)
    {
        philo->lst_eat--;
        if (philo->lst_eat == 0)
        {
            pthread_mutex_lock(&philo->agora->end_ph);
            philo->agora->min_meals++;
            pthread_mutex_unlock(&philo->agora->end_ph);
        }
    }
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->left);
    print_status(philo, "has taken a fork", 0);
    if (philo->agora->n_phils == 1)
    {
      print_status(philo, "died", 1);
      pthread_mutex_unlock(&philo->left);
      return ;
    }
    pthread_mutex_lock(philo->right);
    print_status(philo, "has taken a fork", 0);
    pthread_mutex_lock(&philo->died);
    philo->dead = time_passed(philo->agora->start) + philo->agora->ttdie;
    pthread_mutex_unlock(&philo->died);
    if (philo->lst_eat != 0) //amigo dannyel del pasado, parsea mejor lolololol
        print_status(philo, "is eating", 0);
    food_left(philo);
    sleeping(philo->agora->ttsleep, philo->agora);
    pthread_mutex_unlock(&philo->left);
    pthread_mutex_unlock(philo->right);
    if (philo->lst_eat != 0)
		print_status(philo, "is sleeping", 0);
    sleeping(philo->agora->ttsleep, philo->agora);
    if (philo->lst_eat != 0)
        print_status(philo, "is thinking", 0);
    }

void sleeping(int ttsleep, t_agora *agora)
{
    int time;

    time = time_passed(agora->start) + ttsleep;
    while (time_passed(agora->start) < time)
        usleep(100); //hay que investigarlo '-'
}

int food_supervisor(t_agora *agora)
{
    int i;
    int aux;

    i = 0;
    pthread_mutex_lock(&agora->end_ph);
    aux = agora->min_meals;
    pthread_mutex_unlock(&agora->end_ph);
    if (aux == agora->n_phils)
    {
        pthread_mutex_lock(&agora->end);
        agora->ended = 1;
        pthread_mutex_unlock(&agora->end);
        return (1);
    }
    return (0);
}

long int    time_passed(struct timeval start)
{
    struct timeval  end;
    suseconds_t time;

    gettimeofday(&end, NULL);
    time = (end.tv_usec / 1000 + end.tv_sec * 1000)
            - (start.tv_usec / 1000 + start.tv_sec * 1000);
	//printf("el start es: %d\n", time);
    return (time);
}

void    sargent(t_agora *agora)
{
    int i;
    int time;

    i = 0;
    while (i < agora->n_phils)
    {
        pthread_mutex_lock(&agora->philo[i].died);
        time = agora->philo[i].dead;
        pthread_mutex_unlock(&agora->philo[i].died);
        if (time_passed(agora->start) > time)
        {
            pthread_mutex_lock(&agora->end);
            agora->ended = 1;
            pthread_mutex_unlock(&agora->end);
            print_status(&agora->philo[i], "died", 1);
            break ;
        }
        if (agora->min_meals > 0 && food_supervisor(agora))
            break ;
        i++;
        if (i == agora->n_phils)
            i = 0;
        usleep(60); //hay que comprobarlo
    }
}

void *routine(void *philo_arg)
{
    t_philo *philo;
    int     status;

    philo = (t_philo *)philo_arg; //aclarar pa que sirve
	//printf("n_philo tiene: %i\n", philo->n_philo);
    if (philo->n_philo % 2 == 1)
    {
        sleeping(50, philo->agora); //investigar por que es 50
    }
    status = 0;
    while (status != 1)
    {
        eat(philo);
        pthread_mutex_lock(&philo->agora->end);
        status = philo->agora->ended;
        pthread_mutex_unlock(&philo->agora->end);
    }
    return (NULL);
}
