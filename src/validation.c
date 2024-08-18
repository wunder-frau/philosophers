#include "philo.h"

t_actions	create_actions(void)
{
	t_actions	actions;

	actions.taken_fork = "has taken a fork\n";
	actions.died = "has died\n";
	actions.sleeping = "is sleeping\n";
	actions.eating = "is eating\n";
	actions.thinking = "is thinking\n";
	return (actions);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static long	str_to_long_if_numeric(char *str)
{
	long	len;
	char	*original_str;

	len = ft_strlen(str);
	if (len > 8)
	{
		ft_putstr_fd("Error: Number must have no more than 8 digits.\n", 2);
		exit(1);
	}
	original_str = str;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
		{
			ft_putstr_fd("Error: Non-numeric of negative character found.\n", 2);
			exit(1);
		}
		str++;
	}
	return (ft_atol(original_str));
}

bool	is_args_valid(int argc, char **argv, t_table *table)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: %s number_of_philosophers "
			"time_to_die time_to_eat time_to_sleep\n", 2);
		exit(1);
	}
	table->size = str_to_long_if_numeric(argv[1]);
	table->timing.die = (t_time)str_to_long_if_numeric(argv[2]);
	table->timing.eat = (t_time)str_to_long_if_numeric(argv[3]);
	table->timing.sleep = (t_time)str_to_long_if_numeric(argv[4]);
	if (argc == 6)
		table->meal_count = str_to_long_if_numeric(argv[5]);
	else
		table->meal_count = -1;
	set_action_gap(&table->timing);
	return (true);
}
