#!/bin/bash

function exec_query {
mysql --user=root --password=user parking << EOF
$query
EOF
}

LOG_FILES="/home/user/contiki/examples/er-rest/client*"

# leemos el archivo en tiempo real
tail -f $LOG_FILES | \
while read line ; do
  # buscamos la linea que contiene INFO|
  echo "$line" | grep "INFO|"
  # comprobamos que es la linea correcta
  if [ $? -eq 0 ]; then
    # dividimos la linea por el caracter |
    IFS='|' read -ra array <<< "$line"

    # descartamos el elemento en 0 (INFO|)
    # en array[1] esta la ip del servidor
    ip=${array[1]}
    # en array[2] estan los datos en json
    data=${array[2]}

    # comprobamos que la linea contenga datos
    if [[ $data != "" ]]; then
      IFS='=' read -ra status <<< "$data"
      # actualizar la informacion del nodo en la base de datos
      query="UPDATE sensors SET status='${status[1]}' WHERE sensorID='$ip'"
      $(exec_query)
    fi
  fi
done