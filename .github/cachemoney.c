#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#define CACHE_SIZE 1500

static char *cache[CACHE_SIZE];

const char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
const char *teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
const char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
const char *hundred = "hundred";
const char *thousand = "thousand";
const char *million = "million";
const char *billion = "billion";

void convert_hundreds(long long num, char *buffer) {
    if (num >= 100) {
        strcat(buffer, ones[num / 100]);
        strcat(buffer, " ");
        strcat(buffer, hundred);
        if (num % 100 != 0) strcat(buffer, " ");
    }
    num %= 100;
    if (num >= 20) {
        strcat(buffer, tens[num / 10]);
        if (num % 10 != 0) {
            strcat(buffer, "-");
            strcat(buffer, ones[num % 10]);
        }
    } else if (num >= 10) {
        strcat(buffer, teens[num - 10]);
    } else if (num > 0) {
        strcat(buffer, ones[num]);
    }
}

char *money_to_text(long long cents) {
    if (cents < 0) return "negative values not supported";
    
    if (cents < CACHE_SIZE && cache[cents]) {
        return cache[cents];
    }
    
    int dollars = cents / 100;
    int remaining_cents = cents % 100;
    char *result = (char *)malloc(1024);
    result[0] = '\0';
    
    if (dollars >= 1000000000) {
        convert_hundreds(dollars / 1000000000, result);
        strcat(result, " ");
        strcat(result, billion);
        strcat(result, " ");
        dollars %= 1000000000;
    }
    if (dollars >= 1000000) {
        convert_hundreds(dollars / 1000000, result);
        strcat(result, " ");
        strcat(result, million);
        strcat(result, " ");
        dollars %= 1000000;
    }
    if (dollars >= 1000) {
        convert_hundreds(dollars / 1000, result);
        strcat(result, " ");
        strcat(result, thousand);
        strcat(result, " ");
        dollars %= 1000;
    }
    if (dollars > 0) { 
        convert_hundreds(dollars, result); 
    }
    
    if (dollars == 1) {
        strcat(result, " dollar and ");
    } else if (dollars == 0){
        strcat(result, "zero dollars and ");
    } else {
        strcat(result, " dollars and ");
    }
    
    if (remaining_cents == 0) {
        strcat(result, "zero cents");
    } else {
        convert_hundreds(remaining_cents, result);
        if (remaining_cents == 1) {
            strcat(result, " cent");
        } else {
            strcat(result, " cents");
        }
    }
    
    if (cents < CACHE_SIZE) {
        cache[cents] = strdup(result);
    }
    
    return result;
}


int main(void) {
    long long cents;
    while (scanf("%lld", &cents) == 1) {
        char *text = money_to_text(cents);
        printf("%s\n", text);
        // Free the memory if it wasn't cached.
        if (cents >= CACHE_SIZE)
            free(text);
    }
    return 0;
}
