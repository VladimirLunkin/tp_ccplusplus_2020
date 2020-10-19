#include <stdio.h>
#include "test.h"  // NOLINT

int main(int argc, char *argv[]) {
    printf("%s\n%d\n", "hello", test(2));
    return 0;
}
