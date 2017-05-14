/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef NOWSERVING_H
#define NOWSERVING_H
#include <string>

struct sentData
{
   std::string userClass;
   std::string name;
   int time;
   bool emergency;
   bool empty;
};
void nowServing();
#endif 


