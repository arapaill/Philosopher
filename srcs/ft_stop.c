/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 15:08:57 by user42            #+#    #+#             */
/*   Updated: 2022/01/20 16:35:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

int	check_death_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info.end);
	if (philo->info.dead)
	{
		pthread_mutex_unlock(&philo->info.end);
		return (1);
	}
	pthread_mutex_unlock(&philo->info.end);
	return (0);
}

void	ft_stop(t_philo *philo)
{
	int		i;

	i = -1;
	while (!check_death_philo(philo))
		ft_usleep(1, &philo->info);
	while (++i < philo->info.nb_total)
		pthread_join(philo->thread[i].thread_id, NULL);
	pthread_mutex_destroy(&philo->info.write_mutex);
	i = -1;
	while (++i < philo->info.nb_total)
		pthread_mutex_destroy(&philo->thread[i].l_fork);
	if (philo->info.dead == 2)
		printf("Every philo ate %d time\n", philo->info.must_eat);
	free(philo->thread);
}
