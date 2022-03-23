#ifndef SERIALIZATION_HPP
#define SERIALIZATION_HPP

#include "serialization_types.hpp"
#include "serialization_iostream.hpp"
#include "vector_streambuff.h"

#ifndef NDEBUG
#include <set>
#include <map>
#include <array>
#include <deque>
#include <list>
#include <vector>
#include <string>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

static_assert(any_container<std::string>,                                   "std::string is not container!");
static_assert(any_container<std::array<char,5>>,                            "std::array is not container!");
static_assert(any_container<std::vector<char>>,                             "std::vector is not container!");
static_assert(any_container<std::deque<char>>,                              "std::deque is not container!");
static_assert(any_container<std::list<char>>,                               "std::forward_list is not container!");
static_assert(any_container<std::forward_list<char>>,                       "std::forward_list is not container!");
static_assert(any_container<std::set<char>>,                                "std::set is not container!");
static_assert(any_container<std::map<char,char>>,                           "std::map is not container!");
static_assert(any_container<std::multiset<char>>,                           "std::multiset is not container!");
static_assert(any_container<std::multimap<char,char>>,                      "std::multimap is not container!");
static_assert(any_container<std::unordered_set<char>>,                      "std::unordered_set is not container!");
static_assert(any_container<std::unordered_map<char,char>>,                 "std::unordered_map is not container!");
static_assert(any_container<std::unordered_multiset<char>>,                 "std::unordered_multiset is not container!");
static_assert(any_container<std::unordered_multimap<char,char>>,            "std::unordered_multimap is not container!");

static_assert(sequence_container<std::string>,                              "std::string is not sequence container!");
static_assert(sequence_container<std::array<char,5>>,                       "std::array is not sequence container!");
static_assert(sequence_container<std::vector<char>>,                        "std::vector is not sequence container!");
static_assert(sequence_container<std::deque<char>>,                         "std::deque is not sequence container!");
static_assert(sequence_container<std::list<char>>,                          "std::list is not sequence container!");
static_assert(sequence_container<std::forward_list<char>>,                  "std::forward_list is not sequence container!");
static_assert(!sequence_container<std::set<char>>,                          "std::set is sequence container!");
static_assert(!sequence_container<std::map<char,char>>,                     "std::map is sequence container!");
static_assert(!sequence_container<std::multiset<char>>,                     "std::multiset is sequence container!");
static_assert(!sequence_container<std::multimap<char,char>>,                "std::multimap is sequence container!");
static_assert(!sequence_container<std::unordered_set<char>>,                "std::unordered_set is sequence container!");
static_assert(!sequence_container<std::unordered_map<char,char>>,           "std::unordered_map is sequence container!");
static_assert(!sequence_container<std::unordered_multiset<char>>,           "std::unordered_multiset is sequence container!");
static_assert(!sequence_container<std::unordered_multimap<char,char>>,      "std::unordered_multimap is sequence container!");

static_assert(!associative_container<std::string>,                          "std::string is associative container!");
static_assert(!associative_container<std::array<char,5>>,                   "std::array is associative container!");
static_assert(!associative_container<std::vector<char>>,                    "std::vector is associative container!");
static_assert(!associative_container<std::deque<char>>,                     "std::deque is associative container!");
static_assert(!associative_container<std::list<char>>,                      "std::list is associative container!");
static_assert(!associative_container<std::forward_list<char>>,              "std::forward_list is associative container!");
static_assert(associative_container<std::set<char>>,                        "std::set is not associative container!");
static_assert(associative_container<std::map<char,char>>,                   "std::map is not associative container!");
static_assert(associative_container<std::multiset<char>>,                   "std::multiset is not associative container!");
static_assert(associative_container<std::multimap<char,char>>,              "std::multimap is not associative container!");
static_assert(associative_container<std::unordered_set<char>>,              "std::unordered_set is not associative container!");
static_assert(associative_container<std::unordered_map<char,char>>,         "std::unordered_map is not associative container!");
static_assert(associative_container<std::unordered_multiset<char>>,         "std::unordered_multiset is not associative container!");
static_assert(associative_container<std::unordered_multimap<char,char>>,    "std::unordered_multimap is not associative container!");

static_assert(!has_emplace_front<std::vector<char>>,                        "");
static_assert(has_emplace_front<std::list<char>>,                           "");
static_assert(has_emplace_front<std::deque<char>>,                          "");
static_assert(!has_emplace_front<std::string>,                              "");
static_assert(!has_emplace_front<std::array<char,3>>,                       "");
static_assert(has_emplace_front<std::forward_list<char>>,                   "");
static_assert(!has_emplace_front<std::set<char>>,                           "");
static_assert(!has_emplace_front<std::map<char,char>>,                      "");
static_assert(!has_emplace_front<std::multiset<char>>,                      "");
static_assert(!has_emplace_front<std::multimap<char,char>>,                 "");
static_assert(!has_emplace_front<std::unordered_set<char>>,                 "");
static_assert(!has_emplace_front<std::unordered_map<char,char>>,            "");
static_assert(!has_emplace_front<std::unordered_multiset<char>>,            "");
static_assert(!has_emplace_front<std::unordered_multimap<char,char>>,       "");

static_assert(has_emplace_back<std::vector<char>>,                          "");
static_assert(has_emplace_back<std::list<char>>,                            "");
static_assert(has_emplace_back<std::deque<char>>,                           "");
static_assert(!has_emplace_back<std::string>,                               "");
static_assert(!has_emplace_back<std::array<char,3>>,                        "");
static_assert(!has_emplace_back<std::forward_list<char>>,                   "");
static_assert(!has_emplace_back<std::set<char>>,                            "");
static_assert(!has_emplace_back<std::map<char,char>>,                       "");
static_assert(!has_emplace_back<std::multiset<char>>,                       "");
static_assert(!has_emplace_back<std::multimap<char,char>>,                  "");
static_assert(!has_emplace_back<std::unordered_set<char>>,                  "");
static_assert(!has_emplace_back<std::unordered_map<char,char>>,             "");
static_assert(!has_emplace_back<std::unordered_multiset<char>>,             "");
static_assert(!has_emplace_back<std::unordered_multimap<char,char>>,        "");

static_assert(!has_emplace<std::vector<char>>,                              "");
static_assert(!has_emplace<std::list<char>>,                                "");
static_assert(!has_emplace<std::deque<char>>,                               "");
static_assert(!has_emplace<std::string>,                                    "");
static_assert(!has_emplace<std::array<char,3>>,                             "");
static_assert(!has_emplace<std::forward_list<char>>,                        "");
static_assert(has_emplace<std::set<char>>,                                  "");
static_assert(has_emplace<std::map<char,char>>,                             "");
static_assert(has_emplace<std::multiset<char>>,                             "");
static_assert(has_emplace<std::multimap<char,char>>,                        "");
static_assert(has_emplace<std::unordered_set<char>>,                        "");
static_assert(has_emplace<std::unordered_map<char,char>>,                   "");
static_assert(has_emplace<std::unordered_multiset<char>>,                   "");
static_assert(has_emplace<std::unordered_multimap<char,char>>,              "");


#endif

#endif // SERIALIZATION_HPP
