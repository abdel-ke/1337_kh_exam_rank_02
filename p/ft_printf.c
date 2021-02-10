#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int ft_intlen(unsigned int n, int base)
{
	int i;

	i = 1;
	while (n / base != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

int ft_putnbr(unsigned int n, int base)
{
	char str[12];
	int i;

	if (n == 0)
	{
		write(1,"0",1);
		return (0);
	}
	i = 0;
	while (n != 0)
	{
		str[i] = n % base > 9 ? n % base + 87 : n % base + 48;
		n = n / base;
		i++;
	}
	while (i > 0)
	{
		i--;
		write(1,str + i,1);
	}
	return (0);
}

int ft_print_s(char *str, int width, int precision)
{
	int i;
	int min;
	int len;

	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	min = precision < 0 ? len : ft_min(len, precision);

	i = 0;
	while (i < width - min)
	{
		write(1," ",1);
		i++;
	}
	write(1,str,min);
	return (i + min);
}

int ft_print_d(int n, int width, int precision)
{
	int i;
	int max;
	int len;
	unsigned int u;

	u = n > 0 ? n : n * -1;
	len = ft_intlen(u, 10);
	max = ft_max(len, precision);
	if (n == 0 && precision == 0)
		max = 0;
	if (n < 0)
		max++;
	i = 0;
	while (i < width - max)
	{
		write(1," ",1);
		i++;
	}
	if (n < 0)
		write(1,"-",1);
	i = 0;
	while(i < precision - len)
	{
		write(1,"0",1);
		i++;
	}
	if (n != 0 || precision != 0)
		ft_putnbr(u,10);
	return (ft_max(max, width));
}

int ft_print_x(unsigned int u, int width, int precision)
{
	int i;
	int max;
	int len;

	len = ft_intlen(u, 16);
	max = ft_max(len, precision);
	if (u == 0 && precision == 0)
		max = 0;
	i = 0;
	while (i < width - max)
	{
		write(1," ",1);
		i++;
	}
	i = 0;
	while(i < precision - len)
	{
		write(1,"0",1);
		i++;
	}
	if (u != 0 || precision != 0)
		ft_putnbr(u,16);
	return (ft_max(max, width));
}

char *ft_scan_flags(char *str, int *width, int *precision)
{
	*width = 0;
	*precision = -1;

	while (*str > 47 && *str < 58)
	{
		*width = *width * 10 + *str - 48;
		str++;
	}
	if (*str == '.')
	{
		*precision = 0;
		str++;
	}
	while (*str > 47 && *str < 58)
	{
		*precision = *precision * 10 + *str - 48;
		str++;
	}
	return (str);
}

int ft_print(va_list *pa, char c, int width, int precision)
{
	if (c == 's')
		return (ft_print_s(va_arg(*pa, char*), width, precision));
	if (c == 'd')
		return (ft_print_d(va_arg(*pa, int), width, precision));
	if (c == 'x')
		return (ft_print_x(va_arg(*pa, unsigned int), width, precision));
	return (0);
}

int ft_printf(const char *str, ...)
{
	int i;
	int width;
	int precision;
	va_list pa;

	va_start(pa, str);
	i = 0;
	while (*str != '\0')
	{
		while (*str == '%')
		{
			str = ft_scan_flags((char*)++str, &width, &precision);
			i += ft_print(&pa, *str, width, precision);
			if (*str == 's' || *str == 'd' || *str == 'x')
				str++;
		}
		if (*str != '\0')
		{
			write(1,str++,1);
			i++;
		}
	}
	va_end(pa);
	return (i);
}

int main()
{
	int x, y;
	x =    printf("|%5|\n");
	y = ft_printf("|%5|\n");
	printf("|%d|\t|%d|\n", x, y);
}