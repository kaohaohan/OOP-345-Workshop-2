#ifndef SENECA_DATABASE_H
#define SENECA_DATABASE_H

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace seneca {

enum class Err_Status {
  Err_Success,
  Err_NotFound,
  Err_OutOfMemory,
};
template <typename T> class Database {
  static std::shared_ptr<Database<T>> m_ptr;
  Database();

  size_t m_size;
  std::array<std::string, 20> m_keys;
  std::array<T, 20> m_values;
  std::string m_fileName;
  Database(const std::string &filename);
  void encryptDecrypt(T &value);

public:
  // static 型別 名字
  static std::shared_ptr<Database<T>> getInstance(const std::string &filename);
  Err_Status GetValue(const std::string &key, T &value);
  Err_Status SetValue(const std::string &key, const T &value);
  ~Database();
};
} // namespace seneca
#endif