#!/bin/bash

function init_db {
mysql --user=root --password=user parking << EOF
source /home/user/contiki/examples/er-rest/database.sql;
EOF
}

$(init_db)

curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7402:0002:0202&lat=36.5364157&lon=-6.302509900000001&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7403:0003:0303&lat=36.5367649&lon=-6.298593899999999&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7404:0004:0404&lat=36.53686830000001&lon=-6.2987655&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7405:0005:0505&lat=36.5369976&lon=-6.2989211&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7406:0006:0606&lat=36.53707949999999&lon=-6.299071299999999&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7407:0007:0707&lat=36.53721310000001&lon=-6.2992322000000005&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7408:0008:0808&lat=36.5373295&lon=-6.2993932&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7409:0009:0909&lat=36.537432900000006&lon=-6.2995702&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:740a:000a:0a0a&lat=36.5375536&lon=-6.299747199999999&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:740b:000b:0b0b&lat=36.5376571&lon=-6.2999457&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:740c:000c:0c0c&lat=36.53777339999999&lon=-6.3000959&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:740d:000d:0d0d&lat=36.5378639&lon=-6.3002568&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:740e:000e:0e0e&lat=36.5378898&lon=-6.3004875&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:740f:000f:0f0f&lat=36.5378208&lon=-6.3007128&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7410:0010:1010&lat=36.5377303&lon=-6.3009971&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7411:0011:1011&lat=36.53758380000001&lon=-6.3011742&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7412:0012:1212&lat=36.5374415&lon=-6.3013297&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7413:0013:1313&lat=36.53729499999999&lon=-6.3015121&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7414:0014:1414&lat=36.53714850000001&lon=-6.3016677&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7415:0015:1515&lat=36.53701920000001&lon=-6.3018233&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7416:0016:1616&lat=36.536876899999996&lon=-6.301978799999999&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7417:0017:1717&lat=36.53673899999999&lon=-6.3021451&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7418:0018:1818&lat=36.5366226&lon=-6.302273899999999&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7419:0019:1919&lat=36.53648470000001&lon=-6.3024455&status=0" http://localhost/sensors > /dev/null

curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7420:0020:2020&lat=36.5195007&lon=-6.2842923&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7421:0021:2121&lat=36.5195481&lon=-6.2841743&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7422:0022:2222&lat=36.5195869&lon=-6.2840509&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7423:0023:2323&lat=36.5196128&lon=-6.283949&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7424:0024:2424&lat=36.5196472&lon=-6.2838525&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7425:0025:2525&lat=36.5196817&lon=-6.2837398&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7426:0026:2626&lat=36.5197162&lon=-6.2836379&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7427:0027:2727&lat=36.5197507&lon=-6.2835306&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7428:0028:2828&lat=36.5197852&lon=-6.2834126&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7429:0029:2929&lat=36.5198197&lon=-6.2832999&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:742a:002a:2a2a&lat=36.5198542&lon=-6.2831819&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:742b:002b:2b2b&lat=36.51988&lon=-6.2830961&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:742c:002c:2c2c&lat=36.5199102&lon=-6.2829942&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:742d:002d:2d2d&lat=36.5199361&lon=-6.282903&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:742e:002e:2e2e&lat=36.519962&lon=-6.282801&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:742f:002f:2f2f&lat=36.5199921&lon=-6.2827259&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7430:0030:3030&lat=36.520074&lon=-6.2826991&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7431:0031:3031&lat=36.5201646&lon=-6.2827796&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7432:0032:3232&lat=36.5202379&lon=-6.2828332&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7433:0033:3333&lat=36.5203068&lon=-6.2828922&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7434:0034:3434&lat=36.5203801&lon=-6.2829512&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7435:0035:3535&lat=36.5204577&lon=-6.2829942&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7436:0036:3636&lat=36.5205267&lon=-6.2830532&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7437:0037:3737&lat=36.5206043&lon=-6.2830961&status=0" http://localhost/sensors > /dev/null

curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:743e:003e:3e3e&lat=36.5016936&lon=-6.2754786&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:743f:003f:3f3f&lat=36.501547&lon=-6.2753928&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7440:0040:4040&lat=36.501409&lon=-6.2752962&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7441:0041:4141&lat=36.5012538&lon=-6.2752104&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7442:0042:4242&lat=36.5010985&lon=-6.2751245&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7443:0043:4343&lat=36.5009519&lon=-6.2750602&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7444:0044:4444&lat=36.5008398&lon=-6.2749851&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7445:0045:4545&lat=36.5007018&lon=-6.27491&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7446:0046:4646&lat=36.5005725&lon=-6.2748134&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7447:0047:4747&lat=36.5004258&lon=-6.2747276&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7448:0048:4848&lat=36.5003224&lon=-6.2746418&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7449:0049:4949&lat=36.500193&lon=-6.2745667&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:744a:004a:4a4a&lat=36.500055&lon=-6.2745023&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:744b:004b:4b4b&lat=36.4999688&lon=-6.2744486&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:744c:004c:4c4c&lat=36.499848&lon=-6.2743735&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:744d:004d:4d4d&lat=36.49971&lon=-6.274277&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:744e:004e:4e4e&lat=36.499572&lon=-6.2741911&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:744f:004f:4f4f&lat=36.499434&lon=-6.2741053&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7450:0050:5050&lat=36.499296&lon=-6.2740409&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7451:0051:5051&lat=36.4992874&lon=-6.2738264&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7452:0052:5252&lat=36.499365&lon=-6.2736654&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7453:0053:5353&lat=36.4994254&lon=-6.273483&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7454:0054:5454&lat=36.4994944&lon=-6.2733543&status=0" http://localhost/sensors > /dev/null
curl -s -X POST -d "sensorID=fe80:0000:0000:0000:0212:7455:0055:5555&lat=36.4995548&lon=-6.2731934&status=0" http://localhost/sensors > /dev/null

LOG_FILE="/home/user/contiki/examples/er-rest/client.log"

# leemos el archivo en tiempo real
tail -f $LOG_FILE | \
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
      curl -s -X PUT -d "status=${status[1]}" http://localhost/sensors/$ip > /dev/null
    fi
  fi
done