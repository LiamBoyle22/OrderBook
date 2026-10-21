//
// Created by liamb on 10/19/2026.
//

#include "OrderBook.h"

void OrderBook::AddOrder(OrderPointer order) {
    if (orders.count(order->GetId()) > 0)
        return;
    if (order->GetSide() == Side::Buy)
        bids[order->GetPrice()].push_back(order);
    else
        asks[order->GetPrice()].push_back(order);
    orders[order->GetId()] = order;
}

void OrderBook::RemoveOrder(OrderPointer order) {
        orders.erase(order->GetId());
}