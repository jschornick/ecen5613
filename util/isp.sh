#!/bin/bash -f

FLIP_HOME=/home/jeff/flip.3.2.1/bin
JAVA_HOME=/usr/lib/jvm/java-8-openjdk-i386

export LD_LIBRARY_PATH="$FLIP_HOME:$JAVA_HOME/jre/lib/i386/server"

export PATH="$FLIP_HOME:$PATH"
cd $FLIP_HOME
./batchisp3 $*
