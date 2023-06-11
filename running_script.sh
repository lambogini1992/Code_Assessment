#Check Argument input is had
if [ -z "$1" ]
  then
    echo "No argument supplied"
    exit
fi

#Intall dependence package
sudo apt-get install build-essential linux-headers-$(uname -r)

#Build linux kernel
make all

#intall Linux kernel
sudo insmod kernel_module.ko

#change permission
sudo chmod 777 /dev/invert_dev

#clear terminal screen
clear

#build application
gcc user_app.c -o user_app

#sleep 1 second
sleep 1

#run application
sudo ./user_app $1

#remove Linux kernel
sudo rmmod kernel_module.ko
#clean output folder
make clean && rm user_app