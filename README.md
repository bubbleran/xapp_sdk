# BubbleRAN O-RAN xApp SDK

[![O-RAN Compatible](https://img.shields.io/badge/O--RAN_Compatible-v2.1-green)](https://www.o-ran.org)
[![License](https://img.shields.io/badge/License-Apache_2.0_With_SDK_Addendum-blue.svg)](LICENSE)

The BubbleRAN xApp SDK enables development of O-RAN compliant near-real-time RAN applications. 
This repository includes both the SDK framework (Apache 2.0 + Addendum) and sample xApps (Apache 2.0).

## Key Features
- 🚀 Production-grade xApp SDK and an Open Source xApp samples
- 📡 Supports O-RAN E2 interface and KPM, RC, and CCC E2SM
- 🧩 Modular architecture for service models
- 🧪 Pre-validated with BubbleRAN Compatibility Test Suite
- ☁️ Cloud-native deployment with BubbleRAN MX-ORS and MX-PDK products

## Directory Structure

```bash

xapp_sdk/
├── LICENSE              # Apache 2.0 with SDK Addendum
├── NOTICES              # Attribution file
├── COMPLIANCE/
│   ├── BR-CTS.md        # Test suite documentation
│   └── SPECIFICATIONS.md # O-RAN interface details
├── CONTRIBUTING.md      # Contribution guidelines
├── README.md            # Revised documentation
├── conf/
├── include/
├── lib/
└── src/

```


##License Structure

| Software  | License |
| ------------- |:-------------|
| xApp SDK				   | BubbleRAN Software License |
| BubbleRAN xApps		    | Apache 2.0 + Addendum	 |
| 3rd Party xApps			| Apache 2.0 + Addendum  | 
| Documentation				| CC-BY-4.0	Guides, specifications, and examples | 

Important: When building xApps using this SDK, your application code can use Apache 2.0 + Addendum, but must agree with the xApp SDK License.

## xApp SDK Source Code
### Getting stated

1. Install common dependencies in Ubuntu:  (at least python3.8)

```
sudo apt install libsctp-dev python3 cmake-curses-gui python3-dev pkg-config libconfig-dev libconfig++-dev python3-pip
```

2. Install MySQL as a storage for xApps:

```
sudo apt install libmysqlclient-dev mysql-server
```

3. Install python packages

```
pip3 install tabulate
```

## Build and install

List of options in CMakeList:

* XAPP_DB=SQLITE3_XAPP/MYSQL_XAPP/NONE_XAPP (NONE_XAPP by default)

```
mkdir build

cd build

cmake -D{your options} ..

make -j

sudo make install

sudo ldconfig

```

## Run the xApp (i.e helloworld in c)

```
./src/dev/c/hw -c ../conf/default.conf
```

## Run the xApp (i.e helloworld in python)

```
cd build/src/usr/python3 

python3 mntr.py -c ../../../conf/default.conf
```


