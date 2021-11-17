#!/bin/bash

rm -rf *~
rm -rf Read_C_ACLiC_dict_rdict.pcm  Read_C.d  Read_C.so

root -l -b -q Read.C+(\"data/Proton_100PeV_33km_85.root\",\"hist/hist_Proton_100PeV_33km_85.root\")
root -l -b -q Read.C+(\"data/Proton_100PeV_525km_67_7.root\",\"hist/hist_Proton_100PeV_525km_67_7.root\")



