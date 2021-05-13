#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include "coin.h"
#include <libnotify/notify.h>
#include <iostream>

using namespace std;
// parameters
string userCoin, userCurrency, userCurrencySymbol;
vector<Coin> coinList;

// reads config file
// coins to be listed can be changed in config file
void readSettings() {
  string configOutput;
  ifstream readConfig("settings.conf");
  vector<string> settings;

  while (getline(readConfig, configOutput)) {

    if (configOutput.at(0) == '/') {
      continue;
    } else {
      int pos = configOutput.find("=");
      string varName = configOutput.substr(0, pos);
      if (varName == "currency") {
        userCurrency = configOutput.substr(configOutput.find("=") + 1);
      }
      else if (varName == "currency_symbol") {
        userCurrencySymbol = configOutput.substr(configOutput.find("=") + 1);
      }
      else if (varName == "coins") {
        userCoin = configOutput.substr(configOutput.find("=") + 1);
        stringstream stringSplit(userCoin);
        string temp;
        while(getline(stringSplit, temp, ',')) {
          coinList.push_back(Coin(temp));
        }
      }
    }
  }
}
string createNotification() {
  string coinNotification = "\n\n";
  string fileOutput;
  readSettings();
  replace(userCoin.begin(), userCoin.end(), ',', ' ');
  system(("sh getcoindata.sh " + userCurrency + " " + userCoin).c_str());
   for (int i=0; i < coinList.size(); i++) {
     ifstream coinFile(coinList[i].getName() + ".json");
     while (getline(coinFile, fileOutput)) {
       coinList[i].setPrice(fileOutput);
     }
     coinNotification += "\n" + coinList[i].getName() + ": " + userCurrencySymbol + coinList[i].getPrice();
     coinFile.close();
     system(("rm " + coinList[i].getName() + ".json").c_str());
   }
   return coinNotification;
}

int main(int argc, char *argv[]) {
  string coinNotify;

  coinNotify = createNotification();

  notify_init("Crypto Tracker");
  NotifyNotification* n = notify_notification_new ("Current Prices",
                               (coinNotify).c_str(),
                                0);
  notify_notification_set_timeout(n, 20000); // 20 seconds

  if (!notify_notification_show(n, 0))
  {
      std::cerr << "show has failed" << std::endl;
      return -1;
  }
  return 0;
}
