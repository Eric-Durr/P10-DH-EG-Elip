

/*!
 *  @file   lfsr.hpp 
 *  @brief  Linear Feedback Shift Register object template tool 
 *  @author Eric Dürr Sierra 
 *  @date   2021-04-02 
 * 
 * # LFSR object class template
 * 
 * Due to the common use in cyphering engines, this class
 * is made to contain an LFSR object wich can be described
 * by it's lenght and taps.
 * 
 * ## Usage
 * There are multiple ways to use the constructor:
 * 
 * **default**
 * ```cpp
 * LFSR<int> my_int_set;
 * // length = 1
 * // content by default = [ 1 ]
 * // no taps
 * ```
 * 
 * **only length**
 * ```cpp
 * LFSR<int> my_int_set(10);
 * // length = 10
 * // content by default = [ 1 1 1 1 1 1 1 1 1 1 ]
 * // no taps
 * ```
 * 
 * **length and taps**
 * ```cpp
 * LFSR<int> my_int_set(10, {2, 9});
 * // length = 10
 * // content by default = [ 1 1 1 1 1 1 1 1 1 1 ]
 * //                            ^             ^
 * ```
 * > Keep in mind that taps uses the vector position so n is m-1
 * >  (tap 10 is 9)
 * 
 * **length, taps and default value**
 * ```cpp
 * LFSR<int> my_int_set(10, {2, 9}, 0);
 * // length = 10
 * // content by default = [ 0 0 0 0 0 0 0 0 0 0 ]
 * //                            ^             ^
 * ```
 * 
 * > Copy constructor is defined too, so you can use the 
 * = operator
 * 
 * ### Methods
 *
 * **Selection operator ( [] )**
 * ```cpp
 * LFSR<int> my_secuence(10, {2,9});
 * int value_at_5 = secuence[5] // value_at_5 = 1
 * ```
 * 
 * **Length value getter**
 * ```cpp
 * LFSR<int> my_secuence(10, {2,9});
 * int my_length = my_secuence.length() // my_length = 10
 * ```
 * 
 * **Length state **
 * ```cpp
 * LFSR<int> my_secuence(10, {2,9});
 * int my_length = my_secuence.length() // my_length = 10
 * ```
 * 
 * **step shift method**
 * Operates one step in the LFSR according to taps
 * ```cpp
 * LFSR<int> my_secuence(10, {2,9}); // [ 1 1 1 1 1 1 1 1 1 1 ]
 * my_secuence.step() // [ 0 1 1 1 1 1 1 1 1 1 ]
 * ```
 * **generate shift method**
 * Operates a number of steps and returns the full secuence
 * ```cpp
 * LFSR<int> my_secuence(10, {2,9}); // [ 1 1 1 1 1 1 1 1 1 1 ]
 * LFSR<int> returned = my_secuence.generate(5) 
 * // my_secuence [ 1 1 0 0 0 1 1 1 1 1 1 1 ] 
 * // returned [ 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ]
 * ```
 * **String format method**
 * Ouputs a string value of the secuence
 * ```cpp
 * LFSR<int> my_secuence(10, {2,9}); // [ 1 1 1 1 1 1 1 1 1 1 ]
 * std::cout << my_secuence.to_string() << std::endl
 * // [ 1 1 1 1 1 1 1 1 1 1 ]
 * //       ^             ^
 * ```
 * > Observe that the taps are marked with '^'
 *  
 * @copyright Copyright 2021 Eric Dürr. All rights reserved 
 * @par This project is released under the GNU Public License.
 * */

#ifndef LFSR_H_
#define LFSR_H_

#include <vector>
#include <string>
#include <set>

template <class T>
class LFSR
{
private:
  int length_;
  std::vector<T> lfsr_set_;
  std::set<int> taps_;

public:
  LFSR(const int &length = 1, const std::set<int> &taps = {}, const T &def_input = 1);
  LFSR(const LFSR<T> &other);
  ~LFSR();

  const T &at(int pos) const { return lfsr_set_[pos]; };
  T &at(int pos) { return lfsr_set_[pos]; };

  const int &length(void) const { return length_; }

  const std::set<int> &taps(void) const { return taps_; }

  std::string to_string(void) const;

  T step(void);
  // L
  LFSR<T> generate(int steps);

  const T &operator[](int pos) const { return this->at(pos); }
  T &operator[](int pos) { return this->at(pos); }

  void rotate_ri(const T &new_element);
  void rotate_le(const T &new_element);

private:
  void initialize(const T &def_input);
  void push_back(const T &new_element, LFSR<T> &secuence);
  bool is_a_tap(const int &i) const;
};

template <class T>
LFSR<T>::LFSR(const int &length, const std::set<int> &taps, const T &def_input)
    : length_(length), taps_(taps)
{
  this->initialize(def_input);
}

template <class T>
LFSR<T>::LFSR(const LFSR<T> &other)
    : length_(other.length_),
      taps_(other.taps_)
{
  for (auto element : other.lfsr_set_)
    this->lfsr_set_.push_back(element);
}

template <class T>
LFSR<T>::~LFSR() {}

template <class T>
std::string LFSR<T>::to_string(void) const
{
  std::string output = "\n[ ";
  for (auto element : lfsr_set_)
    output += std::to_string(element) + " ";

  output += "]\n  ";
  for (int i = 1; i <= length_; ++i)
    this->is_a_tap(i - 1) ? output += "^ " : output += "  ";
  return output += "\n";
}

template <class T>
T LFSR<T>::step(void)
{
  T new_element = 0;
  T last = this->at(this->length_ - 1);
  for (auto tap : this->taps_)
  {
    new_element += this->lfsr_set_[tap];
  }
  this->rotate_ri(new_element % 2);
  return last;
}

template <class T>
LFSR<T> LFSR<T>::generate(int steps)
{
  LFSR<T> output_sec = *this;
  for (int i = 0; i < steps; ++i)
    output_sec.push_back(this->step(), output_sec);
  return output_sec;
}

/* Private methods */

template <class T>
void LFSR<T>::rotate_ri(const T &new_element)
{
  for (int i = this->length_ - 1; i > 0; --i)
    this->lfsr_set_[i] = this->lfsr_set_[i - 1];
  this->lfsr_set_[0] = new_element;
}

template <class T>
void LFSR<T>::rotate_le(const T &new_element)
{
  for (int i = 0; i < this->length_ - 1; ++i)
    this->lfsr_set_[i] = this->lfsr_set_[i + 1];
  this->lfsr_set_[this->length_ - 1] = new_element;
}

template <class T>
void LFSR<T>::initialize(const T &def_input)
{
  for (int i = 0; i < this->length_; ++i)
    this->lfsr_set_.push_back(def_input);
}

template <class T>
void LFSR<T>::push_back(const T &new_element, LFSR<T> &secuence)
{
  secuence.lfsr_set_.push_back(new_element);
  secuence.length_++;
}

template <class T>
bool LFSR<T>::is_a_tap(const int &i) const
{
  for (auto tap : this->taps_)
    if (i == tap)
      return true;
  return false;
}

#endif /* LFSR_H_ */