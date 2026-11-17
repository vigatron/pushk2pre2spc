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

    /// Loading data block from binary file
    /// @param filename Path to the file
    /// @param offset Offset in bytes from the start of the file (default 0)
    /// @param length Number of bytes to read (default 0 = read to end of file)
    /// @return true if loading succeeded, false if an error occurred
    bool load(const std::string& filename, std::size_t offset = 0, std::size_t length = 0) {
        data_.clear();

        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            return false; // file did not open
        }

        // Determining file size
        file.seekg(0, std::ios::end);
        std::size_t fileSize = static_cast<std::size_t>(file.tellg());

        if (offset >= fileSize) {
            return false; // offset out of bounds
        }

        // If length == 0, read to end of file
        if (length == 0) {
            length = fileSize - offset;
        }

        // Bounds check
        if (offset + length > fileSize) {
            return false; // requested more than available
        }

        // Moving pointer and reading data
        file.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
        data_.resize(length);

        if (!file.read(reinterpret_cast<char*>(data_.data()), static_cast<std::streamsize>(length))) {
            data_.clear();
            return false; // read error
        }

        return true;
    }

    /// Access to data (read only)
    const std::vector<uint8_t>& data() const noexcept {
        return data_;
    }

    /// Check whether data is loaded
    bool empty() const noexcept {
        return data_.empty();
    }

    /// Size of loaded block
    std::size_t size() const noexcept {
        return data_.size();
    }
};

#endif // MEMARRBLK_HPP
