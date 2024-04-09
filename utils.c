/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:19:25 by gabsanch          #+#    #+#             */
/*   Updated: 2024/04/09 17:42:38 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    print_status(t_philo *philo, char *str, int status)
{
    int time;
    int the_end;

    the_end = 0;
    pthread_mutex_lock(&philo->agora->print); //probar estos mutex raros
    pthread_mutex_lock(&philo->agora->end); //cosas raras del dannyel del pasado. se pueden borrar?
    the_end = philo->agora->ended;
    pthread_mutex_unlock(&philo->agora->end);
    time = time_passed(philo->agora->start);
	//printf("\ntime devuelve : %d\n", time);
    if (the_end != 1 || status == 1)
        printf("%d %d %s\n", time, philo->n_philo + 1, str);
    pthread_mutex_unlock(&philo->agora->print);
}

void    dead(t_agora *agora)
{
    int i;

    i = -1;
    while (++i < agora->n_phils)
        pthread_join(agora->baby[i], NULL);
    i = -1;
    while (++i < agora->n_phils)
    {
        pthread_mutex_destroy(&agora->philo[i].left);
        pthread_mutex_destroy(&agora->philo[i].died);
    }
    pthread_mutex_destroy(&agora->print);
    pthread_mutex_destroy(&agora->m_start);
    pthread_mutex_destroy(&agora->end);
    pthread_mutex_destroy(&agora->end_ph);
    free_mmr(&agora->baby, &agora->philo, 0);
}
