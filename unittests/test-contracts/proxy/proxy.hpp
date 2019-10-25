/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>
#include <ltnio/singleton.hpp>
#include <ltnio/asset.hpp>

// Extacted from ltnio.token contract:
namespace ltnio {
   class [[ltnio::contract("ltnio.token")]] token : public ltnio::contract {
   public:
      using ltnio::contract::contract;

      [[ltnio::action]]
      void transfer( ltnio::name        from,
                     ltnio::name        to,
                     ltnio::asset       quantity,
                     const std::string& memo );
      using transfer_action = ltnio::action_wrapper<"transfer"_n, &token::transfer>;
   };
}

// This contract:
class [[ltnio::contract]] proxy : public ltnio::contract {
public:
   proxy( ltnio::name self, ltnio::name first_receiver, ltnio::datastream<const char*> ds );

   [[ltnio::action]]
   void setowner( ltnio::name owner, uint32_t delay );

   [[ltnio::on_notify("ltnio.token::transfer")]]
   void on_transfer( ltnio::name        from,
                     ltnio::name        to,
                     ltnio::asset       quantity,
                     const std::string& memo );

   [[ltnio::on_notify("ltnio::onerror")]]
   void on_error( uint128_t sender_id, ltnio::ignore<std::vector<char>> sent_trx );

   struct [[ltnio::table]] config {
      ltnio::name owner;
      uint32_t    delay   = 0;
      uint32_t    next_id = 0;

      LTNLIB_SERIALIZE( config, (owner)(delay)(next_id) )
   };

   using config_singleton = ltnio::singleton< "config"_n,  config >;

protected:
   config_singleton _config;
};
