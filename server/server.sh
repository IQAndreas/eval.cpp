#!/bin/bash

# Run this with
#  $ tcpserver 0 9999 server/server.sh
# You can then connect to it with
#  $ nc 127.0.0.1 9999

echo "New connection from $TCPREMOTEIP:$TCPREMOTEPORT ($TCPREMOTEHOST)" 1>&2;

#BANNER=server/banner.txt
BANNER=server/banner-small.txt

# Show banner
IFS=$'\n'
for line in $(cat $BANNER)
do
	echo -e "$line";
done

mkdir -p server/logs;
LOGFILE=server/logs/$(date +"%Y%m%d-%H%M%S-%N");

VERSION=$(git describe);

echo "VERSION: eval-test $VERSION" >> $LOGFILE;
echo "LOCAL: $TCPLOCALIP:$TCPLOCALPORT ($TCPLOCALHOST)" >> $LOGFILE;
echo "REMOTE: $TCPREMOTEIP:$TCPREMOTEPORT ($TCPREMOTEHOST)" >> $LOGFILE;
echo "CONNECTION: $PROTO $TCPREMOTEINFO" >> $LOGFILE;
echo "    " >> $LOGFILE;

# Start the server, redirecting stderr back to the user
#  rather than to the server console.
#server/eval-server 2>&1 | tee -a $LOGFILE;
server/eval-server "$LOGFILE" 2>&1;

