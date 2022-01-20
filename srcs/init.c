/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:06:21 by user42            #+#    #+#             */
/*   Updated: 2022/01/20 15:54:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

int	init_info(t_philo *philo, int argc, char **argv)
{
	if (argc > 6 || argc < 5)
		return (ft_error("Error: not enought or too much arguments\n"));
	philo->info.nb_total = ft_atoi(argv[1]);
	if (philo->info.nb_total <= 0)
		return (ft_error("Error: bad argument: nb_total\n"));
	philo->info.time_to_die = ft_atoi(argv[2]);
	if (philo->info.time_to_die <= 0)
		return (ft_error("Error: bad argument: time_to_die\n"));
	philo->info.time_to_eat = ft_atoi(argv[3]);
	if (philo->info.time_to_eat <= 0)
		return (ft_error("Error: bad argument: time_to_eat\n"));
	philo->info.time_to_sleep = ft_atoi(argv[4]);
	if (philo->info.time_to_sleep <= 0)
		return (ft_error("Error: bad argument: time_to_sleep\n"));
	if (argc == 6)
	{
		philo->info.must_eat = ft_atoi(argv[5]);
		if (philo->info.must_eat <= 0)
			return (ft_error("Error: bad argument: must_eat\n"));
	}
	return (0);
}

int	init_philo(t_philo *philo)
{
	int		i;

	i = 0;
	philo->info.start_t = get_time();
	philo->info.dead = 0;
	philo->info.nb_finish = 0;
	while (i < philo->info.nb_total)
	{
		philo->thread[i].id = i + 1;
		philo->thread[i].ms_eat = philo->info.start_t;
		philo->thread[i].nb_eat = 0;
		philo->thread[i].end = 0;
		philo->thread[i].r_fork = NULL;
		if (pthread_mutex_init(&philo->thread[i].l_fork, NULL) == -1)
			return (ft_error("ERROR: mutex_init returned -1\n"));
		if (philo->info.nb_total == 1)
			return (1);
		if (i == philo->info.nb_total - 1)
			philo->thread[i].r_fork = &philo->thread[0].l_fork;
		else
			philo->thread[i].r_fork = &philo->thread[i + 1].l_fork;
		i++;
	}
	return (1);
}

int	init_thread(t_philo *philo)
{
	int		i;

	i = 0;
	pthread_mutex_init(&philo->info.end, NULL);
	pthread_mutex_init(&philo->info.eat_time, NULL);
	pthread_mutex_init(&philo->info.finish, NULL);
	pthread_mutex_init(&philo->info.write_mutex, NULL);
	while (i < philo->info.nb_total)
	{
		philo->thread[i].p_info = &philo->info;
		if (pthread_create(&philo->thread[i].thread_id,
				NULL, &thread, &philo->thread[i]) != 0)
			return (ft_error("ERROR: pthread_create != 0\n"));
		i++;
	}
	return (1);
}
