#ifndef MESSAGE_H
#define MESSAGE_H

#include "Date.h"
#include <string>

/**
 * @class Message
 */
class Message{
protected:
    std::string message;
    Date date;
public:
    /**
     * @brief Message Class Constructor
     */
    Message();
    /**
     * @brief Message Class Constructor
     * @param msg Content of the message
     * @param dt Date when the message was sent
     */
    Message(std::string msg, const Date& dt);
    /**
     * @brief Default destructor
     */
    virtual ~Message();
    /**
     * @brief Set the value of message
     * @param msg The new value of message
     */
    void setMsg(std::string msg);
    /**
     * @brief Set the value of date
     * @param dt The new value of date
     */
    void setDate(const Date& dt);
    /**
     * @brief Get the value of message
     * @return text of the message
     */
    std::string getMsg() const;
    /**
     * @brief Get the value of Date
     * @return date of the message
     */
    Date getDate() const;
    /**
     * @brief Show on the screen the info of the message
     * @param showWho True if it is suppose to print who sent the message, false otherwise
     */
    virtual void printMessage(bool showWho) const = 0;
    /**
     * @brief Return the type of the message
     * @return String with the type of the message
     */
    virtual std::string messageType() const = 0;
    /**
     * @brief Write the info of the message in a file
     * @param out Ostream where it is supposed to write in
     */
    virtual void writeMessageInFile(std::ostream & out) const = 0;
};

/**
 * @class AdminMessage
 */
class AdminMessage : public Message{
public:
    /**
     * @brief AdminMessage class constructor
     * @param msg The content of the message
     * @param dt The date of the message
     */
    AdminMessage(std::string msg, const Date& dt);
    /**
     * @brief Lower operator
     * @param msg1 Message to be compared
     * @return True if this object has a lower date or a lower message, false otherwise
     */
    bool operator<(const AdminMessage & msg1) const;
    /**
     * @brief Message comparator
     * @param msg1 Message to be compared
     * @return True if both messages have the same date and message attributes, else otherwise
     */
    bool operator==(const AdminMessage &msg1) const;
    /**
     * @brief Show on the screen the info of the message
     * @param showWho True if it is suppose to print "admin", false otherwise
     */
    void printMessage(bool showWho) const override;
    /**
     * @brief Return the type of the message
     * @return String with the type of the message (in this case with "admin_message")
     */
    std::string messageType() const override;
    /**
     * @brief Write the info of the message in a file
     * @param out Ostream where it is supposed to write in
     */
    void writeMessageInFile(std::ostream & out) const override;
};

/**
 * @class ClientMessage
 */
class ClientMessage : public Message{
private:
    std::string eMail;
    bool processed = false;
public:
    /**
     * @brief Message Class Constructor
     * @param msg Text of the message
     * @param eM Email of the client that sent the message
     * @param dt Date when the message was sent
     */
    ClientMessage(std::string msg, std::string eM, const Date& dt);
    /**
     * @brief Default Destructor
     */
    ~ClientMessage() override;
    /**
     * @brief Set the value of eMail
     * @param eM The new value of eMail
     */
    void setEMail(std::string eM);
    /**
     * @brief Get the value of eMail
     * @return eMail of the message
     */
    std::string getEMail() const;
    /**
     * @brief Lower operator
     * @param msg1 Message to be compared
     * @return True if this object has a lower date or a lower eMail, or a lower message, false otherwise
     */
    bool operator<(const ClientMessage & msg1) const;
    /**
     * @brief Message comparator
     * @param msg1 Message to be compared
     * @return True if both messages have the same eMail, date, processed and message attributes, else otherwise
     */
    bool operator==(const ClientMessage &msg1) const;
    /**
     * @brief Change the processed argument of the message to true
     * @return A pointer to the updated message
     */
    ClientMessage * processMessage();
    /**
     * @brief Show on the screen the info of the message
     * @param showWho True if it is suppose to print the email of the client, false otherwise
     */
    void printMessage(bool showWho) const override;
    /**
     * @brief Return the type of the message
     * @return String with the type of the message (in this case with "client_message")
     */
    std::string messageType() const override;
    /**
     * @brief Write the info of the message in a file
     * @param out Ostream where it is supposed to write in
     */
    void writeMessageInFile(std::ostream & out) const override;
};
#endif //MESSAGE_H
