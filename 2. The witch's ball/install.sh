#!/bin/env bash

if [ $EUID != 0 ]; then
    echo "This script needs elevated rights since it has to aquire /var/lib/dpkg/lock-frontend lock"
    echo && echo && echo
    sudo "$0" "$@"
    exit $?
fi

apt-get update && apt-get install -y netpbm