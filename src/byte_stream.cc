#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  // Your code here.
  return is_close_;
}

void Writer::push( string data )
{
  // Your code here.
  if (is_close_) {
    return;
  }

  // uint64_t len = data.length();
  // for (uint64_t i = 0; i < len; i ++) {
  //   if (buffer_.size() < capacity_) {
  //     pushcnt_ ++;
  //     buffer_.push_back(data[i]);
  //   } else {
  //     set_error();
  //   }
  // }

  uint64_t push_size = std::min(data.length(), Writer::available_capacity());
  // buffer_.append(data.substr(0, push_size));
  buffer_ += data.substr(0, push_size);
  pushcnt_ += push_size;
}

void Writer::close()
{
  // Your code here.
  is_close_ = true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return (capacity_ - buffer_.size());
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return pushcnt_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return (is_close_  /* && buffer_.empty() */ && pushcnt_ == popcnt_);
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return popcnt_;
}

string_view Reader::peek() const
{
  // Your code here.
  if (buffer_.empty()) {
    return {};
  }
  
  return (std::string_view(buffer_));
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  // if (is_close_) {
  //   return;
  // }

  // for (uint64_t i = 0; i < len; i ++) {
  //   if (buffer_.empty()) {
  //     set_error();
  //   }
  //   buffer_.erase(0);
  // }

  uint64_t pop_size = std::min(len, buffer_.size());
  buffer_ = buffer_.substr(pop_size);
  popcnt_ += pop_size;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return (buffer_.size());
}
