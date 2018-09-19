#ifndef __GLOBALVARS_H_INCLUDED__
#define __GLOBALVARS_H_INCLUDED__

#include <map>
#include <vector>
#include <mutex>
#include <string>
#include <queue>

extern double decayConst;
extern bool interruptFlag;
extern bool computeFlag;
extern bool clientFlag;
extern double currentTimestamp;
extern std::map<std::string, std::vector<double> > mostPopItem;
extern std::mutex mtx;
extern std::queue<std::string> addDataList;
#endif
