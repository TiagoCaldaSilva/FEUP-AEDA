//
// Created by user on 25/12/2020.
//

#include "Message.h"

#include <utility>

Message::Message()= default;

Message::Message(std::string msg, const Date& dt){
  message = std::move(msg);
  date = dt;
}

void Message::setMsg(std::string msg){
    message = std::move(msg);
}

Message::~Message() = default;

void Message::setDate(const Date& dt){
    date = dt;
}

std::string Message::getMsg() const{
    return message;
}

Date Message::getDate() const{
    return date;
}

AdminMessage::AdminMessage(std::string msg, const Date& dt):Message(std::move(msg), dt){}

bool AdminMessage::operator<(const AdminMessage & msg1) const{
    if(date == msg1.date){
        return message < msg1.message;
    }return date < msg1.date;
}

bool AdminMessage::operator==(const AdminMessage &msg1) const {
    return date == msg1.date && message == msg1.message;
}

void AdminMessage::printMessage(bool showWho) const {
    if(showWho) std::cout << std::endl << "admin - " << date << std::endl; //showWho is true when it is necessary to show who is sending the message
    std::string temp = message;
    while(!temp.empty()){
        if(temp.size() < 30){           //Each line has a limit of 30 characters
            std::cout << temp << std::endl;
            temp.clear();
        }
        else{
            size_t found = temp.substr(0, 30).find_last_of(" .-,!?:/");
            std::cout << temp.substr(0, found + 1) << std::endl;
            temp.erase(0, found + 1);
        }
    }
}

void AdminMessage::writeMessageInFile(std::ostream &out) const{
    out << "admin" << std::endl << date << std::endl << message << std::endl;
}

std::string AdminMessage::messageType() const {
    return "admin_message";
}

ClientMessage::ClientMessage(std::string msg, std::string eM, const Date& dt):Message(std::move(msg), dt){
    eMail = std::move(eM);
}

ClientMessage::~ClientMessage() = default;

void ClientMessage::setEMail(std::string eM){
    eMail = std::move(eM);
}

std::string ClientMessage::getEMail() const{
    return eMail;
}

bool ClientMessage::operator<(const ClientMessage & msg1) const{
    if(date == msg1.date){
        if(eMail < msg1.eMail){
            return message < msg1.message;
        }return eMail < msg1.eMail;
    }return date < msg1.date;
}

bool ClientMessage::operator==(const ClientMessage &msg1) const {
    return eMail == msg1.eMail && date == msg1.date && message == msg1.message && processed == msg1.processed;
}

void ClientMessage::printMessage(bool showWho) const {
    if(showWho) std::cout << std::endl << eMail << " - " << date << std::endl; //showWho is true when it is necessary to show who is sending the message
    std::string temp = message;
    while(!temp.empty()){                   //Each line has a limit of 30 characters
        if(temp.size() < 30){
            std::cout << temp << std::endl;
            temp.clear();
        }
        else{
            size_t found = temp.substr(0, 30).find_last_of(" .-,!?:/");
            std::cout << temp.substr(0, found + 1) << std::endl;
            temp.erase(0, found + 1);
        }
    }
}

ClientMessage * ClientMessage::processMessage(){
    processed = true;
    return this;
}

std::string ClientMessage::messageType() const {
    return "client_message";
}

void ClientMessage::writeMessageInFile(std::ostream &out) const{
    out << eMail << std::endl << date << std::endl << message << std::endl;
}