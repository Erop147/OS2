#!/bin/bash

mkfifo p;
./main  1> p;
read fbpid < p;
sleep 10s;
kill -INT -$fbpid;
rm p;
