#include "reading.h"

/// Notes
/// 1) This assumes the platform uses \n for newline, some uses \r\n.
///    Fixing this to be platform-independent is left as an exercise. 

#define READ_INT_INVALID_MSG "Invalid input"

/// Reads a line from the keyboard, puts it in the len-sized
/// memory space pointed to by buf, and optionally removed newlines
char *read_string_with_buffer(char *buf, size_t len, bool strip_newline)
{
  ssize_t read = getline(&buf, &len, stdin);
  if (read > 0 && strip_newline)
    {
      buf[read-1] = '\0'; // Note 1
    }
  return buf;
}

/// Reads a line from the keyboard, converts it to an int if it contains
/// only digits, otherwise, keeps asking. 
int read_int(bool repeat_until_valid_int)
{
  char buf[16] = {};
  bool only_digits = true;

  do
    {
      if (!only_digits) puts(READ_INT_INVALID_MSG); 
	
      read_string_with_buffer(buf, sizeof(buf), STRIP_NEWLINE);
      only_digits = true;
  
      for (char *c = buf; *c && only_digits; ++c)
	{
	  only_digits = only_digits && isdigit(*c);
	}

    } while (only_digits == false);

  return atol(buf);
}

/// Asks a question and reads a string in response
char *ask_string_question(char *question)
{
  puts(question);
  return read_string();
}

/// Asks a question and reads a char in response
int ask_int_question(char *question)
{
  puts(question);
  return read_int(VALIDATE);
}

int main(int argc, char *argv[])
{
  printf("'%d'\n", ask_int_question("Give me an int: "));
  printf("'%s'\n", ask_string_question("Give me a string:"));
  return 0;
}
