#!/bin/bash
LOG_FILES="/home/user/contiki/examples/er-rest/client*"

# eliminar los logs de simulacion
echo "eliminando los logs de simulacion"
rm $LOG_FILES

cmd_clean="make clean"
cmd_make1="make TARGET=cooja sim1.csc"
cmd_make2="make TARGET=cooja sim2.csc"
cmd_make3="make TARGET=cooja sim3.csc"
cmd_connect="echo user | sudo -S make connect-router-cooja"

# inicilizar la simulacion 1
echo "inicilizando la simulacion 1"
cd "/home/user/contiki/examples/er-rest/1"
$cmd_clean &
$cmd_make1 &

sleep 6

# inicilizar la simulacion 2
echo "inicilizando la simulacion 2"
cd "/home/user/contiki/examples/er-rest/2"
$cmd_clean &
$cmd_make2 &

sleep 6

# inicilizar la simulacion 3
echo "inicilizando la simulacion 3"
cd "/home/user/contiki/examples/er-rest/3"
$cmd_clean &
$cmd_make3 &

sleep 6

echo "conectando router"
$cmd_connect &

sleep 3

#inciar el script de scaneo para escribir en BD
echo "iniciando scaneo"
source /home/user/contiki/examples/er-rest/scan.sh