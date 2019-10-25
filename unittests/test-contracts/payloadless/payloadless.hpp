/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] payloadless : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void doit();
};
