/**
 *  @file
 *  @copyright defined in ltn/LICENSE
 */
#include <iostream>

#include <boost/test/unit_test.hpp>

#include <fc/network/message_buffer.hpp>

namespace ltnio {
using namespace std;

size_t mb_size(boost::asio::mutable_buffer& mb) {
#if BOOST_VERSION >= 106600
   return mb.size();
#else
   return boost::asio::detail::buffer_size_helper(mb);
#endif
}

void* mb_data(boost::asio::mutable_buffer& mb) {
#if BOOST_VERSION >= 106600
   return mb.data();
#else
   return boost::asio::detail::buffer_cast_helper(mb);
#endif
}

BOOST_AUTO_TEST_SUITE(message_buffer_tests)

constexpr size_t     def_buffer_size_mb = 4;
constexpr size_t     def_buffer_size = 1024*1024*def_buffer_size_mb;

/// Test default construction and buffer sequence generation
BOOST_AUTO_TEST_CASE(message_buffer_construction)
{
  try {
    fc::message_buffer<def_buffer_size> mb;
    BOOST_CHECK_EQUAL(mb.total_bytes(), def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0u);
    BOOST_CHECK_EQUAL(mb.read_ptr(), mb.write_ptr());

    auto mbs = mb.get_buffer_sequence_for_boost_async_read();
    auto mbsi = mbs.begin();
    BOOST_CHECK_EQUAL(mb_size(*mbsi), def_buffer_size);
    BOOST_CHECK_EQUAL(mb_data(*mbsi), mb.write_ptr());
    mbsi++;
    BOOST_CHECK(mbsi == mbs.end());
  }
  FC_LOG_AND_RETHROW()
}

/// Test buffer growth and shrinking
BOOST_AUTO_TEST_CASE(message_buffer_growth)
{
  try {
    fc::message_buffer<def_buffer_size> mb;
    mb.add_buffer_to_chain();
    BOOST_CHECK_EQUAL(mb.total_bytes(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0u);
    BOOST_CHECK_EQUAL(mb.read_ptr(), mb.write_ptr());

    {
      auto mbs = mb.get_buffer_sequence_for_boost_async_read();
      auto mbsi = mbs.begin();
      BOOST_CHECK_EQUAL(mb_size(*mbsi), def_buffer_size);
      BOOST_CHECK_EQUAL(mb_data(*mbsi), mb.write_ptr());
      mbsi++;
      BOOST_CHECK(mbsi != mbs.end());
      BOOST_CHECK_EQUAL(mb_size(*mbsi), def_buffer_size);
      BOOST_CHECK_NE(mb_data(*mbsi), nullptr);
      mbsi++;
      BOOST_CHECK(mbsi == mbs.end());
    }

    mb.advance_write_ptr(100);
    BOOST_CHECK_EQUAL(mb.total_bytes(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), 2 * def_buffer_size - 100);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 100u);
    BOOST_CHECK_NE(mb.read_ptr(), nullptr);
    BOOST_CHECK_NE(mb.write_ptr(), nullptr);
    BOOST_CHECK_EQUAL((mb.read_ptr() + 100), mb.write_ptr());

    {
      auto mbs = mb.get_buffer_sequence_for_boost_async_read();
      auto mbsi = mbs.begin();
      BOOST_CHECK_EQUAL(mb_size(*mbsi), def_buffer_size - 100);
      BOOST_CHECK_EQUAL(mb_data(*mbsi), mb.write_ptr());
      mbsi++;
      BOOST_CHECK(mbsi != mbs.end());
      BOOST_CHECK_EQUAL(mb_size(*mbsi), def_buffer_size);
      BOOST_CHECK_NE(mb_data(*mbsi), nullptr);
      mbsi++;
      BOOST_CHECK(mbsi == mbs.end());
    }

    mb.advance_read_ptr(50);
    BOOST_CHECK_EQUAL(mb.total_bytes(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), 2 * def_buffer_size - 100);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 50u);

    mb.advance_write_ptr(def_buffer_size);
    BOOST_CHECK_EQUAL(mb.total_bytes(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), def_buffer_size - 100);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 50 + def_buffer_size);

    // Moving read_ptr into second block should reset second block to first
    mb.advance_read_ptr(def_buffer_size);
    BOOST_CHECK_EQUAL(mb.total_bytes(), def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), def_buffer_size - 100);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 50u);

    // Moving read_ptr to write_ptr should shrink chain and reset ptrs
    mb.advance_read_ptr(50);
    BOOST_CHECK_EQUAL(mb.total_bytes(), def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0u);

    mb.add_buffer_to_chain();
    BOOST_CHECK_EQUAL(mb.total_bytes(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0u);

    mb.advance_write_ptr(50);
    BOOST_CHECK_EQUAL(mb.total_bytes(), 2 * def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), 2 * def_buffer_size - 50);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 50u);

    // Moving read_ptr to write_ptr should shrink chain and reset ptrs
    mb.advance_read_ptr(50);
    BOOST_CHECK_EQUAL(mb.total_bytes(), def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_write(), def_buffer_size);
    BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0u);
  }
  FC_LOG_AND_RETHROW()
}

/// Test peek and read across multiple buffers
BOOST_AUTO_TEST_CASE(message_buffer_peek_read)
{
  try {
    {
      const uint32_t small = 32;
      fc::message_buffer<small> mb;
      BOOST_CHECK_EQUAL(mb.total_bytes(), small);
      BOOST_CHECK_EQUAL(mb.bytes_to_write(), small);
      BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0);
      BOOST_CHECK_EQUAL(mb.read_ptr(), mb.write_ptr());
      BOOST_CHECK_EQUAL(mb.read_index().first, 0);
      BOOST_CHECK_EQUAL(mb.read_index().second, 0);
      BOOST_CHECK_EQUAL(mb.write_index().first, 0);
      BOOST_CHECK_EQUAL(mb.write_index().second, 0);

      mb.add_space(100 - small);
      BOOST_CHECK_EQUAL(mb.total_bytes(), 4 * small);
      BOOST_CHECK_EQUAL(mb.bytes_to_write(), 4 * small);
      BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0);
      BOOST_CHECK_EQUAL(mb.read_ptr(), mb.write_ptr());

      char* write_ptr = mb.write_ptr();
      for (char ind = 0; ind < 100; ) {
        *write_ptr = ind;
        ind++;
        if (ind % small == 0) {
          mb.advance_write_ptr(small);
          write_ptr = mb.write_ptr();
        } else {
          write_ptr++;
        }
      }
      mb.advance_write_ptr(100 % small);

      BOOST_CHECK_EQUAL(mb.total_bytes(), 4 * small);
      BOOST_CHECK_EQUAL(mb.bytes_to_write(), 4 * small - 100);
      BOOST_CHECK_EQUAL(mb.bytes_to_read(), 100);
      BOOST_CHECK_NE((void*) mb.read_ptr(), (void*) mb.write_ptr());
      BOOST_CHECK_EQUAL(mb.read_index().first, 0);
      BOOST_CHECK_EQUAL(mb.read_index().second, 0);
      BOOST_CHECK_EQUAL(mb.write_index().first, 3);
      BOOST_CHECK_EQUAL(mb.write_index().second, 4);

      char buffer[100];
      auto index = mb.read_index();
      mb.peek(buffer, 50, index);
      mb.peek(buffer+50, 50, index);
      for (int i=0; i < 100; i++) {
        BOOST_CHECK_EQUAL(i, buffer[i]);
      }

      BOOST_CHECK_EQUAL(mb.total_bytes(), 4 * small);
      BOOST_CHECK_EQUAL(mb.bytes_to_write(), 4 * small - 100);
      BOOST_CHECK_EQUAL(mb.bytes_to_read(), 100);
      BOOST_CHECK_NE((void*) mb.read_ptr(), (void*) mb.write_ptr());

      char buffer2[100];
      mb.read(buffer2, 100);
      for (int i=0; i < 100; i++) {
        BOOST_CHECK_EQUAL(i, buffer2[i]);
      }

      BOOST_CHECK_EQUAL(mb.total_bytes(), small);
      BOOST_CHECK_EQUAL(mb.bytes_to_write(), small);
      BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0);
      BOOST_CHECK_EQUAL(mb.read_ptr(), mb.write_ptr());
    }
  }
  FC_LOG_AND_RETHROW()
}

/// Test automatic allocation when advancing the read_ptr to the end.
BOOST_AUTO_TEST_CASE(message_buffer_write_ptr_to_end)
{
  try {
    {
      const uint32_t small = 32;
      fc::message_buffer<small> mb;
      BOOST_CHECK_EQUAL(mb.total_bytes(), small);
      BOOST_CHECK_EQUAL(mb.bytes_to_write(), small);
      BOOST_CHECK_EQUAL(mb.bytes_to_read(), 0);
      BOOST_CHECK_EQUAL(mb.read_ptr(), mb.write_ptr());
      BOOST_CHECK_EQUAL(mb.read_index().first, 0);
      BOOST_CHECK_EQUAL(mb.read_index().second, 0);
      BOOST_CHECK_EQUAL(mb.write_index().first, 0);
      BOOST_CHECK_EQUAL(mb.write_index().second, 0);

      char* write_ptr = mb.write_ptr();
      for (uint32_t ind = 0; ind < small; ind++) {
        *write_ptr = ind;
        write_ptr++;
      }
      mb.advance_write_ptr(small);

      BOOST_CHECK_EQUAL(mb.total_bytes(), 2 * small);
      BOOST_CHECK_EQUAL(mb.bytes_to_write(), small);
      BOOST_CHECK_EQUAL(mb.bytes_to_read(), small);
      BOOST_CHECK_NE((void*) mb.read_ptr(), (void*) mb.write_ptr());
      BOOST_CHECK_EQUAL(mb.read_index().first, 0);
      BOOST_CHECK_EQUAL(mb.read_index().second, 0);
      BOOST_CHECK_EQUAL(mb.write_index().first, 1);
      BOOST_CHECK_EQUAL(mb.write_index().second, 0);

      auto mbs = mb.get_buffer_sequence_for_boost_async_read();
      auto mbsi = mbs.begin();
      BOOST_CHECK_EQUAL(mb_size(*mbsi), small);
      BOOST_CHECK_EQUAL(mb_data(*mbsi), mb.write_ptr());
      BOOST_CHECK_EQUAL(mb.read_ptr()+small, mb.write_ptr());
      mbsi++;
      BOOST_CHECK(mbsi == mbs.end());
    }
  }
  FC_LOG_AND_RETHROW()
}

BOOST_AUTO_TEST_CASE(message_buffer_read_peek_bounds) {
   using my_message_buffer_t = fc::message_buffer<1024>;
   my_message_buffer_t mbuff;
   unsigned char stuff[] = {
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
   };
   memcpy(mbuff.write_ptr(), stuff, sizeof(stuff));
   mbuff.advance_write_ptr(sizeof(stuff));

   my_message_buffer_t::index_t index = mbuff.read_index();
   uint8_t throw_away_buffer[4];
   mbuff.peek(&throw_away_buffer, 4, index); //8 bytes left to peek afterwards
   mbuff.peek(&throw_away_buffer, 4, index); //4 bytes left to peek afterwards
   mbuff.peek(&throw_away_buffer, 2, index); //2 bytes left to peek afterwards
   BOOST_CHECK_THROW(mbuff.peek(&throw_away_buffer, 3, index), fc::out_of_range_exception);
   mbuff.peek(&throw_away_buffer, 1, index); //1 byte left to peek afterwards
   mbuff.peek(&throw_away_buffer, 0, index); //1 byte left to peek afterwards
   mbuff.peek(&throw_away_buffer, 1, index); //no bytes left to peek afterwards
   BOOST_CHECK_THROW(mbuff.peek(&throw_away_buffer, 1, index), fc::out_of_range_exception);

   mbuff.read(&throw_away_buffer, 4); //8 bytes left to read afterwards
   mbuff.read(&throw_away_buffer, 4); //4 bytes left to read afterwards
   mbuff.read(&throw_away_buffer, 2); //2 bytes left to read afterwards
   BOOST_CHECK_THROW(mbuff.read(&throw_away_buffer, 4), fc::out_of_range_exception);
   mbuff.read(&throw_away_buffer, 1); //1 byte left to read afterwards
   mbuff.read(&throw_away_buffer, 0); //1 byte left to read afterwards
   mbuff.read(&throw_away_buffer, 1); //no bytes left to read afterwards
   BOOST_CHECK_THROW(mbuff.read(&throw_away_buffer, 1), fc::out_of_range_exception);
}

BOOST_AUTO_TEST_CASE(message_buffer_read_peek_bounds_multi) {
   using my_message_buffer_t = fc::message_buffer<5>;
   my_message_buffer_t mbuff;
   unsigned char stuff[] = {
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
   };
   memcpy(mbuff.write_ptr(), stuff, 5);
   mbuff.advance_write_ptr(5);
   memcpy(mbuff.write_ptr(), stuff+5, 5);
   mbuff.advance_write_ptr(5);
   memcpy(mbuff.write_ptr(), stuff+10, 2);
   mbuff.advance_write_ptr(2);

   my_message_buffer_t::index_t index = mbuff.read_index();
   uint8_t throw_away_buffer[4];
   mbuff.peek(&throw_away_buffer, 4, index); //8 bytes left to peek afterwards
   mbuff.peek(&throw_away_buffer, 4, index); //4 bytes left to peek afterwards
   mbuff.peek(&throw_away_buffer, 2, index); //2 bytes left to peek afterwards
   BOOST_CHECK_THROW(mbuff.peek(&throw_away_buffer, 3, index), fc::out_of_range_exception);
   mbuff.peek(&throw_away_buffer, 1, index); //1 bytes left to peek afterwards
   mbuff.peek(&throw_away_buffer, 0, index); //1 bytes left to peek afterwards
   mbuff.peek(&throw_away_buffer, 1, index); //no bytes left to peek afterwards
   BOOST_CHECK_THROW(mbuff.peek(&throw_away_buffer, 1, index), fc::out_of_range_exception);

   mbuff.read(&throw_away_buffer, 4); //8 bytes left to read afterwards
   mbuff.read(&throw_away_buffer, 4); //4 bytes left to read afterwards
   mbuff.read(&throw_away_buffer, 2); //2 bytes left to read afterwards
   BOOST_CHECK_THROW(mbuff.read(&throw_away_buffer, 4), fc::out_of_range_exception);
   mbuff.read(&throw_away_buffer, 1); //1 bytes left to read afterwards
   mbuff.read(&throw_away_buffer, 0); //1 bytes left to read afterwards
   mbuff.read(&throw_away_buffer, 1); //no bytes left to read afterwards
   BOOST_CHECK_THROW(mbuff.read(&throw_away_buffer, 1), fc::out_of_range_exception);
}

BOOST_AUTO_TEST_CASE(message_buffer_datastream) {
   using my_message_buffer_t = fc::message_buffer<1024>;
   my_message_buffer_t mbuff;

   char buf[1024];
   fc::datastream<char*> ds( buf, 1024 );

   int v = 13;
   fc::raw::pack( ds, v );
   v = 42;
   fc::raw::pack( ds, 42 );
   fc::raw::pack( ds, std::string( "hello" ) );

   memcpy(mbuff.write_ptr(), buf, 1024);
   mbuff.advance_write_ptr(1024);

   for( int i = 0; i < 3; ++i ) {
      auto ds2 = mbuff.create_peek_datastream();
      fc::raw::unpack( ds2, v );
      BOOST_CHECK_EQUAL( 13, v );
      fc::raw::unpack( ds2, v );
      BOOST_CHECK_EQUAL( 42, v );
      std::string s;
      fc::raw::unpack( ds2, s );
      BOOST_CHECK_EQUAL( s, std::string( "hello" ) );
   }

   {
      auto ds2 = mbuff.create_datastream();
      fc::raw::unpack( ds2, v );
      BOOST_CHECK_EQUAL( 13, v );
      fc::raw::unpack( ds2, v );
      BOOST_CHECK_EQUAL( 42, v );
      std::string s;
      fc::raw::unpack( ds2, s );
      BOOST_CHECK_EQUAL( s, std::string( "hello" ) );
   }
}

BOOST_AUTO_TEST_SUITE_END()

} // namespace ltnio
