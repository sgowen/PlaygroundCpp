//
//  RandomFileAccessTest.h
//  PlaygroundCpp
//
//  Created by Stephen Gowen on 11/14/17.
//  Copyright © 2017 Stephen Gowen. All rights reserved.
//

#ifndef RandomFileAccessTest_h
#define RandomFileAccessTest_h

#include <fstream>

/* Make sure content of this file is equal to the following:
This is line 1
This is line 2
This is line 3
This is line 4
*/
#define TEST_FILE "/Users/sgowen/Dropbox/Documents/gamedev/github/PlaygroundCpp/PlaygroundCpp/random_file_access/Sample.dat"

class RandomFileAccessTest
{
public:
    static void test()
    {
        test1();
        test2();
        test1();
    }
    
    static void test1()
    {
        using namespace std;
        
        // TODO, make relative
        ifstream inf(TEST_FILE);
        
        // If we couldn't open the input file stream for reading
        if (!inf)
        {
            // Print an error and exit
            cerr << "Uh oh, Sample.dat could not be opened for reading!" << endl;
            exit(1);
        }
        
        string strData;
        
        inf.seekg(5); // move to 5th character
        // Get the rest of the line and print it
        getline(inf, strData);
        cout << strData << endl;
        
        inf.seekg(8, ios::cur); // move 8 more bytes into file
        // Get rest of the line and print it
        getline(inf, strData);
        cout << strData << endl;
        
        inf.seekg(-15, ios::end); // move 15 bytes before end of file
        // Get rest of the line and print it
        getline(inf, strData);
        cout << strData << endl;
    }
    
    static void test2()
    {
        using namespace std;
        
        // Note we have to specify both in and out because we're using fstream
        fstream iofile(TEST_FILE, ios::in | ios::out);
        
        // If we couldn't open iofile, print an error
        if (!iofile)
        {
            // Print an error and exit
            cerr << "Uh oh, Sample.dat could not be opened!" << endl;
            exit(1);
        }
        
        char chChar; // we're going to do this character by character
        
        // While there's still data to process
        while (iofile.get(chChar))
        {
            switch (chChar)
            {
                    // If we find a vowel
                case 'a':
                case 'e':
                case 'i':
                case 'o':
                case 'u':
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                    
                    // Back up one character
                    iofile.seekg(-1, ios::cur);
                    
                    // Because we did a seek, we can now safely do a write, so
                    // let's write a # over the vowel
                    iofile << '#';
                    
                    // Now we want to go back to read mode so the next call
                    // to get() will perform correctly.  We'll seekg() to the current
                    // location because we don't want to move the file pointer.
                    iofile.seekg(iofile.tellg(), ios::beg);
                    
                    break;
            }
        }
    }
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    RandomFileAccessTest();
    RandomFileAccessTest(const RandomFileAccessTest&);
    RandomFileAccessTest& operator=(const RandomFileAccessTest&);
};

#endif /* RandomFileAccessTest_h */
