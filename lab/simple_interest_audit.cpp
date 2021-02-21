
//==============================================================
// Copyright © 2021 Intel Corporation
// Author:Prilvesh Krishna
// Email:prilcool@hotmail.com    
// Linkedin:https://www.linkedin.com/in/prilvesh-k-4349ba54/
// Date:03/02/2020        
// SPDX-License-Identifier: MIT
// =============================================================


// Step 1 Include necessary headers and name spaces 

#include <CL/sycl.hpp>
#include <array>
#include <iostream>
#include <cmath>
#include<iomanip>
#include<limits>
#include <chrono>

using namespace sycl;

//Step 2  in the main program

int main() {
  

    // Declare start time  as we want to track how long it takes  for our program to run.
    
     auto start_time = std::chrono::high_resolution_clock::now();
    
    
    //Declare interger to specify number of records to process  our size is  1 million
    
    
    int N =1000000;
    
    //Declare Interest rates  that you want to apply to an bank account 
    double interest_rate_1=0.01;
    double interest_rate_2=0.02;
    double interest_rate_3=0.03;
    double interest_rate_4=0.04;
    double interest_rate_5=0.05;
    double interest_rate_6=0.07;
  
    //Define  the device that you want to use for processing in our case  CPU   
      // if you select a GPU device than Device: Intel(R) Graphics Gen9 [0x3e96] will process in 5 second.
     queue q(gpu_selector{});
    
    //if you select a CPU device than Device: Intel(R) Xeon(R) E-2176G CPU @ 3.70GHz will process in 5 seconds.
    //to use cpu un comment the below and comment the above.
    //queue q(cpu_selector{});
    
    //Show on screen what device was selected 
    
    std::cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;
    //Allocate the  shared memory space to your  arrays 
    
    double* data = malloc_shared<double>(N, q);
    double* bank_interest_rates = malloc_shared<double>(N, q);
    double* rate_used= malloc_shared<double>(N, q);

//Step 3  iterate and allocate valeus from  1 to 1 million to I
    
    for (int i = 1; i < N; i++) {
        i = i ;
    }
    
    
// Begin paralelle processing using the CPU device 
    
        q.parallel_for(range<1>(N), [=](id<1> i) {
    
            
 // Enter our conditional interest rate  calculation alogrithm .
            
            double apply_interest_rate=0.00;
            data[i] = (double)i + 0.00;
            
            if(i >= 1 && i <= 50000){
               apply_interest_rate=interest_rate_1; 
            }else if(i >=50001 && i <= 100000){
               apply_interest_rate=interest_rate_2; 
            }else if(i >=100001 && i <= 400000){
               apply_interest_rate=interest_rate_3; 
            }else if(i >=400001 && i <= 700000){
               apply_interest_rate=interest_rate_4; 
            }else if (i >=700001 && i <= 1000000){
               apply_interest_rate=interest_rate_5; 
            }else if (i >=1000001){
               apply_interest_rate=interest_rate_6; 
            }
            else{
               apply_interest_rate=0.00; 
            }
            
            
            bank_interest_rates[i] =(double)i* apply_interest_rate;
            rate_used[i]=apply_interest_rate;
            }).wait();

    
    
    //Step 4  Notify user about whats happening and write file parralel_one_million_records_for_audit.txt  to disk 

            std::cout << "Writing Computations to file " << std::endl;
    
            std::ofstream out("parralel_one_million_records_for_audit.txt", std::ios::app);

            for (int i = 1; i < N; i++) {
                out << "Record ID:00" << i << " Original Balance: " << std::fixed << std::setprecision(2) << data[i] << " Addon Interest: " << bank_interest_rates[i] 
                <<" Interest Rate used %:" <<rate_used[i]<<std::endl;
            }

   
           std::cout << "Processing complete you can now refer to the audit file on the left hand side named parallel_interest_on_account_audit.txt " << std::endl;
           auto current_time = std::chrono::high_resolution_clock::now();

           std::cout << "Processing completed in  " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() << " seconds" << std::endl;
    
    //  Release the shared memory space  that you allocated earlier.
    
            free(data, q);
            free(bank_interest_rates, q);
            free(rate_used, q);
    
            return 0;
}








