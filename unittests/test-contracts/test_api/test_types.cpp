/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#include <ltniolib/ltnio.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   ltnio_assert( sizeof(int64_t)   ==  8, "int64_t size != 8"   );
   ltnio_assert( sizeof(uint64_t)  ==  8, "uint64_t size != 8"  );
   ltnio_assert( sizeof(uint32_t)  ==  4, "uint32_t size != 4"  );
   ltnio_assert( sizeof(int32_t)   ==  4, "int32_t size != 4"   );
   ltnio_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   ltnio_assert( sizeof(int128_t)  == 16, "int128_t size != 16" );
   ltnio_assert( sizeof(uint8_t)   ==  1, "uint8_t size != 1"   );

   ltnio_assert( sizeof(ltnio::name) ==  8, "name size !=  8");
}

void test_types::char_to_symbol() {

   ltnio_assert( ltnio::name::char_to_value('1') ==  1, "ltnio::char_to_symbol('1') !=  1" );
   ltnio_assert( ltnio::name::char_to_value('2') ==  2, "ltnio::char_to_symbol('2') !=  2" );
   ltnio_assert( ltnio::name::char_to_value('3') ==  3, "ltnio::char_to_symbol('3') !=  3" );
   ltnio_assert( ltnio::name::char_to_value('4') ==  4, "ltnio::char_to_symbol('4') !=  4" );
   ltnio_assert( ltnio::name::char_to_value('5') ==  5, "ltnio::char_to_symbol('5') !=  5" );
   ltnio_assert( ltnio::name::char_to_value('a') ==  6, "ltnio::char_to_symbol('a') !=  6" );
   ltnio_assert( ltnio::name::char_to_value('b') ==  7, "ltnio::char_to_symbol('b') !=  7" );
   ltnio_assert( ltnio::name::char_to_value('c') ==  8, "ltnio::char_to_symbol('c') !=  8" );
   ltnio_assert( ltnio::name::char_to_value('d') ==  9, "ltnio::char_to_symbol('d') !=  9" );
   ltnio_assert( ltnio::name::char_to_value('e') == 10, "ltnio::char_to_symbol('e') != 10" );
   ltnio_assert( ltnio::name::char_to_value('f') == 11, "ltnio::char_to_symbol('f') != 11" );
   ltnio_assert( ltnio::name::char_to_value('g') == 12, "ltnio::char_to_symbol('g') != 12" );
   ltnio_assert( ltnio::name::char_to_value('h') == 13, "ltnio::char_to_symbol('h') != 13" );
   ltnio_assert( ltnio::name::char_to_value('i') == 14, "ltnio::char_to_symbol('i') != 14" );
   ltnio_assert( ltnio::name::char_to_value('j') == 15, "ltnio::char_to_symbol('j') != 15" );
   ltnio_assert( ltnio::name::char_to_value('k') == 16, "ltnio::char_to_symbol('k') != 16" );
   ltnio_assert( ltnio::name::char_to_value('l') == 17, "ltnio::char_to_symbol('l') != 17" );
   ltnio_assert( ltnio::name::char_to_value('m') == 18, "ltnio::char_to_symbol('m') != 18" );
   ltnio_assert( ltnio::name::char_to_value('n') == 19, "ltnio::char_to_symbol('n') != 19" );
   ltnio_assert( ltnio::name::char_to_value('o') == 20, "ltnio::char_to_symbol('o') != 20" );
   ltnio_assert( ltnio::name::char_to_value('p') == 21, "ltnio::char_to_symbol('p') != 21" );
   ltnio_assert( ltnio::name::char_to_value('q') == 22, "ltnio::char_to_symbol('q') != 22" );
   ltnio_assert( ltnio::name::char_to_value('r') == 23, "ltnio::char_to_symbol('r') != 23" );
   ltnio_assert( ltnio::name::char_to_value('s') == 24, "ltnio::char_to_symbol('s') != 24" );
   ltnio_assert( ltnio::name::char_to_value('t') == 25, "ltnio::char_to_symbol('t') != 25" );
   ltnio_assert( ltnio::name::char_to_value('u') == 26, "ltnio::char_to_symbol('u') != 26" );
   ltnio_assert( ltnio::name::char_to_value('v') == 27, "ltnio::char_to_symbol('v') != 27" );
   ltnio_assert( ltnio::name::char_to_value('w') == 28, "ltnio::char_to_symbol('w') != 28" );
   ltnio_assert( ltnio::name::char_to_value('x') == 29, "ltnio::char_to_symbol('x') != 29" );
   ltnio_assert( ltnio::name::char_to_value('y') == 30, "ltnio::char_to_symbol('y') != 30" );
   ltnio_assert( ltnio::name::char_to_value('z') == 31, "ltnio::char_to_symbol('z') != 31" );

   for(unsigned char i = 0; i<255; i++) {
      if( (i >= 'a' && i <= 'z') || (i >= '1' || i <= '5') ) continue;
      ltnio_assert( ltnio::name::char_to_value((char)i) == 0, "ltnio::char_to_symbol() != 0" );
   }
}

void test_types::string_to_name() {
   return;
   ltnio_assert( ltnio::name("a") == "a"_n, "ltnio::string_to_name(a)" );
   ltnio_assert( ltnio::name("ba") == "ba"_n, "ltnio::string_to_name(ba)" );
   ltnio_assert( ltnio::name("cba") == "cba"_n, "ltnio::string_to_name(cba)" );
   ltnio_assert( ltnio::name("dcba") == "dcba"_n, "ltnio::string_to_name(dcba)" );
   ltnio_assert( ltnio::name("edcba") == "edcba"_n, "ltnio::string_to_name(edcba)" );
   ltnio_assert( ltnio::name("fedcba") == "fedcba"_n, "ltnio::string_to_name(fedcba)" );
   ltnio_assert( ltnio::name("gfedcba") == "gfedcba"_n, "ltnio::string_to_name(gfedcba)" );
   ltnio_assert( ltnio::name("hgfedcba") == "hgfedcba"_n, "ltnio::string_to_name(hgfedcba)" );
   ltnio_assert( ltnio::name("ihgfedcba") == "ihgfedcba"_n, "ltnio::string_to_name(ihgfedcba)" );
   ltnio_assert( ltnio::name("jihgfedcba") == "jihgfedcba"_n, "ltnio::string_to_name(jihgfedcba)" );
   ltnio_assert( ltnio::name("kjihgfedcba") == "kjihgfedcba"_n, "ltnio::string_to_name(kjihgfedcba)" );
   ltnio_assert( ltnio::name("lkjihgfedcba") == "lkjihgfedcba"_n, "ltnio::string_to_name(lkjihgfedcba)" );
   ltnio_assert( ltnio::name("mlkjihgfedcba") == "mlkjihgfedcba"_n, "ltnio::string_to_name(mlkjihgfedcba)" );
}
