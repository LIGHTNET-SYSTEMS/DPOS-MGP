/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] ram_restrictions_test : public ltnio::contract {
public:
   struct [[ltnio::table]] data {
      uint64_t           key;
      std::vector<char>  value;

      uint64_t primary_key() const { return key; }
   };

   typedef ltnio::multi_index<"tablea"_n, data> tablea;
   typedef ltnio::multi_index<"tableb"_n, data> tableb;

public:
   using ltnio::contract::contract;

   [[ltnio::action]]
   void noop();

   [[ltnio::action]]
   void setdata( uint32_t len1, uint32_t len2, ltnio::name payer );

   [[ltnio::action]]
   void notifysetdat( ltnio::name acctonotify, uint32_t len1, uint32_t len2, ltnio::name payer );

   [[ltnio::on_notify("tester2::notifysetdat")]]
   void on_notify_setdata( ltnio::name acctonotify, uint32_t len1, uint32_t len2, ltnio::name payer );

   [[ltnio::action]]
   void senddefer( uint64_t senderid, ltnio::name payer );

   [[ltnio::action]]
   void notifydefer( ltnio::name acctonotify, uint64_t senderid, ltnio::name payer );

   [[ltnio::on_notify("tester2::notifydefer")]]
   void on_notifydefer( ltnio::name acctonotify, uint64_t senderid, ltnio::name payer );

};
