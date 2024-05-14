#include <stdio.h>
#include <stdlib.h>

int main() {
    char *value = getenv("USERsfdR");
    if (value != NULL) {
        printf("The value of HOME is: %s\n", value);
    } else {
        printf("HOME environment variable is not set.\n");
    }
    return 0;
}
