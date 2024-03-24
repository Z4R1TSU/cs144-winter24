#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  // if the stream is closed then return
  if (get_stream()) {
    return;
  }

  uint64_t min_index = get_min_idx();
  // if this index is shown before then ignore it
  if (first_index < min_index || buffer.top().begin()->first > min_index) {
    return;
  } else if (buffer.top().begin()->first == min_index) {
    output_.writer();
    modify_min_idx_to(buffer.top().begin()->first);
  } else if (first_index == min_index) {
    output_.writer();
    modify_min_idx_to(first_index);
  }

  // mm cur_element;
  // cur_element[first_index] = data;

  // buffer.push(cur_element);

  // incre_pendcnt(data.length());

  if (is_last_substring) {
    turnoff_stream();
  }
  if (get_stream()) {
    // write all substrings which in reassembler into the byte stream
    output_.writer();
  }
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return get_pendcnt();
}
