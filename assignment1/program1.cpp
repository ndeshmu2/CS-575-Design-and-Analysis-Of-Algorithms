
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <map>

using namespace std;

//creating classes for all data set values.

class BaseballCard{
public:
  string baseballPlayer;
  int costOfMarket;
  int costListed;
};

class Data{
public:
  int num;
  int totalWeight;
  vector<BaseballCard> c1;
};

class FinalOutput{
public:
  int lastProfit;
  int priceListCards;
  int boughtCards;
  double secs;
  int maxprofit;
  string attr1;
  int attr2;
};

vector<BaseballCard> finalvector1;
std::vector<int> my_v1;
FinalOutput computeMaxProfit(Data a, int weight){
    int s = clock();
    weight = a.totalWeight;
    int n = a.c1.size();
    int totalprice = 0;
    int i = 0;
    while(i < n){
        totalprice += a.c1[i].costListed;
        i++;
    }

    vector<int> subset(n+1);
    int maxProfit = 0;
    vector<BaseballCard> finalvector;
    int boughtCards = 0;
    int cardnumber;
    int highestprofit = 0;

    for (int i = 1; i <= n; i++) {
        subset[i] = i-1;
    }

    for (int i = 0; i < (1<<n); i++){
        vector<BaseballCard> currvector;
        int currProfit = 0;
        int currprice = 0;
        for (int j = 0; j < n; j++) {
        if (i & (1<<j)) {
            currvector.push_back(a.c1[j]);
            currProfit += a.c1[j].costOfMarket - a.c1[j].costListed;
            currprice += a.c1[j].costListed;
        }
        }
        if (currprice <= weight && currProfit > maxProfit) {
        maxProfit = currProfit;
        finalvector = currvector;
        boughtCards = currvector.size();
        cardnumber = i;
        highestprofit = 0;
        for (int j = 0; j < boughtCards; j++) {
            int currprofit = currvector[j].costOfMarket - currvector[j].costListed;
            if (currprofit >= highestprofit) {
            highestprofit = currprofit;
            cardnumber = j;
            }
        finalvector1 = finalvector;
        }
        }
    }

    FinalOutput o;
    o.boughtCards = boughtCards;
    o.lastProfit = maxProfit;
    o.priceListCards = n;
    o.maxprofit = highestprofit;
    o.attr1 = a.c1[cardnumber].baseballPlayer;
    o.attr2 = a.c1[cardnumber].costListed;

    int s1 = clock();
    o.secs = (s1 - s) / double(CLOCKS_PER_SEC) * 1000;

    return o;
}

int num1 = 0;

int main(int argc, char *argv[]){

    int n1 = 0;
    int cardnumber;
    int w1;
    if (argc != 5){
        cout << "You are entering incorrect input" << endl;
        exit(1);
    }
    else if ((strcmp(argv[1], "-m") != 0) || (strcmp(argv[3], "-p") != 0)){
        cout << "The flags you entered are incorrect" << endl;
        exit(1);
    }

    ifstream marketPriceFile(argv[2]);
    ifstream priceFile(argv[4]);

    if (!(marketPriceFile.is_open() && priceFile.is_open())){
        cout << "The entered input files are not to be found" << endl;
        exit(1);
    }
    
    map<string, int> market;
    map<int, Data> inputmap;
    vector<FinalOutput> outputvector;

    while (marketPriceFile >> n1){
        int i = 0;
        while (i < n1){
        i++;
        // card c;
        string cardname;
        int mktprice;
        marketPriceFile >> cardname;
        marketPriceFile >> mktprice;
        market[cardname] = mktprice;
        }
    }
    marketPriceFile.clear();
    marketPriceFile.close();

    int saleslist;
    int inputbudget;
    string playercardname;
    int playerprice;
    int index = 1;
    while (priceFile >> saleslist >> inputbudget){
        Data a;
        int i = 0;
        a.num = saleslist;
        a.totalWeight = inputbudget;
        inputbudget = w1;
        my_v1.push_back(saleslist);
        while (i < saleslist){
            i++;
            priceFile >> playercardname;
            priceFile >> playerprice;
            if (market.find(playercardname) != market.end()){
                BaseballCard c;
                c.baseballPlayer = playercardname;
                c.costOfMarket = market[playercardname];
                c.costListed = playerprice;
                a.c1.push_back(c);
            }
            // else{
            //     cout << "Error, cardname is not present in market_price file" << endl;
            // }
        }
        inputmap[index] = a;
        index++;
    }

    priceFile.clear();
    priceFile.close();
    
    
    ofstream output;
    output.open("output.txt");
    a:
    for (auto const& [key, value] : inputmap){
        FinalOutput o = computeMaxProfit(value, w1);
        if(o.lastProfit == 0){
            output << o.lastProfit;
        }
        else{
            //for(int k = 0; k < finalvector1.size(); k++){
                //int num1 = 0;
                //for(num1; num1 <= my_v1.size();num1++){
            if(o.priceListCards < my_v1[num1]){
                output << "Error: cardname not present in market file" << endl;
                num1 += 1;
                goto a;
            }
            output << o.priceListCards << " " 
            << o.lastProfit << " " 
            << o.boughtCards << " " 
            << o.secs << endl;
            int j = 0;
            //for (int j = 0; j < finalvector1.size(); j++)
            while(j < finalvector1.size()){
                output << finalvector1[j].baseballPlayer << endl;
                j++;
            }
            num1 += 1;    
        }
                // output << o.inputcards << " " 
                // << o.profitoutcome << " " 
                // << o.numcardspurchased << " " 
                // << o.time << endl;
                // int j = 0;
                // //for (int j = 0; j < finalvector1.size(); j++)
                // while(j < finalvector1.size()){
                //     output << finalvector1[j].playerName << endl;
                //     j++;
                // }
    }
    output.close();
}