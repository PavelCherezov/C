#include "string.h"

void *my_to_upper(const char *str) {
  char *buff = 0;
  if (str != my_NULL) {
    int n = my_strlen(str);
    buff = (char *)calloc(n + 1, sizeof(char *));
    if (buff != my_NULL) {
      for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          buff[i] = str[i] - 32;
        } else
          buff[i] = str[i];
      }
      buff[n] = '\0';
    }
  }
  return buff;
}

void *my_to_lower(const char *str) {
  char *buff = 0;
  if (str != my_NULL) {
    int n = my_strlen(str);
    buff = (char *)calloc(n + 1, sizeof(char *));
    if (buff != my_NULL) {
      for (int i = 0; i < n; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          buff[i] = str[i] + 32;
        } else
          buff[i] = str[i];
      }
      buff[n] = '\0';
    }
  }
  return buff;
}

void *my_insert(const char *src, const char *str, my_size_t start_index) {
  if (!src || !str || (int)start_index < 0 || my_strlen(src) < start_index) {
    return my_NULL;
  }
  my_size_t len = my_strlen(src) + my_strlen(str);
  my_size_t s = start_index + my_strlen(str);
  my_size_t t = my_strlen(str);
  char *result = (char *)calloc(len, sizeof(char *));
  if (result != my_NULL) {
    for (my_size_t i = 0; i < len; i++) {
      if (i < start_index) {
        result[i] = src[i];
      } else if (i >= start_index && i < s) {
        result[i] = str[i - start_index];
      } else if (i >= s) {
        result[i] = src[i - t];
      }
    }
    result[len] = '\0';
  }
  return result;
}

void *my_trim(const char *src, const char *trim_chars) {
  if (!src) {
    return my_NULL;
  }

  if (!trim_chars) {
    return (void *)my_strdup(src);
  }

  char *start = (char *)src;
  char *end = (char *)src + my_strlen(src) - 1;

  while (*start && my_strchr(trim_chars, *start)) {
    start++;
  }

  while (end > start && my_strchr(trim_chars, *end)) {
    end--;
  }

  void *new_str = malloc((end - start + 2) * sizeof(char));
  if (!new_str) {
    return my_NULL;
  }

  my_memcpy(new_str, start, end - start + 1);
  ((char *)new_str)[end - start + 1] = '\0';

  return new_str;
}

char *my_strdup(const char *s) {
  char *copy = malloc(my_strlen(s) + 1);
  if (copy) {
    my_strcpy(copy, s);
  }
  return copy;
}