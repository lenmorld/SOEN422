#!/bin/bash
if [ "$EUID" -ne 0 ]
  then echo "Please run this script as root"
  exit
fi
echo ==== Preparing SOEN422 Embedded Environment... ====
echo
echo ==== Adding necessary configuration for internet use... ====
/sbin/route add default gateway 192.168.7.1
echo "nameserver 8.8.8.8" >> /etc/resolv.conf
echo 
echo ==== Updating apt repositories, performing basic upgrades and updating time... ====
apt-get update
apt-get install ntpdate -y
ntpdate pool.ntp.org
apt-get upgrade -y
echo 
echo ==== Now updating and installing Python and Ruby... ====
apt-get install build-essential python-dev python-setuptools python-pip python-smbus g++ curl ruby -y
echo 
echo ==== Now updating the device tree compiler... ====
wget -c --no-check-certificate https://raw.githubusercontent.com/RobertCNelson/tools/master/pkgs/dtc.sh
chmod +x dtc.sh
./dtc.sh
echo 
echo ==== Now installing device tree overlays... ====
git clone https://github.com/beagleboard/bb.org-overlays
cd ./bb.org-overlays
./install.sh
cd ..
echo 
echo ==== Now installing Python and Ruby libraries for device... ====
gem install beaglebone
easy_install -U distribute
pip install Adafruit_BBIO
echo 
echo ==== Cleaning up... ====
rm dtc.sh
rm -rf git
rm -rf build
rm -rf bb.org-overlays
exit
