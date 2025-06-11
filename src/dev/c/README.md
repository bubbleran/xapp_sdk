# xApp for developer

## Commands to compile xapp

1. Example

```
gcc xapp_oran_moni.c libe42_xapp.a -DKPM_V3_00 -DE2AP_V3 -lconfig -lpthread -lm -lsctp

```

2. Running

2.1 Command
```
./a.out
```

2.1 How to run with config file

```
Usage: [options]

    General options:
  -h         : print usage
  -c         : path to the config file

Ex. ./a.out -p /usr/local/lib/flexric/ -c /usr/local/etc/flexric/ric.conf
```

