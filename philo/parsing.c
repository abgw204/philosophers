#include "philo.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	atoi2(const char *str)
{
	long	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!(*str >= '0' && *str <= '9'))
	{
		if (*str == '-')
			sign = -1;
		else if (*str != '+')
			simulation_error(1);
		str++;
	}
	while (*str)
    	{
        	if (!ft_isdigit(*str))
            		break ;
		res = res * 10 + (*str++ - 48);
    	}
    	if ((res * sign) > 2147483647 || (res * sign) < 0)
		simulation_error(1);
	return (res * sign);
}

void	parse_input(t_table *table, char **av)
{
	table->philo_nbr = atoi2(av[1]);
	table->time_to_die = atoi2(av[2]) * 1e3;
	table->time_to_eat = atoi2(av[3]) * 1e3;
	table->time_to_sleep = atoi2(av[4]) * 1e3;
	if (av[5])
		table->meals_limit = atoi2(av[5]);
	else
		table->meals_limit = -1;
}
