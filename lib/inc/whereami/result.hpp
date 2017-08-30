#pragma once

#include <whereami/metadata.hpp>

namespace whereami {

    /**
     * Represents the result of a hypervisor detector
     */
    class result
    {
    public:
        /**
         * Constructs a result given a hypervisor name
         * @param name The name of the hypervisor this result represents
         */
        result(std::string const& name): name_(name) {}

        /**
         * Retrieves the name of the hypervisor
         * @return Returns name of the hypervisor
         */
        std::string name() const;

        /**
         * Reports whether the hypervisor was detected
         * @return Returns true if the hypervisor was detected
         */
        bool valid() const;

        /**
         * Marks the result as having successfully detected the hypervisor
         */
        void validate();

        /**
         * Returns all metadata
         * @return all metadata for this hypervisor
         */
        std::unordered_map<std::string, metadata_value> metadata() const;

        /**
         * Sets a metadata key and value
         * @tparam T The type of the value
         * @param key The key
         * @param value The value
         */
        template<typename T>
        void set(std::string const& key, T&& value)
        {
            metadata_.set(key, std::forward<T>(value));
        }

        /**
         * Retrieves a metadata value by key
         * @tparam T The expected type of the value
         * @param key The key
         * @return Returns the value
         */
        template<typename T>
        T get(std::string const& key) const throw(boost::bad_get)
        {
            return metadata_.get<T>(key);
        }

    protected:
        /**
         * The name of the hypervisor this result respresents
         */
        std::string name_;
        /**
         * Whether this hypervisor has been detected
         */
        bool valid_ = false;
        /**
         * Metadata about the hypervisor
         */
        class metadata metadata_;
    };

};  // namespace whereami
