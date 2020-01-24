#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

#include "gtest/gtest.h"
#include "Error.h"
#include "Activity.h"

const std::string TEST_FILES_DIR = "TestingDir";

#define TEST_FILE(name) (TEST_FILES_DIR + "/" + name)


class Writer : public activity::LogicBlock
{
public:
    Writer(const std::string &outfile)
    {
        file.open(outfile);
        assert(file.good());
    }

    void onUpdate() override
    {
        file << "TESTing" << std::endl;
    }

    ~Writer()
    {
        file.close();
    }

protected:
    std::ofstream file;
};

class iterationsCounter : public activity::LogicBlock
{
public:
    iterationsCounter(activity::Activity *activ, int max)
        : act(activ), cnt(0), max(max) {}

    void onUpdate() override
    {
        cnt++;
        if (cnt == max)
        {
            act->stop();
        }
        if (cnt > max)
        {
            FAIL();
        }
    }

private:
    activity::Activity *act;
    int cnt = 0;
    int max;
};

TEST(testActivityUnitStart, ActivityUnitStart)
{
    try
    {
        activity::Activity act;
        Writer *writer = new Writer(TEST_FILE("act1.test"));
        iterationsCounter counter(&act, 3);
        act.addLogicBlock(writer);
        act.addLogicBlock(&counter);
        act.start();
        delete writer;
        std::ifstream file(TEST_FILE("act1.test"));
        for (int i = 0; i < 3; i++)
        {
            std::string s;
            file >> s;
            EXPECT_EQ(s, "TESTing");
        }
        std::string s;
        file >> s;
        EXPECT_TRUE(file.eof());
    }
    catch (const exception::Exception &ex)
    {
        FAIL();
    }
}

class initWriter : public Writer
{
public:
    initWriter(const std::string &name)
        : Writer(name)
    {
    }

    void onInitialization() override
    {
        file << "init\n";
    }

    void onTermination() override
    {
        file << "term\n";
    }

    void closeFile()
    {
        file.close();
    }
};

TEST(testActivity, ActivityItegrateInitTerminate)
{
    try
    {
        activity::Activity act;
        Writer *writer = new initWriter(TEST_FILE("act2.test"));
        iterationsCounter counter(&act, 3);
        act.addLogicBlock(writer);
        act.addLogicBlock(&counter);
        act.start();
        delete writer;
        std::ifstream file(TEST_FILE("act2.test"));
        std::string initS;
        file >> initS;
        EXPECT_EQ(initS, "init");
        for (int i = 0; i < 3; i++)
        {
            std::string s;
            file >> s;
            EXPECT_EQ(s, "TESTing");
        }
        std::string s;
        file >> s;

        EXPECT_EQ(s, "term");

        file >> s;
        EXPECT_TRUE(file.eof());
    }
    catch (const exception::Exception &ex)
    {
        FAIL();
    }
}

class InputOutput : public activity::Activity
{
public:
    InputOutput(const std::string &nameIn, const std::string &nameOut)
        : inFile(nameIn), outFile(nameOut) {}

    void onInput() override
    {
        inFile >> cmd;
    }

    void onOutput() override
    {
        outFile << cmd << ' ';
        outFile.flush();
    }

    void close()
    {
        inFile.close();
        outFile.close();
    }

private:
    std::ifstream inFile;
    std::ofstream outFile;
    std::string cmd;
};

TEST(test_activity, ActivityUnitInputOutput1)
{
    std::ofstream file(TEST_FILE("act_in.test"));
    file << "C1" << ' ' << "C2" << ' ' << "C3" << std::endl;
    file.close();

    InputOutput act(TEST_FILE("act_in.test"), TEST_FILE("act_out.test"));
    iterationsCounter counter(&act, 3);
    act.addLogicBlock(&counter);
    act.start();
    act.close();

    std::ifstream res(TEST_FILE("act_out.test"));
    std::string s;
    std::getline(res, s);
    EXPECT_EQ(s, "C1 C2 C3 ");
}

TEST(test_activity, ActivityUnitInputOutput2)
{
    std::ofstream file(TEST_FILE("act_in.test"));
    file << "" << ' ' << "" << ' ' << "" << std::endl;
    file.close();

    InputOutput act(TEST_FILE("act_in.test"), TEST_FILE("act_out.test"));
    iterationsCounter counter(&act, 3);
    act.addLogicBlock(&counter);
    act.start();
    act.close();

    std::ifstream res(TEST_FILE("act_out.test"));
    std::string s;
    std::getline(res, s);
    EXPECT_EQ(s, "   ");
}

TEST(test_activity, ActivityIntegrateInitInputOutputTerminate1)
{
    std::string inName = TEST_FILE("act_in.test");
    std::string outName = TEST_FILE("act_out.test");
    std::string wName = TEST_FILE("act_writer.test");

    std::ofstream file(inName);
    file << "C1" << ' ' << "C2" << ' ' << "C3" << std::endl;
    file.close();

    InputOutput act(inName, outName);
    iterationsCounter counter(&act, 3);
    act.addLogicBlock(&counter);
    initWriter writer(wName);
    act.addLogicBlock(&writer);
    act.start();
    act.close();
    writer.closeFile();

    std::string s;
    std::ifstream actOut(outName);
    std::getline(actOut, s);
    EXPECT_EQ(s, "C1 C2 C3 ");
    std::getline(actOut, s);
    EXPECT_TRUE(actOut.eof());
    actOut.close();

    std::ifstream res(wName);
    assert(res.good());
    std::getline(res, s);
    EXPECT_EQ(s, "init");
    std::getline(res, s);
    EXPECT_EQ(s, "TESTing");
    std::getline(res, s);
    EXPECT_EQ(s, "TESTing");
    std::getline(res, s);
    EXPECT_EQ(s, "TESTing");
    std::getline(res, s);
    EXPECT_EQ(s, "term");

    res.close();
    

}
