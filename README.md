# Banking & Financial Audits through parallel computing DPC++ 

Banking &amp; Financial Audits through parallel computing DPC++ ( Process Millions of records in seconds)

Design scalable and flexible  parallel data processing and audit systems with Intel DPC++.  

We show you how you can utilize DPC++  to  efficiently process millions of records in parallel in under 60 seconds .

Eg :Auditing interest  paid to each user based on the users dynamic account  balances . 


Entry for codeproject.com and INTEL Devmesh  DPC++



## Usage instructions :
Copy the entire structure including all files to  Intel dev cloud .

Ensure that the  Python 3.7 (Intel OneApi)  kernal is running

Ensure that you are using the q file ,run_audit.sh and Makefile that is provided with this sourcecode.

Ensure that file exist in  lab/simple_interest_audit.cpp


Run the following  jupyter notebook  Interest-on-account-audit-onemillion_records.ipynb

## Than Run  the following command
! chmod 755 q; chmod 755 run_audit.sh;if [ -x "$(command -v qsub)" ]; then ./q run_audit.sh; else ./run_audit.sh; fi 


On successfull run you would have processed  simple interest calculations on  One million records  at around  4 to  6 seconds  
This same calulation in php or msql will take ages to complete :)

You should be able to download the file containing the out put from the left hand side in jupyter notebook  named  parallel_interest_on_account_audit.txt 
containing 1 million records at around 180 mb .

![alt text](https://raw.githubusercontent.com/prilcool/Intel-devmesh-codeproject-one/main/Assets/out.PNG)

