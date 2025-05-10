#include "philo_bonus.h"

char	*ft_strdup( char *s1)
{
	char	*p;
	int		size;
	int		i;

	i = 0;
	size = (int)ft_strlen(s1);
	p = malloc(size + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
char	*alloc(int j, int sign)
{
	char	*a;

	a = malloc((j + sign + 1) * sizeof(char));
	if (!a)
		return (NULL);
	return (a);
}

char	*fill(int n, int sign)
{
	char	*a;
	int		i;
	char	num[10];
	int		j;

	j = 0;
	i = 0;
	while (n > 0)
	{
		num[j++] = n % 10 + 48;
		n = n / 10;
	}
	a = alloc(j, sign);
	if (!a)
		return (NULL);
	if (sign == 1)
		a[i++] = '-';
	while (--j >= 0)
		a[i++] = num[j];
	a[i] = '\0';
	return (a);
}

char	*ft_itoa(int n)
{
	char	*a;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		n *= -1;
		a = fill(n, 1);
	}
	else
		a = fill(n, 0);
	return (a);
}