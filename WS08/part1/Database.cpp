#include "Database.h"
#include <algorithm>

namespace seneca {
std::shared_ptr<Database> Database::m_ptr = nullptr;
Database::Database(const std::string &filename) {
  // prints to the screen the address of the current instance
  // and the prototype of the constructor (see sample output for details)
  std::cout << "[" << m_ptr << "]"
            << " Database(const std::string&)" << std::endl;
  // Ashleigh_Barty      $3,765,182
  m_size = 0;
  std::ifstream file(filename);

  std::string key;
  std::string value;
  while (file >> key >> value) {
    std::replace(key.begin(), key.end(), '_', ' ');
    m_keys[m_size] = key;
    m_values[m_size] = value;
    m_size++;
  }
  m_fileName = filename;
}
std::shared_ptr<Database> Database::getInstance(const std::string &filename) {
  if (m_ptr != nullptr) {
    return m_ptr;
  } else {
    // new 一個shared pointer
    m_ptr = std::shared_ptr<Database>(new Database(filename));

    return m_ptr;
  }
}
Err_Status Database::GetValue(const std::string &key, std::string &value) {
  for (size_t i = 0; i < m_size; i++) {
    if (m_keys[i] == key) {
      value = m_values[i];
      return Err_Status::Err_Success;
    }
  }
  return Err_Status::Err_NotFound;
}
Err_Status Database::SetValue(const std::string &key,
                              const std::string &value) {
  for (size_t i = 0; i < m_size; i++) {
    if (m_keys[i] == key) {
      m_values[i] = value;
      return Err_Status::Err_Success;
    }
  }
  if (m_size < 20) {
    m_keys[m_size] = key;
    m_values[m_size] = value;
    m_size++;
    return Err_Status::Err_Success;
  } else {
    return Err_Status::Err_OutOfMemory;
  }
}
Database::~Database() {
  std::cout << "[" << m_ptr << "]"
            << " ~Database()" << std::endl;
  std::string outputFilename = m_fileName + ".bkp.txt";
  std::ofstream outputFile(outputFilename);
  if (outputFile.is_open()) {
    for (size_t i = 0; i < m_size; ++i) {
      outputFile << std::left << std::setw(25) << m_keys[i] << " -> "
                 << m_values[i] << std::endl;
    }
    outputFile.close();
  } else {
    std::cerr << " File error!!!!" << outputFilename << std::endl;
  }
}
} // namespace seneca
