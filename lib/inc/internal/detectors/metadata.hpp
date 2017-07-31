#pragma once

#include <unordered_map>
#include <boost/variant.hpp>

namespace whereami { namespace detectors {

    /**
     * Metadata values can be string, boolean, or int
     */
    using metadata_value = boost::variant<std::string, bool, int>;

    /**
     * Metadata container
     */
    class metadata
    {
    public:
        /**
         * Set a key with a string value using a string
         * @param key The key
         * @param value The value
         */
        void set(std::string const& key, std::string const& value);

        /**
         * Set a key with a string value using a string literal
         * @param key The key
         * @param value The value
         */
        void set(std::string const& key, const char *value);

        /**
         * Set a key with a boolean value
         * @param key The key
         * @param value The value
         */
        void set(std::string const& key, bool value);

        /**
         * Set a key with an integer value
         * @param key The key
         * @param value The value
         */
        void set(std::string const& key, int value);

        /**
         * Retrieve a metadata value by key
         * @tparam T The expected type of the value
         * @param key The key
         * @return
         */
        template<typename T>
        T get(std::string const& key) const throw(boost::bad_get)
        {
            auto it = data_.find(key);
            if (it == data_.end()) {
                return {};
            }
            return boost::get<T>((*it).second);
        }

    protected:
        /**
         * Metadata key/value map
         */
        std::unordered_map <std::string, metadata_value> data_;
    };

}}  // namespace whereami::detectors
