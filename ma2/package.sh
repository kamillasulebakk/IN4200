if [ $1 = "zip" ]; then
  echo Zipping...
  zip cluster.zip -r parallel_code/ serial_code/ img/ simple-jpeg/
elif [ $1 = "send" ]; then
  echo Sending...
  scp cluster.zip kisuleba@login.ifi.uio.no:Documents/IN4200
elif [ $1 = "deliver" ]; then
  folder_name="IN4200_Oblig2_15438"
  if [ -d $folder_name ]; then
    echo Deleting folder $folder_name
    rm -r $folder_name/
  fi
  echo Creating delivery folder...
  mkdir $folder_name
  cp -r README.md serial_code/ parallel_code/ img/ $folder_name/
  if [ -f $folder_name.zip ]; then
    echo Deleting old zip file
    rm $folder_name.zip
  fi
  echo Zipping...
  zip -r $folder_name.zip $folder_name
else
  echo Unknown option $1
fi
