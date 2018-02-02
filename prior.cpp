#include <stdio.h>
#include <cstdio>
#include <cinttypes>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
// Get the size of a file
long getFileSize(FILE *file)
{
    long lCurPos, lEndPos;
    lCurPos = ftell(file);
    fseek(file, 0, 2);
    lEndPos = ftell(file);
    fseek(file, lCurPos, 0);
    return lEndPos;
}

int concat()
{
    const char *filePath = "front-road.f8";
    uint8_t *fileBuf;			// Pointer to our buffered data
    FILE *file = NULL;		// File pointer

    FILE* pFile;
    pFile = fopen("8.f8", "wb");
    list<const char*> files_list = { "front-road.f8", "front-ceiling.f8", "front-pole.f8", "front-pole.f8", "front-pole.f8", "front-pole.f8", "front-void.f8", "front-pole.f8" };
    for (auto f: files_list){
        // Open the file in binary mode using the "rb" format string
        // This also checks if the file exists and/or can be opened for reading correctly
        if ((file = fopen(f, "rb")) == NULL)
            cout << "Could not open specified file" << endl;
        else
            cout << "File opened successfully" << endl;

        // Get the size of the file in bytes
        long fileSize = getFileSize(file);

        // Allocate space in the buffer for the whole file
        fileBuf = new std::uint8_t[fileSize];

        // Read the file in to the buffer
        fread(fileBuf, fileSize, 1, file);

        // Now that we have the entire file buffered, we can take a look at some binary infomation
        // Lets take a look in hexadecimal
        //for (int i = 0; i < 320*200; i++)
        //    std::cout << (int)fileBuf[i] << std::endl;

        //write to binary

        fwrite(fileBuf, sizeof(uint8_t), fileSize, pFile);

        delete[]fileBuf;
        fclose(file);   // Almost forgot this
    }

    fclose(pFile);   // Almost forgot this
    return 0;
}

int image2tensor()
{
    //image to tensor
    cv::Mat in = cv::imread("front-pole.png", 0);
    FILE* pFile;
    pFile = fopen("void.f8", "wb");
    std::uint8_t a = 1;
    for (unsigned long long i = 0; i < 200; ++i){
        for (unsigned long long j = 0; j < 320; ++j){
            a = 0;
            if(in.at<std::uint8_t>(i,j) >= 1){
                a = 1;
            }
            fwrite(&a, sizeof(uint8_t), 1, pFile);
        }
    }
}

int main()
{
    //call image2tensor or concat function
    return 0;
}
