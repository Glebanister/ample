#include <vector>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <cassert>

#include "Storage.h"
#include "Condition.h"
#include "Activity.h"

class ConsoleActivity : public ample::Activity
{
public:
    void processInput() override
    {
        std::cin >> this->input;
        this->hasInput = true;
    }

    void generateOutput() override
    {
        for (auto &string : this->outputs)
        {
            std::cout << string << std::endl;
        }
        this->clearOutputs();
    }

    void addString(const std::string string)
    {
        this->outputs.push_back(string);
    }

    void clearOutputs()
    {
        this->outputs.clear();
    }

    bool hasNewInput()
    {
        return this->hasInput;
    }

    std::string getInput()
    {
        this->hasInput = false;
        return this->input;
    }

private:
    bool hasInput = false;
    std::string input = "";
    std::vector<std::string> outputs;
};

class User
{
public:
    int defaultAge = -1;
    int defaultId = -1;
    std::string defaultName = "Username";

    User()
        : age(defaultAge), id(defaultId), name(defaultName) {}

    void setId(const int &_id)
    {
        id = _id;
    }
    void setAge(const int &_age)
    {
        age = _age;
    }
    void setName(const std::string &_name)
    {
        name = _name;
    }
    int getId() const
    {
        return id;
    }
    int getAge() const
    {
        return age;
    }
    std::string getName() const
    {
        return name;
    }

private:
    int id, age;
    std::string name;
};

class UserInfoGetter : public ample::Condition
{
public:
    UserInfoGetter(User *user)
        : user(user) {}

    int init(ample::Activity *activity) override
    {
        ConsoleActivity *console = static_cast<ConsoleActivity *>(activity);
        console->addString("Your name: ");
        this->st = 0;
        console->generateOutput();
        return 0;
    }

    int update(ample::Activity *activity) override
    {
        ConsoleActivity *console = static_cast<ConsoleActivity *>(activity);
        if (console->hasNewInput())
        {
            if (st == 0)
            {
                user->setName(console->getInput());
            }
            else if (st == 1)
            {
                user->setId(stoi(console->getInput()));
            }
            else if (st == 2)
            {
                user->setAge(stoi(console->getInput()));
            }
        }
        if (st == 0)
        {
            console->addString("Your Id: ");
            this->st = 1;
        }
        else if (st == 1)
        {
            console->addString("Your Age: ");
            this->st = 2;
        }
        else if (st == 2)
        {
            console->addString("Hello, " + user->getName());
            console->stop();
        }
        return 0;
    }

private:
    User *user;
    int st = -1;
};

int main()
{
    ConsoleActivity *console = new ConsoleActivity;
    User *user = new User;
    UserInfoGetter *getter = new UserInfoGetter(user);
    console->addCondition(getter);
    console->run();

    return 0;
}
