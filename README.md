# BubbleRAN O-RAN xApp SDK

[![O-RAN Compatible](https://img.shields.io/badge/O--RAN_Compatible-v2.1-green)](https://www.o-ran.org)
[![License: AGPL v3](https://img.shields.io/badge/License-AGPL_v3-blue.svg)](https://spdx.org/licenses/AGPL-3.0.html)

The BubbleRAN xApp SDK enables development of O-RAN compliant near-real-time RAN applications. 
This repository includes both the SDK framework and xApps, licensed under the [GNU Affero General Public License v3.0 or later](https://spdx.org/licenses/AGPL-3.0.html) (AGPL-3.0-or-later).

## Key Features
- 🚀 Production-grade xApp SDK and an Open Source xApp samples
- 📡 Supports O-RAN E2 interface and KPM, RC, and CCC E2SM
- 🧩 Modular architecture for service models
- 🧪 Pre-validated with BubbleRAN Compatibility Test Suite
- ☁️ Cloud-native deployment with BubbleRAN MX-ORS and MX-PDK products

## Directory Structure

```bash

xapp_sdk/
├── LICENSE              # GNU AGPL v3.0
├── NOTICES              # Attribution file
├── CONTRIBUTING.md      # Contribution guidelines
├── README.md            # Revised documentation
├── conf/
├── include/
├── lib/
└── src/

```

## BubbleRAN Compatibility Test Suites (CTR)

|Badge	| Requirements| 
| ------------- |:-------------|
| [![E2AP](https://img.shields.io/badge/Compliance-Basic-yellow)](https://www.o-ran.org)	      | **CTR-Basic:** Core E2AP tests passed |
| [![E2SM-1](https://img.shields.io/badge/Compliance-Advanced-orange)](https://www.o-ran.org) 	| **CTR-Advanced:** E2AP + 1 Service Model |
| [![E2SM-ALL](https://img.shields.io/badge/Compliance-Full-green)](https://www.o-ran.org)    	| **CTR-Full:** All Service Models validated | 


## License Structure

| Software  | License |
| ------------- |:-------------|
| xApp SDK				    | [AGPL-3.0-or-later](https://spdx.org/licenses/AGPL-3.0.html) |
| BubbleRAN xApps		  | [AGPL-3.0-or-later](https://spdx.org/licenses/AGPL-3.0.html) |
| 3rd Party xApps			| [AGPL-3.0-or-later](https://spdx.org/licenses/AGPL-3.0.html)  | 
| Documentation				| [CC-BY-4.0](https://creativecommons.org/licenses/by/4.0/deed.en)	Guides, specifications, and examples | 

Important: xApps built with (linked against) this SDK are covered works under the AGPL-3.0-or-later and must be distributed under compatible terms, including making the corresponding source available to users interacting with them over a network.

Files inherited from the OpenAirInterface FlexRIC project keep their original header and remain licensed under the [OAI Public License v1.1](http://www.openairinterface.org/?page_id=698). Each file states its license in its header.

## xApp SDK Source Code
### Getting stated

1. Install common dependencies in Ubuntu:  (at least python3.8)

```
sudo apt install libsctp-dev python3 cmake-curses-gui python3-dev pkg-config libconfig-dev libconfig++-dev python3-pip
```

2. Install python packages

```
pip3 install tabulate
```

## Build and install

List of options in CMakeList:

* XAPP_DB=VICTORIAMETRICS_XAPP/NONE_XAPP (NONE_XAPP by default)

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
./src/dev/c/hw ../conf/xapp.yaml
```

## Run the xApp (i.e helloworld in python)

```
cd build/src/usr/python3 

python3 mntr.py ../../../conf/xapp.yaml
```


