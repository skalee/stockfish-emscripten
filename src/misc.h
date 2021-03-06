/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
  Copyright (C) 2008-2013 Marco Costalba, Joona Kiiski, Tord Romstad

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "types.h"

extern const std::string engine_info(bool to_uci = false);
extern void timed_wait(WaitCondition&, Lock&, int);
extern void prefetch(char* addr);
extern void start_logger(bool b);

extern void dbg_hit_on(bool b);
extern void dbg_hit_on_c(bool c, bool b);
extern void dbg_mean_of(int v);
extern void dbg_print();

extern "C" void emit_uci_response(const char*);

struct Log : public std::ofstream {
  Log(const std::string& f = "log.txt") : std::ofstream(f.c_str(), std::ios::out | std::ios::app) {}
 ~Log() { if (is_open()) close(); }
};


namespace Time {
  typedef int64_t point;
  inline point now() { return system_time_to_msec(); }
}


template<class Entry, int Size>
struct HashTable {
  HashTable() : e(Size, Entry()) {}
  Entry* operator[](Key k) { return &e[(uint32_t)k & (Size - 1)]; }

private:
  std::vector<Entry> e;
};


class EventedOStream : public std::ostream {

private:
  class EventedBuf : public std::stringbuf {
  public:
   ~EventedBuf() { pubsync(); }
    int sync();
  };

public:
  EventedOStream() : std::ostream(new EventedBuf) {}
 ~EventedOStream() { delete rdbuf(); }

};


extern EventedOStream eout;

#define sync_cout eout
#define sync_endl std::flush

#endif // #ifndef MISC_H_INCLUDED
