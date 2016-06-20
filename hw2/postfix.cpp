#include "stackdbl.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

double calculate(string& expr, bool& success);

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
	ofstream outfile (argv[2]);
	//list takes the equation from each line
	string list;

	//when there are still lines to get, copy to list
	while (getline(infile, list)){
		bool valid=true; //calculate function will set to false if equation is bad
		double result = calculate(list, valid); 
		if(valid==false)
			outfile << "invalid" << endl;
		else
			outfile << result << endl;
	}

	infile.close();
	outfile.close();

	return 0;
}

double calculate(string& expr, bool& success){

	stringstream ss (expr);
	//item parses each int/operator in equation
	string item;
	ss >> item;

	//if empty, bad
	if(ss.fail()){
		success = false;
		return 0.1;
	}
	//if first item is an operator, bad
	if(item=="*" || item=="/" || item=="+" || item=="-"){
		success = false;
		return 0.1;
	}
	else{
		StackDbl stack = StackDbl();
		//add number to stack
		stack.push(atof(item.c_str()));//converted string to char* to double
		ss >> item;
		//if only one number in string, return that number
		if(ss.fail())
			return stack.top();
		//if second item is an operator, bad
		else if(item=="*"|| item=="/" || item=="+" || item=="-"){
			success = false;
			return 0.1;
		}
		else{
			stack.push(atof(item.c_str()));
			ss >> item;
			//keep going if there are more items to parse and stack has items to operate on
			while(!ss.fail() && !stack.empty()){
				//Multiply 
				if(item=="*"){
					double part2 = stack.top(); 
					stack.pop();
					if(!stack.empty()){ //check if another integer exists
						double part1 = stack.top();
						stack.pop();
						stack.push(part1*part2);
						ss >> item;
					}
					else{ //if no number for operator (too many operators)
						success=false;
						return 0.1;
					}

				} 
				//Divide
				else if(item=="/"){
					double part2 = stack.top();
					stack.pop();
					if(!stack.empty()){
						double part1 = stack.top();
						stack.pop();
						stack.push(part1/part2);
						ss >> item;
					}
					else{
						success=false;
						return 0.1;
					}
				}
				//Add
				else if(item=="+"){
					double part2 = stack.top();
					stack.pop();
					if(!stack.empty()){
						double part1 = stack.top();
						stack.pop();
						stack.push(part1+part2);
						ss >> item;
					}
					else{
						success=false;
						return 0.1;
					}

				}
				//Subtract
				else if(item=="-"){
					double part2 = stack.top();
					stack.pop();
					if(!stack.empty()){
						double part1 = stack.top();
						stack.pop();
						stack.push(part1-part2);
						ss >> item;
					}
					else{
						success=false;
						return 0.1;
					}

				}
				else{ //if a regular number, push to stack
					stack.push(atof(item.c_str()));
					ss >> item;
				}
					
			}
			//if stack is empty, bad
			if(stack.empty()){
				success=false;
				return 0.1;
			}
			else{
				double result = stack.top();
				stack.pop();
				//if still numbers in stack, bad
				if(stack.empty()==false){
					success=false;
					return 0.1;
				}
				else
					return result;
			}
		}
	}	
}