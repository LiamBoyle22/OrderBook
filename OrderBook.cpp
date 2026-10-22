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

void OrderBook::CancelOrder(OrderId id) {
    if (orders.count(id) == 0)
        return;

    OrderPointer order = orders[id];
    Price price = order->GetPrice();

    if (order->GetSide() == Side::Buy) {
        bids[price].remove(order);
        if (bids[price].empty())
            bids.erase(price);
    }

    else {
        asks[price].remove(order);
        if (asks[price].empty())
            asks.erase(price);
    }

    orders.erase(order->GetId());
}