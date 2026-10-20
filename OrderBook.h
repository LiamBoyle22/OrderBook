//
// Created by liamb on 10/19/2026.
//

#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H
#pragma once
#include <vector>
#include <cstdint>
#include <stdexcept>

//sides this stays firm
enum class Side: uint8_t
{
    Buy,
    Sell
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
    Order(OrderType type, OrderId id, Price price, Quantity quantity)
        : type {type}, id {id}, side {side}, price {price}, InitialQuantity {quantity}, RemainingQuantity {quantity}
    {}

    OrderId GetId() const {return id;}
    Side GetSide() const {return side;}
    Price GetPrice() const {return price;}
    OrderType GetType() const {return type;}
    Quantity GetInitialQuantity() const {return InitialQuantity;}
    Quantity GetRemainingQuantity() const {return RemainingQuantity;}
    Quantity GetFilledQuantity() const {return InitialQuantity - RemainingQuantity;}
    bool IsFilled() const {return RemainingQuantity ==0;}

    void Fill(Quantity quantity) {
        if (quantity > RemainingQuantity)
            throw std::logic_error {"Cannot fill order with less than its remaining quantity. "};
        RemainingQuantity = quantity;
    }

private:
    OrderType type;
    OrderId id;
    Side side;
    Price price;
    Quantity InitialQuantity;
    Quantity RemainingQuantity;
};

using OrderPointer
#endif //ORDERBOOK_ORDERBOOK_H
