/*Thee game logic
*/

#pragma once
#include <string>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame(); // Constructor
	~FBullCowGame(); // Destructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; // TODO make a more rich return value

	void Reset(); // TODO make a more rich return vallue
	FBullCowCount submitValidGuess(FString);

private:
	int32 MyCurrenTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};

FBullCowGame::FBullCowGame(){ Reset(); }

FBullCowGame::~FBullCowGame()
{
}

inline int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}
inline int32 FBullCowGame::GetCurrentTry() const { return MyCurrenTry; }
inline bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

inline void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrenTry = 1;
	bGameIsWon = false;
	return;
}

inline EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != GetHiddenWordLength()) return EGuessStatus::Wrong_Length;
	else if (!IsLowercase(Guess)) return EGuessStatus::Not_Lowercase;
	else if (!IsIsogram(Guess)) return EGuessStatus::Not_Isogram;
	return EGuessStatus::OK;
}

// receives a valid guess, increments turn, and return count
inline FBullCowCount FBullCowGame::submitValidGuess(FString Guess)
{
	// Increiment the turn number
	MyCurrenTry++;
	// setup a return variable
	FBullCowCount BullCowCount;

	// loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	bGameIsWon = BullCowCount.Bulls == HiddenWordLength;
	// Compare letters against the hidden word
	return BullCowCount;
}

inline bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) return true;
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) return false;
		else LetterSeen[Letter] = true;
	}
	return true;
}

inline bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (isupper(Letter)) return false;
	}
	return true;
}

inline int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }
