#include <iostream> //c++ input/output stream library
#include <vector>   //�zel bir array tarz� olan vekt�r i�in kullan�l�r.
#include <fstream>   //filestream, dosyalar i�in
#include <cstdlib>   // used for rand() operation in this code
#include <time.h>    //rastgele se�me i�in kullan�l�r.
#include <Windows.h> 	 // T�rk�e karakterler i�in kullan�ld�.
using namespace std;

void Printer(string message, bool Top = true, bool Bottom = true);

void DrawingHangman(int numOfGuesses = 0); //�ekil �izen fonksiyon

void Letters(string input, char start, char end); // Tahmin i�in kullan�labilir harfleri yazd�r�yor.

void LettersForTurkish(string input);   // Tahmin i�in kullan�labilir harfleri yazd�r�yor(T�rk�e i�in).

void AvailableLettersPrinting(string UserInput); //Kullan�labilir kelimelerin aral���n� belirliyor.

bool WordChecker(string word, string guessedWord); //Tahmin edilecek kelimenin t�m harflerinin a��l�p a��lmad���n� kontrol eder.

string RandomWordFromFile(string path); //Dosyadan rastgele kelime se�er.

int LeftTryings(string word, string guessed);   //Deneme say�s�n� hesaplar

int main(){
SetConsoleOutputCP(1254);  // T�rk�e karakterler i�in kullan�ld�.
SetConsoleCP(1254);
char flag = 'E';
	while(flag == 'E'){	
		system("cls");
		system("clear");
		srand(time(0));
	
		string guesses;
		string wordToBeAsked;			
		wordToBeAsked =	RandomWordFromFile("WordsTurkish.txt");
	
		int shots = 0;
		bool winning = false;
		while ( shots < 9 ) {
		system("cls");
		Printer("ADAM ASMACA");
		DrawingHangman(shots);
		if(shots > 6)
			Printer("", false, false);
		Printer("MEVCUT HARFLER");
		Printer("", false, false);
		LettersForTurkish(guesses);
		Printer("", false, false);
		Printer("KEL�MEY� TAHM�N ED�N", false, true);
		Printer("", false, false);
		winning = WordChecker(wordToBeAsked, guesses);
				
		if(winning)
			break;
		char letter;
		if (shots == 0)
			printf("(Sadece b�y�k haarfleri kullan�n)\n");
		printf("Tahmininizi giriniz : "); cin >> letter;
		//scanf("%s", &letter);
		
		if(guesses.find(letter) == string::npos)
			guesses += letter;
					
		shots = LeftTryings(wordToBeAsked, guesses);
			
		}	 
		system("cls");
		
		if(winning)
			Printer("KAZANDIN TEBR�KLER");
		else{
			Printer("KAYBETT�N DOSTUM!");
			DrawingHangman(shots);
			Printer("",false,true);
		}
					
		//	system("pause");
		do{
			if(flag != 'E')
				printf("TANIMLANMAYAN B�R HARF G�RD�N�Z\n");
			printf("TEKRAR OYNAMAK �STER M�S�N�Z ( Evet i�in 'E', Hay�r i�in 'H') : ");
			scanf("%s", &flag);
		}
		while(flag != 'E' && flag != 'H');
	}
  return(0);
}


void Printer(string message, bool Top, bool Bottom)  //Genel yazma i�lemi
{
	if (Top){
		printf("<-|||||||||||||||||||||||||||||||||->\n");
		printf("|                                   |\n");
		printf("|");
	}
	else{
		printf("|");
	}
	bool front = true;
	for(int i = message.length(); i<35; i++){
		if (front){
			message = " " + message ;
		}
		else{
			message = message + " " ;
		}
		front = !front;
	}
	cout << message.c_str();
	
	if (Bottom){
		printf("|\n");;
		printf("|                                   |\n");
		printf("<-|||||||||||||||||||||||||||||||||->\n");
	}
	else{
		printf("|\n");
	}
}

void DrawingHangman(int numOfGuesses)  //�ekil �izen fonksiyon
{
	if(numOfGuesses >= 1){
		Printer("_______         ",false,false);
	}
	else{
		Printer("",false,false);
	}
	if(numOfGuesses >= 2){
		Printer("|       |        ",false,false);
	}
	else{
		Printer("",false,false);
	}
	if(numOfGuesses >= 3){
		Printer("|      _|_       ",false,false);
	}
	else{
		Printer("",false,false);
	}
	if(numOfGuesses >= 4){
		Printer("|     |_O_|      ",false,false);
	}
	else{
		Printer("",false,false);
	}
	if(numOfGuesses == 5){
		Printer("|     /          ",false,false);
	}
	if(numOfGuesses == 6){
		Printer("|     / |        ",false,false);
	}
	if(numOfGuesses >= 7){
		Printer("|     / | \\      ",false,false);
	}
	else{
		Printer("",false,false);
	}
	if(numOfGuesses == 8){
		Printer("__|__    /            ",false,false);
	}
	if(numOfGuesses >= 9){
		Printer("__|__    / \\         ",false,false);
	}
	else{
		Printer("",false,false);
	}				
	
}

void LettersForTurkish(string input){   // Tahmin i�in kullan�labilir harfleri yazd�r�yor(T�rk�e i�in).
	string lettersFirst;
	string lettersSecond;
	char lettersOne[14] = {'A','B','C','�','D','E','F','G','�','H','I','�','J','K'};
	char lettersTwo[15] = {'L','M','N','O','�','P','R','S','�','T','U','�','V','Y','Z'};
	for(int i = 0; i <= 13; i++){
		if(input.find(lettersOne[i]) == string::npos){
			lettersFirst += lettersOne[i] ;
			lettersFirst += " ";
		}
		else{
			lettersFirst += "  ";
		}
	}
	Printer(lettersFirst, false, false);
	for(int i = 0; i <= 14; i++){
		if(input.find(lettersTwo[i]) == string::npos){
			lettersSecond += lettersTwo[i] ;
			lettersSecond += " ";
		}
		else{
			lettersSecond += "  ";
		}
	}
	Printer(lettersSecond, false, false);
}

bool WordChecker(string word, string guessedWord){  //Tahmin edilecek kelimenin t�m harflerinin a��l�p a��lmad���n� kontrol eder.
	//setlocale(LC_ALL, "Turkish");
	bool win = true;
	string space;
	for(int i = 0; i < word.length(); i++){
		if(guessedWord.find(word[i]) == string::npos){
			win = false;
			space += "_ ";
		}
		else{
			space += word[i];
			space += " ";
		}
	}
	Printer(space, false, true);
	return win;
}

string RandomWordFromFile(string path){ //Dosyadan rastgele kelime se�er.
	//setlocale(LC_ALL, "Turkish");
	int lineNumber = 0;
	string word;
	vector<string> Vec;
	ifstream reader(path.c_str());
	if (reader.is_open()){
		while(std::getline(reader, word)){
			Vec.push_back(word);
		}
		int randomLine = rand() % Vec.size();
		word = Vec.at(randomLine);
		reader.close();
	}
	return word;
}

int LeftTryings(string word, string guessed){    //Deneme say�s�n� hesaplar
//	setlocale(LC_ALL, "Turkish");
	int missShots = 0;
	for(int i = 0; i < guessed.length(); i++){
		if(word.find(guessed[i]) == string::npos)
			missShots++;
	}
	return missShots; 
}
/*
<-|||||||||||||||||||||||||||||||||->
|              						|
|			ADAM ASMACA				|
|              						|
<-|||||||||||||||||||||||||||||||||->
|        _________ 					|
|       |      	  |					|
|       |      	 _|_				|
|       |      	|_O_|				|
|       |      	/ | \				|
|     __|__    	 / \				|
|              						|
<-|||||||||||||||||||||||||||||||||->
|              						|
|	      MEVCUT  HARFLER			|
|              						|
<-|||||||||||||||||||||||||||||||||->
|              						|
|    A B C � D E F G � H I � J K    |
|   L M N O � P R S � T U � V Y Z 	|
|			   						|
|       KEL�MEY� TAHM�N ED�N		|
|              						|
<-|||||||||||||||||||||||||||||||||->
|              						|
|     _ _ _ _ _ _ _ _ _ _ _ _ _ _   |
|              						|
<-|||||||||||||||||||||||||||||||||->
*/
