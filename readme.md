# R-Type (Clone of official Game)

## Unix instructions

```bash
mkdir build && cd build
conan install .. --build=missing
cmake -G "Unix Makefiles" && cmake --build .
cd ..
```

## Windows instructions
```bash
mkdir build && cd build
conan install .. -s build_type=Debug -s arch=x86 --build=missing
cmake -G "[your VS generator here]" && cmake --build .
cd ..
```

## USAGE

### Server

>First, build monster library and make sure she is inside ***.monsters*** folder.

To run a server:
```bash
./r-type_server
```

> In this case the server will run on the port ***7777***

To run multiple ***Multi threaded*** servers:
```bash
./r-type_server -n n(number of servers)
```

> In this case the server will run on Ports ***7777*** through ***7777 + n-1***

Please note that running too many servers will slow down your computer.

### Client

```bash
./r-type_client
```

## Documentations

| Type  | Document |
| :-------------: |:-------------:|
| ***RFC Protocol***    | [.txt](https://github.com/EpitechPromo2024/B-CPP-501-LIL-5-1-rtype-adrien.courbebaisse/blob/master/documentations/rfc_protocol.txt)     |
| ***UML***             | [.txt](https://docs.google.com/document/d/1cLxam0mOCrNaI-JSNV2BMfq5Yy6UC-hQ_rNLxHUfj1I/edit?usp=sharing)     |

## Screenshots

<p align="center">
  <img src="/documentations/examples/menu.png">
  <img src="/documentations/examples/lobby.png">
  <img src="/documentations/examples/connection.png">
</p>

## Authors 

> 👤 **Leo Fabre**

* Github: [@LeoFabre](https://github.com/LeoFabre)
* LinkedIn: [@leo-fabre](https://linkedin.com/in/leo-fabre)

> 👤 **Adrien Courbebaisse**

* Github: [@adriencourbebaisse](https://github.com/adriencourbebaisse)
* LinkedIn: [@adrien-courbebaisse](https://fr.linkedin.com/in/adrien-courbebaisse-708607212)

> 👤 **Achille Bourgault**

* Github: [@achillebourgault](https://github.com/achillebourgault)
* LinkedIn: [@achille-bourgault](https://fr.linkedin.com/in/achille-bourgault-266514177)

> 👤 **Frédéric Lawecki--Walkowiak**

* Github: [@fredericlw](https://github.com/fredericlw)
* LinkedIn: [@frederic-lawecki-walkowiak](https://www.linkedin.com/in/frederic-lawecki-walkowiak/)