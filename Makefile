CFLAGS = -Wall -Wextra -O2

lagrange_interpolate:
	cc $(CFLAGS) lag.c lagrange_interpolate

clean:
	rm -f lagrange_interpolate