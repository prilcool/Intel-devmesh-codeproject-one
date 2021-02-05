
//==============================================================
// Copyright © 2021 Intel Corporation
// Author:Prilvesh Krishna
// Email:prilcool@hotmail.com    
// Linkedin:https://www.linkedin.com/in/prilvesh-k-4349ba54/
// Date:03/02/2020        
// SPDX-License-Identifier: MIT
// =============================================================



#include<CL/sycl.hpp>
#include<array>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<limits>
#include <chrono>



using namespace sycl;

int main() {
    auto start_time = std::chrono::high_resolution_clock::now();

    int N = 5;
    queue q(cpu_selector{});
    std::cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;
    double*data = malloc_shared<double>(N, q);
    double bank_balances[]={100.95,25,0.50,5.99};
    double*bank_interest_rates= malloc_shared<double>(N, q);
    double*accumulated_rates=malloc_shared<double>(N, q);
    for (int i =0; i < 5; i++) {i=bank_balances[i];}
    
    std::cout << "Parallel data processing initialized" << std::endl;
    q.parallel_for(range<1>(N), [=](id<1> i) {
        data[i]=bank_balances[i]+2.00; 
        bank_interest_rates[i]=data[i]*0.20;
        accumulated_rates[0]=accumulated_rates[0]+bank_interest_rates[i];
        
    }).wait();

    std::cout << "Proceeding to output results to csv file " << std::endl;
    std::ofstream out("parallel_interest_on_account_audit.txt", std::ios::app);
    
   
    out << "Record ID,Original Balance,Addon Interest "<< std::endl; 
    for (int i = 0; i < N; i++) {
    out << i << "," << std::fixed << std::setprecision(2) << data[i] << "," << bank_interest_rates[i] << std::endl;
    }
  
     std::cout << "Processing complete you can now refer to the audit file on the left hand side named parallel_interest_on_account_audit.csv " << std::fixed << std::setprecision(2) << accumulated_rates[0] << std::endl;
     auto current_time = std::chrono::high_resolution_clock::now();

     std::cout << "Processing completed in  " << std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count() << " seconds" << std::endl;

     free(data, q);
     free(bank_interest_rates, q);
     free(accumulated_rates, q);
    return 0;
}







