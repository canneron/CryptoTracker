#!/usr/bin/env bash

coinarray=("$@")
for coin in "${coinarray[@]}"
do
  curl -sX GET "https://api.coingecko.com/api/v3/simple/price?ids=$coin&vs_currencies=usd" -H "accept: application/json" | grep -o "usd.*" | cut -f2- -d: | tr -d '}' >> $coin.json

done
