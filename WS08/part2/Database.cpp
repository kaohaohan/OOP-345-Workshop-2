#include "Database.h"
#include <algorithm>

namespace seneca {

template <typename T> std::shared_ptr<Database<T>> Database<T>::m_ptr = nullptr;

// fuck instruction is shit
template <typename T> Database<T>::Database() : m_size(0) {
  m_keys.fill("");
  m_values.fill(T{});
}
template <typename T> Database<T>::Database(const std::string &filename) {
  m_keys.fill("");
  m_values.fill(T{});
  // prints to the screen the address of the current instance
  // and the prototype of the constructor (see sample output for details)
  std::cout << "[" << m_ptr << "]"
            << " Database(const std::string&)" << std::endl;
  // Ashleigh_Barty      $3,765,182
  m_size = 0;
  std::ifstream file(filename);

  std::string key;
  T value;
  while (file >> key >> value) {
    std::replace(key.begin(), key.end(), '_', ' ');
    m_keys[m_size] = key;
    encryptDecrypt(value);
    m_values[m_size] = value;
    m_size++;
  }
  m_fileName = filename;
}
template <typename T>
std::shared_ptr<Database<T>>
Database<T>::getInstance(const std::string &filename) {
  if (m_ptr != nullptr) {
    return m_ptr;
  } else {
    // new 一個shared pointer
    m_ptr = std::shared_ptr<Database<T>>(new Database<T>(filename));

    return m_ptr;
  }
}
template <typename T>
Err_Status Database<T>::GetValue(const std::string &key, T &value) {
  for (size_t i = 0; i < m_size; i++) {
    if (m_keys[i] == key) {
      value = m_values[i];
      return Err_Status::Err_Success;
    }
  }
  return Err_Status::Err_NotFound;
}

template <typename T>
Err_Status Database<T>::SetValue(const std::string &key, const T &value) {
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

template <typename T> Database<T>::~Database() {
  std::cout << "[" << m_ptr << "]"
            << " ~Database()" << std::endl;
  std::string outputFilename = m_fileName + ".bkp.txt";
  std::ofstream outputFile(outputFilename);
  if (outputFile.is_open()) {
    for (size_t i = 0; i < m_size; ++i) {
      T value = m_values[i];
      encryptDecrypt(value);
      outputFile << std::left << std::setw(25) << m_keys[i] << " -> " << value
                 << std::endl;
    }
    outputFile.close();
  } else {
    std::cerr << " File error!!!!" << outputFilename << std::endl;
  }
}

template <typename T> void Database<T>::encryptDecrypt(T &value) {}
// specialize the encryptDecrypt() for the type std::string as following
// (pseudocode)
template <> void Database<std::string>::encryptDecrypt(std::string &value) {
  const char secret[]{"secret encryption key"};
  for (auto &C : value) {
    for (auto K : secret) {
      C = C ^ K;
    }
  }
};
template <> void Database<long long>::encryptDecrypt(long long &value) {
  const char secret[]{"super secret encryption key"};
  char *bytes = reinterpret_cast<char *>(&value);
  size_t totalBytes = sizeof(value);
  for (size_t i = 0; i < totalBytes; i++) {
    for (const auto &K : secret) {
      bytes[i] = bytes[i] ^ K;
    }
  }
};
template class Database<std::string>;
template class Database<long long>;
} // namespace seneca
