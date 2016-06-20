/**
 * Code to generate all permutations of a string of characters
 */

#include <iostream>
#include <cstring>

using namespace std;


// A nice interface to the user who doesn't care about a current location
void all_perms(char *src_chars, char* buf);

// This is where we'll do the work
void perm_helper(char *src_chars, char* buf, int curr);

// Invokes the helper
void all_perms(char *src_chars, char* buf)
{
  perm_helper(src_chars, buf, 0);
}

// Iterates through all possible characters for the 'curr' location
// which are characters not previously used earlier in buf
void perm_helper(char *src_chars, char* buf, int curr)
{
  if(buf[curr] == '\0'){
    cout << buf << endl;
  }
  else {
    int len = strlen(src_chars);
    for(int i=0; i < len; i++){
      if(buf[0]!=src_chars[i] && buf[1]!=src_chars[i] && buf[2]!=src_chars[i]){
        buf[curr] = src_chars[i];
        perm_helper(src_chars, buf, curr+1);
      }
      buf[curr] = ' ';
    }
  }
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a string of characters to generate all permutations" << endl;
    return 1;
  }

  // Allocate a temporary buffer of equal size to the src string
  //  and initialize it with all spaces
  char* buf = new char[strlen(argv[1])+1];
  for(int i=0; i < strlen(argv[1]); i++){
    buf[i] = ' ';
  }
  buf[strlen(argv[1])] = '\0';

  // Now find all permutations
  all_perms(argv[1], buf);

  // Cleanup and return
  delete [] buf;
  return 0;
}
