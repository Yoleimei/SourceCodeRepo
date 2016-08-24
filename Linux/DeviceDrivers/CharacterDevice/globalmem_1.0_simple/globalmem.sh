sudo insmod globalmem.ko && ( \
	sudo mknod /dev/globalmem0 c 248 0 && \
	sudo chmod 666 /dev/globalmem0 && \
	sudo echo 'hello' > /dev/globalmem0 && \
	sudo cat /dev/globalmem0; \
	sudo mknod /dev/globalmem1 c 248 1 && \
	sudo chmod 666 /dev/globalmem1 && \
	sudo echo 'nihao' > /dev/globalmem1 && \
	sudo cat /dev/globalmem1; \
)
sudo rm /dev/globalmem*
sudo rmmod globalmem

