# Hello World Binding Example
This repository hosts the code for the a sample HelloWorld AGL binding.

# Getting the Source Code
```
git clone --recursive git@github.com:nbobbili-amazon/HelloWorldBinding.git
export MY_PROJECTS_DIR = <Your Project Directory>
pushd $MY_PROJECTS_DIR
git clone --recursive 
```

# On Ubuntu 16.04
### Setup Application Framework

[Set up host AGL host configuration for debian based operating system ](http://docs.automotivelinux.org/docs/devguides/en/dev/reference/host-configuration/docs/1_Prerequisites.html#add-repo-for-debian-distro). Get the AGL debian distro for AGL Master branch by running the following commands.
    
```
export REVISION="FunkyFlounder"
export DISTRO="xUbuntu_16.04"
wget -O - http://download.opensuse.org/repositories/isv:/LinuxAutomotive:/AGL_${REVISION}/${DISTRO}/Release.key | sudo apt-key add -
sudo bash -c "cat >> /etc/apt/sources.list.d/AGL.list <<EOF
#AGL
deb http://download.opensuse.org/repositories/isv:/LinuxAutomotive:/AGL_${REVISION}/${DISTRO}/ ./
EOF"
sudo apt-get update
```

Install the afb-daemon (Binder) used for running the alexa voice agent binding. The binaries will be installed in /opt/AGL folder after running the following command.

```
sudo apt-get install agl-app-framework-binder-dev agl-libmicrohttpd-dev libjson-c-dev libsystemd-dev
```

## Compiling

```
export PKG_CONFIG_PATH=/opt/AGL/lib/pkgconfig
pushd helloworld
mkdir build
pushd build
cmake ..
make autobuild
popd
./conf.d/autobuild/linux/autobuild package
```

## Running
```
export LD_LIBRARY_PATH=/opt/AGL/lib
afb-daemon --port=1111 --name=afb-helloworld --workdir=$MY_PROJECTS_DIR/helloworld/build/package --ldpaths=lib --roothttp=htdocs --token= -vvv
```

# Testing
* The binding can be tested by launching the HTML5 sample application that is bundled with the package in a browser.
The HTML5 app is in htdocs folder.

```
http://localhost:1111
```
