/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomes <egomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:26:22 by egomes            #+#    #+#             */
/*   Updated: 2021/11/05 09:12:31 by egomes           ###   ########.fr       */
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
		i++;
	}
}

void	exit_function(t_obj *obj)
{
	int	i;

	printf("%d\n", obj->arg.philos);
	i = -1;
	while (++i < obj->arg.philos)
		pthread_join(obj->philo[i].thread_id, NULL);
	i = -1;
	while (++i < obj->arg.philos)
		pthread_mutex_destroy(&(obj->arg.forks[i]));
	pthread_mutex_destroy(&(obj->arg.writing));
}
