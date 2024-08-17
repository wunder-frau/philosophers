#include "philo.h"
#include "limits.h"

int	ft_isdigit(int d)
{
	return (d >= '0' && d <= '9');
}

int	ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s != NULL)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

// static bool has_no_more_than_8_digits(char *str)
// {
//     int digit_count = 0;
//     while (*str)
//     {
//         if (ft_isdigit(*str))
//         {
//             digit_count++;
//      	 if (digit_count > 8)
//             {
//                 fprintf(stderr, "Error: Number must have no more than 8 digits.\n");
//                 return false; // More than 8 digits found
//             }
//         }
//         str++;
//     }
//     return true; // 8 or fewer digits
// }

long ft_atol(char *str) {
    unsigned long result = 0;
    int sign = 1;

    while (ft_is_space((unsigned char)*str)) {
        str++;
    }

    if (*str == '-' || *str == '+') {
        if (*str == '-') {
            sign = -1;
        }
        str++;
    }

    while (ft_isdigit((unsigned char)*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * (long)result;
}
// long	ft_atol(char *str)
// {
// 	unsigned long	result;
// 	int				sign;

// 	result = 0;
// 	sign = 1;
// 	while (ft_is_space(*str))
// 		str++;
// 	if ((*str == '-' || *str == '+') && ft_isdigit(*str))
// 	{
// 		if (*str == '-')
// 			sign = -1;
// 		else
// 			sign = 1;
// 		str++;
// 	}
// 	while (ft_isdigit(*str))
// 	{
// 		result = result * 10 + (*str - 48);
// 		str++;
// 	}
// 	printf("llllll_____%ld\n", (long)sign * result);
// 	return ((long)sign * result);
// }

void	*ft_calloc(size_t count, size_t size)
{
	void			*dest;
	size_t			total;

	total = -1;
	if (count != 0 && total / count < size)
		return (NULL);
	total = count * size;
	dest = malloc(total);
	if (dest == NULL)
		return (NULL);
	memset(dest, 0, total);
	return (dest);
}