/* This is the console executable that makes use of the BullCow class
This acts as the view in MVC pattern, and is possible for all
User interaction. For game logic see th FBullCowGame
*/
#pragma once


#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make syntax Unreal friendly
using FText = std::string; // To not use std::string
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game, which re-use across plays

// The entry for our app
int32 main() {
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	// introduce the game
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of ?" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop for the number of turns asking for guesses
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); // TODO make loop checking valid
		
		// Submit valid guess to the game
		FBullCowCount BullCowCount =  BCGame.submitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	
	// TODO summarise game
	PrintGameSummary();
}

FText GetValidGuess()
{

	EGuessStatus Status = EGuessStatus::Invalid_status;
	FText Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter you guess : ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " Letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n) ? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "WELL DONE - YOU WIN!\n";
		return;
	}
	std::cout << "Better luck next time :(\n";
}
