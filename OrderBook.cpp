//
// Created by liamb on 10/19/2026.
//

#include "OrderBook.h"
#pragma once
#include <cstdint>
#include <vector>

//sides this stays firm
enum class Side: uint8_t
{
  Buy,
  Sell
};

enum class OrderType {
  FillAndKill,
  ExpiryOrder
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

int main() {

};