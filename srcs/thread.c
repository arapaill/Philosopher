/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arapaill <arapaill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:59:48 by user42            #+#    #+#             */
/*   Updated: 2022/01/31 12:38:43 by arapaill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void	ft_end_nxt(t_thread *thread)
{
	pthread_mutex_lock(&thread->p_info->nb_eat_mutex);
	if ((int)thread->nb_eat == thread->p_info->must_eat)
	{
		pthread_mutex_unlock(&thread->p_info->nb_eat_mutex);
		thread->end = 1;
		check_death(thread, 2);
		return ;
	}
	pthread_mutex_unlock(&thread->p_info->nb_eat_mutex);
}

void	ft_end(t_philo *philo)
{
	int				i;

	i = 0;
	while (!check_death_info(&philo->info) && i < philo->info.nb_total)
	{
		pthread_mutex_lock(&philo->info.eat_time);
		if (!check_death_info(&philo->info) && !philo->thread[i].end
			&& (get_time() - philo->thread[i].ms_eat)
			>= (long)(philo->info.time_to_die))
		{
			pthread_mutex_unlock(&philo->info.eat_time);
			display_message("died\n", philo->thread);
			check_death(&philo->thread[i], 1);
		}
		pthread_mutex_unlock(&philo->info.eat_time);
		if (philo->info.must_eat)
			ft_end_nxt(&philo->thread[i]);
		if (++i == philo->info.nb_total)
			i = 0;
	}
}

void	*thread(void *data)
{
	t_thread	*thread;

	thread = (t_thread *)data;
	if (thread->id % 2 == 0)
		ft_usleep(10, thread->p_info);
	routine(thread);
	return (NULL);
}
