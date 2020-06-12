//
//  MiscTest.hpp
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/3/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#pragma once

#include <algorithm>
#include <map>
#include <sstream>

std::vector<std::string> splitString(const std::string &s, char delim)
{
    std::vector<std::string> ret;
    
    std::stringstream ss(s);
    std::string value;
    while (std::getline(ss, value, delim))
    {
        ret.push_back(value);
    }
    
    return ret;
}

struct Event
{
    std::string _timeStr;
    std::string _timeExtraStr;
    int _time;
    int _timeExtra;
    std::string _event;
    std::string _teamName;
    std::string _employeeName;
    std::string _employeeNameOther;
    
    Event(std::string teamName, std::string eventStr) :
    _timeStr(""),
    _timeExtraStr(""),
    _time(0),
    _timeExtra(0),
    _event(""),
    _teamName(teamName),
    _employeeName(""),
    _employeeNameOther("")
    {
//        std::vector<std::string> tokens = splitString(eventStr, ' ');
//        std::vector<std::string> timeTokens = splitString(tokens[1], '+');
//
//        _time = std::stoi(timeTokens[0]);
//        _timeExtra = timeTokens.size() > 1 ? std::stoi(timeTokens[1]) : 0;
//        _event = tokens[3];
//        _employeeName = tokens[1];
        
        bool isBuildingTime = false;
        bool isBuildingTimeExtra = false;
        bool isBuildingEvent = false;
        bool isBuildingEmployeeNameOther = false;
        for (char const &c: eventStr)
        {
            if (isBuildingTime)
            {
                if (c == '+')
                {
                    isBuildingTimeExtra = true;
                    continue;
                }
                
                if (c == ' ')
                {
                    isBuildingTime = false;
                    isBuildingTimeExtra = false;
                    isBuildingEvent = true;
                    
                    if (_timeStr.length() > 0)
                    {
                        _time = std::stoi(_timeStr);
                    }
                    
                    if (_timeExtraStr.length() > 0)
                    {
                        _timeExtra = std::stoi(_timeExtraStr);
                    }
                }
                
                if (isBuildingTimeExtra)
                {
                    _timeExtraStr += c;
                }
                else
                {
                    _timeStr += c;
                }
            }
            else if (isBuildingEvent)
            {
                if (c == ' ')
                {
                    isBuildingEvent = false;
                    isBuildingEmployeeNameOther = true;
                    continue;
                }
                
                _event = c;
                
            }
            else if (isBuildingEmployeeNameOther)
            {
                _employeeNameOther += c;
            }
            else
            {
                if (isdigit(c))
                {
                    _employeeName = _employeeName.substr(0, _employeeName.size() - 1);
                    isBuildingTime = true;
                    _timeStr = c;
                }
                else
                {
                    _employeeName += c;
                }
            }
        }
    }
};



bool sortEvent(Event& a, Event& b)
{
    static std::map<std::string, int> eventOrderTable;
    if (eventOrderTable.size() == 0)
    {
        eventOrderTable.insert({"G", 1});
        eventOrderTable.insert({"Y", 2});
        eventOrderTable.insert({"R", 3});
        eventOrderTable.insert({"S", 4});
    }
    
    if (a._time != b._time)
    {
        return a._time < b._time;
    }
    
    if (a._timeExtra != b._timeExtra)
    {
        return a._timeExtra < b._timeExtra;
    }
    
    if (a._event != b._event)
    {
        return eventOrderTable[a._event] < eventOrderTable[b._event];
    }
    
    if (a._teamName != b._teamName)
    {
        return a._teamName < b._teamName;
    }
    
    if (a._employeeName != b._employeeName)
    {
        return a._employeeName < b._employeeName;
    }
    
    return false;
}

class MiscTest
{
public:
    static void sodaPop1(int x)
    {
        assert(x > 0);
        
        bool isMultipleOf3 = false;
        bool isMultipleOf5 = false;
        for (int i = 1; i <= x; ++i)
        {
            isMultipleOf3 = i % 3 == 0;
            isMultipleOf5 = i % 5 == 0;
            
            if (isMultipleOf3 && isMultipleOf5)
            {
                printf("FizzBuzz\n");
            }
            else if (isMultipleOf3)
            {
                printf("Fizz\n");
            }
            else if (isMultipleOf5)
            {
                printf("Buzz\n");
            }
            else
            {
                printf("%d\n", i);
            }
        }
    }
    
    static char sodaPop2(std::vector<std::vector<int> > array)
    {
        assert(array.size() >= 1);
        assert(array[0].size() == 2);
        
        char ret;
        
        int longestKeyPressIndex = 0;
        int previousTime = array[0][1];
        int longestTimeDelta = previousTime;
        for (int i = 1; i < array.size(); ++i)
        {
            assert(array[i].size() == 2);
            assert(array[i][0] >= 0 && array[i][0] <= 25);
            
            int time = array[i][1];
            int timeDelta = time - previousTime;
            if (timeDelta > longestTimeDelta)
            {
                longestTimeDelta = timeDelta;
                longestKeyPressIndex = i;
            }
        }
        
        ret = array[longestKeyPressIndex][0] + 97;
        
        return ret;
    }
    
    static long sumOfIntegerElements(std::vector<int>& array, int divisor)
    {
        long ret = 0;
        
        float value;
        int roundedValue;
        for (int i = 0; i < array.size(); ++i)
        {
            value = array[i];
            value /= divisor;
            roundedValue = ceil(value);
            ret += roundedValue;
        }
        
        return ret;
    }
    
    static int sodaPop3(std::vector<int> array, int x)
    {
        assert(array.size() >= 1);
        assert(x >= array.size());
        
        int ret = 0;
        
        long sum = sumOfIntegerElements(array, 1);
        int divisor = ceil((float)sum / x);
        while (true)
        {
            sum = sumOfIntegerElements(array, divisor);
            if (sum <= x)
            {
                break;
            }
            ++divisor;
        }
        
        ret = divisor;
        
        return ret;
    }
    
    
    
    
    
    static std::vector<std::string> sodaPop4(std::string str1, std::string str2, std::vector<std::string> array1, std::vector<std::string> array2)
    {
        std::vector<std::string> ret;
        
        std::vector<Event> mergedEvents;
        
        for (std::string& eventString : array1)
        {
            mergedEvents.emplace_back(str1, eventString);
        }
        
        for (std::string& eventString : array2)
        {
            mergedEvents.emplace_back(str2, eventString);
        }
        
        std::sort(mergedEvents.begin(), mergedEvents.end(), sortEvent);
        
        for (Event& e : mergedEvents)
        {
            std::string eventString = e._teamName;
            eventString += " ";
            eventString += e._employeeName;
            eventString += " ";
            eventString += std::to_string(e._time);
            if (e._timeExtra > 0)
            {
                eventString += "+";
                eventString += std::to_string(e._timeExtra);
            }
            
            eventString += " ";
            eventString += e._event;
            
            if (e._employeeNameOther.length() > 0)
            {
                eventString += " ";
                eventString += e._employeeNameOther;
            }
            
            ret.push_back(eventString);
        }
        
        return ret;
    }
    
    static void test()
    {
        {
            sodaPop1(15);
        }
        {
            std::vector<std::vector<int> > v;
            std::vector<int> iv1;
            iv1.push_back(0);
            iv1.push_back(2);
            std::vector<int> iv2;
            iv2.push_back(1);
            iv2.push_back(5);
            std::vector<int> iv3;
            iv3.push_back(0);
            iv3.push_back(9);
            std::vector<int> iv4;
            iv4.push_back(2);
            iv4.push_back(15);
            v.push_back(iv1);
            v.push_back(iv2);
            v.push_back(iv3);
            v.push_back(iv4);
            char ret = sodaPop2(v);
            printf("sodaPop2: %c \n", ret);
        }
        {
            std::vector<int> array;
            array.push_back(305709952);
            array.push_back(617901827);
            array.push_back(559066417);
            array.push_back(846642314);
            array.push_back(349430261);
            array.push_back(930100012);
            array.push_back(425149509);
            array.push_back(50710994);
            array.push_back(348655290);
            array.push_back(207497545);
            array.push_back(663923396);
            array.push_back(873283308);
            array.push_back(243509537);
            array.push_back(657804153);
            array.push_back(547001100);
            array.push_back(203492670);
            array.push_back(344685642);
            array.push_back(808597188);
            array.push_back(129005353);
            array.push_back(142684482);
            array.push_back(387013286);
            array.push_back(58302119);
            array.push_back(216770904);
            array.push_back(793436542);
            array.push_back(234999067);
            array.push_back(471073451);
            array.push_back(42602919);
            array.push_back(10272918);
            array.push_back(326437084);
            array.push_back(774854236);
            array.push_back(544470926);
            array.push_back(507360048);
            int x = 612271938;
            int ret = sodaPop3(array, x);
            printf("sodaPop3: %d \n", ret);
        }
        {
            std::string str1 = "edc a";
            std::string str2 = "cde y";
            std::vector<std::string> array1;
            array1.push_back("alex beck 12 G");
            array1.push_back("sam brown 43 Y");
            array1.push_back("tyler dickson 45+12 S");
            array1.push_back("stephen gowen 45+12 R");
            array1.push_back("mikel adkins 45+12 R");
            std::vector<std::string> array2;
            array2.push_back("kris ericson 45+1 S avery");
            array2.push_back("robin taylor 46 G");
            array2.push_back("eric straight 23 R");
            array2.push_back("kathrine buentello 45+12 R");
            array2.push_back("kathrine buentello 45+12 S stephen gowen");
            std::vector<std::string> ret = sodaPop4(str1, str2, array1, array2);
            
            for (const auto& item : ret)
            {
                printf("sodaPop4: %s \n", item.c_str());
            }
        }
    }
    
private:
    MiscTest();
    ~MiscTest();
    MiscTest(const MiscTest&);
    MiscTest& operator=(const MiscTest&);
};
