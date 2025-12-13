int	ft_atoi(const char *nptr)
{
	int		sign;
	long	sum;

	sign = 1;
	sum = 0;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		sum = sum * 10 + (*nptr - 48);
		nptr++;
	}
	return ((int)(sum * sign));
}
