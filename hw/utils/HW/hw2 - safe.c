/*
  Author: Michael Mascari
  Email: mmascari2017@my.fit.edu
  Course: algorithms and data structures 
  Section: 2
  Description: Homework 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//for storing the words when read in from file
typedef struct WORD{
	char first;
	char letters[20];
	char last;
	struct WORD* next;
}WORD;

//stores the found words
typedef struct FINAL{
	char letters[60];
	struct FINAL* next;
}FINAL;

//a head node and free pointer for every struct
WORD* WHead = NULL;
WORD* WPointer = NULL;
FINAL* FHead = NULL;
FINAL* FPointer = NULL;

int read_File(int argc, char *argv[]); //reads from the file
void make_Word(char word[20]); //makes the word linked list
void make_Final(char word[60], char final[60]); //puts a palindrome in a completed linked list;
void FPrint(); //prints all of the found plindromes from single or the smashed palindromes from other_Length();
void WPrint(); //debug function prints the word linked list
void single(char word[60], char final[60]); //palLenght == 1 
void other_Length(int argc, char *argv[], int amount); //palLength > 1


int main(int argc, char *argv[]){
	char word[20]; //copies the words from the "word" struct to save them from editing
	char final[60]; //makes sure the final string is formatted
	int amount; //amount of words in the file
	amount = read_File(argc, argv); //returns the amount of words from the file
	if(*argv[2] == '1'){ //if palLength is 1
		WPointer = WHead; //resets WPointer
		while(WPointer != NULL){
			strcpy(word, WPointer->letters); //preserves WPointer->letters from editing
			strcpy(final, word);
			single(word, final);
			WPointer = WPointer->next;
		}
	}else{ //if palLength is > 1
		other_Length(argc, argv, amount);
	}
	FPrint(); //prints all the found palidromes
	return 0;
}

//palLength > 1
void other_Length(int argc, char *argv[], int amount){
	WPointer = WHead; //resets WPointer
	char word[60];
	char final[60];
	while(WPointer != NULL){
		WORD* TempWord = WHead;
		for(int i = 0; i < amount; i++){ //needs to check for every word scanned in
			while(TempWord->next != NULL){ //then it checks every word against it
				if(WPointer->first == TempWord->last){ //only checks them if they can make a palindrome
					strcpy(word, WPointer->letters);
					strcpy(final, TempWord->letters);
					strcat(word,TempWord->letters);
					//printf("%s\n", word);
					if(strcmp(WPointer->letters, TempWord->letters)!= 0){//makes sure the word addedisnt the original words
						single(word, final);
					}
				}
				TempWord = TempWord->next;
			}
		}
		WPointer = WPointer->next;
	}
	return;
}

// palLength == 1 or words smashed together
void single(char word[60], char final[60]){
	int i = 0;
	int j = 0;
	while(word[i] != '\0'){//finds the length of the word
		i++;
	}
	if(i == 1 || (i == 2 && word[0] == word[1])){ //if it has been cut to one letter or two letters that are the same, make it a final word
		make_Final(WPointer->letters, final);
		return;
	}else{
		if(word[0] == word[i-1]){ //if the first and last letter are the same
			while(j+1 < i){ //move each letter one foreward
				word[j] = word[j+1];
				j++;
			}
			word[i-2] = '\0'; //marks the new end of the word
			single(word, final); //recursive
		}
	}
	return;
}

//takes words and puts them in a final struct
void make_Final(char word[60], char final[60]){
	FINAL* NewFinal = (FINAL*) malloc(sizeof(FINAL)); //makes the new final node
	NewFinal->next = NULL;
	if(strcmp(word,final)==0){//makes sure they are the same before making it final
		strcpy(NewFinal->letters, word);
		if(FHead == NULL){
			FHead = NewFinal;
			FPointer = NewFinal;
		}else{
			FPointer->next = NewFinal;
			FPointer = NewFinal;
		}
	}else{
		strcpy(NewFinal->letters, word); //makes it look nice for multiple word palindromes
		strcat(NewFinal->letters, " ");
		strcat(NewFinal->letters, final);
		if(FHead == NULL){
			FHead = NewFinal;
			FPointer = NewFinal;
		}else{
			FPointer->next = NewFinal;
			FPointer = NewFinal;
		}
	}
	return;
}

//self explainitory 
int read_File(int argc, char *argv[]){
	char word[20];
	int amount = 0;
	FILE * data_input = fopen(argv[1], "r");
	while(fscanf(data_input, "%s ", word)!= EOF){
		make_Word(word);
		amount++;
	}
	return amount;
}

//sets up the word struct for each word scanned in from file
void make_Word(char word[20]){
	int i = 0;
	WORD* NewWord = (WORD*) malloc(sizeof(WORD));
	NewWord->next = NULL;
	NewWord->first = word[0];//so the words can be compared easier
	while(word[i] != '\0'){
		i++;
	}
	NewWord->last = word[i-1];
	strcpy(NewWord->letters,word); 
	if(WHead == NULL){
		WHead = NewWord;
		WPointer = NewWord;
	}else{
		WPointer->next = NewWord;
		WPointer = NewWord;
	}
	return;
}

//prints out the final struct 
void FPrint(){
	FPointer = FHead;
	while(FPointer != NULL){
		printf("%s\n",FPointer->letters);
		FPointer = FPointer->next;
	}
	return;
}

//debug function
void WPrint(){
	WPointer = WHead;
	while(WPointer != NULL){
		printf("%s\n", WPointer->letters);
		WPointer = WPointer->next;
	}
	return;
}












