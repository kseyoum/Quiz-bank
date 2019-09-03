// Kirubel Seyoum
// ITP 165, Fall 2018
// Homework 07
// kseyoum@usc.edu
//  main.cpp
//  Homework 7
//
//  Created by Kirubel Seyoum on 10/17/18.
//  Copyright © 2018 Kirubel Seyoum. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

struct QAPair{
    std::string question;
    std::string answer;
};
// Function is called loadData
// Parameters consist of the array of quiz items, the potential question, and the potential answer
//Function is a integer thus returns the length of the array.
//Fuction computes what's in each file
int loadData( QAPair quizItems[], std::string& question, std::string& answer)
{
    std::string fileName;
    std::cout<< "Enter file name:";
    std::cin >> fileName;
    std::ifstream fileInput(fileName);
    int i = 0;
    if (fileInput.is_open())
    {
        
        std::getline(fileInput,question,',');
        std::getline(fileInput,answer);
        std::cout<< "Questions are "<< question << " and answers are "<< answer<< "\n";
        while(!fileInput.eof()){
            std::string line;
            std::string first;
            std::string second;
            std::getline(fileInput, line);
            std::getline(fileInput,first,',');
            std::getline(fileInput,second);
            QAPair ToAdd;
            ToAdd.question=first;
            ToAdd.answer=second;
            quizItems[i]=ToAdd;
                i++;
        }
    }
    else
    {
        std::cout<< "file is not opened";
    }
    
    
    return i;
}
//Function is called display data.
//Parameters consist of array of quiz items and the length of the array
// Function is a void thus returns nothing
// Function prints the question and answer set
void displayData (QAPair quizItems[], int length)
{
    for (int i=0; i<length; i++){
        QAPair ToAdd;
        ToAdd=quizItems[i];
        std::cout << ToAdd.question << " " << ToAdd.answer << std::endl;
    }
}
//Function is called pick5
//Parameters consist of an array of random numbers, the size of the array, and the size of the quiz items
//Function is a void thus returns nothing
//function picks five non repeating numbers from the file
void pick5(int randNums[], int n, int r, int& length)
{
    r=length;
    bool nne =false;
    for(int i=0;i<n; i++)
    {
        do
        {
            nne=true;
            int rnad=rand()%r;
            for (int j=0; j< i; j++)
            {
                if (rnad==randNums[j])
                {
                    nne= false;
                }
                
            }
            randNums[i]=rnad;
        }while (nne=false);
    }
}
//Function ask the user one question from the file and provides feedback on answer
//Function is a bool so it returns a true or false statement
// function is called ask1
//parameters consist of quiz items, a question answer pair and the length of the array
bool ask1(QAPair& ToAdd, int length,QAPair quizItems[])
{
    bool feedback;
    int i=0;
    int n=5;
    int randNums[5];
    int r=length;
    int randomNum;
    pick5(randNums, n, r, length);
    int rnad;
    ToAdd=quizItems[randNums[i]];
    std::cout<< ToAdd.question<< "? ";
    std::string userAnswer;
    std::cin>> userAnswer;
    if (userAnswer==ToAdd.answer)
    {
        feedback=true;
        if (feedback==true)
        {
            std::cout<< "correct!";
        }
        
    }
    else{
        feedback=false;
        std::cout<< "oops, correct answer is "<< ToAdd.answer;
        
        }

return feedback;
}

//Function is a void thus doesn't return anything.
//Function is called do Quiz
//The function runs a quiz with five questions from the file.
//Parameters consist of quiz Items array, the amount the user gets correct, and the length of the array
void doQuiz(QAPair quizItems[], int amtCorrect, int length)
{
    std::string question;
    std::string answer;
    int n=5;
    int randNums[5];
    int r=length;
    pick5(randNums, n, r,length);
    for (int i=0; i<5; i++)
    {
        if (ask1(quizItems[randNums[i]],length,quizItems)==true)
        {
            amtCorrect++;
        }
    }
    std::cout << "You got " << amtCorrect << " correct \n";
}
//Function is a void thus doesn't return anything
// Function is called doTrain
// Parameters consist of quiz Items array, the amount of tries the user does, and the length of the array
// Function runs a training session for the user to learn and test knowledge.
void doTrain (QAPair quizItems[], int tries, int length)
{
    std::string question;
    std::string answer;
    int right=0;

    int n=5;
    int randNums[5];
    int r=length;
    pick5(randNums, n, r,length);
    bool correct=false;
    while (right==5)
    {
        int i=0;
        ask1(quizItems[randNums[i]],length,quizItems);
            if (ask1(quizItems[randNums[i]],length,quizItems)==true)
            {
                right++;
            }
            else
            {
                while (correct==false)
                {
                    correct=ask1(quizItems[randNums[i]],length,quizItems);
                }
            }
        i++;
        tries++;
            
    }
}


int main(int argc, const char * argv[]) {
    //establish variables
    QAPair quizItems[1000];
    std::ofstream fileStream("quiz.txt");
    int myInput;
    std::string question;
    std::string answer;
    std::string userInput;
    int length;
    int amtCorrect=0;
    int tries=0;
    length=loadData(quizItems, question, answer);
    //do while loop to make sure that the function runs atleast once
    do
    {
        //provide user with options
        std::cout << "1: quiz\n";
        std::cout << "2: train\n";
        std::cout << "3 quit\n";
        std::cin >> myInput;
    if (myInput==1)
    {
        doQuiz(quizItems, amtCorrect, length);
    }
    if (myInput==2)
    {
        doTrain(quizItems, tries, length);
    }
    if (myInput == 3)
    {
    return 0;
    }}
    //parameters for do while loop
    while (myInput == 1|| myInput == 2);
}
