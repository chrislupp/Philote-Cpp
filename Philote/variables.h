#include <map>
#include <vector>
#include <string>

namespace philote
{
    /**
     * @brief Enum defining the type of variable being used.
     *
     */
    enum VariableType
    {
        kInput,
        kDiscreteInput,
        kOutput,
        kDiscreteOutput
    };

    /**
     * @brief Class for saving variable metadata.
     *
     */
    class VariableMeta
    {
    public:
        /**
         * @brief Construct a new Variable Meta object
         *
         */
        VariableMeta();

        /**
         * @brief Destroy the Variable Meta object
         *
         */
        ~VariableMeta();

        /**
         * @brief Adds an input to the list of variables.
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddInput(const std::string name, const std::vector<size_t> shape,
                      const std::string units);

        /**
         * @brief Adds a discrete input to the list of variables
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddDiscreteInput(const std::string name,
                              const std::vector<size_t> shape,
                              const std::string units);

        /**
         * @brief Adds an output to the list of variables
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddOutput(const std::string name, const std::vector<size_t> shape,
                       const std::string units);

        /**
         * @brief Adds a discrete output to the list of variables
         *
         * @param name
         * @param shape
         * @param units
         */
        void AddDiscreteOutput(const std::string name,
                               const std::vector<size_t> shape,
                               const std::string units);

        /**
         * @brief Returns the number of variables saved (including all types)
         *
         * @return size_t Number of variables in the discipline (all types).
         */
        size_t NumVariables() const;

    private:
        /**
         * @brief Maps the name of the variable to its type.
         *
         */
        std::map<std::string, VariableType> type_;

        /**
         * @brief Maps the name of the variable to its shape.
         *
         */
        std::map<std::string, std::vector<size_t>> shape_;

        /**
         * @brief Maps the name of the variable to its units
         *
         */
        std::map<std::string, std::string> units_;

    }; // VariableMeta
} // namespace philote