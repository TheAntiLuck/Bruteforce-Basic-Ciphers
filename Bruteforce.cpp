// Programmer: Erik Lipsky
// Class: CPSC 353
// Project: Cryptoanalytic Attacks

/*
Implement the following:
1) Playfair bruteforce
2) Vigenere bruteforce
3) Caesar bruteforce
4) Vigenere cryptoanalysis
*/

/*

2. Cryptanalytic Attacks
Part I: Write a program that performs a brute force attack against the playfair cipher,
Vigenere cipher (assuming you know the key length), and Caesar cipher.
You will be given a file containing a dictionary of English words.
You may assume that the text was successfully decrypted if each decrypted word is in the dictionary.

Part II: write a program that performs cryptoanalysis of the Vigenere cipher.

*/

/*
pseudocode:

part 1)
input plaintext
choose how to encrpyt plaintext (playfair, vigenre, caesar)
encrypt plaintext with chosen cipher
optional: create an option to import ciphertext from .txt file

part 2)
now that we have the ciphertext and chosen cipher, perform bruteforce.
return ciphertext

part 3)
perform cryptoanalysis, don't take key as argument.
return ciphertext

part 4)
output the original plaintext.
output the cipher used.
output the decrypted text.
output the result (if any)

TODO:
decryption for vigenre
decryption for playfair
cryptoanalysis for Vigenre

Complete:
encryption for vigenre
encryption for caesar
encryption for playfair
decryption for caesar
dictionary
main program
menu function

*/

#include <iostream>
#include <string>
#include <cmath>
#include <cctype>

using namespace std;

// 50% of all written material is made up of 100 words.
// source https://www.dictionary.com/e/common-words/

string dictionary[100] = {
	"the", "of", "and", "a", "to", "in", "is", "you", "that", "it",
	"he", "was", "for", "on", "are", "as", "with", "his", "they", "I",
	"at", "be", "this", "have", "from", "or", "one", "had", "by", "word",
	"but", "not", "what", "all", "were", "we", "when", "your", "can", "said",
	"there", "use", "an", "each", "which", "she", "do", "how", "their", "if",
	"will", "up", "there", "about", "out", "many", "then", "them", "these", "so",
	"some", "her", "would", "make", "like", "him", "into", "time", "has", "look",
	"two", "more", "write", "go", "see", "number", "no", "way", "could", "people",
	"my", "than", "first", "water", "been", "call", "who", "oil", "its", "now",
	"find", "long", "down", "day", "did", "get", "come", "made", "may", "part"
};

// Get a valid cipher
void menu(int &choice, string &pText)
{
	do {
		system("cls");
		cout << "Please enter plaintext: ";
		getline(cin, pText);

		cout << "Please choose a ciper to encrypt with.(1-3)" << endl
			<< "1) Playfair Cipher" << endl
			<< "2) Vigenre Cipher" << endl
			<< "3) Caesar Cipher" << endl;
		cout << "Option: ";
		cin >> choice;

		if (choice < 1 && choice > 3) {
			cout << "Please pick a valid option." << endl;
			system("pause");
			// may need cin.ignore();
		}
	} while (choice <= 1 && choice >= 3);

	//cout << "In menu()" << endl;
	//cout << "Cipher = " << choice << endl;
	//cout << "Plaintext = " << pText << endl << endl;
}

// use encryption chosen by user.
// start with plain text.
// user enters key
// encrypt the plain text

void encryption(int choice, int &cKey, string &pKey, string &vKey, string &pText, string &cText)
{
	char alpha[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char alphaC[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	//cout << "In encryption()" << endl;
	//cout << "Cipher = " << choice << endl;
	//cout << "Plaintext = " << pText << endl << endl;

	cout << "Please enter a key: ";

	// encrypt using playfair
	if (choice == 1) {

		// 1) get key
		cin.ignore();
		getline(cin, pKey);
		cout << endl;

		// 2) capitalize all word letters (also changes J letters to I if found)
		for (int i = 0; i < pKey.length(); i++) {
			pKey[i] = toupper(pKey[i]);
			if (pKey[i] == 'J')
				pKey[i] = 'I';
		}

		// 3) create a 5x5 table
		char pTable[5][5];

		// Alphabet, except for letter 'J'
		char alphabet[25] = { 'A', 'B', 'C', 'D', 'E',
			'F', 'G', 'H', 'I', 'K',
			'L', 'M', 'N', 'O', 'P',
			'R', 'Q', 'S', 'T', 'U',
			'V', 'W', 'X', 'Y', 'Z' };

		// check if letter has been used.
		bool lCheck = 1;

		// 4) Create a playfair matrix using the key inputed,
		// and fill matrix with the rest of the alphabet.

		// rows of playfair matrix
		for (int i = 0, wordIndex = 0; i < 5; i++) {

			// columns of playfair matrix
			for (int j = 0; j < 5; j++) {

				// traverse key length
				while (wordIndex < pKey.length()) {

					// go through alphabet
					for (int k = 0; k < 25; k++) {
						if (pKey[wordIndex] == alphabet[k]) {
							lCheck = 0;
							alphabet[k] = '0';
							break;
						}
					}

					// assign to matrix
					if (!lCheck) {
						pTable[i][j] = pKey[wordIndex];
						lCheck = 1;
						break;
					}

					//go to the next word letter in key
					wordIndex++;
				}
				// once key is enterted, fill the rest with the alphabet.
				if (wordIndex >= pKey.length()) {
					for (int k = 0; k < 25; k++) {
						if (alphabet[k] != '0') {
							pTable[i][j] = alphabet[k];
							alphabet[k] = '0';
							break;
						}
					}
				}
			}
		}

		string eResult = "";

		// 5) convert and transform to uppercase of plain text
		for (int i = 0; i < pText.length(); i++) {
			pText[i] = toupper(pText[i]);
			if (pText[i] == 'J')
				pText[i] = 'I';
		}

		// 6) Insert the letter 'X' between two duplicate letters
		for (int i = 0; i < pText.length(); i++) {
			// if current and next letter are the same,
			if (pText[i] == pText[i + 1]) {
				eResult += pText[i];
				eResult += 'X';
			}
			else
				eResult += pText[i];

		}

		// 7) If there is a space get rid of it
		for (int i = 0; eResult[i]; i++) {
			if (eResult[i] == ' ') {
				eResult.erase(i, 1);
			}
		}

		// 8) If result is odd, append an 'X'
		if (eResult.length() % 2 == 1) {
			eResult = eResult + "X ";
		}

		//cout << "eResult: " << eResult << endl;
		//cout << "pText: " << pText << endl;

		// 9) Encrypt the text

		// traverse plaintext and write to cipher text,
		// 2 letters at a time.
		for (int i = 0; i <= eResult.length() - 2; i += 2) {

			int row1, row2, col1, col2;
			bool fLetter = false, sLetter = false;

			if (eResult.at(i) == ' ') {
				cText += ' ';
			}

			// gets coordinates
			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {
					if (eResult[i] == pTable[y][x]) {
						col1 = x;
						row1 = y;
						fLetter = true;
					}
					else if (eResult[i + 1] == pTable[y][x]) {
						col2 = x;
						row2 = y;
						sLetter = true;
					}
					if (fLetter && sLetter)
						break;
				}
			}

			// check for playfair rule of same column/row
			if (col1 != col2 && row1 != row2) {
				int temp = col1;
				col1 = col2;
				col2 = temp;
			}

			// column rule if true
			else if (col1 == col2) {
				row1++;
				row2++;
				if (row1 == 5)
					row1 = 0;
				if (row2 == 5)
					row2 = 0;
			}

			// row rule if true
			else if (row1 == row2) {
				col1++;
				col2++;
				if (col1 == 5)
					col1 = 0;
				if (col2 == 5)
					col2 = 0;
			}

			// append the result
			cText = cText + pTable[row1][col1] + pTable[row2][col2];
		}
	}

	// encrypt using vigenre
	if (choice == 2) {

		// 1) get the key
		cin.ignore();
		getline(cin, vKey);
		string cKey = "";

		int maxP, maxK;

		maxP = pText.length();
		maxK = vKey.length();
		int counter = 0;

		// 2) create key as long as ptext
		for (int i = 0; i < maxP; i++) {
			if (pText.at(i) == ' ') {
				cKey += ' ';
			}
			for (int j = 0; j < 26; j++) {
				if (pText.at(i) == alpha[j]) {
					cKey += vKey.at(counter);
					counter++;
				}
				if (counter == maxK)
					counter = 0;
			}
		}

		//cout << "vKey = " << vKey << endl;
		//cout << "cKey = " << cKey << endl;

		int index = 0;

		// 3) Perform encryption
		for (int h = 0; h < maxP; h++) {
			index = 0;
			if (pText.at(h) == ' ') {
				cText += ' ';
			}

			// Traverse column and row matrix
			for (int i = 0; i < 26; i++) {
				for (int j = 0; j < 26; j++) {

					// if the letter is found, encrypt.
					if (pText.at(h) == alpha[j] && cKey.at(h) == alpha[i]) {
						cText += alpha[index];
					}
					// Shift matrix to the right
					index = (index + 1) % 26;
				}
				index++;
			}
		}
		vKey = cKey;
	}

	// encrypt using caesar cipher
	if (choice == 3) {

		// 1) get the key
		cin >> cKey;

		int max;
		max = pText.length();
		int index;

		// encrypt function
		for (int i = 0; i < max; i++) {
			// Grab spaces
			if (pText.at(i) == ' ') {
				cText += ' ';
			}

			// Traverse alphabet
			for (int j = 0; j < 26; j++) {

				// Find the letter
				if (pText.at(i) == alpha[j])
				{
					// Mod 26 to transform and add to ciphertext
					index = alpha[(j + cKey) % 26];
					cText += toupper(index);
				}
			}
		}
	}

	cout << "Ciphertext = " << cText << endl << endl;
	system("pause");
}

void decryption(int choice, int &cKey, string &pKey, string &vKey, string pText, string &cText)
{
	char alpha[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	char alphaC[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	//cout << "In decryption()" << endl;
	//cout << "Cipher = " << choice << endl;
	//cout << "Ciphertext = " << cText << endl;
	//cout << "Plaintext = " << pText << endl << endl;

	string eResult = "";	// encryption result
	string dResult = "";	// decryption result

	int bpKey = 0;			// bruteforce playfair Key
	int bvKey = 0;			// bruteforce vigenre Key
	int bcKey = 0;			// bruteforce caesar Key

	int flag = 0;
	int neg;
	int index;
	int max;

	// decrypt using playfair
	if (choice == 1) {

	}

	// decrypt using vigenre
	if (choice == 2) {

		// since length is known, we will start from a^keylength
		// for instance, if keylength = 3, then keyCheck = "aaa"
		// also get all spaces
		string keyCheck = "";
		for (int a = 0; a < vKey.length() - 1; a++) {

			// get spaces
			if (vKey.at(a) == ' ') {
				keyCheck += ' ';
			}
			keyCheck += alpha[0];
		}

		max = pText.length();
		int inc = 0;

		// For bruteforcing, need to check 0 to 26^keylength
		for (bvKey = 0; bvKey < pow(26, max); bvKey++) {
			index = 0;
			neg = 0;
			eResult = cText;
			dResult = "";
			inc = bvKey % 26;
			keyCheck += alpha[inc];

			if (pText.at(bvKey) == ' ') {
				dResult += ' ';
			}
			for (int i = 0; i < 26; i++) { // rows or key
										   // copy blank spaces
				for (int j = 0; j < 26; j++) { // columns or plaintext
											   //cout << alphaC[index] << " ";

					if (eResult.at(bvKey) == alpha[j] && keyCheck.at(bvKey) == alpha[i]) {
						neg = (((j - i) + 26) % 26);
						dResult += alpha[neg];
						//cout << "(" << alphaC[j] << ", " << alphaC[i] << ")";
					}
					index = (index + 1) % 26;
				}
				//cout << endl;
				index++;
			}

			cout << dResult;
			// need to break up string into words
			string word = "";
			for (auto x : dResult)
			{
				if (x == ' ')
				{
					for (int d = 0; d < 100; d++) {
						// compare to dictionary and set flag if found
						if (word == dictionary[d]) {
							flag = 1;
						}
					}
					word = "";
				}
				else
				{
					word = word + x;
				}
			}

			if (flag == 1) {
				break;
			}
			inc++;
		}
	}

	// decrypt using caesar cipher
	if (choice == 3) {

		max = pText.length();

		// bruteforce key until word is found
		for (bcKey = 0; bcKey < 26; bcKey++) {
			index = 0;
			neg = 0;
			eResult = cText;
			dResult = "";

			for (int i = 0; i < max; i++) {
				// copy blank spaces
				if (eResult.at(i) == ' ') {
					dResult += ' ';
				}

				// check each letter
				for (int j = 0; j < 26; j++) {

					if (eResult.at(i) == alphaC[j])
					{
						neg = (j - bcKey);
						if (neg < 0)
							neg = neg + 26;
						index = alphaC[neg % 26];

						dResult += tolower(index);
					}
				}
			}
			dResult += ' ';

			// need to break up string into words
			string word = "";
			for (auto x : dResult)
			{
				if (x == ' ')
				{
					for (int d = 0; d < 100; d++) {
						if (word == dictionary[d]) {
							flag = 1;
						}
					}
					word = "";
				}
				else
				{
					word = word + x;
				}
			}

			if (flag == 1) {
				break;
			}
		}
	}

	cout << "Original Plaintext: " << pText << endl;
	cout << "Original Key: ";
	if (choice == 1) {			// output original playfair Key
		cout << pKey << endl;
	}
	if (choice == 2) {			// output original vigenre key
		cout << vKey << endl;
	}
	if (choice == 3) {			// output original caesar key
		cout << cKey << endl;
	}

	if (flag == 1) {				// if a match is found, output the result

		cout << "Bruteforce Result: " << dResult << endl;

		cout << "Bruteforce Key: ";
		if (choice == 1) {			// output bruteforced playfair Key
			cout << bpKey << endl;
		}
		if (choice == 2) {			// output bruteforced vigenre key
			cout << bvKey << endl;
		}
		if (choice == 3) {			// output bruteforced caesar key
			cout << bcKey << endl;
		}
	}
	else {							// otherwise, the key didn't work.
		cout << "Bruteforce Key: N/A" << endl;
		cout << "Bruteforce Result: N/A" << endl;
	}
}

int main()
{
	int choice = 0;				// user input
	string pText = "";			// string plaintext
	string cText = "";			// string ciphertext
	string vKey = "";			// vigenre key
	string pKey = "";			// playfair key
	int cKey = 0;				// caesar key	

	menu(choice, pText);

	//cout << "In main()" << endl;
	//cout << "Cipher = " << choice << endl;
	//cout << "Plaintext = " << pText << endl << endl;
	encryption(choice, cKey, pKey, vKey, pText, cText);

	//cout << "In main() again" << endl;
	//cout << "Cipher = " << choice << endl;
	//cout << "Ciphertext = " << cText << endl;
	//cout << "Plaintext = " << pText << endl << endl;
	decryption(choice, cKey, pKey, vKey, pText, cText);

	system("pause");
	return 0;
}




