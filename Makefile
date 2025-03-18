CFLAGS = -Wall -Wextra -O2

SRC = lag.c
lag_interpolate:
	cc $(CFLAGS) $(SRC) -o lag_interpolate

clean:
	rm -f lag_interpolate