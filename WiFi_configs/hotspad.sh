sudo apt-get install -y hostapd udhcpd vim
sudo vim /etc/udhcpd.conf
sudo vim /etc/default/udhcpd
 sudo vim /etc/init.d/hostapd
sudo vim /etc/default/hostapd
sudo ifconfig wlan0 192.168.0.1
sudo vim /etc/network/interfaces
sudo vim /etc/hostapd/hostapd.conf
sudo sh -c "echo 1 > /proc/sys/net/ipv4/ip_forward"
sudo iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
sudo iptables -A FORWARD -i eth0 -o wlan0 -m state --state RELATED,ESTABLISHED -j ACCEPT
sudo iptables -A FORWARD -i wlan0 -o eth0 -j ACCEPT
sudo service hostapd start
sudo service udhcpd start
sudo update-rc.d hostapd enable
sudo update-rc.d hostapd defaults
sudo update-rc.d udhcpd enable
sudo hostapd -dd /etc/hostapd/hostapd.conf # debug
sudo ifdown wlan0 && sudo ifup wlan0
