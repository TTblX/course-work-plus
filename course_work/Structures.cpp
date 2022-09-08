//
// Created by vanish on 06.09.2022.
//
#include "Structures.h"

//Name class

Name::Name() {
    this->last_name = "";
    this->middle_name = "";
    this->first_name = "";
}

Name::Name(string first_name, string middle_name, string last_name) {
    if (checkCorrectness(first_name, middle_name, last_name)){
        this->last_name = last_name;
        this->middle_name = middle_name;
        this->first_name = first_name;
    }
}

std::string Name::getFullName() {
    return first_name + middle_name + last_name;
}

const string &Name::getFirstName() const {
    return first_name;
}

const string &Name::getMiddleName() const {
    return middle_name;
}

void Name::setMiddleName(const string &middleName) {
    middle_name = middleName;
}

void Name::setFirstName(const string &firstName) {
    first_name = firstName;
}

const string &Name::getLastName() const {
    return last_name;
}

void Name::setLastName(const string &lastName) {
    last_name = lastName;
}

bool Name::checkCorrectness(string first_name, string middle_name, string last_name) {
    return true;
    //проверка фио на правильность(нету цифр, знаков препинания и тд)
}

//HomePhone class

HomePhone::HomePhone() {
    this->home_phone = "";
}

HomePhone::HomePhone(string home_phone) {
    if (checkCorrectness(home_phone)) this->home_phone = home_phone;
}

HomePhone::~HomePhone() {

}

bool HomePhone::checkCorrectness(string number) {
    return true;
    //проверка фио на правильность(нету цифр, знаков препинания и тд)
}

string HomePhone::getHomePhone() { return home_phone; }

//MobilePhone

MobilePhone::MobilePhone() {
    this->mobile_phone = "";
}

MobilePhone::MobilePhone(string mobile_phone) {
    if (checkCorrectness(mobile_phone)) this->mobile_phone = mobile_phone;
}

MobilePhone::~MobilePhone() {

}

bool MobilePhone::checkCorrectness(string number) {
    return true;
    //проверка фио на правильность(нету цифр, знаков препинания и тд)
}

string MobilePhone::getMobilePhone() { return mobile_phone; }

//Email class

bool Email::checkCorrectness() {
    return true;
    //проверка на правильность(нету цифр, знаков препинания и тд)
}

//Address class

bool Address::checkCorrectness() {
    return true;
    //проверка на правильность(нету цифр, знаков препинания и тд) еще удалить все символы, кроме цифр, букв и знаков препинания
}

//Photo class

Photo::Photo() {
    file_path = "";
}

Photo::Photo(string file_path) {

}

bool Photo::checkCorrectness() {
    return true;
    //проверка является ли файл фотографией и существует ли он
}

Photo::~Photo() {

}
