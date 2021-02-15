#include <iostream>
#include "Company.h"

#define ADMIN_USER "admin"
#define ADMIN_PASS "20aAEDApff"

/**
 * @brief Menu where the admin can analyse the statistics of the company
 * @param c Company pointer
 */
void companyStats(Company * c);
/**
 * @brief Menu where the admin can analyse all the transactions of the company
 * @param c Company pointer
 */
void transactions(Company * c);
/**
 * @brief Menu where the admin can manage the products of the company
 * @param c Company pointer
 */
void products(Company * c);
/**
 * @brief Menu where the admin can manage the clients of the company
 * @param c Company pointer
 */
void admin_clients(Company * c);
/**
 * @brief Menu where the admin can manage the company
 * @param c Company pointer
 */
void stores(Company * c);
/**
 * @brief Menu that show the categories that the admin can manage/analyse
 * @param c Company pointer
 */
void admin(Company * c);
/**
 * @brief Menu to manage the payment of the given transaction
 * @param c Company pointer
 * @param client Client that is buying
 * @param transaction Transaction with information of what is being bought
 * @param exists True if the client already exists in the company's record and false if the client is new
 */
void paymentMethod(Company * c,Client * client, Transaction * transaction,bool exists);
/**
 * @brief Menu to manage the clients basket
 * @param c Company pointer
 * @param client Client that is buying
 * @param exists True if the client already exists in the company's record and false if the client is new
 * @param date Current date
 */
void clientOperations(Company * c, Client * client,Date * date, bool exists);
/**
 * @brief Menu to welcome a client and manage its entry in the OnlineStore
 * @param c Company pointer
 */
void client(Company * c);
/**
 * @brief Open the chat of a client
 * @param who Distinguish if the function is used by a client or used by an admin
 * @param client Pointer to the client whose chat should be opened
 * @param c Company pointer
 * @param date Current date
 */
void openChat(std::string who, RegisteredClient * client, Company * c, Date * date);
/**
 * @brief Menu where the admin can manage the chats with the registered clients of the company
 * @param c Company pointer
 */
void admin_messages(Company * c);
/**
 * @brief Menu to restock the missing products of the store
 * @param c Company pointer
 */
void admin_restock(Company * c);
/**
 * @brief Menu to manage the company's fleet
 * @param c Company pointer
 */
void admin_fleet(Company * c);
/**
 * @brief
 * @return
 */
Date getDate();