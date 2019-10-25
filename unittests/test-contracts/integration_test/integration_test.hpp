/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] integration_test : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void store( ltnio::name from, ltnio::name to, uint64_t num );

   struct [[ltnio::table("payloads")]] payload {
      uint64_t              key;
      std::vector<uint64_t> data;

      uint64_t primary_key()const { return key; }

      LTNLIB_SERIALIZE( payload, (key)(data) )
   };

   using payloads_table = ltnio::multi_index< "payloads"_n,  payload >;

};
