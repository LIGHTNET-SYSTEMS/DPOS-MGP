/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] asserter : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void procassert( int8_t condition, std::string message );

   [[ltnio::action]]
   void provereset();
};
