# Crypto Tracker

Crypto Tracker is a linux based small application [powered by CoinGecko API](https://www.coingecko.com/en/api#explore-api) that will create a notification on KDE Plasma with the current prices of your chosen cryptocurrencies.

## Dependencies
If GCC is not already installed it will be required.

You will need to have libnotify installed

Arch : ```sudo pacman -S libnotify```

Ubuntu: ```sudo apt-get install libnotify-dev```

## Installation

Pull down this repo and compile with this command:

`` g++ main.cpp -o cryptotracker `pkg-config --cflags --libs libnotify` ``

## Usage

You can edit the coins you want to show in settings.conf.

Example:

```coins=bitcoin,dogira,visor```

Will pull down the prices for bitcoin, dogira and visor.
The currency the prices will be displayed in can also be shown here.

There are a few options on how to run the application
1) The compiled file can be run directly with ./cryptotracker
2) A preferrable option may be to add this command to a daemon that runs on startup or your chosen time.
3) Create an alias and add it to your start up script if you have one

## License

[GPLv3](https://www.gnu.org/licenses/gpl-3.0.html)
