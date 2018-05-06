#!/bin/bash
#
# bootstrap.sh
#
# This file is specified in the Vagrantfile and is loaded by Vagrant as the
# primary provisioning script on the first `vagrant up` or subsequent 'up' with
# the '--provision' flag; also when `vagrant provision`, or `vagrant reload --provision`
# are used. You can also bring up your environment and explicitly not run provisioners 
# by specifying '--no-provision'.
set -e
DEBIAN_FRONTEND=noninteractive
# By storing the date now, we can calculate the duration of provisioning at the
# end of this script.
start_seconds="$(date +%s)"

sudo apt update && sudo DEBIAN_FRONTEND=noninteractive apt-get -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" dist-upgrade && sudo apt -y autoremove && sudo apt clean

#install git
sudo apt install -y git || echo "Clang installation failed"
echo 'Git installed successfully!'

#install gcc
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt -y install gcc || echo "git installation failed" 
echo 'GCC 7 installed successfully!'

#install valgrind
sudo apt install -y valgrind || echo "valgrind installation failed"
echo 'valgrind installed successfully'

#install flex and bison
sudo apt install -y flex || echo "flex installation failed"
sudo apt install -y bison || echo "bison installation failed"
echo 'flex and bison installed successfully'

#install latest clang version
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
sudo apt-add-repository "deb http://apt.llvm.org/zesty/ llvm-toolchain-zesty-5.0 main"
sudo apt update
sudo apt install -y clang-5.0 || echo "Clang installation failed" 
sudo ln -sf /usr/lib/llvm-5.0/bin/clang /usr/bin/clang
echo 'Clang-5 installed successfully!'

#install SML/NJ
sudo apt install -y smlnj || echo "SML/NJ installation failed" 
echo 'SML/NJ installation successfully!'

#install r
sudo apt install -y r-base || echo "R installation failed" 
echo 'R installed successfully!'

#install vim-gtk and emacs
sudo apt install -y vim-gtk || echo "Vim-gtk installation failed" 
sudo apt install -y emacs || echo "Emacs installation failed" 
echo 'emacs and vim-gtk successfully installed!'

#install go
sudo apt install -y golang-go || echo "go installation failed"
echo 'go installed successfully'

#install spim
wget -O qtspim_9.1.20_linux64.deb "https://downloads.sourceforge.net/project/spimsimulator/qtspim_9.1.20_linux64.deb?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fspimsimulator%2Ffiles%2Fqtspim_9.1.20_linux64.deb%2Fdownload&ts=1518130564"
sudo dpkg -i qtspim_9.1.20_linux64.deb || echo "qtspim installation failed"
echo 'qtspim installed successfully'

#install logisim
sudo apt install -y logisim || echo "logisim installation failed"
echo 'logisim installed successfully'

#install sublime text
sudo add-apt-repository -y ppa:webupd8team/sublime-text-3
sudo apt update
sudo apt install -y sublime-text-installer || echo "Sublime-text installation failed"
echo 'sublime-text successfully installed!'

#install chromium
sudo apt install -y chromium-browser || echo "chromium installation failed"
echo 'chromium successfully installed'

#install ubuntu desktop
sudo apt install -y ubuntu-desktop --no-install-recommends || echo "Desktop environment installation failed"
echo 'Ubuntu desktop successfully installed'

#install gnome terminal and set necessary locale
sudo apt install -y gnuplot || echo "Gnuplot installation failed"
echo 'Gnuplot successfully installed'

#install gnome terminal and set necessary locale
sudo apt install -y gnome-terminal || echo "Terminal installation failed"
echo 'Gnome terminal successfully installed'

sudo update-locale LANG=en_US.UTF-8

sudo apt update && sudo DEBIAN_FRONTEND=noninteractive apt-get -y -o Dpkg::Options::="--force-confdef" -o Dpkg::Options::="--force-confold" dist-upgrade && sudo apt -y autoremove && sudo apt clean

end_seconds="$(date +%s)"
echo "-----------------------------"
echo "Provisioning complete in "$(expr $end_seconds - $start_seconds)" seconds"
