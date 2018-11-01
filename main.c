#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

// Request string from user
// PS: With non-fixed size ;)
bool requestString(char**, long*);

void clearBuffer(void);

bool isPunctuationChar(char);
bool isEndPunctuationChar(char);

// Extends string (param 1) with initial length (param 2) with (param 3) elements
bool extendString(char*, long*, int);

// Shift string (param 1) items from position (param 3) with length (param 2)
void shiftString(char*, long, int);

int main() {

  // Initializating necessary variables
  long length = 0;
  char *string = NULL;

  // Just clear the screen
  system(CLEAR_CMD);

  requestString(&string, &length);
  
  // Just clear screen again!
  system(CLEAR_CMD);
  printf("\n\nLength: %ld\nString: \n'%s'\n", length, string);

  for (long i = 0; i < length - 1; i++) {
    
    // Check is current char in [ , . : ; ! ? ]
    // If yes AND next char is not a space extend string and shift starting from i + 1 position.
    // then set next char to space.
    if (isPunctuationChar(string[i]) && string[i + 1] != ' ') {
      if(!extendString(string, &length, 1)) {
        printf("Please, go to hell.\n");
        break;
      }
      shiftString(string, length, i + 1);
      string[i + 1] = ' ';
    }

    // Check is current char in [ ? ! . ]
    // If yes AND next char (if exists) is space (should be replaced before if necessary)
    // AND next-next char is lowercase then set it upper.
    if (isEndPunctuationChar(string[i]) &&
        i + 2 < length &&
        string[i + 1] == ' ' &&
        string[i + 2] >= 'a' &&
        string[i + 2] <= 'z') {
      string[i + 2] = string[i + 2] + ('A' - 'a');
    }
  }

  // Output new string and await for user actions.
  printf("\nNew length: %ld\nNew string:\n'%s'\n", length, string);
  getchar();
  return 0;
}

void shiftString(char *stringPtr, long length, int fromPos) {
  for (long i = length - 2; i >= fromPos; i--) {
      stringPtr[i + 1] = stringPtr[i];
  }
}

// We need MORE pointers
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

// Some sort of dark magic... no, gray magic, I guess... #f4f4f4 magic, to be exact
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