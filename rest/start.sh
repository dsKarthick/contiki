#!/bin/bash
GUI=1

cmd_clean="make clean"
cmd_make="make TARGET=cooja sim.csc"
cmd_make_nogui="java -mx512m -jar /home/user/contiki/tools/cooja/dist/cooja.jar -nogui=/home/user/contiki/examples/rest/sim.csc -contiki=/home/user/contiki"
cmd_connect="echo user | sudo -S make connect-router-cooja"


# inicilizar la simulacion 1
echo "inicilizando la simulacion "
cd "/home/user/contiki/examples/rest"
$cmd_clean &

if [ $GUI -eq 1 ]; then
  $cmd_make &
  sleep 20
else
  if [ -f "COOJA.log" ]; then
    rm COOJA.log
  fi
  if [ -f "COOJA.testlog" ]; then
    rm COOJA.testlog
  fi

  $cmd_make_nogui &
  sleep 20

  if [ -f "COOJA.testlog" ]; then
    mv COOJA.testlog "/home/user/contiki/examples/rest/client.log"
  fi
fi

echo "conectando router"
$cmd_connect &y