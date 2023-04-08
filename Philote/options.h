#include <cstddef>

/**
 * @brief Struct that stores options
 *
 */
struct StreamOptions
{
    /**
     * @brief Maximum number of doubles that will be sent per stream message.
     *
     */
    size_t num_double;

    /**
     * @brief Maximum number of integers that will be sent per stream message.
     *
     */
    size_t num_int;
};