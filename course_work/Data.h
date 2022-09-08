//
// Created by vanish on 05.09.2022.
//

#ifndef COURSE_WORK_DATA_H
#define COURSE_WORK_DATA_H


#include <string>
#include "Structures.h"

using namespace std;

class Data {
public:
    Data(const Name &name, const HomePhone &homePhone, const MobilePhone &mobilePhone, const Email &email,
         const Address &address, const Photo &photo);

    virtual ~Data();

    void saveData();

    const Name &getName() const;
    const Email &getEmail() const;
    const Address &getAddress() const;
    const Photo &getPhoto() const;
    const HomePhone &getHomePhone() const;
    const MobilePhone &getMobilePhone() const;

    void setPhoto(const Photo &photo);
    void setAddress(const Address &address);
    void setEmail(const Email &email);
    void setMobilePhone(const MobilePhone &mobilePhone);
    void setHomePhone(const HomePhone &homePhone);
    void setName(const Name &name);


private:
    Name name;
    HomePhone home_phone;
    MobilePhone mobile_phone;
    Email email;
    Address address;
    Photo photo;
};

#endif //COURSE_WORK_DATA_H
