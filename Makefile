CC=gcc
# CFLAGS=-Wall -Werror -Ofast -march=native -flto -ftree-vectorize -g
CFLAGS=-Wall -Werror -g
LIBS=-lcunit

SRC_DIR=src
TEST_DIR=test
BUILD_DIR=build
TEST_BUILD_DIR=build_test
INCLUDE_HEADERS_DIRECTORY=-Iheaders

SOURCES=$(wildcard $(SRC_DIR)/*.c)
OBJECTS=$(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TEST_SOURCES=$(wildcard $(TEST_DIR)/*.c)
TESTS=$(TEST_SOURCES:$(TEST_DIR)/%.c=$(TEST_BUILD_DIR)/%)

TARGET=kmeans

all: $(TARGET)

$(TARGET): main.c $(OBJECTS)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ -c $<

$(TEST_BUILD_DIR)/%: $(TEST_DIR)/%.c $(OBJECTS)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

# Replace with: kmeans $(TESTS) when every test compiles
tests: kmeans build_test/closest_centroids_test build_test/distance_test
	echo -e "-- \n\033[1;32mUNIT TESTS\033[0m" --; \
	for test in $(TEST_BUILD_DIR)/*; do \
	    echo -e "\n\033[1;32mRunning $$test:\033[0m"; \
		$$test; \
	done

	echo -e "-- \n\033[1;32mMEMORY TEST\033[0m" --; \
	valgrind ./kmeans


clean:
	rm -rf $(BUILD_DIR)
	rm -rf $(TEST_BUILD_DIR)
	rm -f $(TARGET)

.PHONY: all clean tests