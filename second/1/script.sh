#!/bin/bash
set -e

if [[ $1 == '' ]]; then
	host=localhost;
else
	host=$1;
fi;

if [[ $2 -eq  '' ]]; then
	FR=10;
else
	FR=$2;
fi;

if [[ $3 -eq '' ]]; then
	D=0;
else
	D=$3;
fi;

if [[ $4 -eq '' ]]; then
	S=0;
else
	S=$4
fi;

if [[ $5 -eq '' ]]; then
	X=($(ssh $host "DISPLAY=:$D.$S; export DISPLAY; xwininfo -root | awk '/^.*-geometry.*/ { match(\$2, \"^[0-9]+x\"); print(substr(\$2, RSTART, RLENGTH-1)); }';"));
else
	X=$5;
fi;

if [[ $6 -eq '' ]]; then
	Y=($(ssh $host "DISPLAY=:$D.$S; export DISPLAY; xwininfo -root | awk '/^.*-geometry.*/ { match(\$2, \"x[0-9]+\\+\"); print(substr(\$2, RSTART+1, RLENGTH-2)); }'"));
else
	Y=$6;
fi;

ssh $host "ffmpeg -f x11grab -r $FR -s ${X}x$Y -i :$D.$S -f avi pipe:1"|ffplay -f avi -
