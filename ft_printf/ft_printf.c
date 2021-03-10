#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_flags{
	int		i;
	int		len;
	int		width;
	int		have_precision;
	int		precision;
	int		negative;
	int		zero_count;
	int		output;
	va_list	arg;
}				t_flags;

void	init_flags(t_flags *flags)
{
	flags->i = 0;
	flags->printed = 0;
}

void	clear_flags(t_flags *flags)
{
	flags->len = 0;
	flags->width = 0;
	flags->have_precision = 0;
	flags->precision = 0;
	flags->negative = 0;
	flags->zero_count = 0;
}

static void ft_putchar(char c)
{
	write(1, &c, 1);
}

static void ft_putstr_len(char *s, int max)
{
	int	i;

	i = 0;
	while (s[i] && i < max)
		ft_putchar(s[i++]);
}

static int ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static void	ft_putnbr_base(long int nbr, int base_len, char *base)
{
	if (nbr >= base_len)
		ft_putnbr_base(nbr / base_len, base_len, base);
		ft_putnbr_base(nbr % base_len, base_len, base);
	else
		ft_putchar(base[nbr]);
}

static void	ft_print_until(char *s, char c, t_flags *flags)
{
	while (s[flags->i] && s[flags->i] != c)
	{
		//putchar s[flags->i]
		//increment flags->i and output
	}
}

static int	ft_isdigit(char c)
{
}

static int	longlen_base(long nbr, int base_len)
{
	int r;

	r = 1;
	while (nbr >= base_len)
	{
		nbr /= base_len;
		r++;
	}
	return (r);
}

static void	find_flags(char *s, t_flags *flags)
{
	flags->i++;//increment as we stopped right on '%' with function print_until 
	if (ft_isdigit(s[flags->i])) //parsing minimum width param
	{
		while (ft_isdigit(s[flags->i]))
		{
			flags->width = (flags->width * 10) + (s[flags->i] - 48);
			//increment i
		}
	}
	if (s[flags->i] == '.')
	{
		flags->i++;
		flags->have_precision = 1; // made to handle specific cases
		while (ft_isdigit(s[flags->i]))
		{
			flags->precision = //same as for width
			//increment i
		}

	}
}

static void	print_x_char(int len, char c, t_flags **flags)
{
	//used to put n number of ' ' or '0' depending on width or precision
	//increase output by the number of char (**flags).output++;
}

static void	print_s(t_flags *flags)
{
	char *s;

	flags->i++;
	s = va_arg(flags->arg, char *);
	if (!s)
		s = "(null)";
	flags->len = ft_strlen(s);
	//precision only apply if it's less than string len
	if (flags->have_precision && flags->precision < flags->len)
		flags->len = flags->precision;
	//width depends on string len
	print_x_char(flags->width - flags->len, ' ', &flags);
	//printing the string more or less precision
	ft_putstr_len(s, flags->len);
	flags->output += flags->len;
}

static void	print_d(t_flags *flags)
{
	//If precision is greater than nbr len then print '0'
	//If nbr < 0, sign is put as first character if precision is applied
	//
	long nbr;

	flags->i++;
	nbr = va_arg(flags->arg, int)
	if (nbr < 0)
	{
		//to take the '-' sign into account when applying width
		flags->negative = 1;
		nbr *= -1;
	}
	flags->len = longlen_base(nbr, 10);
	// ????
	if (nbr == 0 && flags->have_precision)
		flags->len = 0;
	if (flags->have_precision && flags->precision > flags->len)
		flags->zero_count = flags->precision - flags->len;
	if (flags->negative)
		flags->len++;
	//print x number of ' ' minus the number of '0' to be printed
	print_x_char((flags->width - flags->len - flags->zero_count), ' ', &flags);
	if (flags->negative)
		ft_putchar('-');
	print_x_char(flags->zero_count, '0', &flags);
	if (flags->have_precision && nbr == 0)
		return ;
	ft_putnbr_base(nbr, 10, "0123456789");
	flags->output += flags->len;
}

static void print_x(t_flags *flags)
{
	//similar to print_d except there is no negative value
	unsigned int	nbr;

	nbr = va_arg(flags->arg, unsigned int);
	flags->len = longlen_base(nbr, 16);
	if (nbr == 0 && flags->have_precision)
		flags->len = 0;
	if (flags->have_precision && flags->precision > flags->len)
		flags->zero_count = flags->precision - flags->len;
	print_x_char(flags->width - flags->len - flags->zero_count, ' ', &flags)
	print_x_char(flags->zero_count, '0', &flags);
	if (flags->have_precision && nbr == 0)
		return ;
	ft_putnbr_base(nbr, 16, "0123456789abcdef");
	flags->output += flags->len;
}

static void	print_x(t_flags *flags)
int ft_printf(const char *fmt, ... )
{
	t_flags flags;

	init_flags(&flags);
	va_start(flags.arg, fmt);
	i = 0;
	while (fmt[flags.i])
	{
		clear_flags(&flags);
		print_until(fmt, '%', &flags);
		if (fmt[flags.i])
		{
			discover_flags(fmt, &flags);
			if (fmt[flags.i] == 's')
				print_s(&flags);
			else if (fmt[flags.i] == 'd')
				print_d(&flags);
			else if (fmt[flags.i] == 'x')
				print_x(&flags);
		}
	}
	va_end(flags.arg);
	return (flags.output);
}
