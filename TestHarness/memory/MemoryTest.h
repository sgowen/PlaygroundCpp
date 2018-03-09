//
//  MemoryTest.h
//  TestHarness
//
//  Created by Stephen Gowen on 11/9/17.
//  Copyright © 2017 Noctis Games. All rights reserved.
//

#ifndef MemoryTest_h
#define MemoryTest_h

#include <vector>
#include <string>

#include <vector/Extension.h>

namespace NoctisGames
{
    class MemoryTest
    {
    public:
        static void test()
        {
            std::vector<std::string> testVector;
            testVector.push_back("this is a test");
            testVector.push_back("this is a test as well");
            testVector.push_back("this is a test also");
            testVector.push_back("this is a test too");
            testVector.push_back("this is a test man");
            
            void* pointer1 = &testVector[3];
            
            std::string test = testVector[3];
            void* pointer2 = &test;
            
            std::string& test2 = testVector[3];
            void* pointer3 = &test2;
            
            std::cout << "pointer1 " << pointer1 << std::endl;
            std::cout << "pointer2 " << pointer2 << std::endl;
            std::cout << "pointer3 " << pointer3 << std::endl;
            
            std::string* stringP = new std::string("Why would you ever want a pointer to a string huh?");
            std::string stringDeref = *stringP;
            stringDeref += " You wouldn't!";
            std::string& stringDerefRef = *stringP;
            
            std::cout << "stringP " << stringP << std::endl;
            std::cout << "&stringDeref " << &stringDeref << std::endl;
            std::cout << "&stringDerefRef " << &stringDerefRef << std::endl;
            
            testStringConstructor();
            
            std::string OptionString = std::string("imagertemp=-10.0");
            testStringCopyToken(OptionString);
            
            std::string OptionString2 = std::string("");
            testStringCopyToken(OptionString2);
        }
        
        struct DataInput
        {
            const unsigned char* cursor;
            const unsigned char* end;
        };
        
        static unsigned char readByte(DataInput* input)
        {
            return *input->cursor++;
        }
        
        static int readVarint(DataInput* input, bool optimizePositive)
        {
            unsigned char b = readByte(input);
            int value = b & 0x7F;
            if (b & 0x80)
            {
                b = readByte(input);
                value |= (b & 0x7F) << 7;
                if (b & 0x80)
                {
                    b = readByte(input);
                    value |= (b & 0x7F) << 14;
                    if (b & 0x80)
                    {
                        b = readByte(input);
                        value |= (b & 0x7F) << 21;
                        if (b & 0x80) value |= (readByte(input) & 0x7F) << 28;
                    }
                }
            }
            
            if (!optimizePositive)
            {
                value = (((unsigned int)value >> 1) ^ -(value & 1));
            }
            
            return value;
        }
        
        static char* readString(DataInput* input)
        {
            int length = readVarint(input, true);
            char* string;
            if (length == 0)
            {
                return 0;
            }
            string = MALLOC(char, length);
            memcpy(string, input->cursor, length - 1);
            input->cursor += length - 1;
            string[length - 1] = '\0';
            return string;
        }
        
        static unsigned char* readFile(const char* path, int* length)
        {
            unsigned char *data;
            FILE *file = fopen(path, "rb");
            if (!file) return 0;
            
            fseek(file, 0, SEEK_END);
            *length = (int)ftell(file);
            fseek(file, 0, SEEK_SET);
            
            data = MALLOC(unsigned char, *length);
            fread(data, 1, *length, file);
            fclose(file);
            
            return data;
        }
        
        static std::string readStuff(const unsigned char* binary, const int length)
        {
            DataInput* input = CALLOC(DataInput, 1);
            input->cursor = binary;
            input->end = binary + length;
            
            char* char_hash = readString(input);
            std::string hash = std::string(char_hash);
            FREE(char_hash);
            
            return hash;
        }
        
        static void testStringConstructor()
        {
            int length;
            const unsigned char* binary = readFile("test.txt", &length);
            
            std::string stringThatWeRead = readStuff(binary, length);
            
            printf("stringThatWeRead: %s", stringThatWeRead.c_str());
            
            FREE(binary);
        }
        
#define IMAGER_TEMP_OPTION "imagertemp"
#define INTEGRATION_TIME_OPTION "integrationtime"
        
        static void testStringCopyToken(std::string OptionString)
        {
            float ImagerTemp = 0.0f;
            bool SetImagerTemp = false;
            bool AutoIntegration = false;
            const float DEFAULT_INTEGRATION_TIME = 1.0f;
            float IntegrationTime = DEFAULT_INTEGRATION_TIME;
            if (OptionString.length() > 0)
            {
                char *dup = strdup(OptionString.c_str());
                char* Token = strtok(dup, ",");
                
                while(Token != NULL)
                {
                    std::size_t found = std::string(Token).find(IMAGER_TEMP_OPTION);
                    if(found!=std::string::npos)
                    {
                        if(strlen(Token) > strlen(IMAGER_TEMP_OPTION)+2 && Token[strlen(IMAGER_TEMP_OPTION)] == '=')
                        {
                            SetImagerTemp = true;
                            ImagerTemp = atof(Token+strlen(IMAGER_TEMP_OPTION)+1);
                        }
                    }
                    found = std::string(Token).find(INTEGRATION_TIME_OPTION);
                    if(found!=std::string::npos)
                    {
                        if(strlen(Token) > strlen(INTEGRATION_TIME_OPTION)+2 && Token[strlen(INTEGRATION_TIME_OPTION)] == '=')
                        {
                            const char* parameter = Token+strlen(INTEGRATION_TIME_OPTION)+1;
                            float temp = atof(parameter);
                            if(temp >= 0.01f && temp <= 10.0f)IntegrationTime = temp;
                            if(temp == 0.0f && !strcmp(parameter, "auto"))
                            {
                                IntegrationTime = 0.01f; //Start point for AutoIntegration
                                AutoIntegration = true;
                            }
                        }
                    }
                    Token = strtok (NULL, ",");
                }
                
                free(dup);
            }
        }
        
    private:
        // ctor, copy ctor, and assignment should be private in a Singleton
        MemoryTest();
        MemoryTest(const MemoryTest&);
        MemoryTest& operator=(const MemoryTest&);
    };
}

#endif /* MemoryTest_h */
