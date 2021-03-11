//include stdarg/ unistd	

typedef struct	s_flags{

	int		i;
	int		is_negative;
	int		width;
	int		precision;
	int		has_precision;
	int		count_zeros;
	int		output;
	int		len;
	va_list	arg;
}				t_flags;

void	init_flags(t_flags *flags)
{
	flags->i = 0;
	flags->output = 0;

}

void	clear_flags(t_flags *flags)
{
	flags->is_negative = 0;
	flags->precision = 0;
	flags->width = 0;
	flags->has_precision = 0;
	flags->count_zeros = 0;
	flags->len = 0;
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_till_char(char *s, char c, t_flags *flags)
{
	while (s[flags->i] && s[flags->i] != c)
	{
		ft_putchar(s[flags->i])
		flags->output++;
		flags->i++;
	}
}

void	ft_putstr_len(char *s, int len)
{
	
	while(s[i] && i < len)
		ft_putchar(s[i++]);
}

void	ft_put_x_char(int nbr, char c, t_flags *flags)
{
	while (i < nbr) //<<
		ft_putchat(c);
		flags->output++;
}

int		_nbr_len_in_base(long nbr, int b_len)
{
	int i;

	i = 1;
	while ( nbr >= base_len) // << Measuring nbr len according to its base
		(nbr /= b_len); // <<
		i++;
}

void	_putnbr_base(long nbr, int b_len, char *b)
{
	if (nbr >= b_len)
		_putnbr_base(nbr / b_len, b_len, b);
		_putnbr_base(nbr % b_len, b_len, b);
	else
		ft_putchar(b[nbr]);

}

void	print_s(t_flags *flags)
{
	char *s;

	flags->i++;
	s = va_arg(flags->arg, char *);
	if (!s) //<< null case on OSX
			s = "(null)";
	flags->len = ft_strlen(s);
	if (flags->has_precision && flags->precision < flags->len)
		flags->len = flags->precision;
	ft_put_x_char(flags->width - flags->len, ' ', &flags);
	ft_putsr_len(s, flags->len);
	output+= flags->len;
}

void	print_d(t_flags *flags)
{
	long	nbr;

	flags->i++;
	nbr = va_arg(flags->arg, int);
	if  (nbr < 0) //<<

	{
		flags->is_negative = 1;
		nbr *= -1;
	}
	flags->len = _nbr_len_in_base(nbr, 10);
	if (nbr == 0 && flags->has_precision) //<< 0 case
		flags->len = 0;
	if (flags->has_precision && flags->precision > flags->len)
		flags->count_zeros = flags->precision - flags->len;
	if (flags->is_negative)
		flags->len++;
	ft_put_x_char(flags->width - flags->count_zeros - flags->width, ' ', &flags);
	if (flags->is_negative)
		ft_putchar('-');
	ft_put_x_char(flags->count_zeros, '0', &flags);
	if (nbr == 0 && flags->has_precision)
		return ;
	_putnbr_base(nbr, 10, "0123456789");
	flags->output += flags->len;
}

void	print_x(t_flags *flags)
{
	unsigned int	hex;

	flags->i++;
	hex = va_arg(flags->arg, unsigned int *);
	flags->len = _nbr_len_in_base(nbr, 16);
	if (nbr == 0 && flags->has_precision) //<< 0 case
		flags->len = 0; //<<
	if (flags->has_precision && flags->precision > flags->len)
		flags->count_zeros = flags->precision - flags->len;
	ft_put_x_char(flags->width - flags->len - flags->count_zeros, ' ', &flags);
	ft_put_x_char(flags->count_zeros, '0', &flags);
	if (nbr == 0 && flags->has_precision)
		return ;
	_putnbr_base(nbr, 16, "0123456789abcdef");
	flags->output += flags->len;
}

void	disco_flags(t_flags *flags)
{
	flags->i++;
	while (ft_isdigit(fmt[flags->i]))
	{
		flags->width = flags->width * 10 + fmt[flags->i] - 48;
		flags->i++;
	}
	if (fmt[flags->i] = '.')
	{
		flags->has_precision = 1;
		flags->i++;
	}
	while (ft_isdigit(fmt[flags->i]))
	{
		flags->precision = flags->precision * 10 + fmt[flags->i] - 48;
		flags->i++;
	}
}

int ft_printf(const char *fmt, ... )
{
	//2 while loop
	//1st to reach % sign and print fmt
	//2nd to parse char after a % and print into the corresponding conversion
	t_flags	flags;

	init_flags(&flags); //<<
	va_start(flags.arg, fmt);
	while (fmt[flags->i])
	{
		clear_flags(&flags); //<<
		ft_putstr_till_char(fmt, '%', &flags); //<<
		while (fmt[flags->i])
		{
			disco_flags(fmt, &flags);
			if (fmt[flags->i] == 's')
				print_s(&flags);
			if (fmt[flags->i] == 'd')
				print_d(&flags);
			if (fmt[flags->i] == 'x')
				print_x(&flags);
		}
	}
	return (flags.output);
}
