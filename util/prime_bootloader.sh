#!/bin/bash

# The Atmel BatchISP program often has trouble synchronizing with the AT89C51,
# where the bootloader apparently doesn't respond during auto baud rate configuration.
#
# If we prime the serial port by waiting for the a successful negotiation, the
# ISP works more consistently.
#
# At worst case, even if flashing fails, it takes at most two attempts with
# priming.

SERIAL=${1:-/dev/ttyS1}

cat ${SERIAL} >/tmp/foo &
RD_PID=$!

sleep 0.1
echo -n U >${SERIAL}
while :; do
    echo -n Waiting for U...
    U=$(cat /tmp/foo)
    if [ -z $U ]; then
        echo resending.
        echo -n U >${SERIAL}
        sleep 0.2
    else
        echo got it!
        kill ${RD_PID}
        #sleep 0.2
        exit
    fi
done
