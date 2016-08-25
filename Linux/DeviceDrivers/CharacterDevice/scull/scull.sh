sudo insmod ./scull.ko $* || exit 1 
 
rm -r /dev/scull[0-3] 
 
major=$(awk "\\$2==\"scull\" {print \\$1}" /proc/devices) 
 
mknod /dev/scull0 c $major 0 
mknod /dev/scull1 c $major 1 
mknod /dev/scull2 c $major 2 
mknod /dev/scull3 c $major 3 
 
chmod 664 /dev/scull[0-3] 
