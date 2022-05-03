if [ $1 = "zip" ]; then
  echo Zipping...
  zip cluster.zip parallel_code/ parallel_code/*.c parallel_code/*.h parallel_code/Makefile serial_code/ serial_code/*.c serial_code/*.h serial_code/Makefile img/*
elif [ $1 = "send" ]; then
  echo Sending...
  scp cluster.zip kisuleba@login.ifi.uio.no:Documents/IN4200
else
  echo Unknown option $1
fi
