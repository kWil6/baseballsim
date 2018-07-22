#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
 //Compiler version g++ 6.3.0

class player
{
    public:
        int H;
        int BB;
        int PA;
        int TwoB;
        int ThreeB;
        int HR;
        int SB;
        int CS;
        int AB;
        int OneB;
        int OB;
        double avg;
        double singleAvg;
        double doubleAvg;
        double tripleAvg;
        double HRAvg;
        double BBAvg;
        int base;
        string name;
        int ID;
    public:
        player(int H1 = 0, int BB1 = 0, int PA1 = 0, int TwoB1 = 0, int ThreeB1 = 0, int HR1 = 0, int SB1 = 0, int CS1 = 0, string name1 = "Anonymous", int ID1 = 100){
            H = H1; BB = BB1; PA = PA1; TwoB = TwoB1; ThreeB = ThreeB1; HR = HR1; SB = SB1; CS = CS1; name = name1; ID = ID1;
            AB = PA - BB; OneB = H - TwoB - ThreeB - HR; OB = H + BB;
            if (AB == 0) {
              avg = 0;
            } else {
              avg = H/(double) AB;
            }
            if (PA == 0) {
                singleAvg = doubleAvg = tripleAvg = HRAvg = BBAvg = 0;
            } else {
                singleAvg = OneB/(double) PA;
                doubleAvg = TwoB/(double) PA;
                tripleAvg = ThreeB/(double) PA;
                HRAvg = HR/(double) PA;
                BBAvg = BB/(double) PA;
            }
            base = 0;
        }
};
int randEvent(player currPlayer) {
    float rand1 = (double)rand()/(RAND_MAX);
    if (rand1 < currPlayer.singleAvg){
        //cout << currPlayer.name << " singled!" << endl;
        return 1; //Single
    } else if (rand1 < currPlayer.singleAvg + currPlayer.doubleAvg){
        //cout << currPlayer.name << " doubled!" << endl;
        return 2; //Double
    } else if (rand1 < currPlayer.singleAvg + currPlayer.doubleAvg + currPlayer.tripleAvg){
        //cout << currPlayer.name << " tripled!" << endl;
        return 3; //Triple
    } else if (rand1 < currPlayer.singleAvg + currPlayer.doubleAvg + currPlayer.tripleAvg + currPlayer.HRAvg){
        //cout << currPlayer.name << " homered!" << endl;
        return 4; //Home Run
    } else if (rand1 < currPlayer.singleAvg + currPlayer.doubleAvg + currPlayer.tripleAvg + currPlayer.HRAvg + currPlayer.BBAvg){
        //cout << currPlayer.name << " walked!" << endl;
        return 5; //BB
    } else {
        //cout << currPlayer.name << " got out!" << endl;
        return 0; //Out
    }
}

void update(int event, int *outs, player currPlayer, vector <player> &bases, int *runs){
    if (event ==0){
        *outs = *outs + 1;
    } else if (event == 1){
        if (bases[2].name != "Anonymous"){
            //cout << bases[2].name << " scored!" << endl;
            *runs = *runs+1;
            bases[2] = NULL;
        }
        if (bases[1].name != "Anonymous"){
            //cout << bases[1].name << " scored!" << endl;
            *runs = *runs+1;
            bases[1] = NULL;
        }
        bases[1] = bases[0];
        bases[0] = currPlayer;
    } else if (event == 2){
        if (bases[2].name != "Anonymous"){
            //cout << bases[2].name << " scored!" << endl;
            *runs = *runs+1;
            bases[2] = NULL;
        }
        if (bases[1].name != "Anonymous"){
            //cout << bases[1].name << " scored!" << endl;
            *runs = *runs+1;
        }
        if (bases[0].name != "Anonymous"){
            //cout << bases[0].name << " scored!" << endl;
            *runs = *runs+1;
            bases[0] = NULL;
        }
        bases[1] = currPlayer;
    } else if (event == 3){
        if (bases[2].name != "Anonymous"){
            //cout << bases[2].name << " scored!" << endl;
            *runs = *runs+1;
        }
        if (bases[1].name != "Anonymous"){
            //cout << bases[1].name << " scored!" << endl;
            *runs = *runs+1;
            bases[1] = NULL;
        }
        if (bases[0].name != "Anonymous"){
            //cout << bases[0].name << " scored!" << endl;
            *runs = *runs+1;
            bases[0] = NULL;
        }
        bases[2] = currPlayer;
    } else if (event == 4){
        if (bases[2].name != "Anonymous"){
            //cout << bases[2].name << " scored!" << endl;
            *runs = *runs+1;
            bases[2] = NULL;
        }
        if (bases[1].name != "Anonymous"){
            //cout << bases[1].name << " scored!" << endl;
            *runs = *runs+1;
            bases[1] = NULL;
        }
        if (bases[0].name != "Anonymous"){
            //cout << bases[0].name << " scored!" << endl;
            *runs = *runs+1;
            bases[0] = NULL;
        }
        //cout << currPlayer.name << " scored!" << endl;
        *runs = *runs+1;
    } else if (event == 5){
        if (bases[0].name != "Anonymous"){
            if(bases[1].name != "Anonymous"){
                if(bases[2].name != "Anonymous"){
                    //cout << bases[2].name << " scored!" << endl;
                    *runs = *runs+1;
                }
                bases[2] = bases[1];
            }
            bases[1] = bases[0];
        }
        bases[0] = currPlayer;
    }


}
 int main()
 {
    player playerOne (71, 34, 327, 13, 1, 5, 0, 3, "Tucker Barnhardt", 0);
    player playerTwo (99, 73, 422, 21, 2, 9, 1, 0, "Joey Votto", 1);
    player playerThree (115, 26, 389, 21, 0, 16, 2, 1, "Scooter Gennett", 2);
    player playerFour (108, 22, 403, 15, 3, 5, 17, 2, "Jose Peraza", 3);
    player playerFive (93, 40, 348, 17, 2, 19, 1, 0, "Eugenio Suarez", 4);
    player playerSix (60, 30, 329, 15, 0 ,14, 2, 2, "Adam Duvall", 5);
    player playerSeven (68, 34, 332, 7, 5 ,3, 22, 4, "Billy Hamilton", 6);
    player playerEight (74, 24, 299, 15, 0, 12, 3, 1, "Scott Schebler", 7);
    player playerNine (50, 10, 400, 5, 0, 2, 0, 0, "Pitcher", 8);
    vector <player> roster = {playerOne, playerTwo, playerThree, playerFour, playerFive, playerSix, playerSeven, playerEight, playerNine};
    vector <player> bases = {NULL, NULL, NULL};
    int order[9] = {0,1,2,3,4,5,6,7,8};
    float runtotals[362880] = {};
    int currentiteration = 0;
    int sims = 1000;
    while (std::next_permutation(order, order + 9))
    {
        int runs = 0;
        srand(time(NULL));
        for (int i = 0; i < sims; i++){
            int pos =0;
            for (int inning=1;inning<10;inning++){
                int outs =0;
                while(outs<3){
                    player currPlayer = roster[order[pos]];
                    int event = randEvent(currPlayer);
                    update(event, &outs, currPlayer, bases, &runs);
                    if (pos == 8){
                        pos = 0;
                    } else {
                        pos++;
                    }
                }
                bases = {NULL, NULL, NULL};
                //cout << "END OF INNING " << inning <<endl;
            }
        }
            //cout << "END OF GAME" << endl;
            //cout << "RUNS SCORED: " << runs << endl;
        runtotals[currentiteration]= runs/((float) sims);
        currentiteration++;
        if (currentiteration %100 == 0){
            cout << "\r" << currentiteration << " / " << 362880 << " : " << fixed << setprecision(1) << currentiteration/3628.8 << "%";
        }
    }
    cout << endl << "Complete!" << endl;
    float maxruns = 0;
    int maxlineup = 0;
    for (int i = 0; i < 362880; i++){
        if(runtotals[i]>maxruns){
            maxruns = runtotals[i];
            maxlineup = i;
        }
    }
    cout << "Maximum runs per game: " << maxruns << endl;
    std::sort (order,order+9);
    int counter = 0;
    while (std::next_permutation(order, order + 9) && counter < maxlineup){
        counter++;
    }
    cout << "Random lineup: " << runtotals[0] << endl;
    cout << "Best lineup: ";
    for(int i = 0; i<9; i++){
            for(int j = 0; j<9; j++){
                if(roster[j].ID == order[i]){
                    cout << roster[j].name;
                    if (i != 8){
                        cout << ", ";
                    }
                }
            }
    }

 }

