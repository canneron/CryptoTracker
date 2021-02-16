#!/usr/bin/env bash

currency_flag=false

coinarray=("$@")
for paramOutput in "${coinarray[@]}"
do
  if [ "$currency_flag" = false ]
  then
    currency=${paramOutput}
    currency_flag=true
  else
    curl -sX GET "https://api.coingecko.com/api/v3/simple/price?ids=$paramOutput&vs_currencies=$currency" -H "accept: application/json" | grep -o "$currency.*" | cut -f2- -d: | tr -d '}' > $paramOutput.json
  fi

done
