#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool requestString(char**, long*);
bool isPunctuationChar(char);
bool isEndPunctuationChar(char);
bool extendString(char*, long*, int);
void shiftString(char*, long, int);

int main() {
  long length = 0;
  char *string = NULL;
  system("clear");

  requestString(&string, &length);

  system("clear");
  printf("\n\nLength: %ld\nString: \n'%s'\n", length, string);

  for (long i = 0; i < length - 1; i++) {
    if (isPunctuationChar(string[i]) && string[i + 1] != ' ') {
      if(!extendString(string, &length, 1)) {
        printf("Please, go to hell.\n");
        break;
      }
      shiftString(string, length, i + 1);
      string[i + 1] = ' ';
    }
    if (isEndPunctuationChar(string[i]) &&
        i + 2 < length &&
        string[i + 1] == ' ' &&
        string[i + 2] >= 'a' &&
        string[i + 2] <= 'z') {
      string[i + 2] = string[i + 2] + ('A' - 'a');
    }
  }
  printf("\nNew length: %ld\nNew string:\n'%s'\n", length, string);
  getchar();
  return 0;
}

void shiftString(char *stringPtr, long length, int fromPos) {
  for (long i = length - 2; i >= fromPos; i--) {
      stringPtr[i + 1] = stringPtr[i];
  }
}

bool extendString(char *stringPtr, long *lengthPtr, int step) {
  (*lengthPtr) = (*lengthPtr) + step;
  return (stringPtr = (char*) realloc(stringPtr, (*lengthPtr + step) * sizeof(char))) != NULL;
}

bool isEndPunctuationChar(char c) {
  return c == '.' || c == '!' || c == '?';
}

bool isPunctuationChar(char c) {
  return c == ',' || c == ':' || c == ';' || isEndPunctuationChar(c);
}

bool requestString(char **stringPtr, long *lengthPtr) {
  int lengthStep = 64;
  (*stringPtr) = realloc(*stringPtr, lengthStep * sizeof(char));
  int length = lengthStep;
  printf("Enter string: \n> ");
  if ((*stringPtr) == NULL) {
    return false;
  }
  int key = EOF;
  int i = 0;
  while ((key = getchar()) != '\n' && key != EOF) {
    (*stringPtr)[i++] = key;
    if (i == length) {
      length = i + lengthStep;
      (*stringPtr) = (char*) realloc(*stringPtr, length);
    }
  }
  (*stringPtr)[i] = '\0';
  *lengthPtr = i + 1;
  return true;
}