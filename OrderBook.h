//
// Created by liamb on 10/19/2026.
//

#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H
#pragma once
#include <vector>
#include <cstdint>
#include <list>
#include <map>
#include <unordered_map>
#include <memory>
#include <stdexcept>

//sides this stays firm
enum class Side: uint8_t
{
    Buy,
    Sell
  };

enum class OrderType2 {
    Market,
    Limit
};

enum class OrderType {
    FillAndKill,
    GoodTillCancel
  };

//now we make our dependant values for our buy or sell side items
using OrderId = uint64_t;
using Price = int64_t;
using Quantity = uint32_t;

//now we initialise the order it self
struct LvInfo {
    Price price;
    Quantity quantity;
};

struct Trade {
    OrderId bidId;
    OrderId askId;
    Price price;
    Quantity quantity;
};

using Trades = std::vector<Trade>;

using LvInfoVec = std::vector<LvInfo>;

class OrderBookLevels {
public:
    OrderBookLevels(const LvInfoVec& bids, const LvInfoVec& asks)
      : bids {bids}, asks {asks}
    {}

    const LvInfoVec& GetBids() const { return bids; }
    const LvInfoVec& GetAsks() const { return asks; }

private:
    LvInfoVec bids;
    LvInfoVec asks;
};

class Order {
public:
    Order(OrderType type, OrderType2 type2, OrderId id, Side side, Price price, Quantity quantity)
        : type {type}, type2 {type2}, id {id}, side {side}, price {price}, InitialQuantity {quantity}, RemainingQuantity {quantity}
    {}

    OrderId GetId() const {return id;}
    Side GetSide() const {return side;}
    Price GetPrice() const {return price;}
    OrderType GetType() const {return type;}
    OrderType2 GetType2() const {return type2;}
    Quantity GetInitialQuantity() const {return InitialQuantity;}
    Quantity GetRemainingQuantity() const {return RemainingQuantity;}
    Quantity GetFilledQuantity() const {return InitialQuantity - RemainingQuantity;}
    bool IsFilled() const {return RemainingQuantity ==0;}

    void Fill(Quantity quantity) {
        if (quantity > RemainingQuantity)
            throw std::logic_error {"Cannot fill order with less than its remaining quantity. "};
        RemainingQuantity -= quantity;
    }

private:
    OrderType type;
    OrderType2 type2;
    OrderId id;
    Side side;
    Price price;
    Quantity InitialQuantity;
    Quantity RemainingQuantity;
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

class OrderBook {
public:
    Trades AddOrder(OrderPointer order);
    void CancelOrder(OrderId id);
    std::size_t Size() const { return orders.size();}
private:
    Trades MatchOrders(OrderPointer incoming);

    std::map<Price, OrderPointers, std::greater<Price>> bids;
    std::map<Price, OrderPointers, std::less<Price>> asks;
    std::unordered_map<OrderId, OrderPointer> orders;
};

#endif //ORDERBOOK_ORDERBOOK_H
