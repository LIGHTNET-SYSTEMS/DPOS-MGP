/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] noop : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void anyaction( ltnio::name                       from,
                   const ltnio::ignore<std::string>& type,
                   const ltnio::ignore<std::string>& data );
};
