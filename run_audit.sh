#!/bin/bash
source /opt/intel/oneapi/setvars.sh > /dev/null 2>&1
/bin/echo "##" $(whoami) is compiling your interest on account audit program.
dpcpp lab/simple_interest_audit.cpp -o bin/simple_interest_audit -std=c++11
if [ $? -eq 0 ]; then bin/simple_interest_audit; fi

