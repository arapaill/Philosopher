/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 09:57:51 by user42            #+#    #+#             */
/*   Updated: 2021/12/23 14:22:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_philo.h"

int		ft_error(char *msg)
{
	printf("%s", msg);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_philo  philo;

	if (init_info(&philo, argc, argv) == -1)
		return (-1);
	philo.thread = malloc(sizeof(t_thread) * philo.info.nb_total);
	if (!philo.thread)
		return (ft_error("Error: Malloc error\n"));
	if (!init_philo(&philo) || !init_thread(&philo))
	{
		free(philo.thread);
		return (-1);
	}
	return (0);
}