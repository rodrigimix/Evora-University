/*
                                                              ,#%%%%*                     
                                                       *%%%%%%%%%%%%%%%%%%%%              
                                                       %%%%%%%%%%%%%%%%%%%%%%%%           
                                                  %      %%%%%%%%%%%%%%%%%%%%%%%%,        
                                                %%%        %%%%%%%%%%/  %%%%%%%%%%%       
                                               %%%%*         %%%%%%%%%  %%%%%%%%/         
                                              %%%%%%           %%%%%%%  %%%%%%            
                                              %%%%%%%            .%%%/  %%%.              
                                             *%%%%%%%%                                    
                                              %%%%%%%%%#                                  
                                              %%%%%%%%%%%%%       /       ..       %%     
                                               %%%%%%%%%%%%%%%%%%%%%     ,%%%%%%%%%%      
                                                %%%%%%%%%%%%%%%%%%%%%   *%%%%%%%%%%       
                                                  %%%%%%%%%%%%%%%%%%%% /%%%%%%%%%.        
                                                    #%%%%%%%%%%%%%%%%%%%%%%%%%%           
                                                        %%%%%%%%%%%%%%  %%%*              
                                                               ,/((*     


    ____            __     _                __  ___                                    __   ______   ___      ___   ____     _____
   / __ \____  ____/ /____(_)___ _____     /  |/  /___ __________ ___  _____  _____   / /  / ____/  |__ \    <  /  ( __ )   |__  /
  / /_/ / __ \/ __  / ___/ / __ `/ __ \   / /|_/ / __ `/ ___/ __ `/ / / / _ \/ ___/  / /  /___ \    __/ /    / /  / __  |    /_ < 
 / _, _/ /_/ / /_/ / /  / / /_/ / /_/ /  / /  / / /_/ / /  / /_/ / /_/ /  __(__  )  / /  ____/ /   / __/    / /  / /_/ /   ___/ / 
/_/ |_|\____/\__,_/_/  /_/\__, /\____/  /_/  /_/\__,_/_/   \__, /\__,_/\___/____/  / /  /_____/   /____/   /_/   \____/   /____/  
                         /____/                              /_/                  /_/                                            
*/

#include <stdbool.h>

typedef char ElementType2;

#ifndef _HashLin_H
#define _HashLin_H


typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable CreateHash(int Tablesize);
void DestroyTBL(HashTable H);

bool Find(ElementType2 *Key ,HashTable H);

void Insert(ElementType2 *Key, HashTable H);

ElementType2* Retrieve_Hash(Position P, HashTable H);

HashTable Rehash(HashTable H);

void PrintTable(HashTable H);

int TableSize(HashTable H);

float LoadFactor(HashTable H);
#endif