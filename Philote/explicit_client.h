#pragma once

#include <string>
#include <map>
#include <utility>
#include <Philote/array.h>
#include <Philote/discrete_array.h>

namespace philote
{
    /**
     * @brief Client class for calling a remote explicit discipline.
     *
     * This class may be inherited from or used by MDO framework developers.
     * However, it is a fully functional Philote MDO client.
     */
    class ExplicitClient
    {
    public:
        //! Constructor
        ExplicitClient();

        //! Destructor
        ~ExplicitClient();

        /**
         * @brief Calls the setup function on the remote analysis server.
         *
         */
        void RemoteSetup();

        /**
         * @brief Calls the remote analysis server function evaluation via gRPC.
         *
         * Unlike the analysis server, this function does not need to be
         * overridden, as it contains all logic necessary to retrieve the remote
         * function evaluation.
         *
         * @param inputs
         * @param discrete_inputs
         * @param outputs
         * @param discrete_outputs
         */
        void RemoteCompute(std::map<std::string, Array> &inputs,
                           std::map<std::string, DiscreteArray> &discrete_inputs,
                           std::map<std::string, Array> &outputs,
                           std::map<std::string, DiscreteArray> &discrete_outputs);

        /**
         * @brief Calls the remote analysis server function evaluation via gRPC.
         *
         * Unlike the analysis server, this function does not need to be
         * overridden, as it contains all logic necessary to retrieve the remote
         * gradient evaluation.
         *
         * @param inputs
         * @param discrete_inputs
         * @param partials
         */
        void RemotePartials(std::map<std::string, Array> &inputs,
                            std::map<std::string, DiscreteArray> &discrete_inputs,
                            std::map<std::pair<std::string, std::string>, Array> &partials);

    private:
        //! names of all functions defined for this discipline
        std::vector<std::string> funcs_;

        //! shape of all functions defined for this discipline
        std::map<std::string, std::vector<size_t>> funcs_shape_;

        //! units of all functions defined for this discipline
        std::map<std::string, std::string> funcs_units_;

        //! names of all discrete functions defined for this discipline
        std::vector<std::string> discrete_funcs_;

        //! shape of all discrete functions defined for this discipline
        std::map<std::string, std::vector<size_t>> discrete_funcs_shape_;

        //! shape of all discrete functions defined for this discipline
        std::map<std::string, std::string> discrete_funcs_units_;

        //! names of all variables defined for this discipline
        std::vector<std::string> vars_;

        //! shape of all variables defined for this discipline
        std::map<std::string, std::vector<size_t>> vars_shape_;

        //! units of all variables defined for this discipline
        std::map<std::string, std::string> vars_units_;

        //! names of all discrete variables defined for this discipline
        std::vector<std::string> discrete_vars_;

        //! shape of all discrete variables defined for this discipline
        std::map<std::string, std::vector<size_t>> discrete_vars_shape_;

        //! units of all discrete variables defined for this discipline
        std::map<std::string, std::string> discrete_vars_units_;

        //! vector of all defined partials
        std::vector<std::pair<std::string, std::string>> partials_;
    };
} // namespace philote