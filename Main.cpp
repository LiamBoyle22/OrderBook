//
// Created by liamb on 10/20/2026.
//

#include "OrderBook.h"
#include <iostream>

int main() {
    orderBook book;
    book.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, OrderType2::Limit, 1, Side::Buy, 100, 10));
    std::cout << book.Size() << "\n";
}