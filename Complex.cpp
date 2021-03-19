#include <iostream>
#include <stdio.h>
class complex
{
public:

	complex(int RE = 0, int IM = 0)
	{
		re = RE;
		im = IM;
	}

	void setComplex(float RE, float IM)
	{
		re = RE;
		im = IM;
	}

	void setRe(float RE)
	{
		re = RE;
	}

	void setIm(float IM)
	{
		im = IM;
	}

	void getComplex(float& RE, float& IM)
	{
		RE = re;
		IM = im;
	}

	float getRe()
	{
		return re;
	}

	float getIm()
	{
		return im;
	}

	bool operator == (complex& obj)
	{
		if ((re == obj.re) && (im == obj.im))
			return true;
		return false;
	}

	complex operator + (complex y)
	{
		if (!chekSUM(re, y.re) && !chekSUM(im, y.im))
			throw 5;

		complex rez;

		rez.re = y.re + re;
		rez.im = y.im + im;

		return rez;
	}

	complex operator - (complex y)
	{
		if (!chekSUB(re, y.re) && !chekSUB(im, y.im))
			throw 5;

		complex rez;

		rez.re = re - y.re;
		rez.im = im - y.im;

		return rez;
	}

	complex operator * (complex y)
	{
		if (!chekMULT(re, y.re) && !chekMULT(im, y.im) && !chekMULT(re, y.im) && !chekMULT(im, y.re))
			throw 5;

		float z1 = re * y.re, z2 = im * y.im, z3 = re * y.im, z4 = im * y.re;

		if (!chekSUB(z1, z2) && !chekSUM(z3, z4))
			throw 5;

		complex rez;

		rez.re = z1 - z2;
		rez.im = z3 + z4;

		return rez;
	}

	complex operator / (complex y)
	{
		if (!y.re && !y.im)
			throw 0;

		if (!chekMULT(re, y.re) && !chekMULT(im, y.im) && !chekMULT(re, y.im) && !chekMULT(im, y.re) && !chekMULT(y.re, y.re) && !chekMULT(y.im, y.im))
			throw 5;

		float z1 = re * y.re, z2 = im * y.im, z3 = im * y.re, z4 = re * y.im, m1 = y.re * y.re, m2 = y.im * y.im;

		if (!chekSUM(z1, z2) && !chekSUB(z3, z4) && !chekSUM(m1, m2))
			throw 5;

		float x1 = z1 + z2, x2 = z3 - z4, x3 = m1 + m2;

		if (!chekDEV(x1, x3) && !chekDEV(x2, x3))
			throw 5;

		complex rez;

		rez.re = x1 / x3;
		rez.im = x2 / x3;

		return rez;
	}

	friend std::istream& operator >> (std::istream& in, complex& x);
	friend std::ostream& operator << (std::ostream& out, complex& y);

private:

	bool chekSUM(float x, float y)
	{
		if (x + y == INFINITY || x + y == -INFINITY)
			return false;
		return true;
	}

	bool chekSUB(float x, float y)
	{
		if (x - y == INFINITY || x - y == -INFINITY)
			return false;
		return true;
	}

	bool chekMULT(float x, float y)
	{
		if (x * y == INFINITY || x * y == -INFINITY)
			return false;
		return true;
	}

	bool chekDEV(float x, float y)
	{
		if (x / y == INFINITY || x / y == -INFINITY)
			return false;
		return true;
	}

	float re;
	float im;

};

std::istream& operator >> (std::istream& in, complex& x)
{
	char a;
	bool negative = false;
	in.get(a);

	for (; a == ' '; in.get(a));

	if (a == '\n')
		throw 1;
	if (a == '-')
	{
		negative = true;
		in.get(a);

		for (; a == ' '; in.get(a));

		if (a == '\n')
			throw 1;
	}

	for (; a > 47 && a < 58; in.get(a))
	{
		if ((x.re = x.re * 10 + (a - 48)) == INFINITY)
			throw 1;
	}
	if (negative)
	{
		x.re = x.re * (-1);
		negative = false;
	}

	for (; a == ' '; in.get(a));

	if (a == '\n')
	{
		x.im = 0;
		return in;
	}
	if (a == '-' || a == '+')
	{
		if (a == '-')
			negative = true;
		in.get(a);
		for (; a == ' '; in.get(a));

		if (a == '\n')
			throw 1;

		for (; a > 47 && a < 58; in.get(a))
		{
			if ((x.im = x.im * 10 + (a - 48)) == INFINITY)
				throw 1;
		}
		if (negative)
		{
			x.im = x.im * (-1);
			negative = false;
		}

		for (; a == ' '; in.get(a));

		if (a == '\n')
			throw 1;
		if (a == 'i')
		{
			for (; a != '\n'; in.get(a));
			return in;
		}
	}

	throw 1;
}

std::ostream& operator << (std::ostream& out, complex& x)
{

	out << x.re << " + (" << x.im << "i)\n";

	return out;
}


void main()
{
	complex a, b, c;

	try
	{
		std::cin >> a >> b;
		c = a + b;

		std::cout << c;
		c = a / b;
		std::cout << c;

	}
	catch (int i)
	{
		switch (i)
		{
		case 0:
			printf_s("error: %d dividing\n", i);
			break;
		case 1:
			printf_s("wrong input\n");
			break;
		case 5:
			printf_s("overflow");
			break;
		}
	}
}