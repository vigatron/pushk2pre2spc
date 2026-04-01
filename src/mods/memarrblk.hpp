#ifndef MEMARRBLK_HPP
#define MEMARRBLK_HPP

#include <vector>
#include <cstdint>
#include <fstream>
#include <string>

class MemArrBlk {
private:
    std::vector<uint8_t> data_;

public:
    MemArrBlk() = default;

    /// Загрузка блока данных из бинарного файла
    /// @param filename путь к файлу
    /// @param offset смещение в байтах от начала файла (по умолчанию 0)
    /// @param length количество байт для чтения (по умолчанию 0 — читаем до конца файла)
    /// @return true если загрузка успешна, false если произошла ошибка
    bool load(const std::string& filename, std::size_t offset = 0, std::size_t length = 0) {
        data_.clear();

        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return false; // файл не открылся
        }

        // Определение размера файла
        file.seekg(0, std::ios::end);
        std::size_t fileSize = static_cast<std::size_t>(file.tellg());

        if (offset >= fileSize) {
            return false; // смещение за пределами файла
        }

        // Если length == 0, читаем до конца файла
        if (length == 0) {
            length = fileSize - offset;
        }

        // Проверка выхода за пределы файла
        if (offset + length > fileSize) {
            return false; // пользователь запросил больше, чем доступно
        }

        // Перемещение указателя и чтение данных
        file.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
        data_.resize(length);

        if (!file.read(reinterpret_cast<char*>(data_.data()), static_cast<std::streamsize>(length))) {
            data_.clear();
            return false; // ошибка чтения
        }

        return true;
    }

    /// Доступ к данным (только для чтения)
    const std::vector<uint8_t>& data() const noexcept {
        return data_;
    }

    /// Проверка, загружены ли данные
    bool empty() const noexcept {
        return data_.empty();
    }

    /// Размер загруженного блока
    std::size_t size() const noexcept {
        return data_.size();
    }
};

#endif // MEMARRBLK_HPP
