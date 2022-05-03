if [ $1 = "zip" ]; then
  echo Zipping...
  zip cluster.zip -r parallel_code/ serial_code/ img/ simple-jpeg/
elif [ $1 = "send" ]; then
  echo Sending...
  scp cluster.zip kisuleba@login.ifi.uio.no:Documents/IN4200
else
  echo Unknown option $1
fi
