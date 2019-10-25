/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] test_api_db : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action("pg")]]
   void primary_i64_general();

   [[ltnio::action("pl")]]
   void primary_i64_lowerbound();

   [[ltnio::action("pu")]]
   void primary_i64_upperbound();

   [[ltnio::action("s1g")]]
   void idx64_general();

   [[ltnio::action("s1l")]]
   void idx64_lowerbound();

   [[ltnio::action("s1u")]]
   void idx64_upperbound();

   [[ltnio::action("tia")]]
   void test_invalid_access( ltnio::name code, uint64_t val, uint32_t index, bool store );

   [[ltnio::action("sdnancreate")]]
   void idx_double_nan_create_fail();

   [[ltnio::action("sdnanmodify")]]
   void idx_double_nan_modify_fail();

   [[ltnio::action("sdnanlookup")]]
   void idx_double_nan_lookup_fail( uint32_t lookup_type );

   [[ltnio::action("sk32align")]]
   void misaligned_secondary_key256_tests();

};
