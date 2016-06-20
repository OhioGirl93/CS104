#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <cstring>
#include <map>
#include <utility>
#include "setint.h"

using namespace std;

int main(int argc, char *argv[]){

	//check input file
	if(argc<2){
		cout << "Please enter an input file." << endl;
		return 0;
	}
	//check output file
	if(argc<3){
		cout << "Please enter an output file." << endl;
		return 0;
	}

	ifstream infile (argv[1]);
	fstream outfile (argv[2]);

	map<string, SetInt> map;

	string line;
	int pagenum = 1; //start pages at 1

	while(getline(infile, line)){
		string word;
		stringstream ss(line);
		ss >> word;
		while(!ss.fail()){
			if(word=="<pagebreak>") //increment page
				pagenum++;
			else{
				//cstring of word to loop through
				char clist [word.length()+1];
				strcpy(clist, word.c_str());

				//delete punctuation from front
				while(ispunct(clist[0])){ 
					for(unsigned int i=0; i<strlen(clist); i++){
						clist[i] = clist[i+1];
					}
				}
				//delete punctuation from back
				while(ispunct(clist[strlen(clist)-1])){ 
					clist[strlen(clist)-1] = '\0';
				}

				//if the word is at least 2 characters
				if(strlen(clist)>1){
					//checking if word has punctuation
					bool haspunc = false;
					//check for hyphens
					int lasthyphen = strlen(clist)-1; //position of last hyphen 
					//loop through from back to front
					for(unsigned int i=strlen(clist)-2; i> 0; i--){
						if(clist[i]=='-'){
							string newWord = clist;
							//take the substring from last hyphen up to current position
							newWord = newWord.substr(i+1, lasthyphen);
							//reassign hyphen position
							lasthyphen = i;
							//change back to cstring to make word lowercase
							char temp [newWord.length()+1];
							strcpy(temp, newWord.c_str());
							for(unsigned int j=0; j<strlen(temp); j++){
								temp[i] = tolower(temp[i]);
								if(ispunct(temp[j])!=0) //0 = false, not punct
									haspunc = true;
							}
							//if the word does not have punctuation, add
							if(!haspunc){
								if(map.find(newWord)==map.end()){
									SetInt set;
									set.insert(pagenum);
									map[newWord] = set;
								}
								else{
									SetInt set = map[newWord];
									set.insert(pagenum);
									map[newWord] = set;
								}	
							}
						}
					}
					
					//if no hyphens, set to lowercase and check punctuation
					haspunc = false;
					for(unsigned int i=0; i<strlen(clist); i++){
						clist[i] = tolower(clist[i]);
						if(ispunct(clist[i])!=0)
							haspunc = true;
					}
					//word to be ultimately added
					string finalWord = clist;
					//if no punctuation, add to map
					if(haspunc==false){
						if(map.find(finalWord)==map.end()){
							SetInt set;
							set.insert(pagenum);
							map[finalWord] = set;
						}
						else{
							SetInt set = map[finalWord];
							set.insert(pagenum);
							map[finalWord] = set;
						}	
					}
				}
			}
			ss>>word; // read next word
		}
	} //finished reading

	//loop through words user is searching
	for(int i=3; i<argc; i++){
		string search = argv[i];
		char csearch [search.length()+1];
		strcpy(csearch, search.c_str());
		//set search words to lowercase
		for(unsigned int j=0; j<strlen(csearch); j++){
			csearch[j] = tolower(csearch[j]);
		}
		//reassign and print the set if exists, else print none
		search = csearch;
		if(map.find(search)==map.end())
			outfile << "None" << endl;
		else{
			SetInt outset = map[search];
			outfile << *(outset.first()) << " ";
			int size = outset.size()-1;
			//print subsequent values in set
			while(size >0){
				outfile << *(outset.next()) << " ";
				size--;
			}
			outfile << endl;
		
		}
	}

	return 0;
}