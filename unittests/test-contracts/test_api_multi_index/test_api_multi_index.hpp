/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#pragma once

#include <ltnio/ltnio.hpp>

class [[ltnio::contract]] test_api_multi_index : public ltnio::contract {
public:
   using ltnio::contract::contract;

   [[ltnio::action("s1g")]]
   void idx64_general();

   [[ltnio::action("s1store")]]
   void idx64_store_only();

   [[ltnio::action("s1check")]]
   void idx64_check_without_storing();

   [[ltnio::action("s1findfail1")]]
   void idx64_require_find_fail();

   [[ltnio::action("s1findfail2")]]
   void idx64_require_find_fail_with_msg();

   [[ltnio::action("s1findfail3")]]
   void idx64_require_find_sk_fail();

   [[ltnio::action("s1findfail4")]]
   void idx64_require_find_sk_fail_with_msg();

   [[ltnio::action("s1pkend")]]
   void idx64_pk_iterator_exceed_end();

   [[ltnio::action("s1skend")]]
   void idx64_sk_iterator_exceed_end();

   [[ltnio::action("s1pkbegin")]]
   void idx64_pk_iterator_exceed_begin();

   [[ltnio::action("s1skbegin")]]
   void idx64_sk_iterator_exceed_begin();

   [[ltnio::action("s1pkref")]]
   void idx64_pass_pk_ref_to_other_table();

   [[ltnio::action("s1skref")]]
   void idx64_pass_sk_ref_to_other_table();

   [[ltnio::action("s1pkitrto")]]
   void idx64_pass_pk_end_itr_to_iterator_to();

   [[ltnio::action("s1pkmodify")]]
   void idx64_pass_pk_end_itr_to_modify();

   [[ltnio::action("s1pkerase")]]
   void idx64_pass_pk_end_itr_to_erase();

   [[ltnio::action("s1skitrto")]]
   void idx64_pass_sk_end_itr_to_iterator_to();

   [[ltnio::action("s1skmodify")]]
   void idx64_pass_sk_end_itr_to_modify();

   [[ltnio::action("s1skerase")]]
   void idx64_pass_sk_end_itr_to_erase();

   [[ltnio::action("s1modpk")]]
   void idx64_modify_primary_key();

   [[ltnio::action("s1exhaustpk")]]
   void idx64_run_out_of_avl_pk();

   [[ltnio::action("s1skcache")]]
   void idx64_sk_cache_pk_lookup();

   [[ltnio::action("s1pkcache")]]
   void idx64_pk_cache_sk_lookup();

   [[ltnio::action("s2g")]]
   void idx128_general();

   [[ltnio::action("s2store")]]
   void idx128_store_only();

   [[ltnio::action("s2check")]]
   void idx128_check_without_storing();

   [[ltnio::action("s2autoinc")]]
   void idx128_autoincrement_test();

   [[ltnio::action("s2autoinc1")]]
   void idx128_autoincrement_test_part1();

   [[ltnio::action("s2autoinc2")]]
   void idx128_autoincrement_test_part2();

   [[ltnio::action("s3g")]]
   void idx256_general();

   [[ltnio::action("sdg")]]
   void idx_double_general();

   [[ltnio::action("sldg")]]
   void idx_long_double_general();

};
