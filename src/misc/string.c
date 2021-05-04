#include <printf.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

inline void *memset(void *b, int c, size_t len) {
  unsigned char *p = b;

  // Fast memset. We do not use this trick on very
  // small stuff because it is not worth it :')
  if(len > sizeof(uintptr_t) * 4) {
    size_t flen = len / sizeof(uintptr_t);
    len %= sizeof(uintptr_t);

    // Compose a "big" integer to copy as-is
    uintptr_t fast_c = 0;
    for (size_t i = 0; i < sizeof(uintptr_t); i++) {
      fast_c |= c & 0xff;
      fast_c <<= 8;
    }

    uintptr_t * fp = (uintptr_t *)p;
    while (flen > 0) {
      *fp = fast_c;
      fp++;
      flen--;
    }
  }

  while (len > 0) {
    *p = c;
    p++;
    len--;
  }
  return (b);
}

inline void memcpy(void *dest, void *src, size_t n) {
  // Typecast src and dest addresses to (char *)
  char *csrc = (char *)src;
  char *cdest = (char *)dest;

  // We use a very fast copy-paste onto the dest to speed things up
  uintptr_t * fast_src = (uintptr_t *)src;
  uintptr_t * fast_dest = (uintptr_t *)dest;

  size_t i = n / sizeof(uintptr_t);
  while (i != 0) {
    *fast_dest = *fast_src;
    fast_dest++;
    fast_src++;
  }

  // Remainder is copied as-bytes
  size_t j = n % sizeof(uintptr_t);
  while (j != 0) {
    *cdest = *csrc;
    cdest++;
    csrc++;
  }
}

inline unsigned int strlen(const char *s) {
  unsigned int count = 0;
  while (*s != '\0') {
    count++;
    s++;
  }
  return count;
}

inline char *strcat(char *s1, const char *s2) {
  // Pointer should not null pointer
  if ((s1 == NULL) && (s2 == NULL))
    return NULL;
  // Create copy of s1
  char *start = s1;
  // Find the end of the destination string
  while (*start != '\0') {
    start++;
  }
  // Now append the source string characters
  // until not get null character of s2
  while (*s2 != '\0') {
    *start++ = *s2++;
  }
  // Append null character in the last
  *start = '\0';
  return s1;
}

inline char *strcpy(char *destination, const char *source) {
  if (destination == NULL)
    return NULL;

  char *ptr = destination;

  while (*source != '\0') {
    *destination = *source;
    destination++;
    source++;
  }

  *destination = '\0';

  return ptr;
}

inline int atoi(char *str) {
  int res = 0;

  for (int i = 0; str[i] != '\0'; ++i) {
    res = res * 10 + str[i] - '0';
  }

  return res;
}

char *itoa(int value, char *str, size_t base) {
  char *rc;
  char *ptr;
  char *low;
  // Check for supported base.
  if (base < 2 || base > 36) {
    *str = '\0';
    return str;
  }
  rc = ptr = str;
  // Set '-' for negative decimals.
  if (value < 0 && base == 10) {
    *ptr++ = '-';
  }
  // Remember where the numbers start.
  low = ptr;
  // The actual conversion.
  do {
    // Modulo is negative for negative value. This trick makes abs()
    // unnecessary.
    *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrst"
             "uvwxyz"[35 + value % base];
    value /= base;
  } while (value);
  // Terminating the string.
  *ptr-- = '\0';
  // Invert the numbers.
  while (low < ptr) {
    char tmp = *low;
    *low++ = *ptr;
    *ptr-- = tmp;
  }
  return rc;
}

inline int strcmp(const char *input, const char *check) {
  for (int i = 0; input[i] && check[i]; i++) {
    if (input[i] != check[i])
      return 0;
  }
  return 1;
}

// Custom function. Count amount of whitespace in a string
inline int wspaceamount(char *a) {
  int i = 0, count = 0;

  while (a[i] != '\0') {
    if (a[i] == ' ') {
      count++;
    }
    i++;
  }

  return count;
}

inline int isdigit(int c) {
  if (c >= '0' && c <= '9')
    return c;
  else
    return 0;
}

float atof(const char *s) {
  float rez = 0, fact = 1;
  if (*s == '-') {
    s++;
    fact = -1;
  }
  for (int point_seen = 0; *s; s++) {
    if (*s == '.') {
      point_seen = 1;
      continue;
    }
    int d = *s - '0';
    if (d >= 0 && d <= 9) {
      if (point_seen)
        fact /= 10.0f;
      rez = rez * 10.0f + (float)d;
    }
  }
  return rez * fact;
}

uint64_t str_to_u64(const char *str) {
  uint64_t val = 0;
  size_t i, j;

  for (i = 0, j = strlen(str); i < j; i++) {
    if (i >= 8)
      break; // Limit to 8 characters

    uint8_t c = str[i];
    if (c <= 0x20)
      c = 0x00; // Also include spaces

    val |= (c << (i << 3));
  }

  return val;
}
