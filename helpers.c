#include <ctype.h>
#include <string.h>

#include "helpers.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "backend.h"

#include "tests/CuTest.h"

char *trimwhitespace(char *str) {
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}


//getPath()
//Returns name of file with current directory prepended
char *getPath(const char* fileName, int shouldEscape){
	FILE* pwd = popen("pwd","r");
	char buf[512];
	fgets(buf,sizeof(buf),pwd);
	pclose(pwd);
	strcpy(buf, strtok(buf, "\n")); //removes newline
	strcat(buf, "/");
	strcat(buf, fileName);
  if(shouldEscape == 1) {
    //if spaces should be escaped
    strcpy(buf, escapedString(buf));
  }
  char* retStr = calloc(512, sizeof(char));
  strcpy(retStr, buf);
	return retStr;
}


//str_end()
//Checks if a string ends with another string
//Credit to a Stack Overflow post
int str_end(const char *s, const char *t)
{
  size_t ls = strlen(s); // find length of s
  size_t lt = strlen(t); // find length of t
  if (ls >= lt)  // check if t can fit in s
  {
      // point s to where t should start and compare the strings from there
      return (0 == memcmp(t, s + (ls - lt), lt));
  }
  return 0; // t was longer than s
}


//escapedString()
//Escapes certain characters if needed by calling command
char* escapedString(char* buffer){

  int bufferLen = strlen(buffer);
  int spaceCount = 0;

  //get the number of spaces in the original string
  for(int n = 0; n < bufferLen; n++) {
    if(buffer[n] == ' ') {
      spaceCount++;
    }
  }

  //allocate space for a new string of size (oldstring + number of spaces, because each ' ' becomes '\ ')
  //init a counter to keep track of number of spaces replaced while iterating for indexing correctly
  char* str = calloc(bufferLen + spaceCount , sizeof(char));
  int currentNumberOfSpaces = 0;

  //iterate over old string to build new string
  for(int i = 0; i < bufferLen; i++) {
    if(buffer[i] == ' ' && buffer[i-1] != '\\') {
      //if current char is space and previous char is not a backslash (to prevent multiple escaping)
      //then set char and next char to backslash and space respectively, increment counter
      str[i + currentNumberOfSpaces] = '\\';
      str[i + currentNumberOfSpaces + 1] = ' ';
      currentNumberOfSpaces++;
    } else {
      //if any other char, simply duplicate
      str[i + currentNumberOfSpaces] = buffer[i];
    }
  }

  return str;
}

//unused
int appendCharToString(char* s, size_t size, char c) {
  if(strlen(s) + 1 >= size) {
    return 1;
  }
  int len = strlen(s);
  s[len] = c;
  s[len+1] = '\0';
  return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~TESTING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void TestGetPathNormal (CuTest *tc) {
  //Test getting path without escaping

  char* actual = getPath("em.mp3", 0); //change based on your filesystem
  char* expected = "/home/kevin/Documents/github/lemonade/em.mp3"; //change based on your filesystem
  CuAssertStrEquals(tc, expected, actual);
}

void TestGetPathEscapedSpaces (CuTest *tc) {
  //Test getting path with escaping

  char* actual = getPath("In\\ The\\ Dark.mp3", 1); //change based on your filesystem
  char* expected = "/home/kevin/Documents/github/lemonade/In\\ The\\ Dark.mp3"; //change based on your filesystem
  CuAssertStrEquals(tc, expected, actual);
}

void TestGetPathEscapedNoSpaces (CuTest *tc) {
  //Test getting path with escaping (no spaces)

  char* actual = getPath("em.mp3", 1); //change based on your filesystem
  char* expected = "/home/kevin/Documents/github/lemonade/em.mp3"; //change based on your filesystem
  CuAssertStrEquals(tc, expected, actual);
}

void TestStr_endMatching(CuTest *tc) {
  int actual = str_end("This is a test.mp3", ".mp3");
  int expected = 1;
  CuAssertIntEquals(tc, expected, actual);
}

void TestStr_endNonmatching(CuTest *tc) {
  int actual = str_end("This is a test.mp3", ".mp4");
  int expected = 0;
  CuAssertIntEquals(tc, expected, actual);
}

void TestEscapedStringSingle(CuTest *tc) {
  char* actual = escapedString("This is a test for escaping spaces in strings!");
  char* expected = "This\\ is\\ a\\ test\\ for\\ escaping\\ spaces\\ in\\ strings!";
  CuAssertStrEquals(tc, expected, actual);
}

void TestEscapedStringMulti(CuTest *tc) {
  char* actual = escapedString("This  is  a  test  for  multiple  spaces!");
  char* expected = "This\\ \\ is\\ \\ a\\ \\ test\\ \\ for\\ \\ multiple\\ \\ spaces!";
  CuAssertStrEquals(tc, expected, actual);
}

CuSuite* helpersGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestGetPathNormal);
  SUITE_ADD_TEST(suite, TestGetPathEscapedSpaces);
  SUITE_ADD_TEST(suite, TestGetPathEscapedNoSpaces);
  SUITE_ADD_TEST(suite, TestStr_endMatching);
  SUITE_ADD_TEST(suite, TestStr_endNonmatching);
  SUITE_ADD_TEST(suite, TestEscapedStringSingle);
  SUITE_ADD_TEST(suite, TestEscapedStringMulti);

  return suite;
}
