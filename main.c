/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:36:54 by gabsanch          #+#    #+#             */
/*   Updated: 2024/03/31 17:19:55 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philos	philos;
	void *ret;

	if (argc < 5 || argc > 6)
		return (write(2, "Wrong number of arguments!\n", 28));
	else
	{
		if (check_argv(&philos, argv) == -1)
			return (write(2, "Not valid arguments\n", 21));
		pthread_create(&philos.baby, NULL, thread, "thread 1");
		pthread_join(philos.baby, &ret);
	}
	return 0;
}
