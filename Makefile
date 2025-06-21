flags = -O2 -Wall -std=c2x -g
ldflags = -lreadline

all: clean bin/main bin/donut

bin/main: out/main.o out/builtins.o out/banner.o out/donut.o | bin/
	cc ${flags} $^ -o $@ ${ldflags} -lm

bin/donut: out/donut.o | bin/
	cc ${flags} $^ -o $@ -lm

out/main.o: src/main.c | out/
	cc ${flags} -c $^ -o $@

out/builtins.o: src/builtins.c | out/
	cc ${flags} -c $^ -o $@

out/banner.o: src/utils/banner.c | out/
	cc ${flags} -c $^ -o $@

out/donut.o: src/utils/donut.c | out/
	cc ${flags} -c $^ -o $@

# Individual build targets
main: bin/main

donut: bin/donut

# Run targets
run-main: bin/main
	./bin/main

run-donut: bin/donut
	./bin/donut

# Create output directories if they don't exist
out/:
	mkdir -p out

bin/:
	mkdir -p bin

clean:
	rm -f bin/main bin/donut out/*.o
	rm -rf out/ bin/