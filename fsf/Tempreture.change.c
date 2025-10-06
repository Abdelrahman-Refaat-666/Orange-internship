#include <stdio.h>
#include <stdlib.h>

int main() {
    float temp_in_f, temp_in_c;
    scanf("%f", &temp_in_f);
    temp_in_c = (temp_in_f - 32) * (5.0/9.0);
    printf("%.2f", temp_in_c);
    return 0;
}