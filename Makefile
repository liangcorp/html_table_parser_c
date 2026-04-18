CC=clang
AR=ar

all:
	mkdir -p lib
	mkdir -p bin
	mkdir -p bin/Debug
	${CC} -Wall -Werror -Wpedantic -std=c99 -g -I ./lib/ -I ./src/include -c ./src/html_table_parser/html_table_parser.c -o ./lib/html_table_parser.o
	${CC} -Wall -Werror -Wpedantic -std=c99 -g -I ./lib/ -I ./src/include -c ./src/hashmap/hashmap.c -o ./lib/hashmap.o
	${CC} -Wall -Werror -Wpedantic -std=c99 -g -I ./lib/ -I ./src/include -c ./src/fnv_hash/fnv1a_hash.c -o ./lib/fnv1a_hash.o
	${AR} rcs ./lib/libhtml_table_parser.a ./lib/html_table_parser.o
	${AR} rcs ./lib/libhashmap.a ./lib/hashmap.o
	${AR} rcs ./lib/libfnv1a_hash.a ./lib/fnv1a_hash.o
	cd ..
	${CC} -Wall -Werror -Wpedantic -std=c99 -g -I ./lib/ -I ./src/include -I ./src/html_table_parser -I ./src/hashmap -I ./src/fnv_hash -c ./src/main.c -o ./lib/main.o
	${CC} -Wall -Werror -Wpedantic -std=c99 -g -o ./bin/Debug/html_table_parser ./lib/main.o ./lib/libhtml_table_parser.a ./lib/libhashmap.a ./lib/libfnv1a_hash.a

memory_debug:
	mkdir -p lib
	mkdir -p bin
	mkdir -p bin/Debug
	${CC} -Wall -Werror -Wpedantic -D F_MEMORY_DEBUG -std=c99 -g -I ./lib/ -I ./src/include -c ./src/html_table_parser/html_table_parser.c -o ./lib/html_table_parser.o
	${CC} -Wall -Werror -Wpedantic -D F_MEMORY_DEBUG -std=c99 -g -I ./lib/ -I ./src/include -c ./src/memory_debug/memory_debug.c -o ./lib/memory_debug.o
	${CC} -Wall -Werror -Wpedantic -D F_MEMORY_DEBUG -std=c99 -g -I ./lib/ -I ./src/include -I ./src/memory_debug -c ./src/hashmap/hashmap.c -o ./lib/hashmap.o
	${CC} -Wall -Werror -Wpedantic -D F_MEMORY_DEBUG -std=c99 -g -I ./lib/ -I ./src/include -c ./src/fnv_hash/fnv1a_hash.c -o ./lib/fnv1a_hash.o
	${AR} rcs ./lib/libhtml_table_parser.a ./lib/html_table_parser.o
	${AR} rcs ./lib/libmemory_debug.a ./lib/memory_debug.o
	${AR} rcs ./lib/libhashmap.a ./lib/hashmap.o
	${AR} rcs ./lib/libfnv1a_hash.a ./lib/fnv1a_hash.o
	cd ..
	${CC} -Wall -Werror -Wpedantic -D F_MEMORY_DEBUG -std=c99 -g -I ./lib/ -I ./src/include -I ./src/html_table_parser -I ./src/hashmap -I ./src/fnv_hash -I ./src/memory_debug -c ./src/main.c -o ./lib/main.o
	${CC} -Wall -Werror -Wpedantic -D F_MEMORY_DEBUG -std=c99 -g -o ./bin/Debug/html_table_parser ./lib/main.o ./lib/libhtml_table_parser.a ./lib/libhashmap.a ./lib/libfnv1a_hash.a ./lib/libmemory_debug.a

release:
	mkdir -p lib
	mkdir -p bin
	mkdir -p bin/Release
	${CC} -std=c99 -I ./lib/ -I ./src/include -c ./src/html_table_parser/html_table_parser.c -o ./lib/html_table_parser.o
	${CC} -std=c99 -I ./lib/ -I ./src/include -c ./src/hashmap/hashmap.c -o ./lib/hashmap.o
	${CC} -std=c99 -I ./lib/ -I ./src/include -c ./src/fnv_hash/fnv1a_hash.c -o ./lib/fnv1a_hash.o
	${AR} rcs ./lib/libhtml_table_parser.a ./lib/html_table_parser.o
	${AR} rcs ./lib/libhashmap.a ./lib/hashmap.o
	${AR} rcs ./lib/libfnv1a_hash.a ./lib/fnv1a_hash.o
	cd ..
	${CC} -std=c99 -g -I ./lib/ -I ./src/include -I ./src/html_table_parser -I ./src/hashmap -I ./src/fnv_hash -c ./src/main.c -o ./lib/main.o
	${CC} -std=c99 -g -o ./bin/Release/html_table_parser ./lib/main.o ./lib/libhtml_table_parser.a ./lib/libhashmap.a ./lib/libfnv1a_hash.a


check:
	${CC} --version

distcheck:
	uname -a

bad_function_check:
	bash sh/bad_function_check.sh

format:
	find -name *.h -exec clang-format -i {} \;
	find -name *.c -exec clang-format -i {} \;

clean:
	rm -rf ./bin
	rm -rf ./lib
