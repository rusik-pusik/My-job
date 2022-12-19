#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
 
#include <fstream>
#include <sstream>
 
using namespace std;
 
// error() simply disguises throws:
[[noreturn]] inline void error (const string& s)
{
  throw runtime_error(s);
}
 
[[noreturn]] inline void error (const string& s, const string& s2)
{
  error (s + s2);
}
 
[[noreturn]] inline void error (const string& s, int i)
{
  ostringstream os;
  os << s <<": " << i;
  error (os.str());
}
 
string wn;  //word or number
 
int count (const vector<char>& digits, char d) //looking a number of elimets in number
{
  int k{};
 
  for (int i = 0; i < digits.size(); ++i)
    if (digits[i] == d)
      ++k;
 
  return k;
}
 
void validate (const vector<char>& number) //testing for bad input
{
  for (int i = 0; i < number.size(); ++i)
  {
    if (wn == "number" && (number[i] < '0' || '9' < number[i]))
      error("the number contains not a digit");
    if (wn == "word" && (number[i] < 'a' || number[i] > 'z'))
      error("the word contains not a letter");
    if (wn == "number" && (count(number, number[i]) != 1))
      error("digits of the number are not unique");
    if (wn == "word" && (count(number, number[i]) != 1))
      error("letters of the word are not unique");
  }
}
 
vector<char> user_guess () //geting the try number
{
  vector<char> number(4);
 
  cout <<"guess the " << wn << ": ";
  for (int i = 0; i < number.size(); ++i)
    cin >> number[i];
 
  if (!cin)
    error("invalid input");
 
  validate (number);
 
  return number;
}
 
char random(int a , int b) // random char from range
{
    return static_cast<char>(a+rand()%(b-a+1));
}
 
vector<char> rando(int a , int b) //random number in vector for game
{
    vector<char> number{random(a , b) , random(a , b) , random(a , b) , random(a , b)};
    do
    {
        srand(time(NULL));
        number = {random(a , b) , random(a , b) , random(a , b) , random(a , b)};
    }
    while (number[0]==number[1] || number[1]==number[2] || number[2]==number[3] ||
          number[0]==number[2] || number[0]==number[3] || number[1]==number[3]);
    return number;
}
 
void cls()
{
    for(int i=0 ; i<50 ; i++) // clearing screen
        cout <<"\n";
}
 
 
//computer-guess functional
int trfl(int a, int b)
{
    if (a==b) return 1;
    if (a!=b) return 0;
}
 
vector<char> split(int x)
{
    vector<char> number;
    for (int i{0} ; i<4 ; ++i)
    {
        number.push_back(x%10);
        x/=10;
    }
    return number;
}
 
bool is_valid(int x)
{
    vector<char> number;
    //аналог функции validate для четырёхзначного числа
    int k{0};
    number = split(x);
    for (int i{0}; i < number.size(); ++i)
    {
        k += count(number, number[i]);
    }
 
    return k == 4;
}
 
bool matches(int n1, int n2, int bulls, int cows)
{
    //full match with parametrs of an other number
    int curb{0} , curc{0};
    vector<char> N1 = split( n1 );
    vector<char> N2 = split( n2 );
 
    for (int i{0} ; i < N1.size() ; ++i)
    {
        for (int j{0} ; j < N2.size() ; ++j)
        {
            if (i == j && N1[i] == N2[j] ) curb+=1;
        }
    }
 
    for (int i{0} ; i < N1.size() ; ++i)
    {
        for (int j{0} ; j < N2.size() ; ++j)
        {
            if (i != j && N1[i] == N2[j] ) curc+=1;
        }
    }
 
    return bulls == curb && cows == curc;
}
 
void computer_guess()
{
    const int setSize = 9877;
    bool badNum[setSize]; //index - number, is's vale - true or false for this number
 
    for (int i = 0; i < setSize; i++)  //getting all incorrect numbers (true in badNum)
        badNum[i] = !is_valid(i);
    while (true)
    {
        int bulls, cows;
        int question;
        for (question = 0; question < setSize && badNum[question]; ++question); //cheking if there is any
                                         //numbers that match (for won't stop until any match meet) question > setsize wont be a problem
 
        if (question >= setSize) // no more numbers that can match
        {
            cout << "Wrong bull/cow conditions!";
            break;
        }
       if (question / 1000 == 0){
            cout << "0" << question << "\n";
        } else {
            cout << question << "\n"; }
 
        cout << "enter bulls and cows: ";
        cin >> bulls >> cows;
 
        if (bulls == 4 && cows == 0) //end gsme with 4 bulls
        { if (question / 1000 == 0) {
            cout << "your number is: " << "0" << question <<endl;
            break;
            } else {
                cout << "your number is: " << question <<endl;
                break;
            }}
 
        for (int i = 0; i < setSize; i++)
            badNum[i] = badNum[i] || !matches(i, question, bulls, cows); //getting number doesn't match for new conditions
    }
}
 
void user_play(vector<char> number)
{
        int bulls{};
        do
        {
            bulls = 0;
            int cows{};
 
            vector<char> uguess = user_guess();
 
            for (int i = 0; i < uguess.size(); ++i)
            {
                if (uguess[i] == number[i])
                    ++bulls;
                else if (count(number, uguess[i]) == 1)
                    ++cows;
            }
 
            cout << bulls <<" bull(s) and "<< cows <<" cow(s)"<< endl;
        }
        while (bulls != 4);
}
 
void mode_direct( char mode )
{
    vector <char> number(4);
    switch (mode)
    {
    case '1' :
        cout << "Enter the 4 digit number:" << endl
             << "Your opponent will try to ";
        wn = "number";
        number = user_guess();
        cls();
        user_play(number);
        break;
    case '2' :
        number = rando('0' , '9');
        wn = "number";
        user_play(number);
        break;
    case '3' :
        number = rando('a' , 'z');
        wn = "word";
        user_play(number);
        break;
    case '4' :
        cout << "Enter 4-letter word for your opponent: ";
        wn = "word";
        for (int i{0}; i<4 ; ++i)
        {
            char let;
            cin >> let;
            if (let < 'a' || let > 'z')  error("Word contains not a letter");
            number[i] = let;
        }
        cls();
        user_play(number);
        break;
    case '5' :
        cout << "Make up the 4-letter word and enter" << endl
             << "it's bulls and cows paramets for computar to guess: " <<endl << endl;
        computer_guess();
        break;
    default:
        error("wrong mode");
    }
}
 
 
int main()
{
    cout <<"<<Bulls and Cows>>"<<endl
         <<"The number set of 4 unique digits(letters)."<<endl
         <<"Try to guess it."<<endl
         <<"<Bull> means right digit(letter) in the right position."<<endl
         <<"<Cow> means right digit(letter) in the wrong position."<<endl
         <<endl << "Game is on" << endl
         << "Chouse the game mode: " << endl
         << "Digit_PvP(1)  PvE(2)  HardCore(3)  Letter_PvP(4)  ComputerSolving(5)" << endl;
 
    char mode{};
    cin >> mode;
 
    try
    {
        mode_direct( mode );
        cout <<"game is over"<< endl;
    }
    catch (exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    catch (...)
    {
      cerr <<"Oops, something went wrong..."<< endl;
      return 2;
    }
}