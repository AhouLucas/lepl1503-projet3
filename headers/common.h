#ifndef COMMON_H
#define COMMON_H

// Fix pthread vscode error
#ifndef __USE_XOPEN2K
#define __USE_XOPEN2K
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <stdbool.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>
#include "portable_semaphore.h"
#include "portable_endian.h"
#include <pthread.h>

#endif // COMMON_H