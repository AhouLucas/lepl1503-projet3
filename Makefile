CC=gcc
CFLAGS=-Wall -Werror -flto -g -std=gnu99
LIBS=-lcunit -lpthread

SRC_DIR=src
TEST_DIR=test
BUILD_DIR=build
TEST_BUILD_DIR=build_test
INCLUDE_HEADERS_DIRECTORY=-Iheaders

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_SOURCES=$(wildcard $(TEST_DIR)/*.c)
TESTS=$(TEST_SOURCES:$(TEST_DIR)/%.c=$(TEST_BUILD_DIR)/%.bin)

TARGET=kmeans

all: $(TARGET)

$(TARGET): main.c $(OBJECTS)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

$(TEST_BUILD_DIR)/%.bin: $(TEST_DIR)/%.c $(OBJECTS)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

tests: kmeans #$(TESTS)
	@set -e; \
	# echo -e "\n[UNIT TESTS]"; \
	# for test in $(TEST_BUILD_DIR)/*.bin; do \
	#     echo -e "\n=> RUNNING $$test:"; \
	# 	$$test; \
	# done; \
	echo -e "\n[MEMORY ANALYSIS]\n"; \
	valgrind --error-exitcode=1 --leak-check=full ./kmeans -k 3 -p 5 ./scripts/exemple.bin -f output-temp-c.csv; \
	echo -e "\n[STATIC ANALYSIS]\n"; \
	cppcheck --enable=all --error-exitcode=1 --suppress=missingIncludeSystem --suppress=unknownMacro .; \
	echo -e "\n[PYTHON COMPATIBILITY]\n"; \
	/bin/env python3 scripts/k-means.py -k 3 -p 5 ./scripts/exemple.bin -f output-temp-py.csv; \
	/bin/env python3 scripts/compare_solutions.py output-temp-py.csv output-temp-c.csv; \

	@rm output-temp-py.csv;
	@rm output-temp-c.csv;
	@rm temp.csv;

clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TEST_BUILD_DIR)
	rm -f $(TARGET)

.PHONY: all clean tests