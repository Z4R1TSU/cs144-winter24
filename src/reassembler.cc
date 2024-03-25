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
    // write into byte stream
    output_.writer().push(buffer.top().begin()->second);
    // update the min_index
    modify_min_idx_to(buffer.top().begin()->first + 1);
    // decrement the pendcnt in the size of that substring
    decre_pendcnt(buffer.top().begin()->second.length());
    // pop the substring from reassembler
    buffer.pop();
  } else if (first_index == min_index) {
    // if this substring is the next, push it to byte stream
    output_.writer().push(data);
    modify_min_idx_to(first_index + 1);
    // we need to consider the case that if it exists more substrings whose index == min_index
    while (buffer.top().begin()->first == min_index && buffer.top().begin()->second.length() <= output_.writer().available_capacity()) {
      // just like what we did in the case above
      output_.writer().push(buffer.top().begin()->second);
      modify_min_idx_to(buffer.top().begin()->first + 1);
      decre_pendcnt(buffer.top().begin()->second.length());
      buffer.pop();
    } 
  } else if (data.length() <= output_.writer().available_capacity()) {
    // if still something remain, the substring should be staged in reassembler
    mm cur_element;
    cur_element[first_index] = data;

    buffer.push(cur_element);

    incre_pendcnt(data.length());
  }

  if (is_last_substring) {
    turnoff_stream();
  }
  if (get_stream()) {
    // write all substrings which in reassembler into the byte stream
    while (!buffer.empty()) {
      std::string cur_substring = buffer.top().begin()->second;
      output_.writer().push(cur_substring);
      decre_pendcnt(cur_substring.length());
      buffer.pop();
    }
  }
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  return get_pendcnt();
}
