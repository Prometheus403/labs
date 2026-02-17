#!/bin/bash
echo "       System Information"

echo
echo "CPU Model:"
lscpu | grep "Model name"

echo
echo "CPU Architecture:"
lscpu | grep "Architecture"

echo
echo "CPU ID (if available):"
grep -m 1 "Serial" /proc/cpuinfo || echo "Not available on this system"

echo
echo "Total Memory:"
free -h | grep Mem

echo
echo "Disk Information:"
lsblk -o NAME,SIZE,TYPE,MOUNTPOINT

echo
echo "Disk Serial Number:"
sudo lsblk -o NAME,SERIAL 2>/dev/null || echo "Requires sudo or not available"

echo
echo "MAC Address:"
ip -brief link | grep -v LOOPBACK

echo
echo "OS Version:"
cat /etc/os-release | grep PRETTY_NAME

echo
echo "Kernel Version:"
uname -r
