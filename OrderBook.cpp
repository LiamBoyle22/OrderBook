//
// Created by liamb on 10/19/2026.
//

#include "OrderBook.h"
#pragma once
#include <cstdint>

//sides this stays firm
enum class Side: uint8_t
{
  Buy,
  Sell
};

//now we make our dependant values for our buy or sell side items
using OrderId = uint64_t;
using Price = int64_t;
using Quantity = uint32_t;

//now we initialise the order it self
struct Order {
  OrderId id;
  Side side;
  Price price;
  Quantity quantity;

  Order (OrderId id, Side side, Price price, Quantity quantity)
    : id(id), side(side), price(price), quantity(quantity) {}
};