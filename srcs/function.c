/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomes <egomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 15:58:38 by egomes            #+#    #+#             */
/*   Updated: 2021/11/18 17:45:16 by egomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_eats(t_philo *philo)
{
	t_arg	*arg;

	arg = philo->arg;
	pthread_mutex_lock(&(arg->forks[philo->l_f]));
	print(arg, philo->id, "has taken a fork");
	pthread_mutex_lock(&(arg->forks[philo->r_f]));
	print(arg, philo->id, "has taken a fork");
	pthread_mutex_lock(&(arg->meal_check));
	print(arg, philo->id, "is eating");
	philo->last_meal = actual_time();
	pthread_mutex_unlock(&(arg->meal_check));
	smart_sleep(arg->eat, arg);
	(philo->x_eat)++;
	pthread_mutex_unlock(&(arg->forks[philo->l_f]));
	pthread_mutex_unlock(&(arg->forks[philo->r_f]));
}

void	*thread(void	*p)
{
	t_philo		*philo;
	t_arg		*arg;
	int			i;

	philo = (t_philo *)p;
	arg = philo->arg;
	if (philo->id % 2)
		usleep(15000);
	i = 0;
	while (!(arg->dieded))
	{
		philo_eats(philo);
		if (arg->all_eat)
			break ;
		print(arg, philo->id, "is sleeping");
		smart_sleep(arg->sleep, arg);
		print(arg, philo->id, "is thinking");
		usleep(100);
		i++;
	}
	return (NULL);
}

void	init_function(t_obj *obj)
{
	int	i;

	obj->arg.first_time = actual_time();
	i = 0;
	while (i < obj->arg.philos)
	{
		pthread_create(&(obj->philo[i].thread_id),
			NULL, thread, &(obj->philo[i]));
		obj->philo[i].last_meal = actual_time();
		i++;
	}
	death_checker(obj);
	exit_function(obj);
}
