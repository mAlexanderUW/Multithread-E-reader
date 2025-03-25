#include "Threads.h"




Threads::Threads()
{
    theEnd = false;
    pageCount = 0;
    pageTotal = 379;
    lineCount = 0;
    fileTxt = "";
    fileName = "Moby Dick.txt";
}

void Threads::thread1()
{
    std::ifstream istream(fileName);
    std::string temp;


    if (!std::filesystem::exists(fileName))
    {
        fileTxt = "TEXT FILE NOT FOUND PLEASE QUIT";
    }

    while (pageCount < pageTotal)
    {
        readThread.acquire();
        while (lineCount < 50)
        {
            std::getline(istream, temp);
            fileTxt += temp + "\n";
            lineCount++;
        }
        lineCount = 0;
        writeThread.release();

    }
    theEnd = true;
}

void Threads::thread2()
{

    while (!theEnd) {

        writeThread.acquire();
        sharedTxt = fileTxt;
        pageCount += 1;
        fileTxt = "";
        
    }
}

void Threads::releaseEvent()
{
    readThread.release();
}

std::string Threads::getSharedTxt()
{
    return sharedTxt;
}

