//
// Created by vanish on 06.09.2022.
//
#include "Data.h"

Data::Data(const Name &name, const HomePhone &homePhone, const MobilePhone &mobilePhone, const Email &email,
           const Address &address, const Photo &photo) : name(name), home_phone(homePhone), mobile_phone(mobilePhone),
                                                         email(email), address(address), photo(photo) {}

Data::~Data() {

}


const Name &Data::getName() const {
    return name;
}

const Email &Data::getEmail() const {
    return email;
}

const Address &Data::getAddress() const {
    return address;
}

const Photo &Data::getPhoto() const {
    return photo;
}

const HomePhone &Data::getHomePhone() const {
    return home_phone;
}

const MobilePhone &Data::getMobilePhone() const {
    return mobile_phone;
}

void Data::setPhoto(const Photo &photo) {
    Data::photo = photo;
}

void Data::setAddress(const Address &address) {
    Data::address = address;
}

void Data::setEmail(const Email &email) {
    Data::email = email;
}

void Data::setMobilePhone(const MobilePhone &mobilePhone) {
    mobile_phone = mobilePhone;
}

void Data::setHomePhone(const HomePhone &homePhone) {
    home_phone = homePhone;
}

void Data::setName(const Name &name) {
    Data::name = name;
}

void Data::saveData() {

}
