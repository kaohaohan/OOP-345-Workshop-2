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

class Database {
  static std::shared_ptr<Database> m_ptr;
  Database() = default;

  size_t m_size;
  std::string m_keys[20];
  std::string m_values[20];
  std::string m_fileName;
  Database(const std::string &filename);

public:
  // static 型別 名字
  static std::shared_ptr<Database> getInstance(const std::string &filename);
  Err_Status GetValue(const std::string &key, std::string &value);
  Err_Status SetValue(const std::string &key, const std::string &value);
  ~Database();
};
} // namespace seneca
#endif