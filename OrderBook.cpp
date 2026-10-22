//
// Created by liamb on 10/19/2026.
//

#include "OrderBook.h"

Trades OrderBook::AddOrder(OrderPointer order) {
    if (orders.count(order->GetId()) > 0)
        return{};
    if (order->GetSide() == Side::Buy)
        bids[order->GetPrice()].push_back(order);
    else
        asks[order->GetPrice()].push_back(order);
    orders[order->GetId()] = order;

    return MatchOrders(order);
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

Trades OrderBook:: MatchOrders(OrderPointer incoming) {
    Trades trades;

    while (!bids.empty() && !asks.empty()) {
        auto BestBid = bids.begin();
        auto BestAsk = asks.begin();

        if (BestBid->first < BestAsk->first)
            break;

        OrderPointers& BidList = BestBid->second;
        OrderPointers& AskList = BestAsk->second;
        OrderPointer bid = BidList.front();
        OrderPointer ask = AskList.front();

        Quantity quantity = std::min(bid->GetRemainingQuantity(), ask->GetRemainingQuantity());
        bid->Fill(quantity);
        ask->Fill(quantity);
        //leaving off here 10/22/26 12:00pm
    }
}