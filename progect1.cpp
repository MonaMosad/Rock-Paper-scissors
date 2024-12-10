#include<iostream>
#include<string>
#include<math.h>
#include<cstdlib>
#include<ctime>
using namespace std;
enum enGamechoice{stone =1,paper=2,scissors=3};
enum enwinner{player=1,computer=2,draw=3};
struct stRoundInfo
{
    short roundNumber;
    enGamechoice playerchoice;
    enGamechoice computerchoice ;
    enwinner winner;
    string winnerName;
};
struct stGameResults
{
    short GameRounds=0;
    short Player1Winnertimes=0;
    short ComputerWinnertimes;
    short DrawTimes=0;
    enwinner Gamewinner;
    string WinnerName ="";
};
enwinner WhowONTheRound(stRoundInfo info)
{
    if (info.playerchoice==info.computerchoice)
    {
        return enwinner::draw;
    }
    switch (info.playerchoice)
    {
    case enGamechoice::stone:
    if (info.computerchoice==enGamechoice::paper)
    {
        return enwinner::computer;
    }
    
        break;
        case enGamechoice::scissors:
        if (info.computerchoice==enGamechoice::stone)
        {
            return enwinner::computer;
        }
        case enGamechoice::paper:
        if (info.computerchoice==enGamechoice::scissors)
        {
            return enwinner::computer;
        }
    }
    return enwinner::player;
}
int RandNumber(int from ,int to)
{
    int Randnum=rand()%(to -from + 1)+from;
    return Randnum;
}
string WinnerName(enwinner winner)
{
   string arrwinner[3]={"player","computer","NO Winner"};
   return arrwinner[winner-1];

}

void SetWinnerScreenColor(enwinner Winner)
{
    switch (Winner)
    {
    case enwinner::player:
    system("color 2f");
        break;
    
    case enwinner::computer:
        system("color 4f");
        cout<<"\a";
        break;
        default:
        system("color 6f");
        break;
    }
}
string ChoiceName(enGamechoice Choice)
{
    string arrGameChoice[3]={"stone","paper","scissers"};
    return arrGameChoice[Choice-1];
}
void PrintRoundResult(stRoundInfo roundinfo)
{
    cout<<"\n_________Round["<<roundinfo.roundNumber<<"]__________\n\n";
    cout<<"player choice: "<< ChoiceName(roundinfo.playerchoice)<<endl;

    cout<<"computer choice : "<< ChoiceName(roundinfo.computerchoice);
    cout<<"\n";

    cout<<"Round Winner : ["<<roundinfo.winnerName<<"]\n";
    cout<<"_________________________________________\n\n";
    SetWinnerScreenColor(roundinfo.winner);

}
enwinner WhoWonTheGame(short player1WinTimes,short ComputerWinTimes)
{
    if (player1WinTimes>ComputerWinTimes)
    {
       return enwinner::player;
    }
    else if(ComputerWinTimes>player1WinTimes)
    return enwinner::computer;
    else
    return enwinner::draw;
}
stGameResults FillGameResults(int GameRounds,short PlayerWinTimes,
short computerWinTimes,short DrawTimes)
{
    stGameResults GameResults;
    GameResults.GameRounds=GameRounds;
    GameResults.Player1Winnertimes=PlayerWinTimes;
    GameResults.ComputerWinnertimes=computerWinTimes;
    GameResults.DrawTimes=DrawTimes;
    GameResults.Gamewinner=WhoWonTheGame(PlayerWinTimes,computerWinTimes);
    GameResults.WinnerName=WinnerName(GameResults.Gamewinner);
    return GameResults;
    
}
enGamechoice readPlayer1Choice()
{
    short choice =1;
    do
    {
        cout<<"\n Your Choice : [1]:stone ,[2]:paper,[3]:scissors?";
        cin>>choice;
    } while (choice<1||choice>3);
    return (enGamechoice)choice;
    
}

enGamechoice GetComputerChoice()
{
    return (enGamechoice)RandNumber(1,3);
}
stGameResults playGame(short howManyRounds)
{
    stRoundInfo roundinfo;
    short playerWinTimes=0,computerwinstimes=0,Drawtimes=0;
    for (short gameround= 1; gameround <= howManyRounds; gameround++)
    {
        cout <<"\nRound ["<<gameround<<"]begins:\n";
        roundinfo.roundNumber=gameround;
        roundinfo.playerchoice=readPlayer1Choice();
        roundinfo.computerchoice=GetComputerChoice();
        roundinfo.winner=WhowONTheRound(roundinfo);
        roundinfo.winnerName=WinnerName(roundinfo.winner);

        if (roundinfo.winner==enwinner::player)

       playerWinTimes++;
       else if(roundinfo.winner==enwinner::computer)
       computerwinstimes++;
       else
       Drawtimes++;
       PrintRoundResult(roundinfo);
    }
    return FillGameResults(howManyRounds,playerWinTimes,
    computerwinstimes,Drawtimes);

    
}
string tabs(short NumberOfTabs)
{
    string t="";
    for (int i = 1; i < NumberOfTabs; i++)
    {
       t=t+"\t";
       cout<<t;
    }
    return t;
}
void showgameoverscreen()
{
    cout<<tabs(2)<<
    "_____________________________________________________________\n\n";
    cout<<tabs(2)<<"           +++Game Over +++\n";
    cout<<tabs(2)<<
    "______________________________________________________________\n\n";
}
void ShowFinalGameResults(stGameResults gameResults)
{
    cout<<tabs(2)<<"_______________________[Game Results]______________\n\n";
    cout<<tabs(2)<<"Game Rounds        :"<<gameResults.GameRounds<<endl;
    cout<<tabs(2)<<"player 1 won times :"<<gameResults.Player1Winnertimes<<"\n";
    cout<<tabs(2)<<"Computer won times :"<<gameResults.ComputerWinnertimes<<endl;
    cout<<tabs(2)<<"Draw Times         :"<<gameResults.DrawTimes<<"\n";
    cout<<tabs(2)<<"final winner       :"<<gameResults.WinnerName<<endl; 
    cout<<tabs(2)<<
    "______________________________________________________________\n\n";
   SetWinnerScreenColor(gameResults.Gamewinner);
}
short ReadHowManyRounds() 
{ 
    short GameRounds = 1;
     do 
        {   
           cout << "How Many Rounds 1 to 10 ? \n";    
           cin >> GameRounds;   
    
         } while (GameRounds < 1 || GameRounds >10);
             return GameRounds;
} 
void ResetScreen()
 {   
      system("cls");
           system("color 0F");
 }
 void StartGame()
 { 
    char PlayAgain = 'Y';
     do  
       {  
              
         ResetScreen();
        stGameResults GameResults = playGame(ReadHowManyRounds());
        showgameoverscreen();
         ShowFinalGameResults(GameResults);   
      cout << endl <<tabs(3) << "Do you want to play again? Y/N? ";  
         cin >> PlayAgain; 
 
     } while (PlayAgain == 'Y' || PlayAgain == 'y');
     }
     int main()
     {
        srand ((unsigned)time(NULL));
        StartGame();

     }