/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomes <egomes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:57:24 by egomes            #+#    #+#             */
/*   Updated: 2021/11/09 21:14:34 by egomes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error(char *str)
{
	printf("Error : %s\n", str);
	return (0);
}

int	arg_validation(char **av, int i, int j)
{
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		if (j == 1 && av[i][0] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	init_philo(t_obj *obj, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error("Arguments Numbers"));
	if (arg_validation(av, 1, 0))
		return (error("Only Positive Numbers are Accepted. Starts by '1'"));
	obj->arg.philos = ft_atoi(av[1]);
	obj->arg.die = ft_atoi(av[2]);
	obj->arg.eat = ft_atoi(av[3]);
	obj->arg.sleep = ft_atoi(av[4]);
	obj->arg.nb_eat = -1;
	if (ac == 6)
		obj->arg.nb_eat = ft_atoi(av[5]);
	if (obj->arg.philos > 250 || obj->arg.die <= 0
		|| obj->arg.eat <= 0 || obj->arg.sleep <= 0
		|| obj->arg.nb_eat < -1)
		return (error("Arguments Numbers"));
	return (1);
}
