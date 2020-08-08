//
//  main.cpp
//  BarberAppointmentScheduler
//
//  Created by Yash Arora on 08/08/20.
//  Copyright © 2020 Yash Arora. All rights reserved.
//


/*
 A barber has many appointments in a day, each appointment has different cost associated with it
 barber can choose which one to pick and drop, the appointments time cannot overlap
 schedule the appointments in a way to achieve maximum profit
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct appointment{
    int startTime,endTime,cost;
};

bool appointmentComporator(appointment apt1,appointment apt2)
{
    return (apt1.endTime < apt2.endTime);
}
int getLastNonConflictiongAptmnt(vector<appointment> &apntmnt, int pos)
{
    for(int j=pos-1;j>=0;j--)
    {
        if(apntmnt[pos].startTime >= apntmnt[j].endTime)
            return j;
    }
    return -1;
}

int getLastNonConflictiongAptmnt_BS(vector<appointment> &apntmnt, int pos)
{

    int lo = 0, hi = pos - 1;
  
    while (lo <= hi)
    {
        int mid = lo + ((hi - lo) / 2);
        if (apntmnt[mid].endTime <= apntmnt[pos].startTime)
        {
            if (apntmnt[mid + 1].endTime <= apntmnt[pos].startTime)
                lo = mid + 1;
            else
                return mid;
        }
        else
            hi = mid - 1;
    }
  
    return -1;
}


int findMaxProfitAppointments(vector<appointment> &apntmnt)
{
    const int sz = apntmnt.size();
    //sort based on endTime
    sort(apntmnt.begin(),apntmnt.end(),appointmentComporator);
    
    vector<int> DP(sz);
    DP[0]=apntmnt[0].cost;
    
    for(int i=1;i<sz;i++)
    {
        int includedProfit = apntmnt[i].cost;
        int pos = getLastNonConflictiongAptmnt_BS(apntmnt,i);
        if(pos>=0)
            includedProfit+=DP[pos];
        int excludedProfit = DP[i-1];
        
        DP[i] = max(includedProfit,excludedProfit);
    }
    apntmnt.clear();
    return DP[sz-1];
}

void Test1()
{
    vector<appointment> appointments {{900,1000,100},
                                    {1030,1130,200},
                                    {930,1200,300},
                                    {1130,1230,100}};
    
    findMaxProfitAppointments(appointments) == 400 ? cout<<"Test1 Passed" : cout<<"Test2 Failed";
    cout<<endl;
}

void Test2()
{
    vector<appointment> appointments {{800,1100,100},
                                    {1030,1130,200},
                                    {1230,1330,300},
                                    {1130,1230,100}};
    
    findMaxProfitAppointments(appointments) == 600 ? cout<<"Test2 Passed" : cout<<"Test3 Failed";
    cout<<endl;
}

void Test3()
{
    vector<appointment> appointments {{900,1000,100},
                                    {1030,1130,200},
                                    {1230,1330,300},
                                    {1130,1230,100}};
    
    findMaxProfitAppointments(appointments) == 700 ? cout<<"Test3 Passed" : cout<<"Test3 Failed";
    cout<<endl;
}

void Test4()
{
    vector<appointment> appointments {{900,1300,100},
                                    {1030,1400,200},
                                    {1230,1500,300},
                                    {1130,1300,100}};
    
    findMaxProfitAppointments(appointments) == 300 ? cout<<"Test4 Passed" : cout<<"Test4 Failed";
    cout<<endl;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    Test1();
    Test2();
    Test3();
    Test4();
    
    return 0;
}
