CFLAGS = -Wall -Wextra -O2

SRC = lag.c

all: $(SRC)
	cc $(CFLAGS) $(SRC) -o lag_interpolate

debug: $(SRC)
	cc $(CFLAGS) -DDEBUG -g $(SRC) -o lag_interpolate

.PHONY clean:
clean:
	rm -f lag_interpolate
