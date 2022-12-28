# mmWave ns-3 module #

<<<<<<< HEAD
This is an [ns-3](https://www.nsnam.org "ns-3 Website") mmWave module for the simulation
of 5G mmWave cellular networks. A description of this module can be found on [arXiv](https://arxiv.org/abs/1705.02882 "mmwave paper").

The new-handover branch offers integration between LTE and mmWave and dual connectivity features.

## Documentation and examples ##

For a complete description and examples, refer to:

- [End-to-End Simulation of 5G mmWave Networks](https://arxiv.org/abs/1705.02882 "comst paper")
- [A Framework for End-to-End Evaluation of 5G mmWave Cellular Networks in ns-3](https://arxiv.org/abs/1602.06932 "wns3 paper")
- [ Performance Comparison of Dual Connectivity and Hard Handover for LTE-5G Tight Integration](https://arxiv.org/abs/1607.05425 "simutools paper")
- [ns-3 manual](https://www.nsnam.org/docs/manual/html "ns-3 Manual")

## Authors ##

 - Marco Mezzavilla <mezzavilla@nyu.edu>
 - Menglei Zhang <menglei@nyu.edu>
 - Michele Polese <michele.polese@gmail.com>
 - Sourjya Dutta <sdutta@nyu.edu>
 - Russell Ford <russell.ford@nyu.edu>
 - Marco Giordani <m.giordani91@gmail.com>
=======
This is an [ns-3](https://www.nsnam.org "ns-3 Website") module for the simulation
of 5G cellular networks operating at mmWaves. A description of this module can be found in [this paper](https://ieeexplore.ieee.org/document/8344116/ "mmwave paper").

Main features:

* Support of a wide range of channel models, including the model based on 3GPP TR 38.901 for frequencies between 0.5 and 100 GHz. Ray tracing and measured traces can also be used.

* Custom PHY and MAC classes supporting the 3GPP NR frame structure and numerologies.

* Custom schedulers for supporting dynamic TDD formats

* Carrier Aggregation at the MAC layer

* Enhancements to the RLC layer with re-segmentation of packets for retransmissions

* Dual Connectivity with LTE base stations, with fast secondary cell handover and channel tracking

* Simulation of core network elements (with also the MME as a real node)

## Installation
This repository contains a complete ns-3 installation with the addition of the mmwave module. 

Use these commands to download and build `ns3-mmwave`:
```
git clone https://github.com/nyuwireless-unipd/ns3-mmwave.git
cd ns3-mmwave
./waf configure --disable-python --enable-examples && ./waf build
```

## Usage example
You can use the following command to run the `mmwave-simple-epc` example. 
```
./waf --run mmwave-simple-epc
```
Other examples are included in `src/mmwave/examples/`

## Documentation
The documentation of this module is available at [this link](./src/mmwave/doc/mmwave-doc.md).

## Related modules
- MilliCar is an ns-3 module for the simulation of mmWave NR V2X networks. Check [this repo](https://github.com/signetlabdei/millicar) for further details.
- A seperate module is being developed for [mmWave UE Energy Consumption](https://github.com/arghasen10/mmwave-energy "mmwave-energy"). You can use this module for analyzing 
Energy Consumption behaviour of mmwave UE. Check this repository for further details.
- `ns3-mmwave-iab` is an extended version of `ns3-mmWave` adding wireless relaying capabilities to an ns-3 NetDevice, and the possibility of simulating in-band relaying at mmWave frequencies. Check [this repo](https://github.com/signetlabdei/ns3-mmwave-iab) for further details.

## References 
The following papers describe in detail the features implemented in the mmWave
module:
- [End-to-End Simulation of 5G mmWave Networks](https://ieeexplore.ieee.org/document/8344116/ "comst paper") is a comprehensive tutorial with a detailed description of the whole module. We advise the researchers interested in this module to start reading from this paper;
- [Integration of Carrier Aggregation and Dual Connectivity for the ns-3 mmWave Module](https://arxiv.org/abs/1802.06706 "wns3 2018") describes the Carrier Aggregation implementation;
- [Implementation of A Spatial Channel Model for ns-3](https://arxiv.org/abs/2002.09341 "wns3 2020") describes the integration of the spatial channel model based on the 3GPP specifications TR 38.901 V15.0.0;
- [Performance Comparison of Dual Connectivity and Hard Handover for LTE-5G Tight Integration](https://arxiv.org/abs/1607.05425 "simutools paper") describes the Dual Connectivity feature.

These other papers describe features that were implemented in older releases: 
- [ns-3 Implementation of the 3GPP MIMO Channel Model for Frequency Spectrum above 6 GHz](https://dl.acm.org/citation.cfm?id=3067678 "wns3 2017") describes the implementation of the 3GPP channel model based on TR 38.900;
- [Multi-Sector and Multi-Panel Performance in 5G mmWave Cellular Networks](https://arxiv.org/abs/1808.04905 "globecom2018") describes the multi-sector addition to the 3GPP channel model;

If you use this module in your research, please cite:

M. Mezzavilla, M. Zhang, M. Polese, R. Ford, S. Dutta, S. Rangan, M. Zorzi, _"End-to-End Simulation of 5G mmWave Networks,"_ in IEEE Communications Surveys & Tutorials, vol. 20, no. 3, pp. 2237-2263, thirdquarter 2018. [bibtex available here](https://ieeexplore.ieee.org/document/8344116/)

## Future work
We are actively developing new features for the mmWave module, including:
- 3GPP NR beam tracking
- 3GPP NR Integrated Access and Backhaul feature (see [this repo](https://github.com/signetlabdei/ns3-mmwave-iab) for more details)

## About
This module is being developed by [NYU Wireless](http://wireless.engineering.nyu.edu/) and the [University of Padova](http://mmwave.dei.unipd.it/).
This  work  was  supported  in  part by  the  U.S.  Department  of  Commerce  National  Institute  of  Standards  and Technology through the Project “An End-to-End Research Platform for Public Safety  Communications  above  6  GHz”  under  Award  70NANB17H16.



<!-- The new-handover branch offers integration between LTE and mmWave and dual connectivity features.
 -->

## Authors ##

The ns-3 mmWave module is the result of the development effort carried out by different people. The main contributors are: 
- Tommaso Zugno, University of Padova
- Michele Polese, University of Padova
- Matteo Pagin, University of Padova
- Mattia Lecci, University of Padova
- Matteo Drago, University of Padova
- Mattia Rebato, University of Padova
- Menglei Zhang, NYU Wireless
- Marco Giordani, University of Padova
- Marco Mezzavilla, NYU Wireless
- Sourjya Dutta, NYU Wireless
- Russell Ford, NYU Wireless
- Gabriel Arrobo, Intel
>>>>>>> origin

## License ##

This software is licensed under the terms of the GNU GPLv2, as like as ns-3. See the LICENSE file for more details.
<<<<<<< HEAD


## The Network Simulator, Version 3 ##

Table of Contents:
------------------

1) An overview
2) Building ns-3
3) Running ns-3
4) Getting access to the ns-3 documentation
5) Working with the development version of ns-3

Note:  Much more substantial information about ns-3 can be found at
http://www.nsnam.org

1) An Open Source project
-------------------------

ns-3 is a free open source project aiming to build a discrete-event
network simulator targeted for simulation research and education.   
This is a collaborative project; we hope that
the missing pieces of the models we have not yet implemented
will be contributed by the community in an open collaboration
process.

The process of contributing to the ns-3 project varies with
the people involved, the amount of time they can invest
and the type of model they want to work on, but the current
process that the project tries to follow is described here:
http://www.nsnam.org/developers/contributing-code/

This README excerpts some details from a more extensive
tutorial that is maintained at:
http://www.nsnam.org/documentation/latest/

2) Building ns-3
----------------

The code for the framework and the default models provided
by ns-3 is built as a set of libraries. User simulations
are expected to be written as simple programs that make
use of these ns-3 libraries.

To build the set of default libraries and the example
programs included in this package, you need to use the
tool 'waf'. Detailed information on how use waf is 
included in the file doc/build.txt

However, the real quick and dirty way to get started is to
type the command
  ./waf configure --enable-examples
followed by
  ./waf 
(If errors occurred during the build process, type the following command
  CXXFLAGS="-Wall" ./waf  configure --enable-examples
followed by
  ./waf)
in the the directory which contains
this README file. The files built will be copied in the
build/ directory.

The current codebase is expected to build and run on the
set of platforms listed in the RELEASE_NOTES file.

Other platforms may or may not work: we welcome patches to 
improve the portability of the code to these other platforms. 

3) Running ns-3
---------------

On recent Linux systems, once you have built ns-3 (with examples
enabled), it should be easy to run the sample programs with the
following command, such as:

  ./waf --run simple-global-routing

That program should generate a simple-global-routing.tr text 
trace file and a set of simple-global-routing-xx-xx.pcap binary
pcap trace files, which can be read by tcpdump -tt -r filename.pcap
The program source can be found in the examples/routing directory.

4) Getting access to the ns-3 documentation
-------------------------------------------

Once you have verified that your build of ns-3 works by running
the simple-point-to-point example as outlined in 4) above, it is
quite likely that you will want to get started on reading
some ns-3 documentation. 

All of that documentation should always be available from
the ns-3 website: http:://www.nsnam.org/documentation/.

This documentation includes:

  - a tutorial
 
  - a reference manual

  - models in the ns-3 model library

  - a wiki for user-contributed tips: http://www.nsnam.org/wiki/

  - API documentation generated using doxygen: this is
    a reference manual, most likely not very well suited 
    as introductory text:
    http://www.nsnam.org/doxygen/index.html

5) Working with the development version of ns-3
-----------------------------------------------

If you want to download and use the development version 
of ns-3, you need to use the tool 'mercurial'. A quick and
dirty cheat sheet is included in doc/mercurial.txt but
reading through the mercurial tutorials included on the
mercurial website is usually a good idea if you are not
familiar with it.

If you have successfully installed mercurial, you can get
a copy of the development version with the following command:
"hg clone http://code.nsnam.org/ns-3-dev"
=======
>>>>>>> origin
