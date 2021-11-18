/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomes <egomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:26:22 by egomes            #+#    #+#             */
/*   Updated: 2021/11/18 17:43:57 by egomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_mutex(t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->arg.philos)
		pthread_mutex_init(&(obj->arg.forks[i++]), NULL);
	pthread_mutex_init(&(obj->arg.writing), NULL);
	pthread_mutex_init(&(obj->arg.meal_check), NULL);
}

void	init_philos(t_obj *obj)
{
	int	i;

	i = 0;
	while (i < obj->arg.philos)
	{
		obj->philo[i].id = i;
		obj->philo[i].l_f = i;
		obj->philo[i].r_f = (i + 1) % obj->arg.philos;
		obj->philo[i].last_meal = 0;
		obj->philo[i].arg = &obj->arg;
		obj->philo[i].x_eat = 1;
		i++;
	}
}

void	exit_function(t_obj *obj)
{
	int	i;

	i = -1;
	while (++i < obj->arg.philos)
		pthread_join(obj->philo[i].thread_id, NULL);
	i = -1;
	while (++i < obj->arg.philos)
		pthread_mutex_destroy(&(obj->arg.forks[i]));
	pthread_mutex_destroy(&(obj->arg.writing));
	pthread_mutex_destroy(&(obj->arg.meal_check));
}

void	death_checker(t_obj *obj)
{
	int	i;

	while (!(obj->arg.all_eat))
	{
		i = -1;
		while (++i < obj->arg.philos && !(obj->arg.dieded))
		{
			pthread_mutex_lock(&(obj->arg.meal_check));
			if ((actual_time() - obj->philo[i].last_meal) >= obj->arg.die)
			{
				print(&obj->arg, i, "died");
				obj->arg.dieded = 1;
			}
			pthread_mutex_unlock(&(obj->arg.meal_check));
			usleep(100);
		}
		if (obj->arg.dieded)
			break ;
		i = 0;
		while (obj->arg.nb_eat != -1 && i < obj->arg.philos
			&& obj->philo[i].x_eat >= obj->arg.nb_eat)
			i++;
		if (i == obj->arg.philos)
			obj->arg.all_eat = 1;
	}
}
