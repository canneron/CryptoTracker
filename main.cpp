#include <giomm-2.4/giomm.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "coin.h"

using namespace std;

string createNotification(Coin *array, int arrayLen) {
  string coins = "";
  string coinNotification = "\n\n";
  string fileOutput;
   for (int i=0; i < arrayLen; i++) {
     coins.append(array[i].getName() + " ");
   }
   system(("sh getcoindata.sh " + coins).c_str());
   for (int i=0; i < arrayLen; i++) {
     ifstream coinFile(array[i].getName() + ".json");
     while (getline(coinFile, fileOutput)) {
       array[i].setPrice(fileOutput);
     }
     coinNotification += "\n" + array[i].getName() + ":\t" + array[i].getPrice();
     coinFile.close();
   }
   return coinNotification;
}

int main(int argc, char *argv[]) {
  string pricesOutput, input, coinName, coinPrice, coinHistoricPrice, coinPercentageChange, coinNotify;
  int arrLength = argc - 1;
  Coin* coinList = new Coin[arrLength];
  for (int i=1; i < argc; i++) {
    coinList[i-1] = Coin(argv[i]);
  }
  coinNotify = createNotification(coinList, arrLength);
  delete[] coinList;
  auto Application = Gio::Application::create("Crypto Tracker", Gio::APPLICATION_FLAGS_NONE);
	Application->register_application();
	auto Notification = Gio::Notification::create("Current Prices");
	Notification->set_body(coinNotify);
	auto Icon = Gio::ThemedIcon::create("dialog-information");
	Notification->set_icon (Icon);
	Application->send_notification(Notification);
	return 0;

}
