#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
int width, prc, count;
char type;
void	ft_putchar(char c)
{
	write(1, &c, 1);
	count++;
}
char	*ft_atoi(char *s, int *rtn)
{
	while (*s >= '0' && *s <= '9')
	{
		*rtn = *rtn * 10 + (*s - '0');
		s++;
	}
	return s;
}
char	*get_type(char *s)
{
	width = 0;
	prc = -1;
    if (*s)
	s = ft_atoi(s, &width);
	if (*s && *s == '.')
	{
		prc = 0;
		s = ft_atoi(s + 1, &prc);
	}
	return s;
}
int     length(unsigned int d, int base)
{
	int len = 1;
	while ((d /= base))
        len++;
	return len;
}
void	ft_putnbr_x(unsigned int nbr)
{
	if (nbr < 10)
		ft_putchar(nbr + '0');
    else
    {
        if (nbr < 16)
		    ft_putchar(nbr + 'W');
        else
        {
            ft_putnbr_x(nbr / 16);
            ft_putnbr_x(nbr % 16);
        }
    }
}
void	ft_putnbr_d(unsigned int nbr)
{
	if (nbr < 10)
		ft_putchar(nbr + '0');
    else
    {
        ft_putnbr_d(nbr / 10);
        ft_putnbr_d(nbr % 10);
    }
}
void	print_d(va_list pa)
{
	int dd = va_arg(pa, int);
	unsigned int d;
	int max;
	int len;

	d = dd > 0 ? dd : -dd;
	len = length(d, 10);
    // printf("|%d|\n", len); exit(0);
	max = len > prc ? len : prc;
	if (dd == 0 && prc == 0)
		max = 0;
	if (dd < 0)
		max++;
	int i = -1;
	while (++i < width - max)
		ft_putchar(' ');
	if (dd < 0)
		ft_putchar('-');
	i = -1;
	while (++i < prc - len)
		ft_putchar('0');
	if (dd != 0 || prc != 0)
		ft_putnbr_d(d);
}
void    print_x(va_list pa)
{
    unsigned int x = va_arg(pa, unsigned int);
    int len = length(x, 16),
        max = len > prc ? len : prc;
    if (x == 0 && prc == 0)
        max = 0;
    int i = -1;
    while (++i < width - max)
        ft_putchar(' ');
    i = -1;
    while (++i < prc - len)
        ft_putchar('0');
    if (x != 0 || prc != 0)
        ft_putnbr_x(x);
}
void    print_s(va_list pa)
{
    char *s = va_arg(pa, char*);
    if (s == NULL)
        s = "(null)";
    int len = -1, min;
    while (s[++len]);
    min = prc < 0 ? len : len < prc ? len : prc;
    int i = -1;
    while (++i < width - min)
        ft_putchar(' ');
    write(1, s, min);
    count += min;
}
int     ft_printf(const char *s, ...)
{
	count = 0;
	va_list pa;
	va_start(pa, s);
    int i = 0;
	while (*s)
	{
		if (*s != '%')
            ft_putchar(*s);
		else
		{
			s = get_type((char*)s + 1);
			if (*s == 'd')
				print_d(pa);
			if (*s == 'x')
                print_x(pa);
			if (*s == 's')
				print_s(pa);
            if (*s != 's' && *s != 'd' && *s != 'x')
                s--;
		}
        if (*s != 's' || *s != 'd' || *s != 'x')
		s++;
	}
    va_end(pa);
	return count;
}