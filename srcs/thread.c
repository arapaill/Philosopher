/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 15:59:48 by user42            #+#    #+#             */
/*   Updated: 2022/01/27 20:37:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

void	ft_end(t_philo		*philo)
{
	int				i;

	i = 0;
	while (philo->info.dead == 0 && i < philo->info.nb_total)
	{
		if (philo->info.dead == 0 && !philo->thread[i].end
			&& (get_time() - philo->thread[i].ms_eat)
			>= (long)(philo->info.time_to_die))
		{
			display_message("died\n", philo->thread);
			philo->info.dead = 1;
		}
		i++;
		if (i == philo->info.nb_total)
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
