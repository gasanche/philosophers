/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabsanch <gabsanch@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:36:54 by gabsanch          #+#    #+#             */
/*   Updated: 2024/04/09 17:38:04 by gabsanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_agora agora;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments. Have a good day kid :D\n"));
	else
	{
		gettimeofday(&agora.start, NULL);
		if (check_argv(&agora, argv) == -1)
			return (printf("Error. Have a great day kid :D\n"));
		sleeping(100, &agora);
		pthread_mutex_unlock(&agora.m_start);
		sargent(&agora);
		dead(&agora);
	}
	return (0);
}
