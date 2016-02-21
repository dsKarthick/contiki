#!/bin/bash
GUI=0

LOG_FILES="/home/user/contiki/examples/er-rest/client*"

cmd_clean="make clean"
cmd_make1="make TARGET=cooja sim1.csc"
cmd_make1_nogui="java -mx512m -jar /home/user/contiki/tools/cooja/dist/cooja.jar -nogui=/home/user/contiki/examples/er-rest/1/sim1.csc -contiki=/home/user/contiki"
cmd_make2="make TARGET=cooja sim2.csc"
cmd_make2_nogui="java -mx512m -jar /home/user/contiki/tools/cooja/dist/cooja.jar -nogui=/home/user/contiki/examples/er-rest/2/sim2.csc -contiki=/home/user/contiki"
cmd_make3="make TARGET=cooja sim3.csc"
cmd_make3_nogui="java -mx512m -jar /home/user/contiki/tools/cooja/dist/cooja.jar -nogui=/home/user/contiki/examples/er-rest/3/sim3.csc -contiki=/home/user/contiki"
cmd_connect="echo user | sudo -S make connect-router-cooja"

# eliminar los logs de simulacion
echo "eliminando los logs de simulacion"
rm $LOG_FILES

# inicilizar la simulacion 1
echo "inicilizando la simulacion 1"
cd "/home/user/contiki/examples/er-rest/1"
$cmd_clean &

if [ $GUI -eq 1 ]; then
  $cmd_make1 &
  sleep 5
else
  if [ -f "COOJA.log" ]; then
    rm COOJA.log
  fi
  if [ -f "COOJA.testlog" ]; then
    rm COOJA.testlog
  fi

  $cmd_make1_nogui &
  sleep 10

  if [ -f "COOJA.testlog" ]; then
    mv COOJA.testlog "/home/user/contiki/examples/er-rest/client1.log"
  fi
fi

echo "conectando router"
$cmd_connect &

sleep 3

# inicilizar la simulacion 2
echo "inicilizando la simulacion 2"
cd "/home/user/contiki/examples/er-rest/2"
$cmd_clean &

if [ $GUI -eq 1 ]; then
  $cmd_make2 &
  sleep 5
else
  if [ -f "COOJA.log" ]; then
    rm COOJA.log
  fi
  if [ -f "COOJA.testlog" ]; then
    rm COOJA.testlog
  fi

  $cmd_make2_nogui &
  sleep 15

  if [ -f "COOJA.testlog" ]; then
    mv COOJA.testlog "/home/user/contiki/examples/er-rest/client2.log"
  fi
fi

# inicilizar la simulacion 3
echo "inicilizando la simulacion 3"
cd "/home/user/contiki/examples/er-rest/3"
$cmd_clean &

if [ $GUI -eq 1 ]; then
  $cmd_make3 &
  sleep 5
else
  if [ -f "COOJA.log" ]; then
    rm COOJA.log
  fi
  if [ -f "COOJA.testlog" ]; then
    rm COOJA.testlog
  fi

  $cmd_make3_nogui &
  sleep 20

  if [ -f "COOJA.testlog" ]; then
    mv COOJA.testlog "/home/user/contiki/examples/er-rest/client3.log"
  fi
fi

sleep 20

#inciar el script de scaneo para escribir en BD
echo "iniciando scaneo"
source /home/user/contiki/examples/er-rest/scan.sh