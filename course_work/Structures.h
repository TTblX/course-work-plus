//
// Created by vanish on 05.09.2022.
//

#ifndef COURSE_WORK_STRUCTURES_H
#define COURSE_WORK_STRUCTURES_H

#include <string>

using namespace std;

struct  Name{
private:
    std::string first_name;
    std::string middle_name;
    std::string last_name;
public:

    Name();

    Name(string first_name, string middle_name, string last_name);

    std::string getFullName();

    const string &getFirstName() const;

    void setFirstName(const string &firstName);

    const string &getMiddleName() const;

    void setMiddleName(const string &middleName);

    const string &getLastName() const;

    void setLastName(const string &lastName);

    bool checkCorrectness(string first_name, string middle_name, string last_name);
};

struct HomePhone{
private:
    string home_phone;
public:

    HomePhone();

    HomePhone(string home_phone);

    ~HomePhone();

    bool checkCorrectness(string number);

    string getHomePhone();
};

struct MobilePhone{
private:
    string mobile_phone;
public:

    MobilePhone();
    MobilePhone(string mobile_phone);
    ~MobilePhone();

    bool checkCorrectness(string number);

    string getMobilePhone();
};

struct Email{
private:
    std::string email;
public:
    bool checkCorrectness();
};

struct Address{
private:
    std::string addres;
public:
    bool checkCorrectness();
};

struct Photo{
private:
    std::string file_path;
public:
    Photo();
    Photo(string file_path);

    virtual ~Photo();

    bool checkCorrectness();
};

#endif //COURSE_WORK_STRUCTURES_H
