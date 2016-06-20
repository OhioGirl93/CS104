#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src) 
{
  std::transform(src.begin(), src.end(), src.begin(), ::tolower);
  return src;
}

/** Converts a string containing a rawWord to a set of words 
	based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWord) 
{
	//set of words to be returned
	set <string> words;

	stringstream ss (rawWord);
	string currWord;
	ss >> currWord;

	while (!ss.fail()){
		//if the word is less than 2 characters, ignore and get next word
		if(currWord.length()<2)
			ss>>currWord;
		else{
			//remove punctuation from front of word
			while(ispunct(currWord[0])){ 
				currWord = currWord.substr(1);
			}
			//remove puncation from back of the word
			while(ispunct(currWord[currWord.length()])){
				currWord = currWord.substr(0, currWord.length()-1);
			}

			//after removing punction, if word is still at least 2 characters
			if(currWord.length()>1){
				//position of last encountered punctuation
				int lastpunc = currWord.length()-1;
				bool haspunc = false;

				for(int i=currWord.length()-2; i>0; i--){
					//if the character is a punc, create substring from last punc to here
					if(ispunct(currWord[i])){
						haspunc = true;
						string word = currWord.substr(i+1, lastpunc-i-1);
						lastpunc = i;
						//if the word is at least 2 characters
						if(word.length()>1){
							//convert to lowercase
							word = convToLower(word);
							words.insert(word);
						}
					}
				}
				//add the last item to set if there is punctuation
				if(haspunc==true){
					currWord = currWord.substr(0, lastpunc);
					currWord = convToLower(currWord);
					words.insert(currWord);
				}
				//if no punctuation was encountered, convert to lowercase, add the word
				else{
					currWord = convToLower(currWord);
					words.insert(currWord);
				}
			}
			ss >>currWord;
		}
	}
	return words;
}
