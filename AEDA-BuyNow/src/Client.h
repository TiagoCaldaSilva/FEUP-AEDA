#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Payment.h"
#include <queue>
#include "Message.h"

/**
  * @class Client
  */
class Client
{
private:
    std::string name;
    unsigned int nif;
public:
  /**
   * @brief Default Constructor
   */
  Client();
  /**
   * @brief Default Destructor
   */
  virtual ~Client();
  /**
   * @brief Class constructor
   * @param name Name of the client
   * @param nif Nif of the client
   */
  Client(const std::string& name, unsigned int nif);
  /**
   * @brief Get the name of the client
   * @return String with the name of the client
   */
  std::string getName() const;
  /**
   * @brief Get the nif of the client
   * @return Nif of the client
   */
  unsigned int getNIF() const;
  /**
   * Set the value of name
   * @param value The new value of name
   */
  void setName(const std::string& value);
  /**
   * @brief Set the value of NIF
   * @param value The new value of NIF
   */
  void setNIF(unsigned int value);
  /**
   * @brief Client comparator
   * @param c2 The other client that should be compared with
   * @return True if they are equal, false otherwise
   */
  virtual bool operator==(const Client& c2) const;
  /**
   * @brief Client lower operator, by name
   * @param c2 Client to be compared
   * @return True if this(Client) is lower than c2
   */
  bool operator<(const Client& c2) const;
};

/**
  * @class RegisteredClient
  */
class RegisteredClient : public Client
{
private:
    const long ID;
    static long ID_VALUE;
    std::string eMail;
    std::vector<Payment *> paymentMethods;
    std::queue<Message *> messages;
public:
    /**
     * @brief Default Constructor
     */
    RegisteredClient();
    /**
     * @brief Class constructor
     * @param name Name of the client
     * @param nif Nif of the client
     * @param email Email of the client
     */
    RegisteredClient(const std::string& name, unsigned int nif, const std::string& email);
    /**
     * @brief Class constructor
     * @param name Name of the client
     * @param nif Nif of the client
     * @param email Email of the client
     * @param pay_method Vector with the methods of payment of the client
     */
    RegisteredClient(const std::string& name, unsigned int nif, const std::string& email, const std::vector<Payment *>& pay_method);
    /**
     * @brief Class constructor
     * @param name Name of the client
     * @param nif Nif of the client
     */
    RegisteredClient(const std::string& name, unsigned int nif);
    /**
     * @brief RegisteredClient Destructor deallocates the memory owned
     */
    ~RegisteredClient() override;
    /**
     * @brief Get the email of the client
     * @return The email of the client
     */
    std::string getEmail() const;
    /**
     * @brief Get the id of the client
     * @return The id of the client
     */
    unsigned int getID() const;
    /**
     * @brief Get the payment methods of the client
     * @return The payment methods of the client
     */
    std::vector<Payment *> getPaymentMethods() const;
    /**
     * @brief Adds a payment method to the client vector of payments methods
     * @param p Payment method
     */
    void addPaymentMethod(Payment * p);
    /**
     * @brief Set the value of eMail
     * @param value The new value of eMail
     */
    void setEMail(const std::string& value);
    /**
     * @brief Set the value of paymentMethods
     * @param value The new value of paymentMethods
     */
    void setPaymentMethods(const std::vector<Payment *>& value);
    /**
     * @brief Verifies if paymentMethods has payment methods of type MBWay and CreditCard
     * @return True if valid paymentMethod exists
     */
    bool paymentMethodsNotEmpty() const;
    /**
     * @brief Client comparator by ID
     * @param c2 The other client that should be compared with
     * @return True if they are equal, false otherwise
     */
    bool operator==(const RegisteredClient& c2) const;

    /*############################# 2 Part #############################*/
    /**
     * @brief Add a message to the argument messages
     * @param msg Message that should be added
     */
    void addMessage(Message * msg);
    /**
     * @brief Get the last message of the client chat
     * @return The last message that was added to the argument messages
     */
    Message * getLastMessage();
    /**
     * @brief Get the chat of the client
     * @return A queue with all the messages of the client
     */
    std::queue<Message *> getMessages() const;
    /**
     * @brief Tell if the argument messages is empty or not
     * @return True if it is empty, false otherwise
     */
    bool noMessages() const;
    /**
     * @brief Show the client chat on the screen
     */
    void showMessages() const;
    /**
     * @brief Remove the first message of messages
     */
    void removeMessage();
    /**
     * @brief Write the client chat into a file
     * @param out Ostream that is associated to the file
     */
    void writeChat(std::ostream & out);
    /**
     * @brief Get the message on the index position of the queue
     * @param index Position of the message
     * @return The message
     */
    Message * getMessage(size_t index);
    /**
     * @brief Change the processed argument of the last message
     */
    void processLast();
    };

/**
 * @brief Function used to compare two methods of payment
 * @param p1 Payment method 1
 * @param p2 Payment method 2
 * @return True if they are equal, false otherwise
 */
bool paymentComparator(Payment * p1,Payment * p2);

#endif // CLIENT_H
