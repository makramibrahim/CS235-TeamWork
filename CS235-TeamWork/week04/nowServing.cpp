/***********************************************************************
 * Implementation:
 *    Now Serving with deque created before
 * Summary:
 *    This will have nowServing() as well as any
 * Author
 *    Jefferson Santos
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
#include "servingStruct.h"   //for helping nowServing.h
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   int timer = 0;
   cout << "<" << timer << "> ";
   
   //
   sentData servingRequest;
   cin >> servingRequest.userClass;
   cin >> servingRequest.name;
   cin >> servingRequest.time;
   servingRequest.empty = false;
   
   //
   cout << "\tCurrently serving " << servingRequest.name << " for class " <<
   servingRequest.userClass;
   cout << ". Time left: " << servingRequest.time << endl;
   timer++;
   servingRequest.time--;
   
   //
   Deque<sentData> nowServing;
   for(;;)
   {
      string first;
      sentData sentData;
      
      //
      cout << "<" << timer << "> ";
      
      //
      cin >> first;
      
      if (first == "!!")
      {
         sentData.emergency = true;
         cin >> sentData.userClass;
         cin >> sentData.name;
         cin >> sentData.time;
         sentData.empty = false;
         nowServing.push_front(sentData);
      }
      else if (first == "none")
      {
         sentData.empty = true;
      }
      else if (first == "finished")
      {
         cout << "End of simulation\n";
         return;
      }
      else 
      {
         sentData.emergency = false;
         sentData.userClass = first;
         cin >> sentData.name;
         cin >> sentData.time;
         sentData.empty = false;
         nowServing.push_back(sentData);
      }
      
      if (!nowServing.empty())
      {
         if (servingRequest.time <= 0)
         {
            servingRequest = nowServing.front();
            nowServing.pop_front();
         }
         if (servingRequest.emergency)
         {
            cout << "\tEmergency for " << servingRequest.name << " for class " <<
            servingRequest.userClass;
            cout << ". Time left: " << servingRequest.time << endl;
         }
         else
         {
            cout << "\tCurrently serving " << servingRequest.name << " for class " << servingRequest.userClass;
            cout << ". Time left: " << servingRequest.time << endl;
         }
      }
      else if (servingRequest.time > 0)
      {
         if (servingRequest.emergency)
         {
            cout << "\tEmergency for " << servingRequest.name << " for class " << servingRequest.userClass;
            cout << ". TIme left: " << servingRequest.time << endl;
         }
         else
         {
            cout << "\tCurrently serving " << servingRequest.name << " for class " << servingRequest.userClass;
            cout << ". Time left: " << servingRequest.time << endl;
         }
      }
      
      //
      timer++;
      servingRequest.time--;
   }

   // end
   cout << "End of simulation\n";
}
