#pragma once

#include <ltnio/chain/authority.hpp>
#include <ltnio/chain/chain_config.hpp>
#include <ltnio/chain/config.hpp>
#include <ltnio/chain/types.hpp>

namespace ltnio { namespace chain {

using action_name    = ltnio::chain::action_name;

struct newaccount {
   account_name                     creator;
   account_name                     name;
   authority                        owner;
   authority                        active;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(newaccount);
   }
};

struct setcode {
   account_name                     account;
   uint8_t                          vmtype = 0;
   uint8_t                          vmversion = 0;
   bytes                            code;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(setcode);
   }
};

struct setabi {
   account_name                     account;
   bytes                            abi;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(setabi);
   }
};


struct updateauth {
   account_name                      account;
   permission_name                   permission;
   permission_name                   parent;
   authority                         auth;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(updateauth);
   }
};

struct deleteauth {
   deleteauth() = default;
   deleteauth(const account_name& account, const permission_name& permission)
   :account(account), permission(permission)
   {}

   account_name                      account;
   permission_name                   permission;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(deleteauth);
   }
};

struct linkauth {
   linkauth() = default;
   linkauth(const account_name& account, const account_name& code, const action_name& type, const permission_name& requirement)
   :account(account), code(code), type(type), requirement(requirement)
   {}

   account_name                      account;
   account_name                      code;
   action_name                       type;
   permission_name                   requirement;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(linkauth);
   }
};

struct unlinkauth {
   unlinkauth() = default;
   unlinkauth(const account_name& account, const account_name& code, const action_name& type)
   :account(account), code(code), type(type)
   {}

   account_name                      account;
   account_name                      code;
   action_name                       type;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(unlinkauth);
   }
};

struct canceldelay {
   permission_level      canceling_auth;
   transaction_id_type   trx_id;

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(canceldelay);
   }
};

struct onerror {
   uint128_t      sender_id;
   bytes          sent_trx;

   onerror( uint128_t sid, const char* data, size_t len )
   :sender_id(sid),sent_trx(data,data+len){}

   static account_name get_account() {
      return config::system_account_name;
   }

   static action_name get_name() {
      return N(onerror);
   }
};

} } /// namespace ltnio::chain

FC_REFLECT( ltnio::chain::newaccount                       , (creator)(name)(owner)(active) )
FC_REFLECT( ltnio::chain::setcode                          , (account)(vmtype)(vmversion)(code) )
FC_REFLECT( ltnio::chain::setabi                           , (account)(abi) )
FC_REFLECT( ltnio::chain::updateauth                       , (account)(permission)(parent)(auth) )
FC_REFLECT( ltnio::chain::deleteauth                       , (account)(permission) )
FC_REFLECT( ltnio::chain::linkauth                         , (account)(code)(type)(requirement) )
FC_REFLECT( ltnio::chain::unlinkauth                       , (account)(code)(type) )
FC_REFLECT( ltnio::chain::canceldelay                      , (canceling_auth)(trx_id) )
FC_REFLECT( ltnio::chain::onerror                          , (sender_id)(sent_trx) )
