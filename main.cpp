#include <giomm-2.4/giomm.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include "coin.h"

using namespace std;

string userCoin, userCurrency, userCurrencySymbol;
vector<Coin> coinList;

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
  string coinHistoricPrice, coinPercentageChange, coinNotify;

  coinNotify = createNotification();

  auto Application = Gio::Application::create("Crypto Tracker", Gio::APPLICATION_FLAGS_NONE);
	Application->register_application();
	auto Notification = Gio::Notification::create("Current Prices");
	Notification->set_body(coinNotify);
	auto Icon = Gio::ThemedIcon::create("dialog-information");
	Notification->set_icon (Icon);
	Application->send_notification(Notification);
	return 0;

}
