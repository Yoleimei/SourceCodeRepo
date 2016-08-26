sudo insmod ./scull.ko $* || exit 1 
 
rm -r /dev/scull[0-3] 
 
major=$(awk '{if($2=="scull") print $1;}' /proc/devices) 
 
sudo mknod /dev/scull0 c $major 0 
sudo mknod /dev/scull1 c $major 1 
sudo mknod /dev/scull2 c $major 2 
sudo mknod /dev/scull3 c $major 3 
 
sudo chmod 664 /dev/scull[0-3] 
